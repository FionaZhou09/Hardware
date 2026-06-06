from huggingface_hub import hf_hub_download
import torch
import torch.nn as nn
from torchvision import models, transforms
import cv2
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision
from PIL import Image
import time
import serial
import serial.tools.list_ports


# Download model files
model_path = hf_hub_download(
    repo_id="huzaifanasirrr/realtime-sign-language-translator",
    filename="best_model.pth"
)

mediapipe_path = hf_hub_download(
    repo_id="huzaifanasirrr/realtime-sign-language-translator",
    filename="hand_landmarker.task"
)


class SignLanguageModel(nn.Module):
    def __init__(self, num_classes=26):
        super().__init__()

        self.model = models.resnet18(weights=None)

        self.model.fc = nn.Sequential(
            nn.Dropout(0.5),
            nn.Linear(512, 512),
            nn.ReLU(),
            nn.Dropout(0.3),
            nn.Linear(512, num_classes)
        )

    def forward(self, x):
        return self.model(x)


# Use CPU first for stability on Mac
device = torch.device("cpu")
print("Using device:", device)

model = SignLanguageModel(num_classes=26)

checkpoint = torch.load(model_path, map_location=device)
model.load_state_dict(checkpoint["model_state_dict"])
model.to(device)
model.eval()

print("Model loaded successfully!")

if "val_acc" in checkpoint:
    print(f"Validation Accuracy: {checkpoint['val_acc']:.2f}%")


# MediaPipe setup
base_options = python.BaseOptions(model_asset_path=mediapipe_path)

options = vision.HandLandmarkerOptions(
    base_options=base_options,
    running_mode=vision.RunningMode.VIDEO,
    num_hands=1
)

hands = vision.HandLandmarker.create_from_options(options)


preprocess = transforms.Compose([
    transforms.Resize((224, 224)),
    transforms.ToTensor(),
    transforms.Normalize(
        mean=[0.485, 0.456, 0.406],
        std=[0.229, 0.224, 0.225]
    )
])

idx_to_class = {i: chr(65 + i) for i in range(26)}


# Serial setup — auto-detect Nucleo VCP or fall back to manual
def find_stm32_port():
    for port in serial.tools.list_ports.comports():
        desc = port.description.lower()
        if "stlink" in desc or "nucleo" in desc or "stm32" in desc or "usbmodem" in port.device:
            return port.device
    return None

SERIAL_PORT = find_stm32_port() or "/dev/tty.usbmodemXXXX"  # edit if auto-detect fails
BAUD_RATE = 115200

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    time.sleep(0.1)
    print(f"Serial connected: {SERIAL_PORT} @ {BAUD_RATE}")
except serial.SerialException as e:
    ser = None
    print(f"Serial not available ({e}). Running without controller output.")

last_command = None  # track last sent command to avoid flooding


# MacBook webcam: use AVFoundation backend
cap = cv2.VideoCapture(0, cv2.CAP_AVFOUNDATION)

if not cap.isOpened():
    raise RuntimeError(
        "Could not open webcam. Go to System Settings > Privacy & Security > Camera and allow Terminal."
    )

timestamp_ms = int(time.time() * 1000)

print("Webcam started. Press Q to quit.")

try:
    while True:
        ret, frame = cap.read()

        if not ret:
            print("Failed to read frame, retrying...")
            continue

        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        mp_image = mp.Image(
            image_format=mp.ImageFormat.SRGB,
            data=frame_rgb
        )

        now_ms = int(time.time() * 1000)
        results = hands.detect_for_video(mp_image, now_ms)

        if results.hand_landmarks:
            landmarks = results.hand_landmarks[0]

            h, w = frame.shape[:2]
            x_coords = [lm.x * w for lm in landmarks]
            y_coords = [lm.y * h for lm in landmarks]

            x_min = max(0, int(min(x_coords)) - 40)
            y_min = max(0, int(min(y_coords)) - 40)
            x_max = min(w, int(max(x_coords)) + 40)
            y_max = min(h, int(max(y_coords)) + 40)

            hand_crop = frame[y_min:y_max, x_min:x_max]

            if hand_crop.size > 0:
                pil_image = Image.fromarray(
                    cv2.cvtColor(hand_crop, cv2.COLOR_BGR2RGB)
                )

                tensor = preprocess(pil_image).unsqueeze(0).to(device)

                with torch.no_grad():
                    outputs = model(tensor)
                    probabilities = torch.softmax(outputs, dim=1)
                    top_prob, top_idx = torch.max(probabilities, dim=1)

                predicted_class = idx_to_class[top_idx.item()]
                confidence = top_prob.item() * 100

                # Send command to STM32 only when prediction changes
                command = b'L' if predicted_class == 'L' else b'R'
                if ser and command != last_command:
                    ser.write(command)
                    last_command = command
                    response = ser.readline()
                    if response:
                        print(f"STM32: {response.decode(errors='replace').strip()}")

                cv2.rectangle(
                    frame,
                    (x_min, y_min),
                    (x_max, y_max),
                    (0, 255, 0),
                    2
                )

                cv2.putText(
                    frame,
                    f"{predicted_class}: {confidence:.1f}%",
                    (x_min, max(30, y_min - 10)),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.9,
                    (0, 255, 0),
                    2
                )

        cv2.imshow("ASL Recognition - Press Q to quit", frame)

        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

finally:
    cap.release()
    cv2.destroyAllWindows()
    if ser:
        ser.close()
    print("Camera released.")
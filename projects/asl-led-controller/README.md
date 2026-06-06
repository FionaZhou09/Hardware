# ASL LED Controller

Uses a webcam to detect American Sign Language (ASL) hand signs in real time and sends commands to an STM32 Nucleo-G474RE over USB serial. The board lights up one of two LEDs depending on the detected sign.

- Sign **L** → Left LED on (built-in LD2, green)
- Any other sign → Right LED on (external LED on PB5)

---

## Files

| File | Purpose |
|------|---------|
| `asl_webcam.py` | Python — captures webcam, classifies ASL sign, sends `'L'`/`'R'` over serial |
| `stm32_main.c` | STM32 firmware — receives serial byte, toggles LEDs, replies `"OK\n"` |

---

## Hardware Required

- STM32 Nucleo-G474RE
- USB cable (connects Nucleo to computer — also carries serial data via ST-Link VCP)
- 1× external LED (any colour)
- 1× 330Ω resistor
- Breadboard + jumper wires
- Webcam (built-in or USB)

---

## LED Wiring

### Left LED — built-in, no wiring needed

The Nucleo-G474RE has a green LED (LD2) already on the board connected to **PA5**. Nothing to wire.

### Right LED — external, wire it up

```
STM32 Pin PB5  ──►|── [330Ω] ── GND
                 LED
```

Step by step:
1. Push the LED into the breadboard. Note which leg is longer (anode, +).
2. Connect a jumper wire from **PB5** (Arduino header **D4**) to the **anode** (long leg) of the LED.
3. Connect a 330Ω resistor from the **cathode** (short leg) to any **GND** pin on the Nucleo.

### Nucleo Pin Reference

| Signal | Nucleo Pin | Arduino Label | Notes |
|--------|-----------|---------------|-------|
| Left LED (L) | PA5 | — | Built-in LD2, no wiring |
| Right LED (R) | PB5 | D4 | External LED + 330Ω to GND |
| UART TX | PA2 | D1 | Internal ST-Link, no wiring |
| UART RX | PA3 | D0 | Internal ST-Link, no wiring |
| GND | GND | GND | Any GND pin on the board |

---

## Setup

### 1. Flash the STM32

1. Open **STM32CubeIDE** and create a new project for the **Nucleo-G474RE**
2. Replace the generated `Core/Src/main.c` with `stm32_main.c` from this folder
3. Build and flash via the ST-Link (Run → Debug or Run)

### 2. Install Python dependencies

```bash
pip install torch torchvision mediapipe opencv-python pillow huggingface_hub pyserial
```

### 3. Find your serial port

Plug in the Nucleo via USB, then run:

```bash
ls /dev/tty.*
```

Look for something like `/dev/tty.usbmodemXXXX`. The script will try to auto-detect it. If it fails, open `asl_webcam.py` and set `SERIAL_PORT` manually at the top of the serial setup section.

### 4. Run

```bash
python asl_webcam.py
```

A webcam window opens. Hold your hand up to the camera:
- Show the **L** sign → left LED lights up
- Show any other sign → right LED lights up

Press **Q** to quit.

---

## How It Works

```
Webcam frame
  → MediaPipe: find 21 hand landmarks
  → Crop hand region
  → ResNet18 (fine-tuned on ASL): classify A–Z
  → If letter changed: send 'L' or 'R' over USB serial @ 115200
  → STM32 receives byte → toggles LEDs → replies "OK\n"
  → Python prints ACK
```

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| `Serial not available` printed | Nucleo not plugged in, or wrong port — check `ls /dev/tty.*` |
| Webcam window doesn't open | Allow Terminal camera access in System Settings → Privacy & Security → Camera |
| Wrong LED lights up | Double-check PB5 → anode, cathode → 330Ω → GND wiring |
| LED too dim / too bright | Swap the 330Ω resistor for a higher / lower value |
| STM32 doesn't respond | Confirm USART2 is enabled in CubeMX and the firmware is flashed |

# Smart Kids Bike Safety System

A safety device designed for kids riding bikes at night. Cars can detect a bike going straight, but cannot predict a turn. This system solves two problems:

1. **Turn Signal Indicators** — bright flashing LEDs warn cars when the rider is turning left or right.
2. **Ultrasonic Radar Scanner** — sweeping HC-SR04 sensor warns the rider of nearby obstacles with audio and visual alerts.

---

## Hardware Kit

![STM32 kit with MPU6050 and servo](images/hardware-kit.jpg)

![Expanded sensor kit](images/expanded-sensor-kit.jpg)

Current components include:

- STM32 Nucleo development board
- MPU6050 IMU sensor: accelerometer and gyroscope
- MCP9808 high-accuracy I2C temperature sensor
- HC-SR04 ultrasonic distance sensor
- SG90 servo motors
- Speaker / buzzer module
- LEDs
- Breadboard
- Jumper wires

---

## Hardware Components

| Component | Role |
|---|---|
| STM32 Nucleo development board | Main microcontroller |
| MPU6050 IMU sensor (accelerometer + gyroscope) | Roll angle detection via I2C |
| HC-SR04 ultrasonic distance sensor | Obstacle detection via GPIO + Timer |
| SG90 servo motor | Radar sweep via PWM |
| Speaker / buzzer module | Proximity audio alert via PWM tone |
| LEDs (left turn, right turn, proximity indicator) | Visual warnings via GPIO |
| MCP9808 temperature sensor | Optional environmental monitor |
| Breadboard and jumper wires | Prototyping |

---

## Sub-System 1: Turn Signal Indicator (for cars)

### How it works

- The MPU6050 is mounted on the handlebar and measures **roll angle** via I2C.
- The STM32 reads roll continuously.
- If roll > +threshold → **right turn detected** → right LED flashes.
- If roll < −threshold → **left turn detected** → left LED flashes.
- Straight riding → both LEDs on solid (running lights).

### Peripherals used

| Peripheral | Purpose |
|---|---|
| I2C | MPU6050 IMU data |
| GPIO output | Left LED, Right LED |
| UART | Serial debug output |

---

## Sub-System 2: Ultrasonic Radar Scanner (for the rider)

### How it works

- The SG90 servo sweeps the HC-SR04 sensor across a ~180° arc.
- The STM32 reads distance at each servo angle using timer input capture on the echo pin.
- If an object is detected within the **danger zone (< 50 cm)** → buzzer beeps faster.
- If an object is detected within the **critical zone (< 20 cm)** → continuous alarm tone.

### Peripherals used

| Peripheral | Purpose |
|---|---|
| GPIO output | HC-SR04 Trigger pin |
| GPIO input + Timer input capture | HC-SR04 Echo pin (pulse width measurement) |
| PWM (TIM) | SG90 servo sweep (50 Hz, 1–2 ms pulse) |
| PWM (TIM) | Buzzer tone generation |
| GPIO output | Proximity indicator LEDs |

---

## STM32 Logic Flow

```
MPU6050 (I2C)
  └─► Roll angle ──► Left/Right LED flash (GPIO)

HC-SR04 (GPIO + Timer input capture)
  └─► Distance ──► Buzzer alert (PWM tone)
        └─► SG90 Servo sweep (PWM 50 Hz)
              └─► Radar scan arc (~180°)
```

---

## Build Phases

| Phase | Goal |
|---|---|
| 1 | MPU6050 roll detection → left/right LED turn signals |
| 2 | HC-SR04 distance reading → buzzer proximity alert |
| 3 | SG90 servo sweep → full 180° radar scan |
| 4 | Integrate both sub-systems on one STM32 |
| 5 | Tune thresholds, add night-mode LED brightness control |

---

## Peripheral Summary

| Peripheral | Usage |
|---|---|
| I2C | MPU6050 IMU |
| GPIO output | LEDs (left, right, proximity), HC-SR04 trigger |
| GPIO input | HC-SR04 echo |
| Timer input capture | Echo pulse width → distance calculation |
| PWM | SG90 servo (50 Hz) + buzzer tone |
| UART | Serial debug |

---

## Learning Outcomes

- STM32 I2C communication with IMU
- Timer input capture for pulse-width measurement
- PWM servo control at 50 Hz
- GPIO interrupt and polling patterns
- Sensor fusion decision logic (angle + distance → action)
- Real-time embedded control loop design

# STM32 Robotics Starter Kit: Learning Roadmap

This repository documents a hands-on robotics learning path built around an STM32 Nucleo development board and a small collection of sensors, actuators, and prototyping parts.

The goal is to grow from simple embedded programming into robotics control, sensing, autonomy, and AI-assisted motion analysis.

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

## Core Learning Goals

This kit can be used to learn:

- STM32 microcontroller programming
- GPIO input and output
- I2C communication
- PWM signal generation
- Servo motor control
- Sensor calibration
- Real-time embedded systems
- Closed-loop control
- Robotics feedback systems
- Data collection for AI and machine learning

## Phase 1: Embedded Systems Fundamentals

Start by learning how to control the microcontroller directly.

Topics:

- STM32 project setup
- GPIO output with LEDs
- GPIO input with buttons or sensor signals
- Timing, delays, and hardware timers
- PWM generation
- Servo angle control
- Serial debugging

Starter projects:

- Blink LED patterns
- Button-controlled LED
- Servo angle sweep
- Servo angle control using PWM
- LED status indicator for sensor readings

Key project: **Servo Angle Control**

## Phase 2: Sensor Communication

Learn how STM32 communicates with external sensors.

Topics:

- I2C protocol
- Sensor registers
- Reading raw data
- Converting raw data into physical units
- Basic filtering and smoothing

Sensors:

- MPU6050 for motion and orientation
- MCP9808 for temperature

Projects:

- Read temperature from MCP9808
- Read acceleration from MPU6050
- Read gyroscope angular velocity
- Display sensor values through serial output
- Build a simple sensor dashboard on a computer

Key project: **STM32 Sensor Reader**

## Phase 3: Motion Sensing and Orientation

Use the MPU6050 to understand movement.

Measurements:

- Pitch
- Roll
- Angular velocity
- Motion
- Vibration
- Sudden acceleration

Projects:

- Digital inclinometer
- Tilt-controlled LED indicator
- Motion alarm
- Vibration detector
- Gesture detector using simple thresholds

Key project: **Digital Inclinometer**

## Phase 4: Distance, Environment, and Feedback

Add environmental awareness and user feedback.

New capabilities:

- Measure distance with HC-SR04
- Measure temperature with MCP9808
- Provide audio alerts with the speaker
- Provide visual feedback with LEDs
- React to nearby objects

Projects:

- Ultrasonic distance meter
- Parking distance indicator
- Temperature alarm
- Smart room monitor
- Distance-based sound alert
- LED bar indicator for distance
- Proximity-triggered servo gate

Key project: **Smart Distance and Temperature Monitor**

## Phase 5: Closed-Loop Control

Use sensor feedback to control physical movement.

Topics:

- Feedback loops
- Error calculation
- Proportional control
- PID control
- Servo stabilization
- Sensor noise and filtering

Control idea:

```text
MPU6050 -> STM32 -> Servo -> Automatic Correction
```

Projects:

- Self-leveling servo platform
- Tilt-compensating camera mount
- PID servo stabilizer
- Motion-triggered auto-correction system
- Servo follows board orientation in real time

Key project: **MPU6050-Based Servo Tracking System**

This single project teaches:

- STM32 development
- I2C communication
- IMU sensors
- PWM motor control
- Sensor feedback
- Basic robotics control systems

## Phase 6: Robotics Applications

Combine sensing and actuation into more complete robotics systems.

Project directions:

- Gesture-controlled robot arm
- Self-leveling camera mount
- Smart door lock
- Motion tracking system
- Obstacle detection robot
- Object-approach warning system
- Mini robotic security monitor
- Temperature-aware smart fan controller
- Servo-controlled ultrasonic scanner
- Interactive desk robot with lights and sound

Example system:

```text
Sensor input -> STM32 decision logic -> Servo / LED / speaker action
```

## Phase 7: AI and Robotics

Connect STM32 to a computer running Python and use sensor data for machine learning.

Workflow:

```text
Sensor Data
-> Data Collection
-> Feature Extraction
-> Machine Learning Model
-> Decision Making
-> Robot Action
```

Example AI applications:

- Fall detection
- Activity recognition
- Gesture classification
- Human motion analysis
- Vibration anomaly detection
- Temperature pattern detection
- Object distance behavior analysis
- Smart alarm classification

Possible Python tools:

- NumPy for data processing
- Pandas for logged sensor data
- Matplotlib for visualization
- scikit-learn for classical machine learning
- PyTorch for deeper motion models

## Project Brainstorming Directions

### Beginner Projects

- LED blink patterns
- Servo sweep
- Temperature logger
- Ultrasonic distance reader
- Motion detector
- Serial sensor monitor

### Intermediate Projects

- Digital tilt meter
- Distance-based alarm
- Smart temperature warning system
- Servo-controlled gate
- Ultrasonic object scanner
- Tilt-controlled servo pointer
- Motion-activated LED and sound system

### Advanced Projects

- Self-balancing platform
- PID-controlled stabilizer
- Gesture-controlled robot arm
- Mini obstacle-avoidance robot
- Sensor fusion dashboard
- AI gesture classifier
- Motion tracking and activity recognition system

### Creative Project Ideas

- Smart desk assistant that reacts to hand distance
- Mini robot that turns toward nearby objects
- Temperature-sensitive warning device
- Interactive hardware demo box with LEDs, sound, servo motion, and sensors
- Sensor-based game controller
- Motion-controlled music or sound effects
- DIY robotics learning exhibit

## Long-Term Robotics Roadmap

### Level 1: Embedded Basics

- STM32 programming
- GPIO
- PWM
- Servo control
- I2C sensors
- Basic serial debugging

### Level 2: Sensor Systems

- MPU6050
- MCP9808
- HC-SR04
- Sensor calibration
- Signal filtering
- Sensor dashboards

### Level 3: Control Systems

- Feedback control
- PID control
- Stabilization
- Servo-based correction
- Robotics kinematics basics

### Level 4: Robotics Integration

- Robot arms
- Mobile robots
- Obstacle detection
- Self-leveling platforms
- Multi-sensor behavior

### Level 5: AI Robotics

- Data collection
- Machine learning
- Computer vision
- ROS
- Autonomous navigation
- Reinforcement learning
- Human motion understanding

## Recommended First Full Project

### MPU6050-Based Servo Tracking System

Goal:

- Read tilt angle from the MPU6050
- Convert sensor readings into pitch or roll
- Map the angle to a servo position
- Make the servo follow board orientation in real time
- Add LED or speaker feedback when the angle passes a threshold

Why this project is a strong starting point:

- It uses both sensing and actuation
- It teaches I2C and PWM together
- It introduces closed-loop thinking
- It can later grow into stabilization, gimbals, drones, and robot balancing

## Next Best Expansion Project

### Smart Obstacle and Environment Monitor

Goal:

- Use the HC-SR04 to detect nearby objects
- Use MCP9808 to monitor temperature
- Use LEDs for visual status
- Use the speaker for alerts
- Use the servo to point, open, close, or react

This project connects multiple sensor types and creates a more complete embedded robotics behavior system.

# Project Context

## Target Hardware
- **Primary MCU/Processor**: STM32 (Nucleo series)
- **Secondary Processors**: —
- **Dev Board / Custom PCB**: STM32 Nucleo development board
- **Board Revision**: —

## Clock Configuration
- **HSE/HSI**:
- **PLL Config**:
- **System Clock Frequency**:

## Pin Mapping / GPIO Assignments
- I2C: MPU6050 (IMU), MCP9808 (temperature sensor)
- GPIO: HC-SR04 ultrasonic (trigger + echo), LEDs
- PWM: SG90 servo motors
- GPIO/PWM: Speaker/buzzer

## Memory Layout
- **Flash Size**:
- **RAM Size**:
- **Linker Script Regions**:

## Peripherals & Interfaces
- I2C (MPU6050, MCP9808)
- PWM / Timer (SG90 servo, buzzer)
- GPIO (HC-SR04, LEDs)
- UART (serial debug output)

## External Devices & Sensors
- MPU6050 — 6-axis IMU (accelerometer + gyroscope), I2C
- MCP9808 — high-accuracy temperature sensor, I2C
- HC-SR04 — ultrasonic distance sensor, GPIO trigger/echo
- SG90 — servo motors, PWM (50 Hz, 1–2 ms pulse)
- Speaker / buzzer module
- LEDs

## Communication Protocols
- **Protocol**: I2C (sensors), UART (serial debug)
- **Baud Rate / Mode**: TBD

## Software Stack
- **Build System**: TBD (likely STM32CubeIDE / Makefile)
- **Compile Command**:
- **HAL / Framework**: STM32 HAL (expected)
- **RTOS**: None (bare-metal, polling/interrupt driven)
- **Toolchain**: arm-none-eabi-gcc
- **Compiler Flags**:
- **External Libraries**:

## Development Environment
- **Host OS**: Windows
- **IDE**: TBD (likely STM32CubeIDE)
- **Debug Interface (SWD/JTAG)**: SWD (Nucleo on-board ST-Link)
- **Debug Probe (ST-Link/J-Link/OpenOCD)**: ST-Link (on-board)

## Debug Configuration
<!-- Auto-learned during debug sessions. Edit these directly to change debug settings. -->
- **GDB Server Command**:
- **GDB Executable**:
- **Firmware ELF Path**:
- **GDB Server Port**:

## Power Management
- **Sleep Modes**:
- **Power Domains**:
- **Battery / Power Source**: USB via Nucleo

## Boot Configuration
- **Bootloader**:
- **OTA Mechanism**:

## Interrupt Configuration
- **NVIC Priority Groups**:
- **Key ISRs**: HC-SR04 echo capture (timer input capture or EXTI)

## Compliance & Standards
-

## SDK / Library Paths
<!-- Paths to vendor SDKs or libraries the agent cannot download. -->
<!-- Example: /opt/zephyr-sdk-0.16.8, /home/user/STM32CubeF4, ~/ncs/v2.7.0 -->
-

## Supporting Devices
-

## Project Notes
- STM32 Robotics Starter Kit learning roadmap project
- 7-phase learning path: Embedded Basics → Sensor Systems → Control → Robotics → AI
- Recommended first project: MPU6050-Based Servo Tracking System (I2C + PWM + closed-loop)
- Next expansion: Smart Obstacle & Environment Monitor (HC-SR04 + MCP9808 + LEDs + servo)

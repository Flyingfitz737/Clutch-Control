# EMC Type 1 Controller - ESP32 Version

This folder contains the complete Arduino sketch for the EMC Type 1 Controller for ESP32.

## File Structure
- **EMC_Type_1_ESP32.ino** - Complete Arduino sketch (27KB+)

## Features
- User-configurable parameters via Serial Monitor
- Real-time RPM sensor input and PID control
- Servo motor control for clutch actuation
- LED arming light and comprehensive status feedback
- Serial command interface for remote operation
- **Bluetooth Classic communication** (Device: `EMC_Type_1_Controller`)
- Wireless remote control and monitoring
- Simultaneous Serial and Bluetooth feedback
- Non-volatile storage using ESP32 Preferences library
- Servo preposition feature for customized armed state position

## How to Use
1. Open **EMC_Type_1_ESP32.ino** in Arduino IDE
2. Install required libraries:
   - PID_v1 (Arduino IDE Library Manager)
   - ESP32Servo (Arduino IDE Library Manager)
   - BluetoothSerial (included with ESP32 Core)
3. Select your ESP32 board in Tools > Board
4. Upload to your ESP32 device

## Documentation
- [EMC_Type_1_README.md](../EMC_Type_1_README.md) - Detailed functionality documentation
- [System_Workflow_Overview.md](../System_Workflow_Overview.md) - Setup and usage guide

## Hardware Requirements
- ESP32 development board
- RPM sensor connected to GPIO19
- Potentiometers connected to GPIO34 and GPIO35
- Servo motor connected to GPIO18
- Arm switch connected to GPIO21
- LED connected to GPIO2 (or use built-in LED)

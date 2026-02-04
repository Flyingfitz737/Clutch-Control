# EMC Type 1 Controller - Arduino Uno Version

This folder contains the complete Arduino sketch for the EMC Type 1 Controller for Arduino Uno.

## File Structure
- **EMC_Type_1_Arduino.ino** - Complete Arduino sketch (19KB+)

## Features
- User-configurable parameters via Serial Monitor
- Real-time RPM sensor input and PID control
- Servo motor control for clutch actuation
- LED arming light and comprehensive status feedback
- Serial command interface for remote operation
- Non-volatile storage using EEPROM

## How to Use
1. Open **EMC_Type_1_Arduino.ino** in Arduino IDE
2. Install required libraries:
   - PID_v1 (Arduino IDE Library Manager)
   - Servo (included with Arduino IDE)
3. Select Arduino Uno in Tools > Board
4. Upload to your Arduino device

## Documentation
- [EMC_Type_1_README.md](../EMC_Type_1_README.md) - Detailed functionality documentation
- [System_Workflow_Overview.md](../System_Workflow_Overview.md) - Setup and usage guide

## Hardware Requirements
- Arduino Uno board
- RPM sensor
- Potentiometers
- Servo motor
- Arm switch
- LED for status indication

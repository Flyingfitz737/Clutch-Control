# EMC Type 1 Controller - Arduino Uno Implementation

## Overview
The EMC Type 1 controller is an Arduino Uno-based hydraulic clutch controller specifically designed for motorcycle applications. This implementation provides user-configurable parameters, automatic sensor inputs, PID control, and visual feedback through an LED arming light.

## Features

### 1. User-Defined Parameters
- **Target RPM Setting**: Set desired RPM setpoint via serial commands
- **PID Tuning**: Adjust Kp, Ki, and Kd constants in real-time
- **System Control**: Arm/disarm the system remotely via serial interface

### 2. Automatic Sensor Inputs
- **RPM Sensor**: Analog input from potentiometer or RPM sensor (Pin A0)
- **Secondary Potentiometer**: Additional analog input for system feedback (Pin A1)
- **Digital Switches**: Arm switch input with internal pullup resistors

### 3. PID Control Loop
- **Real-time Control**: Continuous PID computation for servo motor positioning
- **Servo Output**: 0-180 degree servo control for clutch actuation
- **Configurable Parameters**: Runtime adjustment of PID constants

### 4. Visual Feedback
- **Arming Light**: LED indicator on Pin 13 (built-in LED)
- **System Status**: Blinking pattern when armed, solid off when disarmed
- **Serial Monitor**: Comprehensive status reporting and command interface

## Hardware Connections

### Pin Assignments
```
Pin A0  - RPM Sensor/Potentiometer Input
Pin A1  - Secondary Potentiometer Input
Pin 2   - Arm Switch (Active LOW with internal pullup)
Pin 9   - Servo Motor PWM Output
Pin 13  - Arming Light LED (Built-in LED)
```

### Required Components
- Arduino Uno
- Servo motor (for clutch actuation)
- Potentiometer or RPM sensor
- Push button for arm switch
- LED (optional, built-in LED used by default)
- PID_v1 Arduino Library
- Servo Arduino Library

## Serial Commands

The system accepts the following commands via the Serial Monitor (9600 baud):

### Basic Commands
- `help` - Display available commands
- `status` - Show detailed system status
- `arm` - Arm the system
- `disarm` - Disarm the system

### Configuration Commands
- `setrpm <value>` - Set target RPM (1-5000)
  - Example: `setrpm 1500`
- `setpid <kp> <ki> <kd>` - Set PID constants
  - Example: `setpid 2.0 5.0 1.0`

## Operation

### Startup Sequence
1. Connect Arduino to computer
2. Open Serial Monitor at 9600 baud
3. System displays initialization message and help text
4. System begins reading sensors and displaying status

### Normal Operation
1. **Sensor Reading**: System continuously reads RPM sensor and switches
2. **PID Control**: When armed, PID controller adjusts servo position to maintain target RPM
3. **Visual Feedback**: Arming light blinks when system is armed
4. **Serial Output**: Status information displayed every 500ms

### Safety Features
- System returns servo to neutral position (90°) when disarmed
- Dual arming methods: physical switch or serial command
- Input validation for all serial commands
- Real-time status monitoring

## Example Usage

### Setting Target RPM
```
setrpm 1200
Target RPM set to: 1200.00
```

### Tuning PID Parameters
```
setpid 3.0 6.0 1.5
PID constants updated:
  Kp: 3.00
  Ki: 6.00
  Kd: 1.50
```

### Status Monitoring
```
RPM: 1180 | Target: 1200 | Servo: 95° | Armed: YES | PID Out: 95.00
```

## Dependencies

### Required Libraries
1. **PID_v1** - PID control library
   - Install via Arduino Library Manager
   - Search for "PID" by Brett Beauregard

2. **Servo** - Servo motor control
   - Included with Arduino IDE by default

### Installation
1. Install required libraries through Arduino IDE Library Manager
2. Copy the EMC Type 1 code to a new Arduino sketch
3. Upload to Arduino Uno
4. Connect hardware according to pin assignments
5. Open Serial Monitor for operation

## Customization

### Pin Configuration
Modify the pin definitions at the top of the code to match your hardware setup:
```cpp
const int rpmSensorPin = A0;        // Change as needed
const int servoPin = 9;             // PWM-capable pin required
const int armLightPin = 13;         // Any digital pin
```

### PID Parameters
Default PID values can be adjusted in the code or via serial commands:
```cpp
double Kp = 2.0, Ki = 5.0, Kd = 1.0; // Default values
```

### RPM Range
Adjust the RPM mapping range based on your sensor:
```cpp
currentRPM = map(rpmValue, 0, 1023, 0, 3000); // Maps to 0-3000 RPM
```

## Troubleshooting

### Common Issues
1. **Servo not responding**: Check PWM pin connection and power supply
2. **No serial communication**: Verify baud rate is set to 9600
3. **Erratic readings**: Check sensor connections and power supply stability
4. **PID oscillation**: Reduce Kp value or increase Kd value

### Debug Information
Use the `status` command to view detailed system information including:
- Raw sensor readings
- Current PID parameters
- System state
- Pin status

## Safety Considerations

⚠️ **Important Safety Notes**:
- Always test the system in a safe environment before installation
- Ensure proper electrical connections and insulation
- Verify servo movement range is appropriate for your clutch mechanism
- Monitor system operation during initial testing
- Have manual override capability available

## License
This code is provided as-is for educational and experimental purposes. Use at your own risk.
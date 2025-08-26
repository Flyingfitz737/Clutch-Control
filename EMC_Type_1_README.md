# EMC Type 1 Controller

The EMC Type 1 Controller is a fully functional Arduino-based hydraulic clutch controller. Here's an analysis of its **purpose** and **functionality**:

---

## Purpose
The EMC Type 1 Controller is designed to:

1. **Control a hydraulic clutch system** using an Arduino Uno.
2. Provide **automatic control via PID (Proportional-Integral-Derivative)** feedback loops for precise management of RPM.
3. Allow for **manual clutch control** via a potentiometer.
4. Offer **user-defined parameters** for customizing the control system, such as RPM targets, PID constants, and operating modes.
5. Provide **real-time feedback** and control through serial communication and LED signals.

---

## Functionality
The main features and components of the code are:

### **Input Sensors**
- **RPM Pulse Sensor** (`rpmSensorPin`): Measures engine speed in pulses per revolution and calculates RPM using timing intervals.
- **Clutch Switch** (`clutchSwitchPin`): Digital switch input for clutch control functionality.
- **Manual Control Potentiometer** (`manualPotPin`): Potentiometer for manual servo control.

### **Outputs**
- **Servo Motor Control**:
  - Adjusts the hydraulic clutch position for engagement or disengagement.
  - Operates in a range of 0-180 degrees.
- **LED Feedback**:
  - Indicates the system's mode (automatic or manual) through solid or flashing states.

### **Control Modes**
1. **Automatic Mode**:
   - Uses a PID feedback loop to maintain the target RPM.
   - Servo position is dynamically adjusted based on the PID output.
2. **Manual Mode**:
   - Allows direct control of the servo position via a potentiometer.

### **PID Control**
- The PID algorithm ensures the system maintains the desired RPM by minimizing the error between the setpoint and the current RPM.
- Constants (`Kp`, `Ki`, `Kd`) are user-configurable to fine-tune the control system’s responsiveness.

### **Commands via Serial and Bluetooth Communication**
The controller can accept the following commands via both Serial Monitor and Bluetooth Classic connection:
- **`setrpm <value>`**: Sets the target RPM.
- **`setpid <kp> <ki> <kd>`**: Configures PID constants.
- **`arm` / `disarm`**: Toggles between automatic and manual modes.
- **`calibrate set_min <value>`**: Sets the minimum servo position (0-180 degrees).
- **`calibrate set_max <value>`**: Sets the maximum servo position (0-180 degrees).
- **`calibrate set_neutral <value>`**: Sets the neutral servo position (0-180 degrees).
- **`calibrate direction <0|1>`**: Sets servo travel direction (0=normal, 1=reversed).
- **`status`**: Displays the current system status including calibration settings.
- **`help`**: Lists available commands and their descriptions.

### **Bluetooth Classic Integration (ESP32 Version)**
- **Device Name**: `EMC_Type_1_Controller`
- **Functionality**: Full command support and real-time status feedback
- **Compatibility**: Works alongside existing Serial communication
- **Range**: Standard Bluetooth Classic range (~10 meters typical)

### **Interrupts**
- The RPM sensor uses an interrupt service routine (ISR) to count pulses and calculate RPM in real-time.

### **Feedback Loop**
- The system periodically:
  - Reads sensors.
  - Updates the system state based on input (e.g., arm switch or serial commands).
  - Runs PID or manual control logic based on the mode.
  - Outputs updated signals to the servo and LED.

### **Real-time Feedback**
- The controller provides real-time feedback via both the Serial Monitor and Bluetooth connection, including RPM readings, PID outputs, and system states.
- **ESP32 Version**: Simultaneous feedback over Serial and Bluetooth Classic for remote monitoring and control.

### **Safety and Stability**
- Includes safeguards such as:
  - Constraining servo positions within calibrated valid ranges.
  - Checking the validity of user inputs.
  - Disabling interrupts during critical operations to prevent race conditions.
  - Automatic validation and adjustment of calibration parameters.

### **Servo Calibration Feature**
- **Customizable Servo Range**: Set minimum and maximum servo positions to match your specific servo and mechanical setup.
- **Neutral Position**: Configure the default servo position used at startup and when no specific input is provided.
- **Direction Control**: Reverse servo travel direction to match your mechanical requirements.
- **Real-time Feedback**: Servo moves to the specified position during calibration for immediate visual confirmation.
- **Non-volatile Storage**: All calibration parameters are automatically saved to EEPROM (Arduino Uno) or Preferences (ESP32).
- **Validation**: Calibration parameters are validated to ensure they remain within valid ranges and logical constraints.

---

## Applications
This code is specifically crafted for:
- Hydraulic clutch systems in automotive or industrial applications.
- Projects requiring precise control of mechanical systems using sensors and actuators.
- Learning and experimenting with PID control systems in embedded devices.

---

Let me know if you need further analysis or modifications to the code!
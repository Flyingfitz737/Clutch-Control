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
- **Potentiometers**: 
  - One for additional input (`potentiometerPin`).
  - Another for manual control (`manualPotPin`).

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
- **`calibrate set_min <value>`**: Sets the minimum servo position (0-180 degrees).
- **`calibrate set_max <value>`**: Sets the maximum servo position (0-180 degrees).
- **`calibrate set_neutral <value>`**: Sets the neutral/default servo position.
- **`calibrate direction <normal|reversed>`**: Sets the servo travel direction.
- **`arm` / `disarm`**: Toggles between automatic and manual modes.
- **`status`**: Displays the current system status including calibration settings.
- **`help`**: Lists available commands and their descriptions.

### **Servo Calibration System (ESP32 Version)**
The ESP32 version includes an advanced servo calibration system that allows for precise servo setup and configuration:
- **Minimum/Maximum Endpoints**: Configure the operational range of the servo for both automatic and manual modes.
- **Neutral Position**: Set a default position that the servo returns to when switching modes.
- **Travel Direction**: Configure normal or reversed servo operation to match mechanical requirements.
- **Real-time Feedback**: Servo moves to the specified position immediately during calibration for visual confirmation.
- **Persistent Storage**: All calibration parameters are automatically saved to EEPROM and loaded on system startup.
- **Safety Constraints**: All servo operations respect the calibrated limits to prevent mechanical damage.

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
  - Constraining servo positions within calibrated ranges (ESP32 version).
  - Checking the validity of user inputs.
  - Disabling interrupts during critical operations to prevent race conditions.
  - Automatic validation of calibration parameters to prevent invalid configurations.
  - EEPROM data integrity checks to ensure reliable calibration storage (ESP32 version).

---

## Servo Calibration Guide (ESP32 Version Only)

The ESP32 version includes a comprehensive servo calibration system. Follow these steps to set up your servo for optimal performance:

### **Initial Setup**
1. Connect to the controller via Serial Monitor or Bluetooth
2. Use the `status` command to view current calibration settings
3. Default settings: Min=0°, Max=180°, Neutral=90°, Direction=Normal

### **Setting Servo Limits**
1. **Set Minimum Position**: `calibrate set_min <value>`
   - Example: `calibrate set_min 10` (sets minimum to 10 degrees)
   - The servo will move to this position for visual verification
   - Ensure this position doesn't cause mechanical binding

2. **Set Maximum Position**: `calibrate set_max <value>`
   - Example: `calibrate set_max 170` (sets maximum to 170 degrees)
   - The servo will move to this position for visual verification
   - Ensure this position doesn't cause mechanical binding

### **Setting Neutral Position**
1. **Set Neutral/Default Position**: `calibrate set_neutral <value>`
   - Example: `calibrate set_neutral 85` (sets neutral to 85 degrees)
   - Must be between your min and max positions
   - This position is used when switching between modes

### **Setting Travel Direction**
1. **Normal Direction**: `calibrate direction normal`
   - Servo moves in standard direction (0° to 180°)
   
2. **Reversed Direction**: `calibrate direction reversed`
   - Servo movement is reversed for mechanical compatibility
   - Useful when servo needs to operate in opposite direction

### **Verification and Testing**
1. Use `status` command to verify all calibration settings
2. Test both automatic and manual modes to ensure proper operation
3. All settings are automatically saved to EEPROM
4. Settings persist through power cycles

### **Safety Notes**
- Always verify mechanical clearances before setting extreme positions
- Test servo movement gradually to avoid damage
- The system automatically constrains all movements within calibrated limits
- Invalid calibration values are rejected with error messages

---

## Applications
This code is specifically crafted for:
- Hydraulic clutch systems in automotive or industrial applications.
- Projects requiring precise control of mechanical systems using sensors and actuators.
- Learning and experimenting with PID control systems in embedded devices.

---

Let me know if you need further analysis or modifications to the code!
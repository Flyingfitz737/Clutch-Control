# Clutch-Control
Hydraulic clutch controller for motorcycle

## Available Controllers

### EMC Type 1 Controller 
**File:** `EMC Type 1` (Arduino Uno) | `EMC Type 1 ESP 32` (ESP32 with Bluetooth)  
**Documentation:** [EMC_Type_1_README.md](EMC_Type_1_README.md)

Arduino Uno-based controller featuring:
- User-configurable parameters via Serial Monitor
- Real-time RPM sensor input and PID control
- Servo motor control for clutch actuation
- LED arming light and comprehensive status feedback
- Serial command interface for remote operation

**ESP32 Version Adds:**
- **Bluetooth Classic communication** (Device: `EMC_Type_1_Controller`)
- **Advanced servo calibration system** with EEPROM storage
- **Configurable servo endpoints, neutral position, and travel direction**
- **Real-time calibration feedback** with visual servo movement confirmation
- Wireless remote control and monitoring
- Simultaneous Serial and Bluetooth feedback

### Other Controllers
- **Clutch Control PID Basic** - Basic PID implementation
- **Clutch Control Arm Light PID Basic** - PID with arming light
- **Clutch Control PID Auto Tune** - Auto-tuning PID variant
- **PID Autotune** & **PID Auto Tune 20%** - Additional auto-tune implementations

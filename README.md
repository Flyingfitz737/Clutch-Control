# Clutch-Control
Hydraulic clutch controller for motorcycle

## 📁 Where to Find the Complete Code

All Arduino sketches are organized in properly named folders with `.ino` file extensions. Each folder contains the complete code ready to open in Arduino IDE:

### Primary Controllers

#### **EMC Type 1 ESP32** (Recommended)
📂 **Folder:** [`EMC_Type_1_ESP32/`](EMC_Type_1_ESP32/)  
📄 **Complete Code:** [`EMC_Type_1_ESP32.ino`](EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino)  
📖 **Documentation:** [EMC_Type_1_README.md](EMC_Type_1_README.md)

**Features:**
- User-configurable parameters via Serial Monitor
- Real-time RPM sensor input and PID control
- Servo motor control for clutch actuation
- LED arming light and comprehensive status feedback
- **Bluetooth Classic communication** (Device: `EMC_Type_1_Controller`)
- Wireless remote control and monitoring
- Simultaneous Serial and Bluetooth feedback
- Non-volatile storage with ESP32 Preferences
- Servo preposition feature for customized armed state position

#### **EMC Type 1 Arduino Uno**
📂 **Folder:** [`EMC_Type_1_Arduino/`](EMC_Type_1_Arduino/)  
📄 **Complete Code:** [`EMC_Type_1_Arduino.ino`](EMC_Type_1_Arduino/EMC_Type_1_Arduino.ino)  
📖 **Documentation:** [EMC_Type_1_README.md](EMC_Type_1_README.md)

**Features:**
- Same core features as ESP32 version
- Uses EEPROM for non-volatile storage
- Serial communication only (no Bluetooth)

### Alternative Controllers

- 📂 **[Clutch_Control_PID_Basic](Clutch_Control_PID_Basic/)** - Basic PID implementation
- 📂 **[Clutch_Control_Arm_Light_PID_Basic](Clutch_Control_Arm_Light_PID_Basic/)** - PID with arming light
- 📂 **[Clutch_Control_PID_Auto_Tune](Clutch_Control_PID_Auto_Tune/)** - Auto-tuning PID variant
- 📂 **[PID_Autotune](PID_Autotune/)** - PID autotune implementation
- 📂 **[PID_Auto_Tune_20_Percent](PID_Auto_Tune_20_Percent/)** - Auto-tune with 20% parameters

## 🚀 Quick Start

1. **Choose your controller** - We recommend EMC Type 1 ESP32 for full features
2. **Open the folder** in Arduino IDE or navigate to it
3. **Open the `.ino` file** (e.g., `EMC_Type_1_ESP32.ino`)
4. **Install required libraries** (listed in each sketch)
5. **Select your board** in Arduino IDE
6. **Upload** to your device

## 📚 Documentation

- **[EMC_Type_1_README.md](EMC_Type_1_README.md)** - Complete functionality documentation for EMC Type 1 controllers
- **[System_Workflow_Overview.md](System_Workflow_Overview.md)** - Step-by-step setup and usage guide

## 💡 Need Help?

Each controller folder contains a README with specific instructions. Start with the main documentation files above for comprehensive guides.

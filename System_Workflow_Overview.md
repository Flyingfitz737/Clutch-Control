# **System Workflow Overview: Clutch-Control System**

This document serves as a step-by-step guide and checklist for setting up and using the Clutch-Control system.

---

## **Step-by-Step Setup Checklist**

### **1. Calibrate the Servo**:
   1. Set the servo's minimum position:
      ````
      calibrate set_min <value>
      ````
      Example: `calibrate set_min 20` sets the minimum servo angle to 20°.
   2. Set the servo's maximum position:
      ````
      calibrate set_max <value>
      ````
      Example: `calibrate set_max 170` sets the maximum servo angle to 170°.
   3. Optionally, set the neutral position:
      ````
      calibrate set_neutral <value>
      ````
      Example: `calibrate set_neutral 90` sets the neutral position to 90°.
   4. Test and modify the servo travel direction (normal = `0`, reversed = `1`):
      ````
      calibrate direction <0|1>
      ````
      Example: `calibrate direction 1` reverses servo direction.

### **2. Calibrate the Potentiometer**:
   1. Turn the potentiometer to its **minimum physical position** and run:
      ````
      calibrate pot_min
      ````
   2. Turn the potentiometer to its **maximum physical position** and run:
      ````
      calibrate pot_max
      ````

### **3. Configure PID Settings**:
   1. Set the target RPM for PID to maintain:
      ````
      setrpm <value>
      ````
      Example: `setrpm 1500` sets the target RPM to 1500.
   2. Adjust PID constants (Kp, Ki, Kd):
      ````
      setpid <Kp> <Ki> <Kd>
      ````
      Example: `setpid 2.5 6.0 1.2` sets PID constants to Kp=2.5, Ki=6.0, Kd=1.2.

### **4. Configure Safety Override (Optional)**:
   1. Enable the safety override system:
      ````
      safety enable
      ````
   2. Disable the safety override system:
      ````
      safety disable
      ````
   3. Set the threshold for safety override to trigger (valid range: 0-4095):
      ````
      safety set_threshold <value>
      ````
      Example: `safety set_threshold 3000` sets the safety threshold to 3000.

   - **Note**: The safety override system prevents the system from being armed if the potentiometer value is above `overrideThreshold`. Once triggered, the system will disarm and revert to manual mode when the value drops below the threshold. Rearming requires toggling the arm switch OFF and then ON.

### **5. Test and Verify System Behavior**:
   1. **Arming/Disarming**:
      - Use the `arm` command or toggle the arm switch ON to arm the system (automatic mode). The arm light will turn solid.
      - Use the `disarm` command or toggle the arm switch OFF to disarm (manual mode). The arm light will flash normally.
   2. **Safety Override Testing** (Ensure safety mode is enabled):
      - Enable safety override: `safety enable`.
      - Set an appropriate threshold for your system (e.g., `safety set_threshold 3000`).
      - Arm the system (automatic mode) and verify the servo operates in PID mode.
      - Move the potentiometer above the threshold value to trigger safety override. Verify that:
         - The system disarms.
         - The servo switches to manual potentiometer control.
         - The arm light flashes quickly (override mode).
      - Return the potentiometer below the threshold. Confirm that the system remains disarmed (manual mode).
   3. **Rearming After Override**:
      - Toggle the arm switch OFF and ON while keeping the potentiometer below the threshold.
      - Verify the system arms successfully and returns to automatic mode.

---

## **LED Behavior Reference**

| **Mode**                  | **Arm Light Behavior**                                       |
|---------------------------|-------------------------------------------------------------|
| **Disarmed (Manual Mode)** | Flashes at normal intervals (500ms).                        |
| **Automatic (Armed)**      | Solid light.                                                |
| **Safety Override Active** | Flashes faster (250ms) to signal an override is active.     |

---

## **Helpful Commands Reference**

### **General Commands**:
| Command                    | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| `status`                   | Display the current system status (potentiometer values, PID settings, etc). |
| `help`                     | Display this help menu.                                                    |

### **Calibration Commands**:
| Command                    | Description                                                                 |
|----------------------------|-----------------------------------------------------------------------------|
| `calibrate set_min <value>`| Set minimum servo position (0-180).                                         |
| `calibrate set_max <value>`| Set maximum servo position (0-180).                                         |
| `calibrate set_neutral <value>`| Set neutral servo position (0-180).                                    |
| `calibrate direction <0|1>`| Set servo direction (normal or reversed).                                   |
| `calibrate pot_min`        | Set minimum potentiometer value (with current pot position).                |
| `calibrate pot_max`        | Set maximum potentiometer value (with current pot position).                |

### **Safety Override Commands**:
| Command                      | Description                                                               |
|------------------------------|---------------------------------------------------------------------------|
| `safety enable`              | Enable the safety override system.                                        |
| `safety disable`             | Disable the safety override system.                                       |
| `safety set_threshold <value>`| Set potentiometer threshold for safety override (0-4095).               |

### **Operational Commands**:
| Command     | Description                                                                                 |
|-------------|---------------------------------------------------------------------------------------------|
| `arm`       | Arm the system (automatic mode - PID controls the servo).                                   |
| `disarm`    | Disarm the system (manual mode - servo controlled by potentiometer).                        |

---

**Checklist:**
- [ ] Run startup calibration for the servo and potentiometer.
- [ ] Set the PID constants and target RPM as required.
- [ ] Test arming and disarming the system and verify LED behavior.
- [ ] If safety override is enabled, test behavior when the potentiometer exceeds and falls below the threshold.
- [ ] Verify the system persists settings across power cycles.

Print this checklist and work through the steps sequentially to ensure a complete and correct setup of the `Clutch-Control` system. If issues arise during setup, use the `status` command for debugging information.
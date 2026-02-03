# Development Notes and Concepts for EMC Type 1 Controller

This document outlines the developmental concepts and design ideas for the EMC Type 1 Controller for an ESP32-based hydraulic clutch control system.

---

## Features Overview

1. **PID-Based Control**:
    - Implements PID control to adjust a servo-driven hydraulic clutch based on RPM sensor data.
    - User-configurable PID parameters (`Kp`, `Ki`, `Kd`).
    - Servo positions can range between 0-180° with configurable calibration (min, max, neutral).

2. **Inputs and Outputs**:
    - **Inputs**:
        - RPM sensor connected to GPIO19 for pulse-based RPM data.
        - Manual and additional potentiometers (GPIO34, GPIO35) for manual control inputs.
        - Arm switch (GPIO21) for toggling system modes.
    - **Outputs**:
        - Servo motor (PWM signal on GPIO18) for clutch control.
        - LED (GPIO2) for system mode feedback.

3. **Bluetooth Integration**:
    - Device name: `EMC_Type_1_Controller`.
    - Accepts Bluetooth commands for system control and calibration.
        - `setrpm <value>`: Set target RPM.
        - `setpid <kp> <ki> <kd>`: Set PID constants.
        - Arm/disarm the system: `arm`, `disarm`.
        - Calibration commands: `calibrate set_min`, `set_max`, `set_neutral`, `direction`.
        - `status`: Check real-time system status.
        - `help`: List of supported commands.

4. **System Modes**:
    - **Automatic Mode**: PID loop automatically adjusts servo position to meet the target RPM.
    - **Manual Mode**: The potentiometer directly controls the servo position when the system is disarmed.

5. **Calibration Mechanism**:
    - Calibration values (min, max, neutral positions, direction) are stored using non-volatile `Preferences` on the ESP32.
    - Servo positions are constrained within a calibrated operational range (0-180).

---

## manual override design

### Manual Override Logic with Potentiometer in ARM Mode

The design includes a mechanism to detect significant manual potentiometer movement and disable the PID-based automatic mode.

### Implementation Steps

1. **Create a Threshold**: Add a threshold value (`manualThreshold`) to detect significant changes in the potentiometer.

    ```cpp
    const int manualThreshold = 100;  // Threshold for detecting manual override
    ```

2. **Detect Manual Override Input**: Check if the potentiometer input deviates from the servo position.

    ```cpp
    bool checkForManualOverride() {
        manualPotValue = analogRead(manualPotPin);  // Read manual potentiometer input
        int manualMappedPosition = map(manualPotValue, 0, 4095, min_position, max_position);

        if (abs(servoPosition - manualMappedPosition) > manualThreshold) {
            return true;  // Trigger manual override
        }
        return false;  // No significant deviation
    }
    ```

3. **Interrupt the PID Loop**:
    - Modify the `runPIDControl()` function to check for manual override conditions and halt the PID loop if the override is triggered.

    ```cpp
    void runPIDControl() {
        if (!manualOverride && myPID.Compute()) {
            servoPosition = (int)pidOutput;
            servoPosition = applyCalibration(servoPosition);
            clutchServo.write(servoPosition);
        }

        if (checkForManualOverride()) {
            manualOverride = true;
            autoDisabled = true;  // Disable automatic mode until arm switch is recycled
            dualPrintln("Manual override triggered! Disabling automatic mode.");
        }
    }
    ```

4. **Require Arm Switch Reset**:
    - Add functionality in `updateSystemState()` to check for arm switch state changes and re-enable automatic mode after recycling the switch.

    ```cpp
    void updateSystemState() {
        bool armSwitchState = !digitalRead(armSwitchPin);  // Active LOW switch
        static bool previousArmSwitchState = false;

        if (armSwitchState && !previousArmSwitchState) {
            systemArmed = true;
            autoDisabled = false;  // Reset automatic mode disabled flag
            dualPrintln("System ARMED via switch - Automatic PID Control Mode");
        }

        if (!armSwitchState && previousArmSwitchState) {
            systemArmed = false;
            dualPrintln("System DISARMED via switch - Manual Control Mode");
        }

        previousArmSwitchState = armSwitchState;
    }
    ```

5. **Update Arm Light Behavior**:
    Modify the `updateOutputs()` function to include a visual signal (like rapid flashing or double flashes) indicating manual override activation and automatic mode disabling.

    ```cpp
    void updateOutputs() {
        if (manualOverride) {
            unsigned long currentTime = millis();
            if (currentTime - lastLEDFlash >= ledFlashInterval / 2) { // Rapid flashing
                ledState = !ledState;
                digitalWrite(armLightPin, ledState);
                lastLEDFlash = currentTime;
            }
        } else if (autoDisabled) {
            // Double-flash pattern
            // Implement logic for distinct indication when autoDisabled == true
        } else if (systemArmed) {
            digitalWrite(armLightPin, HIGH);  // Solid ON
        } else {
            unsigned long currentTime = millis();
            if (currentTime - lastLEDFlash >= ledFlashInterval) {
                ledState = !ledState;
                digitalWrite(armLightPin, ledState);
                lastLEDFlash = currentTime;
            }
        }
    }
    ```

### Final Behavior

- If the potentiometer input exceeds the threshold (`manualThreshold`) in ARM mode, the system will disable automatic mode.
- **The ARM switch must be recycled** (toggled OFF and then ON) to re-enable automatic mode.
- The arm light will:
    - **Solid ON** for active automatic mode.
    - **Flashing** for normal manual mode.
    - **Rapid flashing** for manual override triggered.
    - Optionally, a **double-flash pattern** for auto-disabled (override triggered and awaiting manual reset).

---

### Brainstorm: Feed-Forward Control (Optional Future Addition)

Feed-forward control can complement PID to improve response time and stability by predicting servo movements rather than relying solely on feedback. Below are potential steps to implement feed-forward control in the EMC Type 1 Controller:

1. Define a new **feed-forward function** that maps the target RPM (`setpointRPM`) to an estimated servo position:
    ```cpp
    double calculateFeedForward(double targetRPM) {
        return map(targetRPM, 0, 10000, min_position, max_position);  // Example linear mapping
    }
    ```

2. Modify `runPIDControl()` to include the feed-forward term:
    ```cpp
    void runPIDControl() {
        if (myPID.Compute()) {
            double feedForward = calculateFeedForward(setpointRPM);  // Feed-forward contribution
            servoPosition = (int)(pidOutput + feedForward);  // Combine feedback and feed-forward
            servoPosition = applyCalibration(servoPosition);
            clutchServo.write(servoPosition);
        }
    }
    ```

3. Tune the feed-forward model by deriving it from theoretical or experimental data to achieve optimal system response.

---

This document serves as both a reference for development and a guide for implementing safety features, advanced control methods, and calibration enhancements.

## EMC Type 1 Controller — ESP32 Hydraulic Clutch Control

This project is an ESP32-based controller designed to regulate a hydraulic clutch/valve using **RPM feedback** and a **PID control loop**. It supports both **automatic (closed-loop) control** and **manual potentiometer control**, includes a **hardware arm switch**, a **safety override**, and provides **USB Serial + Bluetooth Classic** for configuration and live telemetry. All key settings can be saved to ESP32 NVS so the controller restores configuration on reboot.

### Key Features

* **Dual modes**

  * **AUTO (PID):** maintains target RPM using a PID loop that drives a servo-actuated hydraulic valve.
  * **MANUAL:** maps a manual potentiometer to servo position for direct operator control.
* **Period-based RPM measurement**

  * Interrupt-driven tach input; computes RPM from pulse timing for high resolution across a wide RPM range.
  * Optional **noise rejection** and **EMA smoothing** for stable readings.
* **Safety + operator controls**

  * **Arm switch** for hardware enable/disable.
  * **Safety override** using the manual pot threshold (fast LED flash when triggered; disarm on release below threshold).
  * **Status LED patterns** for state indication (armed/disarmed/override).
* **Configuration interfaces**

  * Commands over **USB Serial** and **Bluetooth Classic** (mirrored output to both).
* **Non-volatile persistence**

  * Servo calibration, PID gains, target RPM, sample rate, smoothing alpha, PPR, thresholds, etc. saved in NVS.

---

## Hardware Overview

Typical connections (adjust as needed):

* RPM/Tach input (interrupt-capable GPIO)
* Two analog pots:

  * “Control pot” (optional UI / monitoring)
  * “Manual pot” (manual mode + safety override threshold source)
* Servo output (hydraulic valve/clutch actuator)
* Arm switch input (pulled-up, switch to GND)
* Status LED output

---

## How the Code Works (High-Level)

The sketch is organized around a few core responsibilities:

1. **RPM capture (interrupt-driven)**

   * An ISR triggers on the tach signal edge and records pulse timing.
   * The main loop periodically computes RPM from the **measured period** (time between accepted pulses).
   * Optional smoothing (EMA) provides a stable RPM value for control.

2. **State management (ARMED vs DISARMED)**

   * When **disarmed**, the servo follows the manual potentiometer (manual control).
   * When **armed**, the PID loop is active and drives the servo to maintain the target RPM.
   * A pre-arm “start position” places the servo at a known engagement point before PID takes over.

3. **PID control**

   * Uses `PID_v1` with user-tunable gains (Kp/Ki/Kd).
   * PID sample time is configurable (e.g., 10–200 ms).
   * A separate **aggressiveness multiplier** can scale the PID output without changing gains.

4. **Safety override**

   * If enabled, moving the manual pot above a configured threshold triggers an override state (fast LED flash).
   * Once the pot returns below threshold, the system disarms back into manual mode.

5. **Commands + persistence**

   * Commands are accepted via Serial and Bluetooth (same command parser).
   * Settings can be changed live; a `save` command writes them to ESP32 Preferences (NVS) so they load on reboot.

---

## Common Commands (Examples)

* Set target RPM: `setrpm 1500`
* Set PID gains: `setpid 2.5 4.0 0.8`
* Set PID sample time: `setsample 50`
* Set RPM smoothing: `setalpha 0.20`
* Set tach PPR: `ppr 2`
* Arm / disarm: `arm` / `disarm`
* Save settings: `save`
* View status: `status`

---

## Notes / Intended Use

This controller is designed for experimentation and controlled environments. If used on real equipment, implement appropriate mechanical and electrical safeguards (independent kill/disarm, proper power supply isolation for the servo, shielding on tach wiring, etc.).

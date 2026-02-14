# EMC Type 1 Controller (Clutch Control Firmware)

Firmware for an ESP32-based EMC Type 1 clutch controller featuring a high‑priority deterministic control loop, BLE telemetry/commands, safety override logic, and binary logging to LittleFS.

---

## Features

- **Deterministic control loop (333 Hz)** with watchdog supervision
- **PID clutch control** with adjustable gains and aggressiveness
- **Manual mode** using potentiometer input
- **Safety override** with hysteresis and cooldown
- **BLE UART (NUS)** command/telemetry interface
- **Binary logging** to LittleFS with session headers/footers
- **CSV streaming** of log samples over BLE when disarmed
- **Persistent settings** via NVS (Preferences)

---

## Hardware

- **Target MCU:** ESP32  
- **Servo control:** standard PWM servo (clutch)
- **RPM sensor:** pulse input (configurable PPR)
- **Potentiometers:** setpoint/manual control and override sense
- **Status LED + Arm Switch**

> Pinout intentionally omitted. See source code for pin constants.

---

## Build & Flash (Arduino IDE)

1. Install **ESP32 board support** in Arduino IDE.
2. Install required libraries:
   - **ESP32Servo**
   - **NimBLE-Arduino**
3. Select your ESP32 board and port.
4. Open the `.ino` file and **Upload**.

---

## Core Behavior

### Modes
- **Manual (disarmed):** servo follows manual potentiometer
- **Auto (armed):** PID loop drives servo to maintain target RPM

### Control Loop
- Fixed **3 ms** loop period (~333 Hz)
- Runs on dedicated FreeRTOS task (core 1)
- Watchdog monitoring enabled

---

## BLE Interface

- **Device name:** `EMC_UNO`
- **Service:** Nordic UART Service (NUS)

### Common Commands

```
getall
get <key>
setrpm <rpm>
setpid <kp> <ki> <kd>
piddir direct|reverse
aggressiveness <0.1-3.0>
setstart <deg>
prehold on|off
setalpha <0.10-0.50>
ppr <1|2|4>
telemetry auto|on|off
telemetry rate <ms>
calibrate set_min|set_max|set_neutral <val>
calibrate direction <0|1>
calibrate pot_min|pot_max <val>
safety enable|disable
safety set_threshold_pct <0-100>
safety sense normal|reversed
save
arm
disarm
status
help
```

### Telemetry Output

Example telemetry line:
```
tele rpm=XXXX target=YYYY servo=ZZZ mode=AUTO pid_out=AAA prehold=1 dirty=0
```

---

## Logging

- Logs are stored in **LittleFS** (`/log_<id>_<timestamp>.bin`)
- Binary format with header/footer
- Download via BLE:

```
log list
log read <file>
log cancel
```

---

## Safety Override

When enabled, the manual potentiometer can **force disarm** if it exceeds a configurable threshold. Includes hysteresis and cooldown to prevent rapid toggling.

---

## Configuration Persistence

All settings are saved to NVS with the `save` command.

---

## License

This project is licensed under the **MIT License**.

---

## Disclaimer

This firmware controls mechanical systems. Use responsibly and validate safety mechanisms in your environment.

Perfect! Here's the updated README with your actual repository information:

````markdown name=README.md
# EMC Type 1 Controller for ESP32

A sophisticated PID-based hydraulic clutch controller built for ESP32 with Bluetooth connectivity, real-time RPM monitoring, and comprehensive safety features.

## Features

### Core Functionality
- **Hydraulic Clutch PID Control** - Precision closed-loop control with adjustable aggressiveness scaling
- **Dual Operation Modes**
  - **Automatic Mode**: PID-controlled engagement based on target RPM
  - **Manual Mode**: Direct potentiometer control with calibrated response
- **Real-time RPM Measurement** - Interrupt-driven, period-based tachometer with noise rejection
- **Bluetooth Classic Communication** - Full remote control and monitoring via `EMC_Type_1_Controller` device
- **Serial Console Interface** - Complete command set accessible via USB serial

### Safety Systems
- **Safety Override** - Automatic intervention when manual potentiometer exceeds threshold
- **Arming System** - Requires explicit arming before PID control activation
- **Visual Feedback** - LED indicators for system state (armed/disarmed/override)
- **Configurable Limits** - Software-enforced servo position boundaries

### Advanced Features
- **RPM Smoothing** - Exponential Moving Average (EMA) filtering with adjustable alpha (0.10–0.50)
- **Configurable Tachometer** - Support for 1, 2, or 4 pulses per revolution (PPR)
- **Adaptive PID Sample Time** - User-adjustable from 10–200 ms
- **PID Aggressiveness Scaling** - Fine-tune response characteristics (0.1–3.0×)
- **Pre-PID Arming Position** - Configurable initial servo position for smooth engagement
- **Persistent Settings** - All parameters saved to ESP32 NVS (Non-Volatile Storage)
- **Dirty Flag System** - Only saves to flash when user explicitly runs `save` command

## Hardware Requirements

### Components
- **ESP32 Development Board** (any variant with sufficient GPIO)
- **Servo Motor** - Standard RC servo (0–180°) for clutch actuation
- **Tachometer Sensor** - Hall effect, optical, or inductive proximity sensor
- **Potentiometers** (2×)
  - System feedback potentiometer (clutch position sensor)
  - Manual control potentiometer
- **Arming Switch** - Momentary or toggle switch
- **Status LED** - Visual system state indicator

### Pin Configuration

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| RPM Sensor | GPIO 19 | Interrupt-capable, pulled high |
| Feedback Potentiometer | GPIO 34 | ADC input |
| Manual Potentiometer | GPIO 35 | ADC input |
| Servo Control | GPIO 18 | PWM output |
| Arm LED | GPIO 2 | Built-in LED compatible |
| Arm Switch | GPIO 21 | Pulled high (active low) |

### Wiring Diagram
```
ESP32                     Peripherals
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
GPIO 19 ─────────────── RPM Sensor Signal
GPIO 34 ─────────────── Feedback Pot (wiper)
GPIO 35 ─────────────── Manual Pot (wiper)
GPIO 18 ─────────────── Servo Signal Wire
GPIO 2  ─────────────── LED Anode (+)
GPIO 21 ─────────────── Arm Switch

GND     ─────────────── All component grounds
3.3V    ─────────────── Potentiometer supplies
5V      ─────────────── Servo power (via external supply recommended)
```

**Important**: Use an external 5V power supply for the servo to avoid overloading the ESP32's regulator.

## Installation

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) 1.8.13+ or [PlatformIO](https://platformio.org/)
- ESP32 board support package installed

### Required Libraries
```cpp
#include <Arduino.h>       // Core Arduino framework
#include <PID_v1.h>        // PID controller library
#include <ESP32Servo.h>    // Servo control for ESP32
#include "BluetoothSerial.h"  // Built-in BT Classic
#include <Preferences.h>   // NVS storage
#include <math.h>          // Standard math functions
```

Install via Arduino Library Manager:
1. **PID Library** by Brett Beauregard
2. **ESP32Servo** by Kevin Harrington

### Compilation & Upload
1. Clone this repository:
   ```bash
   git clone https://github.com/Flyingfitz737/Clutch-Control.git
   ```

2. Open `emc_type1_controller.ino` in Arduino IDE

3. Select your ESP32 board:
   - **Tools → Board → ESP32 Arduino → [Your Board]**

4. Configure upload settings:
   - **Upload Speed**: 115200
   - **Flash Frequency**: 80 MHz
   - **Partition Scheme**: Default (or Minimal SPIFFS if storage is tight)

5. Upload to your ESP32

## Configuration

### Initial Setup

1. **Connect via Serial** (115200 baud) or **Bluetooth** (`EMC_Type_1_Controller`)

2. **Calibrate Servo Range**:
   ```
   calibrate set_min 0      # Minimum servo position (degrees)
   calibrate set_max 180    # Maximum servo position (degrees)
   calibrate set_neutral 90 # Neutral/rest position
   ```

3. **Calibrate Manual Potentiometer**:
   ```
   calibrate pot_min 0      # Potentiometer ADC minimum (typically 0)
   calibrate pot_max 4095   # Potentiometer ADC maximum (12-bit ADC)
   ```

4. **Configure Tachometer**:
   ```
   ppr 1                    # Set pulses per revolution (1, 2, or 4)
   setalpha 0.30            # RPM filter smoothing (0.10–0.50)
   ```

5. **Set PID Parameters**:
   ```
   setrpm 1000              # Target RPM
   setpid 2.0 5.0 1.0       # Kp Ki Kd gains
   aggressiveness 1.0       # PID scaling factor (0.1–3.0)
   setsample 100            # PID sample time (10–200 ms)
   setstart 50              # Pre-PID arming position (degrees)
   ```

6. **Configure Safety Override** (optional):
   ```
   safety enable            # Enable safety override system
   safety set_threshold 3500  # Manual pot override threshold (ADC units)
   ```

7. **Save Configuration**:
   ```
   save                     # Persist all settings to NVS
   ```

### Tuning Guide

#### PID Tuning
Start with conservative values and adjust incrementally:

1. **Proportional (Kp)**: Controls immediate response to error
   - Too low: Sluggish response, doesn't reach setpoint
   - Too high: Oscillation, overshoot
   - Start: `2.0`

2. **Integral (Ki)**: Eliminates steady-state error
   - Too low: Never quite reaches setpoint
   - Too high: Overshoot, instability
   - Start: `5.0`

3. **Derivative (Kd)**: Dampens oscillation, predicts future error
   - Too low: Overshoot
   - Too high: Slow response, noise sensitivity
   - Start: `1.0`

**Tuning Process**:
```
1. Set Ki=0, Kd=0, start with low Kp (1.0)
2. Increase Kp until system oscillates
3. Reduce Kp by 25%
4. Add Ki to eliminate steady-state error (start 0.5)
5. Add Kd to reduce overshoot (start 0.1)
6. Fine-tune aggressiveness (0.5–2.0 range typical)
```

#### RPM Filter Tuning
- **Lower alpha (0.10)**: Smoother, slower response - use for noisy sensors
- **Higher alpha (0.50)**: Faster response, more noise - use for clean signals
- **Recommended**: `0.30` for general use

## Usage

### Command Reference

#### System Control
| Command | Description | Example |
|---------|-------------|---------|
| `arm` | Engage automatic PID control | `arm` |
| `disarm` | Switch to manual mode | `disarm` |
| `status` | Display detailed system status | `status` |
| `help` | Show command list | `help` |
| `save` | Write all settings to NVS | `save` |
| `dirty` | Check if unsaved changes exist | `dirty` |

#### PID Configuration
| Command | Parameters | Description |
|---------|------------|-------------|
| `setrpm` | `<rpm>` | Set target RPM (1–100000) |
| `setpid` | `<kp> <ki> <kd>` | Set PID gains |
| `aggressiveness` | `<0.1–3.0>` | Scale PID output |
| `setstart` | `<degrees>` | Pre-PID arming position |
| `setsample` | `<10–200>` | PID sample time (ms) |

#### RPM Configuration
| Command | Parameters | Description |
|---------|------------|-------------|
| `ppr` | `<1\|2\|4>` | Pulses per revolution (auto-scales setpoint) |
| `setalpha` | `<0.10–0.50>` | RPM filter smoothing factor |

#### Calibration Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| `calibrate set_min` | `<0–179>` | Minimum servo position |
| `calibrate set_max` | `<1–180>` | Maximum servo position |
| `calibrate set_neutral` | `<degrees>` | Neutral servo position |
| `calibrate direction` | `<0\|1>` | 0=normal, 1=reversed |
| `calibrate pot_min` | `<0–4095>` | Manual pot ADC minimum |
| `calibrate pot_max` | `<0–4095>` | Manual pot ADC maximum |

#### Safety Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| `safety enable` | - | Enable override system |
| `safety disable` | - | Disable override system |
| `safety set_threshold` | `<ADC value>` | Override trigger level |

### Operation Modes

#### Manual Mode (Default)
- System controlled by manual potentiometer
- LED flashes slowly (500 ms intervals)
- Servo position directly mapped from pot input
- Safe for testing and initial setup

#### Automatic Mode (Armed)
- Activated by `arm` command or arm switch
- LED solid on
- PID controller maintains target RPM
- Servo moves to `pidStartPosition` on arming
- Manual pot acts as safety override (if enabled)

#### Safety Override Mode
- Triggered when manual pot exceeds threshold (if enabled)
- LED flashes rapidly (250 ms intervals)
- PID remains active but user can intervene
- System disarms when pot returns below threshold

### Typical Workflow

```bash
# Connect via Bluetooth or Serial

# 1. Check current configuration
status

# 2. Make adjustments
setrpm 1500
setpid 2.5 6.0 1.2
aggressiveness 1.2

# 3. Test in manual mode first
# (manipulate manual pot to verify servo response)

# 4. Arm the system
arm

# 5. Monitor performance
# (status automatically prints every 500ms)

# 6. Save if settings work well
save

# 7. Disarm when done
disarm
```

## Status Output

### Continuous Status Line (500 ms updates)
```
RPM: 1523 | Target: 1500 | Servo: 87° | Mode: AUTO | PID Out: 85.4 | Agg: 1.20 | PPR: 1 | Ts: 100ms | Alpha: 0.30 | SAVED
```

### Detailed Status (`status` command)
```
=== STATUS ===
RPM: 1523
Target RPM: 1500
Servo: 87°
Mode: AUTO
PID Out: 85.4
PID Gains: Kp=2.5000 Ki=6.0000 Kd=1.2000
Aggressiveness: 1.20
Pre-PID Start Position: 50
PPR: 1
PID Sample Time: 100 ms
RPM Filter Alpha: 0.30
Accepted Pulses Count (since boot): 15487
settingsDirty: false
================
```

## Technical Details

### RPM Measurement
- **Method**: Period-based (time between pulses)
- **Resolution**: 1 microsecond
- **Noise Rejection**: Minimum pulse period 200 µs
- **Timeout**: 300 ms (RPM = 0 if no pulse)
- **Interrupt**: FALLING edge on GPIO 19
- **Formula**: `RPM = 60,000,000 / (period_µs × PPR)`

### PID Implementation
- **Library**: [Arduino PID Library](https://github.com/br3ttb/Arduino-PID-Library)
- **Mode**: DIRECT (increase output = increase process variable)
- **Output Limits**: Constrained to calibrated servo range
- **Aggressiveness**: Multiplicative scaling applied post-computation

### Data Persistence
All settings stored in ESP32 NVS (`emc_calibration` namespace):
- Servo calibration (min, max, neutral, direction)
- Potentiometer calibration
- Safety settings
- PID parameters (Kp, Ki, Kd, aggressiveness)
- RPM configuration (PPR, alpha, sample time)
- Setpoint RPM
- Pre-PID start position

**Write Cycle Management**: Explicit `save` command required to prevent excessive NVS wear.

### Bluetooth
- **Protocol**: Bluetooth Classic (SPP - Serial Port Profile)
- **Device Name**: `EMC_Type_1_Controller`
- **Baud Rate**: N/A (Bluetooth abstraction)
- **Compatible**: Android, Windows, Linux, macOS (with SPP support)

## Troubleshooting

### RPM Reads Zero
- ✓ Check sensor wiring (signal, ground, power)
- ✓ Verify GPIO 19 connection
- ✓ Ensure sensor outputs 3.3V or 5V logic levels
- ✓ Check `ppr` setting matches your sensor (1, 2, or 4)
- ✓ Monitor `Accepted Pulses Count` in `status` - should increment

### Servo Doesn't Move
- ✓ Check servo power supply (external 5V recommended)
- ✓ Verify GPIO 18 connection to servo signal wire
- ✓ Test with `calibrate set_neutral 90` in manual mode
- ✓ Check calibration limits (`set_min` / `set_max`)

### System Won't Arm
- ✓ Manual pot must be below `safety set_threshold` (if override enabled)
- ✓ Check arm switch wiring (GPIO 21, active low)
- ✓ Try `arm` command directly via serial/Bluetooth

### PID Oscillates / Unstable
- ✓ Reduce `Kp` by 50% and test
- ✓ Set `Ki` and `Kd` to 0, tune Kp first
- ✓ Reduce `aggressiveness` to 0.5
- ✓ Increase `setsample` time to 150-200 ms
- ✓ Lower `setalpha` to 0.20 for more smoothing

### Bluetooth Won't Connect
- ✓ Verify device appears as `EMC_Type_1_Controller` in BT scan
- ✓ Unpair and re-pair if previously connected
- ✓ Restart ESP32 (some phones cache BT connections)
- ✓ Disable BT Low Energy filters (this uses Classic BT)

### Settings Don't Persist
- ✓ **Run `save` command** - changes are NOT auto-saved!
- ✓ Check `dirty` command output
- ✓ Verify NVS partition isn't corrupted (re-flash if needed)

## Safety Considerations

⚠️ **WARNING**: This controller operates high-torque mechanical systems. Improper configuration can cause:
- Equipment damage
- Personal injury
- Loss of vehicle control

### Best Practices
1. **Always test in manual mode first** before arming PID
2. **Start with conservative PID gains** and increase gradually
3. **Use safety override** for critical applications
4. **Implement physical emergency stops** independent of this controller
5. **Never exceed servo/actuator rated torque**
6. **Use appropriately rated power supplies** (servo current draw can be high)
7. **Isolate signal lines** from high-current servo power
8. **Monitor temperature** of servos and ESP32 during extended use

### Recommended Safety Additions
- External hardware watchdog timer
- Redundant manual cutoff switch
- Current limiting on servo power supply
- Flyback diodes on servo motor (if not built-in)
- Proper strain relief on all connections
- Fusing on power circuits

## Contributing

Contributions welcome! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit changes (`git commit -m 'Add amazing feature'`)
4. Push to branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow existing code style (2-space indentation)
- Comment complex algorithms
- Test on hardware before submitting
- Update README for new features/commands

## License

[MIT License](LICENSE) - feel free to use in personal or commercial projects

## Acknowledgments

- [Arduino PID Library](https://github.com/br3ttb/Arduino-PID-Library) by Brett Beauregard
- [ESP32Servo Library](https://github.com/madhephaestus/ESP32Servo) by Kevin Harrington
- ESP32 Arduino Core contributors

## Version History

### v1.0.0 (Current)
- Initial release
- Period-based RPM measurement with noise rejection
- Dual-mode operation (Manual/Automatic)
- PID control with aggressiveness scaling
- Bluetooth Classic support
- NVS persistence with dirty flag management
- Safety override system
- Configurable PPR (1/2/4)
- Adjustable PID sample time
- EMA RPM filtering with user-configurable alpha

## Support

For issues, questions, or feature requests:
- Open an [Issue](https://github.com/Flyingfitz737/Clutch-Control/issues)
- Check existing issues for solutions
- Provide hardware details and serial output for bugs

---

**Built with ❤️ for the DIY automation community**
````

All the repository URLs have been updated to `https://github.com/Flyingfitz737/Clutch-Control`! You can now copy this directly to your repository.

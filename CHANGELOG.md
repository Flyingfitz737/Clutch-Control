# Changelog

All notable changes to the Clutch-Control project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- CONTRIBUTING.md with comprehensive GitHub Copilot workflow guide
- CHANGELOG.md for tracking version history
- Documentation on how to access files and maintain continuity

## [1.1.0] - 2024-02-04

### Added
- **Servo Preposition Feature**: User-configurable servo position when system is armed
  - New global variable `preposition` (default: 90 degrees)
  - Command: `calibrate set_preposition <value>` (range: 0-180)
  - Value saved to non-volatile memory (Preferences library)
  - Validation ensures value is within calibration bounds (min_position to max_position)
  - Helper function `moveServoToPreposition()` to handle servo movement
  - `attemptArm()` function modified to move servo to preposition before engaging PID
  - Status functions updated to display preposition value
  - Help commands updated to document the feature

- **Proper Arduino Project Structure**
  - Created 7 Arduino project folders with standard naming (no spaces)
  - All sketches now have proper `.ino` file extensions
  - Each project folder contains a README with usage instructions
  - Files are now directly compatible with Arduino IDE

### Changed
- **README.md Enhanced**
  - Added "📁 Where to Find the Complete Code" section
  - Visual navigation with emojis (📂 📄 📖)
  - Direct links to all code files
  - Clear recommendations (ESP32 marked as "Recommended")
  - Quick Start guide added
  - Professional, scannable format

- **Repository Organization**
  - Organized all code into proper Arduino project folders
  - Removed spaces from folder and file names for better compatibility
  - Each folder now contains complete code ready for Arduino IDE

### Fixed
- File discoverability - users can now easily find complete code files
- Arduino IDE compatibility - proper .ino extensions and folder structure

## [1.0.0] - 2024-01-XX

### Added
- **EMC Type 1 Controller** - Initial release
  - User-configurable parameters via Serial Monitor
  - Real-time RPM sensor input
  - PID control for automatic clutch engagement
  - Servo motor control for clutch actuation
  - LED arming light with status feedback
  - Serial command interface for remote operation

- **ESP32 Version Features**
  - Bluetooth Classic communication (Device: `EMC_Type_1_Controller`)
  - Wireless remote control and monitoring
  - Simultaneous Serial and Bluetooth feedback
  - Non-volatile storage using ESP32 Preferences library

- **Arduino Uno Version**
  - Core EMC Type 1 features
  - EEPROM storage for calibration parameters
  - Serial communication only

- **Calibration System**
  - Customizable servo range (min/max positions)
  - Neutral position configuration
  - Direction control (normal/reversed)
  - Real-time visual feedback during calibration
  - Non-volatile storage of all parameters
  - Automatic validation of parameters

- **Safety Override System**
  - Configurable potentiometer threshold
  - Automatic disarm when threshold exceeded
  - Safety indicator via faster LED flashing
  - Rearm protection requiring switch toggle

- **Commands**
  - `setrpm <value>` - Set target RPM
  - `setpid <kp> <ki> <kd>` - Configure PID constants
  - `arm` / `disarm` - Toggle control modes
  - `calibrate set_min <value>` - Set minimum servo position
  - `calibrate set_max <value>` - Set maximum servo position
  - `calibrate set_neutral <value>` - Set neutral servo position
  - `calibrate direction <0|1>` - Set servo direction
  - `safety enable` / `safety disable` - Control safety override
  - `safety set_threshold <value>` - Set safety threshold
  - `status` - Display system status
  - `help` - Show command list

- **Alternative Controllers**
  - Clutch Control PID Basic
  - Clutch Control Arm Light PID Basic
  - Clutch Control PID Auto Tune
  - PID Autotune
  - PID Auto Tune 20%

- **Documentation**
  - EMC_Type_1_README.md - Detailed functionality documentation
  - System_Workflow_Overview.md - Step-by-step setup guide
  - README.md - Repository overview

## Version Number Guide

Version numbers follow Semantic Versioning (MAJOR.MINOR.PATCH):

- **MAJOR** version: Incompatible API changes or major architectural changes
- **MINOR** version: New features added in a backward compatible manner
- **PATCH** version: Backward compatible bug fixes

## Type of Changes

- **Added**: New features
- **Changed**: Changes in existing functionality
- **Deprecated**: Soon-to-be removed features
- **Removed**: Removed features
- **Fixed**: Bug fixes
- **Security**: Vulnerability fixes

---

## How to Update This File

When making changes to the repository:

1. Add your changes under the `[Unreleased]` section
2. Use the appropriate change type (Added, Changed, Fixed, etc.)
3. Write clear, concise descriptions
4. When creating a release, move Unreleased items to a new version section
5. Add the release date in YYYY-MM-DD format

Example:
```markdown
## [Unreleased]

### Added
- New temperature sensor support on GPIO22

### Fixed
- Bluetooth reconnection issue after power cycle
```

Then when releasing version 1.2.0:
```markdown
## [1.2.0] - 2024-02-15

### Added
- New temperature sensor support on GPIO22

### Fixed
- Bluetooth reconnection issue after power cycle

## [Unreleased]
```

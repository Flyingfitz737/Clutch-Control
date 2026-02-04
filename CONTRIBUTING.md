# Contributing to Clutch-Control

This guide explains how to work with this repository, use GitHub Copilot to make improvements, and maintain continuity with all changes.

## 📁 Repository Structure

The repository is organized with proper Arduino project structure:

```
Clutch-Control/
├── EMC_Type_1_ESP32/              # Primary controller (Recommended)
│   ├── EMC_Type_1_ESP32.ino      # Complete Arduino sketch
│   └── README.md                  # Project-specific documentation
├── EMC_Type_1_Arduino/            # Arduino Uno version
│   ├── EMC_Type_1_Arduino.ino
│   └── README.md
├── Clutch_Control_PID_Basic/      # Alternative controllers
├── Clutch_Control_Arm_Light_PID_Basic/
├── Clutch_Control_PID_Auto_Tune/
├── PID_Autotune/
├── PID_Auto_Tune_20_Percent/
├── README.md                      # Main documentation
├── CONTRIBUTING.md                # This file
├── CHANGELOG.md                   # Version history
├── EMC_Type_1_README.md          # Detailed functionality docs
└── System_Workflow_Overview.md   # Setup guide
```

## 🤖 Using GitHub Copilot to Modify Code

### 1. Accessing the Files

**Local Development:**
```bash
# Clone the repository
git clone https://github.com/Flyingfitz737/Clutch-Control.git
cd Clutch-Control

# Open in your preferred editor (VS Code recommended)
code .
```

**GitHub Codespaces (Recommended):**
- Go to the repository on GitHub
- Click the green "Code" button
- Select "Codespaces" tab
- Click "Create codespace on main"
- GitHub Copilot will be automatically available

**File Locations:**
- **Primary code to modify:** `EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino`
- **Arduino Uno version:** `EMC_Type_1_Arduino/EMC_Type_1_Arduino.ino`
- **Documentation:** `*.md` files in root directory

### 2. Making Changes with GitHub Copilot

#### Step-by-Step Workflow:

1. **Create a Feature Branch**
   ```bash
   git checkout -b feature/your-improvement-name
   ```

2. **Open the File You Want to Modify**
   - Navigate to the appropriate folder (e.g., `EMC_Type_1_ESP32/`)
   - Open the `.ino` file in your editor

3. **Use GitHub Copilot Suggestions**
   - Write comments describing what you want to do
   - Copilot will suggest code completions
   - Example:
     ```cpp
     // Add a function to calculate average RPM over the last 10 readings
     // Copilot will suggest implementation
     ```

4. **Ask Copilot Chat for Help**
   - Use Copilot Chat to ask questions about the code
   - Example: "Explain how the PID control loop works in this file"
   - Example: "How can I add a new calibration parameter?"

5. **Test Your Changes**
   - Upload to your Arduino/ESP32 board
   - Verify functionality works as expected
   - Check all existing features still work

6. **Commit Your Changes**
   ```bash
   git add .
   git commit -m "Add: Brief description of improvement"
   ```

7. **Push and Create Pull Request**
   ```bash
   git push origin feature/your-improvement-name
   ```
   - Go to GitHub and create a Pull Request
   - Describe your changes in detail

### 3. GitHub Copilot Best Practices for This Repository

**Use Descriptive Comments:**
```cpp
// Add a new command to set the servo acceleration rate
// Range: 1-100 degrees per second
// Save to non-volatile storage
// Command format: "calibrate set_acceleration <value>"
```

**Ask Copilot to Maintain Consistency:**
- "Follow the existing pattern for calibration commands"
- "Use the same error handling as other commands"
- "Add this feature using the dual print functions for Serial and Bluetooth"

**Request Documentation:**
- "Add comments explaining this PID calculation"
- "Update the help text to include this new command"

## 📝 Version Management

### Saving Future Versions

**Option 1: Git Tags (Recommended for Releases)**
```bash
# After significant improvements, create a version tag
git tag -a v1.0.0 -m "Version 1.0.0: Added preposition feature"
git push origin v1.0.0
```

**Option 2: Git Branches (For Development)**
```bash
# Main branch: stable, tested code
# Feature branches: active development
git checkout -b feature/new-feature
```

**Option 3: GitHub Releases**
1. Go to repository on GitHub
2. Click "Releases" → "Create a new release"
3. Choose a tag version (e.g., v1.1.0)
4. Add release notes describing improvements
5. Attach compiled binaries if available

### Version Numbering

We use Semantic Versioning (SemVer):
- **Major.Minor.Patch** (e.g., 1.2.3)
- **Major**: Breaking changes or major new features
- **Minor**: New features, backward compatible
- **Patch**: Bug fixes and minor improvements

### Tracking Improvements

**Update CHANGELOG.md for Every Change:**
```markdown
## [1.1.0] - 2024-02-04
### Added
- Servo preposition feature for customized armed state position
- Command: `calibrate set_preposition <value>`
- Non-volatile storage for preposition value

### Changed
- Reorganized code into proper Arduino project folders

### Fixed
- None
```

## 🔄 Git Workflow for Continuity

### Basic Workflow

```bash
# 1. Always start from main branch
git checkout main
git pull origin main

# 2. Create feature branch
git checkout -b feature/add-new-sensor

# 3. Make changes with GitHub Copilot assistance
# ... edit files ...

# 4. Commit frequently with clear messages
git add .
git commit -m "Add: Support for temperature sensor on GPIO22"

# 5. Push to GitHub
git push origin feature/add-new-sensor

# 6. Create Pull Request on GitHub
# 7. After review and merge, update local main
git checkout main
git pull origin main

# 8. Delete feature branch
git branch -d feature/add-new-sensor
```

### Commit Message Format

Follow this format for consistency:
```
Type: Brief description (50 chars or less)

Detailed explanation if needed (wrap at 72 chars)

- Bullet points for multiple changes
- Reference issues: Fixes #123
```

**Types:**
- `Add:` New feature or functionality
- `Fix:` Bug fix
- `Update:` Changes to existing feature
- `Docs:` Documentation only
- `Refactor:` Code restructuring without behavior change
- `Test:` Adding or updating tests

### Examples

```bash
git commit -m "Add: RPM averaging function for smoother control"

git commit -m "Fix: Servo preposition not saved to Preferences

The preposition value was being set but not persisted
to non-volatile storage. Added preferences.putInt() call
in the set_preposition command handler."

git commit -m "Docs: Update System_Workflow_Overview.md with preposition setup"
```

## 📂 Which Files to Modify

### For Feature Development

| What You Want to Do | File to Modify | Notes |
|---------------------|----------------|-------|
| Add new functionality | `EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino` | Primary controller code |
| Arduino Uno changes | `EMC_Type_1_Arduino/EMC_Type_1_Arduino.ino` | Keep in sync with ESP32 version |
| Update features list | `README.md` | Main repository overview |
| Document new commands | `EMC_Type_1_README.md` | Detailed functionality docs |
| Add setup instructions | `System_Workflow_Overview.md` | User guide |
| Track changes | `CHANGELOG.md` | Version history |

### File Organization Rules

1. **Keep .ino files in their respective folders**
   - Don't move `EMC_Type_1_ESP32.ino` out of `EMC_Type_1_ESP32/` folder
   - Arduino IDE requires sketch name to match folder name

2. **Update both versions if applicable**
   - If you add a feature to ESP32 version, consider adding to Arduino version too
   - Document platform-specific features clearly

3. **Maintain documentation**
   - Update README files when adding features
   - Keep CHANGELOG.md current
   - Add comments in code for future reference

## 🎯 Common Scenarios with GitHub Copilot

### Scenario 1: Adding a New Sensor

1. Open `EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino`
2. Find the "Pin Definitions" section
3. Add comment: `// Add temperature sensor on GPIO22`
4. Let Copilot suggest the pin definition
5. Add reading logic in `readSensors()` function
6. Update `printDetailedStatus()` to display temperature
7. Test and commit

### Scenario 2: Adding a New Command

1. Locate `processCommand()` function
2. Add comment: `// Add command to set temperature threshold: "temp set_threshold <value>"`
3. Let Copilot suggest the command parsing code
4. Follow existing pattern (like calibration commands)
5. Add to help text in `printHelp()` and `setup()`
6. Test with Serial and Bluetooth
7. Update documentation

### Scenario 3: Modifying PID Behavior

1. Find `runPIDControl()` function
2. Add descriptive comment about desired change
3. Use Copilot Chat: "Explain this PID implementation"
4. Make changes with Copilot's help
5. Test extensively - PID changes affect system stability
6. Document the change in comments

## 🧪 Testing Your Changes

Before committing:

1. **Compile Check**
   - Verify code compiles in Arduino IDE
   - Check for warnings

2. **Hardware Test**
   - Upload to actual hardware
   - Test new feature
   - Verify existing features still work

3. **Serial Monitor Test**
   - Test new commands via Serial
   - Test via Bluetooth (ESP32)

4. **Documentation Check**
   - Updated README if needed
   - Updated CHANGELOG.md
   - Added code comments

## 🚀 Maintaining Continuity

### Before Making Changes

1. **Pull Latest Code**
   ```bash
   git checkout main
   git pull origin main
   ```

2. **Review Recent Changes**
   ```bash
   git log --oneline -10
   ```

3. **Read CHANGELOG.md**
   - Understand what's been added recently
   - Check for breaking changes

### While Making Changes

1. **Use Clear Branch Names**
   - `feature/add-temperature-sensor`
   - `fix/bluetooth-connection-issue`
   - `docs/update-setup-guide`

2. **Commit Often with Clear Messages**
   - Small, focused commits are better
   - Each commit should work (compilable)

3. **Document As You Go**
   - Update CHANGELOG.md
   - Add code comments
   - Update README files

### After Making Changes

1. **Create Detailed Pull Request**
   - Describe what changed
   - Explain why it changed
   - List any breaking changes
   - Add testing notes

2. **Keep PR Focused**
   - One feature per PR
   - Easier to review and merge
   - Easier to revert if needed

## 📋 Checklist for New Features

Before submitting a pull request:

- [ ] Code compiles without errors or warnings
- [ ] Tested on actual hardware
- [ ] Existing features still work
- [ ] New commands added to help text
- [ ] Code comments added/updated
- [ ] CHANGELOG.md updated
- [ ] README.md updated (if user-facing change)
- [ ] Clear commit messages
- [ ] Branch has descriptive name

## 🆘 Getting Help

### Using GitHub Copilot Chat

Ask specific questions:
- "How does the calibration save/load system work?"
- "What's the best way to add a new sensor reading?"
- "Explain the safety override logic"
- "How can I add a new Bluetooth command?"

### Resources

- **Arduino IDE Documentation**: https://www.arduino.cc/reference/en/
- **ESP32 Documentation**: https://docs.espressif.com/projects/arduino-esp32/
- **PID Library**: https://github.com/br3ttb/Arduino-PID-Library/
- **Git Guide**: https://guides.github.com/

## 📞 Questions?

If you have questions about contributing:
1. Check existing documentation in the repository
2. Use GitHub Copilot Chat for code-specific questions
3. Open an issue on GitHub for discussion
4. Reference CHANGELOG.md to see how previous features were implemented

---

**Remember:** GitHub Copilot is a powerful assistant, but always review and test its suggestions. The goal is to maintain code quality and system stability while making improvements.

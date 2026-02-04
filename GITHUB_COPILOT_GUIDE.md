# Quick Reference: Working with GitHub Copilot

This is a quick reference for using GitHub Copilot to modify and improve the Clutch-Control codebase.

## 🎯 Quick Answer to Common Questions

### "Where do I find the code?"

**Primary Files to Modify:**
- **ESP32 (Recommended):** `EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino`
- **Arduino Uno:** `EMC_Type_1_Arduino/EMC_Type_1_Arduino.ino`

### "How do I save future versions?"

**Method 1: Git Commits (Day-to-day)**
```bash
git add .
git commit -m "Add: Description of change"
git push
```

**Method 2: Git Tags (Milestones)**
```bash
git tag -a v1.2.0 -m "Version 1.2.0 with new features"
git push origin v1.2.0
```

**Method 3: GitHub Releases (Public releases)**
- Go to GitHub repository → Releases → Create new release

### "How do I maintain continuity?"

1. **Always start from main branch:**
   ```bash
   git checkout main
   git pull origin main
   ```

2. **Create feature branches:**
   ```bash
   git checkout -b feature/my-improvement
   ```

3. **Update CHANGELOG.md** with every change

4. **Use clear commit messages:**
   - `Add: New feature`
   - `Fix: Bug description`
   - `Update: Changed functionality`

## 🚀 5-Minute Workflow

### Setup (First Time Only)
```bash
# Clone repository
git clone https://github.com/Flyingfitz737/Clutch-Control.git
cd Clutch-Control

# Open in VS Code (or your editor)
code .
```

### Making Changes
```bash
# 1. Update your local code
git checkout main
git pull

# 2. Create feature branch
git checkout -b feature/add-temperature-sensor

# 3. Open file in editor
# EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino

# 4. Use GitHub Copilot to make changes
# - Add comments describing what you want
# - Accept Copilot's suggestions
# - Use Copilot Chat for explanations

# 5. Test on hardware
# Upload to Arduino/ESP32 and verify

# 6. Commit changes
git add .
git commit -m "Add: Temperature sensor support"

# 7. Push to GitHub
git push origin feature/add-temperature-sensor

# 8. Create Pull Request on GitHub
```

## 📝 GitHub Copilot Tips

### Get Better Suggestions

**Write descriptive comments:**
```cpp
// Add a new command to set servo acceleration
// Command format: "calibrate set_accel <value>"
// Range: 1-100 degrees per second
// Save to Preferences
```

**Ask Copilot Chat questions:**
- "Explain how the PID loop works in this code"
- "How can I add a new sensor reading?"
- "Show me how to add a Bluetooth command"

### Maintain Code Style

**Tell Copilot to match existing patterns:**
```cpp
// Add a new calibration command following the same pattern as set_min and set_max
```

**Reference existing code:**
```cpp
// Use the same error handling as the other calibration commands
```

## 📂 File Map

| Task | File to Edit | Section |
|------|-------------|---------|
| Add sensor | `EMC_Type_1_ESP32.ino` | `readSensors()` function |
| Add command | `EMC_Type_1_ESP32.ino` | `processCommand()` function |
| Change PID | `EMC_Type_1_ESP32.ino` | `runPIDControl()` function |
| Add pin | `EMC_Type_1_ESP32.ino` | "Pin Definitions" section |
| Update help | `EMC_Type_1_ESP32.ino` | `printHelp()` and `setup()` |
| Update docs | `README.md` or `EMC_Type_1_README.md` | Relevant section |
| Track changes | `CHANGELOG.md` | Add under `[Unreleased]` |

## 🔍 Common Tasks

### Adding a New Command

1. Find `processCommand()` function
2. Add new `else if` block following existing pattern
3. Parse command parameters
4. Add validation
5. Implement functionality
6. Save to Preferences if needed
7. Update `printHelp()` function
8. Test via Serial and Bluetooth

### Adding a New Sensor

1. Define pin in "Pin Definitions" section
2. Add variable to store reading
3. Add reading logic to `readSensors()`
4. Display in `printStatus()` or `printDetailedStatus()`
5. Add configuration commands if needed
6. Update documentation

### Modifying PID Behavior

1. Locate `runPIDControl()` function
2. Add comments explaining desired change
3. Modify PID calculation or parameters
4. Test extensively (PID affects system stability)
5. Document changes in code comments
6. Update CHANGELOG.md

## 📊 Version Numbers

When to increment version:

- **1.x.x → 2.x.x (Major):** Breaking changes, major rewrites
- **x.1.x → x.2.x (Minor):** New features, backward compatible
- **x.x.1 → x.x.2 (Patch):** Bug fixes, small improvements

## ⚡ Quick Commands Reference

```bash
# View recent changes
git log --oneline -10

# See what's changed locally
git status
git diff

# Undo uncommitted changes
git checkout -- filename

# Switch branches
git checkout branch-name

# See all branches
git branch -a

# Update CHANGELOG
nano CHANGELOG.md
# Add your changes under [Unreleased]

# Create version tag
git tag -a v1.2.0 -m "Version 1.2.0"
git push origin v1.2.0

# View tags
git tag -l
```

## 📖 Full Documentation

For complete details, see:
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - Complete workflow guide
- **[CHANGELOG.md](CHANGELOG.md)** - Version history
- **[README.md](README.md)** - Repository overview
- **[EMC_Type_1_README.md](EMC_Type_1_README.md)** - Technical documentation

## 🆘 Troubleshooting

**Problem:** Can't find the code  
**Solution:** Look in `EMC_Type_1_ESP32/EMC_Type_1_ESP32.ino`

**Problem:** Changes not showing up  
**Solution:** Make sure you've saved the file and pushed to GitHub

**Problem:** Lost track of changes  
**Solution:** Check `git log` and `CHANGELOG.md`

**Problem:** Copilot not suggesting anything  
**Solution:** Write more descriptive comments, use Copilot Chat

**Problem:** Don't know where to add feature  
**Solution:** Check the "File Map" table above

---

**Remember:** 
- Always work in feature branches
- Commit often with clear messages
- Update CHANGELOG.md
- Test before pushing
- Use GitHub Copilot Chat when stuck

For detailed information, refer to **[CONTRIBUTING.md](CONTRIBUTING.md)**

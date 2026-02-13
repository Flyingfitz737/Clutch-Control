# How to Merge the Pull Request

This guide explains how to merge the pull request that updates the V18 file with the complete EMC Type 1 UNO code.

## Pull Request Details

**Branch to Merge:** `copilot/copy-emc-type-1-uno-to-v18`  
**Target Branch:** `main`  
**Changes:** V18 file updated with complete ESP32 controller code (+1,369 lines, 47KB)

---

## Method 1: Using GitHub Web Interface (Recommended)

This is the easiest method and recommended for most users.

### Steps:

1. **Go to your repository on GitHub:**
   - Visit: https://github.com/Flyingfitz737/Clutch-Control

2. **Navigate to Pull Requests:**
   - Click on the "Pull requests" tab at the top of the repository

3. **Find the PR:**
   - Look for the pull request titled something like "Copy 'EMC Type 1 UNO' to V18 File"
   - If you don't see it, it might need to be created first from the branch

4. **Review the Changes:**
   - Click on the PR to open it
   - Review the "Files changed" tab to see what will be merged
   - Should show V18 file with +1,369 lines added

5. **Merge the Pull Request:**
   - Click the green "Merge pull request" button
   - Choose merge method:
     - **"Create a merge commit"** (recommended) - preserves full history
     - **"Squash and merge"** - combines all commits into one
     - **"Rebase and merge"** - applies commits directly on main

6. **Confirm the Merge:**
   - Click "Confirm merge"
   - Optionally, delete the branch after merging

---

## Method 2: Using Git Command Line

If you prefer to merge locally using Git commands:

### Prerequisites:
- Git installed on your computer
- Repository cloned locally
- Push access to the main branch

### Steps:

```bash
# 1. Navigate to your repository
cd /path/to/Clutch-Control

# 2. Make sure you're on the main branch
git checkout main

# 3. Pull the latest changes from main
git pull origin main

# 4. Fetch the PR branch
git fetch origin copilot/copy-emc-type-1-uno-to-v18

# 5. Merge the PR branch into main
git merge origin/copilot/copy-emc-type-1-uno-to-v18

# 6. Push the merged changes to main
git push origin main

# 7. (Optional) Delete the feature branch remotely
git push origin --delete copilot/copy-emc-type-1-uno-to-v18
```

### Alternative: Merge with --no-ff (preserves branch history)

```bash
git merge --no-ff origin/copilot/copy-emc-type-1-uno-to-v18 -m "Merge PR: Update V18 with EMC Type 1 UNO code"
git push origin main
```

---

## Method 3: Using GitHub CLI

If you have GitHub CLI (`gh`) installed:

```bash
# 1. Navigate to your repository
cd /path/to/Clutch-Control

# 2. List open pull requests
gh pr list

# 3. Merge the PR (replace NUMBER with the PR number)
gh pr merge NUMBER --merge

# Or merge with squash
gh pr merge NUMBER --squash

# Or merge with rebase
gh pr merge NUMBER --rebase
```

---

## Verification After Merge

After merging, verify that the changes are in the main branch:

### Using GitHub Web Interface:
1. Go to your repository on GitHub
2. Make sure you're viewing the `main` branch (check branch selector)
3. Navigate to the V18 file
4. Verify it contains the complete ESP32 controller code (should be ~1,370 lines)

### Using Git Command Line:
```bash
# Switch to main branch
git checkout main

# Pull latest changes
git pull origin main

# Check V18 file
cat V18 | head -20    # View first 20 lines
wc -l V18             # Should show 1370 lines
ls -lh V18            # Should show ~47K file size
```

---

## Expected Result

After merging, the V18 file in the main branch should contain:
- **Size:** 47,613 bytes (~47KB)
- **Lines:** 1,370 lines of code
- **Content:** Complete ESP32 EMC Type 1 Controller code with:
  - BLE/NimBLE support
  - PID control system
  - Servo control
  - RPM sensing
  - Telemetry system
  - Safety override features
  - NVS-backed configuration

---

## Troubleshooting

### "No Pull Request Found"
If you don't see the pull request on GitHub:
1. The branch exists but a PR wasn't created yet
2. Go to the repository, click "Compare & pull request" or manually create a PR
3. Select `copilot/copy-emc-type-1-uno-to-v18` as the source and `main` as the target

### "Merge Conflicts"
If you encounter merge conflicts:
1. The main branch has changed since the PR was created
2. You'll need to resolve conflicts manually
3. Update the PR branch first: `git merge main` on the PR branch, resolve conflicts, then merge to main

### "Permission Denied"
If you can't push to main:
1. Ensure you have write access to the repository
2. Check if branch protection rules are enabled on main
3. You may need to merge via the GitHub UI instead

---

## Need Help?

If you encounter any issues:
1. Check the GitHub documentation: https://docs.github.com/en/pull-requests
2. Review Git merge documentation: https://git-scm.com/docs/git-merge
3. Ask for assistance in the repository issues or discussions


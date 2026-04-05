# 20260405141016 Git 

## Reset or Restore a file from the Repository

Don't worry, this is a very common scenario. To reset **just that one file** to match exactly what is currently on GitHub, follow these steps in your PowerShell:

### 1. Update your local knowledge of GitHub
First, make sure your computer knows exactly what is on GitHub right now:
```powershell
git fetch origin
```

### 2. Reset the file
Run this command to "pull" the version of the README from the GitHub main branch (usually named `main` or `master`) and overwrite your local copy:

**If your branch is called `main`:**
```powershell
git checkout origin/main -- README.md
```

**If your branch is called `master`:**
```powershell
git checkout origin/master -- README.md
```

---

### What if I want to use the modern command?
Git recently introduced a newer, more intuitive command called `restore`. This does the exact same thing:
```powershell
git restore --source origin/main README.md
```

### How to check which branch you are on?
If you aren't sure if your branch is `main` or `master`, just type:
```powershell
git branch
```
(The one with the `*` next to it is your current branch).

### Summary of what happened:
*   **`git fetch`**: Talks to GitHub and gets the latest data without changing your code.
*   **`origin/main`**: Refers to the version of the code stored on GitHub.
*   **`-- README.md`**: Tells Git to only target that specific file, leaving the rest of your Zettelkasten notes safe and untouched.

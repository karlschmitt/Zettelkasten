---
id: 20260414132020
title: Parsing files
date: 2016-04-16
---

#  Parsing files


In PowerShell, the equivalent to the Linux `grep` command is **`Select-String`** (often aliased as **`sls`**).

While it works similarly to grep, the biggest difference is that PowerShell outputs **objects** rather than just plain text. This allows you to perform powerful data manipulation on your results.

Here is how to perform common grep tasks using PowerShell.

---

### 1. Basic Search in a Single File
**Grep:** `grep "error" app.log`  
**PowerShell:**
```powershell
Select-String -Path "app.log" -Pattern "error"
```

### 2. Search Recursively (The most common use case)
**Grep:** `grep -r "connection" .`  
**PowerShell:**
```powershell
# Short version
ls -r | sls "connection"

# Formal version
Get-ChildItem -Recurse | Select-String -Pattern "connection"
```

### 3. Case Sensitivity
PowerShell is **case-insensitive** by default (the opposite of grep).
*   **To ignore case:** Just run the command normally.
*   **To force case-sensitivity:** Use the `-CaseSensitive` flag.
```powershell
Select-String -Path "file.txt" -Pattern "StrictSearch" -CaseSensitive
```

### 4. Search Multiple File Types
**Grep:** `grep "function" *.js *.ts`  
**PowerShell:**
```powershell
Select-String -Path "*.js", "*.ts" -Pattern "function"
```

### 5. Invert Match (Show lines that DON'T match)
**Grep:** `grep -v "info" app.log`  
**PowerShell:**
```powershell
Select-String -Path "app.log" -Pattern "info" -NotMatch
```

### 6. List Filenames Only (Hide the content)
**Grep:** `grep -l "password" *.cfg`  
**PowerShell:**
```powershell
Select-String -Path "*.cfg" -Pattern "password" | Select-Object -Unique Path
# OR
Select-String -Path "*.cfg" -Pattern "password" -List | Select-Object Path
```

### 7. Show Context (Lines before and after)
**Grep:** `grep -C 3 "error" app.log`  
**PowerShell:**
```powershell
Select-String -Path "app.log" -Pattern "error" -Context 3
```
*(You can also use `-Context 2, 4` to get 2 lines before and 4 lines after).*

---

### Comparison Cheat Sheet

| Feature | Linux `grep` | PowerShell `Select-String` |
| :--- | :--- | :--- |
| **Basic Search** | `grep "pat" file` | `sls "pat" file` |
| **Recursive** | `grep -r "pat" .` | `ls -r \| sls "pat"` |
| **Ignore Case** | `-i` | (Default) |
| **Case Sensitive** | (Default) | `-CaseSensitive` |
| **Invert Match** | `-v` | `-NotMatch` |
| **Line Numbers** | `-n` | (Included by default) |
| **List Files Only** | `-l` | `-List` |
| **Regex** | (Standard) | (Standard) |

---

### Pro Tip: The "Power" in PowerShell
Because `Select-String` returns objects, you can do things `grep` cannot easily do. For example, if you want to find a string and then open all those files in VS Code:

```powershell
Select-String -Pattern "TODO" -Path ".\src\*" | ForEach-Object { code $_.Path }
```

Or, if you just want to see the **Line Number** and **Filename** in a clean table:

```powershell
sls "Warning" *.log | Select-Object LineNumber, FileName, Line
```
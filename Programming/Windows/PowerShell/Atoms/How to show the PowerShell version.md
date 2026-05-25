---
id: 20260504204053
title: How to show the PowerShell version?
author: Karl Schmitt
date: 2026-05-04
---

# How to show PowerShell version?

To check the version of PowerShell you are currently running, use one of the following methods:

### Method 1: Using the `$PSVersionTable` Variable (Recommended)
This is the most reliable way to get detailed version information.

1.  Open PowerShell.
2.  Type the following and press **Enter**:
    ```powershell
    $PSVersionTable
    ```
3.  Look for the **PSVersion** line. 

*Example Output:*
```text
Name                           Value
----                           -----
PSVersion                      7.4.1
PSEdition                      Core
...
```

---

### Method 2: Using the `Get-Host` Command
This provides the version of the PowerShell "Host" (the program you are interacting with).

1.  Type the following and press **Enter**:
    ```powershell
    Get-Host | Select-Object Version
    ```

---

### Method 3: Checking from a different terminal (CMD or Bash)
If you aren't inside PowerShell yet and want to check which version is installed:

*   **For Windows PowerShell (older versions):**
    ```cmd
    powershell -command "$PSVersionTable.PSVersion"
    ```
*   **For PowerShell Core (newer v6/v7+):**
    ```bash
    pwsh --version
    ```

---

### Which version am I looking at?
*   **Version 5.1:** This is "Windows PowerShell." It comes built-in with Windows 10 and 11 and is no longer receiving new features.
*   **Version 7.x:** This is "PowerShell Core." It is the modern, cross-platform version that you install manually.
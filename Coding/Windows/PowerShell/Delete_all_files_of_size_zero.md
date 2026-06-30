---
id: 20260416145226
title: How to delete all files of size zero?
date: 2026-04-16
---

# How to delete all files of size zero?

To delete all files of size zero in the current directory (and subdirectories), use the following PowerShell command:

### The Basic Command (Current Directory Only)
```powershell
Get-ChildItem -File | Where-Object { $_.Length -eq 0 } | Remove-Item
```

### The Recursive Command (Includes Subfolders)
This is the most common version used to clean up a whole drive or project folder:
```powershell
Get-ChildItem -Recurse -File | Where-Object { $_.Length -eq 0 } | Remove-Item
```

---

### Breakdown of the command:
1.  **`Get-ChildItem -Recurse -File`**: 
    *   `-Recurse`: Looks into all subfolders.
    *   `-File`: Only looks for files (ignores folders themselves, which don't have a "length" in the same way).
2.  **`Where-Object { $_.Length -eq 0 }`**: 
    *   Filters the list to only include items where the file size (`Length`) is exactly `0`.
3.  **`Remove-Item`**: 
    *   Deletes the files that passed the filter.

---

### Pro-Tips:

**1. Test before you delete (Safety First)**
If you want to see which files will be deleted without actually deleting them yet, add **`-WhatIf`** to the end:
```powershell
Get-ChildItem -Recurse -File | Where-Object { $_.Length -eq 0 } | Remove-Item -WhatIf
```

**2. Include Hidden Files**
By default, `Get-ChildItem` ignores hidden files. To include those in your cleanup, add the `-Force` parameter:
```powershell
Get-ChildItem -Recurse -File -Force | Where-Object { $_.Length -eq 0 } | Remove-Item -Force
```

**3. Shorthand Version**
If you are typing this quickly in the console, you can use aliases:
```powershell
dir -r -file | ? Length -eq 0 | del
```
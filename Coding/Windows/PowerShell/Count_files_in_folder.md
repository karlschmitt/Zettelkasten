---
id: 20260416153055
title: How to count the files in a folder?
---

# How to count the files in a folder?

The closest PowerShell equivalent to `ls | wc -l` is using the `.Count` property or the `Measure-Object` cmdlet.

Here are the most common ways to do it:

### 1. The Direct Approach (Fastest)
Wrap the command in parentheses and access the `.Count` property.
```powershell
(Get-ChildItem).Count
```

### 2. The Pipeline Approach (Closest to `wc -l`)
Use `Measure-Object` (aliased as `measure`). This is useful if you are already piping data.
```powershell
Get-ChildItem | Measure-Object
```

---

### Common Specific Scenarios

Since `ls` in Linux often implies "everything," but sometimes you only want files or specific subdirectories, here is how you refine the count:

**Count ONLY files (exclude folders):**
```powershell
(Get-ChildItem -File).Count
```

**Count everything in all subfolders (Recursive):**
```powershell
(Get-ChildItem -Recurse).Count
```

**Count including hidden files:**
```powershell
(Get-ChildItem -Force).Count
```

---

### Comparison to Linux
| Linux (Bash) | PowerShell |
| :--- | :--- |
| `ls \| wc -l` | `(ls).Count` |
| `ls -R \| wc -l` | `(ls -r).Count` |
| `find . -type f \| wc -l` | `(ls -File).Count` |

### A Note on PowerShell Aliases:
You can use the exact same syntax as Linux for the command names in PowerShell because `ls` is an alias for `Get-ChildItem`.
* **Shortest version:** `(ls).count`
* **Shortest pipeline version:** `ls | measure`
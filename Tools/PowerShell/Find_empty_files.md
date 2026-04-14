# 20260412181015 Find empty files

Absolutely—this is a very practical PowerShell task 👍

***

# 🔎 Find empty files (size = 0 bytes)

The key property is:

```powershell
$_.Length
```

Empty files have `Length = 0`.

***

## ✅ Basic command

```powershell
Get-ChildItem -Path C:\Projects -Recurse -File |
Where-Object { $_.Length -eq 0 }
```

✔ Finds all empty files\
✔ Includes subfolders\
✔ `-File` ensures only files (no folders)

***

## 📄 Show only full file paths

```powershell
Get-ChildItem -Path C:\Projects -Recurse -File |
Where-Object { $_.Length -eq 0 } |
Select-Object -ExpandProperty FullName
```

✔ Cleaner output (just paths)

***

## ⚡ Faster version (slightly optimized)

```powershell
Get-ChildItem -Path C:\Projects -Recurse -File -Filter * |
Where-Object Length -eq 0
```

***

## 🧪 Example: current folder

```powershell
Get-ChildItem -Recurse -File | Where-Object Length -eq 0
```

***

# 🗑️ Delete empty files (be careful!)

```powershell
Get-ChildItem -Path C:\Projects -Recurse -File |
Where-Object Length -eq 0 |
Remove-Item -WhatIf
```

✔ `-WhatIf` = **safe preview** (VERY important)

👉 If it looks good, remove `-WhatIf`:

```powershell
... | Remove-Item
```

***

# 🧠 Bonus: reusable function (like a tool)

```powershell
function Find-EmptyFiles {
    param (
        [string]$Path = "."
    )

    Get-ChildItem -Path $Path -Recurse -File |
    Where-Object { $_.Length -eq 0 }
}
```

### 👉 Usage:

```powershell
Find-EmptyFiles -Path C:\Projects
```

***

# 💡 Tip

Empty files ≠ empty folders\
If you ever want to find empty folders too, that’s a different trick 😉

***

If you want, I can combine both:\
👉 **find empty files + empty folders + delete safely in one script**

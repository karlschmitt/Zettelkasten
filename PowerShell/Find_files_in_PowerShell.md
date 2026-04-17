---
id: 20260414123754
title: Finding files
date: 2026-04-16
---


#  Finding files

Great question — and a perfect step forward 👍
PowerShell can absolutely replace the Linux `find` command, but the mindset is a bit different: **you work with objects instead of plain text**.

Let’s walk through it gently and practically.

---

# 🧠 The PowerShell Equivalent of `find`

In PowerShell, you mainly use:

```powershell
Get-ChildItem
```

👉 Alias: `ls`, `dir`

---

# 🔍 1. Find Files by Name

### Linux:

```bash
find . -name "*.txt"
```

### PowerShell:

```powershell
Get-ChildItem -Path . -Filter *.txt -Recurse
```

👉 Explanation:

* `-Filter` → faster than filtering later
* `-Recurse` → search subfolders

---

# 📂 2. Find Only Files (Not Directories)

```powershell
Get-ChildItem -Recurse -File -Filter *.txt
```

👉 Equivalent to:

```bash
find . -type f -name "*.txt"
```

---

# 📁 3. Find Only Directories

```powershell
Get-ChildItem -Recurse -Directory
```

---

# ⚡ 4. Filter by Size

### Example: Files larger than 1 MB

```powershell
Get-ChildItem -Recurse -File |
Where-Object { $_.Length -gt 1MB }
```

👉 Like:

```bash
find . -size +1M
```

---

# 🕒 5. Filter by Date

### Files modified in last 7 days

```powershell
Get-ChildItem -Recurse -File |
Where-Object { $_.LastWriteTime -gt (Get-Date).AddDays(-7) }
```

---

# 🔎 6. Search Inside Files (like `grep`)

### Linux:

```bash
grep "hello" *.txt
```

### PowerShell:

```powershell
Select-String -Path *.txt -Pattern "hello"
```

👉 Recursive search:

```powershell
Select-String -Path .\* -Pattern "hello" -Recurse
```

---

# 🔗 7. Combine Like a Pro (Pipeline Power)

```powershell
Get-ChildItem -Recurse -File -Filter *.log |
Where-Object { $_.Length -gt 1MB } |
Select-Object FullName, Length
```

👉 This is basically:

```bash
find . -name "*.log" -size +1M
```

---

# 🧪 8. Real Example: Find Empty Files

(Similar to what you asked before 👍)

```powershell
Get-ChildItem -Recurse -File |
Where-Object { $_.Length -eq 0 }
```

---

# 🧭 Key Differences vs Linux `find`

| Linux `find`             | PowerShell                  |
| ------------------------ | --------------------------- |
| Text-based               | Object-based                |
| Flags (`-name`, `-size`) | Parameters + `Where-Object` |
| One command              | Pipeline of commands        |

👉 In PowerShell you often:

> “Get everything → then filter step by step”

---

# 💡 Pro Tips

✅ Use `-Filter` when possible (faster)
✅ Use `-File` / `-Directory` to reduce noise
✅ Use `Where-Object` for complex logic

---

# 🚀 Mini Challenge

Try this:

👉 Find all `.txt` files **larger than 100 KB** modified in the last 3 days

```powershell
Get-ChildItem -Recurse -File -Filter *.txt |
Where-Object {
    $_.Length -gt 100KB -and
    $_.LastWriteTime -gt (Get-Date).AddDays(-3)
}
```

---

If you want, I can build you a **"PowerShell vs Linux cheat sheet"** — super useful if you're coming from Bash 👍

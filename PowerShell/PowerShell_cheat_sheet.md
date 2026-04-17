---
id: 20260414124401
title: PowerShell vs. Linux cheat sheet
date: 2026-04-16
---

#  PowerShell vs. Linux cheat sheet

Awesome — this will be **super useful for you** since you’re clearly thinking in both worlds already 💪
Here’s a **PowerShell ⇄ Linux (bash) cheat sheet** you can actually use daily.

---

# 🧠 PowerShell vs Linux Cheat Sheet

## 📂 File & Directory Commands

| Task              | Linux (bash)     | PowerShell                         |
| ----------------- | ---------------- | ---------------------------------- |
| List files        | `ls`             | `Get-ChildItem` (`ls`, `dir`)      |
| Change directory  | `cd folder`      | `Set-Location folder` (`cd`)       |
| Current directory | `pwd`            | `Get-Location`                     |
| Create file       | `touch file.txt` | `New-Item file.txt`                |
| Create folder     | `mkdir dir`      | `New-Item dir -ItemType Directory` |
| Copy              | `cp a b`         | `Copy-Item a b`                    |
| Move              | `mv a b`         | `Move-Item a b`                    |
| Delete            | `rm file`        | `Remove-Item file`                 |

---

## 🔍 Finding Files

| Task         | Linux                  | PowerShell                                                     |
| ------------ | ---------------------- | -------------------------------------------------------------- |
| Find by name | `find . -name "*.txt"` | `Get-ChildItem -Recurse -Filter *.txt`                         |
| Only files   | `-type f`              | `-File`                                                        |
| Only dirs    | `-type d`              | `-Directory`                                                   |
| By size      | `-size +1M`            | `Where-Object { $_.Length -gt 1MB }`                           |
| By date      | `-mtime -7`            | `Where-Object { $_.LastWriteTime -gt (Get-Date).AddDays(-7) }` |

---

## 🔎 Search Inside Files

| Task        | Linux         | PowerShell               |
| ----------- | ------------- | ------------------------ |
| Search text | `grep "text"` | `Select-String "text"`   |
| Recursive   | `grep -r`     | `Select-String -Recurse` |

Example:

```powershell
Select-String -Path .\* -Pattern "error" -Recurse
```

---

## 🔗 Pipelines (Important!)

| Concept | Linux | PowerShell |   |              |
| ------- | ----- | ---------- | - | ------------ |
| Pipe    | `     | ` (text)   | ` | ` (objects!) |

### Linux:

```bash
ps aux | grep chrome
```

### PowerShell:

```powershell
Get-Process | Where-Object Name -like "*chrome*"
```

👉 Key difference:

* Linux → text filtering
* PowerShell → object filtering

---

## 📦 Working with Data

| Task           | Linux              | PowerShell      |
| -------------- | ------------------ | --------------- |
| Filter         | `grep`             | `Where-Object`  |
| Select columns | `awk '{print $1}'` | `Select-Object` |
| Sort           | `sort`             | `Sort-Object`   |
| Count          | `wc -l`            | `.Count`        |

Example:

```powershell
Get-Process | Sort-Object CPU -Descending
```

---

## 🧪 Variables

| Linux         | PowerShell       |
| ------------- | ---------------- |
| `name="Luke"` | `$name = "Luke"` |
| `$name`       | `$name`          |

---

## 🔁 Loops

### Linux:

```bash
for i in {1..5}; do
  echo $i
done
```

### PowerShell:

```powershell
foreach ($i in 1..5) {
    $i
}
```

---

## 🌐 API Calls

| Linux  | PowerShell          |
| ------ | ------------------- |
| `curl` | `Invoke-RestMethod` |

```powershell
Invoke-RestMethod "https://swapi.dev/api/people/1/"
```

---

## 🛠️ System Info

| Task       | Linux       | PowerShell    |
| ---------- | ----------- | ------------- |
| Processes  | `ps`        | `Get-Process` |
| Services   | `systemctl` | `Get-Service` |
| Disk usage | `df -h`     | `Get-PSDrive` |

---

## 🧠 The BIG Mindset Shift

👉 Linux:

> “Everything is text”

👉 PowerShell:

> “Everything is an object”

Example:

```powershell
Get-Process | Get-Member
```

You’ll see:

* Properties (Name, CPU, Id)
* Methods

---

## ⚡ Power Moves (Very Useful)

### 1. Find large files

```powershell
Get-ChildItem -Recurse -File |
Where-Object { $_.Length -gt 100MB }
```

### 2. Find empty files

```powershell
Get-ChildItem -Recurse -File |
Where-Object { $_.Length -eq 0 }
```

### 3. Top CPU processes

```powershell
Get-Process |
Sort-Object CPU -Descending |
Select-Object -First 5
```

---

## 💡 Pro Tips

* Use **aliases** when learning (`ls`, `cd`)
* Then switch to **real cmdlets** (`Get-ChildItem`)
* Use:

```powershell
Get-Help <command> -Examples
```

---

# 🚀 If You Want to Go Further

Next logical step for you:

👉 Build a **"find clone" function in PowerShell**

I can guide you to build something like:

```powershell
Find-File -Name "*.txt" -SizeGT 1MB -Days 7
```

Just tell me 👍

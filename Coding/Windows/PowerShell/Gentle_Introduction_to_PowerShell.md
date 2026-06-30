---
id: 20260414123400
title: Gentle Introduction to PowerShell
date: 2026-04-16
---

#  Gentle Introduction to PowerShell

Absolutely — let’s build you a **gentle, beginner-friendly introduction to PowerShell** 🌱
I’ll keep it practical and aligned with how you like to learn (step-by-step, hands-on).

---

# 🧠 What is PowerShell?

**PowerShell** is:

* A **command-line shell** (like Bash)
* A **scripting language**
* Built on **.NET**, so it works with *objects*, not just text

👉 Think of it like:

> “A supercharged terminal where everything is an object you can inspect and manipulate.”

---

# ⚡ 1. Your First Command

Open PowerShell and type:

```powershell
Get-Process
```

👉 This shows all running processes.

---

# 🔍 2. Understanding Commands (Cmdlets)

PowerShell commands follow a pattern:

```text
Verb-Noun
```

Examples:

* `Get-Process`
* `Get-Service`
* `Get-ChildItem` (like `ls`)

👉 Try:

```powershell
Get-ChildItem
```

---

# 📂 3. Navigate the File System

```powershell
Get-Location        # Where am I?
Set-Location C:\    # Change directory
Get-ChildItem       # List files
```

Shortcut aliases:

* `ls` → `Get-ChildItem`
* `cd` → `Set-Location`

---

# 📦 4. Objects Instead of Text (VERY IMPORTANT)

In PowerShell, output is **objects**, not plain text.

Try:

```powershell
Get-Process | Get-Member
```

👉 This shows properties like:

* `Name`
* `CPU`
* `Id`

Now filter:

```powershell
Get-Process | Select-Object Name, CPU
```

---

# 🔗 5. The Pipeline (`|`)

The pipeline passes objects from one command to another:

```powershell
Get-Process | Where-Object CPU -gt 100
```

👉 Meaning:

* Get processes
* Filter where CPU > 100

---

# 🧪 6. Variables

```powershell
$name = "Luke Skywalker"
$name
```

Use in commands:

```powershell
$files = Get-ChildItem
$files.Count
```

---

# 🔁 7. Loops

```powershell
$numbers = 1..5

foreach ($n in $numbers) {
    "Number: $n"
}
```

---

# 🔎 8. Filtering (Super Useful)

```powershell
Get-Service | Where-Object Status -eq "Running"
```

---

# 🌐 9. Calling APIs (like your SWAPI example)

```powershell
Invoke-RestMethod "https://swapi.dev/api/people/1/"
```

---

# 🛠️ 10. Help System (Your Best Friend)

```powershell
Get-Help Get-Process
Get-Help Get-Process -Examples
```

---

# 🧭 Mental Model (Important)

Think of PowerShell like this:

| Concept         | Meaning          |
| --------------- | ---------------- |
| Cmdlet          | Small command    |
| Object          | Structured data  |
| Pipeline        | Connect commands |
| `Where-Object`  | Filter           |
| `Select-Object` | Pick fields      |

---

# 🧩 Mini Exercise (Try This)

```powershell
Get-Process |
Where-Object CPU -gt 10 |
Select-Object Name, CPU |
Sort-Object CPU -Descending
```

👉 You just:

1. Got processes
2. Filtered them
3. Selected properties
4. Sorted them

That’s already **real scripting thinking** 💪

---

# 🚀 What Next?

Since you're learning systematically (like your JavaScript bootcamp), a great next step would be:

👉 **PowerShell Week 1 Plan:**

* Day 1: Navigation + Help
* Day 2: Objects + Get-Member
* Day 3: Filtering + Pipeline
* Day 4: Variables
* Day 5: Loops
* Day 6: Files (create/delete/search)
* Day 7: Mini project (e.g., file cleaner)

---

If you want, I can turn this into a **structured 7-day PowerShell bootcamp (like your JavaScript one)** with exercises and mini-projects 👍

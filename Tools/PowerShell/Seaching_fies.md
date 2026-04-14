# 20260412180558 Seaching files using PowerShell

PowerShell is actually **very powerful for searching files**—much more flexible than Windows Explorer once you get used to it. Let me show you the essentials step by step.

***

# 🔎 1. Basic file search (by name)

The most important command is:

```powershell
Get-ChildItem
```

Alias: `gci` or `dir`

### 👉 Example: Find a file by name

```powershell
Get-ChildItem -Path C:\Projects -Filter *.txt
```

✔ Finds all `.txt` files in that folder

***

# 🔁 2. Search recursively (in subfolders)

```powershell
Get-ChildItem -Path C:\Projects -Filter *.txt -Recurse
```

✔ Searches **all subfolders**

***

# ⚡ 3. Faster search with `-Filter` (recommended)

```powershell
Get-ChildItem -Path C:\Projects -Filter report*.pdf -Recurse
```

✔ Much faster than `Where-Object`\
✔ Uses Windows filesystem filtering

***

# 🎯 4. Search using conditions (`Where-Object`)

If you need more control:

```powershell
Get-ChildItem -Path C:\Projects -Recurse | Where-Object {
    $_.Name -like "*report*"
}
```

✔ Slower, but very flexible

***

# 📏 5. Find files by size

### 👉 Files larger than 10 MB

```powershell
Get-ChildItem -Path C:\Projects -Recurse | Where-Object {
    $_.Length -gt 10MB
}
```

***

# 📅 6. Find files by date

### 👉 Modified in last 7 days

```powershell
Get-ChildItem -Path C:\Projects -Recurse | Where-Object {
    $_.LastWriteTime -gt (Get-Date).AddDays(-7)
}
```

***

# 🔍 7. Search inside files (content search)

Use `Select-String` (like `grep`):

```powershell
Select-String -Path "C:\Projects\*.txt" -Pattern "error"
```

### 👉 Recursive search inside files:

```powershell
Get-ChildItem -Path C:\Projects -Recurse -Filter *.log |
    Select-String -Pattern "ERROR"
```

✔ Finds text **inside files**

***

# 📄 8. Show only file paths (clean output)

```powershell
Get-ChildItem -Recurse -Filter *.txt | Select-Object -ExpandProperty FullName
```

***

# 🚫 9. Exclude folders or files

```powershell
Get-ChildItem -Path C:\Projects -Recurse -Exclude *.tmp
```

***

# ⚡ 10. Real-world example (very useful)

👉 Find all `.log` files larger than 5MB containing "ERROR":

```powershell
Get-ChildItem C:\Projects -Recurse -Filter *.log |
Where-Object { $_.Length -gt 5MB } |
Select-String "ERROR"
```

***

# 🧠 Quick mental model

* `Get-ChildItem` → finds files

* `-Recurse` → include subfolders

* `-Filter` → fast name filtering

* `Where-Object` → advanced filtering

* `Select-String` → search inside files

***

# 💡 Pro tip (Windows users)

If you need **super fast search across the whole disk**, you can also use:

```powershell
Get-ChildItem -Path C:\ -Filter *.txt -Recurse -ErrorAction SilentlyContinue
```

…but this can be slow. For huge searches, tools like _Everything_ (Voidtools) are insanely fast.

***

If you want, I can:

* build you a **custom PowerShell search function** (like your empty-file script)

* or create a **cheat sheet** you can store in your Zettelkasten 😊

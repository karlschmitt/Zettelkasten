# 20260414084737 How to query the Star Wars API

You can query the **Star Wars API (SWAPI)** very easily in PowerShell using built-in commands like `Invoke-RestMethod`. Here’s a clear, step-by-step guide 👇

***

# 🚀 1. Basic API Request in PowerShell

The Star Wars API endpoint is:

```
https://swapi.dev/api/
```

### Example: Get all people (characters)

```powershell
$response = Invoke-RestMethod -Uri "https://swapi.dev/api/people/"
$response
```

👉 `Invoke-RestMethod` automatically converts JSON into PowerShell objects.

***

# 🔍 2. Access Specific Data

The response contains properties like `results`, `count`, etc.

### Example: List character names

```powershell
$response.results | Select-Object name
```

### Example: Show name + height

```powershell
$response.results | Select-Object name, height
```

***

# 🎯 3. Query a Specific Character

Each character has an ID.

### Example: Luke Skywalker (ID = 1)

```powershell
$luke = Invoke-RestMethod -Uri "https://swapi.dev/api/people/1/"
$luke
```

***

# 🔎 4. Search for Characters

SWAPI supports search queries:

```powershell
$search = Invoke-RestMethod -Uri "https://swapi.dev/api/people/?search=skywalker"
$search.results | Select-Object name
```

***

# 🔁 5. Handle Pagination

SWAPI returns results in pages.

### Example: Loop through all pages

```powershell
$url = "https://swapi.dev/api/people/"

while ($url) {
    $response = Invoke-RestMethod -Uri $url
    $response.results | Select-Object name

    $url = $response.next
}
```

***

# 🧪 6. Explore Other Endpoints

You can query:

* People → `/people/`

* Planets → `/planets/`

* Starships → `/starships/`

* Films → `/films/`

### Example: Get all films

```powershell
$films = Invoke-RestMethod -Uri "https://swapi.dev/api/films/"
$films.results | Select-Object title, release_date
```

***

# ⚡ 7. Pretty Output (Optional)

Format results nicely:

```powershell
$response.results | Format-Table name, height
```

***

# 💡 Bonus Tip

If you want to inspect the structure:

```powershell
$response | Get-Member
```

***

# 🧠 Summary

* Use `Invoke-RestMethod` to call APIs

* JSON → automatically becomes PowerShell objects

* Use `Select-Object` to filter data

* Handle pagination with `.next`

***

If you want, I can show you a **mini PowerShell project** (like a Star Wars CLI tool) to practice this 👍

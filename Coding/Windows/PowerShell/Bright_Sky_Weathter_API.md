---
id: 20260906161133
title: Bright Sky Weather API
author: Karl Schmitt
date: 2026-09-06
keywords: [ PowerShell, API ]
---

# Invoking the Bright Sky Weather API for Königstein via PowerShell


To retrieve the current weather for _[Königstein im Taunus](https://www.google.com/search?kgmid=/m/08fnz3)_ using the free and open-source [Bright Sky API](https://brightsky.dev/), you can use the `Invoke-RestMethod` cmdlet in PowerShell. \[1]

Because the Bright Sky API queries data based on geographic coordinates rather than location names, the request uses the coordinates for Königstein im Taunus: Latitude 50.1832 and Longitude 8.4636. \[2, 3]

## PowerShell Script

Copy and run the following script in your PowerShell console:
```powershell
# Define coordinates for Königstein im Taunus
$lat = "50.1832"
$lon = "8.4636"

# Construct the Bright Sky API endpoint
$uri = "https://brightsky.dev"

try {
    # Invoke the API and automatically parse the JSON response
    $response = Invoke-RestMethod -Uri $uri -Method Get

    # Extract weather and source info
    $weather = $response.weather
    $source  = $response.sources

    # Display the current weather summary
    Write-Host "Current Weather for Königstein im Taunus (via DWD / Bright Sky):" -ForegroundColor Cyan
    Write-Host "---------------------------------------------------------------"
    [PSCustomObject]@{
        "Station Name"   = $source.station_name
        "Condition"      = $weather.condition
        "Temperature"    = "$($weather.temperature) °C"
        "Relative Humid" = "$($weather.relative_humidity) %"
        "Wind Speed"     = "$($weather.wind_speed) km/h"
        "Precipitation"  = "$($weather.precipitation) mm"
        "Timestamp"      = $weather.timestamp
    } | Format-List
}
catch {
    Write-Error "Failed to fetch weather data: $_"
}
```

## Why this approach works:

* No Authentication Required: The [Bright Sky API documentation](https://brightsky.dev/docs/) states that the public instance does not require an API key.
* Automatic JSON Parsing: `Invoke-RestMethod` natively turns the JSON payload returned by Bright Sky into a structured PowerShell object, allowing you to access fields like `$response.weather.temperature` directly. 

Would you like help modifying this script to log the data to a CSV file or set up an automated alert for specific weather conditions?

> [NOTE!]
>  Feel free to visit the Bright Sky website: [https://brightsky.dev](https://brightsky.dev/docs/)

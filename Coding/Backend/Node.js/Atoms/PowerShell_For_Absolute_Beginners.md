---
id: 20260911194806
---

PowerShell is a command-line shell and scripting language created by Microsoft to automate tasks and manage system configurations. Unlike traditional command prompts that process text, PowerShell processes **objects**, making it vastly more flexible.



Here is a step-by-step tutorial to take you from opening PowerShell for the first time to writing your first script.



## 1. Opening PowerShell

1. Press the **Windows Key**.


2. Type **PowerShell**.


3. Right-click **Windows PowerShell** (or **PowerShell**) and choose **Run as administrator**. _(Admin mode gives you permission to make changes to your system)._



## 2. Core Concept: Commands (Cmdlets)

PowerShell commands are called **Cmdlets** (pronounced _command-lets_). They follow a strict `Verb-Noun` naming structure:



* **Verb:** Action to take (`Get`, `Set`, `New`, `Remove`, `Start`, `Stop`)


* **Noun:** Target item (`Process`, `Service`, `Item`, `Content`)



### Three Discovery Commands Every Beginner Must Know

| **Command**   | **Purpose**                                 | **Example**                 |
| ------------- | ------------------------------------------- | --------------------------- |
| `Get-Command` | Find any command available                  | `Get-Command -Noun Process` |
| `Get-Help`    | Learn how to use a specific command         | `Get-Help Get-Service`      |
| `Get-Member`  | Discover what properties/data an object has | `Get-Process \| Get-Member` |

> **Pro Tip:** Press `Tab` on your keyboard to auto-complete commands and file paths!
>
>

## 3. Essential Everyday Commands

Try entering these commands in your console one by one:



PowerShell

```
# List files and folders in your current directory
Get-ChildItem

# Print your current working folder location
Get-Location

# Get a list of running programs/processes
Get-Process

# Get a list of running background services
Get-Service
```

## 4. The Power of the Pipeline (`|`)

The pipe operator (`|`) takes the output of the command on the left and passes it directly as input to the command on the right.



PowerShell

```
# Get all running processes, but sort them by CPU usage
Get-Process | Sort-Object CPU -Descending

# Get all services and filter to show ONLY running ones
Get-Service | Where-Object Status -eq 'Running'

# Get all files in a folder and export the list into a CSV file
Get-ChildItem | Export-Csv -Path "C:\temp\filelist.csv" -NoTypeInformation
```

## 5. Variables and Basic Logic

In PowerShell, variables always begin with a dollar sign (`$`).



PowerShell

```
# 1. Storing text in a variable
$greeting = "Hello, PowerShell!"
Write-Host $greeting

# 2. Storing objects in a variable
$runningServices = Get-Service | Where-Object Status -eq 'Running'
$runningServices.Count

# 3. Simple IF Statement
$cpuUsage = 85

if ($cpuUsage -gt 80) {
    Write-Host "Warning: CPU usage is high!" -ForegroundColor Red
} else {
    Write-Host "CPU usage is normal." -ForegroundColor Green
}
```

## 6. Writing and Running Your First Script (.ps1)

PowerShell scripts are saved with the `.ps1` extension.



### Step A: Enable Script Execution

By default, Windows blocks custom scripts from running for security. To allow your own scripts to run safely, run this once in PowerShell as Administrator:



PowerShell

```
Set-ExecutionPolicy RemoteSigned
```

### Step B: Create the Script

1. Open **Notepad**.


2. Paste the following script:



PowerShell

```
# System Information Report
$computer = $env:COMPUTERNAME
$date = Get-Date -Format "yyyy-MM-dd HH:mm"

Write-Host "=== System Report for $computer ===" -ForegroundColor Cyan
Write-Host "Generated on: $date"

$stoppedServices = (Get-Service | Where-Object Status -eq 'Stopped').Count
Write-Host "Total stopped services: $stoppedServices" -ForegroundColor Yellow
```

3. Save the file on your Desktop as `SystemReport.ps1` (select _All Files (_._)_ in Notepad so it doesn't save as a `.txt`).



### Step C: Execute the Script

Back in your PowerShell window, navigate to your desktop and run it:

PowerShell

```
Set-Location -Path "$home\Desktop"
.\SystemReport.ps1
```

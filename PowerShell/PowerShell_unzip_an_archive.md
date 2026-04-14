# 20260414160032 Unzip an archive

The standard way to unzip files in PowerShell is using the **`Expand-Archive`** cmdlet.

Here is how to use it in various scenarios:

### 1. Basic Unzip
To extract a zip file to a specific folder:
```powershell
Expand-Archive -Path "C:\Files\Archive.zip" -DestinationPath "C:\Extracted"
```

### 2. Overwrite Existing Files
By default, if the files already exist in the destination, PowerShell will throw an error. Use the `-Force` parameter to overwrite them:
```powershell
Expand-Archive -Path "Archive.zip" -DestinationPath "C:\Extracted" -Force
```

### 3. Unzip All Zip Files in a Folder
If you have a folder full of `.zip` files and want to extract them all at once:
```powershell
Get-ChildItem *.zip | ForEach-Object {
    Expand-Archive -Path $_.FullName -DestinationPath "C:\Extracted\$($_.BaseName)"
}
```
*This script creates a separate sub-folder for each zip file based on its name.*

---

### Important Notes:
*   **Zip only:** `Expand-Archive` natively supports `.zip` files. It does **not** support `.rar`, `.7z`, or `.tar.gz`. For those, you would still need a tool like 7-Zip or WinRAR (or use the `tar` command in modern Windows).
*   **PowerShell Version:** This command requires PowerShell 5.0 or higher (which is standard on Windows 10 and 11).

---

### Bonus: How to Zip files (Compress)
If you need to do the opposite and create a zip file, use **`Compress-Archive`**:

**Zip a single file:**
```powershell
Compress-Archive -Path "C:\Logs\app.log" -DestinationPath "C:\Backup\Logs.zip"
```

**Zip an entire folder:**
```powershell
Compress-Archive -Path "C:\Project\*" -DestinationPath "C:\Backup\Project.zip"
```

**Add a file to an existing zip:**
```powershell
Compress-Archive -Path "C:\NewFile.txt" -Update -DestinationPath "C:\Backup\Project.zip"
```
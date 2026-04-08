


# 20260408191823 How can I substiude curl with PowerShell?

In PowerShell, there are two primary commands (cmdlets) used to replace `curl`:

1.  **`Invoke-WebRequest` (iwr):** Best for downloading files or scraping HTML. It returns the full HTTP response (headers, status codes, etc.).
2.  **`Invoke-RestMethod` (irm):** Best for APIs. It automatically parses JSON or XML responses into PowerShell objects.

### 1. Basic GET Request
In PowerShell, the alias `curl` actually points to `Invoke-WebRequest`, but the syntax is different.

*   **curl:** `curl https://api.example.com/data`
*   **PowerShell:** 
    ```powershell
    Invoke-RestMethod -Uri "https://api.example.com/data"
    ```

### 2. POST Request with Data
*   **curl:** `curl -X POST -d "param1=value1&param2=value2" https://api.example.com/post`
*   **PowerShell:**
    ```powershell
    $body = @{
        param1 = "value1"
        param2 = "value2"
    }
    Invoke-RestMethod -Method Post -Uri "https://api.example.com/post" -Body $body
    ```
    *Note: PowerShell automatically converts the hashtable `@{} ` to form-encoded or JSON data depending on the Content-Type.*

### 3. Sending JSON Data
*   **curl:** `curl -H "Content-Type: application/json" -d '{"name":"John"}' https://api.example.com/user`
*   **PowerShell:**
    ```powershell
    $body = @{ name = "John" } | ConvertTo-Json
    Invoke-RestMethod -Method Post -Uri "https://api.example.com/user" -Body $body -ContentType "application/json"
    ```

### 4. Custom Headers (e.g., API Keys)
*   **curl:** `curl -H "Authorization: Bearer 12345" https://api.example.com/secure`
*   **PowerShell:**
    ```powershell
    $headers = @{
        Authorization = "Bearer 12345"
        "X-Custom-Header" = "Value"
    }
    Invoke-RestMethod -Uri "https://api.example.com/secure" -Headers $headers
    ```

### 5. Downloading a File
*   **curl:** `curl -o image.png https://example.com/image.png`
*   **PowerShell:**
    ```powershell
    Invoke-WebRequest -Uri "https://example.com/image.png" -OutFile "image.png"
    ```

### 6. Following Redirects
*   **curl:** `curl -L https://example.com`
*   **PowerShell:** PowerShell follows redirects by default. To limit them:
    ```powershell
    Invoke-WebRequest -Uri "https://example.com" -MaximumRedirection 5
    ```

---

### Comparison Table

| Feature | curl (Original) | PowerShell Equivalent |
| :--- | :--- | :--- |
| **Simple GET** | `curl [URL]` | `irm [URL]` |
| **Output to file** | `-o [file]` | `-OutFile [file]` |
| **Headers** | `-H "Name: Value"` | `-Headers @{Name="Value"}` |
| **Method** | `-X POST` | `-Method Post` |
| **Request Body** | `-d "data"` | `-Body "data"` |
| **Basic Auth** | `-u user:pass` | `-Credential (Get-Credential)` |
| **Ignore SSL Errors** | `-k` or `--insecure` | `-SkipCertificateCheck` (PS 6.0+) |

### A Note on "curl" in Windows
If you are on Windows 10 (build 1803) or later, **`curl.exe` is actually pre-installed**. 

If you type `curl` in PowerShell, it might run the PowerShell alias (which will fail if you use standard curl flags). To use the **real** curl inside PowerShell, type:
```powershell
curl.exe -X POST https://example.com
```
*(By adding `.exe`, you tell PowerShell to ignore its internal alias and run the actual curl binary.)*


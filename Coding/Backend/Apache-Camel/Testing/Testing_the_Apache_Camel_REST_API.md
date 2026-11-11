---
id: 20261016192340
title: Testing Spring Boot Apache Camel REST APIs with PowerShell
author: Karl Schmitt
date: 2026-10-16
---

# Testing Spring Boot Apache Camel REST APIs with PowerShell

To test your Apache Camel REST DSL application running on Spring Boot, you can use PowerShell's built-in `Invoke-RestMethod` (or its alias `irm`) or `Invoke-WebRequest` (alias `iwr`).

Assuming your application is running locally on the default port **8080**, choose the command block below that matches the HTTP method of your endpoint.


### 1. Test a `GET` Request (Fetch Data or Items)

If your REST DSL exposes a resource like `/api/users` or `/api/products`:

![PowerShell](../Images/PowerShell_Logo.png)
```PowerShell
Invoke-RestMethod -Uri "http://localhost:8080/api/users" -Method Get
```
* **Tip:** `Invoke-RestMethod` automatically parses JSON responses into PowerShell custom objects so you can immediately see properties or pipe them (e.g., `... | Select-Object name`).


### 2. Test a `POST` Request (Create a Resource)

If your REST DSL accepts JSON payloads (e.g., creating a new user or item):

![PowerShell](../Images/PowerShell_Logo.png)
```PowerShell
\$body = @{
    name  = "John Doe"
    email = "john.doe@example.com"
} | ConvertTo-Json

Invoke-RestMethod -Uri "http://localhost:8080/api/users" `
    -Method Post `
    -Body \$body `
    -ContentType "application/json"
```

### 3. Test a `PUT` Request (Update a Resource)

To update an existing record by ID:

![PowerShell](../Images/PowerShell_Logo.png)
```PowerShell
$body = @{
    name = "Johnathan Doe"
} | ConvertTo-Json

Invoke-RestMethod -Uri "http://localhost:8080/api/users/1" `
    -Method Put `
    -Body $body `
    -ContentType "application/json"
```

### 4. Test a `DELETE` Request (Remove a Resource)

To delete a resource:

![PowerShell](../Images/PowerShell_Logo.png)
```PowerShell
Invoke-RestMethod -Uri "http://localhost:8080/api/users/1" -Method Delete
```

### Inspecting Headers and Status Codes

If you need to inspect HTTP status codes, response headers, or error details (rather than just the parsed body), swap `Invoke-RestMethod` for **`Invoke-WebRequest`**:

![PowerShell](../Images/PowerShell_Logo.png)
```PowerShell
$response = Invoke-WebRequest -Uri "http://localhost:8080/api/users" -Method Get

# View the HTTP Status Code (e.g., 200, 201, 404)
$response.StatusCode

# View the raw JSON content text
$response.Content
```

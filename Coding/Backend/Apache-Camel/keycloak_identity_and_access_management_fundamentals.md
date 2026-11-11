---
id: 20261016204604
title: Keycloak Identity and Access Management (IAM) Absolute Beginner Deep Dive
date: 2026-10-16
---

# Keycloak Identity and Access Management (IAM) Absolute Beginner Deep Dive

## 1. What is Keycloak and Why Use It?

**Keycloak** is an open-source **Identity and Access Management (IAM)** solution maintained by Red Hat. It provides out-of-the-box features for user authentication, authorization, single sign-on (SSO), and identity brokering.

Instead of building custom login screens, user databases, password reset flows, and token generation logic into every microservice, you delegate these tasks to Keycloak.

### Key Features
* **Single Sign-On (SSO) & Single Sign-Out**: Authenticate once to access multiple interconnected applications.
* **Standard Protocols**: Supports **OpenID Connect (OIDC)** and **SAML 2.0**.
* **Identity Brokering & Social Login**: Allow users to log in with Google, GitHub, or enterprise LDAP / Active Directory servers.
* **User Federation**: Sync users from external databases or directories.
* **Fine-Grained Authorization**: Manage roles, groups, and permissions centrally.

---

## 2. Core Concepts & Architecture

Understanding Keycloak’s hierarchy is essential for configuring applications:

```
[ Keycloak Instance ]
       │
       ├── [ Realm: Master ] (Admin only)
       │
       └── [ Realm: Enterprise-App ] (Custom isolated domain)
              │
              ├── [ Clients ] (Web Apps, APIs, Mobile Apps)
              ├── [ Roles ]   (ADMIN, USER, MANAGER)
              ├── [ Users ]   (Alice, Bob)
              └── [ Groups ]  (Engineering, Finance)
```

### Core Terminology
1. **Realm**: A logical space/container that manages a set of users, credentials, roles, and clients. The default realm is `Master` (used for Keycloak administration). **Rule of thumb**: Create a separate realm for your applications.
2. **Client**: An entity (application, microservice, or website) that requests Keycloak to authenticate a user or deliver tokens.
3. **User**: The individual end-user logging into the system.
4. **Roles**: Labels assigned to users or clients to define permissions (e.g., `ROLE_ADMIN`, `ROLE_USER`).
   * **Realm Roles**: Global across the entire realm.
   * **Client Roles**: Specific only to a single client application.
5. **Client Scopes**: Definitions that dictate which claims/information (e.g., `email`, `profile`) are included in issued tokens.

---

## 3. Running Keycloak Locally (Docker)

The fastest way to start Keycloak locally is via Docker/Podman using the official container image.

```bash
docker run -d --name keycloak \
  -p 8081:8080 \
  -e KEYCLOAK_ADMIN=admin \
  -e KEYCLOAK_ADMIN_PASSWORD=admin \
  quay.io/keycloak/keycloak:latest start-dev
```

* **Admin Console URL**: `http://localhost:8081`
* **Admin Credentials**: `admin` / `admin`

---

## 4. Hands-On Walkthrough: Step-by-Step Configuration

### Step 1: Create a Custom Realm
1. Log into the Keycloak Admin Console at `http://localhost:8081`.
2. Click the dropdown menu at the top-left (currently `master`).
3. Click **Create Realm**.
4. Set **Realm name** to `my-app-realm` and click **Create**.

---

### Step 2: Create Realm Roles
1. In the left sidebar, navigate to **Realm Roles**.
2. Click **Create Role**.
3. Set **Role Name** to `APP_USER` and click **Save**.
4. Repeat to create a second role named `APP_ADMIN`.

---

### Step 3: Create a New Client (OIDC)
To secure a web application or REST API (like Spring Boot or Apache Camel), register it as a Client:

1. Click **Clients** in the left sidebar $\rightarrow$ **Create client**.
2. **General Configuration**:
   * **Client type**: `OpenID Connect`
   * **Client ID**: `my-service-client`
3. **Capability Config**:
   * Enable **Client authentication** (turns on `Client Credentials Grant` for machine-to-machine APIs).
   * Ensure **Standard flow** (Authorization Code Grant for user logins) is enabled.
4. **Login Settings**:
   * **Valid redirect URIs**: `http://localhost:8080/*`
   * **Web origins**: `http://localhost:8080`
5. Click **Save**.

> **Where to find the Client Secret**: Navigate to the **Credentials** tab of your new client to copy the generated `Client Secret`.

---

### Step 4: Create a User and Assign Roles
1. Go to **Users** $\rightarrow$ **Add user**.
2. Enter **Username**: `alice`.
3. Set **Email**: `alice@example.com`, mark **Email verified** as `Yes`.
4. Click **Create**.
5. Go to the **Credentials** tab:
   * Click **Set password**.
   * Enter a password (e.g., `password123`).
   * Toggle **Temporary** to `Off` (so it won't force a password change on first login).
6. Go to the **Role mapping** tab:
   * Click **Assign role**.
   * Select `APP_USER` and click **Assign**.

---

## 5. Testing OpenID Connect Flows with PowerShell

Now that Keycloak is configured, let's request tokens using PowerShell.

### Flow 1: Machine-to-Machine (Client Credentials Flow)
Used when a service or script needs to call an API directly without user interaction.

```powershell
# Parameters
$tokenUrl = "http://localhost:8081/realms/my-app-realm/protocol/openid-connect/token"
$body = @{
    grant_type    = "client_credentials"
    client_id     = "my-service-client"
    client_secret = "YOUR_CLIENT_SECRET_HERE" # Replace with secret from Credentials tab
}

# Send Token Request
$response = Invoke-RestMethod -Uri $tokenUrl -Method Post -Body $body

# Inspect Output
Write-Host "Access Token:" $response.access_token
Write-Host "Token Type:" $response.token_type
Write-Host "Expires In (seconds):" $response.expires_in
```

---

### Flow 2: User Login (Resource Owner Password Credentials / Direct Grant)
Used to simulate a user logging in with a username and password:

```powershell
# Parameters
$tokenUrl = "http://localhost:8081/realms/my-app-realm/protocol/openid-connect/token"
$body = @{
    grant_type    = "password"
    client_id     = "my-service-client"
    client_secret = "YOUR_CLIENT_SECRET_HERE"
    username      = "alice"
    password      = "password123"
    scope         = "openid"
}

# Request Token for User
$userToken = Invoke-RestMethod -Uri $tokenUrl -Method Post -Body $body

# Inspect Tokens
$accessToken  = $userToken.access_token
$idToken      = $userToken.id_token
$refreshToken = $userToken.refresh_token

Write-Host "User Access Token acquired successfully!"
```

---

## 6. Inspecting the JWT Payload

Keycloak issues standard **JSON Web Tokens (JWT)**. You can decode the payload string (the second part of the dot-separated JWT) to see claims and assigned roles.

### Decoding Base64 in PowerShell
```powershell
# Split token parts
$payloadBase64 = $accessToken.Split(".")[1]

# Pad base64 string if necessary
while ($payloadBase64.Length % 4 -ne 0) { $payloadBase64 += "=" }

# Convert from Base64 to UTF8 String
$jsonBytes = [System.Convert]::FromBase64String($payloadBase64)
$jsonString = [System.Text.Encoding]::UTF8.GetString($jsonBytes)

# Convert to PowerShell Object
$claims = $jsonString | ConvertFrom-Json
$claims | Format-List
```

### Key Claims inside the Keycloak JWT
* **`iss` (Issuer)**: `http://localhost:8081/realms/my-app-realm`
* **`sub` (Subject)**: Unique User UUID in Keycloak.
* **`preferred_username`**: `alice`
* **`realm_access.roles`**: Contains `["APP_USER"]`.

---

## 7. Summary & Key Zettelkasten Concepts

To link this note across your knowledge base:

* **[[OAuth2 and JWT Security in Apache Camel with Spring Boot 4.1 & Java 25]]**: Use this Keycloak instance as the Issuer for securing your Spring Boot/Camel REST routes.
* **[[OAuth2 Architecture]]**: Keycloak acts as the **Authorization Server / Identity Provider (IdP)**.
* **[[OpenID Connect (OIDC)]]**: An identity layer on top of OAuth 2.0 that provides the `id_token` for user identification.
* **[[JWT Claims & Validation]]**: Resource Servers validate incoming tokens against Keycloak's JWKS endpoint (`/protocol/openid-connect/certs`).

---

## Related Notes
* [[202610162019-camel-oauth2-jwt-security]]
* [[202610161947 - REST API Fundamentals: Deep Dive with Star Wars & Weather APIs]]
* [[PowerShell Invoke-RestMethod Cheat Sheet]]
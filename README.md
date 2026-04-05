# Metaprojekt Zettelkasten

The Metaproject **Zettelkasten** collects all the information dicovered for learning **React** and **Angular**. 

The Project **React Bootcamp** collects and documents the information for the React ecosystem.



The Project **Angular Bootcamp** collects and documents the information for the Angular framework. 

## Teilprojekt React Bootcamp

To interact with GitHub or GitLab you need to exchange a SSH key.

### SSH-Key Configuration using GitBash for GitHub

To push code to GitHub securely, you typically create an **SSH key** and add it to your GitHub account. This avoids typing your username/password every time.

Here’s the clean, modern way to do it:

---

## 🔑 1. Generate an SSH key

Open your terminal and run:

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

👉 If your system doesn’t support `ed25519`, use:

```bash
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```

When prompted:

- Press **Enter** to accept the default file location

- Optionally set a **passphrase** (recommended)

---

## 📂 2. Start the SSH agent

```bash
eval "$(ssh-agent -s)"
```

Add your key:

```bash
ssh-add ~/.ssh/id_ed25519
```

---

## 📋 3. Copy your public key

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the full output (it starts with `ssh-ed25519`).

---

## 🌐 4. Add the key to GitHub

1. Go to GitHub

2. Click your profile → **Settings**
   
   1. Important follow the white rabbit: https://github.com/settings/keys

3. Go to **SSH and GPG keys**

4. Click **New SSH key**

5. Paste your key and give it a name (e.g. *My Laptop*)

---

## 🔌 5. Test the connection

```bash
ssh -T git@github.com
```

You should see:

```
Hi <username>! You've successfully authenticated...
```

---

## 🚀 6. Use SSH for your repo

When cloning a repo, use the SSH URL:

```bash
git clone git@github.com:username/repository.git
```

If your repo already exists locally, switch it:

```bash
git remote set-url origin git@github.com:username/repository.git
```

---

## ✅ Done!

Now you can push:

```bash
git push
```

### Reusing the GithBash SSH configuration for PowerShell

Here is the step-by-step guide to setting it up using PowerShell.

### Step 1: Open PowerShell as Administrator
To manage Windows services (like the SSH agent), you must run PowerShell as an Administrator.
1. Right-click your **Start button**.
2. Select **Terminal (Admin)** or **Windows PowerShell (Admin)**.

---

### Step 2: Enable and Start the SSH Agent Service
By default, the SSH agent service is present but disabled. Run these commands to set it to start automatically and turn it on now:

```powershell
# Set the service to start automatically when Windows boots
Set-Service -Name ssh-agent -StartupType Automatic

# Start the service right now
Start-Service ssh-agent

# Verify that it is running (Status should say "Running")
Get-Service ssh-agent
```

---

### Step 3: Add your SSH Key to the Agent
Now that the "manager" (the agent) is running, you need to give it your "ID card" (your private key).

*Note: If you used a different name for your key, replace `id_ed25519` with your filename.*

```powershell
ssh-add $HOME\.ssh\id_ed25519
```
*If your key has a passphrase, you will be asked to enter it one last time here.*

---

### Step 4: Test the Connection to GitHub
Run this command to make sure GitHub recognizes you through PowerShell:

```powershell
ssh -T git@github.com
```
If successful, you will see: *"Hi [YourUsername]! You've successfully authenticated, but GitHub does not provide shell access."*

---

### Step 5: (Optional) Make it work automatically in every Terminal
Sometimes PowerShell doesn't "remember" the agent environment variables across different sessions. To ensure your keys are always ready, you can add a small line to your PowerShell Profile.

1. **Check if you have a profile:**
   ```powershell
   if (!(Test-Path -Path $PROFILE)) { New-Item -ItemType File -Path $PROFILE -Force }
   notepad $PROFILE
   ```

2. **Paste this at the bottom of the Notepad file that opens, then save and close it:**
   ```powershell
   # Ensure the ssh-agent is running and keys are loaded
   if ((Get-Service ssh-agent).Status -ne 'Running') {
       Start-Service ssh-agent
   }
   ```

---

### Troubleshooting Common Issues

*   **"Permission Denied" on GitHub:** Make sure you have added your **public** key (`id_ed25519.pub`) to your GitHub account settings under "SSH and GPG keys".
*   **Git is still asking for a password:** Ensure Git is configured to use the Windows OpenSSH client rather than its built-in one. Run this command:
    ```powershell
    git config --global core.sshCommand C:/Windows/System32/OpenSSH/ssh.exe
    ```

Now you can use `git push` and `git pull` in PowerShell just like you do in Git Bash! Let me know if you run into any errors.


### Zettelkasten

Zettekasten is a nethod and system for collecting information.

### HTTP

### HTML

### CSS

### Tailwind

### JavaScript

### TypeScript

### React

### React Hooks

### React Router

### Material-UI



## Teilprojekt Angular Bootcamp

## Teilproject Spring Boot Backend

## Teilproject Persistency

### PostgreSQL

### PostgresML

### MongoDB

### GraphQL

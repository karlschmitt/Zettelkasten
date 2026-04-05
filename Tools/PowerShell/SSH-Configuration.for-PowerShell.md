# 20260405170258 SSH configuration for PowerShell


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

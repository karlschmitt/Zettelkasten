---
id: 20260826130043
title: Docker step by step
author: Karl Schmitt
date: 2026-08-26
---

# Docker step by step

Since you are already using **Ubuntu via WSL2** (from the previous K3s step), installing Docker directly inside that same Ubuntu environment is the most efficient way to work. 

This guide installs **Docker Engine**, which is the "pure" Linux way. 
It is lighter and faster than installing the heavy "Docker Desktop" application for Windows.

> [NOTE!]
> You can install Ubuntu on Windows 11 with a single command: _**open PowerShell as an Administrator and run `wsl --install`**_. This automatically enables the [Windows Subsystem for Linux (WSL)](https://learn.microsoft.com/en-us/windows/wsl/install) framework and downloads the latest default **Ubuntu** distribution. \[[1](https://pureinfotech.com/install-wsl-windows-11/), [2](https://learn.microsoft.com/en-us/windows/wsl/install)]

## 🚀 Step-by-Step Installation

### Step 1: Open PowerShell as Administrator

1. Click the Windows **Start Menu**.
2. Search for **PowerShell** or **Command Prompt**.
3. Right-click the app and choose **Run as administrator**. \[[1](https://dev.to/devsubha/how-to-install-ubuntu-on-windows-step-by-step-guide-for-beginners-2hjn), [2](https://pureinfotech.com/install-wsl-windows-11/), [3](https://learn.microsoft.com/en-us/windows/wsl/install)]

### Step 2: Run the Install Command

Type the following command into the console window and press **Enter**: \[[1](https://learn.microsoft.com/en-us/windows/wsl/install)]

PowerShell:
```
wsl --install
```
Use code with caution.

_Note: If you already have WSL active and just want a clean or specific Ubuntu edition, run `wsl --install -d Ubuntu` instead._

### Step 3: Reboot Your Computer

1. Wait for the command line to show a success message.
2. **Restart** your PC to apply the virtual machine platform features. \[[1](https://www.youtube.com/watch?v=HrAsmXy1-78), [2](https://learn.microsoft.com/en-us/windows/wsl/install), [3](https://ubuntu.com/wsl/docs/stable/howto/install-ubuntu-wsl2/)]

Step 4: Complete the Linux Configuration

1. After rebooting, an Ubuntu terminal window will open automatically.
2. Wait a minute for the initial setup to unzip files.
3. Enter a **new UNIX username** when prompted.
4. Enter and confirm a **new password**. _(The password will not show on screen as you type it)_

---

### Step 4: Prepare Ubuntu

Open your **Ubuntu terminal** and update your package lists to make sure everything is current.

```bash
sudo apt update && sudo apt upgrade -y
```

### Step 5: Install Required Tools

Install a few basic packages that allow Ubuntu to use repositories over HTTPS.

```bash
sudo apt install -y ca-certificates curl gnupg lsb-release
```

### Step 6: Add Docker’s Official GPG Key
This ensures that the software you download is authentic.

```bash
sudo install -m 0755 -d /etc/apt/keyrings
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
sudo chmod a+r /etc/apt/keyrings/docker.gpg
```

### Step 7: Add the Docker Repository
Run this command to tell Ubuntu where to find the Docker installation files.

```bash
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

### Step 8: Install Docker Engine
Now, update your index again and install the actual Docker components.

```bash
sudo apt update
sudo apt install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

---

### Step 9: Fix Permissions (The most important step!)
By default, Docker requires `sudo`. To run docker commands as a normal user (so you can just type `docker run...` instead of `sudo docker run...`), do this:

1. Create the docker group (usually already exists):
   ```bash
   sudo groupadd docker
   ```
2. Add your user to the group:
   ```bash
   sudo usermod -aG docker $USER
   ```
3. **Crucial:** You must close your Ubuntu terminal and reopen it (or run `wsl --shutdown` in PowerShell) for this change to take effect.

---

### Step 10: Verify the Installation
Open a new Ubuntu terminal and run:

```bash
docker run hello-world
```

If you see a message saying **"Hello from Docker!"**, congratulations! Docker is correctly installed and running inside your virtual Ubuntu.

---

### Managing Docker on WSL2
Since we enabled `systemd` in the previous K3s guide, Docker will start automatically when you open Ubuntu. Here are the commands to manage it:

*   **Check if Docker is running:** `systemctl status docker`
*   **Restart Docker:** `sudo systemctl restart docker`
*   **Stop Docker:** `sudo systemctl stop docker`

### A Note on K3s vs Docker
If you followed the previous guide and installed **K3s**, you now have two different container tools:
1.  **Docker:** Best for building images and local development.
2.  **K3s (Kubernetes):** Best for practicing orchestration and deployment.

**They can coexist perfectly fine!** K3s uses its own internal "containerd" to run pods, so it won't interfere with your Docker images or containers. You now have a professional-grade development environment right on your Windows 11 machine.
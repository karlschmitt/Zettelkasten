---
id: 20260826124754
title: K3s step by step
author: Karl Schmitt
date: 2026-08-26
---

# K3s step by step

Installing **K3s** (a lightweight Kubernetes) on Windows 11 using **WSL2 (Windows Subsystem for Linux)** with **Ubuntu** is the most efficient and popular way to do it. It is much faster and uses fewer resources than a traditional VirtualBox or VMware VM.

Here is the step-by-step guide to getting it running.

### Step 1: Install WSL2 and Ubuntu
If you don't have WSL2 installed yet:
1. Open **PowerShell** as Administrator.
2. Run the following command:
   ```powershell
   wsl --install -d Ubuntu
   ```
3. **Restart your computer** when prompted.
4. After restarting, a console will open to finish the Ubuntu setup. Create your **username** and **password**.

---

### Step 2: Enable Systemd in Ubuntu
K3s requires `systemd` to manage services, but WSL2 disables it by default.
1. Inside your Ubuntu terminal, create/edit the WSL configuration file:
   ```bash
   sudo nano /etc/wsl.conf
   ```
2. Paste the following into the file:
   ```ini
   [boot]
   systemd=true
   ```
3. Save and exit (`Ctrl+O`, `Enter`, then `Ctrl+X`).
4. **Important:** You must restart WSL for this to take effect. Back in **PowerShell**, run:
   ```powershell
   wsl --shutdown
   ```
5. Re-open your **Ubuntu** terminal.

---

### Step 3: Install K3s
Now we will install K3s. We will add a flag to ensure the "Kubeconfig" file is readable so you can run commands without typing `sudo` every time.

1. In the Ubuntu terminal, run:
   ```bash
   curl -sfL https://get.k3s.io | sh -s - --write-kubeconfig-mode 644
   ```
2. Wait for the installation to finish. It usually takes less than a minute.

---

### Step 4: Verify the Installation
Check if Kubernetes is running:
1. Run this command to see your node:
   ```bash
   kubectl get nodes
   ```
   *You should see `ubuntu` (or your machine name) with a status of **Ready**.*

2. Check the running pods (system components):
   ```bash
   kubectl get pods -A
   ```

---

### Step 5: (Optional) Access Kubernetes from Windows
It is much nicer to run `kubectl` commands directly from your Windows PowerShell rather than jumping into Ubuntu.

1. **Install kubectl on Windows:**
   - Download the [latest release](https://dl.k8s.io/release/v1.28.0/bin/windows/amd64/kubectl.exe).
   - Or, if you have **Chocolatey**, run: `choco install kubernetes-cli`.
2. **Copy the Config:**
   In Windows PowerShell, run these commands to copy the configuration from Ubuntu to your Windows user folder:
   ```powershell
   mkdir $HOME\.kube
   wsl cat /etc/rancher/k3s/k3s.yaml > $HOME\.kube\config
   ```
3. **Edit the Config:**
   Open `$HOME\.kube\config` in Notepad. Look for the line:
   `server: https://127.0.0.1:6443`
   (Note: If it says `0.0.0.0`, it will still work via localhost).
4. **Test it:**
   In **Windows PowerShell**, type:
   ```powershell
   kubectl get nodes
   ```

---

### Summary of useful K3s commands inside Ubuntu:
*   **Stop K3s:** `sudo systemctl stop k3s`
*   **Start K3s:** `sudo systemctl start k3s`
*   **Uninstall K3s:** `/usr/local/bin/k3s-uninstall.sh`

### Why choose K3s for this?
*   **Low Memory:** It uses about 512MB of RAM, whereas standard Kubernetes (K8s) or Minikube often requires 2GB+.
*   **Fast:** It boots in seconds.
*   **Real World:** Unlike some desktop "learning" versions, K3s is a production-grade binary used in edge computing and small-scale production environments.
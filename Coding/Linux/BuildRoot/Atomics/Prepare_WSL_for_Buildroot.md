---
id: 20260930225325
title: Prepare WSL for Buildroot
author: Karl Schmitt
---

# Prepare WSL for Buildroot


Absolutely. 😊 We'll do this **one milestone at a time** and verify each step before moving on.

## Step 1 — Prepare WSL for Buildroot

Our first goal is deliberately small:

```text
Windows 11
   │
   ▼
WSL2
   │
   ▼
Ubuntu
   │
   ▼
Buildroot source
```

We are **not** touching Wayland, Sway, Docker, VNC, Node.js, or Electron yet.

### 1. Check WSL

Open **PowerShell** and run:

```powershell
wsl --status
```

Then:

```powershell
wsl --version
```

And:

```powershell
wsl -l -v
```

You should ideally see an Ubuntu distribution with:

```text
VERSION
2
```

For example:

```text
  NAME      STATE    VERSION
* Ubuntu    Running  2
```

### 2. Enter Ubuntu

From PowerShell:

```powershell
wsl
```

Then verify:

```bash
uname -a
```

and:

```bash
cat /etc/os-release
```

We're looking for something along the lines of:

```text
Ubuntu
```

and:

```text
Linux ... x86_64 ...
```

### 3. Update Ubuntu

Inside WSL:

```bash
sudo apt update
```

Then:

```bash
sudo apt upgrade -y
```

### 4. Install Buildroot prerequisites

Still inside Ubuntu:

```bash
sudo apt install -y \
    build-essential \
    git \
    wget \
    cpio \
    unzip \
    rsync \
    bc \
    bison \
    flex \
    file \
    libncurses-dev \
    python3 \
    patch \
    perl \
    tar \
    gzip \
    bzip2 \
    xz-utils
```

Then check Git:

```bash
git --version
```

and GCC:

```bash
gcc --version
```

and Python:

```bash
python3 --version
```

### 5. Create our project directory

I'd keep the whole experiment in one place:

```bash
mkdir -p ~/buildroot-wayland
cd ~/buildroot-wayland
```

Check:

```bash
pwd
```

You should get something similar to:

```text
/home/<your-user>/buildroot-wayland
```

### 6. Download Buildroot

Let's use the **Buildroot 2026.08 release** rather than the development `master` branch.

From WSL:

```bash
wget https://buildroot.org/downloads/buildroot-2026.08.tar.xz
```

Extract it:

```bash
tar -xf buildroot-2026.08.tar.xz
```

Then:

```bash
cd buildroot-2026.08
```

and:

```bash
ls
```

You should see things such as:

```text
Config.in
Makefile
README
board
configs
package
system
toolchain
```

### 7. The first Buildroot test

Before configuring anything, run:

```bash
make --version
```

Then:

```bash
make menuconfig
```

You should get the Buildroot configuration interface.

**Don't change anything yet.**

If the menu appears, exit with:

```text
Esc
Esc
```

and choose **Exit** when prompted.

***

## Your first checkpoint 🎯

Please run these commands and paste the output here:

```powershell
wsl --version
wsl -l -v
```

In case ``` wsl --version ``` says that WSL is not installed, just press space to install it.

Then inside Ubuntu:

```bash
uname -a
cat /etc/os-release
gcc --version
git --version
```

And finally:

```bash
cd ~/buildroot-wayland/buildroot-2026.08
make menuconfig
```

If `menuconfig` opens successfully, **stop there**.

Then we'll do **Step 2: create our first minimal x86-64 Buildroot Linux image**. From that point we'll start turning the tiny Linux system into our Wayland/Sway environment.

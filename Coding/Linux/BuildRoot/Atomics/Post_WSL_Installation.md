---
id: 20260930230431
title: Post WSL Installation
author: Karl Schmitt
date: 2026-09-30
---

# Post WSL Installation

After the instalation invoke the PowerShell command: ```wsl -version```
```powershell
PS C:\Users\User> wsl --version
WSL-Version: 3.0.1.0
Kernelversion: 6.18.40.1-1
WSLg-Version: 1.0.79
MSRDC-Version: 1.2.7214
Direct3D-Version: 1.611.1-81528511
DXCore-Version: 10.0.26100.1-240331-1435.ge-release
Windows-Version: 10.0.26100.9457
PS C:\Users\User>
```

Perfect! 🎉 **WSL is now installed successfully.** Your output also shows WSLg and the Linux kernel are installed, which is particularly interesting for our eventual Wayland experiments.

The important part is:

```text
WSL-Version:       3.0.1.0
Kernelversion:     6.18.40.1-1
WSLg-Version:      1.0.79
```

However, Windows told you that a **restart is required** before the changes become active.

### Do this next

**1. Restart Windows.**

After the reboot, open PowerShell and run:

```powershell
wsl --status
```

Then:

```powershell
wsl -l -v
```

### What we're expecting

You may see that no Linux distribution is installed yet, for example:

```text
NAME      STATE    VERSION
```

That's perfectly fine.

If Ubuntu isn't installed, we'll install it next with:

```powershell
wsl --install -d Ubuntu
```

Then we'll enter Ubuntu and prepare the Buildroot build environment.

**Don't install Buildroot yet.** Let's first get Ubuntu working correctly.

After the reboot, send me the output of:

```powershell
wsl --status
wsl -l -v
```

and we'll take the next step together. 🚀

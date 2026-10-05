---
id: 20261004224824
title: Testing Buildroot using Weston
author: Karl Schmitt
date: 2026-10-04
keywords: [ Buildroot, Weston, QEMU, Docker]
---

# Testing Buildroot using Weston

Buildroot baut erfolgreich. 

## 🎯 1. Schau dir deine fertigen Images an

On your Linux build system:
```bash
ls ~/buildroot-work/buildroot/output/images
```
Du wirst dort sehen:

* `rootfs.tar` → perfekt für Docker

* `rootfs.ext2` / `rootfs.ext4` → für QEMU

* evtl. Kernel‑Image (falls aktiviert)

Das Rootfs kann nun in Docker unter WSL2 ausgeführt werden:

## 🎯 2. Setup your Docker Environment

On your Windows host environment using PowerShell to the Docker container:
```powershell
docker import output/images/rootfs.tar buildroot-image
docker run -it --privileged -p 3389:3389 buildroot-image /sbin/init
```

## 🎯 3. Starting Weston Headless + RDP:

Start Weston on your Buildroot guest system, using a Bash terminal:
```bash
weston --backend=headless-backend.so --rdp --socket=wayland-0
```
## 🎯 4. Verbinde dich von Windows aus

Connect your Windows 11 with your Buildroot guest system, running inside a docker container.
Du siehst deine Buildroot‑Wayland‑GUI.

```**powershell**
mstsc.exe /v:localhost:3389
```

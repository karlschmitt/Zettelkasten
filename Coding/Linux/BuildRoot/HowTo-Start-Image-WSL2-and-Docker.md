---
id: 20261006205921
title: Start the Custom Buildroot Image
author: Karl Schmitt
date: 2026-10-06
keywords: [ Buildroot, Electron, WSL2, Docker ]
---

> [NOTE!]
> Diese Anleitung beschreibt, wie ein **benutzerdefiniertes Linux-Image**, bestehend aus Buildroot, Sway, Node.js und Electron, auf einem Windows-System ausgeführt werden kann. Mithilfe von **PowerShell-Befehlen** lässt sich das Betriebssystem sowohl als **WSL2-Distribution** als auch als **Docker-Container** einrichten. Ein integrierter **Grafik-Selbsttest** validiert die Software-Rendering-Pipeline, indem er eine Headless-Umgebung startet und einen Screenshot der Electron-Anwendung erstellt. Das gleiche **rootfs.tar-Archiv** dient dabei als gemeinsame Grundlage für beide Plattformen, wodurch ein identisches Verhalten gewährleistet wird. Abschließend bietet das Dokument hilfreiche **Fehlerbehebungen** und Befehlsreferenzen zur Verwaltung der virtuellen Umgebungen.

# Start the Custom Buildroot Image

## How-To: Start the Custom Buildroot/Electron Image as WSL2 and as Docker

This guide shows how to **run** the custom Linux image (Buildroot + Wayland/Sway + Node.js +
Electron) on Windows, both as a **WSL2 distribution** and as a **Docker image**, and how to
run the built-in **Electron "Hello World"** graphics-pipeline self-test.

> All commands are for **Windows PowerShell** unless noted. Lines starting with `#` are comments.

---

## 0. Prerequisites

- **Windows 11** with **WSL2** installed and working (`wsl --version` should succeed).
- **Docker Desktop** with the WSL2 backend (for the Docker part).
- The image artifact **`rootfs.tar`** and the **`Dockerfile`**.
  In this environment they are at:
  ```
  D:\Users\BKU\karlschmitt\br-electron-staging\rootfs.tar
  D:\Users\BKU\karlschmitt\br-electron-staging\Dockerfile
  ```

What the self-test does: it starts **Sway** (a Wayland compositor) in headless mode, launches
the **Electron** app, has the app take a screenshot of itself, and prints `RESULT: PASS` if a
real (non-blank) frame was rendered. No GPU or physical display is required.

---

## PART A — Run as a WSL2 distribution

### A1. Import the image as a new WSL2 distro

```powershell
# Pick an install location for the distro's virtual disk:
$dir = "$env:USERPROFILE\ElectronBR"
New-Item -ItemType Directory -Force -Path $dir | Out-Null

# Import rootfs.tar as a WSL2 distro named "ElectronBR":
wsl --import ElectronBR $dir "D:\Users\BKU\karlschmitt\br-electron-staging\rootfs.tar" --version 2

# Confirm it is registered:
wsl --list --verbose
```

> If a distro named `ElectronBR` already exists and you want a clean start, remove it first
> with `wsl --unregister ElectronBR` (this deletes that distro's data).

### A2. Run the graphics-pipeline self-test

```powershell
wsl -d ElectronBR -- bash -c "run-electron verify"
```

Expected output (last line):

```
RESULT: PASS (Electron rendered; screenshot <N> bytes at /tmp/electron-shot.png)
```

### A3. View the rendered screenshot (optional)

```powershell
# Copy the screenshot from the distro to your Windows user profile:
wsl -d ElectronBR -- bash -c "cp /tmp/electron-shot.png /mnt/c/Users/Public/electron-shot.png"
# Then open it:
start C:\Users\Public\electron-shot.png
```

### A4. Open an interactive shell in the image (optional)

```powershell
wsl -d ElectronBR
# You are now inside the image. Try:
#   node --version
#   sway --version
#   cat /etc/motd
#   exit
```

### A5. Run the app in "keep running" mode (optional)

Instead of the one-shot self-test, you can start Sway + Electron and leave them running:

```powershell
wsl -d ElectronBR -- bash -c "run-electron run"
# Press Ctrl+C in the terminal to stop.
```

### A6. Managing the WSL distro

```powershell
wsl --list --verbose            # list distros and state
wsl --terminate ElectronBR      # stop the distro
wsl --unregister ElectronBR     # delete the distro (removes its data)
```

---

## PART B — Run as a Docker image

### B1. Build the Docker image (one time)

The image is built from the same `rootfs.tar` using the provided `Dockerfile`.

```powershell
cd "D:\Users\BKU\karlschmitt\br-electron-staging"
docker build -t electron-br:latest .

# Confirm the image exists:
docker images electron-br
```

> If the image `electron-br:latest` is already built, you can skip to B2.

### B2. Run the graphics-pipeline self-test

The image's default command runs the self-test and exits:

```powershell
docker run --rm electron-br:latest
```

Expected output (last line):

```
RESULT: PASS (Electron rendered; screenshot <N> bytes at /tmp/electron-shot.png)
```

`--rm` automatically removes the container when it finishes.

### B3. Extract the rendered screenshot (optional)

```powershell
# Run without --rm so the container persists, then copy the file out:
docker run --name electron-shot electron-br:latest
docker cp electron-shot:/tmp/electron-shot.png .\electron-shot-docker.png
docker rm electron-shot
start .\electron-shot-docker.png
```

### B4. Open an interactive shell in the container (optional)

```powershell
docker run --rm -it --entrypoint /bin/bash electron-br:latest
# Inside the container, try:
#   run-electron verify
#   node --version
#   exit
```

---

## Quick reference

| Action | WSL2 | Docker |
|---|---|---|
| Prepare (one time) | `wsl --import ElectronBR <dir> rootfs.tar --version 2` | `docker build -t electron-br:latest .` |
| Run self-test | `wsl -d ElectronBR -- bash -c "run-electron verify"` | `docker run --rm electron-br:latest` |
| Interactive shell | `wsl -d ElectronBR` | `docker run --rm -it --entrypoint /bin/bash electron-br:latest` |
| Keep app running | `wsl -d ElectronBR -- bash -c "run-electron run"` | `docker run --rm electron-br:latest /usr/bin/run-electron.sh run` |
| Remove | `wsl --unregister ElectronBR` | `docker rmi electron-br:latest` |

A successful run prints **`RESULT: PASS`** in both environments.

---

## Troubleshooting

| Symptom | Fix |
|---|---|
| `wsl --import` fails: distro exists | `wsl --unregister ElectronBR`, then import again. |
| `run-electron: command not found` | Use the full path: `/usr/bin/run-electron.sh verify`. |
| Docker: `Cannot connect to the Docker daemon` | Start **Docker Desktop** and wait until it reports "running". |
| Self-test shows warnings about `system_bus_socket` or `Xwayland` | **Harmless** — these do not stop rendering; a `PASS` result is still valid. |
| `RESULT: FAIL (no screenshot ...)` | Re-run once (first run can be slow). If it persists, open a shell and run `run-electron verify` to see the full log. |
| Want to see the GUI live on the Windows desktop | Not covered here — the image is configured for **headless** self-testing. Ask for a WSLg-based interactive setup if required. |

---

## Notes

- The **same `rootfs.tar`** powers both the WSL2 distro and the Docker image, so behaviour is
  identical across the two.
- Graphics are **software-rendered** (no GPU needed), which is why it works in headless WSL2
  and in plain Docker containers.
- The distro name `ElectronBR` and the image tag `electron-br:latest` are conventions used
  here; you may choose different names.

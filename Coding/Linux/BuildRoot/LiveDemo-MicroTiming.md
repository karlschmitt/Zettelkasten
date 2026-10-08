---
id: 20261006210825
title: Live Demo
author: Karl Schmitt
date: 2026-10-06
---

> [NOTE!]
> Diese Dokumentation erklärt anschaulich, wie sich ein **maßgeschneidertes Linux-System** samt moderner Benutzeroberfläche und Laufzeitumgebungen auf **Windows-Rechnern** ausführen lässt. Mithilfe spezifischer **PowerShell-Skripte** wird das Betriebssystem wahlweise als **WSL2-Distribution** oder über **Docker-Container** bereitgestellt. Ein automatisierter **Grafik-Test** überprüft dabei die erfolgreiche Darstellung der Benutzeroberfläche durch die Erstellung eines Screenshots. Da für sämtliche Installationswege dasselbe **Tar-Archiv** als Basis dient, ist ein absolut **einheitliches Systemverhalten** garantiert. Nützliche **Hinweise zur Problembehebung** runden die Anleitung ab und erleichtern die Administration der virtuellen Umgebungen im Alltag.

# Live Demo — Micro Timing

**Topic:** Custom Buildroot + Electron/Wayland Linux image — build, run & test on WSL2 and Docker
**Audience:** Team / stakeholders
**Total duration:** ~15 minutes (12 min demo + 3 min buffer for Q&A)
**Presenter setup:** Windows 11, WSL2 (Ubuntu) with the initial build, Docker Desktop running

> **Format:** Each block shows a time budget, what to **say**, and what to **do** (commands/actions).
> Commands are **Windows PowerShell** unless noted. Keep a terminal and a file explorer window open.

---

## Pre-flight checklist (do this BEFORE the audience joins — ~5 min, not counted)

- [ ] Docker Desktop is started and reports **"running"**.
- [ ] `wsl --version` succeeds; WSL2 Ubuntu build host is reachable.
- [ ] Artifacts present: `rootfs.tar` and `Dockerfile` at
      `D:\Users\BKU\karlschmitt\br-electron-staging\`.
- [ ] Docker image pre-built: `docker images electron-br` lists `electron-br:latest`.
      *(Build it ahead of time — a live `docker build` is too slow for a demo.)*
- [ ] Optional: pre-import the WSL distro `ElectronBR` so you can skip the slow import live,
      OR keep the import in to show the full flow (your call — see Section 2).
- [ ] Terminal font size bumped up for readability; clear the screen (`cls`).
- [ ] Have the proof screenshot ready to open as a fallback if live rendering is slow.

**Pre-flight commands (run before the audience joins — copy/paste):**
```powershell
# Confirm WSL and Docker are ready
wsl --version
wsl --list --verbose
docker images electron-br

# Pre-build the Docker image (do this ahead of time — a live build is too slow)
cd "D:\Users\BKU\karlschmitt\br-electron-staging"
docker build -t electron-br:latest .
```

---

## 0. Introduction — the build and its artifacts (0:00 → 2:30, ~2.5 min)

**Say:**
> "What I'm showing today is a single, self-contained custom Linux image. It runs a modern
> **Electron** desktop app on a lightweight **Buildroot** base, with the full **Wayland/Sway**
> graphics stack and **Node.js** built in.
>
> The key idea: **one artifact, two platforms.** The exact same image runs as a **WSL2
> distribution** for developers on Windows, and as a **Docker image** for CI/CD and servers —
> so behaviour is identical everywhere.
>
> The build itself ran from source on my **WSL2 Ubuntu** environment. The headline cost was
> the initial toolchain compilation — roughly an hour, unattended — and after that, rebuilds
> are incremental and fast."

**Say — the artifacts:**
> "The build produces two things we care about:
> - **`rootfs.tar`** — the complete root filesystem of the image. This single file *is* the
>   deliverable; it feeds both WSL2 and Docker.
> - **A `Dockerfile`** — a thin wrapper that turns the same `rootfs.tar` into a Docker image.
>
> Inside the image there's a small **Electron 'Hello World'** app that renders a window,
> takes a screenshot of itself, and prints `RESULT: PASS` — a built-in, automatable proof
> that the whole graphics pipeline works, with **no GPU and no physical display**."

**Do:**
```powershell
cd "D:\Users\BKU\karlschmitt\br-electron-staging"
dir rootfs.tar, Dockerfile    # show the two artifacts and the rootfs.tar size
```

> **Timing tip:** Keep this verbal and quick. Point at the two files on screen; don't read the
> Dockerfile line by line.

---

## 1. (Context) How it was built — on WSL2 Ubuntu (2:30 → 4:00, ~1.5 min)

**Say:**
> "Just for context — the build happened here, on WSL2 Ubuntu. I'm not going to rebuild live;
> the first from-source build takes about an hour. Instead I'll show that the build host and
> the artifact are real, then move straight to **running and testing** the result."

**Do (optional, keep short):**
```powershell
wsl --list --verbose          # show the Ubuntu build distro is present
```
> **Say:** "That's the build side. Now the interesting part — running the *same* artifact in
> two completely different environments."

> **Timing tip:** If you're tight on time, fold this into the intro and skip the command.

---

## 2. Developing, running & testing on WSL2 (4:00 → 8:30, ~4.5 min)

**Say:**
> "First target: **WSL2**. I take `rootfs.tar` and import it as a brand-new WSL2 distribution.
> This is how a developer on a Windows laptop would get the image."

### 2a. Import the image as a WSL2 distro (~1 min)
**Do:**
```powershell
$dir = "$env:USERPROFILE\ElectronBR"
New-Item -ItemType Directory -Force -Path $dir | Out-Null
wsl --import ElectronBR $dir "D:\Users\BKU\karlschmitt\br-electron-staging\rootfs.tar" --version 2
wsl --list --verbose          # confirm ElectronBR is registered
```
> **Say:** "That's it — the image is now a first-class WSL2 distro."
>
> **Timing tip:** If `ElectronBR` already exists from pre-flight, *say so* and skip the import,
> or run `wsl --unregister ElectronBR` first for a clean on-stage import.

### 2b. Run the graphics-pipeline self-test (~1.5 min)
**Say:**
> "Now the self-test: it starts the Sway Wayland compositor headless, launches the Electron
> app, and the app screenshots itself. Watch the last line."

**Do:**
```powershell
wsl -d ElectronBR -- bash -c "run-electron verify"
```
**Expected (last line):**
```
RESULT: PASS (Electron rendered; screenshot <N> bytes at /tmp/electron-shot.png)
```
> **Say:** "`PASS` — a real, non-blank frame was rendered, entirely in software."
>
> **Note:** Warnings about `system_bus_socket` or `Xwayland` are **harmless**; a `PASS` is valid.

### 2c. Show the rendered screenshot (~1 min)
**Do:**
```powershell
wsl -d ElectronBR -- bash -c "cp /tmp/electron-shot.png /mnt/c/Users/Public/electron-shot.png"
start C:\Users\Public\electron-shot.png
```
> **Say:** "And here's the actual rendered window — including full-colour emoji. This is the
> GUI, produced headlessly."

### 2d. (Optional) Peek inside the image (~1 min)
**Do (run in PowerShell to enter the image):**
```powershell
wsl -d ElectronBR
```
**Then, inside the image shell, type these (Linux):**
```bash
node --version
sway --version
exit
```
> **Say:** "It's a real, minimal Linux with Node and Sway inside — nothing more than we chose
> to include."

> **Timing tip:** 2d is the first thing to cut if you're running long.

---

## 3. Running & testing on Docker (8:30 → 12:00, ~3.5 min)

**Say:**
> "Second target: **Docker** — same `rootfs.tar`, wrapped by the `Dockerfile`. This is the
> CI/CD and server story. The image is already built; a live build takes too long, so I built
> it in advance from the identical artifact."

### 3a. Confirm the image exists (~0.5 min)
**Do:**
```powershell
docker images electron-br     # show electron-br:latest is present
```
> **Say (if asked how it was built):** "`docker build -t electron-br:latest .` in this folder —
> one time, from the same `rootfs.tar`."

### 3b. Run the self-test in Docker (~1.5 min)
**Say:**
> "The image's default command runs the exact same self-test and exits."

**Do:**
```powershell
docker run --rm electron-br:latest
```
**Expected (last line):**
```
RESULT: PASS (Electron rendered; screenshot <N> bytes at /tmp/electron-shot.png)
```
> **Say:** "`PASS` again — same image, same result, now in a plain Docker container with no GPU."

### 3c. (Optional) Extract the Docker-rendered screenshot (~1 min)
**Do:**
```powershell
docker run --name electron-shot electron-br:latest
docker cp electron-shot:/tmp/electron-shot.png .\electron-shot-docker.png
docker rm electron-shot
start .\electron-shot-docker.png
```
> **Say:** "Identical rendering from the Docker side — proving true cross-platform parity from
> a single artifact."

> **Timing tip:** 3c is optional; the `PASS` in 3b already proves the point.

---

## 4. Wrap-up (12:00 → 13:00, ~1 min)

**Say:**
> "To recap: **one `rootfs.tar`**, built once on WSL2 Ubuntu, runs and self-tests successfully
> as both a **WSL2 distribution** and a **Docker image** — same `RESULT: PASS`, same rendered
> GUI, no GPU required.
>
> Next steps would be to swap the demo app for the real Electron application, wire this
> self-test into CI/CD as a quality gate, and optionally set up an internal package mirror for
> fully network-independent builds.
>
> Questions?"

**Do (optional cleanup after the demo):**
```powershell
wsl --unregister ElectronBR   # removes the demo distro and its data
```

---

## Quick command reference (presenter cheat-sheet)

| Step | Command |
|---|---|
| Show artifacts | `dir rootfs.tar, Dockerfile` |
| Import WSL distro | `wsl --import ElectronBR $dir "...\rootfs.tar" --version 2` |
| WSL self-test | `wsl -d ElectronBR -- bash -c "run-electron verify"` |
| Show WSL screenshot | `wsl -d ElectronBR -- bash -c "cp /tmp/electron-shot.png /mnt/c/Users/Public/electron-shot.png"` → `start C:\Users\Public\electron-shot.png` |
| Docker image check | `docker images electron-br` |
| Docker self-test | `docker run --rm electron-br:latest` |
| Cleanup WSL | `wsl --unregister ElectronBR` |

---

## Fallback plan (if something misbehaves live)

| Problem | On-stage recovery |
|---|---|
| `wsl --import` says distro exists | Say "already prepared", or `wsl --unregister ElectronBR` then re-import. |
| `run-electron: command not found` | Use full path: `/usr/bin/run-electron.sh verify`. |
| Docker daemon not reachable | Start Docker Desktop; meanwhile narrate the WSL2 result. |
| Self-test shows `FAIL` | Re-run once (first run can be slow); if it persists, open the pre-captured screenshot and continue. |
| Running out of time | Skip 1, 2d, 3c; the two `RESULT: PASS` lines (WSL2 + Docker) are the core. |

---

### Timing summary

| Section | Window | Duration |
|---|---|---|
| 0. Introduction & artifacts | 0:00 → 2:30 | 2.5 min |
| 1. Context: built on WSL2 Ubuntu | 2:30 → 4:00 | 1.5 min |
| 2. Develop/run/test on WSL2 | 4:00 → 8:30 | 4.5 min |
| 3. Run/test on Docker | 8:30 → 12:00 | 3.5 min |
| 4. Wrap-up | 12:00 → 13:00 | 1.0 min |
| **Buffer / Q&A** | 13:00 → 15:00 | 2.0 min |

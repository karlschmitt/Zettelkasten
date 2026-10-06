---
id: 20261004222429
title: Step‑by‑Step Tutorial
author: Karl Schmitt
date: 2026-10-04
keywords: [ Buildroot, WSL2, Docker, Wayland, Weston, RDP]
---
![Anleitung für Linux-Container-Buildsysteme.](../Images/Anleitung_für_Linux-Container-Buildsysteme.png)

> [NOTE!]
> Dieser Leitfaden beschreibt eine reproduzierbare Anleitung zur Erstellung eines maßgeschneiderten Linux-Systems mittels **Buildroot** unter Windows mit **WSL2** und **Docker**. Zunächst wird die Entwicklungsumgebung eingerichtet und ein dedizierter Arbeitsbereich sowie ein externer Baum für benutzerdefinierte Softwarepakete wie **Electron** konfiguriert. Anschließend erfolgt das Kompilieren des gesamten Betriebssystems, dessen anschließender Import als **Docker-Image** das Ausführen des Containers mit aktiviertem **Systemd** ermöglicht. Schließlich wird der **Weston**-Kompositor im Headless-Modus gestartet, sodass über das Remotedesktop-Protokoll (**RDP**) von Windows aus auf die grafische Benutzeroberfläche zugegriffen werden kann.


# Buildroot Step‑by‑Step Tutorial

> [NOTE!]
>  Here’s a clean, reproducible, step‑by‑step tutorial you can follow on any machine.


### 1 Prepare the environment

Set up the basic tools needed to build and run the system.

On Windows: install **WSL2**, a Linux distribution (e.g. Ubuntu), and **Docker Desktop** with WSL2 backend enabled.

* Enable WSL and Virtual Machine Platform in Windows Features

* Install a Linux distro (e.g. Ubuntu) from Microsoft Store

* Install Docker Desktop and ensure it uses the WSL2 backend

* Inside WSL, verify Docker works: `docker ps`

### 2 Create the Buildroot workspace

Organize a working directory for Buildroot and the external tree.

In WSL terminal:

* Create a workspace: `mkdir -p ~/buildroot-work && cd ~/buildroot-work`

* Download or clone Buildroot into `buildroot/` (e.g. `git clone https://git.busybox.net/buildroot buildroot`)

* Verify: `cd buildroot && ls` shows standard Buildroot directories

### 3 Create the Buildroot external tree

Set up an external tree to hold custom packages and configuration.

In WSL terminal:

* Go to home: `cd ~`

* Create external tree: `mkdir -p ~/buildroot-external/package/electron` and `mkdir -p ~/buildroot-external/package/hello-electron`

* Ensure structure: `ls ~/buildroot-external` should show `Config.in`, `external.mk`, `package/` after next steps

### 4 Define external tree integration files

Connect the external tree to Buildroot via Config.in and external.mk.

Edit files under `~/buildroot-external`:

* Create `Config.in` with:

  * `menu "Custom external packages"`

  * `source "$BR2_EXTERNAL/package/electron/Config.in"`

  * `source "$BR2_EXTERNAL/package/hello-electron/Config.in"`

  * `endmenu`

* Create `external.mk` with:

  * `include $(BR2_EXTERNAL)/Config.in`

  * `include $(BR2_EXTERNAL)/package/electron/electron.mk`

  * `include $(BR2_EXTERNAL)/package/hello-electron/hello-electron.mk`

* Ensure files are saved without BOM and with Unix line endings (LF).

### 5 Define custom packages (Electron example)

Add minimal package definitions for custom applications.

Under `~/buildroot-external/package`:

* For `electron`:

  * `Config.in`: `config BR2_PACKAGE_ELECTRON` + `bool "electron"`

  * `electron.mk`: define version/site/install commands and end with `$(eval $(generic-package))`

* For `hello-electron`:

  * `Config.in`: `config BR2_PACKAGE_HELLO_ELECTRON` + `bool "hello-electron"`

  * `hello-electron.mk`: similar minimal package definition

* Keep these simple; they can be extended later with real sources and install logic.

### 6 Configure Buildroot to use the external tree

Tell Buildroot to include the external tree and select required components.

From `~/buildroot-work/buildroot`:

* Run: `make BR2_EXTERNAL=~/buildroot-external menuconfig`

* In menuconfig, enable:

  * `systemd` as init system

  * `Weston` (Wayland compositor) with headless backend and RDP support

  * `Mesa` (software rendering)

  * Your custom packages: `electron`, `hello-electron`

* Save the configuration and exit menuconfig.

### 7 Build the system with Buildroot

Compile the full root filesystem and images.

From `~/buildroot-work/buildroot`:

* Run: `make`

* Wait for Buildroot to download, compile, and assemble all components

* When finished, check `output/images/` for generated artifacts

* Confirm `rootfs.tar` exists (this will be used for Docker).

### 8 Create a Docker image from the Buildroot rootfs

Import the Buildroot root filesystem into Docker as an image.

From `~/buildroot-work/buildroot`:

* In WSL, run: `cd output/images`

* Import the rootfs: `docker import rootfs.tar buildroot-image`

* Verify: `docker images` shows `buildroot-image`

### 9 Run the Buildroot system in a Docker container

Start the container with systemd and expose RDP to Windows.

In WSL terminal:

* Run: `docker run -it --privileged -p 3389:3389 buildroot-image /sbin/init`

* This starts systemd inside the container

* Keep this terminal open; it is the running Buildroot system.

### 10 Start Weston headless with RDP and connect from Windows

Launch the Wayland compositor and access the GUI via RDP.

Inside the running container and on Windows:

* In the container shell, start Weston:

  * `weston --backend=headless-backend.so --rdp --socket=wayland-0`

* On Windows, open the RDP client:

  * Run `mstsc.exe`

  * Connect to `localhost:3389`

* You now see the Buildroot Wayland desktop; Electron or other apps can be started as Wayland clients.

## Summary

Following these steps, you:

* Build a custom, minimal Linux system with Buildroot (including systemd, Weston, Mesa, and custom packages).

* Package it as a Docker image using `rootfs.tar`.

* Run it inside Docker on WSL2 with systemd.

* Start Weston in headless mode with RDP output.

* Connect from Windows via the native RDP client to interact with the GUI and any Wayland/Electron applications.

This sequence is reproducible on any machine with WSL2 and Docker available.

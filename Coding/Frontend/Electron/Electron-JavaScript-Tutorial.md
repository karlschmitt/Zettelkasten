---
id: 20260909185327
title: Electron as a Desktop Runtime
author: Karl Schmitt
date: 2026-09-09
---

![]()

> [NOTE!]
> Dieser Quelltext bietet eine **strukturierte Anleitung** zur Entwicklung von Desktop-Anwendungen mit dem Framework **Electron.js**. Der Text erklärt, wie Entwickler mithilfe von **Webtechnologien** wie JavaScript, HTML und CSS plattformübergreifende Software erstellen können. Der Prozess umfasst essenzielle Schritte von der **Installation von Node.js** bis hin zur Konfiguration des **Hauptprozesses** und der Benutzeroberfläche. Zudem werden fortgeschrittene Themen wie die **automatische Aktualisierung** während der Entwicklung und die finale **Paketierung** der App thematisiert. Das Ziel des Leitfadens ist es, Einsteigern den Weg von einem leeren Verzeichnis zu einem **funktionsfähigen Installationsprogramm** zu ebnen. Durch die Kombination von **Node.js und Chromium** wird aufgezeigt, wie moderne Web-Tools für die Desktop-Umgebung nutzbar gemacht werden.


![Electron.js Logo](./images/electronjs_logo.png)

# Hello Desktop: My First Electron App

Here’s a **clear, structured, step‑by‑step Electron.js tutorial** that walks you from zero to a working desktop app. Since Electron development is a technical, multi-step process, I’ll present it as a procedural guide you can follow directly.

Below is your full tutorial, including setup, project creation, main/renderer processes, packaging, and live reloading.

## Electron.js Tutorial (Beginner-Friendly)

Electron lets you build **cross‑platform desktop apps** using **JavaScript, HTML, and CSS**. It bundles **Node.js** + **Chromium**, giving you a browser-like UI with full access to the OS.

To make this practical, we’ll build a simple “Hello Desktop” app.

### Step-by-step guide

### 01

### Install Node.js

Electron requires Node.js to run its build tools and development server.

Download from **nodejs.org** and install the LTS version

* Verify installation with `node -v`

* Ensure `npm -v` also works

### 02

### Create Your Project Folder

Electron apps start as standard Node.js projects.

In terminal: `mkdir electron-tutorial && cd electron-tutorial`

* Run `npm init -y` to generate a basic package.json

* This file will define your Electron app’s entry point

### 03

### Install Electron

Start Here

Electron is installed as a development dependency.

Run: `npm install electron --save-dev`

* This downloads the Electron runtime

* You can now run Electron locally

### 04

### Create the Main Process

The main process controls windows and app lifecycle.

Create a file: `main.js`

* Add basic window code:

js

```
const { app, BrowserWindow } = require('electron');
function createWindow() {
  const win = new BrowserWindow({ width: 800, height: 600 });
  win.loadFile('index.html');
}
app.whenReady().then(createWindow);
```

### 05

### Create the Renderer (UI)

The renderer process displays HTML/CSS/JS inside Chromium.

Create `index.html`

* Add simple UI:

html

```
<!DOCTYPE html>
<html>
<body>
  <h1>Hello from Electron!</h1>
</body>
</html>
```

### 06

### Add a Start Script

This lets you launch Electron using npm.

Edit `package.json` → add:

json

```
"scripts": { "start": "electron ." }
```

* Now run `npm start`

* Your desktop window should appear

### 07

### Enable Live Reload (Optional)

Live reload speeds up development by refreshing the app automatically.

Install: `npm install electron-reload`

* Add to top of `main.js`:

js

```
require('electron-reload')(__dirname);
```

### 08

### Package Your App

Recommended

Packaging creates an installable desktop application.

Install Electron Forge: `npm install --save-dev @electron-forge/cli` Initialize: `npx electron-forge import`

* Build with `npm run make`

* Output installers appear in the `out/` folder

### What you’ve accomplished

You now have:

* A working Electron.js desktop app

* A main process (`main.js`) controlling windows

* A renderer (`index.html`) displaying UI

* A start script (`npm start`)

* Optional live reload

* Packaging via Electron Forge

Electron is powerful because you can extend this with:

* Custom menus

* IPC communication between main & renderer

* Node.js modules (filesystem, networking, etc.)

* Frameworks like React, Vue, or Svelte

### Where do you want to go next?

You can dive deeper into:

* Electron IPC

* Electron + React

* Packaging and auto-updates

* Building a real-world app

Just pick one and I’ll guide you further.

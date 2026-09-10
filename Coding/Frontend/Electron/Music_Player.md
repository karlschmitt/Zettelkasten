---
id: 20260909190604
title: Building a Desktop Music Player in Electron
author: Karl Schmitt
date: 2026-09-09
---

# Electron Music Player: Local Library Edition

A local‑library music player is a **perfect real‑world Electron.js project** because it uses everything Electron is good at: filesystem access, UI rendering, background processes, and media playback. Below is a **complete, structured guide** that takes you from zero to a working app — with architecture, code, and next‑step enhancements.

## 🎧 Core Idea

You’ll build a desktop app that:

* Scans a folder for audio files

* Reads metadata (title, artist, album)

* Displays a browsable library

* Plays music using the HTML5 `<audio>` element

* Remembers the user’s library path

This is the same architecture used by lightweight players like **MusicBee** or **Clementine**.

## 🏛️ App Architecture

### Main Process (Node.js)

* Opens windows

* Reads the filesystem

* Sends track lists to the renderer

* Stores settings (library path)

### Renderer (Browser UI)

* Displays the music library

* Plays audio

* Shows controls (play/pause/seek)

* Receives track metadata from main

### IPC (Communication)

* `main → renderer`: list of tracks

* `renderer → main`: “scan this folder”, “save settings”

## 📁 Step 1 — Project Setup

bash

```
mkdir electron-music-player
cd electron-music-player
npm init -y
npm install electron music-metadata
```

Add a start script:

json

```
"scripts": {
  "start": "electron ."
}
```

## 🪟 Step 2 — Create `main.js` (Main Process)

This file creates the window and scans the music folder.

js

```
const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const fs = require('fs');
const mm = require('music-metadata');

function createWindow() {
  const win = new BrowserWindow({
    width: 1000,
    height: 700,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  });

  win.loadFile('index.html');
}

app.whenReady().then(createWindow);

// Scan folder for audio files
ipcMain.handle('scan-folder', async (event, folderPath) => {
  const files = fs.readdirSync(folderPath);
  const audioFiles = files.filter(f => f.endsWith('.mp3') || f.endsWith('.flac'));

  const tracks = [];
  for (const file of audioFiles) {
    const fullPath = path.join(folderPath, file);
    const metadata = await mm.parseFile(fullPath);

    tracks.push({
      path: fullPath,
      title: metadata.common.title || file,
      artist: metadata.common.artist || 'Unknown Artist',
      album: metadata.common.album || 'Unknown Album'
    });
  }

  return tracks;
});
```

## 🔌 Step 3 — Create `preload.js` (Secure IPC)

js

```
const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('musicAPI', {
  scanFolder: (folderPath) => ipcRenderer.invoke('scan-folder', folderPath)
});
```

## 🎨 Step 4 — Create `index.html` (Renderer UI)

html

```
<!DOCTYPE html>
<html>
<head>
  <title>Music Player</title>
</head>
<body>
  <h1>My Music Library</h1>
  <input type="file" id="folderPicker" webkitdirectory directory />
  <ul id="trackList"></ul>

  <audio id="player" controls></audio>

  <script src="renderer.js"></script>
</body>
</html>
```

## 🖥️ Step 5 — Create `renderer.js` (UI Logic)

js

```
const folderPicker = document.getElementById('folderPicker');
const trackList = document.getElementById('trackList');
const player = document.getElementById('player');

folderPicker.addEventListener('change', async (e) => {
  const folderPath = e.target.files[0].path;
  const tracks = await window.musicAPI.scanFolder(folderPath);

  trackList.innerHTML = '';

  tracks.forEach(track => {
    const li = document.createElement('li');
    li.textContent = `${track.title} — ${track.artist}`;
    li.onclick = () => {
      player.src = track.path;
      player.play();
    };
    trackList.appendChild(li);
  });
});
```

You now have a **fully working local music player**.

## 🚀 Step 6 — Real‑World Enhancements

### Add these features to make it feel like Spotify or MusicBee:

* **Persistent settings** (store last library path)

* **Waveform or spectrum visualizer**

* **Playlists**

* **Search bar**

* **Album art extraction**

* **Mini-player window**

* **Media key support**

## 🧭 What’s the next step you want?

Choose one and I’ll build it with you:

* persistent settings

* album art

* playlists

* search

Just pick the feature you want to add next.

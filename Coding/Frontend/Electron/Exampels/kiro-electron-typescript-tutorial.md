---
id: 20260910150533
title: Building a Desktop App with Electron.js and TypeScript
author: Karl Schmitt
date: 2026-09-10
keywords: [ Elektron.js, TypeScript]
---

# Building a Desktop App with Electron.js and TypeScript

A hands-on tutorial for creating a cross-platform desktop application using [Electron](https://www.electronjs.org/) with TypeScript, on Windows with PowerShell. You'll build a small but complete "Notes" app that demonstrates Electron's core architecture: the main process, renderer process, secure preload bridge, and inter-process communication (IPC).

---

## Table of Contents

1. [How Electron Works](#1-how-electron-works)
2. [Prerequisites](#2-prerequisites)
3. [Project Setup](#3-project-setup)
4. [TypeScript Configuration](#4-typescript-configuration)
5. [The Main Process](#5-the-main-process)
6. [The Preload Script (Secure Bridge)](#6-the-preload-script-secure-bridge)
7. [The Renderer (UI)](#7-the-renderer-ui)
8. [Wiring Up IPC](#8-wiring-up-ipc)
9. [Building and Running](#9-building-and-running)
10. [Persisting Data to Disk](#10-persisting-data-to-disk)
11. [Packaging for Distribution](#11-packaging-for-distribution)
12. [Next Steps](#12-next-steps)

---

## 1. How Electron Works

An Electron app combines Chromium (for the UI) and Node.js (for system access). It runs in two kinds of processes:

- **Main process** — one per app. Runs in Node.js. Creates windows, accesses the OS, and manages the app lifecycle. Your entry point.
- **Renderer process** — one per window. Runs a web page (HTML/CSS/JS) in Chromium. It builds the UI but, for security, has no direct Node.js access.
- **Preload script** — runs in the renderer *before* the web page loads, with access to a limited Node API. It exposes a safe, explicit bridge between renderer and main via `contextBridge`.

```
┌─────────────────┐        IPC         ┌──────────────────┐
│  Main Process   │ <───────────────>  │  Renderer (UI)   │
│  (Node.js)      │                    │  (Chromium)      │
│  - windows      │   contextBridge    │  - HTML/CSS/TS   │
│  - filesystem   │   via preload.ts   │  - no direct fs  │
└─────────────────┘                    └──────────────────┘
```

This separation is the foundation of Electron security. The renderer never touches the file system directly — it asks the main process to do it through a controlled channel.

---

## 2. Prerequisites

You already have the required tooling:

- **Node.js** v22.17.0 (check: `node --version`)
- **npm** 11.12.1 (check: `npm --version`)
- **git** 2.50.1 (check: `git --version`)

Any Node.js 18+ works for current Electron versions.

---

## 3. Project Setup

Create and initialize the project:

```powershell
New-Item -ItemType Directory -Path "$HOME\electron-notes" -Force
Set-Location "$HOME\electron-notes"
npm init -y
```

Install Electron and TypeScript tooling as dev dependencies:

```powershell
npm install --save-dev electron typescript @types/node
```

> Electron bundles its own Node and Chromium, so it belongs in `devDependencies`. Your app code is packaged separately later.

Create the folder structure:

```powershell
New-Item -ItemType Directory -Path src -Force
New-Item -ItemType Directory -Path dist -Force
```

We'll keep TypeScript sources in `src/` and compile them to `dist/`.

---

## 4. TypeScript Configuration

Create `tsconfig.json` in the project root:

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "Node16",
    "moduleResolution": "node16",
    "outDir": "dist",
    "rootDir": "src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "sourceMap": true,
    "forceConsistentCasingInFileNames": true
  },
  "include": ["src/**/*"]
}
```

We use `Node16` for both `module` and `moduleResolution`. With `.ts` files (no `.mts`/`"type": "module"`), TypeScript still emits CommonJS output — which Electron's main and preload processes load reliably — while satisfying modern TypeScript.

> **TypeScript version note:** TypeScript 7+ removed the legacy `"moduleResolution": "node"` (node10) value, and requires `module` and `moduleResolution` to be consistent. The `Node16` pairing above is verified against TypeScript 7. On older TypeScript (5.x) you could alternatively use `"module": "CommonJS"` with `"moduleResolution": "node"`.

---

## 5. The Main Process

The main process is the app's entry point. Create `src/main.ts`:

```typescript
import { app, BrowserWindow, ipcMain } from "electron";
import * as path from "node:path";

// In-memory store for now; we'll persist to disk in section 10.
let notes: string[] = [];

function createWindow(): void {
  const win = new BrowserWindow({
    width: 900,
    height: 640,
    webPreferences: {
      // Security best practices:
      preload: path.join(__dirname, "preload.js"),
      contextIsolation: true, // renderer & preload get isolated contexts
      nodeIntegration: false, // renderer cannot use Node directly
    },
  });

  win.loadFile(path.join(__dirname, "..", "src", "index.html"));

  // Open DevTools during development (comment out for production):
  // win.webContents.openDevTools();
}

// --- IPC handlers: the renderer calls these through the preload bridge ---

ipcMain.handle("notes:getAll", (): string[] => {
  return notes;
});

ipcMain.handle("notes:add", (_event, text: string): string[] => {
  const trimmed = text.trim();
  if (trimmed.length > 0) {
    notes.push(trimmed);
  }
  return notes;
});

ipcMain.handle("notes:delete", (_event, index: number): string[] => {
  if (index >= 0 && index < notes.length) {
    notes.splice(index, 1);
  }
  return notes;
});

// --- App lifecycle ---

app.whenReady().then(() => {
  createWindow();

  // macOS: re-create a window when the dock icon is clicked and none are open.
  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

// Quit when all windows are closed, except on macOS.
app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit();
});
```

Key points:
- `ipcMain.handle` registers async request/response handlers the renderer can invoke.
- `webPreferences` enforces the secure defaults: context isolation on, Node integration off.

---

## 6. The Preload Script (Secure Bridge)

The preload script exposes a minimal, explicit API to the renderer using `contextBridge`. The renderer can only call exactly what you expose here. Create `src/preload.ts`:

```typescript
import { contextBridge, ipcRenderer } from "electron";

// Expose a safe "notesApi" object on window in the renderer.
contextBridge.exposeInMainWorld("notesApi", {
  getAll: (): Promise<string[]> => ipcRenderer.invoke("notes:getAll"),
  add: (text: string): Promise<string[]> => ipcRenderer.invoke("notes:add", text),
  delete: (index: number): Promise<string[]> =>
    ipcRenderer.invoke("notes:delete", index),
});
```

To get type-safety and editor autocomplete in the renderer, declare the shape of `window.notesApi`. Create `src/global.d.ts`:

```typescript
export interface NotesApi {
  getAll(): Promise<string[]>;
  add(text: string): Promise<string[]>;
  delete(index: number): Promise<string[]>;
}

declare global {
  interface Window {
    notesApi: NotesApi;
  }
}
```

---

## 7. The Renderer (UI)

Create the HTML page `src/index.html`:

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta
      http-equiv="Content-Security-Policy"
      content="default-src 'self'; style-src 'self' 'unsafe-inline';"
    />
    <title>Electron Notes</title>
    <style>
      body {
        font-family: "Segoe UI", system-ui, sans-serif;
        margin: 0;
        padding: 24px;
        background: #1e1e2e;
        color: #cdd6f4;
      }
      h1 { margin-top: 0; }
      .row { display: flex; gap: 8px; margin-bottom: 16px; }
      input {
        flex: 1;
        padding: 10px;
        border-radius: 6px;
        border: 1px solid #45475a;
        background: #313244;
        color: #cdd6f4;
      }
      button {
        padding: 10px 16px;
        border: none;
        border-radius: 6px;
        background: #89b4fa;
        color: #1e1e2e;
        cursor: pointer;
        font-weight: 600;
      }
      button:hover { background: #74c7ec; }
      ul { list-style: none; padding: 0; }
      li {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 10px 12px;
        background: #313244;
        border-radius: 6px;
        margin-bottom: 8px;
      }
      .del {
        background: #f38ba8;
        padding: 4px 10px;
      }
    </style>
  </head>
  <body>
    <h1>📝 Notes</h1>
    <div class="row">
      <input id="note-input" type="text" placeholder="Write a note and press Add..." />
      <button id="add-btn">Add</button>
    </div>
    <ul id="note-list"></ul>

    <!-- The compiled renderer script -->
    <script src="../dist/renderer.js"></script>
  </body>
</html>
```

Create the renderer logic `src/renderer.ts`:

```typescript
const input = document.getElementById("note-input") as HTMLInputElement;
const addBtn = document.getElementById("add-btn") as HTMLButtonElement;
const list = document.getElementById("note-list") as HTMLUListElement;

function render(notes: string[]): void {
  list.innerHTML = "";
  notes.forEach((note, index) => {
    const li = document.createElement("li");

    const span = document.createElement("span");
    span.textContent = note;

    const del = document.createElement("button");
    del.textContent = "Delete";
    del.className = "del";
    del.addEventListener("click", async () => {
      const updated = await window.notesApi.delete(index);
      render(updated);
    });

    li.appendChild(span);
    li.appendChild(del);
    list.appendChild(li);
  });
}

async function addNote(): Promise<void> {
  const text = input.value;
  if (text.trim().length === 0) return;
  const updated = await window.notesApi.add(text);
  input.value = "";
  render(updated);
  input.focus();
}

addBtn.addEventListener("click", addNote);
input.addEventListener("keydown", (e) => {
  if (e.key === "Enter") addNote();
});

// Load existing notes on startup.
window.notesApi.getAll().then(render);
```

---

## 8. Wiring Up IPC

The full request flow when a user adds a note:

```
renderer.ts                preload.ts               main.ts
   │ notesApi.add(text)        │                        │
   ├──────────────────────────>│ ipcRenderer.invoke     │
   │                           ├───────────────────────>│ ipcMain.handle("notes:add")
   │                           │                        │ notes.push(text)
   │                           │<───────────────────────┤ return notes[]
   │<──────────────────────────┤ resolved promise       │
   │ render(updated)           │                        │
```

Each channel name (e.g. `"notes:add"`) must match on both sides. The `contextBridge` ensures the renderer only ever sees the three methods you exposed — nothing else from Node or Electron leaks in.

---

## 9. Building and Running

Add scripts to `package.json`. Open it and set the `main` field and `scripts`:

```json
{
  "main": "dist/main.js",
  "scripts": {
    "build": "tsc",
    "start": "npm run build && electron ."
  }
}
```

Compile the TypeScript and launch the app:

```powershell
npm start
```

This runs `tsc` (compiling `src/*.ts` → `dist/*.js`) and then `electron .`, which reads `main` from `package.json` and boots your app. You should see the Notes window. Add a note, press Enter, and delete it.

For faster iteration, run the compiler in watch mode in one terminal and Electron in another:

```powershell
# Terminal 1
npx tsc --watch

# Terminal 2 (re-run after edits)
npx electron .
```

---

## 10. Persisting Data to Disk

Right now notes vanish when the app closes. Let's persist them to a JSON file in the OS's per-user app data directory (`app.getPath("userData")`).

Update `src/main.ts` — add file loading/saving and replace the in-memory store:

```typescript
import { app, BrowserWindow, ipcMain } from "electron";
import * as path from "node:path";
import * as fs from "node:fs";

let notes: string[] = [];
let dataFile = "";

function loadNotes(): void {
  dataFile = path.join(app.getPath("userData"), "notes.json");
  try {
    if (fs.existsSync(dataFile)) {
      notes = JSON.parse(fs.readFileSync(dataFile, "utf-8"));
    }
  } catch {
    notes = [];
  }
}

function saveNotes(): void {
  fs.writeFileSync(dataFile, JSON.stringify(notes, null, 2), "utf-8");
}

// ... keep createWindow() as before ...

ipcMain.handle("notes:getAll", (): string[] => notes);

ipcMain.handle("notes:add", (_event, text: string): string[] => {
  const trimmed = text.trim();
  if (trimmed.length > 0) {
    notes.push(trimmed);
    saveNotes();
  }
  return notes;
});

ipcMain.handle("notes:delete", (_event, index: number): string[] => {
  if (index >= 0 && index < notes.length) {
    notes.splice(index, 1);
    saveNotes();
  }
  return notes;
});

app.whenReady().then(() => {
  loadNotes(); // load before creating the window
  createWindow();
  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") app.quit();
});
```

Rebuild and run — your notes now survive restarts:

```powershell
npm start
```

On Windows, the data file lives at roughly:

```
C:\Users\<you>\AppData\Roaming\electron-notes\notes.json
```

---

## 11. Packaging for Distribution

To ship a real `.exe`, use [Electron Forge](https://www.electronforge.io/), the officially recommended toolchain. From your project root:

```powershell
npm install --save-dev @electron-forge/cli
npx electron-forge import
```

`import` adds packaging scripts and config to your project. Then create distributable installers:

```powershell
npm run make
```

Output lands in the `out/` folder — on Windows, a Squirrel-based installer `.exe`. For code signing and auto-updates, see the Electron Forge docs.

> Ensure `npm run build` (the `tsc` step) runs before packaging so `dist/` is up to date. You can add it to Forge's `prePackage` hook or a combined script.

---

## 12. Next Steps

- **Bundling** — for larger apps, use a bundler like Vite (`electron-vite`) or webpack to bundle the renderer, enable hot reload, and support modern ES modules.
- **Menus & tray** — add native menus with `Menu.buildFromTemplate` and a system tray icon with `Tray`.
- **Native dialogs** — use `dialog.showOpenDialog` / `showSaveDialog` for file pickers.
- **Auto-update** — integrate `electron-updater` or Forge's publishers.
- **Security** — keep `contextIsolation: true` and `nodeIntegration: false`, set a strict Content-Security-Policy, and validate all IPC input in the main process.

Command reference used in this tutorial:

| Command | Purpose |
|---------|---------|
| `npm init -y` | Initialize package.json |
| `npm install --save-dev electron typescript @types/node` | Install core deps |
| `npm run build` | Compile TypeScript (`tsc`) |
| `npm start` | Build then launch Electron |
| `npx tsc --watch` | Recompile on file changes |
| `npx electron-forge import` | Add packaging support |
| `npm run make` | Build distributable installer |

You now have a secure, typed, cross-platform Electron app. Happy building!

---
id: 20260910145824
title: Learning Electron.js with TypeScript and PowerShell
author: Karl Schmitt
date: 2026-09-10
keywords: [ PowerShell, TypeScript, Electron.js]  
---

![Electron.js Logo](../images/electronjs_logo.png)

# Learning Electron.js with TypeScript and PowerShell

Electron lets you build cross-platform desktop applications with web technologies and Node.js. This tutorial creates a small TypeScript desktop app using Electron Forge.

## Prerequisites

Install Node.js LTS from <https://nodejs.org/>. Then open PowerShell and verify the tools:

```powershell
node --version
npm --version
```

## 1. Create an Electron TypeScript project

Use Electron Forge's TypeScript Webpack template:

```powershell
cd $HOME
npx create-electron-app@latest electron-notes --template=webpack-typescript
cd electron-notes
```

Install dependencies if the generator did not do so automatically:

```powershell
npm install
```

Start the application:

```powershell
npm start
```

A desktop window should open. Stop the application with `Ctrl+C` in PowerShell.

## 2. Understand the project structure

The important files are usually arranged like this:

```text
src/
  index.ts       Main process entry point
  renderer.ts    Renderer process entry point
  index.html     Window HTML
  preload.ts     Secure bridge between processes
webpack.*.config.ts
package.json
```

Electron applications commonly have three parts:

- The **main process** creates windows and accesses native Electron APIs.
- The **renderer process** displays the user interface.
- The **preload script** exposes carefully selected functionality to the renderer.

## 3. Create a TypeScript user interface

Replace the contents of `src/index.html` with:

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Electron Notes</title>
  </head>
  <body>
    <main>
      <h1>Electron Notes</h1>
      <textarea id="note" rows="8" placeholder="Write a note..."></textarea>
      <button id="save-note">Save note</button>
      <p id="status" role="status"></p>
    </main>
    <script type="module" src="./renderer.ts"></script>
  </body>
</html>
```

Replace `src/renderer.ts` with:

```typescript
const noteInput = document.querySelector<HTMLTextAreaElement>("#note");
const saveButton = document.querySelector<HTMLButtonElement>("#save-note");
const status = document.querySelector<HTMLParagraphElement>("#status");

if (!noteInput || !saveButton || !status) {
  throw new Error("Required user-interface elements are missing");
}

saveButton.addEventListener("click", () => {
  const note = noteInput.value.trim();
  status.textContent = note ? `Saved ${note.length} characters.` : "Write a note first.";
});
```

Run the app again:

```powershell
npm start
```

## 4. Configure the main process

The main process creates the application window. A typical `src/index.ts` looks like this:

```typescript
import { app, BrowserWindow } from "electron";
import path from "node:path";

const createWindow = (): void => {
  const window = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      contextIsolation: true,
      nodeIntegration: false,
    },
  });

  window.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);
};

app.whenReady().then(() => {
  createWindow();

  app.on("activate", () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  });
});

app.on("window-all-closed", () => {
  if (process.platform !== "darwin") {
    app.quit();
  }
});
```

Keep the generated Webpack globals such as `MAIN_WINDOW_WEBPACK_ENTRY` intact. Electron Forge supplies them during the build.

## 5. Use a secure preload bridge

The renderer should not access Node.js APIs directly. Use `src/preload.ts` to expose a small, explicit API:

```typescript
import { contextBridge } from "electron";

contextBridge.exposeInMainWorld("electronAPI", {
  getPlatform: (): string => process.platform,
});
```

Add the matching type declaration in `src/renderer.d.ts`:

```typescript
declare global {
  interface Window {
    electronAPI: {
      getPlatform: () => string;
    };
  }
}

export {};
```

Use the bridge from `src/renderer.ts`:

```typescript
const platform = window.electronAPI.getPlatform();
console.log(`Running on ${platform}`);
```

Do not expose the entire `ipcRenderer`, filesystem, or shell API to the page. Expose only narrowly scoped functions that the UI needs.

## 6. Send messages with IPC

For functionality that belongs in the main process, define a channel in `src/preload.ts`:

```typescript
import { contextBridge, ipcRenderer } from "electron";

contextBridge.exposeInMainWorld("electronAPI", {
  saveNote: (note: string): Promise<boolean> =>
    ipcRenderer.invoke("notes:save", note),
});
```

Handle the channel in `src/index.ts`:

```typescript
import { app, BrowserWindow, ipcMain } from "electron";
import path from "node:path";

ipcMain.handle("notes:save", async (_event, note: string): Promise<boolean> => {
  const filePath = path.join(app.getPath("userData"), "note.txt");
  await fs.promises.writeFile(filePath, note, "utf8");
  return true;
});
```

Add the import required by this handler:

```typescript
import fs from "node:fs";
```

In production code, validate IPC input before writing files or performing other native operations.

## 7. Build and package the application

Run the checks and create a distributable package:

```powershell
npm run lint
npm run package
npm run make
```

Electron Forge places generated artifacts in the `out` directory. The exact installer format depends on the configured Forge makers and your operating system.

## 8. Useful PowerShell commands

```powershell
Get-ChildItem                 # List files
Get-Content package.json      # Display a file
Set-Location .\src            # Change directory
npm install                   # Install dependencies
npm start                     # Run the app in development
npm run make                  # Build distributables
```

## Common issues

### `npm` or `node` is not recognized

Install Node.js LTS and restart PowerShell so the updated `PATH` is loaded.

### The window opens but the page is blank

Check the PowerShell output and browser console. TypeScript or Webpack compilation errors usually identify the problem.

### Native APIs are unavailable in the renderer

That is expected when `nodeIntegration` is disabled. Add a narrow API to the preload script and call it through the context-isolated bridge.

## Recommended workflow

```powershell
cd $HOME\electron-notes
npm start
npm run lint
npm run package
npm run make
```

Keep the renderer focused on UI code, keep native operations in the main process, and use the preload script as the small, typed boundary between them.

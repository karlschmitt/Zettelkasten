---
id: 20260909183303
title: Build an Electron App with TypeScript
autor: Karl Schmitt
date: 2026-09-09
keywords: [ Electron, TypeScript ]
---

# Build an Electron App with TypeScript

To build an Electron.js application using TypeScript, the fastest and most reliable approach is to _use [Electron Forge](https://www.electronforge.io/) with its official Webpack + TypeScript template_. This handles all the complex bundling and compilation configurations automatically. 

Here is a step-by-step guide to setting up and running your first TypeScript-powered Electron app.

***

## Step 1: Initialize the Project

Run the following command in your terminal to generate a pre-configured template: \[1]

```bash
npm create electron-app@latest my-typescript-app -- --template=webpack-typescript
```

Navigate into your newly created directory and explore the project:

```bash
cd my-typescript-app
```

## Step 2: Understand the Architecture

Electron uses a multi-process architecture:

* Main Process (`src/main.ts`): Runs in a Node.js environment. It manages the lifecycle of the application and creates native desktop windows.
* Renderer Process (`src/renderer.ts`): Handles the user interface (HTML/CSS) and runs like a standard web page inside a Chromium instance.
* Preload Script (`src/preload.ts`): Acts as a secure bridge, allowing the renderer process to communicate with the main process safely.

## Step 3: Writing the Main Process

Open `src/main.ts`. This file handles creating the window. Notice how TypeScript types can be imported directly from the `electron` package: \[2]

```typescript
import { app, BrowserWindow } from 'electron';
// Declare the entry point for the Webpack bundle
declare const MAIN_WINDOW_WEBPACK_ENTRY: string;
declare const MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY: string;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

const createWindow = (): void => {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    height: 600,
    width: 800,
    webPreferences: {
      preload: MAIN_WINDOW_PRELOAD_WEBPACK_ENTRY,
    },
  });

  // Load the index.html of the app.
  mainWindow.loadURL(MAIN_WINDOW_WEBPACK_ENTRY);

  // Open the DevTools (Optional).
  mainWindow.webContents.openDevTools();
};

// This method will be called when Electron has finished initialization
app.on('ready', createWindow);

// Quit when all windows are closed, except on macOS.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});

app.on('activate', () => {
  if (BrowserWindow.getAllWindows().length === 0) {
    createWindow();
  }
});
```

## Step 4: The Preload Bridge

To keep your application secure, the renderer process should not have direct access to Node.js APIs. Instead, expose context-isolated APIs in `src/preload.ts`:

```typescript
import { contextBridge, ipcRenderer } from 'electron';

// Expose protected APIs to the renderer window
contextBridge.exposeInMainWorld('electronAPI', {
  getAppVersion: () => process.versions.electron,
});
```

## Step 5: Updating the User Interface (Renderer)

Open `src/renderer.ts` to update what your user sees. You can use the exposed API safely here:

```typescript
import './index.css';

console.log('👋 Hello from the TypeScript Renderer Process!');

// Access the secure API exposed via the preload script
const versionNode = document.getElementById('electron-version');
if (versionNode) {
  versionNode.innerText = (window as any).electronAPI.getAppVersion();
}
```

Make sure you have a matching element in your `src/index.html`:

```html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8" />
    <title>Hello World!</title>
  </head>
  <body>
    <h1>💖 Hello World!</h1>
    <p>Welcome to your Electron application built with TypeScript.</p>
    <p>Running Electron version: <strong id="electron-version">Loading...</strong></p>
  </body>
</html>
```

## Step 6: Running the Application

Start your development environment by running:

```bash
npm start
```

Electron Forge will compile your TypeScript code into JavaScript on the fly and open your desktop window.

***

## Step 7: Packaging Your App

When you are ready to distribute your app to users, Electron Forge makes compilation simple: \[1, 6]

```bash
npm run make
```

This builds your TypeScript code and outputs platform-specific installers (e.g., `.exe` for Windows, `.dmg` for macOS, `.deb` for Linux) inside the `out/make` directory. \[6]

Would you like to learn how to connect the front-end to a framework like React or Vite, or should we look into setting up Inter-Process Communication (IPC) so your window can talk directly to native Node.js APIs?

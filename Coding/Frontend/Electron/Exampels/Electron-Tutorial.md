---
id: 20260909223419
title: Electron.js Tutorial
author: Karl Schmitt
date: 2926-09-09
keywords: [ Electron.js]
---

![Electron.js Logo](../images/electronjs_logo.png)

# Electron.js Tutorial

This tutorial will guide you through building a minimal, type-safe desktop application using Electron.js and TypeScript.

## ⚙️ Prerequisites

Before starting, ensure you have Node.js installed on your system.

***

## Step 1: Initialize Your Project

Create a new directory for your project, open your terminal inside it, and initialize a new Node.js configuration.

```bash
mkdir electron-ts-app
cd electron-ts-app
npm init -y
```

## Step 2: Install Dependencies

You need to install Electron as a development dependency, along with TypeScript and the necessary type definitions.

```bash
npm install --save-dev electron typescript @types/node
```

## Step 3: Configure TypeScript

Initialize a TypeScript configuration file (`tsconfig.json`) to define how your code should compile.

```bash
npx tsc --init
```

Open the newly created `tsconfig.json` file and update it with the following secure, modern settings:

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "CommonJS",
    "outDir": "./dist",
    "rootDir": "./src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "forceConsistentCasingInFileNames": true
  },
  "include": ["src/**/*"]
}
```

***

## Step 4: Create the Application Source Files

Create a `src` folder to keep your TypeScript files organized, along with a basic HTML file for your user interface.

```bash
mkdir src
```

## 1. The Main Process (`src/main.ts`)

This file controls the application lifecycle and manages the native desktop window.

```typescript
import { app, BrowserWindow } from 'electron';
import * as path from 'path';

function createWindow(): void {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      // Points to the compiled preload script in the dist folder
      preload: path.join(__dirname, 'preload.js'),
    },
  });

  // Load the local HTML file.
  mainWindow.loadFile(path.join(__dirname, '../index.html'));
}

// Triggered when Electron has finished initialization
app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    // On macOS it's common to re-create a window when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

// Quit when all windows are closed, except on macOS.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
```

## 2. The Preload Script (`src/preload.ts`)

The preload script acts as a secure bridge, allowing you to safely expose selective Node.js APIs to your web frontend.

```typescript
window.addEventListener('DOMContentLoaded', () => {
  const replaceText = (selector: string, text: string | undefined) => {
    const element = document.getElementById(selector);
    if (element) element.innerText = text || '';
  };

  // Safely display the versions of core runtimes being used
  for (const type of ['chrome', 'node', 'electron']) {
    replaceText(`${type}-version`, process.versions[type]);
  }
});
```

## 3. The User Interface (`index.html`)

Create this file in your root directory (not inside `src`). It serves as the frontend visual layer.

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello Electron + TypeScript!</title>
    <style>
        body { font-family: sans-serif; padding: 20px; background: #f4f4f9; }
        h1 { color: #333; }
    </style>
</head>
<body>
    <h1>Hello World!</h1>
    <p>We are using Node.js <span id="node-version"></span>,</p>
    <p>Chromium <span id="chrome-version"></span>,</p>
    <p>and Electron <span id="electron-version"></span>.</p>
</body>
</html>
```

***

## Step 5: Configure Build and Run Scripts

Open your `package.json` file in the root directory. You need to point the `"main"` entry to the compiled JavaScript output and add scripts to build and start your application.

Update your `package.json` to look like this:

```json
{
  "name": "electron-ts-app",
  "version": "1.0.0",
  "main": "dist/main.js",
  "scripts": {
    "build": "tsc",
    "start": "tsc && electron ."
  },
  "devDependencies": {
    "@types/node": "^20.0.0",
    "electron": "^30.0.0",
    "typescript": "^5.0.0"
  }
}
```

***

## Step 6: Run Your Application

To compile your TypeScript and spin up your new Electron app, run the following command in your terminal:

```bash
npm start
```

A native desktop application window should appear on your screen displaying your HTML structure alongside your running environment versions.

Would you like to extend this template to interact with the native file system, or would you prefer to integrate a framework like React or Vue into this setup?


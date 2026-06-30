---
id: 20260520083340
title: How to install playwright?
author: Karl Schmitt
date: 2026-05-20
keywords: [ node, nodejs, playwright ]
---

# How to install playwright?

It is actually spelled **Playwright**. It is a powerful automation tool for web testing.

The installation process depends on which programming language you want to use (Node.js/JavaScript is the most common).

### 1. Installation for Node.js (Recommended)
This is the most popular way to use Playwright. You will need [Node.js](https://nodejs.org/) installed on your computer.

**Step 1: Create a new project**
Open your terminal or command prompt and run:
```bash
npm init playwright@latest
```

**Step 2: Configuration Prompts**
The installer will ask you a few questions:
*   **TypeScript or JavaScript?** (TypeScript is recommended).
*   **Where to put your tests?** (Default is `tests`).
*   **Add a GitHub Actions workflow?** (Yes/No).
*   **Install Playwright browsers?** (Choose **Yes**).

**Step 3: Run the example test**
To make sure everything installed correctly, run:
```bash
npx playwright test
```

---

### 2. Installation for Python
If you prefer Python, follow these steps:

**Step 1: Install the library**
```bash
pip install playwright
```

**Step 2: Install the browsers**
Unlike other tools, Playwright requires you to run a second command to download the actual Chromium, Firefox, and WebKit browsers:
```bash
playwright install
```

---

### 3. VS Code Extension (Highly Recommended)
If you use Visual Studio Code, the easiest way to manage Playwright is via the official extension:
1.  Open VS Code.
2.  Go to the **Extensions** view (Ctrl+Shift+X).
3.  Search for **"Playwright Test"** by Microsoft.
4.  Install it.
5.  Once installed, you can press `Ctrl+Shift+P` and type **"Install Playwright"** to set up a project graphically.

---

### Common Issues
*   **Permissions:** On Linux, you might need to install system dependencies for the browsers. You can do this by running: `npx playwright install-deps`.
*   **Updates:** To update Playwright to the latest version later on, run: `npm install @playwright/test@latest`.

### Summary of Commands (Node.js)
| Task | Command |
| :--- | :--- |
| **Install** | `npm init playwright@latest` |
| **Run Tests** | `npx playwright test` |
| **Show Report** | `npx playwright show-report` |
| **Debug Mode** | `npx playwright test --debug` |
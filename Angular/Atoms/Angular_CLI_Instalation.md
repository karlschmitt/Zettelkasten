---
id: 20260426132915
title: Installing the Angular CLI
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, CLI, installation]
---

# Installing the Angular CLI

To install the Angular CLI, you need to have **Node.js** and **npm** (Node Package Manager) already installed on your computer.

Follow these steps:

### 1. Check for Node.js
Open your terminal (Command Prompt, PowerShell, or macOS Terminal) and type:
```bash
node -v
```
If you see a version number (like `v18.x.x` or `v20.x.x`), you are ready. 

**If you don't have it:**
Download the **LTS version** from [nodejs.org](https://nodejs.org/).

---

### 2. Install Angular CLI
Run the following command in your terminal. The `-g` flag is important because it installs the CLI **globally**, allowing you to use the `ng` command anywhere on your system.

```bash
npm install -g @angular/cli
```

*   **macOS/Linux Users:** If you get a "Permission Denied" error, use `sudo`:
    ```bash
    sudo npm install -g @angular/cli
    ```

---

### 3. Verify Installation
Once the installation finishes, check that it's working by asking for the version:

```bash
ng version
```

This should display the Angular CLI version, your Node.js version, and your Operating System details.

---

### 4. Common Troubleshooting

#### **Windows: "Execution of scripts is disabled"**
If you try to run `ng` in PowerShell and get an error saying scripts are disabled, run this command as **Administrator**:
```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
```

#### **"Command not found: ng"**
If the installation was successful but `ng` isn't recognized:
1.  Restart your terminal.
2.  If that fails, you may need to add the npm global binaries folder to your system's **PATH** environment variable.

---

### 5. Start Your First Project
Now that you have the CLI, you can create the structure we discussed earlier:

```bash
ng new my-awesome-project
```

It will ask you a few questions (Which stylesheet format? Do you want SSR?). Usually, you can just press **Enter** to accept the defaults!
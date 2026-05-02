---
id: 20260501143218
title: Install Angular globally
author: Karl Schmitt
date: 2026-05-01
---

# Install Angular globally

To install the Angular CLI (Command Line Interface) globally on your system, follow these steps:

### 1. Prerequisites
Before installing Angular, you must have **Node.js** and **npm** (Node Package Manager) installed.

*   To check if you have them, open your terminal or command prompt and type:
    ```bash
    node -v
    npm -v
    ```
*   If you don't have them, download and install the **LTS version** from [nodejs.org](https://nodejs.org/).

---

### 2. The Installation Command
Open your terminal (Command Prompt, PowerShell, or Terminal) and run the following command:

```bash
npm install -g @angular/cli
```

*   **`-g`**: This flag stands for "global," meaning you can run Angular commands from any folder on your computer.

#### Note for macOS/Linux users:
If you get a "Permission Denied" error, you may need to run the command with administrator privileges:
```bash
sudo npm install -g @angular/cli
```

---

### 3. Verify the Installation
Once the installation finishes, verify that it was successful by checking the version:

```bash
ng version
```
(Or simply `ng v`)

If installed correctly, you will see the Angular logo in ASCII art and the version numbers for the CLI, Node, and your OS.

---

### 4. Create Your First Project (Optional)
Now that Angular is installed globally, you can create a new project by running:

```bash
ng new my-app
```
Then navigate into the folder and start the development server:
```bash
cd my-app
ng serve --open
```

---

### Common Troubleshooting
*   **"ng is not recognized":** On Windows, if you get this error after installation, you likely need to restart your terminal or add the npm global bin folder to your System Environment Path.
*   **Updating:** If you already had an older version and want to update to the latest, run:
    ```bash
    npm uninstall -g @angular/cli
    npm cache clean --force
    npm install -g @angular/cli@latest
    ```
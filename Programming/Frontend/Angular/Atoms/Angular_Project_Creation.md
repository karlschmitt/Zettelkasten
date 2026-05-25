---
id: 20260426173558
title: Angular Project Creation
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, project, creation ]
---

# Angular Project Creation

To create an Angular project, you use the **Angular CLI** (which you should have installed via `npm install -g @angular/cli`).



Follow these steps to create and launch your first application.

---

### 1. Run the "New" Command
Open your terminal or command prompt, navigate to the folder where you want your project to live, and run:

```bash
ng new my-angular-app
```
*(You can replace `my-angular-app` with any name you like.)*

---

### 2. Answer the Configuration Prompts
The CLI will ask you a few questions to set up the project. For a modern, standard experience, here are the recommended choices:

1.  **Which stylesheet format would you like to use?**
    *   Use the arrow keys to select **SCSS** (it is more powerful than plain CSS and the industry standard).
2.  **Do you want to enable Server-Side Rendering (SSR) and Static Site Generation (SSG/Prerendering)?**
    *   Type **N** (No) if you are a beginner. It adds complexity. You can always add it later.
    *   Type **Y** (Yes) if you are building a production SEO-heavy site.

---

### 3. Navigate into the Project
Once the installation finishes (it will download all necessary packages via npm), move into the new folder:

```bash
cd my-angular-app
```

---

### 4. Run the Application
Start the local development server by running:

```bash
ng serve --open
```

*   **`ng serve`**: Compiles the application and starts a local server.
*   **`--open` (or `-o`)**: Automatically opens your default web browser to `http://localhost:4200`.

---

### 5. Essential CLI Flags (Optional)
If you want to skip the interactive questions and create a project with a single command, you can use flags:

```bash
# Create a project with SCSS, routing enabled, and no SSR
ng new my-app --style=scss --routing --ssr=false
```

---

### 6. What's next?
Once the browser opens and you see the Angular "Welcome" page:

1.  **Open the project in VS Code:** Type `code .` in your terminal.
2.  **Find `src/app/app.component.html`**: Delete everything in that file and type `<h1>Hello World</h1>`.
3.  **Check your browser**: The page will automatically refresh to show your changes!

### Summary Checklist
1.  `ng new project-name`
2.  Choose **SCSS**.
3.  `cd project-name`
4.  `ng serve -o`
---
id: 20260508181615
title: How to create a React project?
author: Karl Schmitt
date: 2026-05-08
keywords: [ React, Vite, JavaScript, TypeScript ]
---

# How to create a React project?

Vite is the recommended tool for starting modern React projects because it is significantly faster than the older "Create React App" (CRA).

Here is the step-by-step guide to setting up a React project with Vite for both JavaScript and TypeScript.

---

### Step 1: Prerequisites
Make sure you have **Node.js** installed (Version 18+ or 20+ is recommended). You can check your version by typing `node -v` in your terminal.

---

### Step 2: The Interactive Setup (Easiest)
Run the following command in your terminal:

```bash
npm create vite@latest
```

Follow the interactive prompts:
1.  **Project name:** Type your project name (e.g., `my-react-app`).
2.  **Select a framework:** Use arrow keys to select **React**.
3.  **Select a variant:**
    *   For **JavaScript**: Select `JavaScript` or `JavaScript + SWC`.
    *   For **TypeScript**: Select `TypeScript` or `TypeScript + SWC`.

> **What is SWC?** SWC is a faster compiler written in Rust. It is highly recommended to choose the **SWC** variants for even faster build times.

---

### Step 3: The "One-Liner" Setup (Fastest)
If you want to skip the prompts, you can run these commands directly:

**For JavaScript:**
```bash
npm create vite@latest my-js-app -- --template react
```

**For TypeScript:**
```bash
npm create vite@latest my-ts-app -- --template react-ts
```

---

### Step 4: Install Dependencies and Start
Vite does not install packages automatically. You must enter the folder and install them yourself:

```bash
# 1. Move into the project folder
cd my-react-app

# 2. Install dependencies
npm install

# 3. Start the development server
npm run dev
```

Your app will now be running at `http://localhost:5173`.

---

### Key Differences: JS vs. TS in Vite

| Feature | JavaScript Setup | TypeScript Setup |
| :--- | :--- | :--- |
| **File Extensions** | `.jsx` | `.tsx` |
| **Config File** | `vite.config.js` | `vite.config.ts` |
| **Type Checking** | None (uses PropTypes) | Strict typing via `tsconfig.json` |
| **Main Entry** | `main.jsx` | `main.tsx` |

---
^^
### Useful Commands
Once your project is created, these are the commands you will use most:

*   `npm run dev`: Starts the local development server.
*   `npm run build`: Creates a production-ready folder (`dist`).
*   `npm run preview`: Locally previews the production build.
*   `npm run lint`: Runs ESLint to check for code errors.

### Next Steps Recommendation
1.  **Tailwind CSS:** If you want to add Tailwind, run `npm install -D tailwindcss postcss autoprefixer` and then `npx tailwindcss init -p`.
2.  **Clean Up:** Vite provides a very clean boiler plate, but you may want to delete the `App.css` and the contents of `App.jsx/tsx` to start fresh.

---
id: 20261112190824
author: Karl Schmitt
date: 2026-11-12
keywords: [ React, Vite ]
---

# React «Hello World» using Vite

Creating a "Hello World" React project using **Vite** is fast and modern. Vite provides an ultra-fast development server and is the officially recommended way to bootstrap React applications.

Here is a complete, step-by-step guide to setting up your first project.

### Step 1: Prerequisites

Make sure you have **Node.js** (version 18+ or 20+) installed on your computer. You can check if you have it by running this command in your terminal:

```PowerShell
node -v
```
```PowerShell
npm -v
```

### Step 2: Create the Vite + React Project

Open your terminal and run the following command to scaffold a new project:

```PowerShell
npm create vite@latest my-react-app -- --template react
```

> [NOTE!]
>  You can replace `my-react-app` with any project name you prefer._



### Step 3: Install Dependencies

Navigate into your newly created project folder and install the required project packages:

```PowerShell
cd my-react-app
npm install
```

### Step 4: Start the Development Server

Run the local development server:

```PowerShell
npm run dev
```

Vite will output a local URL (usually `http://localhost:5173`). Open that link in your browser to see your running React app!



### Step 5: Write Your Custom "Hello World" Component

1. Open the project folder in your favorite code editor (like VS Code).

2. Inside the `src/` directory, open the **`App.jsx`** file.

3. Replace its contents with this clean "Hello World" component code:

```JavaScript
import React from 'react';
import './App.css';

function App() {
  return (
    <div style={{ textAlign: 'center', marginTop: '50px', fontFamily: 'sans-serif' }}>
      <h1>Hello World! 👋</h1>
      <p>Welcome to my first React app powered by Vite.</p>
    </div>
  );
}

export default App;
```

Save the file, and your browser will instantly update to show your custom **Hello World** message via Vite's Hot Module Replacement (HMR)!



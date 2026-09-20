---
id: 20260920132457
title: The All-in-One HTML
author: Karl Schmitt
date: 2026-09-20
keywords: [ TypeScript ]
---

# The All-in-One HTML

Completely zero backend tools, zero runtimes, and zero command-line executables. Just a single **HTML file** using the official browser-ready **`typescript.js` compiler script** loaded via CDN.

You can create this file using **VS Code** (name it `index.html`), and then simply double-click it to open it in any web browser. It features a built-in interactive code editor, live compilation, and a browser console simulator!

### The All-in-One HTML + TypeScript Inline Compiler (`index.html`)

Save this code into a file named **`index.html`** in VS Code:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Browser TypeScript Bootcamp</title>
    <!-- Load the official TypeScript Compiler browser build -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/typescript/5.5.4/typescript.min.js"></script>
    <style>
        body { font-family: system-ui, sans-serif; background: #0f172a; color: #f8fafc; margin: 0; padding: 2rem; }
        .container { max-width: 900px; margin: 0 auto; }
        h1 { color: #38bdf8; margin-top: 0; }
        .grid { display: grid; grid-template-columns: 1fr 1fr; gap: 1rem; margin-top: 1rem; }
        textarea, pre { width: 100%; height: 350px; background: #1e293b; color: #e2e8f0; border: 1px solid #334155; border-radius: 8px; padding: 1rem; font-family: monospace; font-size: 14px; box-sizing: border-box; }
        pre { white-space: pre-wrap; overflow-y: auto; margin: 0; }
        button { background: #0ea5e9; color: white; border: none; padding: 0.75rem 1.5rem; font-size: 1rem; border-radius: 6px; cursor: pointer; font-weight: bold; margin-top: 1rem; }
        button:hover { background: #0284c7; }
        .section-title { font-weight: bold; margin-bottom: 0.5srem; color: #94a3b8; }
        .presets { margin-bottom: 1rem; }
        .presets button { background: #334155; margin-right: 0.5rem; margin-top: 0; padding: 0.5rem 1rem; font-size: 0.85rem; }
        .presets button:hover { background: #475569; }
    </style>
</head>
<body>

<div class="container">
    <h1>🚀 Browser TypeScript Bootcamp</h1>
    <p>Runs entirely in your browser using the inline <code>typescript.js</code> compiler. No Node, npm, or terminal required!</p>

    <div class="presets">
        <span class="section-title">Load Bootcamp Module:</span>
        <button onclick="loadModule(1)">1. Basics</button>
        <button onclick="loadModule(2)">2. Functions</button>
        <button onclick="loadModule(3)">3. Interfaces</button>
        <button onclick="loadModule(4)">4. Generics</button>
    </div>

    <div class="grid">
        <div>
            <div class="section-title">TypeScript Source Code</div>
            <textarea id="tsInput"></textarea>
        </div>
        <div>
            <div class="section-title">Execution Console Output</div>
            <pre id="consoleOutput">Click "Compile & Run" to execute code...</pre>
        </div>
    </div>

    <button onclick="compileAndRun()">▶ Compile & Run</button>
</div>

<script>
    // Bootcamp modules data
    const modules = {
        1: `// Module 1: Primitives & Type Inference
let courseName: string = "Browser TypeScript Bootcamp";
let studentCount = 42; 
let modules: string[] = ["Basics", "Functions", "Interfaces", "Generics"];

console.log("Welcome to " + courseName + "!");
console.log("Student count: " + studentCount);
console.log("Available modules: " + modules.join(", "));`,

        2: `// Module 2: Functions & Arrow Functions
const createUser = (name: string, role: string = "Developer", age?: number): string => {
  return "User: " + name + ", Role: " + role + (age ? ", Age: " + age : "");
};

console.log(createUser("Alice"));
console.log(createUser("Bob", "Architect", 30));`,

        3: `// Module 3: Interfaces
interface UserProfile {
  readonly id: string;
  username: string;
  email: string;
}

const user: UserProfile = {
  id: "USR-001",
  username: "code_master",
  email: "admin@bootcamp.test"
};

console.log("User Profile:", user.username, "(" + user.email + ")");`,

        4: `// Module 4: Generics
function wrapInArray<T>(item: T): T[] {
  return [item];
}

console.log(wrapInArray("Hello Generics"));
console.log(wrapInArray(500));`
    };

    function loadModule(id) {
        document.getElementById('tsInput').value = modules[id];
        document.getElementById('consoleOutput').textContent = "Loaded Module " + id + ". Click 'Compile & Run'.";
    }

    // Load module 1 by default on startup
    loadModule(1);

    function compileAndRun() {
        const tsCode = document.getElementById('tsInput').value;
        const outputElement = document.getElementById('consoleOutput');
        outputElement.textContent = "";

        try {
            // Compile TypeScript string to JavaScript using the inline ts compiler
            const transpiled = ts.transpileModule(tsCode, {
                compilerOptions: { 
                    target: ts.ScriptTarget.ES2022,
                    module: ts.ModuleKind.None 
                }
            });

            // Capture console.log outputs during execution
            const logs = [];
            const customConsole = {
                log: (...args) => logs.push(args.map(arg => 
                    typeof arg === 'object' ? JSON.stringify(arg, null, 2) : String(arg)
                ).join(' ')),
                error: (...args) => logs.push("[ERROR] " + args.join(' '))
            };

            // Execute the compiled JavaScript in a safe function wrapper
            const runCode = new Function('console', transpiled.outputText);
            runCode(customConsole);

            outputElement.textContent = logs.length > 0 ? logs.join('\n') : "Code executed successfully (no console output).";
        } catch (err) {
            outputElement.textContent = "Compilation/Runtime Error:\n" + err.message;
        }
    }
</script>

</body>
</html>
```

### How to use it:

1. Open **VS Code**, create a file named `index.html`, paste the code above, and save it.


2. Double-click the saved `index.html` file to open it in Chrome, Edge, Firefox, or Safari.


3. Click through the bootcamp modules (`1. Basics`, `2. Functions`, etc.) at the top, modify the code directly in the box, and hit **Compile & Run** to see real-time execution!

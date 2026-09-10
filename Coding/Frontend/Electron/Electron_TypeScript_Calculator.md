---
id: 20260909202645
title: Building a Desktop Calculator
author: Karl Schmitt
date: 2026-09-09
---

# From Beginner to Practical: Building a Calculator

Since you're working with a **C++ backend + Electron.js frontend**, a calculator is an excellent first Electron project. It lets you learn the important pieces without introducing too much complexity.

And yes: **Electron works very well with TypeScript**. For a new project, I'd recommend TypeScript.

## 🧮 Electron + TypeScript Calculator

We will build this architecture:

```text
┌─────────────────────────────────────────────┐
│              Electron Application           │
│                                             │
│  ┌───────────────────────────────────────┐  │
│  │        Renderer Process               │  │
│  │                                       │  │
│  │  ┌─────────────────────────────────┐  │  │
│  │  │       Calculator UI             │  │  │
│  │  │                                 │  │  │
│  │  │          123.45                 │  │  │
│  │  │                                 │  │  │
│  │  │   7   8   9   ÷                 │  │  │
│  │  │   4   5   6   ×                 │  │  │
│  │  │   1   2   3   −                 │  │  │
│  │  │   0   .   =   +                 │  │  │
│  │  └─────────────────────────────────┘  │  │
│  │                                       │  │
│  │          TypeScript / HTML / CSS      │  │
│  └───────────────────────────────────────┘  │
│                    │                        │
│                  IPC                       │
│                    │                        │
│  ┌─────────────────▼────────────────────┐  │
│  │          Main Process                │  │
│  │          TypeScript                  │  │
│  └──────────────────────────────────────┘  │
└─────────────────────────────────────────────┘
```

For our **first version**, however, we won't even need IPC. We'll keep the calculator logic in the renderer so you can concentrate on learning Electron itself.

***

# 1. What we are going to learn

By building this little calculator you'll encounter:

* Electron

* TypeScript

* `package.json`

* `tsconfig.json`

* Electron's **main process**

* Electron's **renderer process**

* `BrowserWindow`

* HTML

* CSS

* DOM manipulation

* TypeScript event handling

* npm

* TypeScript compilation

* Electron application startup

Later we can evolve it into:

```text
Calculator
    │
    ├── TypeScript
    │
    ├── Electron
    │
    ├── IPC
    │
    ├── C++ backend
    │
    └── C++ calculation engine
```

That would be particularly useful for your new work project.

***

# 2. Create the project

Since you're using **Windows 11 + PowerShell**, open PowerShell:

```powershell
mkdir electron-calculator
cd electron-calculator
```

Initialize npm:

```powershell
npm init -y
```

Install Electron:

```powershell
npm install --save-dev electron
```

Install TypeScript:

```powershell
npm install --save-dev typescript
```

Install Node.js type definitions:

```powershell
npm install --save-dev @types/node
```

Your project now looks roughly like:

```text
electron-calculator
│
├── node_modules
├── package-lock.json
└── package.json
```

***

# 3. Create the project structure

Create these directories:

```powershell
mkdir src
mkdir src\main
mkdir src\renderer
```

We will eventually have:

```text
electron-calculator
│
├── node_modules
│
├── src
│   │
│   ├── main
│   │   └── main.ts
│   │
│   └── renderer
│       ├── index.html
│       ├── calculator.ts
│       └── style.css
│
├── package.json
├── package-lock.json
└── tsconfig.json
```

This is already teaching us an important Electron concept:

```text
main
  │
  └── Electron application

renderer
  │
  └── User interface
```

***

# 4. Configure TypeScript

Create:

```text
tsconfig.json
```

with:

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "CommonJS",
    "strict": true,
    "outDir": "dist",
    "rootDir": "src",
    "esModuleInterop": true,
    "skipLibCheck": true
  },
  "include": [
    "src/**/*.ts"
  ]
}
```

The important part is:

```json
"rootDir": "src"
```

and:

```json
"outDir": "dist"
```

So TypeScript will transform:

```text
src/main/main.ts
```

into:

```text
dist/main/main.js
```

***

# 5. Configure package.json

Open `package.json`.

Change it to:

```json
{
  "name": "electron-calculator",
  "version": "1.0.0",
  "description": "Electron TypeScript Calculator",
  "main": "dist/main/main.js",
  "scripts": {
    "build": "tsc",
    "start": "npm run build && electron ."
  },
  "devDependencies": {
    "@types/node": "^24.0.0",
    "electron": "^38.0.0",
    "typescript": "^5.0.0"
  }
}
```

The important line is:

```json
"main": "dist/main/main.js"
```

It tells Electron:

> "This is the JavaScript file that starts my Electron application."

And:

```json
"start": "npm run build && electron ."
```

means:

```text
TypeScript
    ↓
tsc
    ↓
JavaScript
    ↓
Electron
    ↓
Application
```

***

# 6. Create the Electron main process

Create:

```text
src/main/main.ts
```

Put this inside:

```typescript
import { app, BrowserWindow } from "electron";
import path from "node:path";

function createWindow(): void {

    const window = new BrowserWindow({
        width: 400,
        height: 600,
        webPreferences: {
            contextIsolation: true,
            nodeIntegration: false
        }
    });

    window.loadFile(
        path.join(__dirname, "../renderer/index.html")
    );
}

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

This is our first real Electron code.

***

# 7. Understand `BrowserWindow`

This:

```typescript
const window = new BrowserWindow({
    width: 400,
    height: 600
});
```

creates an application window.

Conceptually:

```text
Electron
   │
   └── BrowserWindow
           │
           └── HTML page
```

Then:

```typescript
window.loadFile(...)
```

loads our HTML.

So Electron is essentially giving us:

```text
Desktop Window
      +
HTML
      +
CSS
      +
JavaScript / TypeScript
```

That's one of the reasons Electron is so interesting for web developers.

***

# 8. Create the HTML

Create:

```text
src/renderer/index.html
```

Use:

```html
<!DOCTYPE html>

<html lang="en">

<head>
    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    >

    <title>Calculator</title>

    <link rel="stylesheet" href="style.css">
</head>

<body>

    <main class="calculator">

        <input
            id="display"
            class="display"
            type="text"
            value="0"
            readonly
        >

        <section class="buttons">

            <button data-value="7">7</button>
            <button data-value="8">8</button>
            <button data-value="9">9</button>
            <button data-operation="/">÷</button>

            <button data-value="4">4</button>
            <button data-value="5">5</button>
            <button data-value="6">6</button>
            <button data-operation="*">×</button>

            <button data-value="1">1</button>
            <button data-value="2">2</button>
            <button data-value="3">3</button>
            <button data-operation="-">−</button>

            <button data-value="0">0</button>
            <button data-value=".">.</button>
            <button id="equals">=</button>
            <button data-operation="+">+</button>

            <button id="clear" class="clear">
                C
            </button>

        </section>

    </main>

    <script src="../../dist/renderer/calculator.js"></script>

</body>

</html>
```

***

# 9. Why `data-value`?

Look at:

```html
<button data-value="7">7</button>
```

We are attaching data to the HTML element.

For example:

```html
<button data-value="7">7</button>
<button data-value="8">8</button>
<button data-value="9">9</button>
```

TypeScript can later retrieve it:

```typescript
button.dataset.value
```

So:

```text
HTML
 │
 │ data-value="7"
 ▼
TypeScript
 │
 ▼
"7"
```

This is a very common technique in frontend development.

***

# 10. Create the CSS

Create:

```text
src/renderer/style.css
```

```css
* {
    box-sizing: border-box;
}

body {
    margin: 0;

    font-family:
        Arial,
        sans-serif;

    background: #222;

    display: flex;

    justify-content: center;
    align-items: center;

    min-height: 100vh;
}

.calculator {
    width: 320px;

    padding: 20px;

    background: #333;

    border-radius: 15px;
}

.display {
    width: 100%;

    height: 70px;

    margin-bottom: 15px;

    padding: 10px;

    font-size: 32px;

    text-align: right;
}

.buttons {
    display: grid;

    grid-template-columns:
        repeat(4, 1fr);

    gap: 10px;
}

button {
    height: 60px;

    font-size: 22px;

    border: none;

    border-radius: 8px;

    cursor: pointer;
}

button:hover {
    opacity: 0.8;
}

.clear {
    grid-column: span 4;
}
```

Now we have a proper calculator UI.

***

# 11. The interesting part: TypeScript

Create:

```text
src/renderer/calculator.ts
```

Start with:

```typescript
const display =
    document.getElementById("display")
    as HTMLInputElement;

const buttons =
    document.querySelectorAll<HTMLButtonElement>(
        "button"
    );

let firstNumber: number | null = null;

let operator: string | null = null;

let waitingForSecondNumber = false;
```

We now have three pieces of calculator state:

```text
firstNumber
operator
waitingForSecondNumber
```

For example, when the user enters:

```text
12 + 5
```

we might have:

```text
firstNumber = 12
operator = "+"
waitingForSecondNumber = true
```

***

# 12. Number buttons

Add:

```typescript
buttons.forEach((button) => {

    button.addEventListener("click", () => {

        const value = button.dataset.value;

        if (value !== undefined) {
            enterNumber(value);
        }
    });
});
```

And:

```typescript
function enterNumber(value: string): void {

    if (waitingForSecondNumber) {

        display.value = value;

        waitingForSecondNumber = false;

        return;
    }

    if (display.value === "0") {

        display.value = value;

    } else {

        display.value += value;
    }
}
```

Now clicking:

```text
7
8
9
```

will produce:

```text
789
```

on the display.

***

# 13. Operators

Add:

```typescript
document
    .querySelectorAll<HTMLButtonElement>(
        "[data-operation]"
    )
    .forEach((button) => {

        button.addEventListener("click", () => {

            const operation =
                button.dataset.operation;

            if (operation !== undefined) {

                setOperation(operation);
            }
        });
    });
```

Then:

```typescript
function setOperation(
    operation: string
): void {

    firstNumber = Number(display.value);

    operator = operation;

    waitingForSecondNumber = true;
}
```

Now if the user presses:

```text
12
+
```

we store:

```text
firstNumber = 12
operator = "+"
```

***

# 14. The equals button

Add:

```typescript
const equals =
    document.getElementById("equals");

equals?.addEventListener("click", calculate);
```

And:

```typescript
function calculate(): void {

    if (
        firstNumber === null ||
        operator === null
    ) {
        return;
    }

    const secondNumber =
        Number(display.value);

    let result: number;

    switch (operator) {

        case "+":
            result =
                firstNumber + secondNumber;
            break;

        case "-":
            result =
                firstNumber - secondNumber;
            break;

        case "*":
            result =
                firstNumber * secondNumber;
            break;

        case "/":

            if (secondNumber === 0) {

                display.value =
                    "Error";

                return;
            }

            result =
                firstNumber / secondNumber;

            break;

        default:
            return;
    }

    display.value =
        String(result);

    firstNumber = null;

    operator = null;

    waitingForSecondNumber = true;
}
```

And now we have a working calculator.

***

# 15. Clear button

Finally:

```typescript
const clear =
    document.getElementById("clear");

clear?.addEventListener("click", () => {

    display.value = "0";

    firstNumber = null;

    operator = null;

    waitingForSecondNumber = false;
});
```

***

# 16. Complete TypeScript

Your `calculator.ts` should now look like this:

```typescript
const display =
    document.getElementById("display")
    as HTMLInputElement;

const buttons =
    document.querySelectorAll<HTMLButtonElement>(
        "button"
    );

let firstNumber: number | null = null;

let operator: string | null = null;

let waitingForSecondNumber = false;


// Number buttons
buttons.forEach((button) => {

    button.addEventListener("click", () => {

        const value = button.dataset.value;

        if (value !== undefined) {
            enterNumber(value);
        }
    });
});


// Enter number
function enterNumber(value: string): void {

    if (waitingForSecondNumber) {

        display.value = value;

        waitingForSecondNumber = false;

        return;
    }

    if (display.value === "0") {

        display.value = value;

    } else {

        display.value += value;
    }
}


// Operator buttons
document
    .querySelectorAll<HTMLButtonElement>(
        "[data-operation]"
    )
    .forEach((button) => {

        button.addEventListener("click", () => {

            const operation =
                button.dataset.operation;

            if (operation !== undefined) {

                setOperation(operation);
            }
        });
    });


// Set operator
function setOperation(
    operation: string
): void {

    firstNumber = Number(display.value);

    operator = operation;

    waitingForSecondNumber = true;
}


// Equals button
const equals =
    document.getElementById("equals");

equals?.addEventListener(
    "click",
    calculate
);


// Calculate
function calculate(): void {

    if (
        firstNumber === null ||
        operator === null
    ) {
        return;
    }

    const secondNumber =
        Number(display.value);

    let result: number;

    switch (operator) {

        case "+":

            result =
                firstNumber + secondNumber;

            break;

        case "-":

            result =
                firstNumber - secondNumber;

            break;

        case "*":

            result =
                firstNumber * secondNumber;

            break;

        case "/":

            if (secondNumber === 0) {

                display.value =
                    "Error";

                return;
            }

            result =
                firstNumber / secondNumber;

            break;

        default:

            return;
    }

    display.value =
        String(result);

    firstNumber = null;

    operator = null;

    waitingForSecondNumber = true;
}


// Clear button
const clear =
    document.getElementById("clear");

clear?.addEventListener(
    "click",
    () => {

        display.value = "0";

        firstNumber = null;

        operator = null;

        waitingForSecondNumber = false;
    }
);
```

***

# 17. Build the application

From PowerShell:

```powershell
npm run build
```

TypeScript should create:

```text
dist
│
├── main
│   └── main.js
│
└── renderer
    └── calculator.js
```

Notice something interesting:

```text
src
 │
 ├── main
 │   └── main.ts
 │
 └── renderer
     └── calculator.ts

          │
          │ tsc
          ▼

dist
 │
 ├── main
 │   └── main.js
 │
 └── renderer
     └── calculator.js
```

TypeScript has transformed our `.ts` files into `.js`.

***

# 18. Start Electron

Now:

```powershell
npm start
```

Electron should open your calculator.

Try:

```text
7 + 5 =
```

Result:

```text
12
```

Try:

```text
100 / 4 =
```

Result:

```text
25
```

And:

```text
10 / 0 =
```

Result:

```text
Error
```

🎉 You have built your first **Electron + TypeScript desktop application**.

***

# 19. The important Electron architecture

There is a very important concept I'd like you to take away from this example.

Electron has two major worlds:

```text
                 ELECTRON
                    │
          ┌─────────┴─────────┐
          │                   │
          ▼                   ▼
       MAIN                 RENDERER
     PROCESS                PROCESS
          │                   │
          │                   │
          ▼                   ▼
    Electron APIs       HTML / CSS
    File system         TypeScript
    OS integration      User interface
    Windows             DOM
          │                   │
          └─────────┬─────────┘
                    │
                   IPC
```

For example:

### Main process

```typescript
new BrowserWindow(...)
```

is Electron functionality.

### Renderer process

```typescript
document.getElementById(...)
```

is browser functionality.

That's a fundamental distinction in Electron.

***

# 20. Why this is especially relevant to your new project

You mentioned that your new work project has:

```text
C++ backend
       +
Electron frontend
```

A very interesting next step would therefore be to evolve this calculator into:

```text
             Electron
                │
        ┌───────┴────────┐
        │                │
        ▼                ▼
     Renderer           Main
   TypeScript         TypeScript
        │                │
        │      IPC       │
        └───────►────────┘
                         │
                         │
                         ▼
                   C++ Backend
                         │
                         ▼
                  Calculation
```

That would teach you something much closer to your actual work environment:

**Electron → TypeScript → IPC → C++**

And that is a _very_ useful Electron learning project.

For your Zettelkasten, I'd give this tutorial the heading:

> **Electron.js + TypeScript: Building a Desktop Calculator**

or, if you want it to fit your other tutorial titles:

> **Electron.js + TypeScript — From Beginner to Practical: Building a Calculator**

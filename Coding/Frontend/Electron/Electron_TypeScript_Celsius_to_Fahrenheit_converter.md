---
id: 20260909204626
title: Converting Celsius to Fahrenheit
author: Karl Schmitt
date: 2026-09-09
---

# Celsius-to-Fahrenheit Conversion

😊 A **Celsius → Fahrenheit converter** is actually an even better first Electron + TypeScript exercise than the calculator because the application logic is very small. You can concentrate on understanding the **Electron architecture**.

We will build:

```text
Electron + TypeScript
        │
        ▼
┌──────────────────────┐
│   Celsius Converter  │
│                      │
│ Celsius: [  25  ]    │
│                      │
│       [ Convert ]    │
│                      │
│ Fahrenheit: 77 °F    │
└──────────────────────┘
```

The formula is:

```text
°F = (°C × 9 / 5) + 32
```

For example:

```text
25 °C
  │
  ▼
(25 × 9 / 5) + 32
  │
  ▼
77 °F
```

***

# 1. Project structure

Let's use the same structure as the calculator:

```text
electron-temperature-converter
│
├── node_modules
│
├── src
│   ├── main
│   │   └── main.ts
│   │
│   └── renderer
│       ├── index.html
│       ├── converter.ts
│       └── style.css
│
├── package.json
├── package-lock.json
└── tsconfig.json
```

The architecture is:

```text
                 Electron
                    │
             ┌──────┴──────┐
             │             │
             ▼             ▼
          Main          Renderer
        Process          Process
             │             │
        main.ts       HTML/CSS/TS
                           │
                           ▼
                    Temperature UI
```

***

# 2. Create the project

In **PowerShell**:

```powershell
mkdir electron-temperature-converter
cd electron-temperature-converter
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

Install Node.js types:

```powershell
npm install --save-dev @types/node
```

***

# 3. Create the directories

```powershell
mkdir src
mkdir src\main
mkdir src\renderer
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

This tells TypeScript:

```text
src/**/*.ts
     │
     │ tsc
     ▼
dist/**/*.js
```

***

# 5. Configure package.json

Change your `package.json` to:

```json
{
  "name": "electron-temperature-converter",
  "version": "1.0.0",
  "description": "Celsius to Fahrenheit converter using Electron and TypeScript",
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

Your actual installed versions may differ, which is fine.

***

# 6. Create the Electron main process

Create:

```text
src/main/main.ts
```

```typescript
import { app, BrowserWindow } from "electron";
import path from "node:path";

function createWindow(): void {

    const window = new BrowserWindow({
        width: 500,
        height: 450,

        webPreferences: {
            contextIsolation: true,
            nodeIntegration: false
        }
    });

    window.loadFile(
        path.join(
            __dirname,
            "../renderer/index.html"
        )
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

This is almost identical to our calculator.

The important Electron object is:

```typescript
BrowserWindow
```

which creates our desktop application window.

***

# 7. Create the HTML

Create:

```text
src/renderer/index.html
```

```html
<!DOCTYPE html>

<html lang="en">

<head>

    <meta charset="UTF-8">

    <meta
        name="viewport"
        content="width=device-width, initial-scale=1.0"
    >

    <title>Celsius to Fahrenheit</title>

    <link
        rel="stylesheet"
        href="style.css"
    >

</head>

<body>

    <main class="converter">

        <h1>🌡️ Temperature Converter</h1>

        <p>
            Celsius → Fahrenheit
        </p>

        <label for="celsius">
            Celsius
        </label>

        <input
            id="celsius"
            type="number"
            placeholder="Enter Celsius"
        >

        <button id="convert">
            Convert
        </button>

        <div class="result">

            <span>Fahrenheit:</span>

            <strong id="fahrenheit">
                —
            </strong>

        </div>

    </main>

    <script src="../../dist/renderer/converter.js"></script>

</body>

</html>
```

The important elements are:

```html
<input id="celsius">
```

and:

```html
<button id="convert">
    Convert
</button>
```

and:

```html
<strong id="fahrenheit">
    —
</strong>
```

Our TypeScript will interact with these elements.

***

# 8. Create the CSS

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

    min-height: 100vh;

    display: flex;

    justify-content: center;
    align-items: center;

    font-family: Arial, sans-serif;

    background: #222;
}

.converter {
    width: 400px;

    padding: 30px;

    background: white;

    border-radius: 15px;

    text-align: center;
}

h1 {
    margin-bottom: 10px;
}

label {
    display: block;

    margin-top: 25px;

    margin-bottom: 8px;
}

input {
    width: 100%;

    padding: 12px;

    font-size: 20px;

    text-align: center;
}

button {
    width: 100%;

    margin-top: 20px;

    padding: 12px;

    font-size: 18px;

    cursor: pointer;
}

.result {
    margin-top: 30px;

    font-size: 22px;
}

#fahrenheit {
    display: block;

    margin-top: 10px;

    font-size: 32px;
}
```

***

# 9. Now the TypeScript

This is the most interesting part.

Create:

```text
src/renderer/converter.ts
```

Start with:

```typescript
const celsiusInput =
    document.getElementById(
        "celsius"
    ) as HTMLInputElement;

const convertButton =
    document.getElementById(
        "convert"
    ) as HTMLButtonElement;

const fahrenheitOutput =
    document.getElementById(
        "fahrenheit"
    ) as HTMLElement;
```

We are getting references to the HTML elements.

Think of it like this:

```text
HTML

<input id="celsius">
       │
       │ getElementById()
       ▼
celsiusInput
       │
       ▼
TypeScript
```

***

# 10. Listen for the button click

Now:

```typescript
convertButton.addEventListener(
    "click",
    convertTemperature
);
```

This means:

> When the user clicks the Convert button, call `convertTemperature()`.

We can visualize it:

```text
User
 │
 │ clicks
 ▼
Convert button
 │
 │ "click"
 ▼
convertTemperature()
```

***

# 11. Implement the conversion

Add:

```typescript
function convertTemperature(): void {

    const celsius =
        Number(celsiusInput.value);

    const fahrenheit =
        (celsius * 9 / 5) + 32;

    fahrenheitOutput.textContent =
        `${fahrenheit} °F`;
}
```

And that's essentially the complete application.

***

# 12. Complete converter.ts

Your complete TypeScript file is:

```typescript
const celsiusInput =
    document.getElementById(
        "celsius"
    ) as HTMLInputElement;

const convertButton =
    document.getElementById(
        "convert"
    ) as HTMLButtonElement;

const fahrenheitOutput =
    document.getElementById(
        "fahrenheit"
    ) as HTMLElement;


convertButton.addEventListener(
    "click",
    convertTemperature
);


function convertTemperature(): void {

    const celsius =
        Number(celsiusInput.value);

    const fahrenheit =
        (celsius * 9 / 5) + 32;

    fahrenheitOutput.textContent =
        `${fahrenheit} °F`;
}
```

***

# 13. Build it

In PowerShell:

```powershell
npm run build
```

TypeScript creates:

```text
dist
│
├── main
│   └── main.js
│
└── renderer
    └── converter.js
```

So:

```text
converter.ts
     │
     │ TypeScript compiler
     ▼
converter.js
```

***

# 14. Run it

```powershell
npm start
```

Electron opens the application.

Enter:

```text
25
```

and click:

```text
Convert
```

You get:

```text
77 °F
```

Try:

```text
0
```

Result:

```text
32 °F
```

And:

```text
100
```

Result:

```text
212 °F
```

***

# 15. Let's understand the data flow

This tiny application is actually teaching you an important frontend concept.

When you enter:

```text
25
```

the data flows like this:

```text
┌────────────────────┐
│ HTML <input>       │
│                    │
│ value = "25"       │
└─────────┬──────────┘
          │
          │ .value
          ▼
┌────────────────────┐
│ TypeScript         │
│                    │
│ Number("25")       │
└─────────┬──────────┘
          │
          ▼
     celsius = 25
          │
          ▼
┌────────────────────┐
│ Calculation        │
│                    │
│ (25 × 9 / 5) + 32  │
└─────────┬──────────┘
          │
          ▼
     fahrenheit = 77
          │
          │ textContent
          ▼
┌────────────────────┐
│ HTML               │
│                    │
│ 77 °F              │
└────────────────────┘
```

That's a very nice first **Electron renderer-process exercise**.

***

# 16. One small TypeScript detail

This line:

```typescript
const celsius =
    Number(celsiusInput.value);
```

is interesting.

HTML input values are strings.

Even though you enter:

```text
25
```

JavaScript/TypeScript sees:

```typescript
"25"
```

not:

```typescript
25
```

Therefore we convert:

```typescript
Number("25")
```

into:

```typescript
25
```

This distinction becomes very important in JavaScript and TypeScript development.

***

# 17. A better version: validation

Our first implementation has a small problem.

What happens if the user clicks **Convert** without entering a value?

We should handle that.

Change the function to:

```typescript
function convertTemperature(): void {

    const input =
        celsiusInput.value.trim();

    if (input === "") {

        fahrenheitOutput.textContent =
            "Please enter a temperature.";

        return;
    }

    const celsius =
        Number(input);

    if (Number.isNaN(celsius)) {

        fahrenheitOutput.textContent =
            "Invalid temperature.";

        return;
    }

    const fahrenheit =
        (celsius * 9 / 5) + 32;

    fahrenheitOutput.textContent =
        `${fahrenheit} °F`;
}
```

Now our data flow becomes:

```text
                 Input
                   │
                   ▼
              Is it empty?
              /         \
            yes          no
            │             │
            ▼             ▼
          Error       Is it a number?
                       /       \
                     no         yes
                     │           │
                     ▼           ▼
                   Error      Calculate
                                  │
                                  ▼
                               Result
```

This is a much more realistic application pattern.

***

# 18. Even better: put the calculation in its own function

Here's another useful TypeScript lesson.

Instead of putting everything into `convertTemperature()`, we can separate the **business logic** from the **UI logic**.

```typescript
function celsiusToFahrenheit(
    celsius: number
): number {

    return (celsius * 9 / 5) + 32;
}
```

Then:

```typescript
function convertTemperature(): void {

    const input =
        celsiusInput.value.trim();

    if (input === "") {

        fahrenheitOutput.textContent =
            "Please enter a temperature.";

        return;
    }

    const celsius =
        Number(input);

    if (Number.isNaN(celsius)) {

        fahrenheitOutput.textContent =
            "Invalid temperature.";

        return;
    }

    const fahrenheit =
        celsiusToFahrenheit(celsius);

    fahrenheitOutput.textContent =
        `${fahrenheit} °F`;
}
```

Now we have a nice separation:

```text
┌───────────────────────────┐
│ UI                        │
│                           │
│ convertTemperature()      │
└─────────────┬─────────────┘
              │
              │ calls
              ▼
┌───────────────────────────┐
│ Business Logic            │
│                           │
│ celsiusToFahrenheit()     │
└───────────────────────────┘
```

And this function:

```typescript
function celsiusToFahrenheit(
    celsius: number
): number
```

could easily be unit-tested without Electron at all.

That's a very good habit to develop.

***

# 19. What you've learned

With this small project you have already touched several important concepts:

| Concept               | Example                  |
| --------------------- | ------------------------ |
| Electron              | `BrowserWindow`          |
| Electron main process | `main.ts`                |
| Renderer process      | `converter.ts`           |
| HTML                  | `<input>`                |
| CSS                   | `style.css`              |
| TypeScript            | `converter.ts`           |
| DOM                   | `getElementById()`       |
| Events                | `addEventListener()`     |
| Type conversion       | `Number()`               |
| Validation            | `Number.isNaN()`         |
| Functions             | `celsiusToFahrenheit()`  |
| Template strings      | `` `${fahrenheit} °F` `` |
| npm                   | `npm start`              |
| TypeScript compiler   | `tsc`                    |

And most importantly:

```text
Electron
   │
   ├── Main Process
   │
   │      main.ts
   │
   └── Renderer Process
          │
          ├── HTML
          ├── CSS
          └── TypeScript
```

## 🚀 A very useful next step

For your new **C++ backend + Electron frontend** project, I'd make the next exercise:

```text
Electron + TypeScript
        │
        ▼
Temperature Converter
        │
        │ IPC
        ▼
Electron Main Process
        │
        │
        ▼
C++ Backend
        │
        ▼
Celsius → Fahrenheit
```

That would take this very simple exercise and turn it into a miniature version of the architecture you're likely to encounter at work.

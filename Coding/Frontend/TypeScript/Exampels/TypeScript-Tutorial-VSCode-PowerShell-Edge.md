---
id: 20260917173149
title: Pure TypeScript 
author: Karl Schmitt
date: 2026-09-17
keywords: [TypeScript, VS Code, PowerShell, Edge]
---

> [NOTE!]
> Dieses Tutorial beschreibt eine Methode, um **TypeScript** ausschließlich mit **Visual Studio Code**, **PowerShell** und **Microsoft Edge** zu nutzen, ohne dabei Node.js oder Deno installieren zu müssen. Der Prozess nutzt einen **browserbasierten Compiler**, der TypeScript-Dateien zur Laufzeit direkt in ausführbares JavaScript umwandelt. Während **VS Code** die statische Typprüfung und Autovervollständigung übernimmt, dient die **PowerShell** zur effizienten Projektverwaltung und Dateierstellung. Der Leitfaden vermittelt **Kernkonzepte der Sprache**, wie Schnittstellen, Klassen und Generics, anhand praktischer Beispiele wie einer To-Do-Liste. Abschließend wird erläutert, wie Entwickler ihren Code direkt innerhalb der **Edge DevTools** untersuchen und Fehler beheben können.

# TypeScript Tutorial — Using Only VS Code, PowerShell, and Edge

A beginner-friendly TypeScript tutorial that requires **no Node.js and no Deno**. You write TypeScript in Visual Studio Code, orchestrate files from PowerShell, and compile + run everything inside Microsoft Edge using the **in-browser TypeScript compiler**.

> **Toolset for this tutorial**
> - **Editor:** Visual Studio Code
> - **Terminal / Shell:** PowerShell
> - **Runtime + Compiler:** Microsoft Edge (browser JS engine + the in-browser TypeScript compiler)
>
> **Not used:** Node.js, Deno, `npm`, or the `tsc` command-line tool.

---

## Table of Contents

1. [The Challenge: TypeScript Without Node.js](#1-the-challenge-typescript-without-nodejs)
2. [Setting Up Your Workspace with PowerShell](#2-setting-up-your-workspace-with-powershell)
3. [Configuring Visual Studio Code for TypeScript](#3-configuring-visual-studio-code-for-typescript)
4. [Your First TypeScript: Compile in the Browser](#4-your-first-typescript-compile-in-the-browser)
5. [Types: The Whole Point of TypeScript](#5-types-the-whole-point-of-typescript)
6. [Functions with Types](#6-functions-with-types)
7. [Interfaces and Type Aliases](#7-interfaces-and-type-aliases)
8. [Classes](#8-classes)
9. [Generics](#9-generics)
10. [Union Types, Narrowing, and Enums](#10-union-types-narrowing-and-enums)
11. [Typed DOM Interaction in Edge](#11-typed-dom-interaction-in-edge)
12. [A Small Project: Typed To-Do List](#12-a-small-project-typed-to-do-list)
13. [Debugging TypeScript in Edge DevTools](#13-debugging-typescript-in-edge-devtools)
14. [Next Steps](#14-next-steps)

---

## 1. The Challenge: TypeScript Without Node.js

TypeScript is normally compiled to JavaScript with the `tsc` command, which is installed through Node.js and `npm`. Since Node.js and Deno are off the table, we use a different, fully browser-based path.

The TypeScript team publishes a **standalone compiler** (`typescript.js`) that runs *inside the browser*. We load it from a CDN with a `<script>` tag, then hand it our TypeScript source and let it produce JavaScript that Edge runs immediately. No installation, no command line compiler, no runtime beyond the browser.

Two things still matter a lot and are covered here:

- **VS Code gives you full TypeScript type-checking as you type** — VS Code bundles the TypeScript language service, so you see errors, autocompletion, and type hints in the editor even without running anything. This is where TypeScript's real value shows up.
- **Edge compiles and runs the code** at page load using the in-browser compiler.

---

## 2. Setting Up Your Workspace with PowerShell

Open **PowerShell** (Windows key → type `PowerShell` → Enter).

```powershell
# Create a project folder
New-Item -ItemType Directory -Path "D:\CodingDojo\TsPractice" -Force

# Move into it
Set-Location "D:\CodingDojo\TsPractice"

# Confirm the location
Get-Location
```

Create the starter files:

```powershell
New-Item -ItemType File -Name "index.html" -Force
New-Item -ItemType File -Name "main.ts" -Force
New-Item -ItemType File -Name "tsconfig.json" -Force

Get-ChildItem
```

Open the folder in VS Code from PowerShell:

```powershell
code .
```

> If `code` is not recognized: open VS Code manually, press `Ctrl+Shift+P`, run **"Shell Command: Install 'code' command in PATH"**, then reopen PowerShell.

Launch a page in Microsoft Edge from PowerShell:

```powershell
Start-Process msedge "D:\CodingDojo\TsPractice\index.html"
```

---

## 3. Configuring Visual Studio Code for TypeScript

VS Code has **built-in TypeScript support** — no extension or Node.js required for type-checking in the editor.

**The `tsconfig.json`** tells VS Code how to interpret your TypeScript. Paste this into `tsconfig.json`:

```json
{
  "compilerOptions": {
    "target": "ES2020",
    "module": "ESNext",
    "strict": true,
    "noImplicitAny": true,
    "checkJs": false,
    "lib": ["ES2020", "DOM"]
  },
  "include": ["*.ts"]
}
```

With this file present, VS Code will:

- Underline type errors in red as you type.
- Offer autocompletion based on types.
- Show inline hints when you hover over variables and functions.

> **Important:** VS Code checks types purely in the editor using its bundled language service. It does **not** need `tsc` or Node.js installed to do this. The actual JavaScript output is produced later, in the browser.

**Useful shortcuts:**

| Action | Shortcut |
|---|---|
| Open integrated PowerShell terminal | `` Ctrl+` `` |
| Command Palette | `Ctrl+Shift+P` |
| Go to definition | `F12` |
| Show hover / type info | `Ctrl+K Ctrl+I` |
| Rename symbol | `F2` |

---

## 4. Your First TypeScript: Compile in the Browser

Put this in `index.html`. It loads the in-browser TypeScript compiler, reads your `main.ts`, compiles it to JavaScript, and runs it — all inside Edge.

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>TypeScript in the Browser</title>
</head>
<body>
  <h1>Open DevTools (F12) → Console</h1>

  <!-- 1. Load the standalone TypeScript compiler from a CDN -->
  <script src="https://cdnjs.cloudflare.com/ajax/libs/typescript/5.4.5/typescript.min.js"></script>

  <!-- 2. Fetch, compile, and run our TypeScript file -->
  <script>
    async function runTypeScript(file) {
      const source = await fetch(file).then(r => r.text());

      // Compile TypeScript → JavaScript in the browser
      const result = ts.transpileModule(source, {
        compilerOptions: {
          target: ts.ScriptTarget.ES2020,
          module: ts.ModuleKind.None
        }
      });

      // Execute the generated JavaScript
      const script = document.createElement("script");
      script.textContent = result.outputText;
      document.body.appendChild(script);
    }

    runTypeScript("main.ts");
  </script>
</body>
</html>
```

Put this in `main.ts`:

```typescript
const greeting: string = "Hello from TypeScript, compiled in Edge!";
console.log(greeting);
```

Open the page in Edge from PowerShell:

```powershell
Start-Process msedge "D:\CodingDojo\TsPractice\index.html"
```

Press `F12` in Edge, open the **Console**, and you'll see the greeting.

> **Note on `fetch` and local files:** Opening `index.html` directly (`file://`) may block `fetch` for security reasons in some cases. If the console shows a fetch/CORS error, use the free **Live Preview** extension in VS Code (right-click `index.html` → **"Show Preview"**), which serves the files over `http://localhost` and works perfectly. This still uses only VS Code and Edge — no Node.js.

---

## 5. Types: The Whole Point of TypeScript

Edit `main.ts` and reload Edge. Watch VS Code underline the mistakes *before* you even run the code.

### Basic Type Annotations

```typescript
let title: string = "TypeScript";
let count: number = 42;
let isActive: boolean = true;

// This line is flagged by VS Code as an error:
// count = "not a number"; // Type 'string' is not assignable to type 'number'
```

### Type Inference

TypeScript often figures out the type for you:

```typescript
let language = "TS";   // inferred as string
let version = 5.4;     // inferred as number

// language = 10;      // Error: number not assignable to string
```

### Arrays and Tuples

```typescript
let scores: number[] = [90, 85, 100];
let names: Array<string> = ["Ada", "Grace"];

// Tuple: fixed length, fixed types per position
let pair: [string, number] = ["age", 30];
```

### `any`, `unknown`, and `void`

```typescript
let flexible: any = "anything";   // disables type checking (avoid when possible)
let careful: unknown = 5;         // must be checked before use
function logMessage(msg: string): void {
  console.log(msg);               // returns nothing
}
```

---

## 6. Functions with Types

```typescript
// Parameter types and a return type
function add(a: number, b: number): number {
  return a + b;
}

// Arrow function with types
const multiply = (a: number, b: number): number => a * b;

// Optional parameter (?) and default value
function greet(name: string, greeting: string = "Hello"): string {
  return `${greeting}, ${name}!`;
}

console.log(add(2, 3));            // 5
console.log(greet("Edge"));       // Hello, Edge!
console.log(greet("Edge", "Hi")); // Hi, Edge!

// Function type as a variable
let operation: (x: number, y: number) => number;
operation = add;
console.log(operation(10, 5));    // 15
```

---

## 7. Interfaces and Type Aliases

Interfaces describe the shape of an object.

```typescript
interface Person {
  name: string;
  age: number;
  email?: string;      // optional
  readonly id: number; // cannot be changed after creation
}

const user: Person = {
  id: 1,
  name: "Linus",
  age: 30
};

// user.id = 2; // Error: id is readonly

function describe(p: Person): string {
  return `${p.name} is ${p.age} years old.`;
}

console.log(describe(user));
```

**Type aliases** do something similar and can also name unions and primitives:

```typescript
type ID = string | number;
type Point = { x: number; y: number };

const origin: Point = { x: 0, y: 0 };
let recordId: ID = "abc-123";
recordId = 456; // also valid
```

---

## 8. Classes

```typescript
class Animal {
  // Access modifiers: public (default), private, protected
  private name: string;
  protected legs: number;

  constructor(name: string, legs: number) {
    this.name = name;
    this.legs = legs;
  }

  describe(): string {
    return `${this.name} has ${this.legs} legs.`;
  }
}

// Inheritance
class Dog extends Animal {
  constructor(name: string) {
    super(name, 4);
  }

  speak(): string {
    return "Woof!";
  }
}

const rex = new Dog("Rex");
console.log(rex.describe()); // Rex has 4 legs.
console.log(rex.speak());    // Woof!
```

**Shorthand constructor** (parameter properties):

```typescript
class Point {
  // Declaring + assigning in the constructor signature
  constructor(public x: number, public y: number) {}

  distanceFromOrigin(): number {
    return Math.sqrt(this.x ** 2 + this.y ** 2);
  }
}

const p = new Point(3, 4);
console.log(p.distanceFromOrigin()); // 5
```

---

## 9. Generics

Generics let you write reusable, type-safe code that works with many types.

```typescript
// A function that returns whatever type it receives
function identity<T>(value: T): T {
  return value;
}

console.log(identity<string>("hello"));
console.log(identity<number>(42));

// A generic function that works on arrays
function firstElement<T>(arr: T[]): T | undefined {
  return arr[0];
}

console.log(firstElement([10, 20, 30])); // 10 (typed as number)
console.log(firstElement(["a", "b"]));   // "a" (typed as string)

// A generic interface
interface Box<T> {
  contents: T;
}

const stringBox: Box<string> = { contents: "books" };
const numberBox: Box<number> = { contents: 99 };
```

---

## 10. Union Types, Narrowing, and Enums

### Union Types

```typescript
function format(value: string | number): string {
  // Narrowing: TypeScript knows which branch is which type
  if (typeof value === "number") {
    return value.toFixed(2); // value is a number here
  }
  return value.toUpperCase(); // value is a string here
}

console.log(format(3.14159)); // "3.14"
console.log(format("hi"));    // "HI"
```

### Literal Types

```typescript
type Direction = "up" | "down" | "left" | "right";

function move(dir: Direction): void {
  console.log(`Moving ${dir}`);
}

move("up");
// move("sideways"); // Error: not a valid Direction
```

### Enums

```typescript
enum Status {
  Active,
  Inactive,
  Pending
}

let current: Status = Status.Active;
console.log(current);          // 0
console.log(Status[current]);  // "Active"
```

---

## 11. Typed DOM Interaction in Edge

TypeScript gives the DOM full type information (thanks to `"DOM"` in the `lib` setting).

Update `index.html` body (keep the two compiler scripts):

```html
<h1 id="title">Original</h1>
<button id="btn">Change Title</button>
<p id="output"></p>
```

Update `main.ts`:

```typescript
// Type assertions tell TS the specific element type
const title = document.getElementById("title") as HTMLHeadingElement;
const button = document.getElementById("btn") as HTMLButtonElement;
const output = document.getElementById("output") as HTMLParagraphElement;

button.addEventListener("click", (event: MouseEvent): void => {
  title.textContent = "Changed by TypeScript!";
  output.textContent = "Button was clicked.";
});
```

Reload in Edge and click the button. VS Code would have flagged, for example, calling a non-existent method on `title` before you ever ran the page.

---

## 12. A Small Project: Typed To-Do List

Set up files with PowerShell:

```powershell
Set-Location "D:\CodingDojo\TsPractice"
New-Item -ItemType File -Name "todo.html" -Force
New-Item -ItemType File -Name "todo.ts" -Force
```

`todo.html`:

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8" />
  <title>Typed To-Do</title>
  <style>
    body { font-family: sans-serif; max-width: 420px; margin: 40px auto; }
    li.done { text-decoration: line-through; color: gray; }
    input, button { font-size: 1rem; padding: 6px; }
  </style>
</head>
<body>
  <h1>To-Do List</h1>
  <input id="taskInput" type="text" placeholder="New task..." />
  <button id="addBtn">Add</button>
  <ul id="list"></ul>

  <script src="https://cdnjs.cloudflare.com/ajax/libs/typescript/5.4.5/typescript.min.js"></script>
  <script>
    async function runTypeScript(file) {
      const source = await fetch(file).then(r => r.text());
      const result = ts.transpileModule(source, {
        compilerOptions: {
          target: ts.ScriptTarget.ES2020,
          module: ts.ModuleKind.None
        }
      });
      const script = document.createElement("script");
      script.textContent = result.outputText;
      document.body.appendChild(script);
    }
    runTypeScript("todo.ts");
  </script>
</body>
</html>
```

`todo.ts`:

```typescript
// A typed model for a task
interface Task {
  id: number;
  text: string;
  done: boolean;
}

let tasks: Task[] = [];
let nextId = 1;

const input = document.getElementById("taskInput") as HTMLInputElement;
const addBtn = document.getElementById("addBtn") as HTMLButtonElement;
const list = document.getElementById("list") as HTMLUListElement;

function addTask(text: string): void {
  if (text.trim() === "") return;
  tasks.push({ id: nextId++, text: text.trim(), done: false });
  render();
}

function toggleTask(id: number): void {
  const task = tasks.find(t => t.id === id);
  if (task) task.done = !task.done;
  render();
}

function render(): void {
  list.innerHTML = "";
  tasks.forEach((task: Task) => {
    const li = document.createElement("li");
    li.textContent = task.text;
    if (task.done) li.classList.add("done");
    li.addEventListener("click", () => toggleTask(task.id));
    list.appendChild(li);
  });
}

addBtn.addEventListener("click", () => {
  addTask(input.value);
  input.value = "";
});

input.addEventListener("keydown", (e: KeyboardEvent) => {
  if (e.key === "Enter") {
    addTask(input.value);
    input.value = "";
  }
});
```

Open it in Edge:

```powershell
Start-Process msedge "D:\CodingDojo\TsPractice\todo.html"
```

Add tasks with the button or Enter key; click a task to toggle it done.

---

## 13. Debugging TypeScript in Edge DevTools

Because the browser compiles TypeScript to JavaScript at runtime, DevTools shows the **generated JavaScript** in the Sources tab. You can still debug effectively:

- **`console.log`** works exactly as in JavaScript:

  ```typescript
  console.log("tasks:", tasks);
  console.table(tasks);
  ```

- **`debugger` statement** pauses execution when DevTools is open:

  ```typescript
  function addTask(text: string): void {
    debugger; // Edge pauses here
    tasks.push({ id: nextId++, text, done: false });
    render();
  }
  ```

- **Breakpoints:** In Edge, `F12` → **Sources**. The injected script appears as a `<script>` under the page; click a line number to set a breakpoint, then use **Step over** (`F10`) and **Step into** (`F11`).

> **Where TypeScript catches most bugs:** in **VS Code**, before running. Red squiggles, hover types, and autocompletion catch type mismatches at edit time — that is the main safety net. The browser is only responsible for compiling and running.

---

## 14. Next Steps

You now have a complete, browser-only TypeScript workflow: **write and type-check in VS Code, manage files with PowerShell, compile and run in Edge** — with no Node.js or Deno.

Ideas to keep learning:

- **Stricter types:** explore `strictNullChecks`, `readonly` arrays, and `as const`.
- **Utility types:** `Partial<T>`, `Pick<T, K>`, `Record<K, V>`, `Omit<T, K>`.
- **Discriminated unions:** model state machines with a shared literal `kind` field.
- **`localStorage` with types:** persist the to-do list using `JSON.parse` and a typed cast.
- **Modules:** split code across `.ts` files and compile each with the in-browser compiler.

Reference documentation:

- **TypeScript Handbook:** <https://www.typescriptlang.org/docs/handbook/intro.html>
- **TypeScript Playground** (compiles in the browser, great for experiments): <https://www.typescriptlang.org/play>
- **MDN Web Docs:** <https://developer.mozilla.org/en-US/docs/Web/JavaScript>
- **Edge DevTools guide:** <https://learn.microsoft.com/en-us/microsoft-edge/devtools-guide-chromium/>

Happy typing — all inside VS Code, PowerShell, and Edge!

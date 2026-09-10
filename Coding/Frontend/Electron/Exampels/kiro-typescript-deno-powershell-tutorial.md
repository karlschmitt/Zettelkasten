---
id: 20260910151545
title: TypeScript with Deno on PowerShell
author: Karl Schmitt
date: 2026-09-10
keywords: [ PowerShell, TypeScript, Deno ]
---

# TypeScript with Deno on PowerShell — A Practical Tutorial

A hands-on guide to writing and running TypeScript using [Deno](https://deno.com) on Windows with PowerShell 7+. Deno runs TypeScript natively — no `tsc`, no `node_modules`, no build config required.

---

## Table of Contents

1. [Prerequisites](#1-prerequisites)
2. [Installing Deno](#2-installing-deno)
3. [Your First TypeScript Program](#3-your-first-typescript-program)
4. [Types in Action](#4-types-in-action)
5. [Modules and Imports](#5-modules-and-imports)
6. [The Permissions Model](#6-the-permissions-model)
7. [Reading Input and Files](#7-reading-input-and-files)
8. [Fetching Data from the Web](#8-fetching-data-from-the-web)
9. [Testing](#9-testing)
10. [Formatting, Linting, and Compiling](#10-formatting-linting-and-compiling)
11. [A Mini Project: CLI Word Counter](#11-a-mini-project-cli-word-counter)
12. [Next Steps](#12-next-steps)

---

## 1. Prerequisites

- Windows 10/11
- PowerShell 7+ (you have 7.6.5 — check with the command below)

```powershell
$PSVersionTable.PSVersion
```

No prior TypeScript or Node.js knowledge is required, though familiarity with JavaScript helps.

---

## 2. Installing Deno

Install Deno with the official PowerShell one-liner:

```powershell
irm https://deno.land/install.ps1 | iex
```

> `irm` is `Invoke-RestMethod` and `iex` is `Invoke-Expression`. This downloads the install script and runs it.

After installation, **open a new PowerShell window** (so the updated `PATH` is picked up), then verify:

```powershell
deno --version
```

You should see something like:

```
deno 2.x.x
v8 13.x.x
typescript 5.x.x
```

If `deno` is still not recognized, add it to your PATH manually for the current session:

```powershell
$env:Path += ";$HOME\.deno\bin"
```

To make it permanent for your user account:

```powershell
[Environment]::SetEnvironmentVariable(
    "Path",
    [Environment]::GetEnvironmentVariable("Path", "User") + ";$HOME\.deno\bin",
    "User"
)
```

---

## 3. Your First TypeScript Program

Create a working folder and a file:

```powershell
New-Item -ItemType Directory -Path "$HOME\deno-tutorial" -Force
Set-Location "$HOME\deno-tutorial"
```

Create `hello.ts`. You can use your editor, or write it from PowerShell:

```powershell
@'
const name: string = "world";
console.log(`Hello, ${name}!`);
'@ | Set-Content -Path hello.ts -Encoding utf8
```

Run it — Deno compiles and executes the TypeScript directly:

```powershell
deno run hello.ts
```

Output:

```
Hello, world!
```

No compilation step, no config file. That is the core Deno experience.

---

## 4. Types in Action

TypeScript adds static types on top of JavaScript. Create `types.ts`:

```typescript
// Primitive types
let count: number = 42;
let title: string = "TypeScript";
let isActive: boolean = true;

// Arrays
const scores: number[] = [90, 85, 77];

// Tuples — fixed-length, typed positions
const point: [number, number] = [10, 20];

// Interfaces describe object shapes
interface User {
  id: number;
  name: string;
  email?: string; // optional
}

const user: User = { id: 1, name: "Ada" };

// Union types
type Status = "active" | "inactive" | "pending";
let state: Status = "active";

// Functions with typed params and return
function greet(u: User): string {
  return `Hi ${u.name} (#${u.id})`;
}

console.log(greet(user));
console.log(`count=${count}, active=${isActive}, state=${state}`);
console.log(`scores total: ${scores.reduce((a, b) => a + b, 0)}`);
console.log(`point: ${point[0]},${point[1]}`);
```

Run it:

```powershell
deno run types.ts
```

Try introducing a type error — change `let state: Status = "active";` to `"archived"` and re-run. Deno reports the type error before executing:

```
error: TS2322 [ERROR]: Type '"archived"' is not assignable to type 'Status'.
```

---

## 5. Modules and Imports

Deno uses standard ES modules with explicit file extensions. Create `math.ts`:

```typescript
export function add(a: number, b: number): number {
  return a + b;
}

export function multiply(a: number, b: number): number {
  return a * b;
}

export const PI = 3.14159;
```

Create `main.ts` that imports it (note the `.ts` extension is required):

```typescript
import { add, multiply, PI } from "./math.ts";

console.log("2 + 3 =", add(2, 3));
console.log("4 * 5 =", multiply(4, 5));
console.log("PI =", PI);
```

Run:

```powershell
deno run main.ts
```

You can also import directly from URLs or the JSR/npm registries. Example using the Deno standard library:

```typescript
import { bold, green } from "jsr:@std/fmt/colors";

console.log(bold(green("Modules from a registry — no install step!")));
```

---

## 6. The Permissions Model

Deno is secure by default: scripts cannot access the file system, network, or environment unless you grant permission. This is a key difference from Node.js.

| Flag | Grants access to |
|------|------------------|
| `--allow-read` | File system reads |
| `--allow-write` | File system writes |
| `--allow-net` | Network |
| `--allow-env` | Environment variables |
| `--allow-run` | Running subprocesses |
| `-A` | Everything (use sparingly) |

Example — a script that reads an env var:

```typescript
// env.ts
const user = Deno.env.get("USERNAME") ?? "unknown";
console.log(`Running as: ${user}`);
```

Without permission it fails:

```powershell
deno run env.ts   # PermissionDenied
```

Grant only what is needed:

```powershell
deno run --allow-env env.ts
```

You can also scope permissions, e.g. `--allow-env=USERNAME` to allow just that one variable.

---

## 7. Reading Input and Files

Create `files.ts` to write and read a file:

```typescript
const path = "note.txt";

// Write
await Deno.writeTextFile(path, "Learning Deno with PowerShell.\n");

// Read
const contents = await Deno.readTextFile(path);
console.log("File says:", contents.trim());

// File info
const info = await Deno.stat(path);
console.log(`Size: ${info.size} bytes`);
```

Run with read and write permissions:

```powershell
deno run --allow-read --allow-write files.ts
```

---

## 8. Fetching Data from the Web

Deno implements the standard Web `fetch` API. Create `fetch.ts`:

```typescript
interface Todo {
  id: number;
  title: string;
  completed: boolean;
}

const res = await fetch("https://jsonplaceholder.typicode.com/todos/1");
const todo: Todo = await res.json();

console.log(`Todo #${todo.id}: ${todo.title}`);
console.log(`Completed: ${todo.completed}`);
```

Run with network permission:

```powershell
deno run --allow-net fetch.ts
```

---

## 9. Testing

Deno has a built-in test runner. Create `math_test.ts`:

```typescript
import { assertEquals } from "jsr:@std/assert";
import { add, multiply } from "./math.ts";

Deno.test("add sums two numbers", () => {
  assertEquals(add(2, 3), 5);
});

Deno.test("multiply multiplies two numbers", () => {
  assertEquals(multiply(4, 5), 20);
});
```

Run all tests in the folder:

```powershell
deno test
```

Output:

```
running 2 tests from ./math_test.ts
add sums two numbers ... ok
multiply multiplies two numbers ... ok

ok | 2 passed | 0 failed
```

---

## 10. Formatting, Linting, and Compiling

Deno ships with a formatter, linter, and compiler — no extra tooling.

Format all files in place:

```powershell
deno fmt
```

Lint for common problems:

```powershell
deno lint
```

Type-check without running:

```powershell
deno check main.ts
```

Compile to a standalone `.exe` (no Deno needed to run it):

```powershell
deno compile --allow-net --output fetcher.exe fetch.ts
.\fetcher.exe
```

---

## 11. A Mini Project: CLI Word Counter

Let's combine what you've learned. This reads a text file passed as an argument and reports word, line, and character counts.

Create `wc.ts`:

```typescript
// Usage: deno run --allow-read wc.ts <file>
function countStats(text: string): { lines: number; words: number; chars: number } {
  const lines = text.split(/\r\n|\r|\n/).length;
  const words = text.split(/\s+/).filter((w) => w.length > 0).length;
  const chars = text.length;
  return { lines, words, chars };
}

const file = Deno.args[0];

if (!file) {
  console.error("Usage: deno run --allow-read wc.ts <file>");
  Deno.exit(1);
}

const text = await Deno.readTextFile(file);
const stats = countStats(text);

console.log(`File:  ${file}`);
console.log(`Lines: ${stats.lines}`);
console.log(`Words: ${stats.words}`);
console.log(`Chars: ${stats.chars}`);
```

Create a sample file and run the tool:

```powershell
"The quick brown fox`njumps over the lazy dog" | Set-Content sample.txt -Encoding utf8
deno run --allow-read wc.ts sample.txt
```

Output:

```
File:  sample.txt
Lines: 3
Words: 9
Chars: 45
```

> Note: `Set-Content` appends a trailing newline, so splitting on line breaks yields 3 segments, and the trailing newline plus the ``` `n ``` escape add up to 45 characters. Exact counts depend on how the file is written.

You can also compile it into a reusable executable:

```powershell
deno compile --allow-read --output wc.exe wc.ts
.\wc.exe sample.txt
```

---

## 12. Next Steps

- **Standard Library** — explore [jsr.io/@std](https://jsr.io/@std) for HTTP servers, file utilities, and more.
- **`deno init`** — scaffold a new project: `deno init myproject`.
- **Config file** — use `deno.json` to define tasks, import maps, and compiler options.
- **npm compatibility** — import npm packages directly: `import express from "npm:express";`.
- **Web servers** — build an HTTP API with the built-in `Deno.serve`.

Quick reference of the commands used in this tutorial:

| Command | Purpose |
|---------|---------|
| `deno run <file>` | Run a TS/JS file |
| `deno test` | Run tests |
| `deno fmt` | Format code |
| `deno lint` | Lint code |
| `deno check <file>` | Type-check only |
| `deno compile <file>` | Build a standalone executable |
| `deno init` | Scaffold a new project |

Happy hacking with TypeScript and Deno on PowerShell!

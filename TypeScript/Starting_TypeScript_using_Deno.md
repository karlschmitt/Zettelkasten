---
id: 20260416214421
title: Starting TypeScript using Deno
date: 2026-04-16
keywords: [ TypeScript, Deno]
author: Karl Schmitt
---

# Starting TypeScript using Deno

Learning TypeScript with Deno is an excellent choice because Deno was built from the ground up to support TypeScript **natively**. Unlike Node.js, you don't need to install `tsc` (the TypeScript compiler), configure a complex `tsconfig.json`, or set up build pipelines like Webpack or Vite just to get started.

Here is a step-by-step guide to learning TypeScript using Deno.

---

### 1. Installation and Environment
First, install Deno and set up your editor.

*   **Install Deno:** Open your terminal and run:
    *   **macOS/Linux:** `curl -fsSL https://deno.land/install.sh | sh`
    *   **Windows (PowerShell):** `irm https://deno.land/install.ps1 | iex`
*   **Editor:** Download **Visual Studio Code**.
*   **Extension:** Install the **[Official Deno Extension](https://marketplace.visualstudio.com/items?itemName=denoland.vscode-deno)**. 
    *   *Crucial:* After installing, open your project folder, press `Ctrl+Shift+P`, and run **"Deno: Initialize Workspace Configuration"**. This tells VS Code to use Deno's engine instead of the default Node engine.

---

### 2. Your First TypeScript File
In Deno, you just create a `.ts` file and run it. No compilation step is required.

Create `hello.ts`:
```typescript
const greeting: string = "Hello, Deno!";

function sayHello(name: string): void {
  console.log(`${greeting} My name is ${name}.`);
}

sayHello("TypeScript Learner");
```

**Run it in your terminal:**
```bash
deno run hello.ts
```

---

### 3. Learn the Core TypeScript Concepts
Since Deno handles the "plumbing," you can focus entirely on the language syntax. Practice these three core pillars:

#### A. Type Annotations and Interfaces
Create a file `types.ts`:
```typescript
interface User {
  id: number;
  name: string;
  isAdmin: boolean;
}

const newUser: User = {
  id: 1,
  name: "Alice",
  isAdmin: true
};

console.log(newUser);
```

#### B. Working with Fetch (Async/Await)
Deno supports top-level `await`, making it great for learning how to handle API data types.
```typescript
interface Post {
  userId: number;
  id: number;
  title: string;
  body: string;
}

const response = await fetch("https://jsonplaceholder.typicode.com/posts/1");
const data: Post = await response.json();

console.log(data.title.toUpperCase());
```
*Note: Run this with permissions: `deno run --allow-net types.ts`*

---

### 4. Leverage Deno’s Built-in Tooling
One of the best ways to learn "Good" TypeScript is by using tools that enforce best practices. Deno includes these out of the box:

*   **Linter:** Run `deno lint`. It will tell you if you are using "bad" patterns (like using `any` too much).
*   **Formatter:** Run `deno fmt`. It automatically cleans up your code style.
*   **Documentation:** Run `deno doc hello.ts`. It generates documentation from your type definitions and comments.

---

### 5. Learning via Testing
A great way to learn TypeScript is to write small functions and test them. Deno has a built-in test runner.

Create `math_test.ts`:
```typescript
import { assertEquals } from "https://deno.land/std/assert/mod.ts";

function add(a: number, b: number): number {
  return a + b;
}

Deno.test("add function works", () => {
  const result = add(2, 3);
  assertEquals(result, 5);
});
```
**Run it:** `deno test`

---

### 6. Managing Dependencies (The Deno Way)
In Deno, there is no `node_modules`. You import modules directly via URLs or via `deno.json`. 

If you want to use a library (like the `Hono` web framework) to learn how types work in large libraries:
```typescript
import { Hono } from "npm:hono"; // Deno supports npm packages directly

const app = new Hono();

app.get("/", (c) => c.text("Hello TypeScript!"));

Deno.serve(app.fetch);
```

---

### Recommended Learning Path

1.  **The Basics:** Learn `string`, `number`, `boolean`, and `arrays`.
2.  **Functions:** Learn how to type parameters and return values.
3.  **Interfaces vs. Types:** Learn how to describe the shape of objects.
4.  **Generics:** This is the "Level 2" of TypeScript. Try writing a function that works with any type of array.
5.  **Deno Standard Library:** Browse the [Deno Standard Library](https://deno.land/std). Read the source code; it is written in very clean, high-quality TypeScript.

### Summary: Why this works
By using Deno, you remove the **configuration fatigue** that usually comes with TypeScript. You don't have to worry about `package.json`, `tsconfig.json`, `eslint.json`, or `prettierrc`. You just write code, and Deno tells you if your types are wrong.
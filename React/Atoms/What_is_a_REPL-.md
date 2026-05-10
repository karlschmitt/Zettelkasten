---
id: 20260510162114
title: What is a REPL?
author: Karl Schmitt
date: 2026-05-10
---

# What is a REP?

In the context of Deno and JavaScript, 
**REPL** stands for **Read-Eval-Print Loop**. 
It is an interactive programming environment that takes single user inputs, 
executes them, and returns the result to the user.

Think of it as a "scratchpad" where you can type code and see what happens immediately without having to create a file, save it, and run it through a terminal.

![scratchpad](../Images/small-scratchpad.png)

---

### 1. How it Works (The Loop)

![Loop](../Images/very-small-arrows-in-loop.png)

1.  **Read:** It reads the JavaScript or TypeScript code you type.
2.  **Eval:** It evaluates (executes) that code using the V8 engine.
3.  **Print:** It prints the result of that evaluation to your screen.
4.  **Loop:** It waits for your next line of code.

### 2. How to access it in Deno

![Deno](../Images/dino.png)

If you have Deno installed, you can enter the REPL by simply typing `deno` in your terminal:
```bash
$ deno
Deno 1.40.0
exit using ctrl+d, ctrl+c, or close()
> 
```
![Deno REPL 001](../Images/deno-repl-001.png)

### 3. Key Features of the Deno REPL
Deno’s REPL is significantly more powerful than the standard Node.js REPL or the browser console in several ways:

#### A. First-Class TypeScript Support
Unlike most other REPLs, you can type TypeScript directly into the Deno REPL. It will compile and run it on the fly.
```typescript
> const add = (a: number, b: number): number => a + b;
> add(5, 10)
15
```

#### B. Top-Level Await
In many environments, you have to wrap asynchronous code in an `async` function. In Deno’s REPL, you can use `await` directly at the prompt.
```typescript
> const response = await fetch("https://deno.land");
> response.status
200
```

#### C. Importing Modules
You can import external modules (via URLs) directly into the REPL session:
```typescript
> import { delay } from "https://deno.land/std/async/delay.ts";
> await delay(1000);
> console.log("Done!");
```

#### D. The "Underline" Variable (`_`)
Deno stores the result of the last evaluated expression in a special variable called `_`.
```typescript
> 10 + 20
30
> _ * 2
60
```

#### E. Built-in Help and Tab Completion
Deno provides excellent "IntelliSense" in the terminal. If you type `Deno.` and hit **Tab**, it will list all available methods. You can also use the `help()` command.

### 4. Why use a REPL?
*   **Prototyping:** Testing a small logic snippet or a regular expression before putting it into your main codebase.
*   **Learning:** Experimenting with new JavaScript features or Deno APIs.
*   **Debugging:** Checking the output of a specific function or an API response quickly.
*   **Calculator:** Using it as a high-powered mathematical calculator with access to the `Math` object.

### 5. How to Exit
To leave the REPL, you can:
*   Press `Ctrl + D` (EOF).
*   Press `Ctrl + C` twice.
*   Type `close()` or `exit()`.

### Summary
The Deno REPL is an **interactive terminal** that allows you to execute **JavaScript and TypeScript** instantly. It is unique because it supports **modern web standards** (like fetch), **top-level await**, and **direct URL imports** without any configuration.
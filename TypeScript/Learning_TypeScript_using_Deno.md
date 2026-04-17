---
id: 20260416213134
title: Learning TypeScript using Deno
date: 2016-04-16
keywords: [ TypeScript, Deno ]
author: Karl Schmitt
...

# Learning TypeScript using Deno

Learning **TypeScript with Deno** is actually one of the _best combinations_—because Deno has **first-class TypeScript support built in** (no setup, no transpilers, no bundlers needed 👍).

Here’s a clean, structured path you can follow (similar to your JavaScript bootcamp style):

***

# 🚀 Why Deno is perfect for TypeScript

* ✅ Runs `.ts` files **directly**

* ✅ No `tsconfig.json` needed (optional)

* ✅ Built-in tooling (formatter, linter, test runner)

* ✅ Secure by default

Example:

```bash
deno run hello.ts
```

***

# 🧠 Step 1: Learn the TypeScript Basics

Start with the core concepts:

### 1. Types

```ts
let name: string = "Karl";
let age: number = 30;
let isLearning: boolean = true;
```

### 2. Functions

```ts
function greet(name: string): string {
  return `Hello ${name}`;
}
```

### 3. Arrays & Objects

```ts
let numbers: number[] = [1, 2, 3];

let user: { name: string; age: number } = {
  name: "Karl",
  age: 30
};
```

👉 Run it:

```bash
deno run basics.ts
```

***

# 🛠️ Step 2: Use Deno Like a Learning Playground

Deno is perfect for experimentation:

### Watch mode (auto-reload)

```bash
deno run --watch app.ts
```

### Permissions (important concept!)

```bash
deno run --allow-read app.ts
```

***

# 🧩 Step 3: Learn Intermediate TypeScript

### Interfaces

```ts
interface User {
  name: string;
  age: number;
}

const user: User = { name: "Karl", age: 30 };
```

### Union Types

```ts
let id: string | number;
id = "abc";
id = 123;
```

### Type Inference

```ts
let message = "Hello"; // TypeScript infers string
```

***

# 📦 Step 4: Work with Modules (Deno Style)

Deno uses **URL imports** instead of npm:

```ts
import { serve } from "https://deno.land/std/http/server.ts";

serve(() => new Response("Hello World"));
```

Run:

```bash
deno run --allow-net server.ts
```

***

# 🧪 Step 5: Testing with Deno

Deno has a built-in test runner:

```ts
import { assertEquals } from "https://deno.land/std/testing/asserts.ts";

Deno.test("adds numbers", () => {
  assertEquals(1 + 2, 3);
});
```

Run:

```bash
deno test
```

***

# 🧹 Step 6: Format & Lint

```bash
deno fmt
deno lint
```

***

# 📅 Suggested 7-Day Learning Plan

### Day 1–2: Basics

* Types, variables, functions

### Day 3: Objects & Arrays

* Practice modeling data

### Day 4: Interfaces & Types

* Create reusable structures

### Day 5: Modules & Imports

* Build small multi-file apps

### Day 6: APIs

* Create a small HTTP server

### Day 7: Testing + Mini Project

* Build a CLI tool or simple API

***

# 💡 Mini Project Ideas (Perfect for You)

Since you're doing a **Zettelkasten + Bootcamp approach**, try:

* 📒 CLI note tool (`deno run notes.ts`)

* 🔍 File search tool (PowerShell alternative in TS)

* 🌐 Simple REST API

* 🧮 Calculator CLI

***

# ⚡ Example Mini CLI Tool

```ts
const args = Deno.args;

if (args.length === 0) {
  console.log("Please provide a name");
} else {
  console.log(`Hello ${args[0]}`);
}
```

Run:

```bash
deno run cli.ts Karl
```

***

# 🧭 How to Think While Learning

Since you're already learning:

* JavaScript ✅

* PowerShell ✅

* Zettelkasten method ✅

👉 Combine them:

* Write **small `.ts` scripts daily**

* Document each concept in your notes

* Refactor JS → TS (great exercise!)

***

# 🎯 Key Mindset Shift

TypeScript is:

> **JavaScript + Types + Safety**

Deno removes complexity so you can focus purely on learning.

***

If you want, I can build you a **Week 1 + Week 2 TypeScript bootcamp (just like your JavaScript one)** tailored to Deno 👍

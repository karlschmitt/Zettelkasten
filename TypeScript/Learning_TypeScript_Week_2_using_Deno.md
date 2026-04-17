---
id: 20260416215853
title: Learning TypeScript Week Two  using Deno
date: 2026-04-16
keywords: [ TypeScript, Deno ]
author: Karl Schmitt
---

# Learning TypeScript Week Two using Deno

Nice—Week 1 done ✅\
Now we level up: **real-world TypeScript with Deno**.

***

# 📅 Week 2 — TypeScript with Deno (Real Usage)

## 🎯 Goal of Week 2

By the end, you will:

* Work with **modules & imports**

* Use **Deno permissions**

* Read/write **files**

* Build **real CLI tools**

* Understand how Deno replaces many PowerShell tasks

***

# 🧠 Day 8 — Modules (Deno Style)

### ✅ What to learn

* Splitting code into files

* Import/export

### 🧪 Exercise

**math.ts**

```ts
export function add(a: number, b: number): number {
  return a + b;
}
```

**app.ts**

```ts
import { add } from "./math.ts";

console.log(add(2, 3));
```

Run:

```bash
deno run app.ts
```

***

### 💡 Insight

Unlike Node.js:

* You must include `.ts`

* No `require()`, only `import`

***

# 🧠 Day 9 — Deno Permissions 🔐

### ✅ What to learn

Deno is secure by default!

### 🧪 Example

```ts
const text = await Deno.readTextFile("data.txt");
console.log(text);
```

Run:

```bash
deno run --allow-read app.ts
```

***

### 🔑 Common Permissions

* `--allow-read`

* `--allow-write`

* `--allow-net`

***

### 💡 Think like this:

> “My script must ask for permission to act.”

***

# 🧠 Day 10 — Working with Files

### ✅ What to learn

* Read/write files

### 🧪 Exercise

```ts
await Deno.writeTextFile("note.txt", "Hello Zettelkasten!");
```

```ts
const content = await Deno.readTextFile("note.txt");
console.log(content);
```

Run:

```bash
deno run --allow-read --allow-write app.ts
```

***

### 🔁 Challenge

* Append text to a file

* Create multiple notes

***

# 🧠 Day 11 — CLI Arguments (Advanced)

You already used:

```ts
Deno.args
```

### 🧪 Build a smarter CLI

```ts
const [command, value] = Deno.args;

if (command === "greet") {
  console.log(`Hello ${value}`);
} else {
  console.log("Unknown command");
}
```

Run:

```bash
deno run app.ts greet Karl
```

***

# 🧠 Day 12 — Fetch API (HTTP Requests)

### ✅ What to learn

* Call APIs (like curl / PowerShell)

### 🧪 Example

```ts
const res = await fetch("https://api.github.com/users/denoland");
const data = await res.json();

console.log(data.login);
```

Run:

```bash
deno run --allow-net app.ts
```

***

### 💡 Insight

Deno has `fetch()` built-in (like browser JS)

***

# 🧠 Day 13 — Build a Real Tool 🛠️

## 🧩 Project: File Search Tool (PowerShell Alternative)

👉 This fits PERFECTLY with your previous PowerShell work

### 🧪 Example

```ts
for await (const entry of Deno.readDir(".")) {
  if (entry.isFile && entry.name.endsWith(".ts")) {
    console.log(entry.name);
  }
}
```

Run:

```bash
deno run --allow-read search.ts
```

***

### 🔁 Challenge

* Search for `.txt` files

* Filter by keyword

***

# 🧠 Day 14 — Mini Project 🚀

## 🛠️ Build: Zettelkasten CLI Tool

### Features:

* Add note

* Read notes

***

### 🧪 Example

```ts
const [command, title, content] = Deno.args;

if (command === "add") {
  await Deno.writeTextFile(`${title}.txt`, content);
  console.log("Note added");
}

if (command === "read") {
  const text = await Deno.readTextFile(`${title}.txt`);
  console.log(text);
}
```

Run:

```bash
deno run --allow-read --allow-write notes.ts add mynote "Hello World"
deno run --allow-read notes.ts read mynote
```

***

# 📌 Weekly Summary

You now know:

* ✅ Modules (`import/export`)

* ✅ Permissions (security model)

* ✅ File system access

* ✅ HTTP requests

* ✅ CLI tools

* ✅ Real-world scripting

***

# 🧭 How This Connects to YOUR Learning

You already worked with:

* PowerShell 🔧

* File search 🔍

* Zettelkasten 📒

👉 Now you can **replace PowerShell scripts with TypeScript**

***

# 🧱 Suggested Folder Structure

```bash
deno-project/
├── src/
│   ├── app.ts
│   ├── math.ts
│   └── search.ts
├── notes/
└── README.md
```

***

# ⚡ What Comes in Week 3 (if you want)

* Testing (`deno test`)

* Formatting & linting

* Building APIs (server)

* Better project structure

* External libraries

***

If you want next:\
👉 I can guide you **Day 8 interactively (like a tutor)**\
👉 Or build **Week 3 (Advanced Deno + real apps)**


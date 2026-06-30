---
id: 20260416215435
title: Learning TypeScript Week One using Deno
date: 2026-04-16
keywords: [ TypeScript, Deno]
author: Karl Schmitt
---

# Learning TypeScript Week One using Deno


Great—let’s build your **Week 1 TypeScript Bootcamp with Deno** 👨‍💻\
Focused, practical, and aligned with how you’ve been learning (small steps + Zettelkasten).

***

# 📅 Week 1 — TypeScript with Deno (Foundations)

## 🎯 Goal of Week 1

By the end, you will:

* Understand **basic TypeScript types**

* Run `.ts` files with Deno

* Build small scripts confidently

* Start thinking in **typed JavaScript**

***

# 🧠 Day 1 — Your First TypeScript with Deno

### ✅ What to learn

* Running `.ts` files

* Basic types (`string`, `number`, `boolean`)

### 🧪 Exercise

Create `hello.ts`:

```ts
let name: string = "Karl";
let age: number = 30;

console.log(`Hello ${name}, age ${age}`);
```

Run:

```bash
deno run hello.ts
```

### 💡 Zettelkasten Note Idea

* “TypeScript basic types”

* Example + explanation in your own words

***

# 🧠 Day 2 — Functions

### ✅ What to learn

* Typed parameters

* Return types

### 🧪 Exercise

```ts
function add(a: number, b: number): number {
  return a + b;
}

console.log(add(2, 3));
```

👉 Try breaking it:

```ts
add("2", 3); // ❌ Type error
```

### 💡 Insight

TypeScript helps you **catch errors early**

***

# 🧠 Day 3 — Arrays & Loops

### ✅ What to learn

* Typed arrays

* Loops

### 🧪 Exercise

```ts
let numbers: number[] = [1, 2, 3, 4];

for (const num of numbers) {
  console.log(num * 2);
}
```

### 🔁 Challenge

* Create an array of strings

* Print each in uppercase

***

# 🧠 Day 4 — Objects

### ✅ What to learn

* Object types

### 🧪 Exercise

```ts
let user: { name: string; age: number } = {
  name: "Karl",
  age: 30
};

console.log(user.name);
```

### 🔁 Challenge

Add a new property:

```ts
email: string
```

***

# 🧠 Day 5 — Interfaces (Very Important!)

### ✅ What to learn

* Reusable types

### 🧪 Exercise

```ts
interface User {
  name: string;
  age: number;
}

const user: User = {
  name: "Karl",
  age: 30
};
```

### 💡 Insight

Interfaces = **blueprints for objects**

***

# 🧠 Day 6 — Union Types & Flexibility

### ✅ What to learn

* Multiple possible types

### 🧪 Exercise

```ts
let id: string | number;

id = "abc";
id = 123;
```

### 🔁 Challenge

Create:

```ts
status: "success" | "error"
```

***

# 🧠 Day 7 — Mini Project 🚀

## 🛠️ Build: Simple CLI Greeting Tool

Create `greet.ts`:

```ts
const args: string[] = Deno.args;

if (args.length === 0) {
  console.log("Please provide a name");
} else {
  const name: string = args[0];
  console.log(`Hello ${name}!`);
}
```

Run:

```bash
deno run greet.ts Karl
```

***

# 🧪 Bonus (Optional if you feel strong)

Add:

* Age input

* Validation

***

# 📌 Weekly Summary

You now know:

* ✅ Types

* ✅ Functions

* ✅ Arrays

* ✅ Objects

* ✅ Interfaces

* ✅ Basic CLI scripting

***

# 🧭 Daily Routine (Your Learning System)

Each day:

1. Write code (10–20 min)

2. Break something intentionally 😄

3. Fix it

4. Write a **Zettelkasten note**

***

# 🧱 Suggested Zettelkasten Structure

```
TypeScript/
├── Basics/
│   ├── types.md
│   ├── functions.md
│   ├── arrays.md
│   └── objects.md
```

***

# ⚡ What Comes in Week 2

If you continue, Week 2 will cover:

* Modules (Deno imports)

* File system access

* Permissions (`--allow-read`)

* Real tools (like your PowerShell replacements)

***

If you want, I can:\
👉 Turn this into a **printable checklist**\
👉 Or guide you **day-by-day interactively** (like a real bootcamp)

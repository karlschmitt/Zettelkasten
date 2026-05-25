---
id: 20260413230534 
title: A 7-day JavaScript Bootcamp using Deno
date: 2026-04-16
keywords [ JavaScript, Bootcamp, Deno ]
---

# A 7-day JavaScript Bootcamp using Deno

Perfect—this fits _exactly_ with how you’ve been learning (Deno + Zettelkasten + small experiments).\
Here’s a **focused 7-day JavaScript bootcamp using Deno**—designed to be practical, short, and repeatable.

***

# 🚀 7-Day JavaScript Bootcamp (Deno Edition)

## 🧭 Structure (same every day)

* ⏱️ ~30–45 minutes

* 🔁 Loop:

  1. Learn concept

  2. Try in `deno repl`

  3. Write small `.js` file

  4. Save notes (Zettelkasten)

***

# 📅 Day 1 — Primitive Types (Foundation)

## 🎯 Goal

Understand all primitive types + `typeof`

## 🔬 REPL Practice

```js
typeof "hello"
typeof 42
typeof true
typeof undefined
typeof null
typeof 123n
typeof Symbol("id")
```

## 🛠️ Mini Project

```js
// day1-types.js
const values = ["text", 123, true, null, undefined];

for (const v of values) {
  console.log(v, "=>", typeof v);
}
```

Run:

```bash
deno run day1-types.js
```

## 🧠 Note

* `typeof null === "object"` ❗

***

# 📅 Day 2 — Variables & Assignment

## 🎯 Goal

Learn `let`, `const`, and reassignment

## 🔬 REPL

```js
let x = 10
x = 20

const y = 5
// y = 10 ❌ error
```

## 🛠️ Mini Project

```js
// day2-variables.js
let name = "Karl";
let age = 30;

age = age + 1;

console.log(name, age);
```

## 🧠 Note

* Use `const` by default

* Use `let` if value changes

***

# 📅 Day 3 — Operators & Type Coercion

## 🎯 Goal

Understand JavaScript’s weird conversions

## 🔬 REPL

```js
"5" + 1
"5" - 1
true + 1
null + 1
undefined + 1
```

## 🛠️ Mini Project

```js
// day3-coercion.js
const tests = [
  "5" + 1,
  "5" - 1,
  true + 1,
  null + 1,
  undefined + 1
];

console.log(tests);
```

## 🧠 Note

* `+` → string concatenation if string involved

* Other operators → numeric conversion

***

# 📅 Day 4 — Equality & Comparisons

## 🎯 Goal

Master `==` vs `===`

## 🔬 REPL

```js
5 == "5"
5 === "5"

null == undefined
null === undefined
```

## 🛠️ Mini Project

```js
// day4-equality.js
const pairs = [
  [5, "5"],
  [null, undefined],
  [true, 1]
];

for (const [a, b] of pairs) {
  console.log(a, b, "==", a == b);
  console.log(a, b, "===", a === b);
}
```

## 🧠 Rule

👉 Always use `===`

***

# 📅 Day 5 — Conditionals

## 🎯 Goal

Use `if`, `else`, truthy/falsy

## 🔬 REPL

```js
if ("hello") console.log("truthy")
if (0) console.log("won't run")
```

## 🛠️ Mini Project

```js
// day5-conditions.js
let value = 0;

if (value) {
  console.log("Truthy");
} else {
  console.log("Falsy");
}
```

## 🧠 Falsy values

* `false`, `0`, `""`, `null`, `undefined`, `NaN`

***

# 📅 Day 6 — Functions (Core Skill)

## 🎯 Goal

Write reusable code

## 🔬 REPL

```js
function add(a, b) {
  return a + b;
}

add(2, 3);
```

## 🛠️ Mini Project

```js
// day6-functions.js
function describe(value) {
  return `${value} is of type ${typeof value}`;
}

console.log(describe(42));
console.log(describe("hello"));
```

***

# 📅 Day 7 — Mini Project (Bring it all together)

## 🎯 Goal

Combine everything

## 🛠️ Project: Type Analyzer

```js
// day7-project.js
function analyze(value) {
  return {
    value: value,
    type: typeof value,
    isTruthy: Boolean(value)
  };
}

const inputs = [0, 1, "hello", "", null, undefined];

for (const input of inputs) {
  console.log(analyze(input));
}
```

Run:

```bash
deno run day7-project.js
```

***

# 🧠 Bonus: Daily Zettelkasten Template

Use this every day:

```
JavaScript / Day X / Topic

Concept:
- 

Examples:
- 

Weird things:
- 

Rules:
- 
```

***

# ⚡ After These 7 Days

You’ll understand:

* Primitive types ✅

* Type coercion ✅

* Equality pitfalls ✅

* Basic logic ✅

* Functions ✅

👉 That’s already **strong beginner level**

***

# 🚀 Next Step (if you want)

I can guide you into:

* **Week 2:** Arrays, Objects, Loops

* **Week 3:** Async (fetch, APIs with Deno)

* **Real Project:** CLI tool using Deno

Just tell me 👍

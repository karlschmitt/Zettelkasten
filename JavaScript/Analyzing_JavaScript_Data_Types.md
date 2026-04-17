---
id: 20260415194808
title: Analyzing JavaScript Data Types
date: 2026-04-15
---

# Analyzing JavaScript Data Types

Great question—this is exactly the kind of hands-on exploration that makes JavaScript “click,” especially with **Deno** 👍

Let’s walk through a **practical, beginner-friendly way to analyze JavaScript data types using Deno**.

***

# 🚀 1. Quick Setup (Deno)

If you haven’t already:

```bash
deno --version
```

Run a script:

```bash
deno run app.js
```

***

# 🔍 2. Core Idea: Inspecting Data Types

In JavaScript (and Deno), you mainly use:

* `typeof` → quick type check

* `Array.isArray()` → detect arrays

* `instanceof` → check object types

* `Object.prototype.toString.call()` → deep inspection

***

# 🧪 3. Your First Data Type Analyzer

Create a file:

```bash
touch analyze.js
```

### Example:

```js
const values = [
  "Hello",
  42,
  3.14,
  true,
  null,
  undefined,
  [1, 2, 3],
  { name: "Karl" },
  function () {},
  Symbol("id"),
  BigInt(123)
];

for (const value of values) {
  console.log("Value:", value);
  console.log("typeof:", typeof value);
  console.log("isArray:", Array.isArray(value));
  console.log(
    "toString:",
    Object.prototype.toString.call(value)
  );
  console.log("----------------------");
}
```

Run it:

```bash
deno run analyze.js
```

***

# 🧠 4. Understanding the Output

### `typeof` quirks:

```js
typeof null // ❌ "object" (this is a known JS bug)
typeof []   // ❌ "object"
```

So you need better tools 👇

***

# 🧰 5. Build a Better Type Detector

```js
function getType(value) {
  if (value === null) return "null";
  if (Array.isArray(value)) return "array";
  return typeof value;
}
```

### Usage:

```js
for (const value of values) {
  console.log(getType(value));
}
```

***

# 🔬 6. Deep Inspection Utility (Pro Level)

```js
function analyze(value) {
  return {
    value,
    type: typeof value,
    isArray: Array.isArray(value),
    isNull: value === null,
    isObject: typeof value === "object" && value !== null,
    constructor: value?.constructor?.name,
    tag: Object.prototype.toString.call(value)
  };
}

console.dir(values.map(analyze), { depth: null });
```

***

# 📊 7. Pretty Output in Deno

Deno supports `console.table()`:

```js
console.table(values.map(v => ({
  value: String(v),
  type: typeof v
})));
```

***

# ⚡ 8. Bonus: Use Deno REPL for Exploration

Run:

```bash
deno repl
```

Then try:

```js
typeof "hello"
typeof 123
typeof null
Array.isArray([1,2,3])
```

This is the **fastest way to learn** 🔥

***

# 🧭 9. What You Should Practice

Try analyzing:

* Nested objects

* Arrays of objects

* Functions vs arrow functions

* Dates:

```js
new Date()
```

***

# 🧩 10. Mini Challenge

Write a function that returns:

```js
getDetailedType([1,2,3])
// → "array"

getDetailedType(null)
// → "null"

getDetailedType(new Date())
// → "date"
```

***

# 💡 Key Takeaway

In JavaScript (and Deno):

* `typeof` → basic but imperfect

* `Array.isArray()` → for arrays

* `Object.prototype.toString` → most reliable

* Custom functions → best practice

***

If you want, I can turn this into a **small CLI tool in Deno** (like `deno run inspect.js file.json`) so you can analyze real data files 👍

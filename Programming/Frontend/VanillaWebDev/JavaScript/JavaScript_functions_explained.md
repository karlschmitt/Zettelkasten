---
id: 20260415201418 
title: JavaScript function explained
subtitle: Lerning the JavaScript function concept using Deno.
abstract: Explaining the function keyword, and the use of functions in JavaScript.
keywords: [ JavaScript, Deno, function keyword ]
date: 2026-04-15
---

# JavaScript functions explained

Absolutely—functions are one of the most important building blocks in JavaScript, and **Deno** is a great environment to explore them hands-on.

Let’s go step by step with **clear examples you can run immediately**.

***

# 🚀 1. What is a Function?

A function is a **reusable block of code**.

### Basic example:

```js
function greet() {
  console.log("Hello, Karl!");
}

greet();
```

Run it:

```bash
deno run app.js
```

***

# 🧱 2. Functions with Parameters

You can pass data into functions:

```js
function greet(name) {
  console.log("Hello, " + name + "!");
}

greet("Karl");
greet("Alice");
```

***

# 🔁 3. Functions that Return Values

Functions can give something back:

```js
function add(a, b) {
  return a + b;
}

const result = add(2, 3);
console.log(result); // 5
```

***

# ⚡ 4. Arrow Functions (Modern JavaScript)

Shorter syntax:

```js
const add = (a, b) => {
  return a + b;
};
```

Even shorter:

```js
const add = (a, b) => a + b;
```

***

# 🧪 5. Try It in Deno REPL

Start:

```bash
deno repl
```

Then experiment:

```js
const square = x => x * x;
square(5);
```

***

# 🧠 6. Functions Are “First-Class Citizens”

This is a big concept in JavaScript:

👉 Functions can be:

* stored in variables

* passed as arguments

* returned from other functions

### Example:

```js
function sayHello() {
  return "Hello!";
}

function run(fn) {
  console.log(fn());
}

run(sayHello);
```

***

# 🔄 7. Callback Functions

Functions passed into other functions:

```js
function processUser(name, callback) {
  console.log("Processing:", name);
  callback(name);
}

processUser("Karl", (name) => {
  console.log("Done with", name);
});
```

***

# ⏳ 8. Async Functions (Very Important in Deno)

Deno is built for async work (like APIs, files).

```js
async function fetchData() {
  const res = await fetch("https://swapi.dev/api/people/1");
  const data = await res.json();
  console.log(data.name);
}

fetchData();
```

***

# 📦 9. Function Variations You Should Know

### Function Declaration

```js
function foo() {}
```

### Function Expression

```js
const foo = function () {};
```

### Arrow Function

```js
const foo = () => {};
```

***

# ⚠️ 10. Important Differences

### `this` behavior:

```js
const obj = {
  name: "Karl",
  regular: function () {
    console.log(this.name);
  },
  arrow: () => {
    console.log(this.name);
  }
};

obj.regular(); // ✅ "Karl"
obj.arrow();   // ❌ undefined
```

Arrow functions **don’t have their own `this`**.

***

# 🧩 11. Default Parameters

```js
function greet(name = "Guest") {
  console.log("Hello", name);
}

greet(); // Hello Guest
```

***

# 🔍 12. Rest Parameters

```js
function sum(...numbers) {
  return numbers.reduce((a, b) => a + b, 0);
}

console.log(sum(1, 2, 3, 4));
```

***

# 🧪 13. Mini Deno Practice Script

Create `functions.js`:

```js
const analyze = (value) => {
  return {
    value,
    type: typeof value
  };
};

const run = () => {
  const values = [1, "hello", true];
  console.table(values.map(analyze));
};

run();
```

***

# 🎯 14. Mini Challenge

Try writing:

```js
// 1. A function that doubles a number
// 2. A function that takes another function as input
// 3. An async function that fetches data
```

***

# 💡 Key Takeaways

* Functions = reusable logic

* Arrow functions = modern & concise

* Functions can be passed around (very powerful!)

* Async functions are essential in Deno

***

If you want, I can build you a **7-day “Functions Mastery Plan” using Deno**, with daily exercises and mini projects 🚀

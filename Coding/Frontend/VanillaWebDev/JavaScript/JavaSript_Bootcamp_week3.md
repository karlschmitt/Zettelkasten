---
id: 20260413231824
title: JavaScript Bootcamp Week 3
date: 2026-04-16
keywords: [ JavaScript, Bootcamp, Deno ]
---

#  JavaScript Bootcamp Week 3

Nice—Week 3 is where things start to feel _real_. You’ll fetch live data, handle async code, and build a small CLI tool using Deno.

***

# 🚀 Week 3 — Async JavaScript + APIs + CLI (Deno)

## 🧭 Structure

* ⏱️ 30–60 minutes/day

* 🔁 REPL → file → mini project

* 🎯 Focus: _real-world data + async thinking_

***

# 📅 Day 15 — What is Async?

## 🎯 Goal

Understand that some operations take time (e.g. network)

## 🔬 REPL

```js
console.log("Start");

setTimeout(() => {
  console.log("Delayed");
}, 1000);

console.log("End");
```

👉 Output:

```
Start
End
Delayed
```

## 🧠 Learn

* JavaScript is **non-blocking**

* Code doesn’t always run top → bottom

***

# 📅 Day 16 — Promises

## 🎯 Goal

Understand how async results are handled

## 🔬 REPL

```js
const promise = new Promise((resolve) => {
  setTimeout(() => resolve("Done!"), 1000);
});

promise.then(result => console.log(result));
```

## 🧠 Learn

* `resolve()` → success

* `.then()` → handle result

***

# 📅 Day 17 — async / await (modern way)

## 🎯 Goal

Write clean async code

## 🔬 REPL

```js
function wait() {
  return new Promise(resolve =>
    setTimeout(() => resolve("Finished"), 1000)
  );
}

async function run() {
  const result = await wait();
  console.log(result);
}

run();
```

## 🧠 Learn

* `await` pauses inside `async`

* Makes async code look synchronous ✅

***

# 📅 Day 18 — Fetch Data (REAL POWER 🔥)

## 🎯 Goal

Get data from an API

Deno has `fetch` built-in 👍

## 🛠️ Mini Project

```js
// day18-fetch.js
const response = await fetch("https://jsonplaceholder.typicode.com/users");
const data = await response.json();

console.log(data);
```

Run:

```bash
deno run --allow-net day18-fetch.js
```

## 🧠 Learn

* `fetch()` → HTTP request

* `.json()` → parse response

***

# 📅 Day 19 — Working with API Data

## 🎯 Goal

Combine async + arrays + objects

## 🛠️ Mini Project

```js
// day19-process.js
const response = await fetch("https://jsonplaceholder.typicode.com/users");
const users = await response.json();

// Extract names
const names = users.map(u => u.name);

console.log(names);
```

***

# 📅 Day 20 — Error Handling

## 🎯 Goal

Handle failures safely

## 🛠️ Mini Project

```js
// day20-error.js
try {
  const response = await fetch("https://wrong-url.com");
  const data = await response.json();
  console.log(data);
} catch (error) {
  console.log("Something went wrong:", error.message);
}
```

## 🧠 Learn

* `try...catch` for async errors

* Always expect failure ❗

***

# 📅 Day 21 — Final Project: CLI Tool 🎉

## 🎯 Goal

Build a real tool with Deno

## 🛠️ Project: User CLI

```js
// day21-cli.js
const response = await fetch("https://jsonplaceholder.typicode.com/users");
const users = await response.json();

function printUsers(users) {
  for (const user of users) {
    console.log(`${user.name} (${user.email})`);
  }
}

printUsers(users);
```

Run:

```bash
deno run --allow-net day21-cli.js
```

***

# 💥 Bonus: Add CLI Argument

```js
// filter by name
const search = Deno.args[0];

const filtered = users.filter(u =>
  u.name.toLowerCase().includes(search?.toLowerCase())
);

printUsers(filtered.length ? filtered : users);
```

Run:

```bash
deno run --allow-net day21-cli.js anna
```

***

# 🧠 What You Just Learned (Big Milestone)

You can now:

* Handle async code ✅

* Use `fetch` to get real data ✅

* Process JSON ✅

* Handle errors ✅

* Build CLI tools with Deno ✅

👉 This is **real developer territory**

***

# 💡 Zettelkasten Note Idea

```text
JavaScript / Async vs Sync

Sync:
- Runs line by line

Async:
- Non-blocking
- Uses Promise / async/await

Key:
- await pauses function
- try/catch handles errors
```

***

# 🚀 What Comes Next?

If you want to keep going, I can guide you into:

### 🔥 Week 4 Options:

* 🖥️ Build a real CLI app (files, arguments, colors)

* 🌐 Build a small web server with Deno

* ⚛️ Move into React (since you started earlier)

***

Just tell me what direction you want 👍

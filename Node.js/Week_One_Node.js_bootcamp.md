---
id: 20260419135925
title: Week One of Node.js Bootcamp
keywords: [ Node.js, node, npm, JavaScript, TypeScript]
author: Karl Schmitt
date: 2026-04-19
---

# Week One of Node.js Bootcamp

Perfect—that’s actually a **great choice**. Using **curl / PowerShell** will make you much stronger than relying on GUI tools 👍

Let’s build your **Week 1 Node.js Bootcamp** step by step.

***

# 🚀 Week 1: Node.js Foundations (Hands-on)

## 🎯 Goal of Week 1

* Understand Node basics

* Build your first server

* Use **curl / PowerShell** to interact with it

* Learn async + filesystem

***

# 📅 Day 1 — Setup & First Script

## ✅ Install Node.js (LTS)

Check:

```bash
node -v
npm -v
```

***

## 🧪 Your First Script

Create `app.js`:

```js
console.log("Hello from Node.js!");
```

Run:

```bash
node app.js
```

***

## 🧠 Learn

* Node runs JavaScript outside the browser

* No `document`, no `window`

***

## 💪 Exercise

Print:

* Your name

* Current date

* Random number

***

# 📅 Day 2 — Modules & Imports

## 📦 Built-in Modules

```js
import os from "os";

console.log(os.platform());
console.log(os.homedir());
```

***

## 🧩 Create Your Own Module

`math.js`

```js
export function add(a, b) {
  return a + b;
}
```

`app.js`

```js
import { add } from "./math.js";

console.log(add(2, 3));
```

***

## 🧠 Learn

* ES Modules (`import/export`)

* File structure matters

***

## 💪 Exercise

Create:

* `multiply()`

* `divide()`

***

# 📅 Day 3 — File System (fs)

## 📁 Read a File

Create `data.txt`:

```
Hello Karl 👋
```

Code:

```js
import { readFile } from "fs/promises";

const data = await readFile("./data.txt", "utf-8");
console.log(data);
```

***

## ✍️ Write a File

```js
import { writeFile } from "fs/promises";

await writeFile("output.txt", "Learning Node.js!");
```

***

## 💪 Exercise

Build a **note saver**:

* Input text

* Save into a file

***

# 📅 Day 4 — Build Your First Server

## 🌐 Basic HTTP Server

```js
import http from "http";

const server = http.createServer((req, res) => {
  res.end("Hello from Node Server!");
});

server.listen(3000, () => {
  console.log("Server running on http://localhost:3000");
});
```

***

## 🧪 Test with curl

```bash
curl http://localhost:3000
```

***

## 💪 Exercise

Return:

* Your name

* Current time

***

# 📅 Day 5 — Routing (Manual)

```js
import http from "http";

const server = http.createServer((req, res) => {
  if (req.url === "/") {
    res.end("Home");
  } else if (req.url === "/about") {
    res.end("About Page");
  } else {
    res.statusCode = 404;
    res.end("Not Found");
  }
});

server.listen(3000);
```

***

## 🧪 Test with curl

```bash
curl http://localhost:3000/
curl http://localhost:3000/about
curl http://localhost:3000/xyz
```

***

## 💪 Exercise

Add route:

* `/contact`

***

# 📅 Day 6 — JSON & APIs

## 📦 Send JSON

```js
import http from "http";

const server = http.createServer((req, res) => {
  if (req.url === "/api") {
    res.setHeader("Content-Type", "application/json");

    const data = {
      name: "Karl",
      learning: "Node.js"
    };

    res.end(JSON.stringify(data));
  }
});

server.listen(3000);
```

***

## 🧪 Test with curl

```bash
curl http://localhost:3000/api
```

***

## 💪 Exercise

Return:

* Array of 3 books

* Array of 3 tasks

***

# 📅 Day 7 — Handle POST Requests (Power Mode 💥)

## 📥 Receive Data

```js
import http from "http";

const server = http.createServer((req, res) => {
  if (req.method === "POST" && req.url === "/data") {
    let body = "";

    req.on("data", chunk => {
      body += chunk.toString();
    });

    req.on("end", () => {
      console.log("Received:", body);
      res.end("Data received");
    });
  }
});

server.listen(3000);
```

***

## 🧪 Test with curl

```bash
curl -X POST http://localhost:3000/data -d "Hello Server"
```

***

## 🧪 PowerShell alternative

```powershell
Invoke-RestMethod -Uri "http://localhost:3000/data" -Method Post -Body "Hello Server"
```

***

## 💪 Exercise

* Accept JSON instead of plain text

* Parse it and log it

***

# 🧠 End of Week 1 — You Now Understand

✅ Node runtime\
✅ Modules\
✅ File system\
✅ HTTP server\
✅ Routing\
✅ JSON APIs\
✅ POST handling

👉 This is already **real backend development**

***

# ⚡ Bonus Challenge (Highly Recommended)

Build a **mini API**:

Routes:

* `GET /notes` → return notes

* `POST /notes` → add note

* Store notes in a JSON file

Test ONLY with:

* curl

* PowerShell

***

# 🚀 Next Step

If you want, I’ll guide you through:

👉 **Week 2: NPM, Packages & Better APIs**

* install libraries

* build a cleaner API

* introduce real-world structure

Just say:\
**“Week 2 please”**

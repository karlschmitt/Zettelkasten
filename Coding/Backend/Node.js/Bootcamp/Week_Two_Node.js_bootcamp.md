---
id: 20260419141120
title: Week Two of Node.js Bootcamp
date: 2026-04-19
author: Karl Schmitt
keywords: [ Node.js, node, npm, JavaScript]
...

# Week Two of Node.js Bootcamp

Great—Week 2 is where Node.js starts to feel like **real-world backend development** 💪\
You’ll move from “manual server” → **structured APIs with packages**

And yes: we’ll stick to **curl + PowerShell only** 😄

***

# 🚀 Week 2: NPM, Packages & Better APIs

## 🎯 Goal of Week 2

* Understand **npm & package.json**

* Use **external libraries**

* Build a **clean REST API**

* Structure your project like a pro

***

# 📅 Day 1 — npm & package.json

## 📦 Initialize Project

```bash
npm init -y
```

This creates:

```json
{
  "name": "node-api",
  "version": "1.0.0",
  "main": "index.js"
}
```

***

## ➕ Install Your First Package

```bash
npm install chalk
```

Example:

```js
import chalk from "chalk";

console.log(chalk.green("Success!"));
```

***

## 🧠 Learn

* `dependencies` vs `devDependencies`

* `node_modules` (don’t touch it 😄)

***

## 💪 Exercise

Install:

* `lodash`

* Use one function (e.g. `_.shuffle()`)

***

# 📅 Day 2 — Scripts & Dev Workflow

## 🛠️ Add Scripts

In `package.json`:

```json
"scripts": {
  "start": "node index.js",
  "dev": "node --watch index.js"
}
```

Run:

```bash
npm run dev
```

***

## 🧠 Learn

* Scripts = shortcuts

* `--watch` auto-restarts server

***

## 💪 Exercise

Add script:

* `"start:prod"`

***

# 📅 Day 3 — Meet Express.js

## 📦 Install Express

```bash
npm install express
```

***

## 🌐 First Express Server

```js
import express from "express";

const app = express();

app.get("/", (req, res) => {
  res.send("Hello Express 🚀");
});

app.listen(3000);
```

***

## 🧪 Test with curl

```bash
curl http://localhost:3000
```

***

## 🧠 Why Express?

* Cleaner routing

* Middleware support

* Industry standard

***

## 💪 Exercise

Add routes:

* `/about`

* `/contact`

***

# 📅 Day 4 — REST API Basics

## 📦 Create API

```js
import express from "express";

const app = express();

app.use(express.json());

let notes = [];

app.get("/notes", (req, res) => {
  res.json(notes);
});

app.post("/notes", (req, res) => {
  notes.push(req.body);
  res.json({ message: "Note added" });
});

app.listen(3000);
```

***

## 🧪 Test with curl

### GET

```bash
curl http://localhost:3000/notes
```

### POST

```bash
curl -X POST http://localhost:3000/notes \
  -H "Content-Type: application/json" \
  -d '{"text":"Learn Node.js"}'
```

***

## 🧪 PowerShell

```powershell
Invoke-RestMethod -Uri "http://localhost:3000/notes" -Method Post -Body (@{text="Learn Node"} | ConvertTo-Json) -ContentType "application/json"
```

***

## 💪 Exercise

* Add `id` to each note

* Return note count

***

# 📅 Day 5 — Project Structure (VERY IMPORTANT)

## 📁 Organize Like a Pro

```
project/
│
├── index.js
├── routes/
│   └── notes.js
├── controllers/
│   └── notesController.js
```

***

## 📦 Route File

`routes/notes.js`

```js
import express from "express";
const router = express.Router();

router.get("/", (req, res) => {
  res.send("All notes");
});

export default router;
```

***

## 📦 Use Route

```js
import notesRoutes from "./routes/notes.js";

app.use("/notes", notesRoutes);
```

***

## 🧠 Learn

* Separation of concerns

* Clean code structure

***

## 💪 Exercise

Split:

* GET

* POST logic into controller file

***

# 📅 Day 6 — Middleware (Power Feature ⚡)

## 🔄 Custom Middleware

```js
app.use((req, res, next) => {
  console.log(`${req.method} ${req.url}`);
  next();
});
```

***

## 🧠 Learn

* Middleware runs before route

* Can modify request/response

***

## 💪 Exercise

Create middleware:

* Log timestamp

* Block requests without body

***

# 📅 Day 7 — Error Handling & Validation

## ❌ Basic Error Handling

```js
app.post("/notes", (req, res) => {
  if (!req.body.text) {
    return res.status(400).json({ error: "Text is required" });
  }

  res.json({ message: "OK" });
});
```

***

## 🧪 Test with curl

```bash
curl -X POST http://localhost:3000/notes \
  -H "Content-Type: application/json" \
  -d '{}'
```

***

## 💪 Exercise

* Validate:

  * text must be at least 3 characters

* Return proper status codes

***

# 🧠 End of Week 2 — You Now Know

✅ npm & packages\
✅ Express.js\
✅ REST APIs\
✅ Routing structure\
✅ Middleware\
✅ Error handling

👉 This is **real backend engineering already**

***

# ⚡ Week 2 Final Project

Build a **Notes API (v2)**:

### Features:

* GET /notes

* POST /notes

* DELETE /notes/:id

* Middleware logging

* Validation

* Clean folder structure

***

## 🧪 Test ONLY with:

### curl

```bash
curl http://localhost:3000/notes
```

### PowerShell

```powershell
Invoke-RestMethod -Uri "http://localhost:3000/notes"
```

***

# 🚀 Next Step

Week 3 gets exciting:

👉 **Database + persistent data**\
👉 No more “data lost on restart”

Just say:\
**“Week 3 please”**

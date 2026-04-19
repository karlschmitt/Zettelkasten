---
id: 20260419141958
title: Week Three of Node.js Bootcamp
author: Karl Schmitt
date: 2026-04-19
keywords: [ Node.js, expres.js, node, npm, JavaScript]
---

# Week Three of Node.js Bootcamp

Nice—you’ve reached the point where things get **seriously real** 💥\
Week 3 is where your apps stop “forgetting everything” and become **persistent + production-like**.

***

# 🚀 Week 3: Databases & Persistent Data

## 🎯 Goal of Week 3

* Store data permanently (no more reset on restart)

* Use a **real database**

* Structure a **data layer**

* Build a proper CRUD API

***

# 🧠 Your Options (We’ll choose one)

For learning, best choice:

👉 **SQLite (simple, file-based, zero setup)**

Later you can move to:

* MongoDB

* PostgreSQL

***

# 📅 Day 1 — Why You Need a Database

## ❌ Problem (current)

```js
let notes = [];
```

👉 Lost when server restarts

***

## ✅ Solution

Store data in:

* File (basic)

* Database (better)

***

## 💪 Exercise

Before DB:

* Save notes into `notes.json`

* Load them on server start

👉 This helps you understand persistence first

***

# 📅 Day 2 — SQLite Setup

## 📦 Install

```bash
npm install sqlite3
```

***

## 📁 Create Database

```js
import sqlite3 from "sqlite3";

const db = new sqlite3.Database("./notes.db");

db.run(`
  CREATE TABLE IF NOT EXISTS notes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    text TEXT
  )
`);
```

***

## 🧠 Learn

* Tables = structured data

* Rows = entries

* SQL basics

***

## 💪 Exercise

Add column:

* `created_at`

***

# 📅 Day 3 — Insert Data

## ➕ Add Note

```js
app.post("/notes", (req, res) => {
  const { text } = req.body;

  db.run(
    "INSERT INTO notes (text) VALUES (?)",
    [text],
    function (err) {
      if (err) {
        return res.status(500).json({ error: err.message });
      }

      res.json({ id: this.lastID, text });
    }
  );
});
```

***

## 🧪 Test with curl

```bash
curl -X POST http://localhost:3000/notes \
  -H "Content-Type: application/json" \
  -d '{"text":"Persistent note"}'
```

***

## 💪 Exercise

Insert:

* 3 different notes

***

# 📅 Day 4 — Read Data

## 📖 Get All Notes

```js
app.get("/notes", (req, res) => {
  db.all("SELECT * FROM notes", [], (err, rows) => {
    if (err) {
      return res.status(500).json({ error: err.message });
    }

    res.json(rows);
  });
});
```

***

## 🧪 Test

```bash
curl http://localhost:3000/notes
```

***

## 💪 Exercise

Create route:

* `/notes/:id`

***

# 📅 Day 5 — Update & Delete (CRUD Complete)

## ✏️ Update

```js
app.put("/notes/:id", (req, res) => {
  const { text } = req.body;

  db.run(
    "UPDATE notes SET text = ? WHERE id = ?",
    [text, req.params.id],
    function (err) {
      if (err) return res.status(500).json({ error: err.message });

      res.json({ updated: this.changes });
    }
  );
});
```

***

## ❌ Delete

```js
app.delete("/notes/:id", (req, res) => {
  db.run(
    "DELETE FROM notes WHERE id = ?",
    req.params.id,
    function (err) {
      if (err) return res.status(500).json({ error: err.message });

      res.json({ deleted: this.changes });
    }
  );
});
```

***

## 🧪 Test

```bash
curl -X DELETE http://localhost:3000/notes/1
```

***

## 💪 Exercise

* Return proper message if note not found

***

# 📅 Day 6 — Clean Architecture (Important!)

## 📁 Structure Upgrade

```text
project/
│
├── db/
│   └── database.js
├── models/
│   └── noteModel.js
├── controllers/
│   └── noteController.js
├── routes/
│   └── noteRoutes.js
├── index.js
```

***

## 🧠 Responsibilities

* **db/** → connection

* **models/** → SQL logic

* **controllers/** → request logic

* **routes/** → endpoints

***

## 💪 Exercise

Move:

* SQL queries into model

* Routes into separate file

***

# 📅 Day 7 — Async/Await Upgrade (Modern Node)

SQLite uses callbacks—let’s modernize it.

## 🔄 Promisify Example

```js
import { promisify } from "util";

const dbAll = promisify(db.all).bind(db);

app.get("/notes", async (req, res) => {
  try {
    const rows = await dbAll("SELECT * FROM notes");
    res.json(rows);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});
```

***

## 🧠 Learn

* async/await = cleaner code

* error handling with try/catch

***

## 💪 Exercise

Convert:

* INSERT

* DELETE\
  to async/await

***

# 🧠 End of Week 3 — You Now Know

✅ Databases (SQLite)\
✅ SQL basics\
✅ CRUD operations\
✅ Persistent APIs\
✅ Clean architecture\
✅ Async patterns

👉 You are now building **real backend systems**

***

# ⚡ Week 3 Final Project

## 🧱 Notes API (Production Style)

Features:

* Full CRUD (GET, POST, PUT, DELETE)

* SQLite database

* Proper folder structure

* Error handling

* Async/await

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

# 🚀 What’s Next (Week 4 Preview)

Now it gets 🔥

👉 Authentication (login system)\
👉 Users & passwords\
👉 JWT tokens\
👉 Protected routes

***

If you want, I can continue with:

👉 **“Week 4 please”**

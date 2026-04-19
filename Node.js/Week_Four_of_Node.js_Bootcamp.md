---
id: 20260419142740
title: Week Four of Node.js Bootcamp
author: Karl Schmitt
date: 2026-04-19
keywords: [ Node.js, expres.js, node, npm, JavaScript]
---

# Week Four of Node.js Bootcamp

Nice—this is where things become **real-world backend engineering** 🔥\
Week 4 adds **authentication, security, and protected APIs**—the stuff every serious app needs.

***

# 🚀 Week 4: Authentication & Security

## 🎯 Goal of Week 4

* Create users

* Hash passwords securely

* Implement login

* Use **JWT (tokens)**

* Protect routes

***

# 🧠 What You’ll Build

👉 A **Notes API with users**

* Register

* Login

* Create notes (only if logged in)

***

# 📅 Day 1 — Users & Password Hashing

## 📦 Install

```bash
npm install bcrypt
```

***

## 🔐 Hash Passwords

```js
import bcrypt from "bcrypt";

const password = "123456";
const hashed = await bcrypt.hash(password, 10);

console.log(hashed);
```

***

## 🧠 Learn

* Never store plain passwords ❌

* Always store hashed passwords ✅

***

## 💪 Exercise

* Hash 3 different passwords

* Compare them

***

# 📅 Day 2 — User Registration

## 📦 Example Route

```js
app.post("/register", async (req, res) => {
  const { username, password } = req.body;

  const hashedPassword = await bcrypt.hash(password, 10);

  db.run(
    "INSERT INTO users (username, password) VALUES (?, ?)",
    [username, hashedPassword],
    function (err) {
      if (err) return res.status(500).json({ error: err.message });

      res.json({ id: this.lastID, username });
    }
  );
});
```

***

## 🧪 Test with curl

```bash
curl -X POST http://localhost:3000/register \
  -H "Content-Type: application/json" \
  -d '{"username":"karl","password":"secret"}'
```

***

## 💪 Exercise

* Prevent duplicate usernames

* Validate input length

***

# 📅 Day 3 — Login System

## 🔑 Verify Password

```js
app.post("/login", (req, res) => {
  const { username, password } = req.body;

  db.get(
    "SELECT * FROM users WHERE username = ?",
    [username],
    async (err, user) => {
      if (!user) return res.status(401).json({ error: "Invalid login" });

      const valid = await bcrypt.compare(password, user.password);

      if (!valid) return res.status(401).json({ error: "Invalid login" });

      res.json({ message: "Login successful" });
    }
  );
});
```

***

## 💪 Exercise

* Return better error messages

* Handle missing user

***

# 📅 Day 4 — JWT (JSON Web Tokens)

## 📦 Install

```bash
npm install jsonwebtoken
```

***

## 🔐 Create Token

```js
import jwt from "jsonwebtoken";

const token = jwt.sign(
  { userId: 1 },
  "secretkey",
  { expiresIn: "1h" }
);
```

***

## 🧠 Learn

* Token = proof of identity

* Sent with each request

***

## 💪 Exercise

* Add username into token

***

# 📅 Day 5 — Login with Token

## 🔑 Return Token

```js
app.post("/login", async (req, res) => {
  const { username, password } = req.body;

  db.get("SELECT * FROM users WHERE username = ?", [username], async (err, user) => {
    if (!user) return res.status(401).json({ error: "Invalid login" });

    const valid = await bcrypt.compare(password, user.password);
    if (!valid) return res.status(401).json({ error: "Invalid login" });

    const token = jwt.sign({ id: user.id }, "secretkey", {
      expiresIn: "1h",
    });

    res.json({ token });
  });
});
```

***

## 🧪 Test with curl

```bash
curl -X POST http://localhost:3000/login \
  -H "Content-Type: application/json" \
  -d '{"username":"karl","password":"secret"}'
```

***

## 💪 Exercise

* Copy token manually (you’ll use it next)

***

# 📅 Day 6 — Protect Routes (Middleware 🔥)

## 🔐 Auth Middleware

```js
function authMiddleware(req, res, next) {
  const authHeader = req.headers.authorization;

  if (!authHeader) {
    return res.status(401).json({ error: "No token" });
  }

  const token = authHeader.split(" ")[1];

  try {
    const decoded = jwt.verify(token, "secretkey");
    req.user = decoded;
    next();
  } catch {
    res.status(401).json({ error: "Invalid token" });
  }
}
```

***

## 🔒 Protect Route

```js
app.get("/notes", authMiddleware, (req, res) => {
  res.json({ message: "Protected notes" });
});
```

***

## 🧪 Test with curl

```bash
curl http://localhost:3000/notes \
  -H "Authorization: Bearer YOUR_TOKEN"
```

***

## 🧪 PowerShell

```powershell
Invoke-RestMethod -Uri "http://localhost:3000/notes" -Headers @{Authorization="Bearer YOUR_TOKEN"}
```

***

## 💪 Exercise

* Return user ID from token

***

# 📅 Day 7 — Connect Users to Notes

## 🧠 Idea

Each note belongs to a user:

```sql
user_id INTEGER
```

***

## ➕ Create Note with User

```js
app.post("/notes", authMiddleware, (req, res) => {
  const { text } = req.body;
  const userId = req.user.id;

  db.run(
    "INSERT INTO notes (text, user_id) VALUES (?, ?)",
    [text, userId],
    function (err) {
      if (err) return res.status(500).json({ error: err.message });

      res.json({ id: this.lastID, text });
    }
  );
});
```

***

## 📖 Get Only User Notes

```js
app.get("/notes", authMiddleware, (req, res) => {
  db.all(
    "SELECT * FROM notes WHERE user_id = ?",
    [req.user.id],
    (err, rows) => {
      res.json(rows);
    }
  );
});
```

***

## 💪 Exercise

* Ensure users only see their own notes

* Try accessing with different token

***

# 🧠 End of Week 4 — You Now Know

✅ Password hashing (bcrypt)\
✅ Authentication (login/register)\
✅ JWT tokens\
✅ Middleware protection\
✅ Multi-user systems

👉 This is **production-level backend knowledge**

***

# ⚡ Final Project (🔥 Important)

## 🧱 Secure Notes API

Features:

* Register & Login

* JWT authentication

* Protected routes

* Notes per user

* Full CRUD

***

## 🧪 Test ONLY with:

### curl

```bash
curl -H "Authorization: Bearer TOKEN" http://localhost:3000/notes
```

### PowerShell

```powershell
Invoke-RestMethod -Uri "http://localhost:3000/notes" -Headers @{Authorization="Bearer TOKEN"}
```

***

# 🚀 What Comes Next?

If you continue, you’re entering **advanced backend territory**:

👉 Week 5 ideas:

* Environment variables (`.env`)

* Docker basics

* Logging

* Rate limiting

* Deploy your API

***

If you want, I can continue with:

👉 **“Week 5 please”**

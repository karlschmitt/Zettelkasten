---
id: 20260516183607
title: A 7-Day Hono and Deno Bootcamp
author: Karl Schmitt
date: 2026-05-16
keywords: [ TypeScript, Deno, Hono ]
---

# A 7-Day Hono and Deno Bootcamp

## 7-Day Hono + Deno Bootcamp

Goal of this bootcamp:

By the end, you will build a small REST API backend using:

* Routing
* JSON APIs
* Middleware
* CRUD operations
* File organization
* Error handling
* Basic persistence

You already have a strong JavaScript + Deno foundation, so this bootcamp focuses on backend architecture and practical APIs.

---

# Bootcamp Structure

| Day | Topic                | Project             |
| --- | -------------------- | ------------------- |
| 1   | Hono Basics          | Hello API           |
| 2   | Routing + Parameters | User API            |
| 3   | POST Requests + JSON | Notes API           |
| 4   | Middleware           | Request Logger      |
| 5   | CRUD REST APIs       | Todo API            |
| 6   | Project Structure    | Organized Backend   |
| 7   | Final Project        | Mini Backend Server |

---

# Day 1 — Hono Fundamentals

## Goal

Learn:

* Create a server
* Define routes
* Return text
* Return JSON

---

# Step 1 — Create Project

```powershell id="g5bf9r"
mkdir hono-bootcamp
cd hono-bootcamp
```

---

# Step 2 — Create `main.ts`

```ts id="xjlwmj"
import { Hono } from "jsr:@hono/hono"

const app = new Hono()

app.get("/", (c) => {
  return c.text("Hello Hono!")
})

Deno.serve(app.fetch)
```

---

# Step 3 — Run Server

```powershell id="r3w0to"
deno run --allow-net main.ts
```

Open:

```text id="p1z4eq"
http://localhost:8000
```

---

# Step 4 — Add More Routes

```ts id="o7cl4s"
app.get("/about", (c) => {
  return c.text("About Page")
})

app.get("/api", (c) => {
  return c.json({
    framework: "Hono",
    runtime: "Deno"
  })
})
```

---

# Concepts Learned

## HTTP GET

Browser requests usually use GET.

---

# JSON Responses

```ts id="x81xth"
return c.json({
  message: "Hello"
})
```

Most APIs return JSON.

---

# Day 1 Exercises

## Exercise 1

Create routes:

```text id="9a4frc"
/contact
/help
/status
```

---

## Exercise 2

Return JSON:

```json id="9nd5if"
{
  "online": true
}
```

---

## Exercise 3

Create route:

```text id="s1y0tb"
/time
```

Return current date/time.

Hint:

```ts id="4m8smf"
new Date()
```

---

# Day 2 — Route Parameters + Query Parameters

## Goal

Learn:

* Dynamic URLs
* Query strings
* Request information

---

# Route Parameters

Example URL:

```text id="10r4ew"
/users/42
```

Code:

```ts id="yk8s2d"
app.get("/users/:id", (c) => {
  const id = c.req.param("id")

  return c.text(`User ID: ${id}`)
})
```

---

# Multiple Parameters

```ts id="b5cd5s"
app.get("/posts/:postId/comments/:commentId", (c) => {
  const postId = c.req.param("postId")
  const commentId = c.req.param("commentId")

  return c.json({
    postId,
    commentId
  })
})
```

---

# Query Parameters

Example:

```text id="oqt2kl"
/search?q=hono
```

Code:

```ts id="b2e4go"
app.get("/search", (c) => {
  const query = c.req.query("q")

  return c.text(`Searching for: ${query}`)
})
```

---

# Query vs Route Parameters

| Type        | Example          |
| ----------- | ---------------- |
| Route Param | `/users/42`      |
| Query Param | `/search?q=hono` |

---

# Day 2 Exercises

## Exercise 1

Create:

```text id="hm98xn"
/products/:id
```

Return JSON with the product ID.

---

## Exercise 2

Create search route:

```text id="3n5c8e"
/movies?title=matrix
```

---

## Exercise 3

Create route:

```text id="2zy1yw"
/weather/:city
```

---

# Day 3 — POST Requests + JSON APIs

## Goal

Learn:

* POST requests
* Reading JSON
* Sending data

---

# Create POST Route

```ts id="k2j0gf"
app.post("/api/message", async (c) => {
  const body = await c.req.json()

  return c.json({
    received: body
  })
})
```

---

# Test Using curl

## PowerShell

```powershell id="9jjp58"
curl -X POST http://localhost:8000/api/message `
  -H "Content-Type: application/json" `
  -d '{"message":"Hello"}'
```

---

# Expected Output

```json id="y7jcbt"
{
  "received": {
    "message": "Hello"
  }
}
```

---

# Validation Example

```ts id="nps8wd"
app.post("/login", async (c) => {
  const body = await c.req.json()

  if (!body.username) {
    return c.text("Username required", 400)
  }

  return c.json({
    success: true
  })
})
```

---

# Day 3 Exercises

## Exercise 1

Create:

```text id="zkfk5x"
/api/user
```

Accept:

```json id="pkld7z"
{
  "name": "Karl",
  "age": 30
}
```

---

## Exercise 2

Validate:

* missing name
* missing age

---

## Exercise 3

Create calculator API:

```text id="h6w3f5"
/add
```

Input:

```json id="jgs34q"
{
  "a": 5,
  "b": 10
}
```

Output:

```json id="g4xpcq"
{
  "result": 15
}
```

---

# Day 4 — Middleware

## Goal

Learn:

* Middleware
* Request logging
* Request timing

---

# Simple Logger Middleware

```ts id="qv0tr8"
app.use("*", async (c, next) => {
  console.log(`${c.req.method} ${c.req.url}`)

  await next()
})
```

---

# Request Timer

```ts id="rjlwmv"
app.use("*", async (c, next) => {
  const start = Date.now()

  await next()

  const end = Date.now()

  console.log(`Request took ${end - start}ms`)
})
```

---

# Middleware Flow

```text id="afn0iy"
Request
   ↓
Middleware
   ↓
Route Handler
   ↓
Response
```

---

# Add Custom Headers

```ts id="fgk9ys"
app.use("*", async (c, next) => {
  await next()

  c.header("X-Powered-By", "Hono")
})
```

---

# Day 4 Exercises

## Exercise 1

Log:

* HTTP method
* URL
* timestamp

---

## Exercise 2

Add custom header:

```text id="2jhjmd"
X-App-Version
```

---

## Exercise 3

Measure request duration.

---

# Day 5 — CRUD REST APIs

## Goal

Learn:

* Create
* Read
* Update
* Delete

This is core backend development.

---

# Todo API

## Data

```ts id="1abvb0"
const todos = [
  { id: 1, text: "Learn Hono" }
]
```

---

# GET All Todos

```ts id="gm8wm0"
app.get("/todos", (c) => {
  return c.json(todos)
})
```

---

# GET One Todo

```ts id="7dkgjx"
app.get("/todos/:id", (c) => {
  const id = Number(c.req.param("id"))

  const todo = todos.find((t) => t.id === id)

  if (!todo) {
    return c.text("Not Found", 404)
  }

  return c.json(todo)
})
```

---

# CREATE Todo

```ts id="9a7b51"
app.post("/todos", async (c) => {
  const body = await c.req.json()

  const todo = {
    id: Date.now(),
    text: body.text
  }

  todos.push(todo)

  return c.json(todo, 201)
})
```

---

# DELETE Todo

```ts id="1zt9pi"
app.delete("/todos/:id", (c) => {
  const id = Number(c.req.param("id"))

  const index = todos.findIndex((t) => t.id === id)

  if (index === -1) {
    return c.text("Not Found", 404)
  }

  todos.splice(index, 1)

  return c.text("Deleted")
})
```

---

# HTTP Methods

| Method | Purpose |
| ------ | ------- |
| GET    | Read    |
| POST   | Create  |
| PUT    | Update  |
| DELETE | Remove  |

---

# Day 5 Exercises

## Exercise 1

Add PUT route.

---

## Exercise 2

Add completed flag:

```json id="fh1nm3"
{
  "completed": true
}
```

---

## Exercise 3

Return proper status codes:

| Code | Meaning     |
| ---- | ----------- |
| 200  | OK          |
| 201  | Created     |
| 400  | Bad Request |
| 404  | Not Found   |

---

# Day 6 — Project Structure

## Goal

Learn:

* Organize code
* Split routes
* Create maintainable apps

---

# Recommended Structure

```text id="84hihh"
project/
├── routes/
├── middleware/
├── services/
├── data/
├── main.ts
└── deno.json
```

---

# Create Route File

## `routes/todos.ts`

```ts id="ppg8z7"
import { Hono } from "jsr:@hono/hono"

const todos = new Hono()

todos.get("/", (c) => {
  return c.text("Todos Route")
})

export default todos
```

---

# Use Route

## `main.ts`

```ts id="gw7o6v"
import { Hono } from "jsr:@hono/hono"
import todos from "./routes/todos.ts"

const app = new Hono()

app.route("/todos", todos)

Deno.serve(app.fetch)
```

---

# Add Deno Tasks

## `deno.json`

```json id="6bwyy6"
{
  "tasks": {
    "dev": "deno run --watch --allow-net main.ts"
  }
}
```

Run:

```powershell id="4t1m5k"
deno task dev
```

---

# Day 6 Exercises

## Exercise 1

Create:

```text id="b6is7m"
routes/users.ts
```

---

## Exercise 2

Create middleware folder.

---

## Exercise 3

Move logger into its own file.

---

# Day 7 — Final Mini Project

# Build a Notes API

## Features

| Feature     | Method |
| ----------- | ------ |
| List notes  | GET    |
| Get note    | GET    |
| Create note | POST   |
| Delete note | DELETE |

---

# Suggested Structure

```text id="t7tlrt"
notes-api/
├── routes/
│   └── notes.ts
├── middleware/
│   └── logger.ts
├── data/
│   └── notes.ts
├── main.ts
└── deno.json
```

---

# Bonus Features

If you finish early:

* Add PUT update route
* Add timestamps
* Add UUID IDs
* Save to file
* Add validation
* Add error middleware

---

# Final Challenge

Build:

## Beginner

* Quotes API
* Movies API
* Recipes API

## Intermediate

* Authentication API
* Markdown Notes API
* Weather Proxy API

## Advanced

* Chat backend
* WebSocket server
* Realtime notifications

---

# Recommended Next Topics

After this bootcamp:

1. TypeScript deep dive
2. SQLite with Deno
3. JWT authentication
4. WebSockets
5. Database design
6. REST best practices
7. Deployment
8. Testing APIs
9. Validation libraries
10. Fullstack applications

---

# Recommended Resources

* [Hono Docs](https://hono.dev/docs?utm_source=chatgpt.com)
* [Deno Docs](https://docs.deno.com/runtime/manual/?utm_source=chatgpt.com)
* [Hono GitHub Repository](https://github.com/honojs/hono?utm_source=chatgpt.com)
* [JSR Package Registry](https://jsr.io?utm_source=chatgpt.com)

---

# Daily Study Recommendation

| Activity           | Time   |
| ------------------ | ------ |
| Read tutorial      | 30 min |
| Type code manually | 45 min |
| Experiment         | 30 min |
| Exercises          | 45 min |

Typing the code yourself is extremely important for backend learning.

---

If you want next, I can also provide:

* A **30-Day Hono Mastery Plan**
* A **Hono + SQLite Bootcamp**
* A **Hono Authentication Tutorial**
* A **Hono Middleware Deep Dive**
* A **REST API Design Tutorial**
* A **Hono + HTMX Tutorial**
* A **Hono + React Fullstack Tutorial**
* A **Production Deployment Guide**
* A **Testing APIs with curl + PowerShell Tutorial**
* A **Complete CRUD Todo Application Project**



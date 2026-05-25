---
id: 20260516181656
title: Hono Tutorial using Deno
author: Karl Schmitt
date: 2026-05-16
keywords: [ TypeScript, Deno, Hono ]
---

# Hono Tutorial using Deno

## The Hono + Deno Tutorial

## What is Hono?

Hono is a very fast, lightweight web framework for modern JavaScript runtimes like:

* [Deno](https://deno.com/)
* [Node.js](https://nodejs.org/en)
* [Bun](https://bun.com/)
* Cloudflare Workers

It feels a bit like:

* [Express.js](https://expressjs.com/) → but much smaller and faster
* Middleware-based frameworks → simple routing and APIs
* Modern TypeScript-first backend development

Official websites:

* [Hono Official Website](https://hono.dev?utm_source=chatgpt.com)
* [Deno Official Website](https://deno.com?utm_source=chatgpt.com)

---

# Why Hono is Great for Learning

Hono is excellent because it teaches:

* Routing
* HTTP APIs
* Middleware
* JSON APIs
* REST concepts
* Authentication basics
* Backend architecture

without lots of boilerplate.

---

# Prerequisites

You should already know:

* Basic JavaScript
* Variables
* Functions
* Objects
* Arrays
* Async/await

Your earlier JavaScript + Deno learning path fits perfectly for Hono.

---

# Install Deno

Install Deno:

## Windows PowerShell

```powershell
irm https://deno.land/install.ps1 | iex
```

Verify:

```powershell
deno --version
```

---

# Your First Hono App

## Step 1 — Create a Folder

```powershell
mkdir hono-demo
cd hono-demo
```

---

## Step 2 — Create `main.ts`

```ts
import { Hono } from "jsr:@hono/hono"

const app = new Hono()

app.get("/", (c) => {
  return c.text("Hello from Hono + Deno!")
})

Deno.serve(app.fetch)
```

---

## Step 3 — Run the Server

```powershell
deno run --allow-net main.ts
```

You should see:

```text
Listening on http://0.0.0.0:8000/
```

Open:

```text
http://localhost:8000
```

Result:

```text
Hello from Hono + Deno!
```

---

# Understanding the Code

## Importing Hono

```ts
import { Hono } from "jsr:@hono/hono"
```

This imports the framework.

---

## Creating the App

```ts
const app = new Hono()
```

This creates your web application.

---

## Defining a Route

```ts
app.get("/", (c) => {
  return c.text("Hello from Hono + Deno!")
})
```

This means:

| Part       | Meaning           |
| ---------- | ----------------- |
| `get`      | HTTP GET request  |
| `/`        | Homepage route    |
| `c`        | Context object    |
| `c.text()` | Return plain text |

---

## Starting the Server

```ts
Deno.serve(app.fetch)
```

This connects Hono to Deno’s HTTP server.

---

# Creating Multiple Routes

```ts
import { Hono } from "jsr:@hono/hono"

const app = new Hono()

app.get("/", (c) => {
  return c.text("Home")
})

app.get("/about", (c) => {
  return c.text("About Page")
})

app.get("/contact", (c) => {
  return c.text("Contact Page")
})

Deno.serve(app.fetch)
```

Test:

```text
http://localhost:8000/about
```

---

# Route Parameters

Dynamic URLs are very important.

Example:

```text
/users/123
```

Code:

```ts
app.get("/users/:id", (c) => {
  const id = c.req.param("id")

  return c.text(`User ID: ${id}`)
})
```

Test:

```text
http://localhost:8000/users/42
```

Output:

```text
User ID: 42
```

---

# Returning JSON

Most backend APIs return JSON.

```ts
app.get("/api/user", (c) => {
  return c.json({
    name: "Karl",
    role: "Developer"
  })
})
```

Output:

```json
{
  "name": "Karl",
  "role": "Developer"
}
```

---

# Query Parameters

Example URL:

```text
/search?q=deno
```

Code:

```ts
app.get("/search", (c) => {
  const query = c.req.query("q")

  return c.text(`Searching for: ${query}`)
})
```

---

# POST Requests

POST requests send data to the server.

## Example API

```ts
app.post("/api/data", async (c) => {
  const body = await c.req.json()

  return c.json({
    received: body
  })
})
```

---

# Testing APIs with curl

You said you prefer curl and PowerShell over Postman — perfect for Hono.

## PowerShell

```powershell
curl -X POST http://localhost:8000/api/data `
  -H "Content-Type: application/json" `
  -d '{"message":"Hello"}'
```

---

# Middleware

Middleware runs before route handlers.

Example logger:

```ts
app.use("*", async (c, next) => {
  console.log(`${c.req.method} ${c.req.url}`)

  await next()
})
```

This logs all requests.

---

# HTML Responses

Hono can also serve HTML.

```ts
app.get("/", (c) => {
  return c.html(`
    <html>
      <body>
        <h1>Hello Hono</h1>
      </body>
    </html>
  `)
})
```

---

# Serving Static Files

Project structure:

```text
project/
├── main.ts
└── public/
    └── index.html
```

Install middleware:

```ts
import { serveStatic } from "jsr:@hono/hono/deno"

app.use("/static/*", serveStatic({ root: "./public" }))
```

---

# Organizing Routes

Large apps separate routes.

## `routes/users.ts`

```ts
import { Hono } from "jsr:@hono/hono"

const users = new Hono()

users.get("/", (c) => {
  return c.text("Users List")
})

export default users
```

---

## `main.ts`

```ts
import { Hono } from "jsr:@hono/hono"
import users from "./routes/users.ts"

const app = new Hono()

app.route("/users", users)

Deno.serve(app.fetch)
```

---

# Environment Variables

Useful for secrets and configuration.

## Run

```powershell
$env:APP_NAME="Hono Demo"
deno run --allow-env --allow-net main.ts
```

## Read Variable

```ts
const appName = Deno.env.get("APP_NAME")
```

---

# Error Handling

```ts
app.notFound((c) => {
  return c.text("404 Not Found", 404)
})

app.onError((err, c) => {
  console.error(err)

  return c.text("Internal Server Error", 500)
})
```

---

# Simple REST API Example

```ts
import { Hono } from "jsr:@hono/hono"

const app = new Hono()

const books = [
  { id: 1, title: "Deno Basics" },
  { id: 2, title: "Learning Hono" }
]

app.get("/books", (c) => {
  return c.json(books)
})

app.get("/books/:id", (c) => {
  const id = Number(c.req.param("id"))

  const book = books.find((b) => b.id === id)

  if (!book) {
    return c.text("Book not found", 404)
  }

  return c.json(book)
})

Deno.serve(app.fetch)
```

---

# Development Workflow

## Auto Reload

```powershell
deno task dev
```

## `deno.json`

```json
{
  "tasks": {
    "dev": "deno run --watch --allow-net main.ts"
  }
}
```

Now your server restarts automatically.

---

# Recommended Folder Structure

```text
project/
├── routes/
├── middleware/
├── services/
├── database/
├── public/
├── main.ts
└── deno.json
```

---

# What to Learn Next

After basics, learn:

1. Middleware
2. REST APIs
3. Validation
4. Authentication
5. JWT
6. Databases
7. SQLite
8. PostgreSQL
9. WebSockets
10. Deployment

---

# Excellent Hono Learning Resources

* [Hono Documentation](https://hono.dev/docs?utm_source=chatgpt.com)
* [Hono Examples](https://hono.dev/examples?utm_source=chatgpt.com)
* [Deno Manual](https://docs.deno.com/runtime/manual/?utm_source=chatgpt.com)
* [JSR Package Registry](https://jsr.io?utm_source=chatgpt.com)

---

# Suggested 7-Day Hono Bootcamp

| Day | Topic                       |
| --- | --------------------------- |
| 1   | Routes + GET requests       |
| 2   | POST requests + JSON        |
| 3   | Route params + query params |
| 4   | Middleware                  |
| 5   | REST APIs                   |
| 6   | HTML + static files         |
| 7   | Build a mini API project    |

---

# Beginner Projects

## Easy

* Notes API
* Todo API
* Quote API
* Calculator API

## Intermediate

* Blog backend
* Authentication system
* Weather API proxy
* Markdown notes app

## Advanced

* Chat server
* Realtime notifications
* Full REST backend
* JWT authentication server

---

# Example Full Mini Project Idea

Build:

```text
Todo REST API
```

Features:

* GET /todos
* GET /todos/:id
* POST /todos
* DELETE /todos/:id

This is one of the best beginner backend exercises.

---

If you want, I can also provide:

1. A **7-Day Hono + Deno Bootcamp**
2. A **30-Day Hono Mastery Plan**
3. A **Hono REST API Deep Dive**
4. A **Hono Middleware Tutorial**
5. A **Hono + SQLite Tutorial**
6. A **Hono Authentication Tutorial**
7. A **Full CRUD Todo API Project**
8. A **Hono + HTMX Tutorial**
9. A **Hono + React Frontend Tutorial**
10. A **Production Deployment Guide for Hono**

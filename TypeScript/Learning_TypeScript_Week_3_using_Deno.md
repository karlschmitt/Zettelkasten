---
id: 20260416220757
title: Learning TypeScript Week Thrre using Deno
date: 2016-04-16
keywords: [ TypeScript, Deno ]
author: Karl Schmitt
---

# Learning TypeScript Week Three using Deno

Perfect—this is where things start to feel _real_ 🚀\
Week 3 turns you from “learning TypeScript” into **building actual tools and services**.

***

# 📅 Week 3 — TypeScript with Deno (Advanced + Real Apps)

## 🎯 Goal of Week 3

By the end, you will:

* Write **tests**

* Use **formatting & linting**

* Build a **web server (API)**

* Structure a **real project**

* Use external libraries the Deno way

***

# 🧠 Day 15 — Testing with Deno 🧪

One of the best features of Deno is built-in testing.

### 🧪 Example

```ts
import { assertEquals } from "https://deno.land/std/testing/asserts.ts";

Deno.test("add function", () => {
  const result = 2 + 3;
  assertEquals(result, 5);
});
```

Run:

```bash
deno test
```

***

### 🔁 Challenge

* Test your `add()` function from Week 2

* Write 2–3 test cases

***

### 💡 Insight

> Good developers don’t just write code—they **prove it works**

***

# 🧠 Day 16 — Formatting & Linting 🧹

### ✅ What to learn

* Clean, consistent code

### 🧪 Commands

```bash
deno fmt
deno lint
```

***

### 💡 Habit

Run this daily:

```bash
deno fmt && deno lint
```

***

# 🧠 Day 17 — Project Structure 📁

### ✅ What to learn

Organize like a real developer

### 🧱 Example

```bash
project/
├── src/
│   ├── main.ts
│   ├── utils.ts
│   └── services/
├── tests/
├── deno.json
└── README.md
```

***

### 🧪 Minimal `deno.json`

```json
{
  "tasks": {
    "start": "deno run --allow-net src/main.ts",
    "test": "deno test"
  }
}
```

Run:

```bash
deno task start
```

***

# 🧠 Day 18 — Build a Web Server 🌐

Deno includes HTTP utilities.

### 🧪 Example

```ts
import { serve } from "https://deno.land/std/http/server.ts";

serve(() => {
  return new Response("Hello from Deno 🚀");
});
```

Run:

```bash
deno run --allow-net server.ts
```

Open browser:

```
http://localhost:8000
```

***

### 🔁 Challenge

Return JSON instead:

```ts
return Response.json({ message: "Hello Karl" });
```

***

# 🧠 Day 19 — Build a Simple API 🔌

### 🧪 Example

```ts
import { serve } from "https://deno.land/std/http/server.ts";

serve((req) => {
  const url = new URL(req.url);

  if (url.pathname === "/hello") {
    return Response.json({ greeting: "Hello World" });
  }

  return new Response("Not Found", { status: 404 });
});
```

***

### 🔁 Try:

* `/hello`

* `/unknown`

***

# 🧠 Day 20 — External Libraries (Deno Style)

Deno uses URLs or modern registries.

### 🧪 Example (std lib)

```ts
import { serve } from "https://deno.land/std/http/server.ts";
```

***

### 💡 Alternative (modern way)

Use:

* `jsr:` (Deno registry)

* `npm:` (yes, Deno supports npm now!)

Example:

```ts
import _ from "npm:lodash";
```

***

# 🧠 Day 21 — Final Project 🚀

## 🛠️ Build: Notes API (Zettelkasten Server)

You already built CLI → now API version.

***

### 🧪 Basic Idea

```ts
import { serve } from "https://deno.land/std/http/server.ts";

serve(async (req) => {
  const url = new URL(req.url);

  if (url.pathname === "/add") {
    const text = await req.text();
    await Deno.writeTextFile("note.txt", text);
    return new Response("Saved");
  }

  if (url.pathname === "/read") {
    const text = await Deno.readTextFile("note.txt");
    return new Response(text);
  }

  return new Response("Not Found", { status: 404 });
});
```

***

### ▶️ Run it

```bash
deno run --allow-net --allow-read --allow-write server.ts
```

***

### 🔁 Test it

```bash
curl -X POST http://localhost:8000/add -d "My note"
curl http://localhost:8000/read
```

***

# 📌 Week 3 Summary

You can now:

* ✅ Write tests (`deno test`)

* ✅ Format & lint code

* ✅ Structure projects

* ✅ Build servers & APIs

* ✅ Use external libraries

***

# 🧭 What You Are Now

At this point, you are no longer a beginner.

You can:

* Replace PowerShell scripts with TS ✅

* Build backend tools ✅

* Create APIs ✅

***

# ⚡ Next Level (Week 4 — if you want)

We can go even deeper:

* Routing frameworks (Oak, Hono)

* Middleware

* Databases (SQLite)

* Authentication basics

* Real full-stack projects

***

If you want, I can:\
👉 Turn your **Notes API into a full app (with routes + structure)**\
👉 Or build you a **Week 4 “real developer” roadmap**

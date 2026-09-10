---
id: 20260910192801
title: Building a REST API using Oak and Hono 
author: Karl Schmitt
date: 2026-09-10
keywords: [ REST, API, TypeScript, Oak, Hono]
---

![Deno Logo 2024](../images/Deno_Logo_2024.png)

# Building a REST API using Oak and Hono

Here is how to rewrite the REST API using **Hono**, which has become the official lightweight web framework of choice across modern JS runtimes (Deno, Bun, Cloudflare Workers).

Hono provides strict TypeScript inference for parameters and body parsing, expressive middleware, and a clean routing syntax without requiring external build tools in Deno.

## Step 1: Updated `server.ts` using Hono

Deno supports importing npm packages directly using the `npm:` specifier prefix.

Replace your previous `server.ts` file with the following:

```TypeScript
import { Hono } from "npm:hono@^4.0.0";
import { store } from "./store.ts";
import type { CreateProductDTO, UpdateProductDTO } from "./types.ts";

const app = new Hono();

// Global Logger Middleware
app.use("*", async (c, next) => {
  console.log(`[${c.req.method}] ${c.req.url}`);
  await next();
});

// 1. GET /api/products -> List all products
app.get("/api/products", (c) => {
  return c.json(store.getAll());
});

// 2. GET /api/products/:id -> Get single product
app.get("/api/products/:id", (c) => {
  const id = c.req.param("id");
  const product = store.getById(id);

  if (!product) {
    return c.json({ error: "Product not found" }, 404);
  }

  return c.json(product);
});

// 3. POST /api/products -> Create a product
app.post("/api/products", async (c) => {
  try {
    const body = await c.req.json<CreateProductDTO>();

    if (!body.name || typeof body.price !== "number") {
      return c.json(
        { error: "Missing required fields: 'name' (string) and 'price' (number)" },
        400
      );
    }

    const newProduct = store.create(body);
    return c.json(newProduct, 201);
  } catch (_err) {
    return c.json({ error: "Invalid JSON body" }, 400);
  }
});

// 4. PUT /api/products/:id -> Update a product
app.put("/api/products/:id", async (c) => {
  const id = c.req.param("id");

  try {
    const body = await c.req.json<UpdateProductDTO>();
    const updated = store.update(id, body);

    if (!updated) {
      return c.json({ error: "Product not found" }, 404);
    }

    return c.json(updated);
  } catch (_err) {
    return c.json({ error: "Invalid JSON body" }, 400);
  }
});

// 5. DELETE /api/products/:id -> Delete a product
app.delete("/api/products/:id", (c) => {
  const id = c.req.param("id");
  const deleted = store.delete(id);

  if (!deleted) {
    return c.json({ error: "Product not found" }, 404);
  }

  return c.json({ message: "Product deleted successfully" });
});

// Start Deno server with Hono handler
Deno.serve(app.fetch);
```

## Key Improvements Over Plain `Deno.serve`

1. **Named Route Handler Methods:** Instead of nested `if/else` checks matching `method` and `pathname`, routes are declaratively written as `app.get()`, `app.post()`, `app.put()`, and `app.delete()`.


2. **Context Object (`c`):** Everything is encapsulated in the Hono context (`c`), which standardizes parsing path parameters (`c.req.param('id')`), parsing JSON payloads (`c.req.json()`), and sending responses (`c.json()`).


3. **Middleware Pipeline:** Middleware functions pass execution control via `await next()`, making cross-cutting concerns like logging, auth checks, or CORS simple to insert globally.



## Step 2: Run the Server

Run the script directly—Deno will automatically download the `hono` module on first launch:

```powershell
deno run --watch --allow-net server.ts
```

All previous `curl` commands work identically against `http://localhost:8000`.

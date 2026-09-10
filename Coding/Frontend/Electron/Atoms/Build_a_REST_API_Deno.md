---
id: 20260910191956
title: Build a REST API with Deno and TypeScript
author: Karl Schmitt
date: 2026-09-10
keywords: [ REST, API, Deno, TypeScript ]
---

![TypeScript Logo](../Images/Typescript_logo_2020.png)

# Build a REST API with Deno and TypeScript

This guide walks through building a complete, type-safe REST API for managing a list of **Products** (CRUD operations) using **Deno** and standard Web/Deno APIs.

We will use Deno's native `Deno.serve()` and standard `URLPattern` router—meaning **zero external dependencies are required**.


## Project Structure

Create a new directory for your project:



Bash

```
mkdir deno-rest-api
cd deno-rest-api
```

We will organize the code into three simple files:



* `types.ts` – Data contracts and models


* `store.ts` – In-memory database logic


* `server.ts` – HTTP routing and request handlers



## Step 1: Define TypeScript Types (`types.ts`)

Create `types.ts` to define the shape of a `Product` and the payload required to create or update one:



TypeScript

```
export interface Product {
  id: string;
  name: string;
  price: number;
  createdAt: string;
}

export type CreateProductDTO = Omit<Product, "id" | "createdAt">;
export type UpdateProductDTO = Partial<CreateProductDTO>;
```

## Step 2: Build the Data Store (`store.ts`)

Create `store.ts` to mock database persistence using an in-memory `Map`:



TypeScript

```
import type { Product, CreateProductDTO, UpdateProductDTO } from "./types.ts";

class ProductStore {
  private products = new Map<string, Product>();

  constructor() {
    // Seed initial data
    this.create({ name: "Mechanical Keyboard", price: 120 });
    this.create({ name: "Wireless Mouse", price: 60 });
  }

  getAll(): Product[] {
    return Array.from(this.products.values());
  }

  getById(id: string): Product | undefined {
    return this.products.get(id);
  }

  create(dto: CreateProductDTO): Product {
    const product: Product = {
      id: crypto.randomUUID(),
      ...dto,
      createdAt: new Date().toISOString(),
    };
    this.products.set(product.id, product);
    return product;
  }

  update(id: string, dto: UpdateProductDTO): Product | null {
    const existing = this.products.get(id);
    if (!existing) return null;

    const updated: Product = { ...existing, ...dto };
    this.products.set(id, updated);
    return updated;
  }

  delete(id: string): boolean {
    return this.products.delete(id);
  }
}

export const store = new ProductStore();
```

## Step 3: Implement the HTTP Handlers & Router (`server.ts`)

Create `server.ts`. Deno supports the standard browser `URLPattern` API, which allows us to parse path parameters like `/api/products/:id` cleanly:



TypeScript

```
import { store } from "./store.ts";
import type { CreateProductDTO, UpdateProductDTO } from "./types.ts";

// Utility function for structured JSON responses
function json(data: unknown, status = 200): Response {
  return Response.json(data, { status });
}

// Define route patterns using native URLPattern
const productItemPattern = new URLPattern({ pathname: "/api/products/:id" });

Deno.serve(async (req: Request): Promise<Response> => {
  const url = new URL(req.url);
  const path = url.pathname;
  const method = req.method;

  try {
    // 1. GET /api/products -> List all products
    if (method === "GET" && path === "/api/products") {
      return json(store.getAll());
    }

    // 2. POST /api/products -> Create a product
    if (method === "POST" && path === "/api/products") {
      const body = (await req.json()) as CreateProductDTO;

      if (!body.name || typeof body.price !== "number") {
        return json({ error: "Missing required fields: 'name' (string) and 'price' (number)" }, 400);
      }

      const newProduct = store.create(body);
      return json(newProduct, 201);
    }

    // Check for parameter-based routes (/api/products/:id)
    const match = productItemPattern.exec(req.url);
    const id = match?.pathname.groups.id;

    if (id) {
      // 3. GET /api/products/:id -> Get single product
      if (method === "GET") {
        const product = store.getById(id);
        if (!product) return json({ error: "Product not found" }, 404);
        return json(product);
      }

      // 4. PUT /api/products/:id -> Update a product
      if (method === "PUT") {
        const body = (await req.json()) as UpdateProductDTO;
        const updated = store.update(id, body);
        if (!updated) return json({ error: "Product not found" }, 404);
        return json(updated);
      }

      // 5. DELETE /api/products/:id -> Delete a product
      if (method === "DELETE") {
        const deleted = store.delete(id);
        if (!deleted) return json({ error: "Product not found" }, 404);
        return json({ message: "Product deleted successfully" });
      }
    }

    // Route not found
    return json({ error: "Route not found" }, 404);
  } catch (error) {
    return json({ error: "Invalid JSON or server error", details: String(error) }, 500);
  }
});
```

## Step 4: Run & Test the API

Run the server with auto-reload (watch mode) and network permissions:



Bash

```
deno run --watch --allow-net server.ts
```

Your server will spin up on `http://localhost:8000`.



### Testing Endpoints with `curl`

* **Get all products:**



  Bash

  ```
  curl http://localhost:8000/api/products
  ```

* **Create a new product:**



  Bash

  ```
  curl -X POST http://localhost:8000/api/products \
    -H "Content-Type: application/json" \
    -d '{"name": "Gaming Monitor", "price": 350}'
  ```

* **Update a product** _(replace `PRODUCT_ID` with a generated UUID)_:



  Bash

  ```
  curl -X PUT http://localhost:8000/api/products/PRODUCT_ID \
    -H "Content-Type: application/json" \
    -d '{"price": 320}'
  ```

* **Delete a product:**

  Bash

  ```
  curl -X DELETE http://localhost:8000/api/products/PRODUCT_ID
  ```

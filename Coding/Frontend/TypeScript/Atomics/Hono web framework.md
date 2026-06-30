---
id: 20260516180044
tile: The Hono web framework
author: Karl Schmitt
date: 2026-05-16
keywords: [ TypeScript, Deno, Hono ]
---

# The Hono web framework

**Hono** is a small, fast, and ultra-lightweight web framework designed for the "Edge." It is built on Web Standards (Fetch API) and is designed to run on any JavaScript runtime, including Deno, Bun, Node.js, Cloudflare Workers, and Fastly.

As of 2025, it is one of the most popular choices for Deno developers because of its speed, excellent TypeScript support, and zero-dependency footprint.

---

### Key Features of Hono
*   **Ultrafast:** It uses a smart router (RegExpRouter) that is among the fastest in the ecosystem.
*   **Middleware support:** Built-in support for CORS, Logger, Basic Auth, JWT, and more.
*   **TypeScript-first:** Provides great IDE autocompletion and type safety.
*   **JSX Support:** You can use Hono to serve server-side rendered (SSR) components using JSX without needing React.
*   **Multi-runtime:** The same code can often run on Deno, Bun, or Cloudflare Workers without modification.

---

### How to use Hono with Deno

Deno makes using Hono very simple because it treats TypeScript as a first-class citizen and doesn't require a complex build step.

#### 1. Basic "Hello World"

Create a file named `main.ts`:

```typescript
import { Hono } from "jsr:@hono/hono";

const app = new Hono();

app.get("/", (c) => {
  return c.text("Hello Hono!");
});

app.get("/user/:name", (c) => {
  const name = c.req.param("name");
  return c.json({ message: `Hello, ${name}!` });
});

// Use Deno.serve to run the Hono app
Deno.serve(app.fetch);
```

**To run this:**
```bash
deno run --allow-net main.ts
```

---

#### 2. Using Middleware

Hono comes with powerful built-in middleware. 
Here is how you use them:

```typescript
import { Hono } from "jsr:@hono/hono";
import { logger, cors, prettyJSON } from "jsr:@hono/hono/middleware";

const app = new Hono();

// Add global middleware
app.use("*", logger());
app.use("*", cors());
app.use("*", prettyJSON());

app.get("/api/data", (c) => {
  return c.json({ success: true, timestamp: Date.now() });
});

Deno.serve(app.fetch);
```

---

#### 3. Handling POST Data & Validation

Hono works excellently with **Zod** for schema validation (via the Hono Zod Validator).

```typescript
import { Hono } from "jsr:@hono/hono";
import { z } from "npm:zod";
import { zValidator } from "npm:@hono/zod-validator";

const app = new Hono();

const schema = z.object({
  email: z.string().email(),
  password: z.string().min(8),
});

app.post("/register", zValidator("json", schema), (c) => {
  const data = c.req.valid("json");
  return c.json({ message: "User registered", user: data.email });
});

Deno.serve(app.fetch);
```

---

#### 4. SSR with JSX

Hono allows you to write HTML using JSX syntax directly in Deno. 
Rename your file to `main.tsx`:

```tsx
/** @jsxImportSource jsr:@hono/hono/jsx */
import { Hono } from "jsr:@hono/hono";

const app = new Hono();

app.get("/", (c) => {
  return c.html(
    <html>
      <body>
        <h1>Welcome to Hono on Deno</h1>
        <p>This is rendered using JSX!</p>
      </body>
    </html>
  );
});

Deno.serve(app.fetch);
```

---

### Why use Hono over Deno's native `Deno.serve`?
While `Deno.serve` is great for simple requests, Hono provides:
1.  **Complex Routing:** Easily handle URL parameters, wildcards, and nested routes.
2.  **Request/Response abstraction:** The `Context` object (`c`) simplifies sending JSON, setting headers, and handling cookies.
3.  **Consistency:** If you ever decide to move your project to Cloudflare Workers or Node.js, your Hono code will remain almost identical.

### Getting Started Checklist
1.  **Install Deno:** Ensure you have the latest version.
2.  **Initialize:** You can run `deno init` to create a `deno.json` file.
3.  **Imports:** Use the `jsr:` specifier (e.g., `jsr:@hono/hono`) as it is the modern standard for Deno packages.
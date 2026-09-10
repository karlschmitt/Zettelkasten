---
id: 20260910191333
title: Learning TypeScript with Deno
author: Karl Schmitt
date: 2026-09-10
keywords: [ TypeScript, Deno ]
---

![TypeScript Logo](../Images/Typescript_logo_2020.png)

# Learning TypeScript with Deno

One of Deno's biggest strengths is **native TypeScript support**. You do not need to install `typescript`, set up a `tsconfig.json`, or run a compilation step like `tsc`—Deno executes `.ts` files directly out of the box.

## Step 1: Rename Your File Extension

Change your file extension from `.js` to `.ts`:

Bash
```
mv app.js app.ts
```

## Step 2: Add Interfaces and Type Annotations

In TypeScript, you explicitly define the structure of your data using `interface` or `type`, and annotate variables and functions.

Here is the fully typed version of `app.ts`:

```powershell
ni app.ts
```
```typescript
// 1. Interfaces (Custom Data Shapes)
interface User {
  id: number;
  name: string;
  age: number;
  isLearning: boolean;
  email?: string; // Optional property
}

// 2. Strongly Typed Variables & Constants
const appName: string = "Deno TypeScript Tutorial";
let userCount: number = 1;

// 3. Typed Object Instantiation
const user: User = {
  id: 101,
  name: "Alex",
  age: 25,
  isLearning: true,
};

// 4. Function with Explicit Parameter and Return Types
function greet(person: User): string {
  return `Welcome ${person.name} (ID: ${person.id})! You are learning TypeScript with ${appName}.`;
}

// 5. Console Output
console.log(greet(user));
```

Run it directly using Deno without pre-compiling using the console:
```powershell
deno run app.ts
```

## Step 3: Type HTTP Requests & Web API Responses

When working with APIs in TypeScript, you can map the JSON response structure to an `interface`.

Create `fetch_data.ts` using the console:

```powershell
ni fetch_data.ts
```

```TypeScript
// Define the shape of the external API response
interface GeoLocation {
  lat: string;
  lng: string;
}

interface Address {
  street: string;
  suite: string;
  city: string;
  zipcode: string;
  geo: GeoLocation;
}

interface ApiUser {
  id: number;
  name: string;
  username: string;
  email: string;
  address: Address;
  phone: string;
  website: string;
}

// Async function returning a Promise typed with ApiUser
async function fetchUser(userId: number): Promise<ApiUser> {
  console.log(`Fetching data for user #${userId}...`);

  const response = await fetch(`https://jsonplaceholder.typicode.com/users/${userId}`);
  
  if (!response.ok) {
    throw new Error(`HTTP error! Status: ${response.status}`);
  }

  // Cast the JSON response to our ApiUser interface
  const data: ApiUser = await response.json();
  return data;
}

// Usage
try {
  const userData = await fetchUser(1);
  console.log(`User Name: ${userData.name}`);
  console.log(`Email: ${userData.email}`);
  console.log(`City: ${userData.address.city}`);
} catch (error) {
  console.error("Failed to fetch user:", error);
}
```

Run with network permissions using the console:
```typescript
deno run --allow-net fetch_data.ts
```

## Step 4: Type a Deno Web Server

When using Deno’s native server APIs, standard Web types like `Request` and `Response` are available globally:


Create `server.ts` using the console:
```PowerShell
ni server.ts
```
```TypeScript
// Deno.serve automatically types the request handler parameter as Request
Deno.serve((req: Request): Response => {
  const url = new URL(req.url);

  if (url.pathname === "/json") {
    const payload = { status: "success", timestamp: Date.now() };
    return Response.json(payload);
  }

  return new Response("Hello from Deno with TypeScript!");
});
```

Run the server using the console:
```powershell
deno run --allow-net server.ts
```

## Built-In Type Checking Commands

While `deno run` checks types automatically, you can explicitly type-check your code without executing it:

* **Check types across your project using the console:**
```typescript
  deno check app.ts
  ```
* **Lint for TypeScript best practices using the console:**
  ```typescript
  deno lint
  ```

---
id: 20260516195237
title: Strings in TypeScript
author: Karl Schmitt
date: 2026-05-16
keywords: [ TypeScript, string ]
---

# Strings in Typescript

 TypeScript allows you to be very specific about **which** strings are allowed, how they are formatted, and even how to transform them at the type level.

Here are the primary ways to handle strings in TypeScript:

---

### 1. Basic String Type

This is the standard way to say a variable can be any text.
```typescript
let message: string = "Hello World";
```

### 2. String Literal Types (Specific Strings)

You can restrict a variable to only allow **exact** specific strings. This is incredibly powerful for settings, modes, or status codes.
```typescript
type Status = "success" | "error" | "loading";

let currentStatus: Status = "success"; 
// currentStatus = "finished"; // ❌ Error: "finished" is not allowed
```

### 3. Template Literal Types

Introduced in TS 4.1, this allows you to create new types by combining strings using a syntax similar to JavaScript template literals.

```typescript
type World = "world";
type Greeting = `hello ${World}`; 
// The type of Greeting is literally "hello world"

type Size = "small" | "medium" | "large";
type Color = "primary" | "secondary";

// This automatically generates 6 combinations: "primary-small", "primary-medium", etc.
type ButtonClass = `${Color}-${Size}`;
```

### 4. String Manipulation Utilities

TypeScript provides built-in types to transform the casing of string literal types.

*   `Uppercase<StringType>`
*   `Lowercase<StringType>`
*   `Capitalize<StringType>`
*   `Uncapitalize<StringType>`

```typescript
type GetterName<T extends string> = `get${Capitalize<T>}`;

type User = "user";
type FnName = GetterName<User>; // Type becomes "getUser"
```

### 5. String Enums

If you want to create a set of named constants that map to strings, use an `enum`. This is useful when you want a clear name for a value that might change.
```typescript
enum API_ROUTES {
  GET_USERS = "/api/v1/users",
  CREATE_USER = "/api/v1/create"
}

console.log(API_ROUTES.GET_USERS); // "/api/v1/users"
```

### 6. The `as const` Assertion

When you define an object or an array, TypeScript usually "widens" strings to the general `string` type. Using `as const` forces TypeScript to treat the strings as exact, immutable literal values.

```typescript
// Without 'as const', config.mode is type 'string'
// With 'as const', config.mode is type 'dark'
const config = {
  mode: "dark",
  port: 8080
} as const;
```

### 7. String indexing (Keyof)

You can ensure a string matches the keys of an object. This is very common in web frameworks.
```typescript
const roles = {
  admin: 1,
  editor: 2,
  viewer: 3
};

// Role can only be "admin", "editor", or "viewer"
type Role = keyof typeof roles;

function getPermissions(role: Role) {
  return roles[role];
}
```

### Summary Table

| Feature | Syntax Example | Purpose |
| :--- | :--- | :--- |
| **Type Annotation** | `name: string` | Any string is valid. |
| **Union Literals** | `"red" \| "blue"` | Only specific strings are valid. |
| **Template Type** | `icon-${string}` | Strings that start with "icon-". |
| **Capitalize** | `Capitalize<"hi">` | Changes type to "Hi". |
| **as const** | `"hello" as const` | Prevents the type from widening to `string`. |

**Pro Tip for Hono/Deno:**
When using Hono, you often use **Template Literal Types** to define route parameters. For example:
```typescript
app.get("/posts/:id", (c) => {
  const id = c.req.param("id"); // TypeScript knows 'id' is a string
});
```
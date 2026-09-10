---
id: 20260910145720
title: Learning TypeScript with Deno and PowerShell
author: Karl Schmitt
date: 2026-09-10
keywords: [ PowerShell, TypeScript, Deno ]
---

# Learning TypeScript with Deno and PowerShell

Deno runs TypeScript directly and includes a formatter, linter, test runner, and secure permissions by default.

## 1. Install Deno

Open PowerShell and run:

```powershell
irm https://deno.land/install.ps1 | iex
```

Restart PowerShell, then verify the installation:

```powershell
deno --version
```

If `deno` is not recognized, add Deno's binary directory to your `PATH`:

```text
$HOME\.deno\bin
```

## 2. Create a project

```powershell
mkdir deno-typescript
cd deno-typescript
deno init
```

This creates files such as:

```text
main.ts
main_test.ts
deno.json
```

Run the example:

```powershell
deno run main.ts
```

## 3. Write a TypeScript program

Replace `main.ts` with:

```typescript
interface User {
  name: string;
  age: number;
}

function introduce(user: User): string {
  return `${user.name} is ${user.age} years old.`;
}

const user: User = {
  name: "Alice",
  age: 30,
};

console.log(introduce(user));
```

Run it:

```powershell
deno run main.ts
```

Output:

```text
Alice is 30 years old.
```

## 4. Use command-line arguments

```typescript
const name = Deno.args[0] ?? "World";

console.log(`Hello, ${name}!`);
```

Run it from PowerShell:

```powershell
deno run main.ts TypeScript
```

Output:

```text
Hello, TypeScript!
```

## 5. Read a file

Create a file from PowerShell:

```powershell
"Learning TypeScript with Deno" | Set-Content notes.txt
```

Update `main.ts`:

```typescript
const text = await Deno.readTextFile("notes.txt");

console.log(text);
```

Deno requires explicit permission to access files:

```powershell
deno run --allow-read main.ts
```

Without `--allow-read`, Deno blocks the file operation.

## 6. Create a small HTTP server

```typescript
Deno.serve((_request) => {
  return new Response("Hello from Deno and TypeScript!");
});
```

Run it:

```powershell
deno run --allow-net main.ts
```

Open `http://localhost:8000` in a browser. Stop the server with `Ctrl+C`.

## 7. Import a module

Deno supports JSR package imports:

```typescript
import { assertEquals } from "jsr:@std/assert";

assertEquals(2 + 2, 4);
```

## 8. Write tests

Create `main_test.ts`:

```typescript
import { assertEquals } from "jsr:@std/assert";

function add(first: number, second: number): number {
  return first + second;
}

Deno.test("adds two numbers", () => {
  assertEquals(add(2, 3), 5);
});
```

Run the tests:

```powershell
deno test
```

## 9. Format and lint code

```powershell
deno fmt
deno lint
```

Check formatting without changing files:

```powershell
deno fmt --check
```

## 10. Define project tasks

Update `deno.json`:

```json
{
  "tasks": {
    "start": "deno run --allow-net main.ts",
    "test": "deno test",
    "check": "deno fmt --check && deno lint && deno check main.ts"
  }
}
```

Run tasks from PowerShell:

```powershell
deno task start
deno task test
deno task check
```

## Useful PowerShell commands

```powershell
Get-ChildItem              # List files
Get-Content main.ts        # Display a file
New-Item app.ts            # Create a file
Remove-Item app.ts         # Delete a file
Set-Location .\src         # Change directory
Get-Location               # Show current directory
```

A typical workflow is:

```powershell
deno init
deno task check
deno test
deno task start
```

## Deno permission flags

```text
--allow-read   File system read access
--allow-write  File system write access
--allow-net    Network access
--allow-env    Environment variable access
--allow-run    Running subprocesses
```

Use the narrowest permissions your program needs.

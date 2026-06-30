---
id: 20260524181128
title: TypeScript Generics Bootcamp
author: Karl Schmitt
date: 2026-05-24
keywords: [ TypeScript, generics, bootcamp, Deno, PowerShell]
---

# TypeScript Generics Bootcamp

Using TypeScript + Deno + PowerShell

This bootcamp teaches Generics from beginner to advanced level using practical examples and a real project structure.

By the end you will understand:

* Generic functions

* Generic classes

* Generic interfaces

* Constraints

* Utility types

* Reusable architectures

* Repository patterns

* Type-safe collections

* Advanced TypeScript typing

***

# What Are Generics?

Generics allow reusable code while preserving type safety.

Without generics:

```typescript
function echo(value: any): any {
  return value;
}
```

Problem:

```text
No type safety.
```

With generics:

```typescript
function echo<T>(value: T): T {
  return value;
}
```

Now TypeScript remembers the exact type.

***

# Project Setup

***

# Create Project

```powershell
mkdir ts-generics-bootcamp
cd ts-generics-bootcamp
code .
```

***

# Create Structure

```powershell
mkdir src
mkdir src\models
mkdir src\repositories
mkdir src\services
mkdir src\utils
```

***

# Run Files

```powershell
deno run src/main.ts
```

***

# Module 1 — Generic Functions

***

# Basic Generic Function

## src/main.ts

```typescript
function identity<T>(value: T): T {
  return value;
}

const numberValue = identity<number>(42);

const stringValue = identity<string>("hello");

console.log(numberValue);
console.log(stringValue);
```

***

# How It Works

```typescript
<T>
```

means:

```text
“Type placeholder”
```

***

# Type Inference

Usually TypeScript infers automatically:

```typescript
const value = identity("hello");
```

No explicit type needed.

***

# Exercise

Create generic functions:

```text
wrap()
firstElement()
lastElement()
```

***

# Example

```typescript
function firstElement<T>(arr: T[]): T {
  return arr[0];
}
```

***

# Module 2 — Generic Arrays

***

# Example

```typescript
const numbers: Array<number> = [1, 2, 3];

const names: Array<string> = [
  "Anna",
  "Karl"
];
```

Equivalent to:

```typescript
const numbers: number[] = [1, 2, 3];
```

***

# Generic Array Function

```typescript
function printArray<T>(items: T[]): void {
  for (const item of items) {
    console.log(item);
  }
}
```

***

# Exercise

Create:

```text
sumArray()
reverseArray()
mergeArrays()
```

***

# Module 3 — Generic Interfaces

***

# Example

```typescript
interface ApiResponse<T> {
  success: boolean;
  data: T;
}
```

***

# Usage

```typescript
const response: ApiResponse<string> = {
  success: true,
  data: "Hello"
};
```

***

# Real Example

```typescript
interface Character {
  name: string;
  level: number;
}

const playerResponse: ApiResponse<Character> = {
  success: true,
  data: {
    name: "Knight",
    level: 10
  }
};
```

***

# Exercise

Create:

```text
DatabaseResult<T>
PaginatedResult<T>
GameSave<T>
```

***

# Module 4 — Generic Classes

***

# Example

## src/models/storage.ts

```typescript
export class StorageBox<T> {
  private items: T[] = [];

  add(item: T): void {
    this.items.push(item);
  }

  getAll(): T[] {
    return this.items;
  }
}
```

***

# Usage

## src/main.ts

```typescript
import { StorageBox } from "./models/storage.ts";

const numberBox = new StorageBox<number>();

numberBox.add(10);
numberBox.add(20);

console.log(numberBox.getAll());

const stringBox = new StorageBox<string>();

stringBox.add("hello");

console.log(stringBox.getAll());
```

***

# Exercise

Create generic classes:

```text
Inventory<T>
Queue<T>
Stack<T>
Cache<T>
```

***

# Module 5 — Generic Constraints

***

# Problem

Sometimes you need specific properties.

***

# Example

```typescript
function printLength<T>(item: T): void {
  console.log(item.length);
}
```

This fails because not every type has:

```typescript
length
```

***

# Solution — Constraints

```typescript
interface HasLength {
  length: number;
}

function printLength<T extends HasLength>(
  item: T
): void {
  console.log(item.length);
}
```

***

# Usage

```typescript
printLength("hello");

printLength([1, 2, 3]);
```

***

# Exercise

Create constraints for:

```text
id
name
health
```

***

# Module 6 — keyof with Generics

***

# Example

```typescript
function getProperty<T, K extends keyof T>(
  obj: T,
  key: K
): T[K] {
  return obj[key];
}
```

***

# Usage

```typescript
const player = {
  name: "Knight",
  level: 10
};

console.log(
  getProperty(player, "name")
);
```

***

# Why Important?

This powers advanced libraries and frameworks.

***

# Exercise

Create:

```text
updateProperty()
pickFields()
sortByKey()
```

***

# Module 7 — Generic Repositories

***

# Repository Pattern

A repository stores entities.

***

# Generic Repository

## src/repositories/repository.ts

```typescript
export class Repository<T> {
  protected items: T[] = [];

  add(item: T): void {
    this.items.push(item);
  }

  getAll(): T[] {
    return this.items;
  }
}
```

***

# Usage

```typescript
interface Player {
  name: string;
}

const playerRepo = new Repository<Player>();

playerRepo.add({
  name: "Knight"
});

console.log(playerRepo.getAll());
```

***

# Exercise

Add:

```text
remove()
find()
update()
count()
```

***

# Module 8 — Generic Services

***

# Example

```typescript
export class ApiService<T> {
  async save(data: T): Promise<void> {
    console.log("Saving", data);
  }
}
```

***

# Usage

```typescript
const service =
  new ApiService<string>();

await service.save("hello");
```

***

# Exercise

Create:

```text
SaveService<T>
EventBus<T>
StateManager<T>
```

***

# Module 9 — Utility Types

TypeScript includes built-in generic utility types.

***

# Partial

```typescript
interface Player {
  name: string;
  health: number;
}

const update: Partial<Player> = {
  health: 50
};
```

***

# Required

```typescript
Required<Player>
```

***

# Readonly

```typescript
Readonly<Player>
```

***

# Pick

```typescript
Pick<Player, "name">
```

***

# Omit

```typescript
Omit<Player, "health">
```

***

# Record

```typescript
Record<string, number>
```

***

# Exercise

Experiment with all utility types.

***

# Module 10 — Advanced Generics

***

# Multiple Generic Types

```typescript
function pair<T, U>(
  first: T,
  second: U
) {
  return [first, second];
}
```

***

# Generic Defaults

```typescript
class ApiResponse<T = string> {
  constructor(public data: T) {}
}
```

***

# Conditional Types

```typescript
type IsString<T> =
  T extends string ? true : false;
```

***

# Mapped Types

```typescript
type Optional<T> = {
  [K in keyof T]?: T[K];
};
```

***

# Exercise

Build:

```text
Nullable<T>
Optional<T>
DeepReadonly<T>
```

***

# Module 11 — Real-World Inventory System

***

# Models

## item.ts

```typescript
export interface Item {
  id: number;
  name: string;
}
```

***

# inventory.ts

```typescript
export class Inventory<T> {
  private items: T[] = [];

  add(item: T): void {
    this.items.push(item);
  }

  getAll(): T[] {
    return this.items;
  }
}
```

***

# main.ts

```typescript
import { Inventory } from "./models/inventory.ts";
import { Item } from "./models/item.ts";

const inventory = new Inventory<Item>();

inventory.add({
  id: 1,
  name: "Sword"
});

inventory.add({
  id: 2,
  name: "Shield"
});

console.log(inventory.getAll());
```

***

# Module 12 — Deno File Persistence

***

# Save Generic Data

```typescript
async function saveToFile<T>(
  filename: string,
  data: T
): Promise<void> {

  await Deno.writeTextFile(
    filename,
    JSON.stringify(data, null, 2)
  );
}
```

***

# Usage

```typescript
await saveToFile(
  "save.json",
  inventory.getAll()
);
```

Run:

```powershell
deno run --allow-write src/main.ts
```

***

# Module 13 — Testing Generics

***

# test.ts

```typescript
import {
  assertEquals
} from "jsr:@std/assert";

Deno.test("inventory adds items", () => {

  const inventory =
    new Inventory<string>();

  inventory.add("Sword");

  assertEquals(
    inventory.getAll().length,
    1
  );
});
```

Run:

```powershell
deno test
```

***

# PowerShell Workflow

***

# Run Project

```powershell
deno run src/main.ts
```

***

# Watch Mode

```powershell
deno run --watch src/main.ts
```

***

# Format

```powershell
deno fmt
```

***

# Lint

```powershell
deno lint
```

***

# Type Check

```powershell
deno check src/main.ts
```

***

# Best Practices

***

# Use Meaningful Generic Names

Good:

```typescript
<TItem>
<TResponse>
<TData>
```

Avoid:

```typescript
<TTT>
```

***

# Prefer Constraints

Avoid overly broad:

```typescript
<any>
```

***

# Use Interfaces

Generics work beautifully with interfaces.

***

# Keep Generic APIs Small

Simple APIs are easier to maintain.

***

# Common Real-World Uses

Generics power:

* Repositories

* Collections

* APIs

* React hooks

* Angular services

* State managers

* ORMs

* Validation systems

* Event buses

* Data stores

***

# Final Challenge Project

Build:

# Generic RPG Engine

Features:

* Generic inventory

* Generic repository

* Generic save system

* Generic event system

* Generic state manager

* Generic cache

***

# Recommended Next Topics

After Generics learn:

1. Advanced TypeScript Types

2. Design Patterns

3. SOLID principles

4. Dependency Injection

5. Clean Architecture

6. CQRS

7. Domain-Driven Design

8. Event-driven systems

9. Functional programming in TypeScript

10. Advanced async architectures

***

# Excellent Resources

* [TypeScript Generics Handbook](https://www.typescriptlang.org/docs/handbook/2/generics.html?utm_source=chatgpt.com)

* [Deno Documentation](https://docs.deno.com/?utm_source=chatgpt.com)

* [PowerShell Documentation](https://learn.microsoft.com/powershell/?utm_source=chatgpt.com)

* [MDN JavaScript Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide?utm_source=chatgpt.com)

***

If you want, I can also provide:

* A **7-Day TypeScript Generics Bootcamp**

* A **30-Day Advanced TypeScript Roadmap**

* A **TypeScript Utility Types Deep Dive**

* A **Repository Pattern tutorial**

* A **Dependency Injection tutorial**

* A **Design Patterns Bootcamp**

* A **TypeScript Advanced Types Masterclass**

* A **Clean Architecture tutorial using Deno**

---
id: 20260909223155
title: Learning TypeScript
author: Karl Schmitt
date: 2026-09-09
keywords: [ TypeScript ]
---

![TypeScript Logo](../Images/Typescript_logo_2020.png)

# Learning TypeScript

Here is a hands-on, beginner-friendly TypeScript tutorial. It covers the absolute essentials you need to start writing typed code immediately.

> [NOTE!]
>  Feel free to follow the white rabut 🐇: [Learn TypeScript](../Atoms/TypeScript.md)

> [NOTE!]
>  Feel free to follow the dinosaur 🦖: [Learning TypeScript with Deno](../Atoms/Learning_TypeScript_with_Deno.md)

***

## 🚀 Step 1: The "Hello World" Setup

TypeScript cannot run directly in the browser; it must be converted (compiled) into JavaScript.

1. Create a directory: ```mkdir Learning-TypeScript```
2. Create a file named `app.ts`. PowerShell: ```ni app.ts ```
3. Add this code:
   ```typescript
   let message: string = "Hello, TypeScript!";
   console.log(message);
   ```
4. Compile it: Open your terminal and run:
   ```bash
   tsc app.ts
   ```
   _This automatically generates a new file called `app.js` containing plain JavaScript that any browser or server can read._

***

## 🎨 Step 2: Working with Basic Types

In JavaScript, a variable can hold a string, then a number, then a boolean. TypeScript prevents this chaos by forcing you to declare the data type using a type annotation (`: type`).

```typescript
// Explicitly typed primitives
let username: string = "Alex";
let age: number = 28;
let isDeveloper: boolean = true;

// TypeScript infers types automatically too! 
// If you don't declare it, TS knows 'score' is a number.
let score = 100; 

// ❌ This will trigger an immediate error in your editor:
age = "twenty-eight"; // Error: Type 'string' is not assignable to type 'number'.
```

***

## 📐 Step 3: Typing Functions

TypeScript requires you to explicitly state what types a function accepts as parameters and what type it will return.

```typescript
// The function expects two numbers and MUST return a number
function addNumbers(a: number, b: number): number {
    return a + b;
}

// Valid usage
let result = addNumbers(5, 10); 

// ❌ Invalid usage caught by the compiler
addNumbers(5, "10"); // Error: Argument of type 'string' is not assignable...
```

***

## 🗂 Step 4: Objects and Interfaces

When dealing with objects, you can use an `interface` to create a strict blueprint/contract of what properties the object must have.

```typescript
// Define the blueprint
interface User {
    id: number;
    name: string;
    isAdmin: boolean;
    email?: string; // The '?' means this property is optional
}

// Apply the blueprint to an object
const profile: User = {
    id: 1,
    name: "Sarah Jones",
    isAdmin: false
    // email is omitted, which is fine because it's optional
};

// ❌ Error: Missing required property 'isAdmin'
const brokenProfile: User = {
    id: 2,
    name: "John Doe"
};
```

***

## 🔀 Step 5: Union Types

Sometimes a value legitimately needs to be more than one thing. A Union Type allows a variable to hold one of a few specified types using the pipe (`|`) symbol.

```typescript
// The ID could be a numeric database ID OR a UUID string
function printId(id: number | string) {
    console.log(`Your ID is: ${id}`);
}

printId(101);      // ✅ Valid
printId("ax92j");  // ✅ Valid
printId(true);     // ❌ Error: Argument of type 'boolean' is not assignable...
```

***

## ⚡ Step 6: Arrays and Tuples

You can specify exactly what type of items a list is allowed to hold.

```typescript
// Array of strings only
let shoppingList: string[] = ["Apples", "Milk", "Bread"];
shoppingList.push("Eggs"); // ✅ Valid
shoppingList.push(42);     // ❌ Error

// Tuples: Arrays with a fixed number of elements and specific types in order
let coordinates: [number, number] = [40.7128, -74.0060]; // [Latitude, Longitude]
```

***

## 🛠 Try it Online Instantly

You don't even need to install anything to practice. Go to the official [TypeScript Playground](https://www.typescriptlang.org/play) to type this code out, view errors in real-time, and see the matching JavaScript output.

Would you like to expand this tutorial into Generics, show how to connect it to a framework like React/Next.js, or write a practical mini-project (like a Todo app logic)?


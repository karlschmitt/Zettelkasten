---
id: 20260920130328
title: TypeScript Bootcamp Using tsc
author: Karl Schmitt
date: 2026-09-20
keywords: [ TypeScript ]
---


Here is a complete, step-by-step **TypeScript Bootcamp** you can run directly on your machine using VS Code and PowerShell.



## Step 1: Initialize Your Local Workspace

Open **PowerShell**, create a dedicated project folder, navigate into it, and open VS Code:



PowerShell

```
mkdir ts-bootcamp
cd ts-bootcamp
code .
```

Inside VS Code, open the integrated terminal (`Ctrl + ~`) and verify if the TypeScript compiler (`tsc`) is available globally, or install it locally:



PowerShell

```
# Check if TypeScript is installed globally
tsc -v

# If not installed or if you want a local project dependency, run:
npm init -y
npm install -D typescript
```

## Step 2: Configure TypeScript (`tsconfig.json`)

Generate a clean configuration file to control compiler options and strict type-checking:



PowerShell

```
npx tsc --init
```

Open the generated `tsconfig.json` file and make sure these core options are enabled for the bootcamp:



* `"target": "ES2022"` (or latest)


* `"strict": true` (enables comprehensive type checking)


* `"noUnusedLocals": true`


* `"noUnusedParameters": true`



## Step 3: Bootcamp Curriculum & Hands-On Exercises

Create a folder named `src` inside your workspace and tackle these modules sequentially. You can execute any module using PowerShell with `npx tsc` followed by `node`, or use `npx ts-node` if you prefer direct execution.



### Module 1: Primitives, Type Inference, and Arrays (`src/01-basics.ts`)

Create `src/01-basics.ts`:



TypeScript

```
// Explicit typing vs Type inference
let courseName: string = "TypeScript Bootcamp";
let studentCount = 42; // Inferred as number

// Arrays and Tuples
let modules: string[] = ["Basics", "Functions", "Interfaces", "Generics"];
let userScore: [string, number] = ["Alice", 95]; // Tuple: fixed length & types

// Union Types
let statusCode: string | number = 200;
statusCode = "OK"; // Valid

console.log(`Welcome to ${courseName}! Students enrolled: ${studentCount}`);
```

**Run it via PowerShell:**



PowerShell

```
npx tsc
node src/01-basics.js
```

### Module 2: Advanced Functions & Arrow Functions (`src/02-functions.ts`)

Create `src/02-functions.ts`:



TypeScript

```
// Optional and Default parameters
const createUser = (name: string, role: string = "Developer", age?: number): string => {
  return `User: ${name}, Role: ${role}${age ? `, Age: ${age}` : ""}`;
};

// Function Overloads
function getLength(value: string): number;
function getLength(value: any[]): number;
function getLength(value: string | any[]): number {
  return value.length;
}

console.log(createUser("Bob"));
console.log(getLength("TypeScript"));
console.log(getLength([1, 2, 3, 4]));
```

### Module 3: Interfaces & Custom Types (`src/03-interfaces.ts`)

Create `src/03-interfaces.ts`:



TypeScript

```
interface UserProfile {
  readonly id: string; // Cannot be modified after creation
  username: string;
  email: string;
  age?: number;        // Optional property
}

interface AdminProfile extends UserProfile {
  permissions: string[];
}

const admin: AdminProfile = {
  id: "USR-001",
  username: "code_master",
  email: "admin@bootcamp.test",
  permissions: ["read", "write", "execute"]
};

console.log(`Admin user: ${admin.username} with permissions: ${admin.permissions.join(", ")}`);
```

### Module 4: Generics (Reusable Components) (`src/04-generics.ts`)

Create `src/04-generics.ts`:



TypeScript

```
// Generic function that accepts any data type safely
function wrapInArray<T>(item: T): T[] {
  return [item];
}

const stringArray = wrapInArray("Hello TypeScript");
const numberArray = wrapInArray(100);

console.log(stringArray);
console.log(numberArray);

// Generic Interface
interface Box<T> {
  value: T;
}

const numericBox: Box<number> = { value: 500 };
console.log(`Box value: ${numericBox.value}`);
```

## Pro-Tips for Your VS Code Workflow

1. **Watch Mode:** Instead of manually running `npx tsc` every time, run the compiler in **watch mode** inside a split PowerShell terminal:



   PowerShell

   ```
   npx tsc --watch
   ```

   This watches your `.ts` files for saves and recompiles them to `.js` instantly.



2. **Task Automation:** You can press `Ctrl + Shift + B` in VS Code to trigger the built-in TypeScript build task.



Which module or concept would you like to explore or expand next?

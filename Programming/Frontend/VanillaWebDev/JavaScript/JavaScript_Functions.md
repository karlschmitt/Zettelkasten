---
id: 20260415195940
title: JavaScript Functions
subtitle: The work horse of JavaScript
date: 2025-04-15
---

# JavaScript Functions

Deno is a modern runtime for JavaScript and TypeScript. Since Deno uses the V8 engine (the same as Chrome and Node.js), JavaScript functions work exactly the same way as they do in the browser, but with the added benefit of modern features like **ES Modules** being the default.

Here is an explanation of JavaScript functions using Deno.

---

### 1. Basic Function Declaration
The most traditional way to write a function.

**File:** `functions.js`
```javascript
function greet(name) {
  return `Hello, ${name}!`;
}

console.log(greet("Deno User"));
```
**To run:** `deno run functions.js`

---

### 2. Arrow Functions (Modern Syntax)
Arrow functions are the standard in modern JavaScript development. They are shorter and handle the `this` keyword differently (lexical scoping).

```javascript
const add = (a, b) => a + b;

const result = add(5, 10);
console.log(`The sum is: ${result}`);
```

---

### 3. Default Parameters
Deno supports modern ES6+ features out of the box. You can set default values for function arguments.

```javascript
function createUser(name, role = "Guest") {
  console.log(`User: ${name}, Role: ${role}`);
}

createUser("Alice");          // User: Alice, Role: Guest
createUser("Bob", "Admin");   // User: Bob, Role: Admin
```

---

### 4. Async Functions (Crucial for Deno)
Deno was built around `async/await`. Most Deno APIs (like reading files or fetching data) return **Promises**.

```javascript
// A function that fetches data from an API
async function getStatus() {
  const response = await fetch("https://api.github.com");
  const data = await response.json();
  return response.status;
}

const status = await getStatus(); // Deno supports top-level await!
console.log(`Github API Status: ${status}`);
```
*Note: In Deno, you can use `await` at the top level of your file without wrapping it in an async function.*

---

### 5. Exporting and Importing Functions
Deno uses **ES Modules (ESM)**. Unlike Node.js (which historically used `module.exports`), Deno uses `export` and `import`.

**File:** `math_utils.js`
```javascript
export function multiply(a, b) {
  return a * b;
}

export const PI = 3.14159;
```

**File:** `main.js`
```javascript
import { multiply, PI } from "./math_utils.js";

console.log(multiply(10, PI));
```
**To run:** `deno run main.js`

---

### 6. Functions as Arguments (Callbacks)
In JavaScript, functions are "first-class citizens," meaning you can pass them into other functions. This is heavily used in Deno's standard library.

```javascript
const numbers = [1, 2, 3, 4, 5];

// The .map() method takes a function as an argument
const doubled = numbers.map((n) => n * 2);

console.log(doubled); // [2, 4, 6, 8, 10]
```

---

### 7. Anonymous Functions and IIFE
Sometimes you need a function that runs immediately and doesn't need a name.

```javascript
// Immediately Invoked Function Expression (IIFE)
(() => {
  console.log("This runs immediately!");
})();
```

---

### Why Deno is great for learning JS Functions:
1.  **No Configuration:** You don't need a `package.json` or a complex build step. Just write a `.js` file and run it.
2.  **TypeScript Support:** If you want to add types to your functions (e.g., `function add(a: number, b: number)`), you can just change the file extension to `.ts` and Deno handles it automatically.
3.  **Modern Defaults:** It forces you to use modern `import/export` syntax, which is the standard for the web today.

### How to Run Your Code
1. Install Deno (from [deno.com](https://deno.com)).
2. Create a file named `app.js`.
3. Paste any of the code above.
4. Open your terminal and run:
   ```bash
   deno run app.js
   ```
   *(Note: If your function uses the network, like the `fetch` example, run: `deno run --allow-net app.js`)*
# 20260413224520 Exploring primitive JavaScript data types using Deno

Deno is an excellent environment for exploring JavaScript because it supports the latest ECMAScript standards out of the box with zero configuration.

To explore primitive data types in Deno, you can use the **REPL (Read-Eval-Print Loop)** or run a **script file**.

### 1. Using the Deno REPL
The REPL is the fastest way to experiment. Open your terminal and type:
```bash
deno
```
You will see a prompt (`>`). You can now type JavaScript directly.

### 2. Exploring the 7 Primitive Types
JavaScript has 7 primitive types. Here is how to identify and explore them using the `typeof` operator in Deno.

#### A. String
Used for textual data.
```javascript
> const name = "Deno";
> typeof name
"string"
```

#### B. Number
Used for both integers and floating-point numbers. It also includes `Infinity` and `NaN`.
```javascript
> const age = 2024;
> const price = 19.99;
> typeof age
"number"
> typeof NaN
"number"
```

#### C. BigInt
Used for integers larger than the `Number` limit ($2^{53} - 1$). Created by appending `n` to an integer.
```javascript
> const bigNumber = 9007199254740991n;
> typeof bigNumber
"bigint"
```

#### D. Boolean
Logical entities: `true` and `false`.
```javascript
> const isModern = true;
> typeof isModern
"boolean"
```

#### E. Undefined
A variable that has been declared but not assigned a value.
```javascript
> let x;
> typeof x
"undefined"
```

#### F. Null
Represents the intentional absence of any object value. 
*Note: `typeof null` returns `"object"`. This is a historical bug in JavaScript, but it is considered a primitive.*
```javascript
> const empty = null;
> typeof empty
"object" 
```

#### G. Symbol
Used to create unique identifiers for objects.
```javascript
> const id = Symbol("id");
> typeof id
"symbol"
```

---

### 3. Creating an Exploration Script
Instead of the REPL, you can create a file named `primitives.js` to see them all at once.

**primitives.js**
```javascript
const primitives = [
  "Hello Deno",           // string
  42,                     // number
  100n,                   // bigint
  true,                   // boolean
  undefined,              // undefined
  null,                   // null
  Symbol("unique")        // symbol
];

console.table(primitives.map(p => ({
  value: String(p),
  type: typeof p
})));
```

**Run it in your terminal:**
```bash
deno run primitives.js
```

### Why use Deno for this?
1.  **No Config:** You don't need a `package.json` or a complex build step to test modern features like BigInt or top-level `await`.
2.  **TypeScript Support:** If you rename your file to `primitives.ts`, Deno will provide instant type-checking, which helps you understand the boundaries of these primitive types (e.g., preventing you from adding a `string` to a `symbol`).
3.  **Strict Mode:** Deno executes code in strict mode by default, which helps catch common JavaScript mistakes.
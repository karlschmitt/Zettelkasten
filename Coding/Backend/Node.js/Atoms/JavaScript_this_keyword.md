---
id: 20260912130234
title: JavaScript this keyword
author: Karl Schmitt
date: 2026-09-12
---

# JavaScript this keyword

The `this` keyword in JavaScript refers to the object executing the current function. Unlike variables in scope, the value of `this` is not static—it is determined dynamically by **how a function is invoked** (with the exception of arrow functions, which inherit it lexically).

![JavaScript Logo](../Images/JavaScript_Logo.png)

## The 6 Execution Contexts

```
                       Where is `this` evaluated?
                                   │
      ┌────────────────────────────┼────────────────────────────┐
      ▼                            ▼                            ▼
 Global Scope                 Functions                   Arrow Functions
  (Window/                     Depends on                  Inherits from
   global)                      Invocation                 Lexical Scope
                                   │
               ┌───────────────────┼───────────────────┐
               ▼                   ▼                   ▼
        Direct Call           Method Call         `new` Keyword
       (window/undefined)     (Owner Object)      (New Object)
```

## 1. Global Scope

Outside of any function, `this` refers to the global execution context.



* **Browsers:** `this` points to `window`.


* **Node.js:** `this` at the top level of a module points to `module.exports`.



JavaScript

```
console.log(this === window); // true (in browser)
```

## 2. Plain Function Invocation

When calling a standalone function directly (e.g., `fn()`), the behavior depends on whether **Strict Mode** is enabled.



* **Non-Strict Mode:** `this` defaults to the global object (`window` or `global`).


* **Strict Mode (`'use strict'`):** `this` is `undefined` to prevent accidental global modifications.



JavaScript

```
function showThis() {
  console.log(this);
}

showThis(); // Prints Window (Non-strict)

function showThisStrict() {
  'use strict';
  console.log(this);
}

showThisStrict(); // Prints undefined
```

## 3. Object Method Invocation

When a function is called as a property of an object (e.g., `obj.method()`), `this` refers to the **object preceding the dot**.



JavaScript

```
const user = {
  name: "Alex",
  greet() {
    console.log(`Hello, I'm ${this.name}`);
  }
};

user.greet(); // "Hello, I'm Alex" (`this` = user)
```

### The "Losing `this`" Gotcha

If you extract a method into a standalone variable, you detach it from its parent object:



JavaScript

```
const detachedGreet = user.greet;
detachedGreet(); // "Hello, I'm undefined" (`this` falls back to global/undefined)
```

## 4. Arrow Functions (Lexical Scope)

Arrow functions **do not** have their own `this` binding. Instead, they capture `this` from their outer enclosing execution context at the moment they are created.



JavaScript

```
const counter = {
  count: 0,
  startTimer() {
    // Traditional callback loses `this` (defaults to window)
    // Arrow function captures `this` from `startTimer()` (`this` = counter)
    setInterval(() => {
      this.count++;
      console.log(this.count);
    }, 1000);
  }
};

counter.startTimer(); // Prints 1, 2, 3...
```

## 5. Explicit Binding (`call`, `apply`, `bind`)

JavaScript lets you explicitly control what `this` refers to regardless of how the function is invoked.



* `call(thisArg, arg1, arg2, ...)`: Invokes the function immediately, passing arguments individually.


* `apply(thisArg, [argsArray])`: Invokes the function immediately, passing arguments as an array.


* `bind(thisArg, arg1, arg2, ...)`: Returns a **new function** permanently bound to `thisArg`.



JavaScript

```
function introduce(language, location) {
  console.log(`I'm ${this.name}, coding in ${language} from ${location}.`);
}

const developer = { name: "Jordan" };

// 1. call
introduce.call(developer, "JavaScript", "Berlin");

// 2. apply
introduce.apply(developer, ["Python", "Remote"]);

// 3. bind
const boundFn = introduce.bind(developer, "TypeScript");
boundFn("London"); // I'm Jordan, coding in TypeScript from London.
```

## 6. Constructor & Class Invocation (`new` Keyword)

When a function or class constructor is invoked with the `new` keyword:



1. A new empty object `{}` is created.


2. `this` inside the function is bound to that new object.


3. The function executes, assigning properties to `this`.


4. The object is implicitly returned (unless another object is returned explicitly).



JavaScript

```
class Car {
  constructor(brand) {
    this.brand = brand; // `this` is the newly created Car instance
  }
}

const myCar = new Car("Tesla");
console.log(myCar.brand); // "Tesla"
```

## 7. DOM Event Handlers

In standard HTML event listeners registered with `addEventListener`, `this` is bound to the element receiving the event.

JavaScript

```
const button = document.querySelector("button");

button.addEventListener("click", function(e) {
  console.log(this); // Refers to <button> element
});

// CAUTION: Arrow functions in event listeners inherit the outer scope instead
button.addEventListener("click", (e) => {
  console.log(this); // Refers to Window (or enclosing scope)
});
```

## Quick Reference Summary

| **Invocation Style**                        | **this Value**                                           |
| ------------------------------------------- | -------------------------------------------------------- |
| **Global Context**                          | `window` (Browser) or `module.exports` (Node)            |
| **`fn()`**                                  | `window` (Non-strict) / `undefined` (Strict)             |
| **`obj.method()`**                          | `obj` (The object left of the dot)                       |
| **`fn.call(obj)` / `.apply()` / `.bind()`** | Explicitly specified `obj`                               |
| **`new Fn()`**                              | The newly constructed instance                           |
| **Arrow Function `() => {}`**               | Inherited from outer lexical scope                       |
| **`element.addEventListener`**              | The target DOM element (when using traditional function) |

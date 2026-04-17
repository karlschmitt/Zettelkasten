---
id: 20260414161339
title: JavaScript objects
date: 2026-04-16
keywords: [ JavaScript, Object]
---
#  JavaScript objects

In JavaScript, an **object** is a standalone entity that holds data in the form of **properties** and **methods**. 

If you think of a variable as a single storage box, an object is like a **chest of drawers** where each drawer has a label (a key) and contains a value.

### 1. The Anatomy of an Object
Objects are written as "key: value" pairs inside curly braces `{}`.

```javascript
const user = {
    firstName: "Alice",        // Property (String)
    age: 30,                   // Property (Number)
    isLoggedIn: true,          // Property (Boolean)
    
    // Method (A function inside an object)
    greet: function() {
        console.log("Hello, my name is " + this.firstName);
    }
};
```

### 2. Why use objects? (The Real-World Analogy)
In the real world, a **Car** is an object.
*   **Properties:** It has a color (Red), a brand (Toyota), and a weight (1500kg).
*   **Methods:** It can perform actions like `start()`, `drive()`, or `brake()`.

In code, this allows you to group related data together instead of having dozens of separate variables.

### 3. How to access data in an Object
There are two ways to get data out of an object:

**A. Dot Notation (Most common)**
```javascript
console.log(user.firstName); // "Alice"
```

**B. Bracket Notation (Used for dynamic keys)**
```javascript
console.log(user["age"]); // 30
```

### 4. Objects are Mutable (Changeable)
Unlike "primitive" data types (like numbers or strings), you can change an object after it is created, even if it was declared with `const`.

```javascript
const car = { color: "red" };

car.color = "blue";      // Change a property
car.year = 2024;         // Add a new property
delete car.color;        // Remove a property
```

### 5. "Everything is an Object" (Almost)
In JavaScript, objects are the foundation for almost everything else:
*   **Arrays** are actually objects (where the keys are index numbers).
*   **Functions** are objects (you can even add properties to them!).
*   **Dates, RegEx, and Maps** are all built-in objects.

### Summary Cheat Sheet
| Concept | Description |
| :--- | :--- |
| **Object Literal** | Creating an object using `{ }`. |
| **Property** | A variable belonging to an object (e.g., `name: "Bob"`). |
| **Method** | A function belonging to an object (e.g., `speak: function() {}`). |
| **`this` Keyword** | Inside a method, `this` refers to the object itself. |
| **Key/Value** | The name of the property and the data it holds. |

**Next Step:** Once you are comfortable with basic objects, you would typically look into **Classes** (which are blueprints for creating many objects of the same type) and **JSON** (the format used to send objects over the internet).
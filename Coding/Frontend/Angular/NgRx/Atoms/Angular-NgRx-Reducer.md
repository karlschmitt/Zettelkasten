---
id: 20260805164758
title: Angular NgRx Reducer
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, NgRx, Reducer, pure function]
---

In NgRx, a **Reducer** is a [pure function](./Atoms/Angular-NgRx-Pure-Funktion.md) that determines how the application's state changes in response to an **Action**.

It is the only part of the NgRx lifecycle responsible for transforming the state.

---

### 1. What is a Reducer?
A reducer is a simple JavaScript function that takes two arguments:
1.  **The Current State** (the way things are now).
2.  **An Action** (an object describing what just happened, e.g., "User clicked login").

The reducer processes these two inputs and returns a **New State**.

#### The Core Rules of a Reducer:
*   **It must be a Pure Function:** Given the same inputs, it must always return the same output. It cannot have "side effects" (it can't call an API, change a global variable, or log to a console).
*   **Immutability:** It never modifies the existing state. Instead, it creates a copy of the old state, applies changes to that copy, and returns the new version.

---

### 2. Why is it called a "Reducer"?

The term is borrowed from **Functional Programming**, specifically from the `reduce()` method used on arrays in JavaScript.

#### The Array.reduce() Connection
In JavaScript, `Array.prototype.reduce()` takes a collection of values and "reduces" them down to a single value. It does this by using a "callback function" that takes an **accumulator** (the result so far) and the **current value**.

```javascript
const numbers = [1, 2, 3];

// The "reducer" function: (accumulator, value) => newValue
const sum = numbers.reduce((total, num) => total + num, 0); 
// Result: 6
```

#### The NgRx Logic
In NgRx, your application state is effectively the "accumulator," and the stream of actions are the "values." 

Imagine your application as a timeline of actions:
1.  **Initial State**: `{ count: 0 }`
2.  **Action 1**: `{ type: 'Increment' }`
3.  **Action 2**: `{ type: 'Increment' }`
4.  **Action 3**: `{ type: 'Decrement' }`

The **Reducer** "reduces" this stream of actions into a **single state value** at any given point in time. 

**The signature is identical:**
*   **Array Reduce:** `(accumulator, currentValue) => nextAccumulator`
*   **NgRx Reducer:** `(state, action) => nextState`

---

### 3. A Practical Example

Here is what a standard NgRx reducer looks like using the modern `createReducer` syntax:

```typescript
export const initialState = { count: 0 };

export const counterReducer = createReducer(
  initialState,
  // When the 'increment' action happens, return a NEW object with count + 1
  on(CounterActions.increment, (state) => ({ 
    ...state, 
    count: state.count + 1 
  })),
  
  // When 'decrement' happens, return a NEW object with count - 1
  on(CounterActions.decrement, (state) => ({ 
    ...state, 
    count: state.count - 1 
  }))
);
```

### Summary
*   **What:** A pure function that takes `(state, action)` and returns `newState`.
*   **Why the name:** Because it acts like the callback in `Array.reduce()`, "folding" or "accumulating" a stream of actions into a single state object over the lifetime of your application.
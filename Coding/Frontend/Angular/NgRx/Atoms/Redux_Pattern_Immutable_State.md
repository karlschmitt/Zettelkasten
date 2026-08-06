---
id: 20260806191529
title: Immutability
author: Karl Schmitt
date: 2026-08-06
---

# Immutability

In the Redux pattern, **immutability** is a core principle. 
Here is a breakdown of what it means, why it’s essential, and how it is implemented.

---

### 1. What is meant by Immutable State?

**Immutability** means "unchangeable." 
In programming, an immutable object is an object that cannot be modified after it is created.

In the context of Redux state:
*   **Mutable approach:** You change the properties of the existing state object (e.g., `state.user.name = "Alice"`).
*   **Immutable approach:** You never touch the existing state object. Instead, you create a **brand new copy** of the state that incorporates the changes you want to make.

**Analogy:** Think of a bank ledger. You don't erase an old balance and write a new one over it. Instead, you add a new line (a new state) that represents the current status, preserving the history of all previous entries.

---

### 2. Why is it needed?

Redux relies on immutability for several critical reasons:

#### A. Predictability and Traceability
Since the state never changes "in place," you can track every single action that led to the current state. This enables **Time Travel Debugging**, allowing developers to move back and forth through the application's history to see exactly how the UI looked at any point in time.

#### B. Efficient Change Detection (Performance)
React and Redux need to know when the state has changed to trigger a UI re-render.
*   **If state were mutable:** The system would have to perform a "deep comparison" (checking every single nested property of an object) to see if anything changed. This is computationally expensive.
*   **With immutability:** The system only needs to perform a "reference check" (`oldState === newState`). If the memory address is different, the state has changed. This is near-instant.

#### C. Avoiding Side Effects
In large applications, multiple components might share the same piece of state. If one component accidentally mutates that state, other components might behave unexpectedly or fail to update. Immutability ensures that state transitions are controlled and explicit.

---

### 3. How is it achieved?

In Redux, immutability is handled within **Reducers**. A reducer must be a "pure function": it takes the old state and an action, and returns a new state.

#### A. Using the Spread Operator (Standard JS)
The most common way to maintain immutability in modern JavaScript is using the spread operator (`...`).

```javascript
// Initial State
const initialState = {
  user: "John",
  posts: []
};

// Reducer logic
function reducer(state = initialState, action) {
  switch (action.type) {
    case 'ADD_POST':
      return {
        ...state,                // Copy all existing state
        posts: [...state.posts, action.payload] // Create a NEW array for posts
      };
    default:
      return state;
  }
}
```

#### B. Avoiding Mutating Methods
When working with arrays, you must avoid methods that modify the original array (like `push`, `splice`, or `sort`). Instead, use methods that return a new array:
*   Use `concat()` or `[...]` instead of `push()`.
*   Use `filter()` instead of `splice()` to remove items.
*   Use `map()` to update specific items.

#### C. Using Redux Toolkit (Immer)
Manually spreading nested objects can become deeply nested and error-prone (e.g., `state.user.address.city`). 

Today, the official recommendation is **Redux Toolkit (RTK)**. RTK uses a library called **Immer** under the hood. Immer allows you to write "mutative" code (like `state.user.name = 'Alice'`), but it intercepts these changes and automatically generates a new immutable state for you.

```javascript
// Using Redux Toolkit (Immer handles immutability for you)
const userSlice = createSlice({
  name: 'user',
  initialState,
  reducers: {
    updateName(state, action) {
      // This LOOKS like mutation, but Immer makes it immutable
      state.user.name = action.payload; 
    }
  }
});
```

### Summary
*   **What:** Never changing the state object directly; always creating a new one.
*   **Why:** For performance (fast reference checks), debugging (time travel), and preventing bugs (predictability).
*   **How:** Using JavaScript spread operators, non-mutating array methods, or Redux Toolkit's built-in Immer integration.
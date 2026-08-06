---
id: 20260805191519
title: What problem does Redux solve?
author: Karl Schmitt
date: 2026-08-05
---

# What problem does Redux solve?

In the context of NgRx and Angular, the Redux pattern is designed to solve the challenges of **managing state in large-scale, complex applications.**

As an application grows, managing data shared across components, services, and modules becomes "spaghetti code." Redux solves the following five core problems:

---

### 1. The "Single Source of Truth" Problem (State Inconsistency)
In a standard Angular app without a state management library, data is often scattered across various services and components. This leads to "fragmented state," where two different parts of the UI might show different versions of the same data.

*   **The Solution:** Redux provides a **Store**, a single JavaScript object that holds the entire state of the application. If you want to know the current status of the app, you look in one place. This ensures data consistency across the entire UI.

### 2. Predictability (The "Who Changed What?" Problem)
In large apps, it becomes difficult to track which component or service modified a piece of data. This leads to "side-effect bugs" where changing a value in one place unexpectedly breaks another.

*   **The Solution:** In Redux, state is **read-only**. To change the state, you must dispatch an **Action** (a plain object describing what happened). This change is then handled by a **Reducer** (a pure function). 
*   **Result:** Because reducers are pure functions (same input always equals same output), state transitions are 100% predictable and easy to unit test.

### 3. Prop Drilling and Component Coupling
Without a central store, you often have to pass data through multiple layers of components (Input/Output) just to get it from a parent to a distant child. This is known as "prop drilling." It makes components hard to reuse because they are tightly coupled to their parents.

*   **The Solution:** Any component can "Select" data directly from the Store and "Dispatch" actions to it, regardless of where that component sits in the component tree. This keeps components decoupled and "dumb."

### 4. Traceability and Debugging
Debugging state-related bugs is notoriously difficult. If a variable is wrong, how do you know what sequence of events led to that error?

*   **The Solution:** Because every change in Redux is triggered by a discrete Action, you can use tools like **Redux DevTools**.
    *   **Time-Travel Debugging:** You can literally "rewind" and "fast-forward" through every action that ever happened in the app to see exactly when the state went wrong.
    *   **State Snapshots:** You can export the state from a user's failed session and import it into your own dev environment to reproduce the bug instantly.

### 5. Managing Asynchronous Complexity (Side Effects)
Handling API calls, web sockets, and long-running tasks in components often leads to messy code filled with `.subscribe()` blocks and race conditions.

*   **The Solution:** NgRx uses **Effects**. Effects listen for actions, perform an external task (like an HTTP request), and then dispatch a new action with the result. 
*   **Result:** This keeps your components "pure." They don't need to know *how* to fetch data; they just ask for it, and the data eventually arrives in the store via the stream.

---

### Summary: When do you actually need it?
Redux/NgRx is powerful but introduces a lot of "boilerplate" code. You generally need it when:
1.  **Multiple components** need to access and manipulate the same data.
2.  The state is updated from **multiple sources** (WebSockets, User Input, Background Tasks).
3.  The application is large enough that **tracking changes** becomes a manual burden.

**If your app is small or data flows are simple, standard Angular Services with `BehaviorSubject` are often a better, lighter choice.**
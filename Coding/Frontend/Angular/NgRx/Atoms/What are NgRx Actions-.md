---
id: 20260803151126
title: What are NgRx Actions?
author: Karl Schmitt
date: 2026-08-03
keywords: [ Angular, NgRx, Action]
---

# What are NgRx Actions?

In NgRx, an **Action** is a plain JavaScript object that represents a **unique event** that happened in your application.

Think of an action as a **message** sent to the store to notify it that something occurred—like a user clicking a button, a form being submitted, or data being returned from an API.

---

### 1. The Structure of an Action
An action consists of two main parts:
1.  **`type` (Required):** A string that describes the event. By convention, it follows the pattern `[Source] Event Name`.
2.  **`props` (Optional):** A payload containing any data needed to update the state.

### 2. How to Define an Action
In modern NgRx (using `createAction`), you define them like this:

```typescript
import { createAction, props } from '@ngrx/store';

// An action without data
export const loadBooks = createAction(
  '[Book List] Load Books'
);

// An action with data (payload)
export const addBook = createAction(
  '[Admin Page] Add Book',
  props<{ bookTitle: string; author: string }>()
);
```

### 3. How an Action Moves Through the System
An action acts as a trigger for two main things:

*   **Reducers:** The reducer listens for the action and creates a **new state** based on the action's payload.
*   **Effects:** An Effect listens for the action to perform **side effects**, like making an HTTP request to a server.

### 4. The Lifecycle (The "Flow")
1.  **Dispatch:** A component "dispatches" the action.
    `this.store.dispatch(addBook({ bookTitle: 'Angular Pro', author: 'John Doe' }));`
2.  **Intercept:** The **Store** receives the action.
3.  **React:** 
    *   The **Reducer** sees the `[Admin Page] Add Book` type and adds the book to the state.
    *   (Optional) An **Effect** sees the type and saves the book to a database via an API.

### 5. Best Practices: "Actions as Events"
A common mistake is naming actions like commands (e.g., `UpdateUser`). The NgRx team recommends naming them as **Events** (e.g., `[Edit Profile] Update Button Clicked`).

**Why?**
*   **Traceability:** In the Redux DevTools, you can see exactly which screen or component triggered the change.
*   **Decoupling:** One action can trigger multiple changes in different parts of the state.

### Summary
*   **Actions** = "What happened" (The message).
*   **Reducers** = "How state changes" (The response).
*   **Effects** = "What else happens" (The side effect).
*   **Store** = "Where it's kept" (The database).
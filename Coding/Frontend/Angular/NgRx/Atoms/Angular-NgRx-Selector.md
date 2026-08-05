---
id: 20260805172138
title: Angular NgRx Selectors
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, NgRy, Selector]
---

# Selector

In NgRx, **Selectors** are [pure functions](./Angular-NgRx-Pure-Funktion.md) used to slice, transform, 
and retrieve specific pieces of data from the global store. 

If the **Store** is a giant database containing all your application's data, 
a **Selector** is like a saved query that grabs exactly what you need.

---

### 1. What is a Selector?
A selector takes the entire state object as an input and returns a specific "slice" of that state.

#### Key Features:
*   **Pure Functions:** Like reducers, selectors are pure. They don't change the state; they just read it.
*   **Memoization (The "Secret Sauce"):** This is the most important technical feature. Selectors are "smart." If the state hasn't changed since the last time the selector was called, it returns a cached result instead of recalculating it. This makes your app very fast.
*   **Composition:** You can combine small selectors to build complex ones. For example, a `selectUser` and a `selectOrders` can be combined into a `selectUserOrders`.

---

### 2. Why is it named "Selector"?

The name comes from the literal act of **selection**—picking a specific item out of a larger collection. It is influenced by two main sources:

#### A. The SQL Connection (`SELECT`)
In the world of databases, when you want data, you write a query starting with the keyword **`SELECT`**.
*   **SQL:** `SELECT username FROM users_table;`
*   **NgRx:** `store.select(selectUsername);`

Just as a SQL `SELECT` statement filters a massive database down to a specific column, an NgRx Selector filters the massive State Tree down to a specific property.

#### B. The "Projector" Concept
In NgRx, the function that actually transforms the data inside a selector is often called a **Projector function**. In mathematics and geometry, a "projection" is taking a high-dimensional object (like the whole State Tree) and mapping it onto a simpler plane (like a single boolean or string). You are **selecting** a specific perspective of the data.

---

### 3. A Practical Example

Without selectors, your component has to know the exact "shape" of the store:
```typescript
// BAD: Component knows too much about the state structure
this.count$ = this.store.select(state => state.feature.counter.value);
```

With **Selectors**, you hide that complexity:
```typescript
// selector.ts
export const selectCounterValue = createSelector(
  (state: AppState) => state.feature.counter,
  (counter) => counter.value // This is the "projector" function
);

// component.ts
// GOOD: Component just asks for the "Counter Value" and doesn't care where it lives
this.count$ = this.store.select(selectCounterValue);
```

---

### 4. Why are they useful?

1.  **Decoupling:** If you decide to rename your state properties (e.g., changing `counter` to `timer`), you only have to update the selector in one place, rather than updating 50 different components.
2.  **Transformation:** You can use selectors to calculate data on the fly. For example, a selector can take a list of `tasks` and return only the `completedTasks`. The component doesn't have to do the filtering logic; it just "selects" the finished tasks.
3.  **Efficiency (Memoization):** If your selector performs an expensive calculation (like sorting a 1,000-item list), memoization ensures that the calculation only runs **once**. It won't run again unless the list actually changes, saving CPU power.

### Summary
*   **What:** A query function for your state.
*   **Why the name:** Because it **selects** a specific slice of data from the state tree, much like a `SELECT` statement in a database.
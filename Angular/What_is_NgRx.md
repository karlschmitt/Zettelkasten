---
id: 20260424121805
title: What is NgRx?
author: Karl Schmitt
date: 2026-04-24
---

# What is NgRx?

**NgRx** is a framework for building reactive applications in Angular. At its core, it is a **state management library** inspired by the Redux pattern (originally from React), but specifically tailored for Angular and built on top of **RxJS**.

In simple terms, NgRx provides a way to manage the "state" (data) of your application in a centralized, predictable, and consistent manner.

---

### Why do you need NgRx?
In a standard Angular app, data is often scattered across various components and services. As the app grows, you face several problems:
1.  **Communication Issues:** Passing data between deeply nested components becomes messy ("Prop Drilling").
2.  **Inconsistency:** One part of the app updates data, but another part doesn't reflect that change.
3.  **Debugging Difficulty:** It’s hard to track exactly when and why a piece of data changed.

---

### The 5 Core Building Blocks of NgRx

NgRx follows a unidirectional data flow. Here are the key concepts:

#### 1. Store
The **Store** is the "Single Source of Truth." It is a global object that holds the entire state of your application. Instead of components holding their own data, they "ask" the store for it.

#### 2. Actions
**Actions** are unique events that describe "what happened" in the application. They are plain objects with a `type` and an optional `payload`.
*   *Example:* `[User Page] Login Button Clicked`

#### 3. Reducers
**Reducers** are pure functions that handle state transitions. They take the **current state** and the **latest action**, and return a **new state**. They never modify the existing state; they always return a new copy (immutability).
*   *Logic:* If action is "Login Success," update the `user` object in the state.

#### 4. Selectors
**Selectors** are pure functions used to slice and transform pieces of the state. Components use selectors to "subscribe" to specific data.
*   *Benefit:* If the whole state changes but the specific data the component is watching doesn't change, the component won't re-render (performance).

#### 5. Effects
**Effects** handle side effects, such as API calls, web sockets, or notifications. They listen for specific actions, perform an asynchronous task, and then usually dispatch a *new* action (like "Load Data Success").

---

### The NgRx Workflow (Cycle)
1.  **Component** dispatches an **Action**.
2.  An **Effect** hears the action and fetches data from an API.
3.  The Effect dispatches a "Success" **Action**.
4.  The **Reducer** catches that "Success" action and updates the **Store**.
5.  The **Component** is automatically updated via a **Selector** because it is subscribed to that part of the Store.

---

### Pros and Cons

| Pros | Cons |
| :--- | :--- |
| **Centralized State:** One place to find all your data. | **Boilerplate:** Requires many files (actions, reducers, etc.). |
| **Predictability:** State is immutable; changes are traceable. | **Learning Curve:** Concepts like RxJS and Redux are hard for beginners. |
| **Tooling:** Redux DevTools allows you to "Time Travel" through state changes. | **Overkill:** Not necessary for simple or small applications. |
| **Testability:** Most NgRx logic consists of pure functions. | |

---

### When should you use it?
A common rule of thumb is the **SHARI** principle. Use NgRx if your state is:
*   **S**hared: State is accessed by many components/services.
*   **H**ydrated: State needs to be persisted or retrieved from storage.
*   **A**vailable: State needs to be available when re-entering a route.
*   **R**etrieved: State must be retrieved with a side effect (API call).
*   **I**mpacted: State is impacted by actions from other components.

**Note:** For smaller apps, Angular **Signals** or simple **BehaviorSubjects** in a service are often sufficient and much simpler.

---
id: 20260804151433
title: NgRx State
author: Karl Schmitt
date: 2026-08-04
---

In the context of NgRx and Redux-based patterns, **State** is a single, plain JavaScript object that represents the **entire status of your application at a specific point in time.**

If you were to take a "snapshot" of your app right now, every piece of data that determines what the user sees and what the app is doing is contained within the State.

Here is a breakdown of what State means in NgRx:

---

### 1. The "Single Source of Truth"
In NgRx, your application has a **Global State** (often called the Store). Instead of having data scattered across different services and components, all important data is centralized. This ensures that every part of your application is looking at the same data at the same time.

### 2. What lives in the State?
State is typically made up of three types of data:

*   **Server Data:** Data fetched from an API (e.g., a list of users, product details, or a user profile).
*   **UI State:** Information about the visual state of the app (e.g., "is the sidebar open?", "is the loading spinner active?", "which tab is currently selected?").
*   **Router State:** Information about the current URL, route parameters, and query parameters.

### 3. An Example of a State Object
Imagine a simple E-commerce app. The NgRx State might look like this:

```json
{
  "products": {
    "items": [{ "id": 1, "name": "Laptop", "price": 999 }],
    "loading": false,
    "error": null
  },
  "cart": {
    "itemIds": [1],
    "totalPrice": 999
  },
  "user": {
    "isLoggedIn": true,
    "username": "JohnDoe"
  },
  "ui": {
    "darkMode": true,
    "sideNavOpen": false
  }
}
```

### 4. Key Characteristics of State in NgRx

#### A. Immutability
This is the most important rule. **State is read-only.** 
You never modify the state object directly (e.g., `state.user.name = 'Jane'`). Instead, when something changes, you create a *new* state object that reflects those changes. This makes it easy to track history (time-travel debugging) and makes change detection in Angular much faster.

#### B. Predictability
Because changes to the state only happen through **Actions** and **Reducers**, you always know exactly how and why the state changed. This removes the "side effect" bugs often found in traditional service-based state management.

#### C. Persistence (Transient vs. Persistent)
*   State is **transient** by default: If you refresh the browser, the NgRx state is wiped out.
*   However, because it is just a JavaScript object, it is very easy to save it to `localStorage` and "rehydrate" it when the app starts again.

### Summary
In NgRx, **State** is the "memory" of your application. It is a single, immutable object that acts as the master record for all the data and UI conditions needed to run your app.
---
id: 20260804170607
title: Debugging
author: Karl Schmitt
date: 2026-08-04
---

# Debugging

Debugging in NgRx is primarily centered around the **Redux DevTools** ecosystem. Because NgRx follows a strict unidirectional data flow and uses immutable state, it provides a level of traceability that is impossible in traditional service-based state management.

Here is a breakdown of how NgRx debugging works, from the underlying mechanics to the features you use.

---

### 1. The Core Architecture: The "Meta-Reducer"
The "magic" of NgRx debugging happens through a specialized **Meta-Reducer**.

When you install `@ngrx/store-devtools` and add `StoreDevtoolsModule.instrument()` to your `app.config.ts` or `AppModule`, NgRx injects a higher-order reducer into your store.

*   **Standard Flow:** Action → Reducer → New State.
*   **Debug Flow:** Action → **Store DevTools Meta-Reducer** → Reducer → **Store DevTools Meta-Reducer** → New State.

This meta-reducer intercepts every action and the resulting state change, sending that data to the Redux DevTools browser extension via a communication bridge.

---

### 2. Key Debugging Features
The Redux DevTools extension provides several powerful ways to inspect your application:

#### A. The Action Log
Every action dispatched in your app is recorded in a chronological list. You can see:
*   The **Type** of the action.
*   The **Payload** (data) sent with the action.
*   The exact timestamp it occurred.

#### B. State Diffing
Instead of looking at a massive JSON object and trying to find what changed, the debugger shows a **Diff**. It highlights exactly which properties were added, removed, or modified in the store after a specific action was fired.

#### C. Time Travel Debugging
This is the most famous feature. Because state in NgRx is **immutable**, the DevTools extension keeps a history of every state "snapshot."
*   **Jump:** You can "jump" back to any previous point in time. The DevTools forces the NgRx store to emit that old state. Your UI (components) will instantly update to reflect how the app looked at that exact moment.
*   **Skip:** You can "toggle off" a specific action from the past to see how the current state would look if that action had never happened.

#### D. Action Dispatching (Manual Testing)
You can manually type and dispatch actions directly from the DevTools console. This allows you to test how your reducers and effects handle specific data without having to manually click through the UI.

---

### 3. How to Enable It
To make debugging work, you need three pieces:

1.  **The Extension:** Install "Redux DevTools" in Chrome, Firefox, or Edge.
2.  **The Library:** Install `@ngrx/store-devtools`.
3.  **The Configuration:** In your Angular app, you must instrument the store:

```typescript
// In app.config.ts (Angular 17+)
provideStoreDevtools({
  maxAge: 25, // Retains last 25 states
  logOnly: !isDevMode(), // Restricts extension to read-only in production
  autoPause: true, // Pauses recording when the extension tab is closed
  trace: false, // Includes stack trace for every action
})
```

---

### 4. Constraints for Debugging to Work
For NgRx debugging to be effective, you must follow two strict rules:

1.  **Immutability:** You must never mutate the state directly (e.g., `state.user = 'bob'`). You must always return a new object (`{...state, user: 'bob'}`). If you mutate state, "Time Travel" will break because all historical snapshots will point to the same modified object.
2.  **Serializability:** All actions and state should be **plain JavaScript objects**. If you put class instances, Map/Set, or Functions into your state, the DevTools won't be able to "stringify" the state, and you won't be able to export/import debug sessions.

---

### 5. Advanced: Debugging Effects
While Redux DevTools tracks State and Actions, **NgRx Effects** are asynchronous. To debug them:
*   **Action Tracking:** Effects usually dispatch a "Success" or "Failure" action. By watching the Action Log, you can see if an effect fired and what it resulted in.
*   **Ngrx/effects/trace:** In newer versions, you can enable tracing to see which effect was triggered by which action.

### Summary
NgRx debugging works by **intercepting the stream of actions and states** through a meta-reducer. It leverages the **predictability of pure functions** (reducers) and **immutability** to allow you to move backward and forward through your application's history as if you were using a DVR.
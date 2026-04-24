---
id: 20260424122437
title: How to learn NgRx?
author: Karl Scmitt
date: 2026-04-24
---

# How to learn NgRx?

Learning NgRx can be intimidating because it introduces many new concepts at once. The best way to learn is to follow a **layered approach**, moving from theory to simple implementation, and then to complex side effects.

Here is a recommended roadmap to master NgRx:

---

### Phase 1: Master the Prerequisites
Before touching NgRx, you must be comfortable with:
*   **RxJS:** You don't need to be a ninja, but you must understand Observables, `pipe()`, and operators like `map`, `filter`, `switchMap`, and `of`.
*   **Immutability:** Understand why we use the spread operator `...` instead of modifying arrays or objects directly (e.g., `state.user = 'Bob'` is a no-go).
*   **TypeScript:** Interfaces and types are used heavily in NgRx.

### Phase 2: Understand the "Why" (Theory)
Don't write code yet. Watch a high-level video or read an article on the **Redux Pattern**.
*   Learn the cycle: **Component → Action → Reducer → Store → Selector → Component**.
*   **Key Concept:** The Store is a read-only database in your browser. To change it, you must send an "Action."

### Phase 3: Start with a "Counter" (The Hello World)
Don't use APIs or Effects yet. Build a simple counter app that only uses:
1.  **Actions:** `increment`, `decrement`, `reset`.
2.  **Reducers:** Logic to update the number.
3.  **Selectors:** To read the current count.
4.  **Store:** To tie it together.

**Resource:** [NgRx Official Walkthrough - Counter](https://ngrx.io/guide/store/walkthrough)

### Phase 4: Add Side Effects (NgRx Effects)
Once you can manage local data, learn how to fetch data from a server.
*   Learn how an **Effect** listens for a `loadData` action.
*   Learn how it calls an Angular Service.
*   Learn how it dispatches a `loadDataSuccess` or `loadDataFailure` action based on the API result.

### Phase 5: Install Redux DevTools
This is the "Aha!" moment for most learners.
*   Install the **Redux DevTools** extension in Chrome.
*   Add `StoreDevtoolsModule` to your app.
*   This allows you to see every action dispatched and "time travel" to see how the state changed at every second.

### Phase 6: Simplify with NgRx Entity
Managing lists (arrays of objects) in a Reducer is tedious (lots of mapping and filtering).
*   Learn **@ngrx/entity**. It provides a standardized way to manage collections (CRUD operations) with much less code.

### Phase 7: Learn Modern NgRx (Signals)
The Angular ecosystem is shifting toward **Signals**. NgRx has evolved to support this.
*   **NgRx Signal Store:** This is a newer, more functional, and less "boilerplate-heavy" way to manage state. Many new projects prefer this over the classic "Global Store."

---

### Recommended Resources

#### 1. Official Documentation
*   **[ngrx.io](https://ngrx.io/):** Their documentation is excellent. Start with the "Guides" section.

#### 2. Top Video Courses / Educators
*   **Deborah Kurata (Pluralsight/YouTube):** She is famous for making complex Angular topics very simple.
*   **Maximilian Schwarzmüller (Udemy):** His "Angular - The Complete Guide" has a very solid NgRx section.
*   **Todd Motto (Ultimate Courses):** Deep dives into the architecture.

#### 3. Practice Project Idea
Build a **"Book Collection"** app:
1.  Search for books via an API (Google Books API).
2.  Click a book to "Add to Collection" (Action → Store).
3.  View your collection in a separate tab (Selector).
4.  Remove books from the collection (Action → Reducer).
5.  Save the collection to LocalStorage using an Effect.

### The Best Advice: Don't Use it Too Early
The biggest mistake beginners make is adding NgRx to a tiny project. If a service with a `BehaviorSubject` works fine, stick with that. Learn NgRx when you feel the pain of data becoming unmanageable.
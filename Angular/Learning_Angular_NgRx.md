---
id: 20260424131007
title: Learning Angular NgRx
author: Karl Scmitt
date: 2026-04-24
keywords: [ Angular, NgRx]
---

# Learning Angular NgRx

Learning **NgRx** can feel intimidating at first—but it becomes much clearer once you see it as a structured way to manage state in an Angular app using patterns inspired by Redux.

Let’s break it into a **practical, progressive path** that fits your bootcamp style.

***

# 🧠 What NgRx _really_ is (simple mental model)

NgRx = **State container + predictable data flow**

Instead of components managing their own messy state, NgRx gives you:

* **Store** → single source of truth (like a global database in memory)

* **Actions** → “what happened”

* **Reducers** → “how state changes”

* **Effects** → “side effects (API calls, async stuff)”

* **Selectors** → “how to read state”

Think of it like:

```
User clicks button
→ Action dispatched
→ Reducer updates state
→ UI reacts automatically
```

***

# ⚠️ Before you start (important)

Don’t jump into NgRx too early.

You should already be comfortable with:

* Angular components & services

* RxJS basics (`Observable`, `pipe`, `map`, `switchMap`)

* Dependency injection

If RxJS still feels shaky, fix that first—NgRx is built on it.

***

# 🚀 Week-by-Week NgRx Bootcamp

***

## 🥇 Week 1 — Foundations (No NgRx yet!)

Goal: Understand the _problem_ NgRx solves.

### Learn:

* Local state vs shared state

* Service-based state (BehaviorSubject pattern)

### Exercise:

Build a **counter app** with a service:

```ts
private counter$ = new BehaviorSubject<number>(0);

increment() {
  this.counter$.next(this.counter$.value + 1);
}
```

👉 This is basically a _mini store_

***

## 🥈 Week 2 — First Contact with NgRx Store

Goal: Understand core pieces

### Install:

```bash
ng add @ngrx/store
```

### Learn:

* Actions

* Reducers

* Store

### Example:

**Action**

```ts
export const increment = createAction('[Counter] Increment');
```

**Reducer**

```ts
export const counterReducer = createReducer(
  0,
  on(increment, state => state + 1)
);
```

**Component**

```ts
count$ = this.store.select('count');

this.store.dispatch(increment());
```

👉 Big shift: you don’t _change state directly anymore_

***

## 🥉 Week 3 — Selectors (Clean State Access)

Goal: Stop accessing raw state

### Learn:

* Feature selectors

* Memoization

```ts
export const selectCount = createSelector(
  selectCounterState,
  (state) => state.count
);
```

👉 Why this matters:

* Performance

* Clean architecture

* Reusability

***

## 🏅 Week 4 — Effects (Async Magic)

Goal: Handle API calls properly

### Install:

```bash
ng add @ngrx/effects
```

### Learn:

* Effects

* `switchMap`, `mergeMap`

### Example:

```ts
loadUsers$ = createEffect(() =>
  this.actions$.pipe(
    ofType(loadUsers),
    switchMap(() =>
      this.api.getUsers().pipe(
        map(users => loadUsersSuccess({ users }))
      )
    )
  )
);
```

👉 Rule:\
Reducers = pure\
Effects = async side effects

***

## 🎯 Week 5 — Entity (Advanced State Handling)

Goal: Manage collections efficiently

### Install:

```bash
ng add @ngrx/entity
```

### Learn:

* Entity adapter

* CRUD helpers

```ts
const adapter = createEntityAdapter<User>();
```

👉 This saves you tons of boilerplate

***

## 🧩 Week 6 — Store DevTools & Debugging

### Install:

```bash
ng add @ngrx/store-devtools
```

### Learn:

* Time travel debugging

* Inspect actions/state

👉 This is where NgRx becomes _fun_

***

## 🏗️ Week 7 — Architecture & Best Practices

Learn:

* Feature modules + feature stores

* Smart vs dumb components

* Folder structure

Suggested structure:

```
/state
  /actions
  /reducers
  /effects
  /selectors
```

***

## 🚀 Week 8 — Real Project

Build:

* Todo App with API

* Auth flow (login/logout)

* Loading/error states

***

# 🧠 Key Concepts to Master

If you truly understand these, NgRx clicks:

* Unidirectional data flow

* Immutability

* Reactive programming (RxJS)

***

# ⚡ Common Mistakes (avoid these)

* ❌ Using NgRx for small apps (overkill)

* ❌ Putting logic in components instead of effects

* ❌ Mutating state inside reducers

* ❌ Skipping selectors

***

# 🧭 When should YOU use NgRx?

Use NgRx if:

* App is large/complex

* Many components share state

* You need predictable debugging

Avoid it if:

* Small project

* Simple state → use services instead

***

# 🔥 Pro Tip (important)

NgRx is not the only option.

Also look at:

* NGXS (simpler)

* Akita (more OOP style)

***

# 👉 If you want next step

I can give you:

* A **hands-on NgRx mini project (step-by-step)**

* A **cheat sheet (actions → reducers → effects flow)**

* Or integrate NgRx into your **Angular Week Bootcamp**

Just tell me 👍

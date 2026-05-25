---
id: 20260424133537
title: Learning Angular RxJS
author: Karl Schmitt
date: 2026-04-24
keywords: []
---

# Learning Angular RxJS

Learning **RxJS** is less about memorizing operators and more about training your brain to think in **streams over time**. Once that clicks, everything else (including NgRx) becomes much easier.

***

# 🧠 What RxJS really is

RxJS lets you work with:

* **Streams of values** (not just single values)

* **Async data over time** (events, HTTP, timers)

* **Functional transformations** (`map`, `filter`, etc.)

👉 Mental shift:

```text
Not: "give me a value"
But: "react to values as they arrive"
```

***

# 🌊 Core idea (super simple)

```ts
const stream$ = of(1, 2, 3);

stream$.subscribe(value => console.log(value));
```

Output over time:

```
1
2
3
```

That’s it. Everything else builds on this.

***

# 🚀 4-Week RxJS Bootcamp (fits your learning style)

***

## 🥇 Week 1 — Observables Basics

Goal: Understand what a stream is.

### Learn:

* `Observable`

* `subscribe`

* `of`, `from`, `interval`

### Try:

```ts
import { interval } from 'rxjs';

interval(1000).subscribe(x => console.log(x));
```

👉 Emits: 0,1,2,3… every second

### Key idea:

You don’t pull data — it _pushes_ to you.

***

## 🥈 Week 2 — Operators (transforming streams)

Goal: Shape data like Lego blocks.

### Learn:

* `map`

* `filter`

* `tap`

### Example:

```ts
import { of, map, filter } from 'rxjs';

of(1,2,3,4,5).pipe(
  filter(x => x % 2 === 0),
  map(x => x * 10)
).subscribe(console.log);
```

👉 Output:

```
20
40
```

### Key idea:

Operators don’t execute until you `subscribe`.

***

## 🥉 Week 3 — Async Power (real-world RxJS)

Goal: Handle async flows cleanly.

### Learn:

* `switchMap` ⭐ (VERY important)

* `mergeMap`

* `debounceTime`

### Example (search input):

```ts
searchInput$.pipe(
  debounceTime(300),
  switchMap(term => http.get(`/api?q=${term}`))
).subscribe(results => console.log(results));
```

👉 Why `switchMap`?\
It cancels old requests → perfect for UI

***

## 🏅 Week 4 — Subjects & State

Goal: Build your own mini state system.

### Learn:

* `Subject`

* `BehaviorSubject`

### Example:

```ts
const counter$ = new BehaviorSubject(0);

counter$.subscribe(console.log);

counter$.next(1);
counter$.next(2);
```

👉 Output:

```
0
1
2
```

### Key idea:

Subjects = both Observable + Observer

***

# 🔑 The 5 RxJS concepts you MUST master

If you get these, you're ahead of most developers:

1. **Streams over time**

2. **Pipe + operators**

3. **switchMap vs mergeMap**

4. **Cold vs Hot Observables**

5. **Subjects (especially BehaviorSubject)**

***

# ⚠️ Common beginner traps

* ❌ Trying to learn _all operators_ → don’t

* ❌ Forgetting to `subscribe`

* ❌ Nesting subscriptions (use operators instead)

* ❌ Ignoring `switchMap` (this one is critical)

***

# 🧪 Practice ideas (important)

Build small things:

* Timer app

* Live search (debounce)

* Auto-refresh data every 5 seconds

* Simple state store (BehaviorSubject)

***

# 🧭 How RxJS fits into Angular

Angular uses RxJS everywhere:

* HTTP → returns Observables

* Forms → valueChanges

* Router → events

And especially:\
👉 NgRx = RxJS + state management

***

# ⚡ Minimal operator cheat sheet

You’ll use these 80% of the time:

* `map` → transform

* `filter` → skip values

* `tap` → debug/log

* `switchMap` → API calls

* `debounceTime` → input delay

***

# 🔥 Pro tip

Don’t try to “understand everything” upfront.

Instead:

1. See a problem

2. Use RxJS to solve it

3. Repeat

That’s how it clicks.

***

# 👉 If you want next

I can:

* Build you a **hands-on RxJS mini project (step-by-step)**

* Give you a **visual mental model cheat sheet**

* Or combine RxJS + Angular + NgRx into one learning path

Just tell me 👍

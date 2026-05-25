---
id: 20260425212421
title: Angular RxJS bootcamp
author: Karl Schmitt
date: 2026-04-25
keywords: [ Angular, RxJS, bootcamp]
---

# Angular RxJS Bootcamp

Good call—**RxJS is the real power behind Angular**. If Angular is the body, RxJS is the nervous system.

Let’s build intuition _and_ practical skill with a **7-day RxJS bootcamp**, aligned with how you’ll actually use it in Angular.

***

# 🚀 RxJS Bootcamp (7 Days)

We’ll use **RxJS** together with **Angular** concepts and evolve your Task Manager app.

***

# 🗓️ Day 1 — What is RxJS?

## 🎯 Goal

Understand **Observables vs Promises**

## 🧠 Core Idea

An **Observable** is a stream of values over time.

***

## ✍️ Example

```ts
import { Observable } from 'rxjs';

const obs$ = new Observable(observer => {
  observer.next('Hello');
  observer.next('World');
  observer.complete();
});

obs$.subscribe(value => console.log(value));
```

***

## 🔑 Learn

* `subscribe()`

* `next`, `error`, `complete`

* Lazy execution

***

## 🧩 Mini Task

Create an Observable that emits:

* 1, 2, 3 (with delays)

***

# 🗓️ Day 2 — Operators (Core Power)

## 🎯 Goal

Transform streams

## 🧠 Core Idea

Operators = functions that modify streams

***

## ✍️ Example

```ts
import { of, map } from 'rxjs';

of(1, 2, 3)
  .pipe(
    map(x => x * 10)
  )
  .subscribe(console.log);
```

***

## 🔑 Must-Know Operators

* `map`

* `filter`

* `tap` (debugging!)

* `take`

***

## 🧩 Mini Task

* Filter even numbers

* Multiply by 2

* Log result

***

# 🗓️ Day 3 — Async Streams (Real World)

## 🎯 Goal

Work with time-based streams

***

## ✍️ Example

```ts
import { interval } from 'rxjs';

interval(1000).subscribe(x => console.log(x));
```

***

## 🔑 Learn

* `interval`

* `timer`

* Unsubscribing!

***

## 🧩 Mini Task

Create a counter that stops after 5 values:

```ts
take(5)
```

***

# 🗓️ Day 4 — Subjects (Hot Observables)

## 🎯 Goal

Understand shared streams

***

## ✍️ Example

```ts
import { Subject } from 'rxjs';

const subject = new Subject<number>();

subject.subscribe(v => console.log('A:', v));
subject.subscribe(v => console.log('B:', v));

subject.next(1);
subject.next(2);
```

***

## 🔑 Learn

* Subject vs Observable

* Multicasting

***

## 🧩 Mini Task

Use a Subject to simulate a chat:

* Multiple subscribers

* Shared messages

***

# 🗓️ Day 5 — RxJS in Angular (HTTP)

## 🎯 Goal

Use RxJS with APIs

***

## ✍️ Example

```ts
this.http.get('https://jsonplaceholder.typicode.com/todos')
  .subscribe(data => console.log(data));
```

***

## 🔑 Learn

* HTTP returns Observables

* Async data flow

***

## 🧩 Mini Task

* Fetch todos

* Display in your Angular app

***

# 🗓️ Day 6 — Advanced Operators

## 🎯 Goal

Handle real-world async complexity

***

## 🔑 Must-Know

* `switchMap` ⭐ (VERY IMPORTANT)

* `mergeMap`

* `debounceTime`

* `distinctUntilChanged`

***

## ✍️ Example (Search Input)

```ts
search$.pipe(
  debounceTime(300),
  distinctUntilChanged(),
  switchMap(term => this.http.get(`/api?q=${term}`))
).subscribe();
```

***

## 🧩 Mini Task

Simulate a search box:

* Delay typing

* Cancel old requests

***

# 🗓️ Day 7 — Real App Integration

## 🎯 Goal

Use RxJS like a pro in Angular

***

## 🧠 Pattern

```ts
tasks$ = this.taskService.getTasks();
```

```html
<div *ngFor="let task of tasks$ | async">
  {{ task }}
</div>
```

***

## 🔑 Learn

* `async` pipe (no manual subscribe!)

* Reactive UI

***

## 🧩 Final Project Upgrade

Upgrade your Task Manager:

* ✅ Tasks as Observable stream

* ✅ Add task via Subject

* ✅ Async pipe in template

* ✅ Debounced input

* ✅ API integration

***

# ⚡ Mental Models (Important)

* Think **streams**, not values

* Avoid manual `subscribe()` when possible

* Prefer `pipe()` + operators

* Use `async` pipe in Angular

***

# 🧠 The 5 Most Important RxJS Tools

If you only remember these:

* `map`

* `filter`

* `switchMap`

* `debounceTime`

* `Subject`

***

# 🔥 After This

You’re ready for:

* NgRx (state management)

* Advanced Angular architecture

* Real-time apps (WebSockets)

***

# 👉 Want Next Level?

I can guide you through:

* 🧠 **NgRx Bootcamp (Redux-style Angular state)**

* 🏗️ **Enterprise Angular architecture**

* ⚡ **RxJS deep-dive (marble diagrams + advanced patterns)**

Just tell me 👍

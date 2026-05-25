---
id: 20260426122314
title: RxJS Deep Dive
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, RxJS ]
---

# RxJS Deep Dive

Alright—now we go beyond “using RxJS” into **thinking in RxJS**. This is where Angular apps start to feel _clean, predictable, and powerful_ instead of messy.

***

# 🧠 RxJS Deep Dive (Advanced)

We’ll focus on **mental models + real patterns** you’ll actually use in Angular.

Using **RxJS** with **Angular**.

***

# 1. 🔄 Cold vs Hot Observables (Critical Concept)

## ❄️ Cold (default)

Each subscriber gets its own execution:

```ts
const obs$ = new Observable(observer => {
  console.log("Executed");
  observer.next(Math.random());
});

obs$.subscribe();
obs$.subscribe();
```

👉 Output: runs twice

***

## 🔥 Hot (shared)

Use **Subject**:

```ts
const subject = new Subject<number>();

subject.subscribe(v => console.log("A", v));
subject.subscribe(v => console.log("B", v));

subject.next(1);
```

👉 Output: both receive same value

***

## 💡 Angular Insight

* HTTP → cold

* UI events → hot

***

# 2. 🧩 Higher-Order Observables (THE Hard Part)

Observable of Observables:

```ts
search$.pipe(
  map(term => http.get(`/api?q=${term}`))
)
```

You get:

```id="1zbv0b"
Observable<Observable<Data>>
```

👉 You must flatten it!

***

## 🔥 The 4 Flattening Operators

### 1. `switchMap` ⭐ (default choice)

```ts
search$.pipe(
  switchMap(term => http.get(`/api?q=${term}`))
)
```

✔ Cancels previous requests\
✔ Best for search

***

### 2. `mergeMap`

```ts
click$.pipe(
  mergeMap(() => http.post('/save'))
)
```

✔ Runs all in parallel\
❗ No cancellation

***

### 3. `concatMap`

```ts
queue$.pipe(
  concatMap(task => http.post('/process', task))
)
```

✔ Sequential (queue)

***

### 4. `exhaustMap`

```ts
login$.pipe(
  exhaustMap(() => http.post('/login'))
)
```

✔ Ignores new events while running\
✔ Great for login buttons

***

## 🧠 Rule of Thumb

* Search → `switchMap`

* Save → `mergeMap`

* Queue → `concatMap`

* Button spam → `exhaustMap`

***

# 3. 🧪 Multicasting & Caching

## Problem

Multiple subscribers = multiple HTTP calls ❌

***

## ✅ Solution: `shareReplay`

```ts
tasks$ = this.http.get('/api/tasks').pipe(
  shareReplay(1)
);
```

✔ One HTTP call\
✔ Cached value\
✔ Shared stream

***

## ⚠️ Pitfall

Without `shareReplay`, Angular may refetch multiple times.

***

# 4. 🧵 Stream Composition

Think LEGO blocks:

```ts
tasks$ = refresh$.pipe(
  startWith(null),
  switchMap(() => this.http.get('/api/tasks'))
);
```

👉 You now control refresh manually!

***

## 💡 Pattern: Refresh Trigger

```ts
private refresh$ = new Subject<void>();

reload() {
  this.refresh$.next();
}
```

***

# 5. 🧼 Avoid Manual subscribe()

## ❌ Bad

```ts
this.http.get('/api').subscribe(data => {
  this.data = data;
});
```

***

## ✅ Good

```ts
data$ = this.http.get('/api');
```

```html
{{ data$ | async | json }}
```

***

## 💡 Why?

* Auto unsubscribe

* Cleaner code

* Reactive UI

***

# 6. 🧨 Memory Leaks & Unsubscribe

## Problem

```ts
interval(1000).subscribe();
```

👉 Never stops

***

## ✅ Solutions

### Option 1: `async` pipe (best)

### Option 2: `takeUntil`

```ts
destroy$ = new Subject<void>();

ngOnDestroy() {
  this.destroy$.next();
  this.destroy$.complete();
}

obs$.pipe(
  takeUntil(this.destroy$)
).subscribe();
```

***

# 7. ⚡ Error Handling

```ts
this.http.get('/api').pipe(
  catchError(err => {
    console.error(err);
    return of([]);
  })
);
```

***

## 💡 Rule

Streams should **never die silently**

***

# 8. 🧭 State Management with RxJS (Mini Store)

You don’t always need NgRx.

***

## Example Store

```ts
private tasksSubject = new BehaviorSubject<string[]>([]);
tasks$ = this.tasksSubject.asObservable();

add(task: string) {
  const current = this.tasksSubject.value;
  this.tasksSubject.next([...current, task]);
}
```

***

## 💡 Why `BehaviorSubject`?

* Holds current value

* Emits immediately to new subscribers

***

# 9. 🧠 Marble Thinking (Mental Model)

Instead of code, think:

```id="5qyo3c"
--a---b---c---->
      map(x2)
--aa--bb--cc--->
```

***

## Key Insight

You are **transforming timelines**, not values.

***

# 10. 🧩 Real Angular Pattern (Production-Ready)

## Task Service

```ts
private refresh$ = new Subject<void>();

tasks$ = this.refresh$.pipe(
  startWith(null),
  switchMap(() => this.http.get('/api/tasks')),
  shareReplay(1)
);
```

***

## Component

```ts
reload() {
  this.taskService.reload();
}
```

***

## Template

```html
<button (click)="reload()">Refresh</button>

<div *ngFor="let task of tasks$ | async">
  {{ task.name }}
</div>
```

***

# 🔥 Golden Rules

1. Prefer `switchMap` by default

2. Avoid nested `subscribe()`

3. Use `async` pipe

4. Cache with `shareReplay`

5. Think in streams, not variables

***

# 🧠 What You’ve Achieved

You now understand:

* Stream composition

* Async control flow

* Cancellation

* Reactive state

👉 This is **senior-level Angular skill**

***

# 🚀 Next Step (Highly Recommended)

You’re now ready for:

* 🧠 **NgRx Bootcamp (Redux-style state)**

* ⚡ **Signals vs RxJS (modern Angular)**

* 🏗️ **Enterprise Angular architecture**

***

If you want, I can:

* Build a **real production-grade Angular + RxJS app with you step-by-step**

* Or give you a **challenging project to solidify everything**

Just tell me 👍

---
id: 20260425213745
title: Angular RxJS Tutorial
author: Karl Schmitt
date: 2026-04--25
keywords: [ Angular, RxJS, Tutorial]
---

# Angular RxJS Tutorial

# Angular RxJS Tutorial: Master Reactive Programming

This tutorial covers the essentials of RxJS within the context of modern Angular (v16+). We will move from basic concepts to advanced patterns and integration with Angular Signals.

---

## 1. What is RxJS?

**RxJS (Reactive Extensions for JavaScript)** is a library for composing asynchronous and event-based programs using **observable sequences**.

Think of RxJS as **"Lodash for events."** It allows you to treat data coming from a server, a user clicking a button, or a timer as a continuous stream of data that you can transform, combine, and filter.

---

## 2. Core Concepts

### Observable
The "Producer." A data stream that can emit multiple values over time.
```typescript
import { Observable } from 'rxjs';

const stream$ = new Observable(subscriber => {
  subscriber.next('Hello');
  subscriber.next('World');
  subscriber.complete();
});
```

### Observer (Subscriber)
The "Consumer." A set of callbacks that listen to the values delivered by the Observable.
```typescript
stream$.subscribe({
  next: (val) => console.log(val),
  error: (err) => console.error(err),
  complete: () => console.log('Done!')
});
```

### Pipe & Operators
Operators are functions that allow you to transform the stream. The `.pipe()` method is where you string them together.

---

## 3. Essential Operators

To use operators, you must import them from `rxjs` or `rxjs/operators`.

### Transformation Operators
*   **`map`**: Transform each emitted value.
*   **`switchMap`**: (Crucial for HTTP) Cancels the previous inner observable and switches to a new one. Useful for search inputs.

### Filtering Operators
*   **`filter`**: Only allow values that pass a condition.
*   **`debounceTime`**: Wait for a pause in events (e.g., stop typing for 300ms).
*   **`distinctUntilChanged`**: Only emit if the current value is different from the last.

### Example: Search Logic
```typescript
import { debounceTime, distinctUntilChanged, switchMap } from 'rxjs';

searchControl.valueChanges.pipe(
  debounceTime(300),
  distinctUntilChanged(),
  switchMap(term => this.apiService.search(term))
).subscribe(results => this.results = results);
```

---

## 4. Using RxJS in Angular Components

### The `AsyncPipe` (Recommended)
Instead of manually subscribing in your TypeScript file, use the `async` pipe in your HTML. This automatically handles **unsubscribing**, preventing memory leaks.

**Component:**
```typescript
@Component({ ... })
export class UserComponent {
  // $ suffix is a convention for Observables
  users$ = this.http.get<User[]>('https://api.example.com/users');

  constructor(private http: HttpClient) {}
}
```

**Template:**
```html
<ul>
  <li *ngFor="let user of users$ | async">
    {{ user.name }}
  </li>
</ul>
```

---

## 5. Subjects and State Management

A **Subject** is a special type of Observable that allows values to be multicasted to many Observers. 

### BehaviorSubject
A `BehaviorSubject` is the most common tool for state management. It:
1. Requires an initial value.
2. Emits the **current value** immediately to new subscribers.

**Service Pattern:**
```typescript
import { BehaviorSubject } from 'rxjs';

@Injectable({ providedIn: 'root' })
export class CartService {
  private cartItems = new BehaviorSubject<string[]>([]);
  
  // Expose as an Observable so components can't call .next()
  cartItems$ = this.cartItems.asObservable();

  addToCart(item: string) {
    const current = this.cartItems.value;
    this.cartItems.next([...current, item]);
  }
}
```

---

## 6. Handling Unsubscription

If you `.subscribe()` manually, you **must** unsubscribe when the component is destroyed to prevent memory leaks.

### Modern Approach: `takeUntilDestroyed`
Since Angular 16, use the `takeUntilDestroyed` operator.

```typescript
import { Component, inject, DestroyRef } from '@angular/core';
import { takeUntilDestroyed } from '@angular/core/rxjs-interop';

@Component({ ... })
export class MyComponent {
  constructor() {
    this.myObservable$.pipe(
      takeUntilDestroyed() // Automatically cleans up
    ).subscribe(data => console.log(data));
  }
}
```

---

## 7. RxJS vs. Signals (Angular 16+)

Angular introduced **Signals** for fine-grained reactivity. Here is how they compare:

| Feature | RxJS | Signals |
| :--- | :--- | :--- |
| **Best for** | Asynchronous events (HTTP, WebSockets, Timers) | Synchronous state (UI variables, derived data) |
| **Complexity** | High (Powerful but steep learning curve) | Low (Easier to read/write) |
| **Emits** | Multiple values over time | A single stable value |

### Interop: Converting between them
You can mix both using `@angular/core/rxjs-interop`:

```typescript
import { toSignal, toObservable } from '@angular/core/rxjs-interop';

// 1. Observable -> Signal
users = toSignal(this.userService.getUsers$(), { initialValue: [] });

// 2. Signal -> Observable
userSearch$ = toObservable(this.searchSignal);
```

---

## 8. Best Practices Checklist

1.  **Avoid nested subscribes**: Never subscribe inside another subscribe. Use `switchMap`, `mergeMap`, or `concatMap`.
2.  **Declarative approach**: Try to define your observables at the top of the class and use the `async` pipe.
3.  **Naming convention**: Suffix observable names with `$` (e.g., `data$`).
4.  **Error Handling**: Always add a `catchError` to your streams to prevent the observable from "dying" on a failed HTTP request.
    ```typescript
    data$ = this.http.get('/api').pipe(
      catchError(err => {
        console.error(err);
        return of([]); // Return fallback data
      })
    );
    ```

---

## Summary
RxJS is the engine behind Angular's asynchronous power. While **Signals** are taking over for UI state, **RxJS** remains the gold standard for handling complex data streams, API calls, and event orchestration.
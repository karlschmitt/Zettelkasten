---
id: 20260424132153
title: What is RxJS?
author: Karl Schmitt
date: 2024-04-24
keywords: [ Angular, RxJS ]
---

# What is RxJS?

**RxJS** (Reactive Extensions for JavaScript) is a library for **reactive programming** using **Observables**. 

It is a core dependency of Angular. You use it to handle asynchronous tasks, such as HTTP requests, user input, and timers, by treating them as **streams of data.**

---

### The Core Concept: The "Stream"
Imagine a water pipe. Water (data) flows through the pipe over time. You can:
1.  **Observe** the water coming out.
2.  **Filter** out impurities (filter the data).
3.  **Transform** the water into ice cubes (map the data).
4.  **Combine** it with another pipe (merge data).

In RxJS, everything is a stream: a single click, an HTTP response, or even an array of numbers.

---

### The 4 Main Pillars of RxJS

#### 1. Observable
The **Observable** is the "source" of the data. It represents a collection of values that will arrive over time. It doesn't do anything until someone starts listening to it.
*   *Analogy:* A Netflix show. It exists on the server, but it doesn't "play" until you hit play.

#### 2. Observer (and Subscription)
The **Observer** is the "listener." To get data out of an Observable, you must **`.subscribe()`** to it. When you subscribe, you provide three callbacks:
*   `next`: What to do when a new value arrives.
*   `error`: What to do if something goes wrong.
*   `complete`: What to do when the stream ends.

#### 3. Operators
Operators are pure functions that allow you to modify, filter, or combine data streams. They are used inside a `.pipe()`.
*   `map`: Change the data (e.g., convert a string to uppercase).
*   `filter`: Only let certain data through (e.g., only numbers greater than 10).
*   `switchMap`: Cancel the previous request and start a new one (great for search bars).

#### 4. Subject
A **Subject** is a special type of Observable that allows values to be multicasted to many Observers. While a regular Observable is like a 1-on-1 phone call, a Subject is like a **Radio Station** (one source, many listeners).

---

### Simple Code Example
Here is how you would use RxJS to handle a stream of numbers:

```typescript
import { of } from 'rxjs';
import { map, filter } from 'rxjs/operators';

// 1. Create an Observable (The Source)
const numbers$ = of(1, 2, 3, 4, 5);

// 2. Use Operators to transform the data (The Pipe)
const processedNumbers$ = numbers$.pipe(
  filter(n => n % 2 !== 0), // Only odd numbers: 1, 3, 5
  map(n => n * 10)          // Multiply by 10: 10, 30, 50
);

// 3. Subscribe to get the result (The Listener)
processedNumbers$.subscribe(val => console.log(val)); 
// Output: 10, 30, 50
```

---

### RxJS vs. Promises
You might wonder: "Why not just use Promises?"

| Feature | Promise | Observable (RxJS) |
| :--- | :--- | :--- |
| **Values** | Emits only **one** value. | Emits **multiple** values over time. |
| **Execution** | Starts immediately. | "Lazy" (Starts only when you subscribe). |
| **Cancellation** | Cannot be cancelled. | Can be cancelled (unsubscribe). |
| **Operators** | None. | Powerful operators (map, filter, retry, debounce). |

---

### Why is RxJS so important in Angular?
Angular is built from the ground up to be reactive. You will encounter RxJS in almost every part of the framework:
*   **HttpClient:** `http.get()` returns an Observable.
*   **Reactive Forms:** `valueChanges` is an Observable that emits every time you type in a field.
*   **Router:** `params` and `data` are Observables.
*   **Event Emitters:** Used for component communication.

### How to start learning it?
1.  **Don't try to learn all 100+ operators.** Focus on the "Big 6": `map`, `filter`, `switchMap`, `take`, `tap`, and `catchError`.
2.  **Use [RxMarbles.com](https://rxmarbles.com/):** This site provides visual diagrams of how operators work.
3.  **Think in streams:** Instead of thinking "When this button is clicked, do X," think "I have a stream of clicks, and I want to map them to an API call."
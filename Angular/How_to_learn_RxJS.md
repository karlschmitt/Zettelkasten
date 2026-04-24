---
id: 20260424132645
title: How to learn RxJS?
author: Karl Scmitt
date: 2026-04-24
keywords: [ Angular, RxJS ]
---

# How to learn RxJS?

RxJS is notoriously one of the hardest parts of Angular to master because it requires a "mindset shift" from **Imperative programming** (doing things step-by-step) to **Reactive programming** (defining how to react to data streams).

Here is a structured, 5-step roadmap to learning RxJS without getting overwhelmed.

---

### Step 1: The Mindset Shift (Streams)
Before looking at code, understand the philosophy. 
*   **Imperative (Standard JS):** "Go get the data, then console log it."
*   **Reactive (RxJS):** "When data arrives in this stream, console log it."

Think of RxJS like a **conveyor belt** in a factory. Items (data) come down the belt, and you set up machines (operators) to check, change, or combine those items before they reach the end.

---

### Step 2: Master the "Big Three" Concepts
Don't try to learn everything. Start with these three:

1.  **Observable:** The source of data (the conveyor belt).
2.  **Observer/Subscription:** The person at the end of the belt. Data only starts moving when you call `.subscribe()`.
3.  **Operators:** The machines on the belt that modify data (placed inside `.pipe()`).

---

### Step 3: Learn the "Essential 8" Operators
There are over 100 operators, but you will use these 8 for 90% of your work. Ignore the rest for now.

1.  **`of` / `from`:** Create an observable from a simple value or an array.
2.  **`map`:** Transform the data (like `Array.map`).
3.  **`filter`:** Only let certain data through.
4.  **`tap`:** "Spy" on the data (use this for `console.log`) without changing it.
5.  **`take(1)`:** Get the first value and then automatically unsubscribe (great for memory management).
6.  **`catchError`:** Handle API or stream failures gracefully.
7.  **`switchMap` (The King of Operators):** If a new request comes in, cancel the old one and switch to the new one (essential for search bars).
8.  **`combineLatest`:** Wait for two different streams to both have values, then give them to you as a pair.

---

### Step 4: Visual Learning (Marble Diagrams)
RxJS deals with **time**, which is hard to read in text. Use **Marble Diagrams** to see how operators work.
*   **Resource:** [RxMarbles.com](https://rxmarbles.com/)
*   **Resource:** [Interactive RxJS Operator Decision Tree](https://rxjs.dev/operator-decision-tree) (The official "I want to do X, which operator should I use?" tool).

---

### Step 5: Understand Subjects (The "Radio Station")
A standard Observable is "unicast" (one source to one listener). A **Subject** is "multicast" (one source to many listeners).
*   **`BehaviorSubject`:** This is the most important one. It holds the "current value" so that anyone who subscribes late immediately gets the last known piece of data. This is how 99% of Angular state management services are built.

---

### Step 6: RxJS in Angular (Best Practices)
Since you are learning this for Angular, follow these rules:

1.  **Prefer the `async` pipe:** Use `{{ data$ | async }}` in your HTML templates. This automatically subscribes and **unsubscribes** for you, preventing memory leaks.
2.  **Avoid nested subscribes:** If you find yourself writing a `.subscribe()` inside another `.subscribe()`, you should be using a flattening operator like `switchMap` or `mergeMap`.
3.  **Unsubscribe:** If you subscribe manually in a component, you **must** unsubscribe in `ngOnDestroy` (or use the new `takeUntilDestroyed` operator in Angular 16+).

---

### Top Recommended Resources

*   **[LearnRxJS.io](https://www.learnrxjs.io/):** This is the "Bible" of RxJS. It lists every operator with clear examples and "Why use this?" sections.
*   **[RxJS.dev](https://rxjs.dev/):** The official documentation.
*   **Joshua Morony (YouTube):** He has excellent "High Level" explanations of RxJS in Angular.
*   **Deborah Kurata:** Look for her "RxJS in Angular" courses on Pluralsight or her talks on YouTube. She is the master of explaining these concepts clearly.

### The "Golden Rule" of Learning RxJS
**Don't try to memorize operators.** Learn that they exist, and then look them up when you have a specific problem to solve. Eventually, the patterns will stick.
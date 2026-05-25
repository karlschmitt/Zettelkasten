---
id: 20260423134903
title: How do Angular signals work?
author: Karl Schmitt
date: 2026-04-23
keywords: []
---

# How do Angular signals work?

At its core, **Angular Signals** are a system that granularly tracks how and where your state is used throughout an application. This allows Angular to update only the specific parts of the UI that change, rather than checking the entire component tree.

Think of a Signal as a **wrapper around a value** that can notify anyone interested when that value changes.

---

### 1. The Three Core Building Blocks

#### A. The Signal (The Producer)
This is the "source of truth." It holds a value that can be changed.
```typescript
const count = signal(0);

// Reading the value: Call it like a function
console.log(count()); 

// Changing the value
count.set(5); 
count.update(val => val + 1);
```

#### B. Computed Signal (The Derived State)
These are read-only signals that derive their value from other signals. They are **lazy** and **memoized** (they only recalculate if the source signal changes).
```typescript
const doubleCount = computed(() => count() * 2);
```

#### C. Effect (The Consumer)
An effect is an operation that runs whenever the signals it depends on change. This is used for side effects like logging, API calls, or manual DOM manipulation.
```typescript
effect(() => {
  console.log(`The count is now: ${count()}`);
});
```

---

### 2. How it works "Under the Hood" (The Producer-Consumer Pattern)

The magic of Signals lies in **Automatic Dependency Tracking**. You don't have to tell Angular which signals a `computed` or `effect` depends on; it figures it out automatically.

#### The "Getter" Registration
When you call `count()` inside a `computed` or `effect`, a hidden mechanism triggers:
1.  **The Context:** Angular sets a "Global Consumer" context (e.g., "I am currently running the `doubleCount` calculation").
2.  **The Read:** You call `count()`.
3.  **The Link:** The `count` signal notices there is an active consumer. It adds that consumer to its "subscriber list."
4.  **The Value:** The signal returns the value.

#### The Notification (The Dependency Graph)
When you update a signal via `.set()`, the signal doesn't immediately force the UI to redraw. Instead:
1.  It sends a notification to all its **consumers** (computeds and effects) saying: *"Hey, I've changed. Your current cached value is now stale."*
2.  If those consumers are also signals (like a `computed`), they pass the notification down the chain.
3.  **The Pull:** The next time the value is needed (e.g., when the browser is ready to paint), the consumer "pulls" the new value.

---

### 3. Key Concepts that make them special

#### 1. Glitch-Free Reactivity
In older reactive systems, if you had a value derived from two other values, you might get "intermediate" incorrect states (glitches). Signals use a "Push-then-Pull" algorithm to ensure that no matter how complex your graph is, the value is always consistent when you read it.

#### 2. No "Monkey Patching" (Bye-bye Zone.js)
Traditionally, Angular used **Zone.js** to intercept every click, timer, and HTTP request to check if *anything* changed. This is expensive. 
Signals tell Angular **exactly** which component and which specific part of the template needs to change. This allows Angular to eventually run without Zone.js (**Zoneless mode**), leading to much better performance.

#### 3. Signals vs. RxJS
*   **RxJS (Observables):** Great for *events* and *asynchronous streams* (e.g., clicking a button 5 times, handling a web socket, debouncing an input). It is "Push-based."
*   **Signals:** Great for *state* (e.g., "Is the sidebar open?", "What is the user's name?", "The total price of the cart"). It is "Pull-based."

---

### 4. What it looks like in a Component
In the new "Angular Renaissance" style, your component looks like this:

```typescript
@Component({
  template: `
    <h1>{{ title() }}</h1>
    <button (click)="increment()">Add</button>
    <p>Total: {{ total() }}</p>
  `
})
export class App {
  // 1. State
  count = signal(0);
  title = signal('My Counter');

  // 2. Derived State
  total = computed(() => this.count() * 100);

  // 3. Logic
  increment() {
    this.count.update(c => c + 1);
  }
}
```

### Summary
Angular Signals work by creating a **dependency graph**. When you read a signal, you are registered as a listener. When the signal changes, it notifies you that your value is old. This makes Angular faster because it stops guessing what changed and starts **knowing** exactly what changed.

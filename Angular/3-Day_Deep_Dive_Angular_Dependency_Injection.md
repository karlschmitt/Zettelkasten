---
id: 20260424174727
title: 3-Day Deep Dive Angular Dependency Injection
author: Karl Schmitt
date: 2026-04-24
keywords: [ Angular, DI, Dependecy Injection, Deep Dive ]
---

# 3-Day Deep Dive Angular Dependency Injection

Good call—this is exactly the kind of focused deep dive that makes Angular “click.”

This **3-day Dependency Injection (DI) mini bootcamp** is designed to give you _real intuition_, not just syntax.

***

# 🅰️ 3-Day Deep Dive — Angular Dependency Injection

We’ll go from:\
👉 “I can use DI”\
to\
👉 “I understand how Angular builds and controls my app”

Using Angular + a bit of RxJS thinking where useful.

***

# 🗓️ Day 1 — The Core: Injection & Shared State

## 🎯 Goal

Understand:

* What Angular _actually does_ when injecting

* Singleton services

* Shared state across components

***

## 🧪 Exercise 1 — Build a Shared Counter

### Step 1 — Service

```bash
ng generate service counter
```

```ts
@Injectable({ providedIn: 'root' })
export class CounterService {
  count = 0;

  increase() {
    this.count++;
  }
}
```

***

### Step 2 — Two Components

```bash
ng generate component counter-a
ng generate component counter-b
```

***

### Step 3 — Inject in both

```ts
constructor(public counter: CounterService) {}
```

***

### Step 4 — Template

```html
<h2>{{ counter.count }}</h2>
<button (click)="counter.increase()">+</button>
```

***

## 🔥 What you should see

👉 Clicking in A updates B instantly

***

## 🧠 Key Insight

> `providedIn: 'root'` = ONE shared instance (singleton)

Angular created ONE service and gave it to both components.

***

## 🧪 Exercise 2 — Break It (Important!)

Add this to ONE component:

```ts
@Component({
  providers: [CounterService]
})
```

***

## 🤯 Observe

Now:

* A and B have **different counters**

***

## 🧠 Insight #2

> Providers define **scope**

***

# 🗓️ Day 2 — Injector Hierarchy (The Hidden System)

## 🎯 Goal

Understand:

* How Angular decides WHICH instance to give you

* Component-level vs root-level injection

***

## 🧠 Concept

Angular has a **tree of injectors**:

```text
Root Injector
   ↓
AppComponent
   ↓
Child Components
```

Each level can provide its own services.

***

## 🧪 Exercise 1 — Visualize the Tree

Create structure:

```bash
ng generate component parent
ng generate component child
```

***

### Parent template

```html
<app-child></app-child>
```

***

### Provide service in parent

```ts
@Component({
  providers: [CounterService]
})
```

***

### Inject in both parent + child

***

## 🔥 Result

👉 Parent and child share SAME instance\
👉 But different from app-level

***

## 🧠 Insight

> Angular walks UP the tree to find a provider

***

## 🧪 Exercise 2 — Override Behavior

* Provide service in child ALSO

```ts
@Component({
  providers: [CounterService]
})
```

***

## 🤯 Result

👉 Child now has its OWN instance\
👉 Parent still has its own

***

## 🧠 Insight #2

> Closest provider wins

***

# 🗓️ Day 3 — Real Power: Tokens, Factories & Advanced DI

## 🎯 Goal

Understand:

* Custom injection tokens

* Factory providers

* How Angular injects built-in services

***

## 🧩 Part 1 — Injection Tokens

Used when:

* You don’t inject a class

* You inject a value/config

***

### Example

```ts
import { InjectionToken } from '@angular/core';

export const API_URL = new InjectionToken<string>('api.url');
```

***

### Provide it

```ts
providers: [
  { provide: API_URL, useValue: 'https://api.example.com' }
]
```

***

### Inject it

```ts
constructor(@Inject(API_URL) private apiUrl: string) {}
```

***

## 🧠 Why this matters

👉 This is how Angular config works internally

***

## 🧪 Exercise

* Create your own `API_URL`

* Log it in component

***

# 🧩 Part 2 — Factory Providers

## 🧠 Concept

Dynamic creation logic

***

### Example

```ts
{
  provide: CounterService,
  useFactory: () => {
    const service = new CounterService();
    service.count = 100;
    return service;
  }
}
```

***

## 🧪 Exercise

* Initialize counter with custom value

* Change behavior dynamically

***

# 🧩 Part 3 — Built-in DI Example

Angular injects things like:

```ts
constructor(private http: HttpClient) {}
```

👉 This comes from Angular’s internal DI system.

***

## 🧠 Final Insight

> DI is not a feature—it’s the **core engine of Angular**

***

# 🧠 What You Now Understand

After 3 days, you should be able to explain:

* Why services are shared

* How scope works

* How Angular resolves dependencies

* How to override behavior

* How to inject configs

***

# ⚠️ Common Pitfalls

* Thinking DI = “just constructor syntax”

* Ignoring provider scope

* Overusing component-level providers

***

# 🧪 Final Challenge 🚀

Build:

## 🎯 “Configurable Counter App”

### Requirements:

* CounterService

* API\_URL token

* Factory-based initialization

* Two counters:

  * One global

  * One local

👉 They must behave differently

***

# 🔁 Mastery Loop

For DI:

1. Inject

2. Share

3. Scope it

4. Override it

5. Customize it

***

If you want to go even deeper next:

👉 NgRx + DI (advanced state management)\
👉 Signals vs DI interplay\
👉 Real-world architecture patterns

Just tell me 👍



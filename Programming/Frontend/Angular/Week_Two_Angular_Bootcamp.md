---
id: 20260423131319
title: Week Two Angular Bootcamp
author: Karl Schmitt
date: 2026-04-23
keywords: [ Angular]
---

# Week Two Angular Bootcamp

Good—this is where Angular starts to feel like a real framework instead of just “components on a page.”

**Week 2 is about communication and structure.**\
You’ll stop building isolated components and start building _connected systems_.

***

# 🅰️ Week 2 — Component Communication & Architecture

## 🎯 Goal of Week 2

By the end, you will:

* Pass data **down** (`@Input`)

* Send events **up** (`@Output`)

* Structure apps like a real Angular project

* Understand parent–child relationships

***

# 🗓️ Day 1 — Parent → Child (`@Input`)

## 🧠 Concept

A parent component sends data to a child.

***

## Example

### Parent (`app.component.html`)

```html
<app-counter [startValue]="5"></app-counter>
```

### Child (`counter.component.ts`)

```ts
import { Input } from '@angular/core';

@Input() startValue = 0;

count = this.startValue;
```

***

⚠️ Important:

* `@Input()` makes a property **public to the parent**

* Data flows **one way (down)**

***

## 🧪 Exercise

* Pass different values:

```html
<app-counter [startValue]="10"></app-counter>
<app-counter [startValue]="100"></app-counter>
```

👉 You should see independent counters.

***

# 🗓️ Day 2 — Child → Parent (`@Output`)

## 🧠 Concept

Child sends events to parent using **EventEmitter**

***

## Example

### Child (`counter.component.ts`)

```ts
import { Output, EventEmitter } from '@angular/core';

@Output() countChanged = new EventEmitter<number>();

increase() {
  this.count++;
  this.countChanged.emit(this.count);
}
```

***

### Parent (`app.component.html`)

```html
<app-counter (countChanged)="onCountChanged($event)"></app-counter>
```

### Parent (`app.component.ts`)

```ts
onCountChanged(value: number) {
  console.log('New value:', value);
}
```

***

## 🧪 Exercise

* Log every change in parent

* Display it in UI:

```html
<p>Last value: {{ lastValue }}</p>
```

***

# 🗓️ Day 3 — Combining Input & Output

Now we build a _real reusable component_.

***

## 🧪 Exercise: Smart Counter

### Requirements:

* Accept `startValue`

* Emit changes

* Parent tracks total clicks

***

### Parent idea:

```html
<app-counter 
  [startValue]="0"
  (countChanged)="track($event)">
</app-counter>
```

***

## 🧠 Key Insight

This pattern = **reusable + testable components**

***

# 🗓️ Day 4 — Multiple Components (Architecture)

Now think in **systems**, not files.

***

## Structure idea

```
AppComponent
 ├── HeaderComponent
 ├── CounterComponent
 └── DashboardComponent
```

***

## 🧪 Exercise

Create:

```bash
ng generate component dashboard
```

Use it:

```html
<app-dashboard></app-dashboard>
```

***

## Dashboard idea:

* Shows summary of counters

* Displays last updated value

***

# 🗓️ Day 5 — Smart vs Dumb Components

## 🧠 Concept

### Dumb (Presentational)

* Only UI

* Receives data via `@Input`

* Emits events

### Smart (Container)

* Holds logic

* Talks to services (later)

***

## 🧪 Exercise

Split your counter:

### Dumb:

* Only buttons + display

### Smart:

* Handles logic + state

***

👉 This is how real Angular apps are built.

***

# 🗓️ Day 6 — Reusability

## 🧠 Goal

Make components reusable like LEGO blocks.

***

## 🧪 Exercise

Create:

```bash
ng generate component button
```

Make it reusable:

```html
<app-button 
  label="Increase" 
  (clicked)="increase()">
</app-button>
```

***

### Inside button:

```ts
@Input() label = '';
@Output() clicked = new EventEmitter<void>();
```

***

👉 Now reuse it everywhere.

***

# 🗓️ Day 7 — Mini Project 🚀

## 🎯 Build: Counter Dashboard

### Features:

* Multiple counters

* Each has:

  * Custom start value

* Dashboard shows:

  * Last updated counter

  * Total interactions

***

## Example UI idea

```
[Counter 1] [+] [-]
[Counter 2] [+] [-]

Last updated: 12
Total clicks: 45
```

***

# 🧠 What You Learned This Week

* `@Input()` → data down

* `@Output()` → events up

* Component hierarchy

* Smart vs dumb components

* Reusable UI patterns

***

# ⚠️ Common Mistakes

* Forgetting to import:

```ts
import { Input, Output, EventEmitter } from '@angular/core';
```

* Mutating parent data directly ❌

* Overcomplicating small components

***

# 🔁 Your Practice Loop

For every component:

1. Can it be reused?

2. Does it depend on parent?

3. Can I split logic/UI?

***

# ⏭️ Next Week Preview

Week 3 will unlock:

* Routing (multi-page apps)

* Navigation

* URL parameters

👉 This is where Angular starts feeling like a **real app framework**

***

If you want to continue:

👉 **“Week 3 Angular Bootcamp”**

---
id: 20260423130638
title: Week One Angular Bootcamp
author: Karl Schmitt
date: 2026-04-23
keywords: [ Angular ]
---

# Week One Angular Bootcamp

Alright—let’s start your **Angular 21 Bootcamp, Week 1**.\
This week is about building a _solid mental model_ and getting your hands dirty immediately.

We’ll keep your usual style: **daily structure + hands-on coding + no fluff**.

***

# 🅰️ Week 1 — Angular Foundations

## 🎯 Goal of Week 1

By the end, you will:

* Understand what Angular actually does

* Create and run Angular apps

* Build your first components

* Use data binding confidently

***

# 🗓️ Day 1 — Setup & First App

## Install Angular CLI

You’ll need:

* Node.js (you already used Node.js 👍)

Install Angular CLI:

```bash
npm install -g @angular/cli
```

## Create your first app

```bash
ng new angular-bootcamp
cd angular-bootcamp
ng serve
```

Open:

```
http://localhost:4200
```

***

## 🧠 Understand the structure

Key files:

* `main.ts` → entry point

* `app.component.ts` → logic

* `app.component.html` → UI

* `app.component.css` → styles

Angular = **Component-based UI**

***

## 🧪 Exercise

Modify `app.component.html`:

```html
<h1>Hello Angular 🚀</h1>
<p>This is my first Angular app</p>
```

***

# 🗓️ Day 2 — Components

## What is a Component?

A component =\
👉 HTML + Logic + Style

Example:

```ts
@Component({
  selector: 'app-test',
  template: `<h2>Hello from component</h2>`
})
```

***

## Generate a component

```bash
ng generate component counter
```

Use it in `app.component.html`:

```html
<app-counter></app-counter>
```

***

## 🧪 Exercise

Edit `counter.component.html`:

```html
<h2>Counter works!</h2>
```

***

# 🗓️ Day 3 — Data Binding (Core Concept 🔥)

Angular binding types:

## 1. Interpolation

```html
<h1>{{ title }}</h1>
```

## 2. Property Binding

```html
<img [src]="imageUrl">
```

## 3. Event Binding

```html
<button (click)="increase()">Click</button>
```

## 4. Two-way Binding

```html
<input [(ngModel)]="name">
```

***

## 🧪 Exercise: Mini Counter

`counter.component.ts`:

```ts
count = 0;

increase() {
  this.count++;
}
```

`counter.component.html`:

```html
<h2>{{ count }}</h2>
<button (click)="increase()">+</button>
```

***

# 🗓️ Day 4 — Styling & Templates

## Add CSS

`counter.component.css`:

```css
h2 {
  color: blue;
}
```

***

## Template logic

```html
<p *ngIf="count > 5">High value!</p>
```

***

## 🧪 Exercise

* Change color when count > 5

* Show message when count === 10

***

# 🗓️ Day 5 — Events & Interaction

## Add more actions

```ts
decrease() {
  this.count--;
}

reset() {
  this.count = 0;
}
```

***

## 🧪 Exercise: Full Counter UI

```html
<h2>{{ count }}</h2>

<button (click)="increase()">+</button>
<button (click)="decrease()">-</button>
<button (click)="reset()">Reset</button>
```

***

# 🗓️ Day 6 — Angular CLI Power

## Generate stuff fast

```bash
ng generate component header
ng generate component footer
```

***

## 🧪 Exercise

Build layout:

```html
<app-header></app-header>
<app-counter></app-counter>
<app-footer></app-footer>
```

***

# 🗓️ Day 7 — Mini Project 🚀

## 🎯 Build: Counter App (Clean Version)

### Features:

* Display count

* * / - / Reset

* Message when:

  * negative

  * > 10

***

## 🧠 Bonus (optional)

Try:

* Input field for step size

* Button to add custom value

***

# 🧠 What You Learned This Week

* Angular project structure

* Components

* Data binding

* Events

* CLI workflow

***

# ⚠️ Common Mistakes

* Forgetting to **use components in HTML**

* Mixing up:

  * `(click)` vs `[value]`

* Not restarting `ng serve` after config changes

***

# 🔁 Your Study Loop

Each day:

1. Type code manually

2. Break it

3. Fix it

4. Add 1 extra feature

***

# ⏭️ Next Step

Week 2 will cover:

* Component communication

* `@Input()` / `@Output()`

* Real component architecture

***

👉 When ready, say:\
**“Week 2 Angular Bootcamp”**
_
---
id: 20260426172348
title: Angular Component Bootcamp
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, Component, Bootcamp ]
---

# Angular Component Bootcamp

Great—components are where Angular really _clicks_. If you master them, everything else (services, RxJS, state) becomes much easier.

Here’s a **hands-on Angular Component Bootcamp (7 days)** using **Angular** and the **Angular CLI**.

We’ll evolve a **Task Manager UI** step by step.

***

# 🚀 Angular Component Bootcamp (7 Days)

***
[Installing the Angular CLI](./Angular_CLI_Instalation.md)

[Angular Project Creation](./Angular_Project_Creation.md)

# 🗓️ Day 1 — Component Basics

## 🎯 Goal

Understand what a component _really is_

[Angular Component](./Angular_Component.md)

## 🧠 Concept

A component = **TypeScript + HTML + CSS**

***

## 🛠️ Create Component

[Angular Component Creation](./Angular_Component_Creation.md)
```bash
ng g c hello
```

***

## ✍️ Example

```ts
export class HelloComponent {
  name = "Karl";
}
```

```html
<p>Hello {{ name }} 👋</p>
```

***

## 🧩 Mini Task

* Change name dynamically

* Add a second variable (`role`)

***

# 🗓️ Day 2 — Templates & Directives

## 🎯 Goal

Control the DOM

***

## 🧠 Learn

* `*ngIf`

* `*ngFor`

* `[class]`, `[style]`

***

## ✍️ Example

```html
<ul>
  <li *ngFor="let task of tasks">
    {{ task }}
  </li>
</ul>
```

***

## 🧩 Mini Task

* Show message if no tasks

* Add conditional styling

***

# 🗓️ Day 3 — Inputs & Outputs (Communication)

## 🎯 Goal

Component interaction

***

## 🧠 Learn

* `@Input()`

* `@Output()`

***

## ✍️ Example

### Child

```ts
@Input() task!: string;
@Output() delete = new EventEmitter<void>();
```

```html
<span>{{ task }}</span>
<button (click)="delete.emit()">❌</button>
```

***

### Parent

```html
<app-task-item
  [task]="task"
  (delete)="removeTask(i)">
</app-task-item>
```

***

## 🧩 Mini Task

* Build `task-item` component

* Handle delete event

***

# 🗓️ Day 4 — Component Composition

## 🎯 Goal

Build real UI structure

***

## 🧠 Learn

* Parent-child hierarchy

* Reusability

***

## Structure

```text
task-page
 ├── task-input
 ├── task-list
      └── task-item
```

***

## 🧩 Mini Task

Split your UI into:

* Input component

* List component

* Item component

***

# 🗓️ Day 5 — Lifecycle Hooks

## 🎯 Goal

Control component lifecycle

***

## 🧠 Learn

* `ngOnInit`

* `ngOnChanges`

* `ngOnDestroy`

***

## ✍️ Example

```ts
ngOnInit() {
  console.log("Component initialized");
}
```

***

## 🧩 Mini Task

* Log when component loads

* Log when input changes

***

# 🗓️ Day 6 — Styling & View Encapsulation

## 🎯 Goal

Understand styling behavior

***

## 🧠 Learn

* Scoped styles

* Global styles

* Encapsulation modes

***

## ✍️ Example

```css
:host {
  display: block;
  padding: 10px;
}
```

***

## 🧩 Mini Task

* Style task items differently when completed

* Add hover effect

***

# 🗓️ Day 7 — Smart vs Dumb Components

## 🎯 Goal

Think like a professional

***

## 🧠 Concept

### Smart (Container)

* Fetch data

* Handle logic

### Dumb (Presentational)

* Only inputs/outputs

***

## ✍️ Example

### Smart

```ts
tasks$ = this.taskService.tasks$;
```

***

### Dumb

```ts
@Input() task!: Task;
@Output() delete = new EventEmitter<number>();
```

***

## 🧩 Final Project

Build:

### ✅ Features

* Add task

* Delete task

* Display list

### 🧠 Architecture

* Smart page component

* Dumb UI components

* Clean separation

***

# ⚡ Advanced Component Patterns

## 1. Async Pipe (Important)

Using **RxJS**:

```html
<div *ngFor="let task of tasks$ | async">
  {{ task }}
</div>
```

***

## 2. TrackBy (Performance)

```ts
trackById(index: number, item: Task) {
  return item.id;
}
```

***

## 3. Content Projection

```html
<app-card>
  <h2>Title</h2>
</app-card>
```

```html
<ng-content></ng-content>
```

***

# 🚫 Common Mistakes

❌ Huge components\
❌ Business logic in templates\
❌ Too many responsibilities\
❌ Manual DOM manipulation

***

# 🧠 Mental Model

Think:

```text
Component = UI + Behavior + Boundaries
```

***

# 🏁 What You Achieved

After this bootcamp you can:

* Build reusable UI components

* Structure Angular apps properly

* Handle communication cleanly

* Think in component architecture

***

# 🚀 Next Step

Now you’re ready for:

* 🧠 **Angular Forms Bootcamp (Reactive Forms)**

* 🏗️ **NgRx (state management)**

* ⚡ **Signals vs RxJS (modern Angular)**

***

If you want, I can:

* Build a **real-world Angular UI project with you step-by-step**

* Or give you a **challenging component architecture exercise**

Just tell me 👍

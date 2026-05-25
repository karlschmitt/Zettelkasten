---
id: 20260425210624
title: Angular CLI bootcamp
author: Karl Schmitt
date: 2026-04-25
keybords: [ Angular, CLI, bootcamp]
---

# Angular CLI bootcamp

Alright—let’s turn you into someone who can _actually build Angular apps_, not just follow tutorials.

Below is a **structured 7-day Angular CLI bootcamp** with daily goals, exercises, and a mini-project that grows each day.

***

# 🚀 Angular CLI Bootcamp (7 Days)

We’ll use the **Angular CLI** as your main tool and build a **Task Manager App** step by step.

***

# 🗓️ Day 1 — Setup + First App

## 🎯 Goal

Understand Angular basics + CLI workflow

## 🛠️ Tasks

```bash
ng new task-manager
cd task-manager
ng serve
```

## 🧠 Learn

* Project structure (`src/app`)

* What a component is

* Dev server

## ✍️ Exercise

Modify `app.component.html`:

```html
<h1>Task Manager 🚀</h1>
<p>My first Angular app</p>
```

## 🧩 Mini Task

Change title dynamically using interpolation:

```ts
title = "Task Manager by Karl";
```

***

# 🗓️ Day 2 — Components Deep Dive

## 🎯 Goal

Break UI into reusable parts

## 🛠️ Tasks

```bash
ng g c header
ng g c task-list
ng g c task-item
```

## 🧠 Learn

* Component structure

* Selector usage

* Parent ↔ child composition

## ✍️ Exercise

Use components:

```html
<app-header></app-header>
<app-task-list></app-task-list>
```

## 🧩 Mini Task

Create static tasks:

```html
<li>Learn Angular</li>
<li>Build App</li>
```

***

# 🗓️ Day 3 — Data Binding Mastery

## 🎯 Goal

Make UI dynamic

## 🧠 Learn

* Interpolation `{{ }}`

* Property binding `[ ]`

* Event binding `( )`

* Two-way binding

## ✍️ Exercise

```html
<input [(ngModel)]="taskName">
<button (click)="addTask()">Add</button>
```

```ts
taskName = "";

addTask() {
  console.log(this.taskName);
}
```

👉 Don’t forget:

```ts
import { FormsModule } from '@angular/forms';
```

## 🧩 Mini Task

Add tasks to an array and display with `*ngFor`

***

# 🗓️ Day 4 — Services + Dependency Injection

## 🎯 Goal

Move logic out of components

## 🛠️ Tasks

```bash
ng g s task
```

## 🧠 Learn

* What a service is

* Dependency Injection (DI)

* Singleton pattern in Angular

## ✍️ Exercise

```ts
export class TaskService {
  tasks: string[] = [];

  add(task: string) {
    this.tasks.push(task);
  }

  getAll() {
    return this.tasks;
  }
}
```

Use it:

```ts
constructor(private taskService: TaskService) {}
```

## 🧩 Mini Task

Move all task logic into the service

***

# 🗓️ Day 5 — Routing

## 🎯 Goal

Multi-page app

## 🛠️ Tasks

```bash
ng g c pages/home
ng g c pages/about
```

## 🧠 Learn

* Router

* Navigation

* `<router-outlet>`

## ✍️ Exercise

```ts
const routes = [
  { path: '', component: HomeComponent },
  { path: 'about', component: AboutComponent }
];
```

```html
<a routerLink="/">Home</a>
<a routerLink="/about">About</a>
```

## 🧩 Mini Task

Create:

* Home = task list

* About = description page

***

# 🗓️ Day 6 — HTTP + APIs

## 🎯 Goal

Fetch real data

## 🧠 Learn

* HttpClient

* Observables (intro)

## 🛠️ Setup

```ts
import { HttpClientModule } from '@angular/common/http';
```

## ✍️ Exercise

```ts
constructor(private http: HttpClient) {}

getTasks() {
  return this.http.get('https://jsonplaceholder.typicode.com/todos');
}
```

## 🧩 Mini Task

Display API tasks in your UI

***

# 🗓️ Day 7 — Build + Polish

## 🎯 Goal

Finish your app

## 🧠 Learn

* Production build

* Basic styling

* Clean structure

## 🛠️ Tasks

```bash
ng build
```

## ✍️ Improve

* Add delete button

* Add basic CSS

* Add empty state ("No tasks")

***

# 🧪 Final Project Features

By the end, your app should:

* ✅ Add tasks

* ✅ Delete tasks

* ✅ Use a service

* ✅ Navigate pages

* ✅ Fetch API data

***

# ⚡ Daily Routine (Important)

Each day:

1. Learn concepts (30–60 min)

2. Code (60–120 min)

3. Break something and fix it 😄

***

# 🔥 After This Bootcamp

Next steps:

* RxJS deep dive

* State management (NgRx)

* Forms (Reactive Forms)

* Real backend (Node.js / Firebase)

***

# 👉 Want More?

I can extend this into:

* 📅 **Week 2 (Advanced Angular CLI + Architecture)**

* 🧠 **RxJS Bootcamp (super important for Angular)**

* 🏗️ **Real-world app (Auth + Backend + Deployment)**

Just tell me what direction you want 👍

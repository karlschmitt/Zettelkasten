---
id: 20260426125928
title: Angular Project Structure Tutorial
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, project, structure, tutorial]
---

# Angular Project Structure Tutorial

A solid project structure is what separates “it works” from “this scales cleanly for months/years.” Let’s build you a **practical, real-world Angular structure** you can actually use.

We’ll base this on **Angular** and the **Angular CLI**.

---

# 🏗️ Angular Project Structure (Real-World Guide)

## 🧠 Core Principle

Structure by **feature**, not by file type.

👉 Bad (beginner):

```
components/
services/
models/
```

👉 Good (scalable):

```
features/
  tasks/
  auth/
  dashboard/
```

---

# 📁 1. Recommended Folder Structure

Here’s a **clean, production-ready layout**:

```
src/
└── app/
    ├── core/
    ├── shared/
    ├── features/
    │   ├── tasks/
    │   ├── auth/
    │   └── dashboard/
    ├── app.routes.ts
    └── app.component.ts
```

---

## 🔵 core/ — Singleton & App-Wide Stuff

**Used once, everywhere**

```
core/
├── services/
│   ├── api.service.ts
│   └── auth.service.ts
├── guards/
├── interceptors/
└── core.module.ts (optional)
```

### 💡 Examples

* Auth service
* HTTP interceptors
* Global config

---

## 🟢 shared/ — Reusable UI + Utilities

```
shared/
├── components/
│   ├── button/
│   └── modal/
├── pipes/
├── directives/
└── shared.module.ts
```

### 💡 Examples

* Buttons
* UI components
* Pipes

👉 No business logic here!

---

## 🟡 features/ — Business Logic (Most Important)

Each feature is **self-contained**:

```
features/
└── tasks/
    ├── components/
    │   ├── task-list/
    │   └── task-item/
    ├── pages/
    │   └── task-page/
    ├── services/
    │   └── task.service.ts
    ├── models/
    │   └── task.model.ts
    ├── store/ (optional)
    └── tasks.routes.ts
```

---

# 🧩 2. Feature Example (Tasks)

## Structure

```
tasks/
├── components/
├── pages/
├── services/
├── models/
```

---

## 🧠 Rule

* **components/** → small UI pieces
* **pages/** → route-level containers
* **services/** → logic + API
* **models/** → types/interfaces

---

# 🛣️ 3. Routing Structure

## App Routes

```ts
export const routes = [
  {
    path: 'tasks',
    loadChildren: () =>
      import('./features/tasks/tasks.routes')
  }
];
```

---

## Feature Routes

```ts
export const TASK_ROUTES = [
  {
    path: '',
    component: TaskPageComponent
  }
];
```

---

## 💡 Why?

* Lazy loading
* Faster apps
* Better separation

---

# ⚡ 4. Smart vs Dumb Components

## 🧠 Smart (Container)

```
pages/task-page/
```

* Fetch data
* Handle logic

---

## 🎨 Dumb (Presentational)

```
components/task-item/
```

* Input/Output only
* No business logic

---

## Example

```ts
@Input() task!: Task;
@Output() delete = new EventEmitter<number>();
```

---

# 🔄 5. Data Flow Pattern

```
Component → Service → API
          ← Observable ←
```

Using **RxJS**:

```ts
tasks$ = this.taskService.tasks$;
```

---

# 🧱 6. Naming Conventions (Important)

| Type      | Example                  |
| --------- | ------------------------ |
| Component | `task-list.component.ts` |
| Service   | `task.service.ts`        |
| Model     | `task.model.ts`          |
| Module    | `tasks.module.ts`        |

---

# 🧪 7. CLI Commands for Structure

```bash
ng g module core
ng g module shared
ng g module features/tasks --route tasks --module app
```

```bash
ng g c features/tasks/components/task-item
ng g c features/tasks/pages/task-page
ng g s features/tasks/services/task
```

---

# 🧠 8. Advanced (Optional but Powerful)

## 🧩 State Management

Inside feature:

```
store/
├── actions.ts
├── reducer.ts
├── effects.ts
```

(Used with NgRx or simple RxJS store)

---

## 🔐 Interceptors

```
core/interceptors/auth.interceptor.ts
```

---

## 🌐 Environment Config

```
environments/
├── environment.ts
├── environment.prod.ts
```

---

# 🚫 Common Mistakes

❌ Everything in `app/`
❌ Huge components
❌ Logic in templates
❌ No separation of concerns

---

# ✅ Clean Architecture Rules

* Features are independent
* Shared = reusable only
* Core = singleton only
* Use lazy loading
* Keep components small

---

# 🧠 Mental Model

Think like this:

```
App
 ├── Core (engine)
 ├── Shared (lego pieces)
 └── Features (actual app)
```

---

# 🚀 What This Unlocks

With this structure you can:

* Scale to large apps
* Add features easily
* Avoid spaghetti code
* Work like a professional Angular dev

---

# 👉 Want Next Level?

I can guide you through:

* 🏗️ **Enterprise Angular architecture (Nx-style monorepo)**
* 🧠 **NgRx integration with this structure**
* ⚡ **Angular Signals vs RxJS (modern patterns)**
* 🔥 **Build a full real-world app using this exact structure**

Just tell me 👍


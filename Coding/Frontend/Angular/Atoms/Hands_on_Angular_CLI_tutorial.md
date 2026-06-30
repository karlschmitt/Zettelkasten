---
id: 20260425205425
title: Hands on Angular CLI tutorial
author: Karl Schmitt
date: 3026-04-25
keywords: [ Angular, CLI, tutorial]
---

# Hands on Angular CLI tutorial

Here’s a **practical Angular CLI tutorial** you can follow step-by-step. I’ll keep it hands-on so you actually _build something_ instead of just reading docs.

***

# 🚀 Angular CLI Tutorial (Hands-On)

## 1. What is the Angular CLI?

The **Angular CLI** is a command-line tool that helps you:

* Create Angular projects

* Generate components/services

* Run a dev server

* Build and test apps

***

## 2. Install Angular CLI

Make sure you have **Node.js** installed.

Then install Angular CLI globally:

```bash
npm install -g @angular/cli
```

Check installation:

```bash
ng version
```

***

## 3. Create Your First Angular App

```bash
ng new my-first-app
```

You’ll be asked:

* Routing? → Yes

* Stylesheet? → CSS (or SCSS if you prefer)

Then:

```bash
cd my-first-app
ng serve
```

Open browser:

```
http://localhost:4200
```

***

## 4. Project Structure (Quick Overview)

```
my-first-app/
├── src/
│   ├── app/
│   │   ├── app.component.ts
│   │   ├── app.component.html
│   │   ├── app.module.ts
│   ├── main.ts
│   ├── index.html
```

Key files:

* `main.ts` → app entry point

* `app.component.ts` → root component

* `app.module.ts` → main module

***

## 5. Generate Your First Component

```bash
ng generate component hello
```

Shortcut:

```bash
ng g c hello
```

Angular CLI creates:

```
hello/
├── hello.component.ts
├── hello.component.html
├── hello.component.css
```

***

## 6. Use the Component

Edit `app.component.html`:

```html
<h1>My Angular CLI App 🚀</h1>
<app-hello></app-hello>
```

***

## 7. Add Data Binding

Edit `hello.component.ts`:

```ts
export class HelloComponent {
  name = "Karl";
}
```

Edit `hello.component.html`:

```html
<p>Hello {{ name }} 👋</p>
```

***

## 8. Add a Button + Event Binding

```html
<button (click)="changeName()">Change Name</button>
```

```ts
changeName() {
  this.name = "Angular Learner";
}
```

***

## 9. Generate a Service

```bash
ng g s data
```

Example service:

```ts
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class DataService {
  getMessage() {
    return "Hello from service!";
  }
}
```

Use it in your component:

```ts
constructor(private dataService: DataService) {}

message = this.dataService.getMessage();
```

***

## 10. Routing (Basic)

Generate a new component:

```bash
ng g c home
ng g c about
```

Edit `app.routes.ts` (or `app-routing.module.ts`):

```ts
import { Routes } from '@angular/router';

export const routes: Routes = [
  { path: '', component: HomeComponent },
  { path: 'about', component: AboutComponent }
];
```

Add navigation:

```html
<a routerLink="/">Home</a>
<a routerLink="/about">About</a>

<router-outlet></router-outlet>
```

***

## 11. Build for Production

```bash
ng build
```

Output goes to:

```
dist/
```

***

## 12. Most Useful CLI Commands

```bash
ng new app-name         # create project
ng serve               # run dev server
ng build               # build project
ng g c component-name  # generate component
ng g s service-name    # generate service
ng g m module-name     # generate module
ng test                # run tests
```

***

# 🧠 Mini Practice Project

Build this small app:

* Component: `task-list`

* Add tasks

* Display tasks

* Delete tasks

This will teach you:

* Data binding

* Event handling

* Component structure

***

# ⚡ Pro Tips

* Use `ng g` instead of manually creating files

* Keep components small

* Use services for logic (not components)

* Learn **RxJS** next (important for Angular)

***

# 👉 Want Next Step?

If you want, I can give you:

* 🗓️ **1-week Angular CLI bootcamp**

* 🧠 **Angular CLI + RxJS combined training**

* 🔥 **Real-world project (Todo App with persistence)**

Just tell me 👍

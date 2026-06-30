---
id: 20260423132715
title: Week Four Angular Bootcamp
author: Karl Schmitt
date: 2026-04-23
keywords: [ Angular ]
---

# Week Four Angular Bootcamp

Now you’re stepping into **real Angular territory**.\
Week 4 is where apps stop being “UI demos” and start behaving like **real applications with data and logic layers**.

***

# 🅰️ Week 4 — Services, Dependency Injection & HTTP

## 🎯 Goal of Week 4

By the end, you will:

* Understand **services** (the backbone of Angular apps)

* Use **Dependency Injection (DI)**

* Fetch data from APIs using `HttpClient`

* Structure logic outside components (clean architecture)

***

# 🗓️ Day 1 — What is a Service?

## 🧠 Concept

A service =\
👉 A class that holds **logic, data, or shared state**

Components should NOT do everything.

***

## Create a service

```bash
ng generate service user
```

***

## Example

```ts
export class UserService {
  getUsers() {
    return ['Alice', 'Bob', 'Charlie'];
  }
}
```

***

## Use in a component

```ts
constructor(private userService: UserService) {}

ngOnInit() {
  const users = this.userService.getUsers();
}
```

***

## 🧪 Exercise

* Create `CounterService`

* Move counter logic into service

👉 Component should only display data

***

# 🗓️ Day 2 — Dependency Injection (DI)

## 🧠 Concept (IMPORTANT 🔥)

Angular **injects** services automatically.

You don’t do:

```ts
const service = new UserService(); ❌
```

You do:

```ts
constructor(private userService: UserService) {}
```

***

## Why DI?

* Reusable

* Testable

* Centralized logic

***

## 🧪 Exercise

* Inject your `CounterService`

* Share one counter between multiple components

👉 You should see **shared state**

***

# 🗓️ Day 3 — HTTP Requests

Angular uses `HttpClient`.

***

## Setup

In modern Angular (standalone style):

```ts
import { provideHttpClient } from '@angular/common/http';

bootstrapApplication(AppComponent, {
  providers: [provideHttpClient()]
});
```

***

## Service example

```ts
import { HttpClient } from '@angular/common/http';

constructor(private http: HttpClient) {}

getUsers() {
  return this.http.get('https://jsonplaceholder.typicode.com/users');
}
```

***

## 🧪 Exercise

* Fetch users from:

```
https://jsonplaceholder.typicode.com/users
```

* Log result in console

***

# 🗓️ Day 4 — Observables & Async Data

Angular uses RxJS.

***

## 🧠 Concept

HTTP returns an **Observable**, not data directly.

***

## Subscribe

```ts
this.userService.getUsers().subscribe(data => {
  this.users = data;
});
```

***

## Async pipe (better way)

```html
<ul>
  <li *ngFor="let user of users$ | async">
    {{ user.name }}
  </li>
</ul>
```

***

## 🧪 Exercise

* Create `users$`

* Use async pipe instead of manual subscribe

***

# 🗓️ Day 5 — Clean Architecture

## 🧠 Rule

👉 Components = UI\
👉 Services = logic + data

***

## Bad ❌

```ts
ngOnInit() {
  fetch('api...');
}
```

## Good ✅

```ts
ngOnInit() {
  this.userService.getUsers();
}
```

***

## 🧪 Exercise

Refactor:

* Move all API logic into service

* Keep component clean

***

# 🗓️ Day 6 — Error Handling

## 🧠 Concept

APIs fail → your app must not crash.

***

## Example

```ts
this.http.get(url).subscribe({
  next: data => this.users = data,
  error: err => console.error('Error:', err)
});
```

***

## 🧪 Exercise

* Show message in UI:

```html
<p *ngIf="error">Failed to load users</p>
```

***

# 🗓️ Day 7 — Mini Project 🚀

## 🎯 Build: User Dashboard App

***

## Features:

### Pages:

* Users list

* User detail (reuse routing from Week 3)

***

## Requirements:

✅ Fetch users from API\
✅ Display list\
✅ Click → navigate to detail\
✅ Use service for data\
✅ Handle errors

***

## Bonus:

* Show loading indicator:

```html
<p *ngIf="loading">Loading...</p>
```

***

# 🧠 What You Learned

* Services

* Dependency Injection

* HTTP requests

* Observables (basic)

* Clean

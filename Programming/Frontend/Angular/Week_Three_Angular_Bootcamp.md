---
id: 20260423132008
title: Week Three Angular Bootcamp
author: Karl Schmitt
date: 2026-04-23
keywords: []
---

# Week Three Angular Bootcamp

Now it gets interesting—**Week 3 is where your Angular app stops being a “single page toy” and becomes a real application with navigation.**

You’ll learn how to move between views, structure pages, and use URLs like a pro.

***

# 🅰️ Week 3 — Routing & Navigation

## 🎯 Goal of Week 3

By the end, you will:

* Build **multi-page Angular apps**

* Use the Angular Router

* Navigate programmatically

* Work with URL parameters

***

# 🗓️ Day 1 — What is Routing?

## 🧠 Concept

Angular doesn’t reload pages like traditional websites.\
Instead, it swaps components based on the URL.

👉 `/home` → HomeComponent\
👉 `/about` → AboutComponent

This is handled by the **Angular Router**.

***

## 🧪 Setup Routing

When creating a project:

```bash
ng new angular-routing --routing
```

Or add manually:

```bash
ng generate module app-routing --flat --module=app
```

***

## Example Routes

```ts
const routes: Routes = [
  { path: '', component: HomeComponent },
  { path: 'about', component: AboutComponent }
];
```

***

# 🗓️ Day 2 — Router Outlet & Links

## 🧠 Core Pieces

### Router outlet

```html
<router-outlet></router-outlet>
```

👉 This is where components get rendered.

***

### Navigation links

```html
<a routerLink="/">Home</a>
<a routerLink="/about">About</a>
```

***

## 🧪 Exercise

Create components:

```bash
ng generate component home
ng generate component about
```

Add navigation menu:

```html
<nav>
  <a routerLink="/">Home</a>
  <a routerLink="/about">About</a>
</nav>

<router-outlet></router-outlet>
```

***

# 🗓️ Day 3 — Programmatic Navigation

## 🧠 Concept

Navigate via code instead of clicking links.

***

## Example

```ts
import { Router } from '@angular/router';

constructor(private router: Router) {}

goToAbout() {
  this.router.navigate(['/about']);
}
```

***

## 🧪 Exercise

* Add button:

```html
<button (click)="goToAbout()">Go to About</button>
```

***

# 🗓️ Day 4 — Route Parameters 🔥

## 🧠 Concept

Dynamic URLs:

```id="qb9q6s"
/users/1
/users/2
```

***

## Define route

```ts
{ path: 'user/:id', component: UserComponent }
```

***

## Read parameter

```ts
import { ActivatedRoute } from '@angular/router';

constructor(private route: ActivatedRoute) {}

ngOnInit() {
  const id = this.route.snapshot.paramMap.get('id');
}
```

***

## 🧪 Exercise

* Create:

```bash
ng generate component user
```

* Navigate:

```html
<a [routerLink]="['/user', 1]">User 1</a>
<a [routerLink]="['/user', 2]">User 2</a>
```

* Display ID in component

***

# 🗓️ Day 5 — Nested Routes

## 🧠 Concept

Routes inside routes (layouts)

***

## Example

```ts
{
  path: 'dashboard',
  component: DashboardComponent,
  children: [
    { path: 'stats', component: StatsComponent },
    { path: 'settings', component: SettingsComponent }
  ]
}
```

***

## 🧪 Exercise

* Create:

```bash
ng generate component dashboard
ng generate component stats
ng generate component settings
```

* Add nested `<router-outlet>` inside dashboard

***

# 🗓️ Day 6 — 404 Page & Redirects

## 🧠 Concept

Handle unknown routes.

***

## Example

```ts
{ path: '**', component: NotFoundComponent }
```

Redirect:

```ts
{ path: '', redirectTo: '/home', pathMatch: 'full' }
```

***

## 🧪 Exercise

* Create:

```bash
ng generate component not-found
```

* Show message:

```html
<h1>404 - Page not found</h1>
```

***

# 🗓️ Day 7 — Mini Project 🚀

## 🎯 Build: Multi-Page App

### Pages:

* Home

* About

* Users

* User Detail

* 404 Page

***

## Features:

✅ Navigation bar\
✅ Dynamic user routes\
✅ Button navigation\
✅ Nested dashboard (optional)

***

## Example Structure

```id="b76s2k"
/home
/about
/users
/user/1
/dashboard/stats
```

***

# 🧠 What You Learned

* Angular Router

* Navigation (link + programmatic)

* Route parameters

* Nested routes

* 404 handling

***

# ⚠️ Common Mistakes

* Forgetting `<router-outlet>`

* Wrong route order (`**` must be last!)

* Using `href` instead of `routerLink` ❌

***

# 🔁 Practice Loop

Try:

* Add new route without tutorial

* Break navigation on purpose

* Fix route config

***

# ⏭️ Next Week (Important 🚀)

Week 4 unlocks:

* **Services**

* **Dependency Injection**

* **HTTP APIs**

👉 This is where Angular becomes a _real-world app framework_

***

If you’re ready:

👉 **“Week 4 Angular Bootcamp”**

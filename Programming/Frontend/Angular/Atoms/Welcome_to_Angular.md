---
id: 20260425181233
title: Welcome to Angular
author: Karl Schmitt
date: 2026-04-25
---

# Welcome to Angular

Angular is a robust, production-grade web framework by Google. It's designed for building single-page applications (SPAs) that are scalable, maintainable, and highly performant.

Unlike "libraries" that focus on one thing, Angular is a full-blown framework. It gives you everything out of the box: routing, state management, form validation, and HTTP client.

## Key Features
- **Modular**: Organize your app into logical units.
- **Reactive**: Built-in support for RxJS and asynchronous data flows.
- **Performant**: Optimized change detection and AOT compilation.

## Key Concepts
- TypeScript-first development
- Declarative templates
- Dependency Injection (DI)
- Standalone Components (Modern Angular)
# Angular Components

Components are the fundamental building blocks of an Angular application. Each component consists of a TypeScript class, an HTML template, and CSS styles.

```ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-hello',
  standalone: true,
  template: `
    <h1>Hello {{ name }}!</h1>
    <button (click)="tapped()">Click me</button>
  `,
  styles: [`
    h1 { color: #dd0031; }
  `]
})
export class HelloComponent {
  name = 'Developer';

  tapped() {
    alert('Hello from Angular!');
  }
}
```

## Data Binding
- **Interpolation**: `{{ value }}` - Displaying data in the template.
- **Property Binding**: `[property]="value"` - Passing data to attributes.
- **Event Binding**: `(event)="handler()"` - Handling user interactions.

# Angular Signals

Signals are the most significant addition to Angular in years. They provide a granular way to track state changes, leading to better performance and simpler code.

```ts
import { Component, signal, computed } from '@angular/core';

@Component({ ... })
export class CounterComponent {
  count = signal(0);
  doubleCount = computed(() => this.count() * 2);

  increment() {
    this.count.update(v => v + 1);
  }
}
```

## Why Signals?
1. **Fine-grained reactivity**: Angular knows exactly which part of the UI needs to update.
2. **Simpler async**: Easier to handle state compared to RxJS in simple cases.
3. **No Zone.js**: Signals are the key to building "Zoneless" apps.

# Angular Routing

The router enables navigation by interpreting browser URLs as instructions to change the views.

```ts
const routes: Routes = [
  { path: 'home', component: HomeComponent },
  { path: 'users/:id', component: UserDetailComponent },
  { path: '**', redirectTo: 'home' }
];
```

## Navigation
Use the `routerLink` directive in templates:

```html
<nav>
  <a routerLink="/home" routerLinkActive="active">Home</a>
  <a [routerLink]="['/users', userId]">Profile</a>
</nav>
<router-outlet></router-outlet>

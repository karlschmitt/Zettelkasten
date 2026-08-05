---
id: 20260804124723
title: Standalone Component
author: Karl Schmiit
date: 2026-08-04
keywords: [Angular, Standalone Compnent]
---

In Angular, a **Standalone Component** is a type of component that does not require being declared in an `@NgModule`. 

Introduced in Angular 14 (and becoming the default in Angular 17+), standalone components simplify the way you build applications by reducing boilerplate code and making components more self-contained.

---

### 1. The Core Difference

*   **Traditional Way:** You had to create a component, then "declare" it in an `NgModule` (like `AppModule`). If that component needed to use `NgIf` or another component, you had to import those dependencies into the Module.
*   **Standalone Way:** The component manages its own dependencies directly within its own metadata.

### 2. What it looks like
To make a component standalone, you set the `standalone: true` flag and add an `imports` array directly into the `@Component` decorator.

```typescript
import { Component } from '@angular/core';
import { CommonModule } from '@angular/common'; // Import tools like NgIf/NgFor
import { UserProfileComponent } from './user-profile.component'; // Import other components

@Component({
  selector: 'app-root',
  standalone: true,             // 1. Mark as standalone
  imports: [                    // 2. Import dependencies directly here
    CommonModule, 
    UserProfileComponent
  ],
  template: `
    <h1 *ngIf="isLoggedIn">Welcome!</h1>
    <app-user-profile></app-user-profile>
  `
})
export class AppComponent {
  isLoggedIn = true;
}
```

### 3. Key Benefits

1.  **Reduced Boilerplate:** You no longer need to manage complex `AppModule` files that grow to hundreds of lines.
2.  **Easier Learning Curve:** Beginners don't have to understand the complex "Module" system immediately; they can just focus on components.
3.  **Better Tree Shaking:** Because dependencies are explicitly linked to the components that use them, build tools can more easily remove unused code, leading to smaller bundle sizes.
4.  **Simplified Testing:** You can test a component in isolation without having to mock or configure a large parent module.
5.  **Lazy Loading:** You can now lazy-load a single component via the router, rather than having to lazy-load an entire module.

### 4. Bootstrapping the Application
In a traditional app, you bootstrap an `NgModule`. In a standalone app, you bootstrap the **Component** directly in your `main.ts` file:

```typescript
// main.ts
import { bootstrapApplication } from '@angular/platform-browser';
import { AppComponent } from './app/app.component';
import { provideRouter } from '@angular/router';
import { routes } from './app/app.routes';

bootstrapApplication(AppComponent, {
  providers: [
    provideRouter(routes) // Provide global services/configs here
  ]
}).catch(err => console.error(err));
```

### 5. Can I use them with existing Modules?
**Yes.** Standalone components are designed to be "interoperable."
*   You can import a Standalone Component into an existing `NgModule`.
*   You can import an existing `NgModule` into a Standalone Component's `imports` array.

### Summary
Standalone components are the **modern standard** for Angular development. They make the framework feel more lightweight, modular, and similar to other modern libraries like React or Vue, while still keeping the powerful features of Angular.
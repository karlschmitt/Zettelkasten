---
id: 20260428122804
title: Standalone Components
author: Karl Schmitt
date: 2026-04-28
keywords: [ Angula, Standalone Components ]
---

# Standalone Components

**Standalone Components** are a feature introduced in Angular v14 (and made the default in v17) that allows you to build components, directives, and pipes without having to declare them in an `NgModule`.

They represent the biggest shift in how Angular applications are structured since the framework's inception.

---

### 1. The "Old Way" vs. Standalone
To understand Standalone Components, you have to remember how `NgModules` worked:

*   **The Old Way (NgModule):** Every component had to belong to a "bucket" (a Module). If `Component A` wanted to use `Component B`, you had to make sure both were in the same module, or that `Component B` was exported from its module and imported into `Component A`’s module. This created a lot of "boilerplate" code and made the architecture hard to follow.
*   **The Standalone Way:** A component is its own "island." It explicitly lists exactly what it needs (other components, directives, or modules) inside its own metadata.

### 2. What a Standalone Component looks like
You create one by setting the `standalone: true` flag in the `@Component` decorator. You then use the `imports` array to bring in dependencies directly.

```typescript
import { Component } from '@angular/core';
import { CommonModule } from '@angular/common'; // For *ngIf, *ngFor
import { SharedButtonComponent } from './shared-button.component';

@Component({
  selector: 'app-user-profile',
  standalone: true, // <--- This is the key!
  imports: [CommonModule, SharedButtonComponent], // List dependencies here
  template: `
    <div *ngIf="isLoggedIn">
      <h1>Welcome Back!</h1>
      <app-shared-button></app-shared-button>
    </div>
  `
})
export class UserProfileComponent {
  isLoggedIn = true;
}
```

### 3. Key Benefits

#### A. Reduced Boilerplate
You no longer need to maintain massive `app.module.ts` files or "SharedModules." This makes the codebase significantly smaller and easier to read.

#### B. Easier Learning Curve
New developers often found `NgModules` confusing. With Standalone Components, Angular works more like standard JavaScript/TypeScript: if you need something, you `import` it.

#### C. Better Tree-Shaking
Because dependencies are explicitly linked to the components that use them, build tools (like Vite/esbuild) can more easily identify and remove code that isn't being used. This results in smaller bundle sizes.

#### D. Simplified Lazy Loading
Previously, to "lazy load" a route (loading code only when the user visits a page), you had to create a separate Module and use `loadChildren`. Now, you can lazy load a **single component** directly in your router config:

```typescript
// Inside your routes file
export const ROUTES: Route[] = [
  {
    path: 'admin',
    loadComponent: () => import('./admin/admin.component').then(m => m.AdminComponent)
  },
];
```

### 4. How does the App start? (Bootstrapping)
In a Standalone-based app, you don't bootstrap a `Module`. Instead, you bootstrap the root **Component** in your `main.ts` file:

```typescript
import { bootstrapApplication } from '@angular/platform-browser';
import { AppComponent } from './app/app.component';
import { provideRouter } from '@angular/router';
import { routes } from './app/app.routes';

bootstrapApplication(AppComponent, {
  providers: [
    provideRouter(routes) // Provide services/configs globally here
  ]
});
```

### 5. Can I still use Modules?
**Yes.** Angular has perfect "interop" (interoperability).
*   You can import an **NgModule** into a **Standalone Component**.
*   You can import a **Standalone Component** into an **NgModule**.

This allows teams to migrate large, old applications to the Standalone style gradually, one component at a time.

### Summary
Standalone Components make Angular **modular by default** rather than **modular by configuration**. They are the foundation of the "Renaissance," enabling faster builds, simpler code, and a more modern developer experience.
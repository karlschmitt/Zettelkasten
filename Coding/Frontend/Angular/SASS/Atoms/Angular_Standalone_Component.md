---
id: 20260502203730
title: Angular Standalone Component
author: Karl Schmitt
date: 2026-05-02
keywords: [Angular, SASS, SCSS, standalone Component ]
---

# Angular Standalone Component

In Angular (starting from version 14/15), a **Standalone Component** is a component that does **not** need to be declared in an `NgModule`. 

Before this feature, every component had to belong to a "box" (an `@NgModule`) to work. Now, components can be self-contained units.

---

### 1. The Key Difference: Then vs. Now

#### Traditional Way (With NgModules)
To use a component, you had to:
1. Create `HeaderComponent`.
2. Add it to the `declarations` array of `AppModule`.
3. If you wanted to use `CommonModule` (for `*ngIf`) or `FormsModule`, you had to import them into the `AppModule`.

#### Standalone Way
The component manages its own dependencies:
1. Create `HeaderComponent`.
2. Set `standalone: true`.
3. Directly `import` the specific tools it needs (like `CommonModule` or other components) right inside the `@Component` decorator.

---

### 2. What does it look like?

Here is a basic standalone component using **SCSS**:

```typescript
import { Component } from '@angular/core';
import { CommonModule } from '@angular/common'; // Direct import of dependencies

@Component({
  selector: 'app-user-card',
  standalone: true,           // This is the magic flag
  imports: [CommonModule],    // Tell the component what it needs
  templateUrl: './user-card.component.html',
  styleUrl: './user-card.component.scss' // Standard SASS integration
})
export class UserCardComponent {
  isLoggedIn = true;
}
```

---

### 3. Why are Standalone Components useful?

1.  **Reduced Boilerplate:** You no longer have to jump back and forth between your component file and an `app.module.ts` file just to get something to work.
2.  **Easier Learning Curve:** For developers coming from React or Vue, the concept of "Modules" was often confusing. Standalone components make Angular feel more modern and straightforward.
3.  **Better Tree-Shaking:** Because dependencies are explicitly imported at the component level, build tools can more easily remove unused code, leading to smaller bundle sizes.
4.  **Simplified Lazy Loading:** You can lazy-load a single component directly in your router without needing to create a separate "Routing Module."

---

### 4. How does SASS fit into Standalone Components?

The relationship between SASS and Standalone Components remains the same as with traditional components, but with a few organizational benefits:

*   **Encapsulation:** Just like traditional components, Standalone components use **View Encapsulation**. This means the SASS you write for `user-card.component.scss` will only ever affect that specific component.
*   **Modular Styling:** Since the component is "standalone" and self-contained, it encourages you to write highly modular SASS. You can keep your component styles tightly coupled with the logic.
*   **Global SASS in Standalone Apps:** Even in an app without `NgModules`, you still use a global `styles.scss` for variables, mixins, and resets. Your standalone components can still `@use` or `@import` those global SASS files.

### 5. Do you still need NgModules?
In modern Angular (v17+), **Standalone is the default.** When you run `ng generate component my-comp`, it will be standalone by default. 

You only need `NgModules` if:
*   You are maintaining an older "Legacy" project.
*   You are using certain third-party libraries that haven't updated to the standalone pattern yet.

### Summary
A Standalone Component is a **self-reliant** piece of UI. It simplifies Angular development by removing the requirement for `NgModules`, making the code easier to read, test, and reuse, while still fully supporting **SASS** for powerful, scoped styling.
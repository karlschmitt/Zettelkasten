---
id: 20260428123550
title: The new renaissance Control Flow
author: Karl Schmitt
date: 2026-04-28
---

# The new renaissance Control Flow


The **"New Control Flow"** was the headline feature introduced in **Angular 17** and refined in **v18 and v19**. It is the most significant change to Angular templates in a decade.

Here is everything you need to know about the new block-based control flow:

---

### 1. What is it?
The new control flow replaces the old "structural directives" (`*ngIf`, `*ngFor`, and `*ngSwitch`) with a new **built-in syntax** that looks like JavaScript/TypeScript. It uses the `@` symbol.

### 2. Comparison: Old vs. New

#### **Conditional Logic (`@if`)**
*   **Old:** Requires a container like `<div>` or `<ng-container>`.
    ```html
    <div *ngIf="isLoggedIn; else loggedOut">
      Welcome back!
    </div>
    <ng-template #loggedOut>
      Please sign in.
    </ng-template>
    ```
*   **New:** Direct and readable.
    ```html
    @if (isLoggedIn) {
      Welcome back!
    } @else {
      Please sign in.
    }
    ```

#### **Loops (`@for`)**
The new loop syntax is significantly faster and more powerful.
*   **Old:**
    ```html
    <li *ngFor="let user of users; trackBy: trackById">
      {{ user.name }}
    </li>
    ```
*   **New:**
    ```html
    @for (user of users; track user.id) {
      <li>{{ user.name }}</li>
    } @empty {
      <li>No users found.</li>
    }
    ```
    *   **Crucial Change:** The `track` property is now **mandatory**. This forces developers to write performant code, as tracking by ID allows Angular to update only the specific item that changed rather than re-rendering the whole list.
    *   **The `@empty` block:** This is a new feature that automatically displays content if the list is empty, removing the need for a separate `*ngIf`.

#### **Switch Cases (`@switch`)**
*   **Old:** Verbose and required `ngSwitchCase` / `ngSwitchDefault`.
*   **New:**
    ```html
    @switch (userRole) {
      @case ('admin') { <app-admin-panel /> }
      @case ('editor') { <app-editor-panel /> }
      @default { <app-viewer-panel /> }
    }
    ```

---

### 3. Why did Angular make this change?

#### **A. Significant Performance Boost**
Because this syntax is built directly into the Angular compiler (rather than being a directive), the framework doesn't have to do as much work at runtime. Initial benchmarks showed that the new `@for` loop can be **up to 90% faster** than `*ngFor`.

#### **B. Better Type Checking**
The new syntax has better integration with the TypeScript compiler, meaning you get better error messages and more accurate type checking within your templates.

#### **C. No Imports Required**
Previously, to use `*ngIf` or `*ngFor` in a Standalone Component, you had to import the `CommonModule`. The new control flow is **built-in**, so you don't need to import anything to use it.

#### **D. Cleaner Syntax (No "Uncanny Valley")**

Developers often hated having to create "fake" `<ng-container>` tags just to hold an `*ngIf`. The new syntax eliminates this extra HTML "noise."

---

### 4. How to Migrate?

If you have an existing project, you don't have to rewrite everything by hand. Angular provides an automated migration tool. You can run:

```bash
ng generate @angular/core:control-flow
```

This command will scan your entire project and automatically convert all `*ngIf`, `*ngFor`, and `*ngSwitch` directives to the new `@` syntax.

### Summary
The new control flow is a key part of the **Angular Renaissance**. It makes the framework feel modern, significantly improves rendering performance, and makes the code much more pleasant to read and write. Even if you are looking toward **Angular 21**, this `@` syntax is now the permanent standard for the framework.

---
id: 20260429111049
title: Angular NgModule
author: Karl Schmitt
date: 2026-04-29
keywords: [ Angular, NgModule]
---

# Angular NgModule

In Angular, an **NgModule** is a class decorated with the `@NgModule` decorator that serves as a **container** for a cohesive block of code. It organizes related components, directives, pipes, and services into functional units.

Think of an NgModule as a **"box"** or a **"manifest"** that tells Angular how to compile a specific part of your application and which pieces of code belong together.

---

### 1. The 5 Key Properties of `@NgModule`
The decorator takes a metadata object that defines the module's behavior. Here are the most important fields:

*   **`declarations`**: Used to register **Components, Directives, and Pipes** that belong to this module. (Important: A component can only belong to *one* NgModule).
*   **`imports`**: Used to import functionality from **other NgModules** (e.g., `CommonModule` for `*ngIf`, or `ReactiveFormsModule`).
*   **`exports`**: Defines the "public API." Any component or directive listed here can be used by *other* modules that import this one.
*   **`providers`**: Used to register **Services**. These services become available to the injectors of the components in this module (and often the whole app).
*   **`bootstrap`**: Only used in the **Root Module** (`AppModule`). It identifies the main component Angular should load first when the app starts.

---

### 2. Types of NgModules
Angular apps are usually organized into different types of modules:

1.  **The Root Module (`AppModule`)**: Every traditional Angular app has at least one. It provides the "entry point" for the application.
2.  **Feature Modules**: These group code related to a specific feature (e.g., `UserModule`, `AdminModule`). This helps with **Lazy Loading**, which allows Angular to download code only when the user navigates to that specific route, making the app faster.
3.  **Shared Modules**: Contains components (like buttons or spinners) used throughout the entire application.

---

### 3. Why do we use them?
*   **Organization:** They help manage large codebases by breaking them into logical chunks.
*   **Compilation Context:** They tell the Angular compiler which components can see which other components (e.g., "Can Component A use the directive from Component B?").
*   **Lazy Loading:** They are the mechanism used to split code into bundles that load on demand.
*   **Dependency Injection:** They help manage the lifecycle of services.

---

### 4. Basic Example
```typescript
import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { UserComponent } from './user.component';
import { UserService } from './user.service';

@NgModule({
  declarations: [ UserComponent ], // My components
  imports:      [ CommonModule ],  // Modules I need
  providers:    [ UserService ],   // My services
  exports:      [ UserComponent ]  // What I let others use
})
export class UserModule { }
```

---

### 5. Important Note: Standalone Components
Since Angular 14/15, there is a new way to build apps called **Standalone Components**. 

*   **Before:** Every component *had* to belong to an NgModule.
*   **Now:** Components can be marked as `standalone: true`. They manage their own dependencies, effectively making NgModules **optional** for most modern Angular development.

**Summary:** While NgModules were once the only way to organize Angular apps, they are now becoming secondary to Standalone Components. However, you will still encounter them in many existing projects and libraries.
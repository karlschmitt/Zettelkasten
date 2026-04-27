---
id: 20260426124446
title: Angular Project Structure
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, Project, Structure ]
---

# Angular Project Structure

**Clarifying Project Structure**

I'm now focusing on the Angular project's structure, aiming for a beginner-friendly overview. I'm starting with the root directory and envision explaining how the various configuration files and initial setup are used. The goal is a clear, step-by-step guide to help new users understand the organization of a basic Angular project and its different components.


**Outlining Project Organization**

I'm now zeroing in on detailing the directory structure. I have a clearer outline now, covering the `src/`, `app/`, `assets/`, and `environments/` folders, and considering modern standalone components versus traditional NgModule approaches. Also included is a more granular dive into root-level config files like `angular.json` and `tsconfig.json`. I'm starting to think about best practices and how to present the information visually, perhaps with a file tree.


A standard Angular project follows a specific convention to ensure scalability and maintainability. Since **Angular 17+**, the structure has shifted slightly to favor **Standalone Components** over the older `NgModule` system.

Here is a breakdown of a modern Angular project structure.

---

### 1. High-Level Tree View
```text
my-angular-app/
├── .angular/              # Internal Angular cache
├── .vscode/               # VS Code specific settings
├── node_modules/          # Downloaded library dependencies
├── public/                # Static assets (images, icons, robots.txt)
├── src/                   # The heart of the application
│   ├── app/               # Logic, components, services
│   ├── assets/            # (Legacy/Common) Static files
│   ├── index.html         # Main HTML host file
│   ├── main.ts            # Entry point of the app
│   └── styles.scss        # Global styles
├── angular.json           # Angular CLI configuration
├── package.json           # Scripts and dependencies
├── tsconfig.json          # TypeScript configuration
└── .editorconfig          # Coding style consistency rules
```

---

### 2. The `src/app/` Folder (Where you code)
In modern Angular, we typically organize this folder by **feature** or **type**.

```text
app/
├── core/                  # Singleton services, interceptors, guards
│   ├── services/
│   └── auth.guard.ts
├── shared/                # Reusable components, pipes, directives
│   ├── components/
│   │   └── button/
│   └── pipes/
├── features/              # Business logic modules/pages
│   ├── user-profile/
│   │   ├── user-profile.component.ts
│   │   ├── user-profile.component.html
│   │   └── user-profile.component.css
│   └── dashboard/
├── app.component.ts       # The "Root" component
├── app.config.ts          # Global app configuration (Providers, Routes)
└── app.routes.ts          # Centralized routing table
```

---

### 3. Key File Descriptions

#### **Project Configuration**
*   **`angular.json`**: The most important config file. It defines how the app is built, where the assets are, and which styles/scripts to include globally.
*   **`package.json`**: Lists the npm packages your project depends on and defines terminal scripts (e.g., `npm start`, `npm build`).
*   **`tsconfig.json`**: Configuration for the TypeScript compiler (strictness, path aliases, etc.).

#### **The `src/` Directory**
*   **`main.ts`**: The starting point. It "bootstraps" (starts) the Angular application.
*   **`index.html`**: The single page of your Single Page Application (SPA). You’ll see `<app-root></app-root>` in the body; Angular injects your app there.
*   **`styles.scss`**: Global CSS rules that apply to the entire application.

#### **The `app/` Directory**
*   **`app.config.ts`**: (Modern Angular) This is where you configure things like `provideHttpClient()` or `provideRouter()`.
*   **`app.routes.ts`**: Defines the URL paths and which components they map to.
*   **`app.component.ts`**: The main container for your app. Every other component sits inside this one.

---

### 4. Component Structure
Every component usually consists of four files:

1.  **`.ts`**: The logic (TypeScript class).
2.  **`.html`**: The structure (Template).
3.  **`.css` / `.scss`**: The styling (Scoped only to this component).
4.  **`.spec.ts`**: The unit tests for the component.

---

### 5. Recommended Best Practice: The Feature-Based Folders
Instead of putting all components in one folder and all services in another, group them by **feature**:

*   **`core/`**: Stuff you only need once (Navbar, Footer, Auth Service, Error Interceptor).
*   **`shared/`**: UI pieces used everywhere (Loading spinners, custom buttons, date format pipes).
*   **`features/`**: The actual "pages" of your app (Login, Product List, Checkout).

### 6. Modern (v17+) vs. Legacy Structure
| Feature | Modern (Standard) | Legacy (Before v17) |
| :--- | :--- | :--- |
| **Organization** | Standalone Components | `AppModule` (`app.module.ts`) |
| **Bootstrapping** | `bootstrapApplication(AppComponent)` | `platformBrowserDynamic().bootstrapModule(AppModule)` |
| **Config** | `app.config.ts` | Inside `@NgModule` providers |
| **Static Assets** | `public/` folder | `src/assets/` folder |

**Note:** If you are working on an older project, you will likely see an `app.module.ts` file. In modern projects, that file is gone, and components manage their own dependencies.
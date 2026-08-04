---
id: 20260803133358
tile: Create an Agular Project
author: Karl Schmitt
date: 2026-08-03
keywords: [Angular, Project]
---

# Create an Angular Project

As of late 2024 and early 2025 (Angular 18/19), the "modern way" to build Angular apps has shifted significantly. The framework is now faster, lighter, and much more functional.

Here is the step-by-step guide to creating a modern Angular project.

---

### 1. Prerequisites
Ensure you have the latest **Node.js (LTS)** version installed. Then, install the latest Angular CLI globally:

```bash
npm install -g @angular/cli
```

### 2. Create the Project
Run the following command to start the interactive setup:

```bash
ng new my-modern-app
```

**Choose these modern defaults when prompted:**
*   **Styles:** SCSS (or CSS if you prefer simplicity).
*   **Server-Side Rendering (SSR):** **Yes.** (Modern Angular defaults to SSR for better SEO and performance using the new "Hydration" engine).

---

### 3. What Makes it "Modern"?
If you haven't used Angular in a year or two, you will notice several major changes in a new project:

#### A. Standalone Components (No `app.module.ts`)
The modern way is **Module-less**. You will no longer find an `NgModule`. Everything is a standalone component.
*   Components, Directives, and Pipes now import their dependencies directly.
*   **Result:** Smaller bundles and easier-to-trace code.

#### B. The `app.config.ts` File
Instead of a root module, global configuration (Providers, Routing, Animations, Client Hydration) happens in `src/app/app.config.ts`:

```typescript
export const appConfig: ApplicationConfig = {
  providers: [
    provideRouter(routes),
    provideClientHydration(), // Enables modern non-destructive hydration
    provideHttpClient(withFetch()), // Uses the modern Fetch API
  ]
};
```

#### C. The New Application Builder
Angular now uses a **Vite-based** dev server and **esbuild** for production. It is significantly faster than the old Webpack-based system. This is automatically configured in `angular.json` under `"builder": "@angular-devkit/build-angular:application"`.

---

### 4. Essential Modern Features to Use

Once your project is created, ensure you are using these "Modern Angular" patterns:

#### 1. Signals (State Management)
Stop relying solely on `BehaviorSubject` for local state. Signals are the new way to handle reactivity.

```typescript
import { signal, computed } from '@angular/core';

export class AppComponent {
  count = signal(0); // A reactive value
  doubleCount = computed(() => this.count() * 2);

  increment() {
    this.count.update(v => v + 1);
  }
}
```

#### 2. New Control Flow
Forget `*ngIf` and `*ngFor`. Use the new built-in syntax for better performance and type safety:

```html
@if (isLoggedIn) {
  <p>Welcome back!</p>
} @else {
  <button>Log In</button>
}

@for (item of items; track item.id) {
  <li>{{ item.name }}</li>
} @empty {
  <p>No items found.</p>
}
```

#### 3. Deferrable Views (`@defer`)
This is perhaps the most powerful modern feature. You can lazy-load parts of a component template based on conditions (like when a component enters the viewport).

```html
@defer (on viewport) {
  <large-chart-component />
} @placeholder {
  <div>Loading chart...</div>
}
```

---

### 5. Recommended Modern Stack

To make your project truly professional in 2025, consider adding these:

1.  **Tailwind CSS:** Still the industry standard for styling.
    *   `npm install -D tailwindcss postcss autoprefixer && npx tailwindcss init`
2.  **Angular Query (TanStack):** For server state management (replacing manual Observable/Pipe logic for API calls).
3.  **Lucide Angular:** For lightweight, modern icons.
4.  **Prettier:** Use the `prettier-plugin-tailwindcss` and `prettier-plugin-organize-attributes` for clean code.

---

### Summary Checklist for a "Modern" App:
- [ ] **Angular 18/19+**
- [ ] **Standalone Components** (No `NgModule`)
- [ ] **Signals** for state
- [ ] **Built-in Control Flow** (`@if`, `@for`)
- [ ] **SSR & Hydration** enabled
- [ ] **Application Builder** (Vite/esbuild)
- [ ] **provideHttpClient(withFetch())** instead of the old XHR backend.
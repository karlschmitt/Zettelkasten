---
id: 20260426131653
title: Angular Project Structure Example
author: Karl Schmitt
date: 2026-04-26
keyboard: [ Angular, project, structure, example]
---

# Angular Project Structure Example

The Angular CLI doesn't have a single command to "create a folder structure," but it creates the structure **automatically** based on the paths you provide in the generation commands.

Here is the step-by-step workflow to build the recommended structure for a project named `my-app`.

---
>[!Note]
>[Installing the Angular CLI](./Atoms/Angular_CLI_Instalation.md)

### Phase 1: Create the Project
Run this command to start a new project with modern defaults (Standalone components, SCSS, and Routing).

```bash
ng new my-app --style=scss --routing --standalone
cd my-app
```

---

### Phase 2: Create the "Core" Layer
The **Core** folder is for services that should have only one instance (Singletons), like Authentication or API interceptors.

```bash
# Create a service inside core/services
ng generate service core/services/auth

# Create an interceptor
ng generate interceptor core/interceptors/error

# Create a guard
ng generate guard core/guards/auth
```

---

### Phase 3: Create the "Shared" Layer
The **Shared** folder is for reusable UI components (buttons, loaders) and pipes that will be used across multiple features.

```bash
# Create a reusable button component
ng generate component shared/components/button

# Create a custom pipe for formatting dates
ng generate pipe shared/pipes/custom-date
```

---

### Phase 4: Create the "Features" Layer
Features represent the actual pages or logic modules of your app.

```bash
# Create a Dashboard feature
ng generate component features/dashboard

# Create a User Profile feature
ng generate component features/user-profile

# Create a service specific only to the User Profile
ng generate service features/user-profile/user-data
```

---

### Phase 5: Organize the Routes
Now that you have created the components, you need to link them in `app.routes.ts`. The CLI created this file for you, but you should update it manually:

```typescript
// src/app/app.routes.ts
import { Routes } from '@angular/router';

export const routes: Routes = [
  { 
    path: 'dashboard', 
    loadComponent: () => import('./features/dashboard/dashboard.component').then(m => m.DashboardComponent) 
  },
  { 
    path: 'profile', 
    loadComponent: () => import('./features/user-profile/user-profile.component').then(m => m.UserProfileComponent) 
  },
  { path: '', redirectTo: '/dashboard', pathMatch: 'full' }
];
```

---

### CLI Pro-Tips & Shortcuts

#### 1. Use Shortcuts
You don't need to type the whole word.
*   `ng g c` = `ng generate component`
*   `ng g s` = `ng generate service`
*   `ng g g` = `ng generate guard`

#### 2. Dry Run
If you aren't sure where the files will end up, add `--dry-run` (or `-d`) to the end. It will show you the file tree without actually creating any files.
```bash
ng g c features/login -d
```

#### 3. Skip Tests
If you don't want the `.spec.ts` files created for every component:
```bash
ng g c features/login --skip-tests
```

#### 4. Flat Services
By default, components get their own folder, but services don't. If you want a service inside its own folder, you must specify it:
*   `ng g s core/services/auth` → creates `core/services/auth.service.ts`
*   If you want a folder: `ng g s core/services/auth/auth`

---

### Summary of what your `src/app` looks like now:
If you ran the commands above, your folder tree will look exactly like the "Best Practice" structure:
```text
app/
├── core/
│   ├── guards/
│   ├── interceptors/
│   └── services/
├── shared/
│   ├── components/
│   └── pipes/
├── features/
│   ├── dashboard/
│   └── user-profile/
├── app.component.ts
├── app.config.ts
└── app.routes.ts
```
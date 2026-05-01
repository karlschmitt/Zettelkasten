---
id: 20260501133241
title: Angular with SASS
author: Karl Schmitt
date: 2025-05-01
---


[Install Angular globally ...](./nstall_Angular_globallY.md) 🐇👩‍🏭🌐

# Angular with SASS

>[!Note]
> How can I create a Angular project using SASS with a standalone Component?

Since **Angular 17 and 18**, Standalone components are the default. To create a modern project that uses SCSS (the most common version of SASS) and Standalone components, follow these steps:

### 1. Create the Project
Open your terminal and run the following command:

```bash
ng new my-sass-project --style=scss --standalone
```

**Breakdown of the flags:**
*   `--style=scss`: Tells Angular to use SCSS. (If you prefer the indented SASS syntax, use `--style=sass` instead).
*   `--standalone`: Ensures the project starts without an `app.module.ts` file. (Note: In Angular 18+, this is the default, so you can often omit it).

### 2. Verify the Standalone Component
Once the project is created, open `src/app/app.component.ts`. You will see the `standalone: true` property in the decorator:

```typescript
import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';

@Component({
  selector: 'app-root',
  standalone: true, // This is the key
  imports: [RouterOutlet], // Standalone components import their dependencies directly
  templateUrl: './app.component.html',
  styleUrl: './app.component.scss' // Points to your SASS file
})
export class AppComponent {
  title = 'my-sass-project';
}
```

### 3. Using SASS/SCSS Features
In a standalone project, you have two places to use SASS:

#### Global Styles
Open `src/styles.scss`. You can define variables or mixins here that apply to the whole app:
```scss
$primary-color: #3498db;

body {
  background-color: #f4f4f4;
  font-family: sans-serif;
}
```

#### Component Styles
Open `src/app/app.component.scss`. These styles are **encapsulated** to this component only:
```scss
$text-color: #2c3e50;

h1 {
  color: $text-color;
  &:hover {
    color: lighten($text-color, 20%);
  }
}
```

### 4. Generating New Standalone Components
When you want to add a new component, use the CLI. Because you set up the project with SCSS, any new component will automatically generate a `.scss` file.

```bash
ng generate component components/my-new-component
```

By default (in modern Angular), this will create:
*   `my-new-component.component.ts` (with `standalone: true`)
*   `my-new-component.component.scss`
*   `my-new-component.component.html`

### 5. Running the Project
```bash
ng serve
```

### Pro Tip: Global SASS Variables
If you create a file for variables (e.g., `src/_variables.scss`), you can import it into any component's SCSS file to use them:

```scss
/* app.component.scss */
@use '../variables' as v;

.container {
  color: v.$primary-color;
}
```

### Troubleshooting
If you already have a project and want to **change** the default style format to SCSS later, run:
```bash
ng config schematics.@schematics/angular:component.style scss
```
And to ensure new components are always standalone by default:
```bash
ng config schematics.@schematics/angular:component.standalone true
```


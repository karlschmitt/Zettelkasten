---
id: 20260426175224
title: Angular Component Creation
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, component, creation, ng]
---

# Angular Component Creation

To create an Angular component, the most efficient and standard way is using the **Angular CLI**. This ensures that all necessary files are created and that the component is correctly configured for modern Standalone use.

### 1. The CLI Command
Open your terminal inside your project folder and run:

```bash
ng generate component component-name
```

**Pro Tip: Use the Shortcut**
Most developers use the shorthand version:
```bash
ng g c component-name
```

---

### 2. Creating a Component in a Specific Folder
If you follow the **Project Structure** we discussed earlier, you should generate components directly into their feature or shared folders:

```bash
# Create a component inside the 'features' folder
ng g c features/user-profile

# Create a reusable button inside 'shared'
ng g c shared/components/button
```

---

### 3. What happens when you run this?
The CLI creates four files and updates your project:

1.  **`name.component.ts`**: The TypeScript logic and metadata.
2.  **`name.component.html`**: The HTML template.
3.  **`name.component.scss`**: The scoped CSS/SCSS styles.
4.  **`name.component.spec.ts`**: The unit test file.

---

### 4. Anatomy of the Created Component
Since Angular 17, components are **Standalone** by default. This is what the `.ts` file looks like:

```typescript
import { Component } from '@angular/core';

@Component({
  selector: 'app-user-card',     // The HTML tag used to call this component
  standalone: true,              // No need for NgModules
  imports: [],                   // Add other components or modules used here
  templateUrl: './user-card.component.html',
  styleUrl: './user-card.component.scss'
})
export class UserCardComponent {
  // Your logic goes here
}
```

---

### 5. How to use your new Component
Once created, you can use your component in two steps:

#### Step 1: Import it
In the component where you want to use it (e.g., `app.component.ts`), add it to the `imports` array:

```typescript
import { UserCardComponent } from './features/user-card/user-card.component';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [UserCardComponent], // Import it here
  template: `<app-user-card></app-user-card>` // Use it here
})
export class AppComponent {}
```

#### Step 2: Place the Tag
Use the `selector` defined in your component (usually prefixed with `app-`) in the HTML:

```html
<!-- Inside app.component.html -->
<app-user-card></app-user-card>
```

---

### 6. Useful CLI Flags
When generating a component, you can customize the output:

*   **Skip the test file:** 
    `ng g c my-comp --skip-tests`
*   **Inline Template (No .html file):** 
    `ng g c my-comp -t`
*   **Inline Styles (No .css file):** 
    `ng g c my-comp -s`
*   **Dry Run (See what will happen without creating files):** 
    `ng g c my-comp -d`

---

### Summary
1.  **Generate:** `ng g c component-name`
2.  **Logic:** Edit `.ts`
3.  **UI:** Edit `.html` and `.scss`
4.  **Connect:** Add the component class to the `imports` array of the parent component.
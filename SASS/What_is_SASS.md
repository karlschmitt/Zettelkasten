---
id: 20260501112108
title: SASS start page
author: Karl Schmitt
date: 2026-05-01
keywerds: [ SASS ]
---

# The SASS start page

## What is SASS?

In the context of Angular, **SASS** (Syntactically Awesome Style Sheets) is a **CSS preprocessor**. 

Think of it as "CSS with superpowers." It allows you to use features that don't exist in standard CSS yet (or are easier to write in SASS), which then get compiled into regular CSS that the browser can understand.

Angular defaults to SASS (specifically the `.scss` syntax) because it makes managing styles in large, complex applications much easier.

[Feel free to try the tutorial](./SASS_tutorial.md). Just follow the white rabbit. 🐇 👩‍🎓

---

### Key Features of SASS

#### 1. [Variables](./Atoms/SASS_Variables.md)

In standard CSS, variables exist, but SASS variables are simpler to write and can be used for calculations.
*   **SASS:** `$primary-color: #3498db;`
*   **Usage:** `button { background: $primary-color; }`

#### 2. [Nesting](./Atoms/SASS_Nesting.md)

SASS lets you nest your CSS selectors in a way that follows the hierarchy of your HTML. 
This makes your code much cleaner and easier to read.

*   **Standard CSS:**
    ```css
    nav { background: white; }
    nav ul { list-style: none; }
    nav li { display: inline-block; }
    ```
*   **SASS ([SCSS](./Atoms/SCSS.md))**
    ```scss
    nav {
      background: white;
      ul {
        list-style: none;
        li {
          display: inline-block;
        }
      }
    }
    ```

#### 3. Mixins (Reusable Blocks)
Mixins are like functions for CSS. You can define a group of styles and reuse them throughout your app.
```scss
@mixin flex-center {
  display: flex;
  justify-content: center;
  align-items: center;
}

.header { @include flex-center; }
.footer { @include flex-center; }
```

#### 4. Partials and Imports
You can break your CSS into smaller, manageable files (e.g., `_variables.scss`, `_buttons.scss`) and import them into one main stylesheet. This keeps your Angular project organized.

---

### SASS vs. SCSS (The Angular Default)
You will notice that Angular uses the extension **`.scss`**. There are actually two syntaxes for SASS:
1.  **SASS (Indented):** Uses indentation instead of brackets and semicolons.
2.  **SCSS (Sassy CSS):** Uses brackets `{}` and semicolons `;`. **This is what Angular uses.** 
    *   *Fun fact:* Every valid CSS file is also a valid SCSS file.

---

### How Angular Handles SASS
When you build or run your Angular app (`ng serve` or `ng build`):

1.  **Writing:** You write your styles in `.scss` files inside your components.
2.  **Compiling:** The Angular CLI automatically runs a compiler (like `sass-loader`) in the background.
3.  **Output:** The compiler converts your SCSS into a single, optimized `.css` file.
4.  **Browser:** The browser receives the standard CSS and renders your app.

### How to use it in Angular
When you create a new Angular project, the CLI asks which stylesheet format you want to use. If you select **SCSS**, Angular automatically configures everything for you.

If you have an existing component, you'll see it linked in the `@Component` decorator:
```typescript
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss'] // Points to the SASS file
})
```

### Summary
Angular uses SASS because it provides **variables, nesting, and modularity**, which makes writing styles faster and more maintainable for professional, large-scale applications.
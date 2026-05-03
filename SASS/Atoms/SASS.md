---
id: 20260502205755
title: What is SASS?
author: Karl Schmitt
date: 2026-05-02
keywords: [ Angular, SASS, CSS ]
---

# What is SASS?


In the context of Angular, **SASS** (Syntactically Awesome Style Sheets) is a **CSS preprocessor**. 

It is an extension of standard CSS that adds powerful features like variables, nested rules, and functions, which help you write cleaner, more maintainable styles for your components.

Browsers cannot read SASS directly. Therefore, during the Angular build process, the Angular CLI automatically "transpiles" (converts) your SASS code into standard CSS so the browser can understand it.

---

### Key Features of SASS in Angular

#### 1. Variables
You can store colors, fonts, or any CSS value in a variable. If you need to change your primary brand color, you only change it in one place.
```scss
$primary-color: #3f51b5;

button {
  background-color: $primary-color;
}
```

#### 2. Nesting
SASS allows you to nest your CSS selectors in a way that follows the hierarchy of your HTML, making the code much easier to read.
```scss
.navbar {
  background: white;
  ul {
    list-style: none;
    li { display: inline-block; }
  }
}
```

#### 3. Mixins
Mixins are like functions for CSS. They allow you to define a group of styles and reuse them throughout your application.
```scss
@mixin flex-center {
  display: flex;
  justify-content: center;
  align-items: center;
}

.hero-section {
  @include flex-center;
}
```

#### 4. Partials and Imports

You can break your styles into smaller, manageable files (e.g., `_variables.scss`, `_buttons.scss`) and import them into your main stylesheet.

---

### SCSS vs. SASS: What's the difference?
When working with Angular, you will notice two different file extensions. Most Angular developers use **SCSS**.

*   **SCSS (.scss):** Stands for "Sassy CSS." It uses the same syntax as CSS (with curly braces `{}` and semicolons `;`). Every valid CSS file is a valid SCSS file. **This is the default for Angular.**
*   **SASS (.sass):** The older "indented" syntax. It uses indentation instead of braces and newlines instead of semicolons.

---

### Using SASS in Angular

#### 1. New Projects
When you create a new Angular project, the CLI asks which stylesheet format you would like to use. You simply select **SCSS**.
```bash
ng new my-app --style=scss
```

#### 2. Existing Projects
If your project is currently using CSS and you want to switch to SCSS, you can change the default in your `angular.json` file:
```json
"schematics": {
  "@schematics/angular:component": {
    "style": "scss"
  }
}
```

#### 3. Global vs. Component Styles
*   **Global styles:** Usually located in `src/styles.scss`. This is where you put your variables, mixins, and base theme.
*   **Component styles:** Located next to your component (e.g., `app.component.scss`). Because of Angular's **View Encapsulation**, styles written here will only affect that specific component.

### Why use SASS with Angular?
1.  **Maintainability:** Large Angular applications can have hundreds of components; SASS makes managing those styles much easier.
2.  **Angular Material:** If you use Angular Material (the official UI library), it is built entirely with SASS, and you need SASS to customize its themes.
3.  **Organization:** It encourages a modular approach to styling that mirrors Angular’s modular component structure.
---
id: 20260502210030
title: What is CSS?
author: Karl Schmitt
date: 2026-05-02
keywords: [ Angular, CSS ]
---

# What is CSS?

In the context of Angular, **CSS** (Cascading Style Sheets) is the fundamental language used to define the look and layout of your application. While SASS is an "extra" tool, CSS is the standard "language of the web" that every browser understands.

In an Angular project, CSS is used to control colors, fonts, spacing, and positioning of your components.

---

### How CSS Works in Angular

Angular treats CSS differently than a standard "plain HTML" website. It uses a unique system called **View Encapsulation**.

#### 1. Component-Level CSS (Scoped)
When you create a component, you usually have a `.css` file dedicated to it (e.g., `header.component.css`). 
*   **The Benefit:** By default, the styles you write in this file **only apply to that specific component**. 
*   **The "Magic":** If you define a `p { color: red; }` in your Header component, the paragraphs in your Footer component will stay black. Angular does this by automatically adding unique attributes (like `_ngcontent-c1`) to your HTML tags.

#### 2. Global CSS
Every Angular project has a file (usually `src/styles.css`). 
*   Styles written here apply to your **entire application**. 
*   This is the best place for your base fonts, CSS resets, and layouts that appear on every page.

---

### Ways to apply CSS in Angular

There are three main ways to include CSS in your components:

#### A. External File (Most Common)
Linked in the `@Component` decorator:
```typescript
@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'] // Points to an external file
})
```

#### B. Inline Styles
Used for very small amounts of CSS:
```typescript
@Component({
  selector: 'app-root',
  template: `<h1>Hello World</h1>`,
  styles: [`h1 { font-weight: bold; }`] // CSS written directly in the TS file
})
```

#### C. Global Styles
Added to the `styles` array in the `angular.json` configuration file.

---

### CSS vs. SASS in Angular

Since you previously asked about SASS, here is the direct comparison:

| Feature | Plain CSS | SASS (SCSS) |
| :--- | :--- | :--- |
| **Browser Support** | Supported natively by all browsers. | Not supported; must be converted to CSS. |
| **Variables** | Limited (using native CSS variables). | Robust and easy to use. |
| **Nesting** | Not traditionally supported. | Supported (makes code cleaner). |
| **Logic** | No math or logic. | Can use loops, if/else, and functions. |
| **Angular Default** | The "vanilla" option. | The industry-standard option for big apps. |

### Summary
In Angular, **CSS is the final product.** Even if you write your styles in SASS, the Angular CLI will turn them into CSS before showing them to the user. CSS in Angular is powerful because of **View Encapsulation**, which prevents your styles from accidentally "leaking" and breaking other parts of your website.


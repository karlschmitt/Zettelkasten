---
id: 20260501123427
title: SASS Tutorial
author: Karl Schmitt
date: 2026-05-01
keywords: [ Angular, SASS, SCSS]
---

Absolutely. Angular commonly supports **SCSS (Sassy CSS)** out of the box, which is the most popular syntax of **Sass**. It helps you write cleaner, reusable, and more maintainable styles for Angular apps.

# 🎨 Angular + SASS (SCSS) Tutorial

## 📌 What is SASS?

>[!NOTE]
> SASS = Syntactically Awesome Style Sheets

>[!IMPORTANT]
> **SASS** = CSS with superpowers.

It adds:

* [Variables](./Atoms/SASS_Variables.md) Follow the white rabbit 🐇 

* [Nesting](./Atoms/SASS_Nesting.md)

* Mixins

* Functions

* Partials

* Reuse

* Cleaner structure

Angular usually uses **SCSS syntax**, not the older indented `.sass` syntax.

```scss
$primary: #1976d2;

button {
  background: $primary;
}
```

***

# 📌 Why Angular Uses SCSS

In Angular, every component can have its own stylesheet:

```ts
@Component({
  selector: 'app-user',
  templateUrl: './user.component.html',
  styleUrls: ['./user.component.scss']
})
```

Benefits:

✅ Component styling\
✅ Cleaner code\
✅ Reusable theme system\
✅ Easier maintenance\
✅ Better scaling for large apps

***

# 📌 Create Angular Project with SCSS

You can use the following comand:
```bash
ng new my-app --style=scss --standalone
```

>[!NOTE]
> You can follow the white rabbit: [Create an Angular Project with SASS](./Atoms/Angular_with_SASS.md)

***

# 📌 Basic SCSS Features

***

# 1️⃣ Variables

```scss
$primary: #3498db;
$danger: #e74c3c;
$radius: 8px;

button {
  background: $primary;
  border-radius: $radius;
}
```

***

# 2️⃣ Nesting

Instead of:

```css
nav ul li a { }
```

Use:

```scss
nav {
  ul {
    li {
      a {
        color: blue;
      }
    }
  }
}
```

***

# 3️⃣ Parent Selector `&`

```scss
button {
  background: blue;

  &:hover {
    background: darkblue;
  }

  &.danger {
    background: red;
  }
}
```

Outputs:

```css
button:hover { }
button.danger { }
```

***

# 4️⃣ Partials + Imports

Create:

```scss
_styles.scss
_variables.scss
_mixins.scss
```

Use:

```scss
@use 'variables';
@use 'mixins';
```

***

# 5️⃣ Mixins

Reusable style blocks.

```scss
@mixin flex-center {
  display: flex;
  justify-content: center;
  align-items: center;
}

.card {
  @include flex-center;
}
```

***

# 6️⃣ Parameters in Mixins

```scss
@mixin button($bg, $color) {
  background: $bg;
  color: $color;
}

.save {
  @include button(green, white);
}

.delete {
  @include button(red, white);
}
```

***

# 7️⃣ Extend

```scss
%box {
  padding: 1rem;
  border-radius: 8px;
}

.card {
  @extend %box;
}

.panel {
  @extend %box;
}
```

***

# 📌 Angular Component Example

## user-card.component.scss

```scss
$primary: #1976d2;

.card {
  border: 1px solid #ddd;
  padding: 1rem;
  border-radius: 10px;

  h2 {
    color: $primary;
  }

  button {
    background: $primary;
    color: white;

    &:hover {
      opacity: 0.8;
    }
  }
}
```

***

# 📌 Global Styles in Angular

Inside:

```scss
src/styles.scss
```

Use for:

* Reset CSS

* Theme variables

* Typography

* Shared utilities

Example:

```scss
body {
  margin: 0;
  font-family: Arial;
}
```

***

# 📌 Recommended Angular Folder Structure

```text
src/
 ├── styles.scss
 ├── scss/
 │   ├── _variables.scss
 │   ├── _mixins.scss
 │   ├── _theme.scss
```

Then in `styles.scss`

```scss
@use './scss/variables';
@use './scss/mixins';
@use './scss/theme';
```

***

# 📌 Dark Mode Example

```scss
$dark-bg: #121212;
$dark-text: white;

.dark-mode {
  background: $dark-bg;
  color: $dark-text;
}
```

Angular:

```html
<body class="dark-mode">
```

***

# 📌 Responsive Design with Mixins

```scss
@mixin mobile {
  @media (max-width: 768px) {
    @content;
  }
}

.sidebar {
  width: 300px;

  @include mobile {
    width: 100%;
  }
}
```

***

# 📌 Best Practices in Angular

✅ Use SCSS per component\
✅ Keep global styles minimal\
✅ Use variables for colors/spacing\
✅ Use mixins for repetition\
✅ Use nesting max 3 levels deep\
✅ Use partials for organization

***

# 📌 Avoid

❌ Too much nesting\
❌ Huge global CSS files\
❌ Random colors everywhere\
❌ `!important` abuse

***

# 📌 Real Angular Theme Example

```scss
$primary: #1976d2;
$accent: #ff4081;

.btn-primary {
  background: $primary;
}

.btn-accent {
  background: $accent;
}
```

***

# 📌 Learn Sass in 7 Days for Angular

### Day 1

Variables + Nesting

### Day 2

Mixins

### Day 3

Partials

### Day 4

Responsive SCSS

### Day 5

Theme system

### Day 6

Component architecture

### Day 7

Build full Angular UI

***

# 📌 Summary

Sass makes Angular styling:

✅ Cleaner\
✅ Faster\
✅ Reusable\
✅ Professional\
✅ Easier to scale

***

# 🚀 If you'd like, I can also give you:

## **7-Day Angular SCSS Bootcamp**

or

## **Advanced Angular SCSS Architecture (Enterprise Style)**

or

## **Angular Material + SCSS Deep Dive**

Just say **continue**

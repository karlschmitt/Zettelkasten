---
id: 20260501124807
title: 7-Day Angular SCSS Bootcamp
author: Karl Schmitt
date: 2026-05-01
---

# 🎨 7-Day Angular SCSS Bootcamp

**Learn SCSS the practical way inside Angular projects**

This bootcamp is designed for Angular developers who want to become productive with **SCSS (Sass)** in real component-based applications.

***

# 📅 Day 1 — SCSS Fundamentals in Angular

## 🎯 Goal

Understand how Angular uses `.scss` files and learn the core syntax.

## Topics

* Angular component styles

* Global `styles.scss`

* Variables

* Nesting

* Parent selector `&`

## Example Component

```ts
@Component({
  selector: 'app-button',
  templateUrl: './button.component.html',
  styleUrls: ['./button.component.scss']
})
```

## button.component.scss

```scss
$primary: #1976d2;

button {
  background: $primary;
  color: white;

  &:hover {
    opacity: 0.85;
  }
}
```

## ✅ Exercise

Create:

* blue button

* red danger button

* green success button

***

# 📅 Day 2 — Variables + Design Tokens

## 🎯 Goal

Centralize colors, spacing, sizes.

## Create

```text
src/styles/_variables.scss
```

```scss
$color-primary: #1976d2;
$color-danger: #e53935;

$space-sm: 8px;
$space-md: 16px;
$space-lg: 24px;

$radius: 8px;
```

## Use

```scss
@use 'variables' as v;

.card {
  padding: v.$space-md;
  border-radius: v.$radius;
}
```

## ✅ Exercise

Build tokens for:

* colors

* spacing

* font sizes

* border radius

***

# 📅 Day 3 — Mixins for Reusable Styles

## 🎯 Goal

Stop repeating CSS.

## Example

```scss
@mixin flex-center {
  display: flex;
  justify-content: center;
  align-items: center;
}

@mixin button($bg) {
  background: $bg;
  color: white;
  padding: 10px 16px;
  border-radius: 8px;
}
```

## Use

```scss
.save-btn {
  @include button(green);
}

.delete-btn {
  @include button(red);
}
```

## ✅ Exercise

Create mixins for:

* card

* button

* center layout

* shadow

***

# 📅 Day 4 — Component Styling Mastery

## 🎯 Goal

Use SCSS effectively per Angular component.

## Example Structure

```text
app/
 ├── navbar/
 ├── sidebar/
 ├── dashboard-card/
```

Each has:

```text
component.ts
component.html
component.scss
```

## dashboard-card.component.scss

```scss
.card {
  padding: 1rem;
  border-radius: 12px;

  h3 {
    margin: 0;
  }

  .value {
    font-size: 2rem;
    font-weight: bold;
  }
}
```

## ✅ Exercise

Build:

* profile card

* pricing card

* dashboard stat card

***

# 📅 Day 5 — Responsive Angular SCSS

## 🎯 Goal

Make layouts mobile-friendly.

## Create mixin

```scss
@mixin mobile {
  @media (max-width: 768px) {
    @content;
  }
}
```

## Use

```scss
.sidebar {
  width: 260px;

  @include mobile {
    width: 100%;
  }
}
```

## Grid Example

```scss
.cards {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 1rem;

  @include mobile {
    grid-template-columns: 1fr;
  }
}
```

## ✅ Exercise

Convert desktop dashboard into mobile layout.

***

# 📅 Day 6 — Theming + Dark Mode

## 🎯 Goal

Build reusable themes.

## Variables

```scss
$light-bg: white;
$light-text: #222;

$dark-bg: #121212;
$dark-text: white;
```

## Theme Classes

```scss
.light-theme {
  background: $light-bg;
  color: $light-text;
}

.dark-theme {
  background: $dark-bg;
  color: $dark-text;
}
```

## Angular Toggle

```html
<body [class.dark-theme]="darkMode">
```

## ✅ Exercise

Create:

* light mode

* dark mode

* blue enterprise theme

***

# 📅 Day 7 — Real Angular SCSS Project

## 🎯 Goal

Combine everything into one polished UI.

## Build App

Choose one:

### Option A Dashboard

* navbar

* sidebar

* cards

* charts placeholder

### Option B Shop UI

* product cards

* cart sidebar

* filters

### Option C Portfolio

* hero section

* projects

* contact form

***

# 📁 Recommended SCSS Architecture

```text
src/
 ├── styles.scss
 ├── styles/
 │   ├── _variables.scss
 │   ├── _mixins.scss
 │   ├── _reset.scss
 │   ├── _theme.scss
```

## styles.scss

```scss
@use './styles/variables';
@use './styles/mixins';
@use './styles/reset';
@use './styles/theme';
```

***

# 🧠 Angular SCSS Best Practices

## ✅ Do

* Keep component styles local

* Use global tokens

* Use mixins

* Use BEM or clear naming

* Keep nesting shallow

## ❌ Avoid

* 7-level nesting

* giant styles.scss

* random colors

* duplicate button styles

* too many `!important`

***

# 🎯 Final Skills After 7 Days

You’ll know how to build:

✅ professional Angular layouts\
✅ responsive apps\
✅ reusable design systems\
✅ dark mode themes\
✅ maintainable enterprise styles

***

# 🚀 Bonus Challenge

Build:

### Angular Admin Dashboard

With:

* sidebar

* cards

* responsive nav

* theme switcher

* reusable buttons

***

# 📚 Next Step After Bootcamp

I can also give you:

## 🎯 30-Day Angular SCSS Mastery Plan

## 🎯 Angular Material + SCSS Bootcamp

## 🎯 Enterprise Angular Folder Structure + SCSS Architecture

## 🎯 Build a Real SaaS Dashboard with Angular + SCSS

Just say **continue**


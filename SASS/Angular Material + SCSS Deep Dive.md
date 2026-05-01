---
id: 20260501130343
title: Angular Material + SCSS Deep Dive
author: Karl Schmitt
date: 2026-05-01
---

# 🎨 Angular Material + SCSS Deep Dive

**Build professional Angular apps with Material Design + custom SCSS**

Angular + Angular Material is a powerful combination:

* Ready-made UI components

* Accessibility built in

* Responsive patterns

* Fast development

* SCSS theming + customization

This deep dive shows how to use Angular Material professionally with SCSS.

***

# 📌 What Is Angular Material?

Angular Material is the official Material Design component library for Angular.

Examples:

* Buttons

* Cards

* Dialogs

* Tables

* Inputs

* Menus

* Toolbar

* Tabs

* Snackbar

* Datepicker

***

# 📌 Install Angular Material

Use Angular CLI:

```bash
ng add @angular/material
```

Choose:

* Theme

* Typography

* Animations

***

# 📌 Why SCSS Matters with Angular Material

Material gives components.

SCSS gives control.

Use SCSS for:

✅ branding\
✅ spacing system\
✅ responsive layout\
✅ dark mode\
✅ overrides\
✅ reusable design tokens

***

# 📌 Example Material App Structure

```text
src/
 ├── styles.scss
 ├── theme/
 │   ├── _palette.scss
 │   ├── _theme.scss
 │   ├── _mixins.scss
```

***

# 📌 Basic Material Example

```html
<mat-card>
  <mat-card-title>Dashboard</mat-card-title>

  <button mat-raised-button color="primary">
    Save
  </button>
</mat-card>
```

***

# 📌 Component Styling with SCSS

```scss
mat-card {
  border-radius: 16px;
  padding: 1rem;
}

button {
  margin-top: 1rem;
}
```

***

# 📌 Global Theme Styling

Inside `styles.scss`

```scss
html, body {
  height: 100%;
  margin: 0;
}

body {
  font-family: Roboto, Arial, sans-serif;
}
```

***

# 🎨 Material Theming with SCSS

***

# 📌 Create Custom Theme

```scss
@use '@angular/material' as mat;

@include mat.core();

$primary: mat.define-palette(mat.$indigo-palette);
$accent: mat.define-palette(mat.$pink-palette);
$warn: mat.define-palette(mat.$red-palette);

$theme: mat.define-light-theme((
  color: (
    primary: $primary,
    accent: $accent,
    warn: $warn
  )
));

@include mat.all-component-themes($theme);
```

***

# 📌 Brand Colors Example

```scss
$primary: mat.define-palette(mat.$blue-palette, 700);
$accent: mat.define-palette(mat.$orange-palette, 500);
```

Great for custom branding.

***

# 📌 Buttons Deep Dive

```html
<button mat-raised-button color="primary">Primary</button>
<button mat-stroked-button>Outline</button>
<button mat-flat-button color="accent">Accent</button>
<button mat-icon-button>
  <mat-icon>menu</mat-icon>
</button>
```

SCSS:

```scss
button {
  border-radius: 12px;
}
```

***

# 📌 Cards Deep Dive

```html
<mat-card class="stats-card">
  <h2>Users</h2>
  <p>1,240</p>
</mat-card>
```

```scss
.stats-card {
  border-radius: 18px;
  box-shadow: 0 10px 20px rgba(0,0,0,.08);

  p {
    font-size: 2rem;
    font-weight: bold;
  }
}
```

***

# 📌 Forms Deep Dive

```html
<mat-form-field appearance="outline">
  <mat-label>Email</mat-label>
  <input matInput>
</mat-form-field>
```

SCSS:

```scss
mat-form-field {
  width: 100%;
}
```

***

# 📌 Toolbar + Navigation

```html
<mat-toolbar color="primary">
  My App
</mat-toolbar>
```

```scss
mat-toolbar {
  position: sticky;
  top: 0;
}
```

***

# 📌 Tables

```html
<table mat-table [dataSource]="users">
</table>
```

SCSS:

```scss
table {
  width: 100%;
}
```

***

# 📌 Dialogs

```ts
this.dialog.open(UserDialogComponent);
```

Dialog SCSS:

```scss
.dialog-content {
  padding: 1rem;
}
```

***

# 🌙 Dark Mode with Angular Material

## Light Theme

```scss
.light-theme {
  @include mat.all-component-colors($light-theme);
}
```

## Dark Theme

```scss
.dark-theme {
  @include mat.all-component-colors($dark-theme);
}
```

Angular:

```html
<body [class.dark-theme]="darkMode">
```

***

# 📱 Responsive Layout with SCSS

```scss
.dashboard {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  gap: 1rem;
}

@media (max-width: 768px) {
  .dashboard {
    grid-template-columns: 1fr;
  }
}
```

***

# 📌 Custom Material Overrides

Example:

```scss
.mat-mdc-card {
  border-radius: 20px;
}
```

Example:

```scss
.mat-mdc-raised-button {
  padding: 0 24px;
}
```

Use carefully.

***

# 📌 Recommended Architecture

```text
src/
 ├── app/
 ├── shared/
 ├── styles/
 │   ├── _variables.scss
 │   ├── _material-theme.scss
 │   ├── _utilities.scss
 │   ├── _dark-theme.scss
```

***

# 🧠 Best Practices

## ✅ Do

* Use Material components first

* Customize via theme system

* Use SCSS tokens

* Keep spacing consistent

* Use dark mode support

## ❌ Avoid

* Random CSS overrides everywhere

* Too much `::ng-deep`

* Inconsistent colors

* Fighting Material defaults constantly

***

# 🚀 Real Projects You Can Build

## 1. Admin Dashboard

* toolbar

* sidenav

* cards

* charts

## 2. CRM Tool

* table

* dialogs

* forms

## 3. Shop UI

* product cards

* filters

* cart drawer

## 4. SaaS App

* auth screens

* analytics

* billing pages

***

# 🎯 What Professionals Do

Companies often use:

* Angular Material for speed

* SCSS tokens for branding

* Custom theme system

* Shared component library

***

# 📚 If You Want Mastery Next

I can also provide:

## 🎯 30-Day Angular Material Mastery Plan

## 🎯 Build Real Admin Dashboard with Angular Material

## 🎯 Angular Material Theming Expert Guide

## 🎯 Angular Material + RxJS + Signals Full Stack UI Project

Just say **continue**

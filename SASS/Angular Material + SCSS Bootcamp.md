---
id: 20260501130956
title: Angular Material + SCSS Bootcamp
author: Karl Schmitt
date: 2026-05-01
---

# 🎨 Angular Material + SCSS Bootcamp

**Build modern Angular apps with professional UI systems**

Angular + Angular Material + SCSS is one of the fastest ways to build polished enterprise-grade frontends.

This bootcamp takes you from setup to real-world app building.

***

# 🧭 What You’ll Learn

By the end, you’ll know how to build:

✅ dashboards\
✅ admin panels\
✅ forms\
✅ responsive layouts\
✅ dark mode themes\
✅ reusable UI architecture\
✅ professional Angular apps

***

# 📅 Phase 1 — Foundations (Days 1–3)

## 🎯 Day 1 — Install + Setup

Use Angular CLI:

```bash
ng new material-app --style=scss
cd material-app
ng add @angular/material
```

Choose:

* theme preset

* global typography

* animations

## Learn

* Angular Material modules

* component SCSS files

* `styles.scss`

## Exercise

Build:

* toolbar

* card

* button row

***

## 🎯 Day 2 — Material Basics

Use components:

```html
<mat-toolbar color="primary">My App</mat-toolbar>

<mat-card>
  <button mat-raised-button color="accent">
    Save
  </button>
</mat-card>
```

Learn:

* buttons

* cards

* icons

* toolbar

## Exercise

Create landing page header.

***

## 🎯 Day 3 — SCSS Basics

Use component SCSS:

```scss
mat-card {
  border-radius: 16px;
  padding: 1rem;
}

button {
  margin-top: 1rem;
}
```

Learn:

* variables

* nesting

* spacing

***

# 📅 Phase 2 — Real UI Skills (Days 4–7)

## 🎯 Day 4 — Forms

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

Build:

* login form

* register form

***

## 🎯 Day 5 — Tables

Use:

* `mat-table`

* sorting

* rows

* hover states

SCSS:

```scss
table {
  width: 100%;
}
```

Build user management page.

***

## 🎯 Day 6 — Navigation Layout

Use:

* sidenav

* toolbar

* menu

```html
<mat-sidenav-container>
  <mat-sidenav>Menu</mat-sidenav>
  <mat-sidenav-content>Main</mat-sidenav-content>
</mat-sidenav-container>
```

Build dashboard shell.

***

## 🎯 Day 7 — Mini Project

Build:

### Admin Dashboard v1

* sidenav

* topbar

* cards

* table

* actions

***

# 📅 Phase 3 — Theming + SCSS Power (Days 8–12)

## 🎯 Day 8 — Custom Theme

```scss
@use '@angular/material' as mat;
@include mat.core();
```

Create custom palettes.

***

## 🎯 Day 9 — Brand Colors

Use company style colors:

* blue enterprise

* fintech green

* startup purple

***

## 🎯 Day 10 — Shared SCSS Tokens

```scss
$space-md: 16px;
$radius-lg: 16px;
$shadow-soft: 0 8px 16px rgba(0,0,0,.08);
```

Use across components.

***

## 🎯 Day 11 — Mixins

```scss
@mixin card {
  border-radius: 18px;
  padding: 1rem;
}
```

***

## 🎯 Day 12 — Utility Classes

Create:

```scss
.mt-1 {}
.p-2 {}
.text-center {}
```

***

# 📅 Phase 4 — Responsive + Dark Mode (Days 13–17)

## 🎯 Day 13 — Responsive Grid

```scss
.dashboard {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
}
```

***

## 🎯 Day 14 — Mobile Breakpoints

```scss
@media (max-width: 768px) {
}
```

***

## 🎯 Day 15 — Dark Mode

```scss
.dark-theme {}
.light-theme {}
```

Angular toggle with component state.

***

## 🎯 Day 16 — Drawer Navigation Mobile

Responsive sidenav behavior.

***

## 🎯 Day 17 — Mini Project

Upgrade dashboard:

✅ mobile ready\
✅ dark mode\
✅ polished spacing

***

# 📅 Phase 5 — Real Production UI (Days 18–24)

## 🎯 Day 18 — Dialogs

Use Angular Material dialogs for create/edit forms.

***

## 🎯 Day 19 — Snackbar Notifications

Success / error messages.

***

## 🎯 Day 20 — Loading States

* spinner

* skeleton cards

* disabled buttons

***

## 🎯 Day 21 — Empty States

"No users found"

***

## 🎯 Day 22 — Reusable Components

Build:

* stat card

* page header

* confirm dialog

* badge chip

***

## 🎯 Day 23 — Accessibility

Use:

* focus styles

* keyboard nav

* contrast

***

## 🎯 Day 24 — Polish UI

Animations:

```scss
transition: all .25s ease;
```

***

# 📅 Final Week — Build Real Apps (Days 25–30)

## 🎯 Choose One Final Project

### Option A — SaaS Dashboard

* analytics cards

* billing page

* settings page

### Option B — CRM System

* contacts table

* dialogs

* notes panel

### Option C — Shop Admin

* products table

* inventory cards

* order dialogs

### Option D — Personal Finance App

* transactions

* charts area

* budgets

***

# 📁 Recommended Folder Structure

```text
src/
 app/
   core/
   shared/
   features/

 styles/
   _variables.scss
   _mixins.scss
   _theme.scss
   _utilities.scss
```

***

# 🧠 Professional Rules

## ✅ Do

* Use Material first

* Theme centrally

* Use SCSS tokens

* Keep spacing consistent

* Build reusable widgets

## ❌ Avoid

* Random overrides

* Massive component CSS

* Too many colors

* Duplicate buttons

***

# 🏆 Final Skills

After this bootcamp you’ll build apps similar in polish to products from:

* Google

* Microsoft

* Atlassian

* Notion

***

# 🚀 Next Level Bootcamps

I can also provide:

## 🎯 30-Day Angular Material Mastery Plan

## 🎯 Build Real Angular Admin Dashboard Step-by-Step

## 🎯 Angular Material Theming Expert Guide

## 🎯 Angular Material + NgRx + Signals Enterprise Project

Just say **continue**

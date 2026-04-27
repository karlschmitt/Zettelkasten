---
id: 20260427122704
title: Angular Property Binding Tutorial
author: Karl Schmitt
date: 2026-04-27
---

# Angular Property Binding Tutorial

Property binding is one of the core template features in Angular. It lets you send data **from your component class into an HTML element property, directive input, or component input**.

Think of it as:

> TypeScript → DOM / Component

---

# 1. Syntax

```html
[property]="expression"
```

Examples:

```html
<img [src]="imageUrl">
<button [disabled]="isSaving">
<input [value]="username">
```

Angular evaluates the expression in your component and assigns it to the target property.

---

# 2. Property Binding vs Interpolation

## Interpolation

```html
<p>{{ title }}</p>
```

Displays text content.

## Property Binding

```html
<img [src]="imageUrl">
```

Sets DOM properties.

Use interpolation for text, property binding for element behavior/configuration.

---

# 3. Basic Example

## component.ts

```ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.html'
})
export class AppComponent {
  imageUrl = 'assets/logo.png';
}
```

## template.html

```html
<img [src]="imageUrl">
```

Angular sets the `src` property of the image element.

---

# 4. Bind Button Disabled State

```ts
isFormInvalid = true;
```

```html
<button [disabled]="isFormInvalid">Save</button>
```

If `true`, button is disabled. If `false`, enabled.

---

# 5. Bind Input Value

```ts
username = 'Karl';
```

```html
<input [value]="username">
```

This writes the value into the input.

---

# 6. Dynamic CSS Classes

```ts
isActive = true;
```

```html
<div [class.active]="isActive">Status</div>
```

Adds class `active` when true.

---

# 7. Dynamic Styles

```ts
width = 250;
color = 'green';
```

```html
<div [style.width.px]="width">Box</div>
<div [style.color]="color">Text</div>
```

---

# 8. Bind Element Attributes vs Properties

This is important.

## Property Binding

```html
<input [value]="name">
```

Changes live DOM property.

## Attribute Binding

```html
<td [attr.colspan]="2"></td>
```

Used when no matching DOM property exists.

Use property binding first. Use `attr.` when needed.

---

# 9. Boolean Properties

```ts
isChecked = true;
isReadonly = false;
```

```html
<input type="checkbox" [checked]="isChecked">
<input [readonly]="isReadonly">
```

---

# 10. Binding Expressions

```ts
price = 10;
qty = 4;
```

```html
<p [textContent]="price * qty"></p>
```

Result: `40`

---

# 11. Bind to Component Inputs

If you create child components:

## child.component.ts

```ts
@Component({
  selector: 'app-user-card',
  template: `<p>{{ name }}</p>`
})
export class UserCardComponent {
  @Input() name = '';
}
```

## parent template

```html
<app-user-card [name]="username"></app-user-card>
```

This is still property binding.

---

# 12. Real World Example

## component.ts

```ts
product = {
  name: 'Keyboard',
  inStock: false,
  image: 'assets/keyboard.png'
};
```

## template.html

```html
<h2>{{ product.name }}</h2>

<img [src]="product.image">

<button [disabled]="!product.inStock">
  Buy Now
</button>
```

---

# 13. One-Way Data Flow

Property binding is:

> Component ➜ Template

User changes do **not** automatically go back.

For two-way input use:

```html
[(ngModel)]
```

or reactive forms.

---

# 14. Common Beginner Mistakes

## ❌ Using interpolation inside brackets

Wrong:

```html
<img [src]="{{ imageUrl }}">
```

Correct:

```html
<img [src]="imageUrl">
```

---

## ❌ Using `this`

Wrong:

```html
<button [disabled]="this.loading">
```

Correct:

```html
<button [disabled]="loading">
```

---

## ❌ Confusing attributes and properties

Wrong sometimes:

```html
<input disabled="false">
```

Still disabled because attribute exists.

Correct:

```html
<input [disabled]="false">
```

---

# 15. Null / Undefined Safety

```ts
user = undefined;
```

```html
<img [src]="user?.avatar">
```

Prevents errors if user missing.

---

# 16. Useful Native Properties

| Element | Property                       |
| ------- | ------------------------------ |
| img     | `src`, `alt`                   |
| input   | `value`, `checked`, `readonly` |
| button  | `disabled`                     |
| video   | `muted`, `controls`            |
| a       | `href`, `target`               |

---

# 17. Mini Practice

## component.ts

```ts
title = 'Dashboard';
darkMode = true;
photo = 'assets/me.png';
fontSize = 22;
```

## template.html

```html
<h1 [textContent]="title"></h1>

<img [src]="photo">

<button [disabled]="darkMode">Toggle</button>

<p [style.fontSize.px]="fontSize">
  Hello
</p>
```

---

# 18. Relationship to Other Bindings

| Type          | Syntax             | Direction |
| ------------- | ------------------ | --------- |
| Interpolation | `{{ value }}`      | TS ➜ Text |
| Property      | `[prop]="value"`   | TS ➜ DOM  |
| Event         | `(click)="save()"` | DOM ➜ TS  |
| Two-way       | `[(ngModel)]`      | Both      |

---

# 19. Best Practices

## ✅ Keep expressions simple

```html
<button [disabled]="isLoading">
```

## ✅ Compute in component

```ts
get canSave() {
  return this.formValid && !this.isLoading;
}
```

```html
<button [disabled]="!canSave">
```

## ✅ Prefer readability

---

# 20. Mental Model

```html
[property]="data"
```

means:

> “Whenever `data` changes, update that property.”

---

# 21. Mini Challenge

Build this:

```html
<img [src]="avatar">

<h2 [textContent]="username"></h2>

<button [disabled]="isOffline">
  Send Message
</button>

<div [style.backgroundColor]="themeColor">
  Panel
</div>
```

---

# 22. Summary

Use property binding when you want to control:

✅ disabled state
✅ image source
✅ input values
✅ CSS classes
✅ styles
✅ child component inputs

Syntax:

```html
[property]="expression"
```

---

# Next Best Topic

After property binding, learn **Event Binding**:

```html
<button (click)="save()">Save</button>
```

This completes the opposite direction.

---

If you'd like, I can also give you an **Angular Property Binding 7-Day Bootcamp with exercises and mini projects** next.

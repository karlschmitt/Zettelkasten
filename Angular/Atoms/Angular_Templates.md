---
id: 20260426180948
title: Angular Templates
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, template ]
---

# Angular Template

An **Angular Template** is a form of HTML that tells Angular how to render a component's user interface. While it looks like regular HTML, it includes special syntax that allows you to display dynamic data and react to user input.

In simple terms: **Template = HTML + Angular "Superpowers".**

---

### 1. External vs. Inline Templates
You can define a template in two ways within the `@Component` decorator:

#### **External File (Recommended)**
The HTML is in a separate file. This is best for large, complex views.
```typescript
@Component({
  selector: 'app-user',
  templateUrl: './user.component.html', // Path to the file
  standalone: true
})
```

#### **Inline Template**
The HTML is written directly in the TypeScript file using backticks (`` ` ``). This is best for very small components.
```typescript
@Component({
  selector: 'app-user',
  template: `<h1>Hello, {{ name }}</h1>`, // HTML written here
  standalone: true
})
```

---

### 2. Core Template Syntax

The "Superpowers" added to standard HTML include:

#### **A. Interpolation `{{ }}`**
Used to display data from your TypeScript class into the HTML.
```html
<p>Welcome back, {{ username }}!</p>
<p>The result of 2+2 is {{ 2 + 2 }}</p>
```

#### **B. Control Flow (Modern Angular 17+)**
These allow you to add logic directly in your HTML to show, hide, or repeat elements.

*   **`@if`**: Conditional rendering.
    ```html
    @if (isLoggedIn) {
      <button>Logout</button>
    } @else {
      <button>Login</button>
    }
    ```
*   **`@for`**: Looping through arrays.
    ```html
    <ul>
      @for (item of items; track item.id) {
        <li>{{ item.name }}</li>
      }
    </ul>
    ```

#### **C. Data Binding**
*   **Property Binding `[ ]`**: Passing data from the class to an HTML attribute.
    ```html
    <img [src]="userImageUrl" [alt]="userName">
    ```
*   **Event Binding `( )`**: Listening for user actions.
    ```html
    <button (click)="saveData()">Save</button>
    ```

---

### 3. Template Reference Variables (`#`)
You can use the `#` symbol to declare a variable that points to a specific HTML element or component so you can access it elsewhere in the template.

```html
<!-- #phone creates a variable that represents the input element -->
<input #phone placeholder="Enter phone number" />

<!-- We can access the value of the input without any TypeScript logic -->
<button (click)="callNumber(phone.value)">Call</button>
```

---

### 4. Pipes (`|`)
Pipes are used inside templates to transform data **before** it is displayed to the user.

```html
<!-- Formats a date object -->
<p>Today is {{ today | date:'shortDate' }}</p>

<!-- Converts text to uppercase -->
<p>{{ username | uppercase }}</p>

<!-- Formats currency -->
<p>Total: {{ price | currency:'USD' }}</p>
```

---

### 5. Directives
Directives are markers on a DOM element that tell Angular to attach a special behavior to it.

*   **`[ngClass]`**: Add or remove CSS classes dynamically.
    ```html
    <div [ngClass]="{ 'active': isActive, 'error': hasError }"></div>
    ```
*   **`[ngStyle]`**: Apply styles dynamically.
    ```html
    <div [ngStyle]="{ 'color': isAdmin ? 'red' : 'blue' }"></div>
    ```

---

### Summary: What makes an Angular Template different?
| Feature | Standard HTML | Angular Template |
| :--- | :--- | :--- |
| **Data** | Static text | Dynamic (`{{ }}`) |
| **Logic** | Requires JS in script tags | Built-in (`@if`, `@for`) |
| **Attributes** | Static values | Property binding (`[src]`) |
| **Interactivity** | Event listeners in JS | Event binding (`(click)`) |
| **Formatting** | Manual string manipulation | Pipes (`| date`) |
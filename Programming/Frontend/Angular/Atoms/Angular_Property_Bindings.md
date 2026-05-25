---
id: 20260427121457
title: Angular Property Bindings
author: Karl Schmitt
date: 2026-04-27
keywords: [ Angular, property, binding]
---

# Angular Property Bindings

**Property Binding** in Angular is a one-way data binding mechanism that allows you to set the value of a **DOM property** (like an image source, a button's disabled state, or a component's input) directly from a TypeScript variable.

While Interpolation (`{{ }}`) is mainly for inserting text between tags, Property Binding is for controlling the behavior and state of HTML elements and components.

---

### 1. The Syntax
Property binding uses **square brackets** `[]` around the target property.

```html
<button [disabled]="isButtonDisabled">Click Me</button>
<img [src]="imageUrl">
```

*   **The Target (in brackets):** The property of the DOM element you want to set.
*   **The Source (inside quotes):** The variable or expression from your TypeScript class.

---

### 2. How it Works: Properties vs. Attributes
To understand property binding, you must understand the difference between **HTML Attributes** and **DOM Properties**:

1.  **Attributes:** Defined in the HTML source code. They initialize the DOM properties and then their job is done.
2.  **Properties:** Live in the DOM tree. They represent the **current state** of the element.

**Angular Property Binding targets DOM Properties.**
For example, when you do `[disabled]="true"`, Angular isn't just writing an attribute to the HTML; it is finding the `disabled` property on the button object in the browser's memory and setting it to `true`.

---

### 3. Key Use Cases

#### A. Disabling Elements (Boolean values)
Interpolation always converts data to a string. If you use interpolation on a boolean, it becomes the string `"true"` or `"false"`. Property binding keeps the data type intact.
*   **TS:** `isProcessing = true;`
*   **HTML:** `<button [disabled]="isProcessing">Submit</button>`

#### B. Dynamic Source/Links
*   **TS:** `userPhoto = 'assets/user-1.jpg';`
*   **HTML:** `<img [src]="userPhoto">`

#### C. Passing Data to Child Components (Communication)
This is the most common way to send data from a Parent component to a Child component.
*   **Parent HTML:** `<app-user-detail [user]="selectedUser"></app-user-detail>`
*   *(Inside the Child component, `user` would be marked with an `@Input()` decorator).*

#### D. Setting CSS Classes or Styles
You can bind to the `class` or `style` properties for dynamic styling.
*   **HTML:** `<div [class.active]="isActive"></div>`
*   **HTML:** `<button [style.color]="isError ? 'red' : 'blue'">Save</button>`

---

### 4. Property Binding vs. Interpolation
Often, you can use either. However, there are rules for when to choose one over the other:

| Feature | Interpolation `{{ }}` | Property Binding `[ ]` |
| :--- | :--- | :--- |
| **Primary Goal** | Render data as **text** in the UI. | Set element **properties** or **inputs**. |
| **Data Type** | Converts everything to a **string**. | Preserves **data types** (Booleans, Objects). |
| **Usage** | `<span>{{ name }}</span>` | `<img [src]="url">` |
| **Rule of Thumb** | Use for text content. | Use for non-string values or element properties. |

**Example of why Property Binding is better for non-strings:**
```html
<!-- This works correctly: passes a boolean false -->
<button [disabled]="false">OK</button> 

<!-- This might fail: passes a string "false", which HTML may treat as true! -->
<button disabled="{{false}}">OK</button> 
```

---

### 5. Security (Sanitization)
Angular is built with security in mind. If you try to bind a property to a value that could be a security risk (like a `javascript:alert()` link in an `href`), Angular will **sanitize** the value before rendering it. It will strip out dangerous code to prevent Cross-Site Scripting (XSS) attacks.

---

### 6. Technical Summary
1.  **Direction:** One-way, from the **Component Source** to the **View Target**.
2.  **Detection:** When the variable in the TypeScript class changes, Angular's change detection detects the new value and updates the DOM property immediately.
3.  **Template Expressions:** Just like interpolation, you can use logic inside the quotes (e.g., `[src]="'path/' + fileName"`), but you cannot perform assignments (`=`) or use complex logic.
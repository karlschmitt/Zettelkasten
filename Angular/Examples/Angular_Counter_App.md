---
id: 20260429132024
title: Angular Counter App
author: Karl Schmitt
date: 2026-04-29
keywords: [ Angular, Counter App ]
---

# Angular Counter App

To build a Counter App in Angular, you can use the modern **Signals** approach (introduced in Angular 16/17+) or the **Classic** approach. 

Below is the guide for the **Modern Approach**, as it is the current best practice for performance and simplicity.

### 1. The Component Logic (`app.component.ts`)
We will use a `signal` to manage the state. Signals allow Angular to update the UI instantly whenever the value changes.

```typescript
import { Component, signal } from '@angular/core';

@Component({
  selector: 'app-root',
  standalone: true,
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent {
  // Initialize the counter with a value of 0
  count = signal(0);

  increment() {
    this.count.update(value => value + 1);
  }

  decrement() {
    this.count.update(value => value - 1);
  }

  reset() {
    this.count.set(0);
  }
}
```

---

### 2. The Template (`app.component.html`)
In the HTML, we use `()` for event binding and `{{ count() }}` to display the value.

```html
<div class="counter-container">
  <h1>Angular Counter</h1>
  
  <!-- Display Value -->
  <div class="display">
    {{ count() }}
  </div>

  <div class="controls">
    <!-- Increment / Decrement buttons -->
    <button (click)="decrement()" class="btn-sub">-</button>
    <button (click)="increment()" class="btn-add">+</button>
  </div>

  <!-- Reset button -->
  <button (click)="reset()" class="btn-reset">Reset</button>
</div>
```

---

### 3. The Styling (`app.component.css`)
Add some basic CSS to make it look like a real app.

```css
.counter-container {
  text-align: center;
  font-family: Arial, sans-serif;
  margin-top: 50px;
}

.display {
  font-size: 5rem;
  font-weight: bold;
  margin: 20px 0;
  color: #3b82f6;
}

button {
  font-size: 1.5rem;
  padding: 10px 25px;
  margin: 5px;
  cursor: pointer;
  border: none;
  border-radius: 8px;
  transition: opacity 0.2s;
}

button:hover {
  opacity: 0.8;
}

.btn-add { background-color: #22c55e; color: white; }
.btn-sub { background-color: #ef4444; color: white; }
.btn-reset { 
  background-color: #64748b; 
  color: white; 
  display: block; 
  margin: 20px auto; 
}
```

---

### Key Concepts Explained:

1.  **`signal(0)`**: This creates a reactive variable. When the value inside it changes, Angular knows exactly which part of the HTML to update without re-rendering the whole page.
2.  **`this.count.update(...)`**: This is the preferred way to change a signal based on its previous value (used for increment/decrement).
3.  **`this.count.set(0)`**: This is used to force the signal to a specific value (used for reset).
4.  **`{{ count() }}`**: In the HTML, you must call the signal like a function `()` to get its current value.

### How to run this:
1.  If you don't have a project yet, run `ng new counter-app` in your terminal.
2.  Paste the code above into the respective files in `src/app/`.
3.  Run `ng serve` and open `localhost:4200`.
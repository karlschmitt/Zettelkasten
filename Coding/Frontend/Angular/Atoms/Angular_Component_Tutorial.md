---
id: 20260426165227
title: Angular Component Tutorial
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, component, tutorial]
summary:
Dieser Leitfaden erläutert die **grundlegende Architektur von Angular-Komponenten**, die als zentrale Bausteine für Benutzeroberflächen dienen. Eine Komponente vereint dabei stets die **logische Programmierung, das visuelle Design sowie die strukturelle Vorlage** in einer Einheit. Die Dokumentation beschreibt detailliert, wie **Datenbindungen und moderne Kontrollstrukturen** eine dynamische Interaktion zwischen dem Code und der Ansicht ermöglichen. Darüber hinaus wird die **Kommunikation zwischen verschiedenen Elementen** durch spezielle Eingabe- und Ausgabebefehle sowie die Verwaltung des **Lebenszyklus einer Komponente** thematisiert. Abschließend bietet der Text praktische Hilfestellungen zur **automatisierten Erstellung von Dateien** über das Terminal und fasst die wichtigsten Entwicklungsschritte zusammen.
---

![Angular_Component_Architecture](../Images/Angular_Component_Architecture.png)

# Angular Component Tutorial: The Building Blocks

In Angular, a **Component** is the fundamental building block of the UI. Every page you see and every reusable widget (like a navbar or a button) is a component.

---

## 1. Anatomy of a Component

A component consists of three main parts:
1.  **The Template (HTML):** Defines the structure.
2.  **The Styles (CSS/SCSS):** Defines the look (scoped to this component).
3.  **The Logic (TypeScript):** Defines the behavior and data.

### The Component Class
Here is what a basic standalone component looks like (`user-profile.component.ts`):

```typescript
import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';

@Component({
  selector: 'app-user-profile',      // How you use it in HTML: <app-user-profile></app-user-profile>
  standalone: true,                 // Modern Angular (v17+) default
  imports: [CommonModule],          // Add other components or modules here
  templateUrl: './user-profile.component.html',
  styleUrl: './user-profile.component.scss'
})
export class UserProfileComponent {
  username: string = 'John Doe';
  isAdmin: boolean = true;

  toggleRole() {
    this.isAdmin = !this.isAdmin;
  }
}
```

---

## 2. Data Binding

Data binding is how the TypeScript class communicates with the HTML template.

### A. Interpolation `{{ }}`
Display logic data in the view.
```html
<h1>Welcome, {{ username }}</h1>
```

### B. Property Binding `[ ]`
Pass values from logic to HTML attributes.
```html
<button [disabled]="!isAdmin">Delete User</button>
```

### C. Event Binding `( )`
Send notifications from the view to the logic (e.g., clicks).
```html
<button (click)="toggleRole()">Change Role</button>
```

### D. Two-Way Binding `[( )]`
Sync data both ways (requires `FormsModule`).
```html
<input [(ngModel)]="username" />
```

---

## 3. Modern Control Flow (`@if`, `@for`)

In Angular 17+, we use a new, cleaner syntax for conditional rendering and loops.

### `@if` (Conditional)
```html
@if (isAdmin) {
  <p>Status: Administrator</p>
} @else {
  <p>Status: Standard User</p>
}
```

### `@for` (Looping)
The `track` property is mandatory and significantly improves performance.
```html
<ul>
  @for (user of users; track user.id) {
    <li>{{ user.name }}</li>
  } @empty {
    <li>No users found.</li>
  }
</ul>
```

---

## 4. Component Communication

Components often need to talk to each other (Parent to Child and vice-versa).

### Parent to Child: `@Input()`
The parent passes data "down."

**Child (`child.component.ts`):**
```typescript
import { Component, Input } from '@angular/core';

@Component({ ... })
export class ChildComponent {
  @Input() userTitle: string = '';
}
```

**Parent Template:**
```html
<app-child [userTitle]="'Manager'"></app-child>
```

### Child to Parent: `@Output()`
The child sends an event "up."

**Child (`child.component.ts`):**
```typescript
import { Component, Output, EventEmitter } from '@angular/core';

@Component({ ... })
export class ChildComponent {
  @Output() notify = new EventEmitter<string>();

  sendToParent() {
    this.notify.emit('Hello Parent!');
  }
}
```

**Parent Template:**
```html
<app-child (notify)="onChildNotify($event)"></app-child>
```

---

## 5. Lifecycle Hooks

Angular components have a "lifecycle" managed by Angular. You can "hook" into specific moments.

| Hook | Purpose |
| :--- | :--- |
| **`ngOnInit`** | Runs once after the component is initialized. Best for API calls. |
| **`ngOnChanges`** | Runs whenever an `@Input` property changes. |
| **`ngOnDestroy`** | Runs just before the component is removed. Best for cleaning up (unsubscribing). |

**Example:**
```typescript
import { Component, OnInit, OnDestroy } from '@angular/core';

@Component({ ... })
export class MyComponent implements OnInit, OnDestroy {
  
  ngOnInit() {
    console.log('Component Loaded!');
  }

  ngOnDestroy() {
    console.log('Cleaning up...');
  }
}
```

---

## 6. How to create a component via CLI

Use the command we discussed in the structure tutorial:

```bash
ng generate component my-component-name
# OR shortcut
ng g c my-component-name
```

**This command creates:**
1. `my-component-name.component.ts` (Logic)
2. `my-component-name.component.html` (Template)
3. `my-component-name.component.scss` (Styles)
4. `my-component-name.component.spec.ts` (Tests)

---

## Summary Checklist
- [ ] Define the class with `@Component`.
- [ ] Set a `selector` name.
- [ ] Use `{{ }}` to show variables.
- [ ] Use `(click)` to handle user actions.
- [ ] Use `@Input()` to receive data from parents.
- [ ] Use `ngOnInit` to fetch your initial data.
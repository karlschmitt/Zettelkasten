---
id: 20260426201752
title: Angular Template Tutorial
author: Karl Schmitt
date: 2026-04-26
keywords: [ Angular, Template, Tutorial ]
---

# Angular Template Tutorial

Absolutely—Angular templates are where your data _comes alive_. If components are the brain, templates are the face.

Here’s a **hands-on Angular Template Tutorial** using **Angular**.

***

# 🧠 Angular Templates — Complete Guide

***

# 1. 🧩 What is an Angular Template?

A template is **HTML + Angular syntax** that:

* Displays data

* Reacts to user input

* Binds UI to your component

***

## ✍️ Example

```ts
export class AppComponent {
  name = "Karl";
}
```

```html
<h1>Hello {{ name }}</h1>
```

👉 `{{ name }}` = **interpolation**

***

# 2. 🔗 Data Binding (Core Concept)

Angular gives you 4 types of binding:

***

## 1. Interpolation `{{ }}`

```html
<p>{{ title }}</p>
```

✔ Display data

***

## 2. Property Binding `[ ]`

```html
<img [src]="imageUrl">
```

✔ Bind to DOM properties

***

## 3. Event Binding `( )`

```html
<button (click)="sayHello()">Click</button>
```

✔ Handle user actions

***

## 4. Two-Way Binding `[( )]`

```html
<input [(ngModel)]="name">
```

✔ Sync UI ↔ data

👉 Requires `FormsModule`

***

# 3. 🧱 Structural Directives

These **change the DOM structure**

***

## 🔹 \*ngIf

```html
<p *ngIf="isLoggedIn">Welcome!</p>
```

***

## 🔹 \*ngFor

```html
<li *ngFor="let task of tasks">
  {{ task }}
</li>
```

***

## 🔹 \*ngSwitch

```html
<div [ngSwitch]="role">
  <p *ngSwitchCase="'admin'">Admin</p>
  <p *ngSwitchDefault>User</p>
</div>
```

***

## 🧠 Rule

Structural directives use `*`

***

# 4. 🎨 Attribute Directives

Change appearance/behavior

***

## ✍️ Examples

```html
<p [class.active]="isActive"></p>
<p [style.color]="isError ? 'red' : 'green'"></p>
```

***

## Multiple Classes

```html
<div [ngClass]="{ active: isActive, disabled: isDisabled }"></div>
```

***

# 5. 🔄 Template Expressions

You can use JavaScript-like expressions:

```html
<p>{{ 2 + 2 }}</p>
<p>{{ user.name.toUpperCase() }}</p>
```

***

## ⚠️ Avoid

* Complex logic

* Heavy computation

👉 Keep templates simple!

***

# 6. 🧠 Template Reference Variables

```html
<input #inputRef>
<button (click)="log(inputRef.value)">Log</button>
```

***

# 7. 🧩 Event Handling

```html
<input (input)="onInput($event)">
```

```ts
onInput(event: Event) {
  const value = (event.target as HTMLInputElement).value;
}
```

***

# 8. ⚡ Pipes (Transform Data)

```html
<p>{{ name | uppercase }}</p>
<p>{{ date | date:'short' }}</p>
```

***

## Common Pipes

* `uppercase`

* `lowercase`

* `date`

* `json`

***

## Custom Pipe

```ts
@Pipe({ name: 'exclaim' })
export class ExclaimPipe {
  transform(value: string) {
    return value + '!';
  }
}
```

```html
<p>{{ "Hello" | exclaim }}</p>
```

***

# 9. 🔁 Async Pipe (VERY IMPORTANT)

Using **RxJS**:

```html
<div *ngFor="let task of tasks$ | async">
  {{ task }}
</div>
```

***

## 💡 Why?

* Auto subscribe/unsubscribe

* Cleaner code

***

# 10. 🧩 Template Control Flow (Modern Angular)

New syntax (Angular 17+):

```html
@if (tasks.length === 0) {
  <p>No tasks</p>
} @else {
  <ul>
    @for (task of tasks; track task) {
      <li>{{ task }}</li>
    }
  </ul>
}
```

***

# 11. 🧠 Best Practices

✔ Keep templates simple\
✔ Move logic to component\
✔ Use async pipe\
✔ Use trackBy for lists

***

## TrackBy Example

```html
<li *ngFor="let task of tasks; trackBy: trackById">
```

```ts
trackById(index: number, item: any) {
  return item.id;
}
```

***

# 12. 🚫 Common Mistakes

❌ Heavy logic in templates\
❌ Nested `*ngIf` chaos\
❌ Manual DOM manipulation\
❌ Not using async pipe

***

# 🧩 Mini Practice (Do This!)

Build a template:

```html
<input [(ngModel)]="task">
<button (click)="addTask()">Add</button>

<ul>
  <li *ngFor="let t of tasks; trackBy: trackByIndex">
    {{ t }}
    <button (click)="removeTask(i)">❌</button>
  </li>
</ul>

<p *ngIf="tasks.length === 0">No tasks yet</p>
```

***

# 🧠 Mental Model

```text
Template = View of your state
```

NOT:

```text
Template = Logic engine ❌
```

***

# 🚀 What’s Next?

Now you’re ready for:

* 🧠 **Angular Forms (Reactive Forms deep dive)**

* ⚡ **Signals vs RxJS in templates**

* 🏗️ **Advanced component architecture**

***

If you want, I can:

* Turn this into a **7-day template bootcamp**

* Or build a **real Angular UI step-by-step with you**

Just tell me 👍

---
id: 20260427150432
title: TypeScript Tutorial for Angular
author: Karl Schmitt
date: 2026-04-27
keywords: [ TypeScript, Angular ]
---

# TypeScript Tutorial for Angular

TypeScript is the main programming language used in Angular. If HTML templates are the “view,” then TypeScript is the **logic layer** of Angular apps.

Think of it like this:

* **HTML** = structure
* **CSS** = styling
* **TypeScript** = behavior, data, application logic

---

# 1. Why Angular Uses TypeScript

Angular relies on TypeScript because it adds:

✅ Types
✅ Classes
✅ Decorators
✅ Interfaces
✅ Better tooling / autocomplete
✅ Easier large-scale apps

Example:

```ts
let name: string = 'Karl';
let age: number = 35;
```

---

# 2. A Typical Angular Component

```ts
import { Component } from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.html'
})
export class AppComponent {
  title = 'My Angular App';
}
```

This file is TypeScript.

---

# 3. Variables and Types

```ts
let username: string = 'Karl';
let age: number = 35;
let isAdmin: boolean = true;
```

Common Angular property declarations:

```ts
export class AppComponent {
  title: string = 'Dashboard';
  count: number = 0;
  isLoading: boolean = false;
}
```

---

# 4. Type Inference

You often don’t need to write types.

```ts
title = 'Angular';
count = 10;
```

TypeScript infers:

* `title` → string
* `count` → number

Angular developers use this often.

---

# 5. Arrays

```ts
items: string[] = ['HTML', 'CSS', 'Angular'];
numbers: number[] = [1, 2, 3];
```

Useful for `@for` / `*ngFor`.

```html
<li *ngFor="let item of items">{{ item }}</li>
```

---

# 6. Objects

```ts
user = {
  name: 'Karl',
  age: 35
};
```

Template:

```html
<p>{{ user.name }}</p>
```

---

# 7. Functions / Methods

Angular components often contain methods.

```ts
export class AppComponent {
  count = 0;

  increment(): void {
    this.count++;
  }
}
```

Template:

```html
<button (click)="increment()">+</button>
<p>{{ count }}</p>
```

---

# 8. Understanding `this`

Inside classes:

```ts
this.count++;
```

Means:

> the property belonging to this component instance.

---

# 9. Classes

Angular components, services, directives use classes.

```ts
class User {
  name: string = '';
  age: number = 0;
}
```

Angular component:

```ts
export class AppComponent { }
```

---

# 10. Access Modifiers

```ts
public title = 'Hello';
private secret = 'abc';
protected token = '123';
```

Common in Angular services/components.

| Modifier  | Meaning            |
| --------- | ------------------ |
| public    | usable anywhere    |
| private   | only inside class  |
| protected | class + subclasses |

---

# 11. Constructor

Used for initialization and dependency injection.

```ts
constructor() {
  console.log('created');
}
```

Angular DI:

```ts
constructor(private http: HttpClient) {}
```

---

# 12. Interfaces

Very important in Angular.

```ts
interface User {
  id: number;
  name: string;
}
```

Use:

```ts
user: User = {
  id: 1,
  name: 'Karl'
};
```

Great for API data.

---

# 13. Optional Properties

```ts
interface User {
  id: number;
  name: string;
  email?: string;
}
```

`email` may exist or not.

---

# 14. Union Types

```ts
status: 'loading' | 'success' | 'error' = 'loading';
```

Very useful in Angular UI state.

---

# 15. Null Safety

```ts
user: User | null = null;
```

Template:

```html
{{ user?.name }}
```

Safe navigation avoids errors.

---

# 16. Generics

Used everywhere in Angular.

Example:

```ts
items: Array<string> = ['a', 'b'];
```

HttpClient:

```ts
this.http.get<User[]>('/api/users');
```

Meaning: request returns array of users.

---

# 17. Enums

```ts
enum Role {
  Admin,
  User,
  Guest
}
```

Use:

```ts
role = Role.Admin;
```

---

# 18. Readonly

```ts
readonly appName = 'Angular Bootcamp';
```

Cannot be changed later.

---

# 19. Angular Decorators

TypeScript supports decorators heavily used by Angular.

```ts
@Component({...})
@Injectable()
@Input()
@Output()
```

These add metadata.

---

# 20. Example Real Angular Component

```ts
import { Component } from '@angular/core';

interface Product {
  name: string;
  price: number;
}

@Component({
  selector: 'app-root',
  templateUrl: './app.html'
})
export class AppComponent {
  title = 'Shop';

  products: Product[] = [
    { name: 'Keyboard', price: 50 },
    { name: 'Mouse', price: 30 }
  ];

  addProduct(): void {
    this.products.push({
      name: 'Monitor',
      price: 200
    });
  }
}
```

---

# 21. Common Beginner Mistakes

## ❌ Forgeting Types

```ts
user;
```

Better:

```ts
user: User | null = null;
```

---

## ❌ Using `any`

```ts
data: any;
```

Avoid when possible.

Use:

```ts
data: User[];
```

---

## ❌ Forgetting `this`

Wrong:

```ts
count++;
```

Correct:

```ts
this.count++;
```

Inside class methods.

---

# 22. Best Types for Angular Beginners

Learn these first:

```ts
string
number
boolean
string[]
number[]
object
interface
User | null
void
```

---

# 23. Mini Practice

```ts
export class AppComponent {
  username = 'Karl';
  age = 35;
  darkMode = true;

  toggle(): void {
    this.darkMode = !this.darkMode;
  }
}
```

Template:

```html
<p>{{ username }}</p>
<p>{{ age }}</p>
<button (click)="toggle()">Toggle</button>
```

---

# 24. Mental Model for Angular

In Angular:

* Properties = data for templates
* Methods = behavior
* Interfaces = data shapes
* Constructor = dependency injection
* Decorators = Angular metadata

---

# 25. Recommended Learning Order

## Week 1

* variables
* strings
* numbers
* arrays
* objects

## Week 2

* functions
* classes
* this
* constructors

## Week 3

* interfaces
* generics
* unions
* null safety

## Week 4

* decorators
* Angular patterns

---

# 26. TypeScript You Need Most for Angular

If your goal is Angular, focus on:

✅ classes
✅ interfaces
✅ arrays of objects
✅ methods
✅ constructor
✅ access modifiers
✅ generics
✅ decorators

---

# 27. Summary

TypeScript is Angular’s engine.

Without TypeScript:

* Angular templates have no data source
* no components logic
* no services
* no routing classes

---

# 28. Mini Challenge

Build:

```ts
interface Todo {
  text: string;
  done: boolean;
}

todos: Todo[] = [
  { text: 'Learn Angular', done: false }
];
```

Then render in template.

---

# Next Best Step

Learn **TypeScript specifically for Angular Components** or **TypeScript for Angular Services**.

---

If you'd like, I can also give you a **7-Day TypeScript for Angular Bootcamp with daily exercises and mini projects** next.

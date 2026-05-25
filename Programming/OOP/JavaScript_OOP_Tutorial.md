---
id: 20260524162241
title: JavaScript OOP Tutorial using Deno
author: Karl Schmitt
date: 2026-05-24
keywords: [ JavaScript, OOP, Deno]
---

# JavaScript OOP Tutorial using Deno

Object-Oriented Programming (OOP) in JavaScript is about organizing code into **objects** that contain:

* **Data** → properties

* **Behavior** → methods

Using Deno is great because you can run modern JavaScript directly without installing Node.js packages first.

***

# 1. Setup Deno

Install Deno from:

[Deno Official Website](https://deno.com/?utm_source=chatgpt.com)

Check installation:

```bash
deno --version
```

Create a project folder:

```bash
mkdir deno-oop
cd deno-oop
```

Create a file:

```bash
touch app.js
```

Run JavaScript:

```bash
deno run app.js
```

***

# 2. What is an Object?

An object stores related information.

```js
const person = {
  name: "Alice",
  age: 30,

  greet() {
    console.log(`Hello, my name is ${this.name}`);
  }
};

console.log(person.name);
person.greet();
```

Run:

```bash
deno run app.js
```

Output:

```txt
Alice
Hello, my name is Alice
```

***

# 3. Constructor Functions (Old Style OOP)

Before classes existed, JavaScript used constructor functions.

```js
function User(name, age) {
  this.name = name;
  this.age = age;

  this.introduce = function () {
    console.log(`I am ${this.name}`);
  };
}

const user1 = new User("Karl", 35);

user1.introduce();
```

***

# 4. Modern JavaScript Classes

Classes are cleaner and easier to read.

```js
class User {
  constructor(name, age) {
    this.name = name;
    this.age = age;
  }

  introduce() {
    console.log(`Hello, I am ${this.name}`);
  }
}

const user1 = new User("Anna", 28);

console.log(user1.name);
user1.introduce();
```

***

# 5. Understanding `this`

`this` refers to the current object.

```js
class Dog {
  constructor(name) {
    this.name = name;
  }

  bark() {
    console.log(`${this.name} says woof!`);
  }
}

const dog = new Dog("Buddy");

dog.bark();
```

***

# 6. Class Properties

Objects can have many properties.

```js
class Car {
  constructor(brand, model, year) {
    this.brand = brand;
    this.model = model;
    this.year = year;
  }

  info() {
    console.log(`${this.brand} ${this.model} (${this.year})`);
  }
}

const car = new Car("Tesla", "Model 3", 2025);

car.info();
```

***

# 7. Encapsulation

Encapsulation hides internal details.

JavaScript supports private fields using `#`.

```js
class BankAccount {
  #balance = 0;

  deposit(amount) {
    this.#balance += amount;
  }

  showBalance() {
    console.log(`Balance: ${this.#balance}`);
  }
}

const account = new BankAccount();

account.deposit(100);
account.showBalance();
```

Trying to access:

```js
console.log(account.#balance);
```

causes an error because the field is private.

***

# 8. Getters and Setters

These control access to properties.

```js
class Temperature {
  constructor(celsius) {
    this._celsius = celsius;
  }

  get fahrenheit() {
    return (this._celsius * 9) / 5 + 32;
  }

  set celsius(value) {
    this._celsius = value;
  }
}

const temp = new Temperature(20);

console.log(temp.fahrenheit);

temp.celsius = 30;

console.log(temp.fahrenheit);
```

***

# 9. Inheritance

Inheritance allows one class to reuse another.

```js
class Animal {
  constructor(name) {
    this.name = name;
  }

  speak() {
    console.log(`${this.name} makes a sound`);
  }
}

class Cat extends Animal {
  speak() {
    console.log(`${this.name} meows`);
  }
}

const cat = new Cat("Milo");

cat.speak();
```

***

# 10. Using `super()`

`super()` calls the parent constructor.

```js
class Animal {
  constructor(name) {
    this.name = name;
  }
}

class Bird extends Animal {
  constructor(name, canFly) {
    super(name);

    this.canFly = canFly;
  }

  info() {
    console.log(`${this.name} can fly: ${this.canFly}`);
  }
}

const bird = new Bird("Eagle", true);

bird.info();
```

***

# 11. Polymorphism

Different classes can implement the same method differently.

```js
class Shape {
  area() {
    console.log("Calculating area...");
  }
}

class Rectangle extends Shape {
  constructor(width, height) {
    super();

    this.width = width;
    this.height = height;
  }

  area() {
    return this.width * this.height;
  }
}

const rect = new Rectangle(5, 10);

console.log(rect.area());
```

***

# 12. Static Methods

Static methods belong to the class itself.

```js
class MathHelper {
  static add(a, b) {
    return a + b;
  }
}

console.log(MathHelper.add(2, 3));
```

***

# 13. OOP + Arrays

Objects are often stored in arrays.

```js
class Product {
  constructor(name, price) {
    this.name = name;
    this.price = price;
  }
}

const products = [
  new Product("Laptop", 1200),
  new Product("Mouse", 25),
  new Product("Keyboard", 80)
];

for (const product of products) {
  console.log(product.name);
}
```

***

# 14. Splitting Classes into Files

## user.js

```js
export class User {
  constructor(name) {
    this.name = name;
  }

  greet() {
    console.log(`Hello ${this.name}`);
  }
}
```

## app.js

```js
import { User } from "./user.js";

const user = new User("Karl");

user.greet();
```

Run:

```bash
deno run app.js
```

***

# 15. A Small Real Project

## task.js

```js
export class Task {
  constructor(title) {
    this.title = title;
    this.completed = false;
  }

  complete() {
    this.completed = true;
  }
}
```

## taskManager.js

```js
export class TaskManager {
  constructor() {
    this.tasks = [];
  }

  addTask(task) {
    this.tasks.push(task);
  }

  showTasks() {
    for (const task of this.tasks) {
      console.log(task.title, task.completed);
    }
  }
}
```

## app.js

```js
import { Task } from "./task.js";
import { TaskManager } from "./taskManager.js";

const manager = new TaskManager();

const task1 = new Task("Learn OOP");
const task2 = new Task("Practice Deno");

task1.complete();

manager.addTask(task1);
manager.addTask(task2);

manager.showTasks();
```

***

# 16. Recommended OOP Concepts to Master

Focus on understanding these deeply:

1. Objects

2. Classes

3. Constructors

4. `this`

5. Methods

6. Encapsulation

7. Inheritance

8. Polymorphism

9. Composition

10. Modules

***

# 17. Composition vs Inheritance

Modern JavaScript often prefers composition.

## Inheritance

```js
class Animal {
  eat() {
    console.log("Eating");
  }
}

class Dog extends Animal {}
```

## Composition

```js
const eater = {
  eat() {
    console.log("Eating");
  }
};

const dog = {
  name: "Buddy",
  ...eater
};

dog.eat();
```

Composition is often more flexible.

***

# 18. Useful Deno Commands

Run file:

```bash
deno run app.js
```

Allow file access:

```bash
deno run --allow-read app.js
```

Watch mode:

```bash
deno run --watch app.js
```

Format code:

```bash
deno fmt
```

Lint code:

```bash
deno lint
```

***

# 19. Best Practices

* Use small focused classes

* Prefer composition over deep inheritance

* Keep methods short

* Use modules/files

* Use meaningful names

* Avoid giant “god objects”

***

# 20. Suggested Learning Path

## Beginner

* Objects

* Classes

* Methods

* Constructors

## Intermediate

* Inheritance

* Encapsulation

* Getters/setters

* Modules

## Advanced

* Composition

* Design patterns

* SOLID principles

* Event-driven architecture

***

# Practice Exercises

## Easy

1. Create a `Book` class

2. Create a `Student` class

3. Add methods to update properties

## Medium

1. Build a shopping cart

2. Build a bank system

3. Build a todo app

## Advanced

1. Build a mini game engine

2. Build a REST API with classes

3. Build a CLI application in Deno

***

# Next Topics You Could Learn

* Functional Programming in JavaScript

* TypeScript OOP

* SOLID principles

* Design Patterns

* Deno file system APIs

* Building APIs with Deno

* Testing classes in Deno

A very natural next step would be learning **TypeScript OOP with Deno**, because TypeScript adds interfaces, types, and stronger class tooling on top of JavaScript.

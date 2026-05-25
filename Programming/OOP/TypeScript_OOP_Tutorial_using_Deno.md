---
id: 20260524163346
title: TypeScript OOP Tutorial with Deno
author: Karl Schmitt
date: 2026-05-24
keywords: [ TypeScript, OOP, Deno, PowerShell]
---

# TypeScript OOP Tutorial with Deno

This tutorial teaches Object-Oriented Programming (OOP) in TypeScript using:

* TypeScript
* Deno
* PowerShell

You will learn:

1. Classes
2. Objects
3. Constructors
4. Methods
5. Access modifiers
6. Inheritance
7. Polymorphism
8. Abstract classes
9. Interfaces
10. Static members
11. Composition
12. A small real-world project

---

# 1. Install Deno

Visit:

* [Deno Official Website](https://deno.com/?utm_source=chatgpt.com)

PowerShell installation:

```powershell
irm https://deno.land/install.ps1 | iex
```

Verify installation:

```powershell
deno --version
```

---

# 2. Create Your First TypeScript File

Create a project folder:

```powershell
mkdir ts-oop
cd ts-oop
```

Create a file:

```powershell
ni main.ts
```

Open in [Visual Studio Code](https://code.visualstudio.com/?utm_source=chatgpt.com):

```powershell
code .
```

---

# 3. Your First Class

## main.ts

```typescript
class Dog {
  name: string;

  constructor(name: string) {
    this.name = name;
  }

  bark(): void {
    console.log(`${this.name} says woof!`);
  }
}

const dog1 = new Dog("Buddy");

dog1.bark();
```

Run it:

```powershell
deno run main.ts
```

Output:

```text
Buddy says woof!
```

---

# 4. Understanding the Basics

## Class

A class is a blueprint.

```typescript
class Dog {
}
```

## Object

An object is created from a class.

```typescript
const dog1 = new Dog("Buddy");
```

## Constructor

Runs automatically when creating an object.

```typescript
constructor(name: string)
```

## Method

A function inside a class.

```typescript
bark()
```

---

# 5. Access Modifiers

TypeScript supports OOP visibility control.

| Modifier  | Meaning                      |
| --------- | ---------------------------- |
| public    | Accessible everywhere        |
| private   | Accessible only inside class |
| protected | Accessible in subclasses     |

---

# Example

```typescript
class BankAccount {
  public owner: string;
  private balance: number;

  constructor(owner: string, balance: number) {
    this.owner = owner;
    this.balance = balance;
  }

  deposit(amount: number): void {
    this.balance += amount;
  }

  showBalance(): void {
    console.log(`Balance: ${this.balance}`);
  }
}

const acc = new BankAccount("Karl", 1000);

acc.deposit(500);

acc.showBalance();
```

Run:

```powershell
deno run main.ts
```

---

# 6. Inheritance

Inheritance allows one class to reuse another class.

---

## Example

```typescript
class Animal {
  name: string;

  constructor(name: string) {
    this.name = name;
  }

  move(): void {
    console.log(`${this.name} moves`);
  }
}

class Cat extends Animal {
  meow(): void {
    console.log(`${this.name} says meow`);
  }
}

const cat = new Cat("Luna");

cat.move();
cat.meow();
```

---

# 7. Method Overriding

Child classes can replace parent behavior.

```typescript
class Animal {
  speak(): void {
    console.log("Animal sound");
  }
}

class Dog extends Animal {
  override speak(): void {
    console.log("Woof!");
  }
}

const dog = new Dog();

dog.speak();
```

---

# 8. Polymorphism

Different classes can use the same method name differently.

```typescript
class Bird {
  speak(): void {
    console.log("Tweet");
  }
}

class Cow {
  speak(): void {
    console.log("Moo");
  }
}

const animals = [new Bird(), new Cow()];

for (const animal of animals) {
  animal.speak();
}
```

---

# 9. Getters and Setters

Useful for controlled access.

```typescript
class Person {
  private _age = 0;

  get age(): number {
    return this._age;
  }

  set age(value: number) {
    if (value >= 0) {
      this._age = value;
    }
  }
}

const p = new Person();

p.age = 30;

console.log(p.age);
```

---

# 10. Static Members

Static members belong to the class itself.

```typescript
class MathHelper {
  static pi = 3.14159;

  static square(x: number): number {
    return x * x;
  }
}

console.log(MathHelper.pi);
console.log(MathHelper.square(4));
```

---

# 11. Abstract Classes

Abstract classes are templates for subclasses.

```typescript
abstract class Shape {
  abstract area(): number;
}

class Rectangle extends Shape {
  constructor(
    private width: number,
    private height: number
  ) {
    super();
  }

  area(): number {
    return this.width * this.height;
  }
}

const rect = new Rectangle(5, 10);

console.log(rect.area());
```

---

# 12. Interfaces

Interfaces define contracts.

```typescript
interface Logger {
  log(message: string): void;
}

class ConsoleLogger implements Logger {
  log(message: string): void {
    console.log(message);
  }
}

const logger = new ConsoleLogger();

logger.log("Hello");
```

---

# 13. Composition

Composition means building classes from other classes.

```typescript
class Engine {
  start(): void {
    console.log("Engine started");
  }
}

class Car {
  private engine: Engine;

  constructor() {
    this.engine = new Engine();
  }

  drive(): void {
    this.engine.start();
    console.log("Driving");
  }
}

const car = new Car();

car.drive();
```

---

# 14. Mini Project — RPG Character System

---

## character.ts

```typescript
export class Character {
  constructor(
    public name: string,
    protected health: number
  ) {}

  takeDamage(amount: number): void {
    this.health -= amount;

    console.log(
      `${this.name} takes ${amount} damage`
    );
  }

  showHealth(): void {
    console.log(
      `${this.name} health: ${this.health}`
    );
  }
}
```

---

## warrior.ts

```typescript
import { Character } from "./character.ts";

export class Warrior extends Character {
  attack(): void {
    console.log(`${this.name} attacks with sword`);
  }
}
```

---

## mage.ts

```typescript
import { Character } from "./character.ts";

export class Mage extends Character {
  castSpell(): void {
    console.log(`${this.name} casts fireball`);
  }
}
```

---

## main.ts

```typescript
import { Warrior } from "./warrior.ts";
import { Mage } from "./mage.ts";

const warrior = new Warrior("Thor", 100);
const mage = new Mage("Merlin", 80);

warrior.attack();
warrior.takeDamage(20);
warrior.showHealth();

console.log();

mage.castSpell();
mage.takeDamage(15);
mage.showHealth();
```

Run:

```powershell
deno run main.ts
```

---

# 15. Useful PowerShell Commands

## Create files

```powershell
ni main.ts
```

## Create folders

```powershell
mkdir models
```

## Run TypeScript

```powershell
deno run main.ts
```

## Run with permissions

```powershell
deno run --allow-read main.ts
```

## Watch mode

```powershell
deno task dev
```

---

# 16. Recommended Project Structure

```text
project/
│
├── main.ts
├── models/
│   ├── user.ts
│   └── product.ts
│
├── services/
│   └── database.ts
│
└── utils/
    └── logger.ts
```

---

# 17. OOP Best Practices

## Keep classes small

One responsibility per class.

## Prefer composition over inheritance

Composition is often simpler.

## Use private fields

Protect internal state.

## Use interfaces

They make code flexible.

## Avoid giant classes

Split responsibilities.

---

# 18. Common Deno Commands

## Run file

```powershell
deno run app.ts
```

## Auto reload

```powershell
deno run --watch app.ts
```

## Format code

```powershell
deno fmt
```

## Lint code

```powershell
deno lint
```

## Type check

```powershell
deno check main.ts
```

---

# 19. Practice Ideas

Build these projects:

1. Library system
2. Banking system
3. RPG game
4. Todo application
5. Inventory manager
6. School management system
7. Chess pieces simulation
8. REST API with classes
9. File parser
10. Shopping cart system

---

# 20. Next Topics

After mastering OOP, learn:

* Generics
* Dependency Injection
* Design Patterns
* SOLID principles
* Async programming
* File system APIs
* REST APIs
* Testing with Deno
* Clean Architecture

---

# Excellent Resources

* [TypeScript Documentation](https://www.typescriptlang.org/docs/?utm_source=chatgpt.com)
* [Deno Documentation](https://docs.deno.com/?utm_source=chatgpt.com)
* [PowerShell Documentation](https://learn.microsoft.com/powershell/?utm_source=chatgpt.com)
* [MDN JavaScript Classes Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes?utm_source=chatgpt.com)

---

# Suggested Learning Path

## Week 1

* Classes
* Objects
* Constructors
* Methods

## Week 2

* Inheritance
* Polymorphism
* Access modifiers

## Week 3

* Interfaces
* Abstract classes
* Composition

## Week 4

* Build a complete project

---

If you want, I can also provide:

* A **7-Day TypeScript OOP Bootcamp**
* A **30-Day TypeScript OOP Mastery Plan**
* A **TypeScript Design Patterns tutorial**
* A **SOLID Principles deep dive**
* A **Deno OOP project tutorial**
* A **TypeScript interfaces deep dive**
* A **real-world REST API architecture with OOP**

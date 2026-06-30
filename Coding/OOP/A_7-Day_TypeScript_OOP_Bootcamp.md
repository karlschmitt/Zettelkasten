---
id: 20260524174835
title: 7-Day TypeScript OOP Bootcamp
author: Karl Schmitt
date: 2026-05-24
keywords: []
---


# 7-Day TypeScript OOP Bootcamp

Using TypeScript + Deno + PowerShell

This bootcamp is designed for hands-on learning.

Each day includes:

* Theory

* Practice

* Mini exercises

* Project work

* PowerShell commands

Goal after 7 days:

* Understand OOP deeply

* Build structured TypeScript applications

* Use Deno comfortably

* Organize larger codebases

* Think like a software engineer

***

# Bootcamp Project

Throughout the week you will build:

# RPG Battle System

Features:

* Characters

* Warriors

* Mages

* Inventory

* Weapons

* Enemies

* Battles

* Save/load system

* Modular architecture

***

# Folder Setup

Create your workspace.

```powershell
mkdir ts-oop-bootcamp
cd ts-oop-bootcamp
code .
```

Create folders:

```powershell
mkdir src
mkdir src\models
mkdir src\services
mkdir src\utils
mkdir src\game
```

***

# Day 1 — Classes and Objects

## Goals

Learn:

* Classes

* Objects

* Constructors

* Properties

* Methods

* this keyword

***

# Theory

A class is a blueprint.

An object is a real instance.

Example:

```typescript
class Dog {
  name: string;

  constructor(name: string) {
    this.name = name;
  }

  bark(): void {
    console.log(`${this.name} says woof`);
  }
}
```

***

# Practice 1 — Create Your First Class

## src/main.ts

```typescript
class Hero {
  name: string;
  health: number;

  constructor(name: string, health: number) {
    this.name = name;
    this.health = health;
  }

  introduce(): void {
    console.log(
      `I am ${this.name} with ${this.health} HP`
    );
  }
}

const hero1 = new Hero("Arthas", 100);

hero1.introduce();
```

Run:

```powershell
deno run src/main.ts
```

***

# Exercise

Create:

* A Car class

* A Book class

* A Monster class

Each should have:

* 2–3 properties

* 1 method

***

# Mini Project

Create:

```text
Player
Enemy
NPC
```

classes.

***

# Day 2 — Access Modifiers + Encapsulation

## Goals

Learn:

* public

* private

* protected

* getters/setters

* encapsulation

***

# Theory

Encapsulation protects internal data.

```typescript
class BankAccount {
  private balance: number = 0;

  deposit(amount: number): void {
    this.balance += amount;
  }

  showBalance(): void {
    console.log(this.balance);
  }
}
```

***

# Practice

## src/models/player.ts

```typescript
export class Player {
  private health: number;

  constructor(
    public name: string,
    health: number
  ) {
    this.health = health;
  }

  takeDamage(amount: number): void {
    this.health -= amount;

    if (this.health < 0) {
      this.health = 0;
    }
  }

  getHealth(): number {
    return this.health;
  }
}
```

***

# src/main.ts

```typescript
import { Player } from "./models/player.ts";

const player = new Player("Knight", 100);

player.takeDamage(25);

console.log(player.getHealth());
```

***

# Exercise

Add:

* heal()

* isAlive()

* setHealth()

***

# PowerShell

Run in watch mode:

```powershell
deno run --watch src/main.ts
```

***

# Day 3 — Inheritance

## Goals

Learn:

* extends

* super()

* parent/child classes

* method reuse

***

# Theory

Inheritance creates specialized classes.

```typescript
class Animal {}
class Dog extends Animal {}
```

***

# Practice

## src/models/character.ts

```typescript
export class Character {
  constructor(
    public name: string,
    protected health: number
  ) {}

  showStats(): void {
    console.log(
      `${this.name}: ${this.health} HP`
    );
  }
}
```

***

## src/models/warrior.ts

```typescript
import { Character } from "./character.ts";

export class Warrior extends Character {
  attack(): void {
    console.log(
      `${this.name} attacks with sword`
    );
  }
}
```

***

## src/models/mage.ts

```typescript
import { Character } from "./character.ts";

export class Mage extends Character {
  castSpell(): void {
    console.log(
      `${this.name} casts fireball`
    );
  }
}
```

***

# Exercise

Create:

* Archer

* Healer

* Dragon

***

# Mini Project

Add:

* Mana

* Strength

* Defense

***

# Day 4 — Polymorphism + Method Overriding

## Goals

Learn:

* override

* polymorphism

* shared interfaces

* dynamic behavior

***

# Theory

Different classes can behave differently through the same method.

***

# Practice

## character.ts

```typescript
export class Character {
  attack(): void {
    console.log("Basic attack");
  }
}
```

***

## warrior.ts

```typescript
import { Character } from "./character.ts";

export class Warrior extends Character {
  override attack(): void {
    console.log("Sword slash");
  }
}
```

***

## mage.ts

```typescript
import { Character } from "./character.ts";

export class Mage extends Character {
  override attack(): void {
    console.log("Fireball");
  }
}
```

***

## main.ts

```typescript
import { Warrior } from "./models/warrior.ts";
import { Mage } from "./models/mage.ts";

const party = [
  new Warrior(),
  new Mage()
];

for (const member of party) {
  member.attack();
}
```

***

# Exercise

Create:

* IceMage

* Paladin

* Assassin

with unique attacks.

***

# Day 5 — Abstract Classes + Interfaces

## Goals

Learn:

* abstract

* interface

* contracts

* reusable architecture

***

# Theory

Interfaces define required behavior.

Abstract classes define partial implementation.

***

# Practice

## damageable.ts

```typescript
export interface Damageable {
  takeDamage(amount: number): void;
}
```

***

## character.ts

```typescript
import { Damageable } from "./damageable.ts";

export abstract class Character
implements Damageable {

  constructor(
    protected health: number
  ) {}

  abstract attack(): void;

  takeDamage(amount: number): void {
    this.health -= amount;
  }
}
```

***

## warrior.ts

```typescript
import { Character } from "./character.ts";

export class Warrior extends Character {
  attack(): void {
    console.log("Warrior attack");
  }
}
```

***

# Exercise

Create:

* Flyable interface

* Tradeable interface

* Boss abstract class

***

# Mini Project

Add:

* Enemy interface

* Loot system

* Damage calculations

***

# Day 6 — Composition + Static Members

## Goals

Learn:

* composition

* has-a relationships

* utility classes

* static methods

***

# Theory

Composition is often better than inheritance.

Instead of:

```text
Car IS Engine
```

Use:

```text
Car HAS Engine
```

***

# Practice

## weapon.ts

```typescript
export class Weapon {
  constructor(
    public name: string,
    public damage: number
  ) {}
}
```

***

## player.ts

```typescript
import { Weapon } from "./weapon.ts";

export class Player {
  constructor(
    public name: string,
    public weapon: Weapon
  ) {}

  attack(): void {
    console.log(
      `${this.name} attacks with ${this.weapon.name}`
    );
  }
}
```

***

## main.ts

```typescript
import { Weapon } from "./models/weapon.ts";
import { Player } from "./models/player.ts";

const sword = new Weapon("Excalibur", 50);

const player = new Player("Knight", sword);

player.attack();
```

***

# Static Example

```typescript
class GameMath {
  static randomDamage(): number {
    return Math.floor(Math.random() * 10);
  }
}

console.log(GameMath.randomDamage());
```

***

# Exercise

Create:

* Armor

* Inventory

* Potion system

using composition.

***

# Day 7 — Final Project Architecture

## Goals

Build a modular OOP project.

***

# Final Structure

```text
src/
│
├── main.ts
│
├── models/
│   ├── character.ts
│   ├── warrior.ts
│   ├── mage.ts
│   ├── weapon.ts
│   ├── armor.ts
│   └── inventory.ts
│
├── services/
│   ├── battle-service.ts
│   ├── save-service.ts
│   └── game-service.ts
│
└── utils/
    ├── logger.ts
    └── random.ts
```

***

# Battle Service

## services/battle-service.ts

```typescript
export class BattleService {
  static fight(
    attacker: string,
    defender: string
  ): void {
    console.log(
      `${attacker} attacks ${defender}`
    );
  }
}
```

***

# Save Service

## services/save-service.ts

```typescript
export class SaveService {
  static save(): void {
    console.log("Game saved");
  }
}
```

***

# Main File

```typescript
import { Warrior } from "./models/warrior.ts";

const hero = new Warrior();

hero.attack();
```

***

# Final Exercises

Add:

* Critical hits

* Experience points

* Level system

* Shops

* Gold

* Quests

* Boss fights

* JSON save files

***

# Recommended Daily Workflow

***

# 1. Start Project

```powershell
cd ts-oop-bootcamp
```

***

# 2. Run Application

```powershell
deno run src/main.ts
```

***

# 3. Watch Mode

```powershell
deno run --watch src/main.ts
```

***

# 4. Format Code

```powershell
deno fmt
```

***

# 5. Lint

```powershell
deno lint
```

***

# 6. Type Check

```powershell
deno check src/main.ts
```

***

# Daily Study Routine

## 30 Minutes

Read theory.

## 60 Minutes

Code examples manually.

## 30 Minutes

Experiment independently.

## 30 Minutes

Refactor your code.

***

# Important OOP Principles

***

# Encapsulation

Protect internal state.

***

# Inheritance

Reuse shared behavior.

***

# Polymorphism

Different behavior through shared APIs.

***

# Abstraction

Hide complexity.

***

# Composition

Build systems from smaller parts.

***

# Best Practices

## Use small classes

Avoid giant “god classes”.

## Prefer composition

Inheritance can become rigid.

## Use interfaces heavily

They improve flexibility.

## Keep methods focused

One job per method.

## Separate responsibilities

Models, services, utilities.

***

# Recommended Next Steps

After this bootcamp:

1. SOLID principles

2. Design patterns

3. Dependency Injection

4. Testing with Deno

5. REST APIs

6. Clean Architecture

7. Event-driven systems

8. CQRS basics

9. Repository pattern

10. Domain-driven design

***

# Excellent Resources

* [TypeScript Docs](https://www.typescriptlang.org/docs/?utm_source=chatgpt.com)

* [Deno Docs](https://docs.deno.com/?utm_source=chatgpt.com)

* [PowerShell Documentation](https://learn.microsoft.com/powershell/?utm_source=chatgpt.com)

* [MDN JavaScript Classes](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes?utm_source=chatgpt.com)

***

If you want, I can also provide:

* A **30-Day TypeScript OOP Mastery Plan**

* A **TypeScript Design Patterns Bootcamp**

* A **SOLID Principles Deep Dive**

* A **Clean Architecture tutorial using Deno**

* A **TypeScript Generics Bootcamp**

* A **Dependency Injection tutorial**

* A **real-world REST API using OOP + Deno**



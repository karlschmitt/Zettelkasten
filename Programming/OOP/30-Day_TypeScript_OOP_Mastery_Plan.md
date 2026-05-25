---
id: 20260524180405
title: 30-Day TypeScript OOP Mastery Plan
author: Karl Schmitt
date: 2026-05-24
keywords: []
---

# 30-Day TypeScript OOP Mastery Plan

Using TypeScript + Deno + PowerShell

This roadmap takes you from:

```text
Beginner → Intermediate → Advanced → Architecture Level
```

By the end you will be able to:

* Design large OOP systems
* Build modular applications
* Use TypeScript professionally
* Structure scalable Deno projects
* Apply SOLID principles
* Use design patterns
* Build real-world backend systems

---

# Overall Learning Structure

| Week   | Focus                  |
| ------ | ---------------------- |
| Week 1 | OOP Foundations        |
| Week 2 | Intermediate OOP       |
| Week 3 | Advanced Architecture  |
| Week 4 | Real-World Engineering |

---

# Main Project

During the 30 days you will gradually build:

# Fantasy RPG Backend Engine

Features:

* Characters
* Inventory
* Equipment
* Quests
* Shops
* Enemies
* Combat
* Save system
* File storage
* Services
* Event system
* Architecture layers

---

# Recommended Daily Routine

| Activity        | Time   |
| --------------- | ------ |
| Read theory     | 30 min |
| Code examples   | 60 min |
| Build exercises | 60 min |
| Refactor        | 30 min |

---

# Initial Project Setup

---

# Install Deno

* [Deno Official Website](https://deno.com/?utm_source=chatgpt.com)

PowerShell:

```powershell id="lm4xxj"
irm https://deno.land/install.ps1 | iex
```

Verify:

```powershell id="7l6i6k"
deno --version
```

---

# Create Project

```powershell id="r8c6u7"
mkdir ts-oop-mastery
cd ts-oop-mastery
code .
```

---

# Create Structure

```powershell id="y5x3up"
mkdir src
mkdir src\models
mkdir src\services
mkdir src\utils
mkdir src\interfaces
mkdir src\repositories
mkdir src\events
mkdir src\config
mkdir src\storage
```

---

# WEEK 1 — OOP FOUNDATIONS

---

# Day 1 — Classes and Objects

## Learn

* Classes
* Objects
* Properties
* Methods
* Constructors
* this keyword

---

# Build

Create:

```text
Player
Enemy
NPC
Weapon
```

classes.

---

# Exercises

Add:

* health
* damage
* attack()
* move()

---

# Day 2 — Access Modifiers

## Learn

* public
* private
* protected
* readonly

---

# Practice

Create:

```text
BankAccount
Inventory
CharacterStats
```

with protected internal state.

---

# Exercise

Use getters/setters.

---

# Day 3 — Encapsulation

## Learn

Encapsulation protects internal logic.

---

# Build

Create:

```text
HealthSystem
ManaSystem
LevelSystem
```

---

# Goals

Prevent invalid values.

Example:

```typescript id="2ndzib"
if (health < 0) {
  health = 0;
}
```

---

# Day 4 — Inheritance

## Learn

* extends
* super()
* method reuse

---

# Build

```text
Character
├── Warrior
├── Mage
├── Archer
└── Healer
```

---

# Exercise

Add specialized attacks.

---

# Day 5 — Polymorphism

## Learn

* override
* dynamic dispatch
* shared APIs

---

# Build

Shared:

```typescript id="xk1k6j"
attack()
```

Different behavior per class.

---

# Day 6 — Abstract Classes

## Learn

* abstract methods
* abstract classes
* reusable templates

---

# Build

```typescript id="ttd0a2"
abstract class Character
```

---

# Exercise

Force subclasses to implement:

```typescript id="k5pj7n"
attack()
specialMove()
```

---

# Day 7 — Interfaces

## Learn

Interfaces define contracts.

---

# Build Interfaces

```text
Damageable
Movable
Tradeable
Lootable
Saveable
```

---

# Mini Project

Create:

```text
BossEnemy
Merchant
Chest
```

using interfaces.

---

# WEEK 2 — INTERMEDIATE OOP

---

# Day 8 — Composition

## Learn

Prefer:

```text
HAS-A
```

instead of:

```text
IS-A
```

---

# Build

```text
Player HAS Weapon
Player HAS Armor
Player HAS Inventory
```

---

# Day 9 — Static Members

## Learn

* static methods
* utility classes

---

# Build

```text
GameMath
RandomGenerator
DamageCalculator
```

---

# Day 10 — File Organization

## Learn

Modular project structure.

---

# Refactor

Split code into:

```text
models/
services/
utils/
interfaces/
```

---

# Day 11 — Dependency Injection Basics

## Learn

Inject dependencies instead of hardcoding them.

---

# Example

Instead of:

```typescript id="06mn3x"
this.weapon = new Sword();
```

Use:

```typescript id="7n0xwm"
constructor(weapon: Weapon)
```

---

# Day 12 — Services

## Build

```text
BattleService
InventoryService
QuestService
SaveService
```

---

# Day 13 — Utility Systems

## Build

```text
Logger
Randomizer
Validator
ConfigLoader
```

---

# Day 14 — Error Handling

## Learn

* try/catch
* custom errors
* validation

---

# Build

```text
InvalidMoveError
InvalidInventoryError
SaveGameError
```

---

# WEEK 3 — ADVANCED OOP + ARCHITECTURE

---

# Day 15 — Generics

## Learn

Type-safe reusable code.

---

# Build

```typescript id="um4y9w"
class Repository<T>
```

---

# Exercise

Create generic:

```text
Inventory<T>
Storage<T>
Cache<T>
```

---

# Day 16 — Repository Pattern

## Learn

Separate storage logic.

---

# Build

```text
PlayerRepository
QuestRepository
ItemRepository
```

---

# Day 17 — JSON Persistence

## Learn

Use Deno file APIs.

---

# Build

Save/load player data.

---

# Example

```typescript id="4mbv50"
await Deno.writeTextFile(
  "save.json",
  JSON.stringify(data)
);
```

---

# PowerShell

Run with permissions:

```powershell id="16m4dr"
deno run --allow-read --allow-write src/main.ts
```

---

# Day 18 — Event Systems

## Build

```text
EventBus
GameEvents
BattleEvents
```

---

# Example Events

```text
PLAYER_DIED
LEVEL_UP
ITEM_FOUND
QUEST_COMPLETED
```

---

# Day 19 — Factory Pattern

## Learn

Object creation abstraction.

---

# Build

```text
CharacterFactory
EnemyFactory
WeaponFactory
```

---

# Day 20 — Singleton Pattern

## Learn

One shared instance.

---

# Build

```text
GameConfig
DatabaseConnection
Logger
```

---

# Day 21 — Strategy Pattern

## Learn

Swap algorithms dynamically.

---

# Build

Combat strategies:

```text
MeleeAttack
MagicAttack
RangedAttack
```

---

# WEEK 4 — PROFESSIONAL ENGINEERING

---

# Day 22 — SOLID Principles

Learn:

* Single Responsibility
* Open/Closed
* Liskov Substitution
* Interface Segregation
* Dependency Inversion

---

# Exercise

Refactor old code using SOLID.

---

# Day 23 — DTOs and Mapping

## Learn

Separate internal models from external data.

---

# Build

```text
PlayerDTO
InventoryDTO
QuestDTO
```

---

# Day 24 — Validation Layer

## Build

```text
PlayerValidator
ItemValidator
QuestValidator
```

---

# Day 25 — State Management

## Build

```text
GameState
BattleState
MenuState
```

---

# Day 26 — Async Programming

## Learn

* async/await
* promises
* file operations

---

# Build

Async save system.

---

# Day 27 — Clean Architecture Basics

## Learn

Separate:

```text
Domain
Application
Infrastructure
Presentation
```

---

# Refactor Project

---

# Day 28 — Testing

## Learn

Testing with Deno.

* Unit tests
* Assertions
* Mocking basics

---

# Example

```typescript id="6pdjlwm"
Deno.test("damage works", () => {
  // test logic
});
```

Run:

```powershell id="ow03nw"
deno test
```

---

# Day 29 — Full Refactor Day

## Goals

Improve:

* naming
* structure
* interfaces
* services
* folder layout

---

# Add

* comments
* logging
* configuration
* reusable utilities

---

# Day 30 — Final Architecture Project

---

# Build Full System

Features:

```text
Players
Enemies
Combat
Inventory
Shops
Quests
Save System
Events
Factories
Repositories
Validation
```

---

# Final Folder Structure

```text
src/
│
├── main.ts
│
├── domain/
│   ├── models/
│   ├── interfaces/
│   └── services/
│
├── application/
│   ├── use-cases/
│   └── dto/
│
├── infrastructure/
│   ├── repositories/
│   ├── storage/
│   └── config/
│
├── presentation/
│   └── cli/
│
└── shared/
    ├── utils/
    ├── errors/
    └── events/
```

---

# Daily PowerShell Commands

---

# Run App

```powershell id="4q9hm9"
deno run src/main.ts
```

---

# Watch Mode

```powershell id="jlwmjh"
deno run --watch src/main.ts
```

---

# Allow File Access

```powershell id="g8xf0v"
deno run --allow-read --allow-write src/main.ts
```

---

# Format

```powershell id="x4khku"
deno fmt
```

---

# Lint

```powershell id="fz4xbr"
deno lint
```

---

# Type Check

```powershell id="3zlc5o"
deno check src/main.ts
```

---

# Run Tests

```powershell id="7nn1a7"
deno test
```

---

# Important OOP Concepts to Master

| Concept              | Why Important            |
| -------------------- | ------------------------ |
| Encapsulation        | Protects state           |
| Inheritance          | Reuses code              |
| Polymorphism         | Flexible behavior        |
| Abstraction          | Hides complexity         |
| Composition          | Better architecture      |
| Interfaces           | Decouples systems        |
| Dependency Injection | Improves scalability     |
| SOLID                | Professional engineering |

---

# Recommended Mini Projects

Build these after Day 30:

1. Turn-based RPG
2. Todo backend
3. Banking system
4. Chess engine
5. Shop inventory system
6. REST API
7. File parser
8. Chat application
9. Blog backend
10. Task scheduler

---

# Recommended Next Topics

After mastering OOP:

* Design Patterns
* CQRS
* Event-Driven Architecture
* Domain-Driven Design
* Hexagonal Architecture
* Microservices
* REST APIs with Hono
* Authentication systems
* WebSockets
* Database architecture

---

# Excellent Resources

* [TypeScript Documentation](https://www.typescriptlang.org/docs/?utm_source=chatgpt.com)
* [Deno Documentation](https://docs.deno.com/?utm_source=chatgpt.com)
* [PowerShell Documentation](https://learn.microsoft.com/powershell/?utm_source=chatgpt.com)
* [MDN JavaScript Classes Guide](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes?utm_source=chatgpt.com)

---

If you want, I can also provide:

* A **TypeScript Design Patterns Bootcamp**
* A **SOLID Principles Deep Dive**
* A **Dependency Injection tutorial**
* A **Repository Pattern deep dive**
* A **Clean Architecture tutorial**
* A **DDD tutorial using Deno**
* A **REST API project using OOP + Deno + Hono**
* A **Testing tutorial with Deno**

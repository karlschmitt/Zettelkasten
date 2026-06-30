---
id: 20260424171516
title: How to learn Angular dependency injections
autor: Karl Schmitt
date: 2026-04-24
keywords: [ Angular, DS]
---

# How to learn Angular dependecy injections?

Dependency Injection (DI) in Angular looks abstract at first—but it becomes simple once you **see it as a pattern, not magic**.

Let’s make it practical and learn it the right way.

***

# 🧠 What Dependency Injection _really_ is

Forget theory for a second.

👉 DI means:

> “Don’t create things yourself—ask Angular to give them to you.”

***

## ❌ Without DI (bad pattern)

```ts
const userService = new UserService();
```

* Hard to test

* Not reusable

* Multiple instances everywhere

***

## ✅ With DI (Angular way)

```ts
constructor(private userService: UserService) {}
```

👉 Angular creates and injects it for you.

***

# 🧩 Mental Model (very important)

Think of Angular as a **factory** 🏭

* You say: “I need a `UserService`”

* Angular says: “Here you go”

You don’t care:

* how it’s created

* where it comes from

***

# 🧭 How to _learn_ DI step-by-step

Don’t try to “understand everything” at once.\
Instead, build it in layers:

***

## 🥇 Step 1 — Use a Service (No Thinking)

Create one:

```bash
ng generate service counter
```

Use it:

```ts
constructor(private counterService: CounterService) {}
```

👉 That’s already DI.

***

## 🥈 Step 2 — See Shared State 🔥

Put state in service:

```ts
count = 0;

increase() {
  this.count++;
}
```

Use in TWO components.

👉 Result:

* Both components share the same value

💡 This is your first “aha” moment:

> DI gives you **shared instances**

***

## 🥉 Step 3 — Understand `providedIn`

```ts
@Injectable({
  providedIn: 'root'
})
```

👉 Means:

* One global instance (singleton)

***

## 🧪 Experiment

Change it to component-level:

```ts
@Component({
  providers: [CounterService]
})
```

👉 Now:

* Each component gets its own instance

💡 Second “aha”:

> Scope controls instance behavior

***

## 🏗️ Step 4 — Inject Multiple Services

```ts
constructor(
  private userService: UserService,
  private logger: LoggerService
) {}
```

👉 Angular resolves all dependencies automatically.

***

## 🔄 Step 5 — Combine with HTTP

```ts
constructor(private http: HttpClient) {}
```

👉 Even Angular’s own tools use DI.

***

# 🧠 The Only 4 Things You Really Need to Know

If you remember only this, you’re good:

1. **Services hold logic/state**

2. **Constructor = where injection happens**

3. **`providedIn: 'root'` = singleton**

4. **Angular manages creation**

***

# ⚠️ Common Mistakes

❌ Creating services manually\
❌ Putting logic in components\
❌ Not understanding scope (`providers` vs `root`)

***

# 🧪 Best Way to Practice (Do This!)

Build a **Shared Counter App**:

### Step 1

* One service with `count`

### Step 2

* Two components:

  * Counter A

  * Counter B

### Step 3

* Both use same service

👉 Click in A → B updates automatically

***

# 🚀 Next Level (Optional)

Once comfortable, explore:

* Injection tokens

* Hierarchical injectors

* Lazy-loaded services

***

# 🧠 Simple Analogy

Think of DI like a **restaurant** 🍽️

* You don’t cook your own food

* You order → it’s delivered

Angular = kitchen\
Service = meal

***

# 🔁 Your Learning Loop

1. Inject service

2. Use it

3. Share it

4. Break scope

5. Observe behavior

***

If you want, I can give you:

👉 a **3-day deep-dive DI mini bootcamp**\
👉 or **advanced DI patterns used in real Angular apps**

Just tell me 👍

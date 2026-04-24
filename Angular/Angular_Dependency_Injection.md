---
id: 20260424170324
title: Angular Dependency Injection
author: Karl Schmitt
date: 2024-04-24
keywords: [ Angular, DI ]
---

# Angular Dependency Injection

**Dependency Injection (DI)** is a design pattern where a class requests its dependencies from an external source rather than creating them itself.

In Angular, DI is the "glue" that connects your components to the data and logic they need (Services).

---

### 1. The Analogy: The Restaurant
Imagine you are a customer (a **Component**) at a restaurant.

*   **Without DI:** You have to go into the kitchen, find the ingredients, cook the meal yourself, and then sit down to eat. You are now responsible for knowing *how* to cook. If the kitchen changes its layout, you are in trouble.
*   **With DI:** You sit at the table and tell the waiter (the **Injector**), "I want a Pizza." The waiter brings it to you. You don't know how it was made or who made it; you just use it.

---

### 2. Why use Dependency Injection?
1.  **Decoupling:** A component doesn't need to know how to create a service (e.g., how to configure an API URL). It just uses the service.
2.  **Testability:** During testing, you can easily "swap" a real service for a "mock" service (a fake one that doesn't actually call an API).
3.  **Reusability:** One service can be injected into 50 different components.
4.  **Singleton Pattern:** By default, Angular creates only **one instance** of a service for the whole app. This makes it easy to share data between components.

---

### 3. The Three Key Parts of Angular DI

#### A. The Dependency (The Service)
This is the class that contains the logic you want to share. It is marked with the `@Injectable()` decorator.
```typescript
@Injectable({
  providedIn: 'root' // This makes it available everywhere
})
export class LoggerService {
  log(msg: string) { console.log(msg); }
}
```

#### B. The Provider (The Instruction)
The provider tells the DI system **how** to create the dependency. In the example above, `providedIn: 'root'` is the provider instruction. It tells Angular: "Create one instance of this and share it globally."

#### C. The Injector (The Delivery)
The Injector is the tool that looks at your component's constructor and figures out what you need.
```typescript
export class UserComponent {
  // We "inject" the service here via the constructor
  constructor(private logger: LoggerService) {}

  login() {
    this.logger.log('User logged in!');
  }
}
```

---

### 4. Hierarchical Injection (Scoping)
Angular’s DI system is **hierarchical**. Where you "provide" the service determines how long it lives and who can see it:

1.  **Root Level (`providedIn: 'root'`):** 
    *   The service is a **Singleton**. 
    *   The entire app shares one instance. 
    *   *Used for: Most services (Auth, APIs).*

2.  **Component Level (`providers: [MyService]`):** 
    *   Each time that component is created, a **new instance** of the service is created. 
    *   The service is destroyed when the component is destroyed.
    *   *Used for: Services that hold state specific to one UI widget.*

---

### 5. Summary of the Workflow
1.  **Define** a class with `@Injectable()`.
2.  **Register** it in the `providedIn` property or a `providers` array.
3.  **Inject** it by adding it as a parameter in a class `constructor`.
4.  **Angular** does the work of finding the instance and handing it to you.

### What about the `inject()` function?
In modern Angular (v14+), you can also inject dependencies without a constructor using the `inject` function:
```typescript
export class UserComponent {
  private logger = inject(LoggerService); // Exactly the same as constructor injection
}
```
This is becoming the preferred way in modern Angular development because it works better with **Standalone Components** and **Functional Guards**.
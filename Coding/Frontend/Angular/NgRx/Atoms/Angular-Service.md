---
id: 20260804135932
title: Angular Service
author: Karl Schmitt
date: 2026-06-04
keywords: [Angular, Service]
---

# Angular Service

In Angular, a **Service** is a class that contains logic, data, or functions that are not directly related to a specific view (UI). 

While Components are responsible for the User Interface (the "look and feel"), Services are responsible for the "behind-the-scenes" work, such as fetching data from a server, logging, or managing state across multiple components.

---

### 1. Why do we use Services?
*   **Separation of Concerns:** Components should be "lean." They shouldn't contain complex business logic or code to fetch data. By moving that code into a service, the component stays focused on the UI.
*   **Reusability:** You can write a piece of logic (like a currency converter or an API call) once in a service and use it in 10 different components.
*   **Sharing Data:** Services are the primary way to share information between components that aren't directly related (e.g., siblings or components in different routes).
*   **Singletons:** By default, Angular services are **Singletons**. This means Angular creates only *one* instance of the service for the entire application, ensuring everyone is looking at the same data.

### 2. The `@Injectable()` Decorator
Every Angular service is a class decorated with `@Injectable()`. This tells Angular that this class can be "injected" into other classes (like components) via **Dependency Injection**.

```typescript
import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root', // This makes the service available globally as a singleton
})
export class LoggerService {
  log(message: string) {
    console.log(`LOG: ${message}`);
  }
}
```

### 3. How to use a Service in a Component
To use a service, you "inject" it into the component's **constructor**. Angular’s Dependency Injection system sees the type you requested and provides the instance automatically.

```typescript
import { Component } from '@angular/core';
import { LoggerService } from './logger.service';

@Component({
  selector: 'app-user',
  template: `<button (click)="notify()">Click Me</button>`
})
export class UserComponent {
  // Injecting the service here:
  constructor(private logger: LoggerService) {}

  notify() {
    this.logger.log('The button was clicked!');
  }
}
```

### 4. Common Use Cases
1.  **HTTP Requests:** Using Angular's `HttpClient` to fetch data from a REST API.
2.  **Data Storage:** Holding a list of items (like a shopping cart) that needs to persist even if the user navigates between different pages.
3.  **Authentication:** Storing the user's login token and checking if they are logged in.
4.  **Event Passing:** Using an `Observable` or `Subject` inside a service to notify other parts of the app when an action occurs.

### Summary
*   **Component:** Handles the HTML/CSS and user interactions.
*   **Service:** Handles business logic, data fetching, and state.
*   **Dependency Injection:** The mechanism Angular uses to give components access to services.
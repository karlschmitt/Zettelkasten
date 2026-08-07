---
id: 20260805123306
title: Angular NgRx Actions
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, NgRx, Actions]
---

![Herzschlag der Zustandsverwaltung](../Images/Herzschlag_der_Zustandsverwaltung.png)

> [NOTE!]
> Dieser Text erläutert die zentrale Rolle von **Actions** innerhalb des **NgRx-State-Managements** für Angular-Anwendungen. Diese fungieren als **eindeutige Ereignisse**, die detailliert beschreiben, welche Interaktionen oder Systemprozesse innerhalb einer App stattgefunden haben. Jede Action besteht aus einem **beschreibenden Typ** und optionalen Daten, die als **Payload** bezeichnet werden. Der Text verdeutlicht zudem den **Lebenszyklus**, in dem Actions durch Reducer den Status aktualisieren oder durch Effects asynchrone Aufgaben auslösen. Ein wesentlicher Teil des Inhalts widmet sich der **Action Hygiene**, die eine präzise Benennung nach der Herkunft des Ereignisses empfiehlt. Letztlich dienen diese Objekte als essenzielle **Informationsträger**, um eine strukturierte Kommunikation zwischen verschiedenen Software-Schichten zu gewährleisten.


# Action

In NgRx, **Actions** are one of the core building blocks of the state management cycle. 
Think of them as **unique events** that describe "what happened" in your application.

Here is a breakdown of what they are, how they work, and why they are used.

---

### 1. The Basic Definition
An Action is a simple JavaScript object that implements the `Action` interface. It has two main parts:
*   **`type` (Required):** A string that provides a unique description of the event (e.g., `[Login Page] User Clicked Login`).
*   **`props` (Optional):** A payload containing any data associated with the event (e.g., the user’s email and password).

### 2. What is their Purpose?
Actions are the **only way** to trigger state changes or side effects in NgRx. They act as "messengers" that tell the rest of the system that something occurred, such as:
*   **User Interactions:** Clicking a button, submitting a form.
*   **External Events:** A successful API response, a WebSocket message.
*   **Lifecycle Events:** A component initializing or a route changing.

### 3. How to Define an Action
In modern NgRx, you use the `createAction` function to define an action.

```typescript
import { createAction, props } from '@ngrx/store';

// A simple action without data
export const loadProducts = createAction(
  '[Product List] Load Products'
);

// An action with a payload (data)
export const loadProductsSuccess = createAction(
  '[Products API] Load Products Success',
  props<{ products: Product[] }>()
);
```

### 4. The Life Cycle of an Action
An Action follows this path once it is "dispatched":
1.  **Dispatch:** A component or service calls `store.dispatch(Action)`.
2.  **Reducers:** The Store sends the action to Reducers. If a Reducer cares about this action, it creates a **new state** based on the action's data.
3.  **Effects:** The Store also sends the action to Effects. Effects use actions to trigger **asynchronous tasks** (like calling an API). Usually, an Effect will dispatch a *new* action when the task is done (e.g., `Load Success`).

### 5. "Action Hygiene" (Best Practices)
NgRx experts recommend a pattern called **Action Hygiene** to keep apps maintainable:

*   **Be Descriptive:** The `type` should follow the pattern `[Source] Event`. 
    *   *Bad:* `load_data`
    *   *Good:* `[Home Page] Load User Profile`
*   **Actions are Events, not Commands:** Don't name actions by what you want the reducer to do (e.g., `SetLoadingTrue`). Name them by what happened (e.g., `[Search Bar] Search Button Clicked`).
*   **Unique Types:** Every action type must be unique across the entire application to avoid accidental triggers.

### Summary
*   **Actions** = Events that happened.
*   **Reducers** = Listen to Actions to update State.
*   **Effects** = Listen to Actions to perform Side Effects (API calls).
*   **Components** = Dispatch Actions to tell the app something changed.
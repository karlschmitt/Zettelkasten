---
id: 20260803121630
title: Second Redux Pattern Tutorial
author: Karl Schmitt
date: 2026-08-03
keywords: [ Angular, Redux Pattern, NgRx]
---

![Architektur für reaktives Zustandsmanagement](./Images/Architektur_für_reaktives_Zustandsmanagement.png)

> [NOTE!]
> Dieses Tutorial von Karl Schmitt bietet eine fundierte Einführung in die Implementierung des **Redux-Patterns** innerhalb moderner **Angular-Anwendungen** unter Verwendung der **NgRx-Bibliothek**. Der Text erläutert die vier zentralen Säulen der Zustandsverwaltung: den globalen **Store**, beschreibende **Actions**, logikbasierte **Reducer** und effiziente **Selectors**. Anhand einer praktischen Beispielanwendung wird der gesamte Entwicklungsprozess von der Installation bis hin zur Integration in **Standalone-Komponenten** detailliert beschrieben. Darüber hinaus hebt die Quelle die Vorteile von **Immutabilität** und der Vorhersagbarkeit von Daten hervor, um die Performance und Wartbarkeit komplexer Softwareprojekte zu steigern. Abschließend wird die Nutzung der **Redux DevTools** empfohlen, um Zustandsänderungen im Browser präzise nachzuverfolgen und zu analysieren.


# Second Redux Pattern Tutorial

In the Angular ecosystem, the most popular and "official" implementation of the Redux pattern is **NgRx**.

This tutorial will guide you through building a simple **Counter Application** using modern Angular (Standalone Components) and NgRx.

## Overview

![NgRx](./Images/NgRx-Redux-Patern.png)

---

### 1. The Redux Pattern Core Concepts

Before coding, understand the four pillars:
1.  **Store:** The single source of truth (a global object).
2.  **Actions:** Plain objects that describe *what* happened (e.g., "[Counter] Increment").
3.  **Reducers:** Pure functions that take the **current state** + **action** and return a **new state**.
4.  **Selectors:** Functions used to grab specific pieces of state from the store.

Das Redux-Pattern, welches in Angular häufig durch die Library **NgRx** implementiert wird, basiert auf vier zentralen Grundpfeilern, die für ein vorhersehbares Zustandsmanagement sorgen:

* **Store:** Der Store ist die **einzige Quelle der Wahrheit** (Single Source of Truth). Man kann ihn sich als ein großes, globales Objekt vorstellen, in dem der gesamte Zustand (State) der Anwendung gespeichert ist. Da es nur diesen einen zentralen Ort für die Daten gibt, behält man stets den Überblick über die aktuelle Datenlage der App.
* **Actions:** Actions sind einfache Objekte, die beschreiben, **was passiert ist** (z. B. „\[Counter] Increment“). Sie dienen als Befehle oder Ereignismeldungen, die dem Store mitteilen, dass eine Änderung des Zustands gewünscht ist. Eine Action selbst enthält dabei nur die Information über das Ereignis, führt aber noch keine Änderung durch.
* **Reducers:** Reducer sind **reine Funktionen** (Pure Functions), welche die eigentliche Logik der Zustandsänderung enthalten. Sie nehmen den **aktuellen Zustand** und die **Action** entgegen und geben daraufhin einen **neuen Zustand** zurück. Ein wichtiges Prinzip dabei ist die **Immutabilität** (Unveränderlichkeit): Der alte Zustand wird nicht modifiziert, sondern durch ein komplett neues Objekt ersetzt.
* **Selectors:** Selectors sind Funktionen, die dazu verwendet werden, **bestimmte Teile des Zustands** effizient aus dem Store abzurufen. Anstatt dass eine Komponente den gesamten globalen Store durchsuchen muss, helfen Selectors dabei, nur die benötigten Datenfragmente "herauszupicken".

**Warum nutzt man dieses System?** Obwohl dieses Muster für kleine Aufgaben komplex wirken kann, bietet es enorme Vorteile bei wachsenden Anwendungen: Es sorgt für **Vorhersehbarkeit**, da jede Änderung protokolliert wird, und ermöglicht durch die Unveränderlichkeit der Daten eine sehr schnelle Performance (z. B. durch Angulars _OnPush_-Change-Detection). Zudem erlauben Tools wie die **Redux DevTools** eine Art „Zeitreise“ durch die verschiedenen Zustände der App.


---

### 2. Installation

Create a new Angular project and add NgRx:
```bash
ng new redux-tutorial
cd redux-tutorial
ng add @ngrx/store@latest
```
![Successful Angular Project Creation with NgRx](./Images/Screenshots/Successful_Angular_Project_Creation_with_NgRx.png)

---

### 3. Step 1: Define the State and Actions
Create a file `src/app/state/counter.actions.ts`. Actions tell the store we want to change something.

```typescript
import { createAction } from '@ngrx/store';

export const increment = createAction('[Counter Component] Increment');
export const decrement = createAction('[Counter Component] Decrement');
export const reset = createAction('[Counter Component] Reset');
```

---

### 4. Step 2: Create the Reducer
Create `src/app/state/counter.reducer.ts`. This logic determines how the state changes.

```typescript
import { createReducer, on } from '@ngrx/store';
import { increment, decrement, reset } from './counter.actions';

export const initialState = 0;

export const counterReducer = createReducer(
  initialState,
  on(increment, (state) => state + 1),
  on(decrement, (state) => state - 1),
  on(reset, (state) => 0)
);
```

---

### 5. Step 3: Register the Store
In a modern Angular app (Standalone), you register the store in your `app.config.ts`.

```typescript
// src/app/app.config.ts
import { ApplicationConfig } from '@angular/core';
import { provideStore } from '@ngrx/store';
import { counterReducer } from './state/counter.reducer';

export const appConfig: ApplicationConfig = {
  providers: [
    provideStore({ count: counterReducer }) // "count" is the key in our global state
  ]
};
```

---

### 6. Step 4: Create Selectors
Selectors help us get data out of the store efficiently.
Create `src/app/state/counter.selectors.ts`.

```typescript
import { createSelector, createFeatureSelector } from '@ngrx/store';

// Select the entire state slice
export const selectCount = (state: { count: number }) => state.count;
```

---

### 7. Step 5: Use it in a Component
Now, let's connect the UI to the Store in `app.component.ts`.

```typescript
import { Component, inject } from '@angular/core';
import { Store } from '@ngrx/store';
import { AsyncPipe } from '@angular/common';
import { increment, decrement, reset } from './state/counter.actions';
import { selectCount } from './state/counter.selectors';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [AsyncPipe],
  template: `
    <h1>Counter: {{ count$ | async }}</h1>

    <button (click)="onIncrement()">Increment</button>
    <button (click)="onDecrement()">Decrement</button>
    <button (click)="onReset()">Reset</button>
  `
})
export class AppComponent {
  private store = inject(Store);
  
  // Select data from store
  count$: Observable<number> = this.store.select(selectCount);

  onIncrement() {
    this.store.dispatch(increment());
  }

  onDecrement() {
    this.store.dispatch(decrement());
  }

  onReset() {
    this.store.dispatch(reset());
  }
}
```

---

### 8. Why use this instead of a simple Service?

You might think, *"I could do this with a simple variable in a service."* For a counter, yes. But Redux shines when:

1.  **Multiple components** need the same data (e.g., User Profile, Shopping Cart).
2.  **Predictability:** Every state change is logged. If you use **Redux DevTools**, you can "Time Travel" through your app's history.
3.  **Immutability:** Since we never "mutate" the state (we return a new object), Angular's `OnPush` change detection becomes extremely fast.

---

### 9. Advanced: Adding Redux DevTools
To see your state changes in your browser's inspect tool, install the DevTools:

1. Install the browser extension (Redux DevTools).
2. Install the package:
   ```bash
   ng add @ngrx/store-devtools@latest
   ```
3. Add it to `app.config.ts`:
   ```typescript
   import { provideStoreDevtools } from '@ngrx/store-devtools';
   // ... inside providers:
   provideStoreDevtools({ maxAge: 25, logOnly: false })
   ```

### 10. Summary Checklist
1. **Define Actions:** What can the user do?
2. **Define Reducer:** How does the state change for each action?
3. **Register Store:** Provide it in `app.config`.
4. **Selector:** How do we read the data?
5. **Dispatch:** Trigger an action from the component.
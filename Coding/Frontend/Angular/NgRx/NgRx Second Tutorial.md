---
id: 20260803115013
title: NgRx Second Tutorial
author: Karl Schmitt
date: 2026-08-03
keywords: [ Angular, NgRx, tutorial]
---

# Second NgRx Tutorial

NgRx is a framework for building reactive applications in Angular. It is based on the **Redux pattern**, which helps manage state in a centralized and predictable way.

This tutorial covers the latest **NgRx (v17+)** using functional approaches and standalone components.

## Overview

![NgRx](./Images/NgRx-Redux-Patern.png)


---

### 1. The Core Concepts
*   **Store:** The single source of truth for your application state.
*   **Actions:** Plain objects that describe *what* happened (e.g., `[Auth] Login`).
*   **Reducers:** Pure functions that take the current state and an action to produce a *new* state.
*   **Selectors:** Functions used to grab specific slices of state from the store.
*   **Effects:** Side-effect handlers (e.g., API calls) that listen for actions and dispatch new actions.

---

### 2. Installation
Open your terminal in your Angular project and run:

```bash
npm install @ngrx/store @ngrx/effects @ngrx/store-devtools
```

---

### 3. Step-by-Step Example: A Counter App

#### Step 1: Define Actions
Actions tell NgRx what you want to do. Create a file `src/app/state/counter.actions.ts`:

```typescript
import { createActionGroup, emptyProps, props } from '@ngrx/store';

export const CounterActions = createActionGroup({
  source: 'Counter',
  events: {
    'Increment': emptyProps(),
    'Decrement': emptyProps(),
    'Reset': emptyProps(),
    'Set Value': props<{ value: number }>(),
  },
});
```

#### Step 2: Create the Reducer
The reducer defines the initial state and how it changes. Create `src/app/state/counter.reducer.ts`:

```typescript
import { createReducer, on } from '@ngrx/store';
import { CounterActions } from './counter.actions';

export interface CounterState {
  count: number;
}

export const initialState: CounterState = {
  count: 0,
};

export const counterReducer = createReducer(
  initialState,
  on(CounterActions.increment, (state) => ({ ...state, count: state.count + 1 })),
  on(CounterActions.decrement, (state) => ({ ...state, count: state.count - 1 })),
  on(CounterActions.reset, () => initialState),
  on(CounterActions.setValue, (state, { value }) => ({ ...state, count: value }))
);
```

#### Step 3: Create Selectors
Selectors allow you to read data efficiently. Create `src/app/state/counter.selectors.ts`:

```typescript
import { createFeatureSelector, createSelector } from '@ngrx/store';
import { CounterState } from './counter.reducer';

export const selectCounterState = createFeatureSelector<CounterState>('counter');

export const selectCount = createSelector(
  selectCounterState,
  (state) => state.count
);
```

#### Step 4: Register the Store
In a modern Angular app (Standalone), update your `app.config.ts`:

```typescript
import { ApplicationConfig } from '@angular/core';
import { provideStore } from '@ngrx/store';
import { counterReducer } from './state/counter.reducer';

export const appConfig: ApplicationConfig = {
  providers: [
    provideStore({ counter: counterReducer }),
  ]
};
```

#### Step 5: Use it in a Component
Now, connect your component to the store.

```typescript
import { Component } from '@angular/core';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { CounterActions } from './state/counter.actions';
import { selectCount } from './state/counter.selectors';
import { AsyncPipe } from '@angular/common';

@Component({
  selector: 'app-counter',
  standalone: true,
  imports: [AsyncPipe],
  template: `
    <h1>Count: {{ count$ | async }}</h1>
    <button (click)="increment()">Increment</button>
    <button (click)="decrement()">Decrement</button>
    <button (click)="reset()">Reset</button>
  `
})
export class CounterComponent {
  count$: Observable<number>;

  constructor(private store: Store) {
    this.count$ = this.store.select(selectCount);
  }

  increment() {
    this.store.dispatch(CounterActions.increment());
  }

  decrement() {
    this.store.dispatch(CounterActions.decrement());
  }

  reset() {
    this.store.dispatch(CounterActions.reset());
  }
}
```

---

### 4. Handling Side Effects (API Calls)
If you need to fetch data from a server, you use **Effects**.

1.  **Define Action:** `[User] Load Users`.
2.  **Effect listens:** It catches `Load Users`, calls the `UserService`.
3.  **Effect dispatches:** Once the data arrives, it dispatches `[User] Load Users Success`.

**Example Effect (`user.effects.ts`):**

```typescript
import { inject } from '@angular/core';
import { Actions, createEffect, onBy } from '@ngrx/effects';
import { UserService } from './user.service';
import { UserActions } from './user.actions';
import { catchError, map, mergeMap, of } from 'rxjs';

export const loadUsers = createEffect(
  (actions$ = inject(Actions), userService = inject(UserService)) => {
    return actions$.pipe(
      ofType(UserActions.loadUsers),
      mergeMap(() => userService.getAll().pipe(
        map(users => UserActions.loadUsersSuccess({ users })),
        catchError(error => of(UserActions.loadUsersFailure({ error })))
      ))
    );
  },
  { functional: true }
);
```

To register effects, add `provideEffects(UserEffects)` to your `app.config.ts`.

---

### 5. Debugging with Redux DevTools
NgRx is famous for its debugging. Install the **Redux DevTools** extension in your browser (Chrome/Edge/Firefox).

In your `app.config.ts`, add:
```typescript
import { provideStoreDevtools } from '@ngrx/store-devtools';

export const appConfig: ApplicationConfig = {
  providers: [
    provideStore({...}),
    provideStoreDevtools({ maxAge: 25, logOnly: false })
  ]
};
```
Now you can see every action and state change in real-time in your browser's inspect tool.

---

### When to use NgRx?
Do **not** use NgRx for everything. Use it if:
1.  Many components share the same state.
2.  The state is accessed from many different routes.
3.  You need to undo/redo actions.
4.  Your state logic is getting too complex for a simple `BehaviorSubject` in a Service.
---
id: 20260803111956
title: NgRx First Tutorial
author: Karl Schmitt
date: 2026-08-03
keywords: [ Angular, NgRx, Tutorial]
---

# First NgRx Tutorial

If you already know Angular, NgRx is the standard library for predictable state management in Angular applications. It is inspired by Redux and uses reactive programming with RxJS.

## Overview

![NgRx Redux Pattern](./Images/NgRx-Redux-Patern.png)


# NgRx Tutorial: From Beginner to Intermediate

## 1. What is NgRx?

NgRx helps manage application state in a predictable way.

Without NgRx:

```
Component
    ↓
Service
    ↓
HTTP API
```

With NgRx:

```
Component
    ↓
Dispatch Action
    ↓
Store
    ↓
Reducer
    ↓
New State
    ↓
Selectors
    ↓
Component
```

Effects handle asynchronous work such as HTTP requests.

***

# 2. Core Concepts

NgRx consists of five major building blocks.

| Concept   | Purpose                                   |
| --------- | ----------------------------------------- |
| Store     | Holds the application state               |
| Actions   | Describe what happened                    |
| Reducers  | Produce new state                         |
| Selectors | Read state                                |
| Effects   | Handle side effects (HTTP, routing, etc.) |

***

# 3. Example Application

Imagine a Todo application.

```
Todos

✓ Buy milk
□ Learn NgRx
□ Build app
```

The application state might look like:

```typescript
export interface Todo {
  id: number;
  text: string;
  completed: boolean;
}

export interface TodoState {
  todos: Todo[];
  loading: boolean;
}
```

***

# 4. Installing NgRx

Install the core packages:

```bash
ng add @ngrx/store
ng add @ngrx/effects
ng add @ngrx/store-devtools
ng add @ngrx/entity
```

This automatically configures much of your Angular application.

***

# 5. Creating Actions

Actions represent events.

```typescript
// todo.actions.ts

import { createAction, props } from '@ngrx/store';

export const loadTodos = createAction(
    '[Todo] Load Todos'
);

export const loadTodosSuccess = createAction(
    '[Todo API] Load Success',
    props<{ todos: Todo[] }>()
);

export const addTodo = createAction(
    '[Todo] Add Todo',
    props<{ text: string }>()
);
```

Notice the naming convention:

```
[Source] Event
```

Example:

```
[Todo] Add Todo
```

***

# 6. State

```typescript
export interface TodoState {
    todos: Todo[];
    loading: boolean;
}

export const initialState: TodoState = {
    todos: [],
    loading: false
};
```

***

# 7. Reducers

Reducers are pure functions.

Input:

```
Old State
Action
```

Output:

```
New State
```

Example:

```typescript
import { createReducer, on } from '@ngrx/store';

export const todoReducer = createReducer(

    initialState,

    on(loadTodos, state => ({
        ...state,
        loading: true
    })),

    on(loadTodosSuccess, (state, { todos }) => ({
        ...state,
        loading: false,
        todos
    }))
);
```

Important:

Never mutate state.

❌ Wrong

```typescript
state.todos.push(todo);
```

✅ Correct

```typescript
return {
    ...state,
    todos: [...state.todos, todo]
};
```

***

# 8. Registering the Reducer

Angular 17+:

```typescript
bootstrapApplication(AppComponent, {
  providers: [
    provideStore({
      todo: todoReducer
    })
  ]
});
```

***

# 9. Dispatching Actions

Inside a component:

```typescript
constructor(private store: Store) {}

load() {
    this.store.dispatch(loadTodos());
}
```

***

# 10. Selectors

Selectors retrieve state.

```typescript
export const selectTodoState =
    createFeatureSelector<TodoState>('todo');

export const selectTodos = createSelector(
    selectTodoState,
    state => state.todos
);

export const selectLoading = createSelector(
    selectTodoState,
    state => state.loading
);
```

Using selectors in a component:

```typescript
todos$ = this.store.select(selectTodos);
loading$ = this.store.select(selectLoading);
```

Template:

```html
<ul>
  <li *ngFor="let todo of todos$ | async">
    {{ todo.text }}
  </li>
</ul>
```

***

# 11. Effects

Reducers must not perform HTTP calls.

Effects handle asynchronous work.

```
Action
    ↓
Effect
    ↓
HTTP Request
    ↓
Success Action
```

Example:

```typescript
@Injectable()
export class TodoEffects {

  loadTodos$ = createEffect(() =>
    this.actions$.pipe(

      ofType(loadTodos),

      switchMap(() =>
        this.todoService.getTodos().pipe(

          map(todos => loadTodosSuccess({ todos }))
        )
      )
    )
  );

  constructor(
    private actions$: Actions,
    private todoService: TodoService
  ) {}
}
```

***

# 12. Component Flow

```
User clicks button

↓

dispatch(loadTodos())

↓

Effect

↓

HTTP GET

↓

loadTodosSuccess()

↓

Reducer

↓

Store updated

↓

Selector emits

↓

UI refreshes
```

***

# 13. Folder Structure

```
src/

store/

    todo/

        todo.actions.ts

        todo.reducer.ts

        todo.effects.ts

        todo.selectors.ts

        todo.state.ts
```

For larger applications:

```
store/

    auth/

    products/

    orders/

    users/

    settings/
```

Each feature owns its own state.

***

# 14. Best Practices

### Keep reducers pure

No:

* HTTP

* timers

* logging

* navigation

Reducers should only compute new state.

***

### Use selectors

Instead of:

```typescript
store.select(state => state.todo.todos)
```

Prefer:

```typescript
store.select(selectTodos)
```

Selectors are reusable, composable, and memoized.

***

### Normalize data

Instead of:

```typescript
todos: Todo[]
```

Large applications benefit from normalized state:

```typescript
{
  ids: [1,2,3],
  entities: {
      1: {...},
      2: {...},
      3: {...}
  }
}
```

`@ngrx/entity` helps manage this efficiently.

***

### Keep components thin

A good component:

* dispatches actions

* subscribes to selectors

* contains minimal business logic

Most business logic belongs in reducers, selectors, or effects.

***

# 15. Common Mistakes

❌ Mutating state

```typescript
state.todos.push(todo)
```

***

❌ Calling services from reducers

Reducers should never perform side effects.

***

❌ Putting everything in the store

Only store shared application state.

Examples of data that usually **should not** go into the store:

* form input while typing (unless shared or long-lived)

* modal open/close flags local to one component

* temporary UI state

***

# 16. Example Flow

```
Component

dispatch(addTodo())

        │

        ▼

Action

        │

        ▼

Effect

        │

        ▼

API

        │

        ▼

Success Action

        │

        ▼

Reducer

        │

        ▼

Store

        │

        ▼

Selector

        │

        ▼

Component updates
```

***

# 17. When Should You Use NgRx?

NgRx is a great fit when:

* Your application has complex shared state across many components.

* You need predictable state transitions and time-travel debugging with the Redux DevTools.

* You want a clear separation between UI, business logic, and side effects.

For small applications with only a few components and minimal shared state, Angular services with signals or RxJS are often simpler and require less boilerplate.

## Suggested Learning Path

1. Understand Angular services and dependency injection.

2. Learn RxJS fundamentals (`Observable`, `pipe`, `map`, `switchMap`).

3. Master NgRx actions and reducers.

4. Learn selectors and how memoization works.

5. Add effects for asynchronous operations.

6. Explore `@ngrx/entity` for managing collections.

7. Learn feature stores, lazy-loaded state, and router integration for larger applications.

Once you're comfortable with these concepts, you'll be able to structure scalable Angular applications with a clear, testable state management architecture.

---
id: 20260806100815
title: How Redux maps to Angular
author: Karl Schmitt
date: 2026-08-06
---

![Zustandsmanagement](../Images/Zustandsmanagement_im_Web-Framework_verstehen.png)

> [NOTE!]
> Dieser Abschnitt erläutert den **konzeptionellen Transfer** von Redux-Prinzipien auf die **Angular-Entwicklung** mithilfe der NgRx-Bibliothek. Er verdeutlicht, wie klassische UI-Komponenten lediglich **Aktionen auslösen** und Daten anzeigen, während die eigentliche **Logik zur Zustandsänderung** in Reducer ausgelagert wird. Ein zentraler Aspekt ist die **Aufgabentrennung**, bei der herkömmliche Angular-Services durch **effiziente Store-Mechanismen** und Selektoren ersetzt werden. Asynchrone Prozesse wie API-Aufrufe werden konsequent in **Effects** verschoben, um die Komponenten schlank zu halten. Das Framework nutzt dabei **Observables und Dependency Injection**, um eine vorhersehbare, einseitige Datenquelle innerhalb der Anwendung zu etablieren. Abschließend wird aufgezeigt, wie dieses Zusammenspiel eine **klare Struktur** schafft, in der jede Einheit eine spezifische Verantwortung trägt.


# How Redux maps to Angular

One of the hardest parts of learning NgRx is understanding **how the abstract Redux concepts map onto concrete Angular concepts**.

The following table gives the high-level mapping:

| Redux Concept | Angular/NgRx Equivalent   | Responsibility                                   |
| ------------- | ------------------------- | ------------------------------------------------ |
| UI            | Angular Component         | Displays data and reacts to user events          |
| Action        | `createAction()`          | Describes what happened                          |
| Store         | `Store` service           | Holds the application state                      |
| Reducer       | `createReducer()`         | Computes the next state                          |
| State         | Plain TypeScript object   | Stores application data                          |
| Selector      | `createSelector()`        | Reads data from the store                        |
| Middleware    | Effects (`@ngrx/effects`) | Performs asynchronous work (HTTP, routing, etc.) |

Let's look at how they work together in an Angular application.

***

# 1. Angular Component = Redux UI

In Redux, the **UI** interacts with the store.

In Angular, the UI is an **Angular component**.

For example:

```typescript
@Component({...})
export class TodoComponent {

    todos$ = this.store.select(selectTodos);

    constructor(private store: Store) {}

    addTodo() {
        this.store.dispatch(addTodo({
            text: 'Learn NgRx'
        }));
    }

}
```

Notice that the component has only two responsibilities:

* dispatch actions

* display state

It **does not** contain the business logic for changing the state.

***

# 2. Angular Service ≠ Store

This often confuses Angular developers.

Without NgRx, you might write:

```text
Component

↓

TodoService

↓

HTTP
```

The service often has multiple responsibilities:

* stores data

* updates data

* performs HTTP requests

* notifies components

With NgRx, these responsibilities are split:

```text
Component

↓

Store

↓

Reducer

↓

State
```

and

```text
Component

↓

Effect

↓

HTTP Service
```

The Angular service becomes focused on communicating with the backend, while the store manages application state.

***

# 3. State = Plain TypeScript Object

Angular doesn't require a special state class.

Instead:

```typescript
export interface TodoState {

    todos: Todo[];

    loading: boolean;

}
```

The store simply contains this object.

Think of it as one large JavaScript object.

```text
Store

{

todos: [...],

loading: false,

user: {...},

products: [...]

}
```

***

# 4. Reducers Are Just Functions

Angular doesn't provide reducers.

NgRx does.

```typescript
export const todoReducer = createReducer(

    initialState,

    on(addTodoSuccess, (state, { todo }) => ({

        ...state,

        todos: [...state.todos, todo]

    }))

);
```

The reducer receives:

```text
Current State

+

Action
```

and returns:

```text
New State
```

Exactly like Redux.

***

# 5. Store Is an Injectable Angular Service

The store is actually injected using Angular's dependency injection.

```typescript
constructor(private store: Store) {}
```

So the store behaves like any other Angular service.

The difference is **what it does**.

Instead of exposing methods like:

```typescript
todoService.addTodo()
```

you dispatch actions:

```typescript
store.dispatch(addTodo())
```

***

# 6. Selectors Replace Manual Data Access

Without NgRx:

```typescript
todos = this.todoService.todos;
```

With NgRx:

```typescript
todos$ = this.store.select(selectTodos);
```

Notice the `$`.

Selectors return **Observables**.

Angular templates subscribe automatically using the `async` pipe.

```html
<li *ngFor="let todo of todos$ | async">
```

***

# 7. Effects Replace Async Logic in Components

Without NgRx:

```typescript
addTodo() {

    this.todoService.addTodo(todo)

        .subscribe(...);

}
```

The component performs the HTTP request.

With NgRx:

```typescript
addTodo() {

    this.store.dispatch(addTodo());

}
```

The component no longer knows about HTTP.

Instead:

```text
Action

↓

Effect

↓

HTTP

↓

Success Action
```

The effect handles the asynchronous work.

***

# 8. Angular Change Detection Works with Selectors

Suppose the reducer returns:

```typescript
return {

    ...state,

    todos: [...state.todos, todo]

};
```

The store now contains a new state object.

Selectors emit the updated data.

Because the component subscribes to the selector:

```typescript
todos$ = this.store.select(selectTodos);
```

Angular receives the new value.

The UI updates automatically.

***

# A Complete Angular Request

Suppose the user presses **Load Todos**.

### Angular Component

```typescript
loadTodos() {

    this.store.dispatch(loadTodos());

}
```

↓

### Action

```text
loadTodos
```

↓

### Effect

```typescript
this.todoService.getTodos()
```

↓

### HTTP

```text
GET /todos
```

↓

### Success Action

```text
loadTodosSuccess
```

↓

### Reducer

```typescript
return {

    ...state,

    todos

};
```

↓

### Store

State updated

↓

### Selector

```typescript
selectTodos
```

↓

### Component

```typescript
todos$ =
this.store.select(selectTodos);
```

↓

### Angular Template

```html
<li *ngFor="let todo of todos$ | async">
```

↓

### Browser

Displays the updated todo list.

***

# A Mental Model

Think of NgRx as dividing responsibilities that are often combined in Angular services:

```text
                 Angular Application

                 User clicks button
                        │
                        ▼
              Angular Component
         (dispatches an action)
                        │
                        ▼
                   NgRx Store
                        │
        ┌───────────────┴───────────────┐
        ▼                               ▼
   Reducer (sync logic)          Effect (async work)
        │                               │
        ▼                               ▼
   New application state         Angular service → HTTP API
        │
        ▼
     Selectors
        │
        ▼
 Angular Component updates
        │
        ▼
      Angular template
```

## The key insight

Angular and NgRx complement each other:

* **Angular** is responsible for **building and rendering the UI**, handling dependency injection, routing, forms, and change detection.

* **NgRx** is responsible for **managing shared application state** in a predictable, one-way data flow.

A useful way to remember the relationship is:

* **Components** ask for data and dispatch actions.

* **Selectors** provide the data.

* **Reducers** decide how state changes.

* **Effects** handle asynchronous operations.

* **Services** communicate with external systems (such as REST APIs).

* **The Store** is the single source of truth that ties everything together.

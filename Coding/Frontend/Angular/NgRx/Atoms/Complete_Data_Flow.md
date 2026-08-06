---
id: 20260806094529
title: Complete Data Flow
author: Karl Schmitt
date: 2026-08-06
keywords: [Angular, NgRx, Redux, actions, reducers, selectors, effects]
---

# Complete Data Flow

The **NgRx data flow** is the heart of how NgRx works. 
Once you understand this flow, the individual concepts—actions, reducers, selectors, and effects—fit together naturally.

Let's walk through the complete cycle using a simple example.

***

# The Big Picture

Imagine a Todo application. The user clicks an **"Add Todo"** button.

The data flows in **one direction only**:

```text
User
  │
  ▼
Component
  │
  ▼
Dispatch Action
  │
  ▼
Effect (optional)
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
Component
  │
  ▼
Updated UI
```

Notice that the data **never flows backwards**. This is called **unidirectional data flow**.

***

# Step 1 – The User Performs an Action

The user clicks a button.

```text
+------------------+
|  Add Todo Button |
+------------------+

        Click
```

At this point, nothing has changed in the application's state.

***

# Step 2 – The Component Dispatches an Action

The component doesn't modify the store directly.

Instead, it announces **what happened**:

```typescript
this.store.dispatch(
  addTodo({ text: 'Learn NgRx' })
);
```

Think of an action as a message.

```text
Action

"I want to add a todo."
```

An action **does not** contain the logic for updating the state. It simply describes an event.

***

# Step 3 – Does the Action Need an HTTP Request?

Now ask:

> **Can the state be updated immediately, or do we need data from somewhere else?**

There are two possible paths.

## Path A: No HTTP Request Needed

Suppose the todo only needs to be added locally.

The action goes directly to the reducer.

```text
Action
   │
   ▼
Reducer
```

***

## Path B: HTTP Request Needed

Suppose the todo must first be saved on a server.

The action is intercepted by an **Effect**.

```text
Action
   │
   ▼
Effect
```

The effect performs the asynchronous work:

```text
HTTP POST

↓

Server saves todo

↓

Server responds
```

The effect then dispatches another action:

```typescript
addTodoSuccess({
    todo: savedTodo
});
```

Notice something important:

The original action did **not** change the store.

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

The **success action** is what eventually reaches the reducer.

***

# Step 4 – The Reducer Creates a New State

The reducer receives two things:

```text
Current State

+

Action
```

Suppose the current state is:

```typescript
{
  todos: [
    "Buy milk"
  ]
}
```

The reducer returns:

```typescript
{
  todos: [
    "Buy milk",
    "Learn NgRx"
  ]
}
```

Notice that the reducer creates a **new state object** rather than changing the existing one.

```text
Old State

↓

Reducer

↓

New State
```

The old state remains unchanged.

***

# Step 5 – The Store Replaces the Old State

The store now updates its current state.

Before:

```text
Store

todos

Buy milk
```

After:

```text
Store

todos

Buy milk
Learn NgRx
```

The store now contains the new state.

***

# Step 6 – Selectors Read the Updated State

Components don't read the store directly.

Instead, they use selectors.

```typescript
todos$ = this.store.select(selectTodos);
```

A selector simply says:

> "Give me the todo list."

```text
Store

↓

Selector

↓

Todo List
```

Selectors can also compute derived values. For example:

```typescript
selectCompletedTodos

selectRemainingTodos

selectTodoCount
```

Each selector returns only the data a component needs.

***

# Step 7 – Components Receive the Updated Data

Because `store.select(...)` returns an **Observable**, components automatically receive new values when the store changes.

```text
Store changed

↓

Selector emits

↓

Observable emits

↓

Component receives new value
```

No manual synchronization is required.

***

# Step 8 – Angular Updates the UI

Finally, Angular updates the view.

Before:

```text
Todos

✓ Buy milk
```

After:

```text
Todos

✓ Buy milk
□ Learn NgRx
```

The user now sees the updated list.

***

# The Complete Flow (Without HTTP)

```text
User clicks button
        │
        ▼
Component
        │
dispatch(addTodo())
        │
        ▼
Action
        │
        ▼
Reducer
        │
Creates new state
        │
        ▼
Store updated
        │
        ▼
Selector emits
        │
        ▼
Component receives new data
        │
        ▼
Angular updates UI
```

***

# The Complete Flow (With HTTP)

```text
User clicks button
        │
        ▼
Component
        │
dispatch(loadTodos())
        │
        ▼
Action
        │
        ▼
Effect
        │
HTTP GET
        │
        ▼
Server
        │
Returns todos
        │
        ▼
loadTodosSuccess()
        │
        ▼
Reducer
        │
Creates new state
        │
        ▼
Store updated
        │
        ▼
Selector emits
        │
        ▼
Component updates
```

***

# Why Is This Flow So Predictable?

Every state change follows the same sequence:

1. **Something happens** (user interaction, timer, route change, etc.).

2. An **action** describes what happened.

3. An **effect** optionally performs asynchronous work.

4. A **reducer** computes a new state.

5. The **store** replaces the old state.

6. **Selectors** expose the updated data.

7. **Components** automatically receive the new values and Angular refreshes the UI.

Because there is only **one path** for changing state, you can always answer questions like:

* _Why did the state change?_ → Look at the dispatched action.

* _How was the new state computed?_ → Look at the reducer.

* _Where did the data come from?_ → Look at the effect (if one was involved).

This predictable, one-way flow is one of the biggest advantages of NgRx. It makes complex applications easier to reason about, debug, and test because every state transition follows the same well-defined lifecycle.

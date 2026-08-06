---
id: 20260806092430
title: The three Redux principles
author: Karl Schmitt
date: 2026-08-06
---

# The three Redux principles 

The **three Redux principles** are the foundation of Redux and NgRx. They explain **how application state is organized and changed**.

***

# 1. Single Source of Truth

**Principle:**

> The entire application state is stored in a single object called the **Store**.

Instead of every component maintaining its own copy of shared data, there is one central place that holds the application's state.

Imagine an online shopping application.

Without a single source of truth:

```text
ShoppingCartComponent
    cartItems = ?

CheckoutComponent
    cartItems = ?

HeaderComponent
    cartItems = ?
```

Each component might have its own copy of the cart, making it easy for them to get out of sync.

With NgRx:

```text
                Store

cartItems
products
user
orders
settings
```

Every component reads the same state.

```text
            Store
               │
      ┌────────┼────────┐
      │        │        │
 Header     Cart    Checkout
```

If the cart changes, every component sees the updated data.

### Why is this useful?

Imagine the user adds a product.

Without a shared store:

* Update Cart Component

* Update Header Badge

* Update Checkout Page

* Update Sidebar

You must manually keep everything synchronized.

With NgRx:

```text
Store changes

↓

Every subscribed component updates automatically
```

The store becomes the **single source of truth** for shared application state.

***

# 2. State Is Read-Only

**Principle:**

> The only way to change the state is by **dispatching an Action**.

Components never modify the store directly.

For example, suppose the current state is:

```typescript
{
    counter: 5
}
```

A component should **not** do this:

```typescript
store.counter++;
```

Instead, it dispatches an action:

```typescript
store.dispatch(increment());
```

Notice what the component is doing.

It isn't saying:

> "Set the counter to 6."

Instead, it is saying:

> "The user wants to increment the counter."

The action describes **what happened**, not **how the state should change**.

The reducer decides how to update the state.

This gives you a predictable flow:

```text
User clicks button

↓

Dispatch Action

↓

Reducer

↓

New State
```

### Why is this useful?

Because every state change follows the same path.

No component can secretly modify the state.

This makes debugging much easier.

***

# 3. Changes Are Made with Pure Functions

**Principle:**

> State changes are described by **pure functions** called **reducers**.

A reducer has a simple signature:

```typescript
(state, action) => newState
```

Example:

```typescript
const reducer = (state, action) => {

    switch(action.type) {

        case "increment":
            return {
                counter: state.counter + 1
            };

        default:
            return state;
    }

}
```

A reducer receives:

* the current state

* an action

and returns:

* a new state

### What is a pure function?

A pure function:

* always returns the same output for the same input

* does not modify its inputs

* has no side effects (such as HTTP requests, timers, logging, or navigation)

For example:

```typescript
function add(a, b) {
    return a + b;
}
```

Calling:

```text
add(2, 3)
```

always returns:

```text
5
```

No matter how many times you call it.

A reducer should behave the same way.

***

## Why return a new state?

Suppose the current state is:

```typescript
{
    counter: 5
}
```

Don't do this:

```typescript
state.counter++;
```

This mutates the existing state object.

Instead:

```typescript
return {
    ...state,
    counter: state.counter + 1
};
```

Now the old state is unchanged, and a **new state object** is returned.

This immutability makes it easy for NgRx to detect changes and update only the parts of the UI that need to be refreshed.

***

# Putting the Three Principles Together

Imagine a user clicks an **"Add Todo"** button.

### Step 1: Single Source of Truth

The store contains:

```text
todos = [
    "Buy milk"
]
```

This is the only copy of the todo list.

***

### Step 2: Dispatch an Action

The component does **not** modify the list.

Instead:

```typescript
store.dispatch(addTodo({
    text: "Learn NgRx"
}));
```

The action says:

> "The user requested a new todo."

***

### Step 3: Reducer Creates New State

The reducer receives:

```text
Current State

+

AddTodo Action
```

It returns:

```typescript
{
    todos: [
        "Buy milk",
        "Learn NgRx"
    ]
}
```

Notice that it creates a new array rather than changing the old one.

***

## The Complete Data Flow

```text
User clicks button
        │
        ▼
Dispatch Action
        │
        ▼
Reducer (pure function)
        │
        ▼
New State
        │
        ▼
Store updated
        │
        ▼
Selectors emit updated values
        │
        ▼
Angular components re-render
```

This one-way flow is a key reason Redux and NgRx applications are predictable and easier to debug.

### A helpful analogy

Think of the store as a **library's catalog**:

* **Single source of truth:** There is one official catalog that everyone consults.

* **State is read-only:** Visitors cannot edit the catalog directly; they submit a request to the librarian.

* **Pure reducers:** The librarian follows a fixed set of rules to produce a new edition of the catalog, rather than scribbling changes into the existing one.

Because everyone uses the same catalog and every update follows the same process, it's always clear how the current state came to be.

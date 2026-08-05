---
id: 20260805112948
title: New State
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, Redux Patern, NgRx, State]
---

# New State

This is probably **the most important concept in Redux**, and it's where many Angular developers have an "aha!" moment.

The phrase **"New State"** does **not** mean "the old state after it has been modified."

It literally means:

> **A brand-new JavaScript object is created that represents the updated application state.**

The old state is left untouched.

***

# What is a State?

Suppose your application's state is:

```ts
const state = {
  cart: {
    items: ["Laptop", "Mouse"]
  },
  user: {
    name: "Alice"
  }
};
```

Think of this object as a snapshot of your application at one moment in time.

```text
Time 10:00

State
----------------
User : Alice
Cart :
    Laptop
    Mouse
----------------
```

***

# The user adds a keyboard

The component dispatches:

```ts
addItem({ product: "Keyboard" })
```

The reducer receives:

* the current state

* the action

```ts
(state, action)
```

Now comes the important part.

***

# Wrong approach (mutation)

A beginner might write:

```ts
state.cart.items.push("Keyboard");

return state;
```

The object in memory changes.

Before:

```text
State
-------------
Laptop
Mouse
-------------
```

After:

```text
Same State Object
-------------
Laptop
Mouse
Keyboard
-------------
```

Nothing new was created.

Redux discourages this because it makes it difficult to detect changes reliably.

***

# Correct approach (immutable update)

Instead, the reducer creates a new object:

```ts
return {
  ...state,
  cart: {
    ...state.cart,
    items: [
      ...state.cart.items,
      "Keyboard"
    ]
  }
};
```

Let's see what this actually does.

***

# Before

```text
Old State

+-----------------------+
| User                  |
|  Alice                |
|                       |
| Cart                  |
|  Laptop               |
|  Mouse                |
+-----------------------+
```

***

# After

A completely new state object is created.

```text
New State

+-----------------------+
| User                  |
|  Alice                |
|                       |
| Cart                  |
|  Laptop               |
|  Mouse                |
|  Keyboard             |
+-----------------------+
```

The **old state still exists**.

It has **not** changed.

***

# Why keep the old state?

Because Redux treats state like snapshots in time.

Imagine taking photos.

10:00

```text
📷 Snapshot

Laptop
Mouse
```

10:01

```text
📷 Snapshot

Laptop
Mouse
Keyboard
```

You don't erase the first photo.

You take another one.

Redux works the same way.

***

# What happens inside the Store?

Initially:

```text
Store
   │
   ▼
State A
```

The reducer calculates:

```text
State B
```

The Store now changes its reference:

```text
Before

Store
   │
   ▼
State A
```

↓

```text
After

Store
   │
   ▼
State B
```

The Store simply points to the newly created state.

The old state is no longer the current state. If nothing else references it, JavaScript's garbage collector will eventually free its memory.

***

# Why create a new object?

Imagine you're proofreading a document.

Option 1:

You edit the only copy.

If you make a mistake, you've lost the original.

Option 2:

You make a copy first.

```
Original

↓

Copy

↓

Edit Copy
```

Now you always know:

* what changed,

* what stayed the same,

* what the previous version looked like.

Redux follows the second approach.

***

# What does the spread operator (`...`) do?

Suppose:

```ts
const state = {
  name: "Alice",
  age: 30
};
```

Writing:

```ts
const newState = {
  ...state,
  age: 31
};
```

creates a new object.

Old object:

```text
{
  name: "Alice",
  age: 30
}
```

New object:

```text
{
  name: "Alice",
  age: 31
}
```

The old object is unchanged.

This is exactly how reducers build a new state.

***

# An Important Optimization

You might wonder:

> "Does Redux copy the entire application state every time?"

No.

Suppose your state is:

```ts
{
  user,
  cart,
  products,
  settings,
  orders
}
```

Only the part that changes is recreated.

For example, if only the cart changes:

```text
Old State

User --------┐
Products ----┤
Settings ----┤
Orders ------┤
Cart ------- Old Cart
```

New State:

```text
New State

User --------┐
Products ----┤
Settings ----┤
Orders ------┤
              │
              ▼
           Same objects

Cart -----> New Cart
```

The `user`, `products`, `settings`, and `orders` objects are **reused**. Only the `cart` object (and any nested objects that changed) is newly created. This technique is called **structural sharing** and keeps immutable updates efficient.

***

# The Lifecycle of a State

Every action creates a new version of the application's state:

```text
Initial State
      │
      ▼
User logs in
      │
      ▼
State #2
      │
Add item
      │
      ▼
State #3
      │
Remove item
      │
      ▼
State #4
      │
Checkout
      │
      ▼
State #5
```

Each state represents a complete snapshot of the application at that point in time.

***

## The key idea

The biggest mental shift in Redux is this:

Traditional programming often thinks:

> **Modify the existing object.**

Redux thinks:

> **Leave the existing object alone. Create a new object that represents the updated reality.**

So when you read **"New State"**, mentally translate it to:

> **"A new snapshot of the application's data, calculated by the reducer from the previous snapshot and the dispatched action."**

That single idea—treating state as a sequence of immutable snapshots—is what makes Redux's behavior predictable and enables features like efficient change detection and time-travel debugging.


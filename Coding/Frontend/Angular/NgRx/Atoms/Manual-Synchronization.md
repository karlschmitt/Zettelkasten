---
id: 20260804145440
title: Manual Synchronization
author: Karl Schmitt
date: 2026-08-04
---

# Manual Synchronization

In this tutorial, **"manual synchronization"** refers to the work developers have to do to keep multiple copies of the same data consistent.

Let's look at an example.

***

# Without Redux

Suppose you have an online shop with these components:

```text
App
 ├── Product List
 ├── Shopping Cart
 ├── Header
 └── Checkout
```

All of them need to know what's in the cart.

***

## First attempt

You create a service:

```ts
export class CartService {

    items: Product[] = [];

}
```

The Product List adds an item:

```ts
this.cartService.items.push(product);
```

So far, so good.

***

## The problem

The Header displays the number of items.

When does it update?

You have to tell it somehow.

One common approach is to use a `BehaviorSubject`.

```ts
private itemsSubject =
    new BehaviorSubject<Product[]>([]);
```

Every time the cart changes:

```ts
this.itemsSubject.next(updatedItems);
```

Now every interested component must subscribe:

```ts
this.cartService.items$
    .subscribe(items => {
        this.items = items;
    });
```

You repeat this in:

* Product List

* Header

* Checkout

* Cart

* Order Summary

Each component now has its own subscription.

***

# Why is this called "manual synchronization"?

Because **you are responsible for keeping everything in sync**.

For example, suppose the user removes an item.

You must remember to:

1. Update the array.

2. Call `next()`.

3. Ensure every component is subscribed.

4. Ensure every subscription is cleaned up if needed.

5. Make sure no component keeps its own outdated copy.

You're coordinating all these updates yourself.

***

# Imagine you forget...

Suppose you accidentally write:

```ts
this.cartService.items.push(product);
```

but forget:

```ts
this.itemsSubject.next(this.cartService.items);
```

Now what happens?

```text
Cart Service
    │
items array updated
    │
BehaviorSubject not notified
    │
Header still shows "2 items"
Checkout still shows old total
Cart component shows stale data
```

The data has changed, but the UI hasn't.

That's a synchronization bug.

***

# Another example

Suppose the application stores:

```text
Cart

3 items
```

The Header copies the count:

```text
Header

cartCount = 3
```

The Checkout copies the total:

```text
Checkout

total = 89 €
```

The Cart component copies the list:

```text
CartComponent

items = [...]
```

Now the user removes an item.

If one component forgets to update its local copy, the application becomes inconsistent:

```text
Header

2 items

Checkout

89 €

Cart

2 items
```

Different parts of the UI disagree because they each maintain their own copy of the state.

***

# How Redux solves this

Redux says:

> **Don't copy the state. Read it from one central place.**

Instead of this:

```text
Header
  cartCount = 3

Checkout
  total = 89

Cart
  items = [...]
```

You have:

```text
          Store
      ----------------
      cart
      products
      user
      ----------------
        ▲   ▲   ▲
        │   │   │
   Header Checkout Cart
```

No component owns its own copy of the cart. They all read from the **Store**.

When the cart changes:

1. An action is dispatched.

2. The reducer creates a new state.

3. The Store publishes the new state.

4. All components automatically receive the updated value.

You no longer have to remember to update each component individually.

***

## A real-world analogy

Imagine an office with a whiteboard showing today's meeting room.

### Manual synchronization

Every employee keeps their own sticky note:

```text
Alice: Room A
Bob:   Room A
Carol: Room A
Dave:  Room A
```

The meeting moves to Room B.

Someone has to walk around updating every sticky note. If one is missed, that person goes to the wrong room.

### Redux

There's one whiteboard:

```text
Meeting Room

Room B
```

Everyone simply looks at the whiteboard. When it changes, everyone sees the same information.

That's the essence of Redux: **a single source of truth**, which eliminates the need for manually keeping multiple copies of the same state synchronized.

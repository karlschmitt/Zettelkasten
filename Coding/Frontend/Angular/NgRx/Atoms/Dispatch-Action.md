---
id: 20260804173144
title: Dispatch Action
author: Karl Schmitt
date: 2026-08-04
---

![Der Weg zum State-Update](..\Images\Der_Weg_zum_State-Update.png)

> [NOTE!]
> In diesem Text erläutert Karl Schmitt das Konzept des **Dispatching** innerhalb der Redux-Architektur und nutzt dafür anschauliche Alltagsvergleiche. Anstatt den Zustand einer Anwendung direkt zu manipulieren, senden Komponenten lediglich **formalisierte Nachrichten** über eingetretene Ereignisse an einen zentralen Speicher. Dieser Prozess wird mit einem **Postdienst oder einem Kellner** verglichen, wobei die Komponente nur den Auftrag erteilt, während die interne Logik die eigentliche Verarbeitung übernimmt. Durch diese **strikte Trennung** von Ereignismeldung und Zustandsänderung bleibt der Code übersichtlich und leichter nachvollziehbar. Das System stellt sicher, dass alle Datenänderungen einem **vorhersehbaren Pfad** folgen, was die Fehlersuche und die Skalierbarkeit erheblich verbessert. Letztlich beschreibt der Autor den **mentalen Wechsel**, Handlungen als bloße Benachrichtigungen über Vergangenes zu verstehen, statt als direkte Befehle zur Datenänderung.



# Dispatch Action

> What does the term "dispatch action" mean, and why was the wording "dispatch" used?

This is an excellent question because the word **"dispatch"** is not obvious if you're new to Redux.

The short answer is:

> **To dispatch an action means to send a message to the Redux Store saying, "This event happened."**

You are **not** changing the state directly. You are **dispatching** (sending) an action to the Store, which decides how to handle it.

***

# Why the word "dispatch"?

The word comes from everyday English.

To **dispatch** means:

* to send

* to forward

* to deliver

* to issue an instruction

Think of a postal service.

```text
You
 │
 │  send letter
 ▼
Post Office
 │
 ▼
Recipient
```

You don't deliver the letter yourself.

You **dispatch** it.

The postal system figures out what happens next.

Redux uses the same idea.

***

# Redux Analogy

Imagine the Store is a company's mailroom.

You are an employee.

When something happens, you don't walk into the accounting department and change their records yourself.

Instead, you send a form.

```text
Employee
    │
    │ dispatch
    ▼
 Mailroom (Store)
    │
    ▼
 Accounting (Reducer)
    │
    ▼
 Updated Records
```

The employee reports what happened.

The accounting department decides how the records change.

***

# Example: Shopping Cart

Suppose a user clicks **Add to Cart**.

Without Redux:

```ts
cart.items.push(product);
```

The component directly changes the cart.

With Redux:

```ts
this.store.dispatch(
    addItem({ product })
);
```

Notice something important.

The component **doesn't** modify the cart.

It merely announces:

> "The user added this product."

***

# What happens after dispatch?

Let's follow the journey.

## Step 1

User clicks button.

```text
Click
```

***

## Step 2

Component dispatches an action.

```ts
this.store.dispatch(
    addItem({ product })
);
```

Think of it as mailing a message.

***

## Step 3

The Store receives the action.

```text
Store

receives

Add Item
```

***

## Step 4

The Store passes it to the reducer.

```text
Reducer

Current State

+

Action

↓

New State
```

***

## Step 5

The Store replaces the old state with the new state.

```text
Old Cart

2 items

↓

New Cart

3 items
```

***

## Step 6

Subscribers are notified.

The UI updates automatically.

***

# Why not call the reducer directly?

Imagine components could do this:

```ts
cartReducer(state, action);
```

Now every component would have to know:

* which reducer to call,

* what the current state is,

* how to replace the old state,

* how to notify everyone else.

That would make the application much more complex.

Instead, Redux centralizes this process.

The component only says:

> "Store, here's an action."

The Store takes care of everything else.

***

# Why are actions called "events"?

Notice the wording:

```ts
addItem()
```

does **not** mean

> "Please change the cart."

It means

> "An item was added."

Likewise:

```ts
login()
```

means

> "The user logged in."

and

```ts
logout()
```

means

> "The user logged out."

Actions describe **what happened**, not **how the state should change**.

The reducer decides how to react to that event.

***

# A Real-World Analogy: Restaurant

A restaurant is a great analogy.

The customer doesn't walk into the kitchen and cook.

Instead:

```text
Customer

↓

Waiter

↓

Kitchen

↓

Chef

↓

Meal

↓

Waiter

↓

Customer
```

In Redux:

```text
User

↓

Component

↓

dispatch(action)

↓

Store

↓

Reducer

↓

New State

↓

UI
```

The component is like the waiter.

It delivers the order.

It does **not** cook the meal.

***

# Why this design?

Redux deliberately separates **requesting** a change from **performing** the change.

This has several benefits:

* Components remain simple.

* Every state change follows the same path.

* It's easy to log every action for debugging.

* You can replay actions to reproduce bugs (time-travel debugging).

* The flow of data is predictable.

***

## The key idea to remember

When you see:

```ts
this.store.dispatch(addItem({ product }));
```

don't read it as:

> "Add the item."

Read it as:

> **"Send a message to the Store saying that the user added an item."**

The Store then forwards that message to the appropriate reducer, which calculates the new state and publishes it to the rest of the application.

This event-driven way of thinking is one of the biggest mental shifts when moving from traditional Angular services to Redux/NgRx.

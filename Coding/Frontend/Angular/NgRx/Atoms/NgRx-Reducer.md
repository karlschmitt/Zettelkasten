---
id: 20260805093240
title: NgRx Reduce
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, NgRx, reduce, Reducer]
---

The term **"reducer"** is probably the most confusing name in Redux because it doesn't sound like it has anything to do with application state.

The name actually comes from **functional programming**, long before Redux existed.

***

# The origin of the word "reduce"

Most programming languages have a function called `reduce()`.

For example, in JavaScript:

```ts
const numbers = [2, 3, 5];

const sum = numbers.reduce(
    (total, current) => total + current,
    0
);

console.log(sum);
```

Output:

```text
10
```

Here, `reduce()` takes many values:

```text
2
3
5
```

and **reduces** them into one result:

```text
10
```

That's why it's called **reduce**.

***

# What is the reducing function?

Inside `reduce()` you write a function:

```ts
(total, current) => total + current
```

This function is called the **reducer function**.

It repeatedly combines:

* the current accumulated value

* the next input

to produce a new accumulated value.

For example:

```text
Start

0

↓

0 + 2 = 2

↓

2 + 3 = 5

↓

5 + 5 = 10
```

Each step **reduces** many inputs into one final result.

***

# Redux borrowed this idea

Redux also has a function that repeatedly combines:

* the current application state

* an incoming action

to produce:

* a new application state

Instead of:

```text
current total

+

next number

↓

new total
```

Redux does:

```text
current state

+

action

↓

new state
```

The pattern is almost identical.

***

# The Redux Reducer

A reducer always has two inputs:

```ts
(state, action)
```

and returns one output:

```ts
newState
```

Example:

```ts
function cartReducer(state, action) {

    switch(action.type) {

        case 'ADD_ITEM':

            return {
                ...state,
                items: [
                    ...state.items,
                    action.product
                ]
            };

        default:

            return state;
    }

}
```

Notice:

It doesn't modify anything.

It simply calculates:

> Given the old state and this action,\
> what should the next state be?

***

# Think of it as a calculator

Imagine a simple calculator.

Current value:

```text
10
```

Action:

```text
+5
```

Reducer:

```text
10 + 5 = 15
```

New value:

```text
15
```

The calculator didn't decide what operation to perform.

Someone told it:

> Apply +5.

Redux reducers work the same way.

***

# Better analogy: A State Machine

Imagine a vending machine.

Current state:

```text
No money inserted
```

Action:

```text
Insert $1
```

Reducer computes:

```text
Ready to select product
```

Later:

Current state:

```text
Ready to select product
```

Action:

```text
Select Coke
```

Reducer computes:

```text
Dispense Coke
```

The reducer isn't making decisions on its own.

It simply applies predefined rules.

***

# Why not call it an "Updater"?

Many people ask exactly this!

Why not:

* updater

* state transformer

* processor

* handler

Those names would arguably be easier to understand.

The answer is historical.

Redux intentionally copied terminology from functional programming.

Since the function looks like the callback passed to `Array.prototype.reduce()`, its creator, Dan Abramov, called it a **reducer**.

The name has stuck ever since.

***

# The Reducer's Job

Think of the reducer as a very boring employee.

It receives two things:

```text
Current State

+

Action
```

Its only job is:

```text
Calculate New State
```

It **cannot**:

❌ make HTTP requests

❌ show dialogs

❌ navigate pages

❌ modify the existing state

❌ generate random numbers

It only performs one task:

```text
Old State

+

Action

↓

New State
```

***

# Dispatch and Reducer Together

Now you can see why the two names fit together.

The component:

```text
dispatches
```

an action.

The reducer:

```text
reduces
```

the current state and that action into a new state.

The complete flow is:

```text
User clicks "Add to Cart"
        │
        ▼
Component
        │
dispatch(action)
        │
        ▼
Store
        │
passes action to
        ▼
Reducer
        │
computes
        ▼
New State
        │
Store saves new state
        │
        ▼
UI updates
```

***

# A simpler name to keep in mind

When you're learning Redux, you can mentally translate **reducer** to:

> **"State Calculator"**

or

> **"State Transition Function."**

Those aren't the official terms, but they describe the role very well:

* **Input:** current state + action

* **Output:** new state

Once you're comfortable with the concept, the historical name **reducer** will feel much more natural.

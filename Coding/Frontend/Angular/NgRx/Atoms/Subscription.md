---
id: 20260804141002
title: Subscription
author: Karl Schmitt
date: 2026-08-04
keywords: [ Angular, RxJS, Subscription]
---

**Subscriptions** are a fundamental concept in RxJS and Angular. 
If you understand them, you'll understand much of how Angular handles asynchronous data.

## What is a Subscription?

A **subscription** is how you tell an **Observable**:

> "Notify me whenever you have a new value."

Think of it like subscribing to a newsletter.

* **Observable** = the newsletter publisher

* **Subscriber** = you

* **Subscription** = your active subscription

* **New value** = the next newsletter

As long as you're subscribed, you'll receive every new value.

***

## Example without RxJS

Suppose you have a variable:

```ts
let temperature = 20;
```

You can read it once:

```ts
console.log(temperature);
```

Output:

```
20
```

If the temperature later changes:

```ts
temperature = 25;
```

Nothing happens automatically. You have to check it again.

***

## Example with an Observable

An Observable can notify you automatically.

```ts
const observable = new Observable(observer => {
    observer.next(20);
    observer.next(25);
    observer.next(30);
});
```

To receive those values:

```ts
observable.subscribe(value => {
    console.log(value);
});
```

Output:

```
20
25
30
```

The call to `subscribe()` creates a **Subscription**.

***

## BehaviorSubject Example

Suppose your service contains:

```ts
private counter = new BehaviorSubject<number>(0);
```

A component subscribes:

```ts
this.counter.subscribe(value => {
    console.log(value);
});
```

Immediately you get:

```
0
```

Later the service does:

```ts
this.counter.next(1);
```

The subscriber automatically receives:

```
1
```

Then:

```ts
this.counter.next(2);
```

Output:

```
2
```

Every call to `next()` notifies all subscribers.

***

## Multiple Subscribers

One Observable can have many subscribers.

```text
               BehaviorSubject
                     │
      ┌──────────────┼──────────────┐
      │              │              │
Component A    Component B    Component C
```

When:

```ts
subject.next("Hello");
```

All three components receive:

```
Hello
```

This is why `BehaviorSubject` is useful for shared application state.

***

## What does `subscribe()` return?

It returns a `Subscription` object.

```ts
const subscription =
    observable.subscribe(value => {
        console.log(value);
    });
```

Later you can stop listening:

```ts
subscription.unsubscribe();
```

After unsubscribing, new values are ignored.

***

## Why unsubscribe?

Imagine a component is destroyed because the user navigates away.

If it stays subscribed:

* it continues receiving values

* it consumes memory unnecessarily

* it can cause unexpected behavior

For long-lived Observables, forgetting to unsubscribe can lead to **memory leaks**.

***

## Angular's `async` Pipe

Angular can manage subscriptions for you.

Instead of:

```ts
export class CartComponent {

    items: Product[] = [];

    ngOnInit() {
        this.cartService.items$
            .subscribe(items => {
                this.items = items;
            });
    }
}
```

you can write:

```ts
items$ = this.cartService.items$;
```

and in the template:

```html
<li *ngFor="let item of items$ | async">
    {{ item.name }}
</li>
```

The `async` pipe:

* subscribes automatically,

* updates the view when new values arrive,

* unsubscribes automatically when the component is destroyed.

This is the preferred approach for displaying observable data in Angular templates.

***

## How does this relate to Redux/NgRx?

When you write:

```ts
cart$ = this.store.select(selectCart);
```

`cart$` is an **Observable**. In the template:

```html
<div>{{ (cart$ | async)?.total }}</div>
```

the `async` pipe subscribes to the store. Whenever the store's state changes, the observable emits a new value, the subscription receives it, and Angular updates the UI.

***

## The Big Picture

Here's the complete flow:

```text
BehaviorSubject (or NgRx Store)
            │
     emits a value
            │
            ▼
      Observable
            │
    subscribe() or async pipe
            │
            ▼
      Component receives value
            │
            ▼
     Angular updates the UI
```

So, a **subscription** is simply the connection between an Observable and the code that wants to react to the values it emits. Without a subscription (or the `async` pipe, which creates one for you), an Observable doesn't deliver its values to your component.


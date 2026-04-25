---
id: 20260425195507
title: Angular RxJS
author: Karl Schmitt
date: 2026-04-25
keywords: [ Angular, RxJS]
---

# Vorschau

Das bereitgestellte Material erläutert die **Funktionsweise von RxJS** als essenzielle Bibliothek für die **reaktive Programmierung** innerhalb des Angular-Frameworks. Es definiert zentrale Konzepte wie **Observables**, die als Datenströme fungieren, sowie **Operatoren**, mit denen Informationen effizient gefiltert oder transformiert werden können. Ein wesentlicher Teil des Textes vergleicht die Vorteile von **Observables gegenüber Promises**, wobei insbesondere die Fähigkeit zur **Stornierung** und die verzögerte Ausführung hervorgehoben werden. Zudem wird aufgezeigt, wie Angular diese Technologie für **HTTP-Anfragen, Formulare und das Routing** nutzt, um asynchrone Ereignisse zu steuern. Die Quellen verdeutlichen somit, warum dieses Werkzeug für die Verwaltung komplexer **Datenströme und Benutzerinteraktionen** in modernen Webanwendungen unverzichtbar ist. Durch praktische Beispiele wird schließlich illustriert, wie Entwickler den **Datenfluss abonnieren** und gezielt manipulieren können.

![Angular_RxJS](../Images/Angular_RxJS.png)

# Angular RxJS

RxJS (Reactive Extensions for JavaScript) is a library used for reactive programming that allows you to handle asynchronous data streams and events using [Observables](https://rxjs.dev/guide/overview). [1, 2] 
In Angular, RxJS is a core dependency and is used extensively for handling everything from HTTP requests to user interactions. [3, 4] 

## 1. Core Concepts

* Observable: A data producer that "emits" values over time. It can be a single value (like an HTTP response) or multiple values (like click events).
* Observer: A set of callbacks (next, error, complete) that "listens" to the values delivered by an Observable.
* Subscription: Represents the execution of an Observable. You must .subscribe() to an Observable to start receiving data.
* Operators: Pure functions that allow you to transform, filter, or combine data streams (e.g., map, filter, switchMap).
* Subject: A special type of Observable that can multicast values to many Observers (acting as both a producer and a consumer). [5, 6, 7, 8, 9, 10, 11] 

## 2. Why Angular Uses RxJS

Angular relies on RxJS for its most critical features: [12] 

* HttpClient: Every network request returns an Observable.
* Reactive Forms: Form controls have properties like valueChanges that are Observables.
* Router: You can subscribe to route parameters and navigation events.
* Event Emitters: Used for component communication via @Output(). [3, 13, 14, 15, 16, 17, 18] 

## 3. Basic Example
Instead of waiting for a single result (like a Promise), you "pipe" a stream through operators: [19, 20] 

import { map, filter } from 'rxjs/operators';
// Fetch users, filter for active ones, and get their namesthis.http.get<User[]>('/api/users').pipe(
  map(users => users.filter(u => u.isActive)),
  map(activeUsers => activeUsers.map(u => u.name))
).subscribe(names => console.log(names));

## 4. RxJS vs. Promises

| Feature [5, 8, 9, 20, 21] | Promise | RxJS Observable |
|---|---|---|
| Values | Emits a single value | Emits multiple values over time |
| Execution | Starts immediately upon creation | Only starts when you .subscribe() ("Lazy") |
| Cancellation | Cannot be easily cancelled | Can be cancelled by unsubscribing |
| Operators | None | Powerful toolset to transform data |

Would you like a guide on common RxJS operators like switchMap and mergeMap, or should we look at how to prevent memory leaks using the AsyncPipe?

[1] [https://www.youtube.com](https://www.youtube.com/watch?v=g8S81JkATi0)
[2] [https://rxjs.dev](https://rxjs.dev/guide/overview)
[3] [https://medium.com](https://medium.com/@justin.guckes/a-simple-intro-into-declarative-angular-app-development-using-rxjs-5de5ee82981)
[4] [https://medium.com](https://medium.com/@matheusluna96/using-rxjs-in-angular-a-comprehensive-guide-b1c9e5e9dab7)
[5] [https://dev.to](https://dev.to/renukapatil/understanding-rxjs-and-observables-in-angular-a-beginner-friendly-guide-ibf)
[6] [https://medium.com](https://medium.com/@dev.murugavel/mastering-rxjs-introduction-to-reactive-programming-in-angular-35d23393b6d1)
[7] [https://rxjs.dev](https://rxjs.dev/guide/overview)
[8] [https://dev.to](https://dev.to/renukapatil/understanding-rxjs-and-observables-in-angular-a-beginner-friendly-guide-ibf)
[9] [https://www.youtube.com](https://www.youtube.com/watch?v=bZKXtgNbKE0)
[10] [https://www.scribd.com](https://www.scribd.com/document/947536063/Angular-RxJS)
[11] [https://fseehawer.medium.com](https://fseehawer.medium.com/mastering-rxjs-essential-concepts-for-building-robust-angular-applications-4c277ddf95b)
[12] [https://www.scribd.com](https://www.scribd.com/document/969329627/Why-Use-RxJS-merged)
[13] [https://blog.angular-university.io](https://blog.angular-university.io/functional-reactive-programming-for-angular-2-developers-rxjs-and-observables/)
[14] [https://www.freecodecamp.org](https://www.freecodecamp.org/news/angular-rxjs-in-depth/)
[15] [https://dev.to](https://dev.to/tianyaschool/angular-advanced-understanding-the-efficient-use-of-rxjs-in-angular-applications-4l06)
[16] [https://medium.com](https://medium.com/@info_80576/understanding-rxjs-and-observables-in-angular-a-beginners-guide-f1b870e6d3c1)
[17] [https://medium.com](https://medium.com/@matheusluna96/using-rxjs-in-angular-a-comprehensive-guide-b1c9e5e9dab7)
[18] [https://blog.angular-university.io](https://blog.angular-university.io/functional-reactive-programming-for-angular-2-developers-rxjs-and-observables/#:~:text=Angular%20currently%20uses%20RxJs%20Observables%20in%20two,namely%20in%20Forms%20and%20the%20HTTP%20module.)
[19] [https://www.reddit.com](https://www.reddit.com/r/angular/comments/130zn1k/can_someone_please_explain_rxjs_with_examples/)
[20] [https://blogs.angriotechnologies.com](https://blogs.angriotechnologies.com/blog-details/What-are-the-Pros-and-Cons-of-RxJS-in-Angular-)
[21] [https://www.reddit.com](https://www.reddit.com/r/angular/comments/130zn1k/can_someone_please_explain_rxjs_with_examples/)

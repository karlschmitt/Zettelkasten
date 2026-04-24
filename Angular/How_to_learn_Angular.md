---
id: 20260423133838
title: How to learn Angular
author: Karl Schmitt
date: 2026-04-23
keywords: [ Angular ]
---

# How to learn Angular

# **Analyzing Angular Versions**

I've been calculating the likely Angular version based on the release cycle and the current date. I'm assuming a six-month cadence for major releases. Considering Angular 17 was released last November, I'm expecting Angular 18 to be imminent, likely in May. I'm taking the release frequency into account.


**Forecasting Angular's Future**

I'm now detailing the planned releases, including the anticipated dates for Angular 19, 20, and 21. I'm focusing on the modern features like Signals, Standalone Components, and the new Control Flow, which will define the learning roadmap. Considering Angular 17/18, I'm emphasizing that this is a "Renaissance" for the framework.

As of mid-2024, Angular 21 does not exist yet. Angular follows a predictable
six-month release cycle. Here is the estimated timeline:

  - Angular 18: Current Stable (Released May 2024)
  - Angular 19: Expected November 2024
  - Angular 20: Expected May 2025
  - Angular 21: Expected November 2025

However, if you want to be ready for Angular 21, you should learn the "Angular
Renaissance" features introduced between versions 14 and 18. These features
represent the future of the framework and will be the standard by the time
version 21 arrives.

Here is your roadmap to learning modern Angular (leading up to v21):

1. Master the New Essentials (The "Renaissance" Features)

The "old way" of writing Angular (Modules, Zone.js) is being phased out. To be
ready for version 21, focus on these:

  - Standalone Components: Learn how to build apps without NgModule. This is now
    the default.
  - Signals: This is the most important change. Signals are a new way to manage
    state and change detection, making apps faster and easier to reason about.
  - New Control Flow: Move away from *ngIf and *ngFor. Learn the new syntax:
    @if, @for, and @switch.
  - Deferrable Views (@defer): Learn how to easily lazy-load parts of your
    template to improve performance.

2. The Modern Learning Path

If you are starting today, follow this sequence:

Step 1: TypeScript

Angular is built on TypeScript. You need to understand:

  - Interfaces and Types.
  - Generics.
  - Decorators.

Step 2: The Official New Documentation

Go to angular.dev. This is the new home for Angular (replacing angular.io). It
features:

  - An interactive, in-browser tutorial.
  - Modern guides focused on Standalone Components and Signals.

Step 3: Server-Side Rendering (SSR) and Hydration

Angular is moving heavily toward better SEO and performance. Learn:

  - Angular Universal (now integrated into the CLI).
  - Hydration: How Angular "wakes up" a server-rendered page.

Step 4: Reactive Programming

While Signals are the new star, RxJS is still used for complex asynchronous
streams (like HTTP requests). Learn the balance between the two.

3. Recommended Resources

  - Angular.dev: The absolute best place to start.
  - YouTube - Angular University: Excellent for deep dives into new features.
  - YouTube - Joshua Morony: Focuses heavily on high-level architecture and
    "Signals-based" reactive patterns.
  - Podcasts: Adventures in Angular or The Angular Show to stay updated on
    what’s coming in v19, v20, and eventually v21.

4. Practice Project

To be ready for the future, try building a "Signal-based" application:

1.  Initialize a project: ng new my-app --standalone
2.  Use Signals for all local state management.
3.  Use the inject() function instead of constructor-based Dependency Injection.
4.  Use the new @for syntax for lists.
5.  Fetch data using the HttpClient and convert it to a Signal using toSignal().

Summary

By the time Angular 21 is released in late 2025, Signals will likely be the
primary way to handle reactivity, and Zone.js (the old change detection system)
might be optional or deprecated. If you learn Angular 18/19 today using
Standalone Components and Signals, you will already know 95% of what Angular 21
will be.


---
id: 20260805170353
title: Angular NgRx Pure Function
author: Karl Schmitt
date: 2026-08-05
keywords: [Angular, NgRx, pure function]
---

![Pure Functions für stabilen State](../Images/Pure_Functions_für_stabilen_State.png)

Dieser Text erläutert das Konzept der **Pure Functions** im Kontext von **Angular NgRx** und deren Ursprung in der Mathematik. Eine solche Funktion zeichnet sich dadurch aus, dass sie bei gleichen Eingabewerten stets das **identische Ergebnis** liefert und keinerlei **Nebeneffekte**, wie etwa API-Aufrufe oder Datenänderungen außerhalb ihres eigenen Bereichs, verursacht. In der NgRx-Architektur sind **Reducer** zwingend als Pure Functions konzipiert, um eine **vorhersehbare Zustandsverwaltung** und effiziente Änderungserkennung zu gewährleisten. Diese Struktur ermöglicht fortgeschrittene Funktionen wie das **Time-Travel-Debugging** und vereinfacht das Testen von Code erheblich, da keine externen Abhängigkeiten simuliert werden müssen. Während Reducer für die reine Logik zuständig sind, werden **unreine Funktionen**, die mit der Außenwelt interagieren, in NgRx gezielt in **Effects** ausgelagert.


# Pure Functions

In the context of NgRx (and computer science in general), a **Pure Function** is a function that follows two very strict rules. 

The name "Pure" comes from **Mathematics**, where functions are seen as simple mappings of inputs to outputs, untainted by the "messiness" of the outside world.

---

### 1. The Two Rules of a Pure Function

#### Rule #1: Determinism (Same Input = Same Output)

A pure function must always return the same result if given the same arguments. 
It does not depend on any hidden state, external variables, or data from an API.

*   **Pure:** `(a, b) => a + b` (If you pass 2 and 2, the result is *always* 4).
*   **Impure:** `(a) => a + Math.random()` (The result changes every time).
*   **Impure:** `(a) => a + externalPrice` (If `externalPrice` changes elsewhere, the function returns a different result for the same `a`).

#### Rule #2: No Side Effects

A pure function does not "reach out" and change anything outside of itself. 
It is a "black box."

A function is **Impure** if it does any of the following:
*   Modifies a global variable.
*   Changes the original object/array passed into it (mutating the input).
*   Logs to the console (`console.log`).
*   Makes an HTTP request.
*   Writes to a database or local storage.

---

### 2. Why is it named "Pure"?

The term is borrowed from **Mathematical Logic**.

In mathematics, a function like $f(x) = x + 2$ is "pure" because:
1.  **It is self-contained:** It doesn't care about the weather, the time of day, or what $f(y)$ did five minutes ago.
2.  **It doesn't "break" the universe:** Solving the equation doesn't change the value of $x$ for the rest of the page; it simply yields a result.

In programming, we call it **"Pure"** because the function is **unpolluted** by the state of the application. 
*   It is not **"polluted"** by inputs it can't see (like global variables).
*   It does not **"pollute"** the rest of the app by changing things outside its own scope.

---

### 3. Why does NgRx require Reducers to be Pure?

If Reducers were "impure," NgRx would break. Pure functions provide three massive benefits to NgRx:

#### A. Predictability (The "Time Machine")
Because pure functions are deterministic, NgRx can implement **Time-Travel Debugging**. If you have a list of 10 Actions, NgRx can "replay" them from scratch. Because the reducers are pure, it is guaranteed that replaying those actions will result in the exact same state every single time.

#### B. Change Detection Performance
NgRx relies on **Immutability**. Instead of checking every single property in a large object to see if it changed, NgRx just checks: `if (oldState === newState)`. 
Since a pure function *must* return a new object rather than modifying the old one, Angular can detect changes instantly by looking at the object reference.

#### C. Testing
Pure functions are the easiest things in the world to test. You don’t need to "mock" an API or "set up" a complex database state. You just pass in an input and check if the output is correct.

---

### Comparison Summary

| Feature | **Pure Function** (NgRx Reducer) | **Impure Function** (NgRx Effect/Service) |
| :--- | :--- | :--- |
| **Output** | Based only on arguments | Based on arguments + external world |
| **Side Effects** | None | API calls, logging, storage |
| **State** | Returns a **new** state | May **mutate** existing state |
| **Predictable** | 100% | No (API might fail, Random might change) |
| **NgRx Role** | **Reducers** | **Effects** |In the context of NgRx (and computer science in general), a **Pure Function** is a function that follows two very strict rules. 

The name "Pure" comes from **Mathematics**, where functions are seen as simple mappings of inputs to outputs, untainted by the "messiness" of the outside world.

---

### 1. The Two Rules of a Pure Function

#### Rule #1: Determinism (Same Input = Same Output)
A pure function must always return the same result if given the same arguments. It does not depend on any hidden state, external variables, or data from an API.

*   **Pure:** `(a, b) => a + b` (If you pass 2 and 2, the result is *always* 4).
*   **Impure:** `(a) => a + Math.random()` (The result changes every time).
*   **Impure:** `(a) => a + externalPrice` (If `externalPrice` changes elsewhere, the function returns a different result for the same `a`).

#### Rule #2: No Side Effects
A pure function does not "reach out" and change anything outside of itself. It is a "black box."

A function is **Impure** if it does any of the following:
*   Modifies a global variable.
*   Changes the original object/array passed into it (mutating the input).
*   Logs to the console (`console.log`).
*   Makes an HTTP request.
*   Writes to a database or local storage.

---

### 2. Why is it named "Pure"?

The term is borrowed from **Mathematical Logic**.

In mathematics, a function like $f(x) = x + 2$ is "pure" because:
1.  **It is self-contained:** It doesn't care about the weather, the time of day, or what $f(y)$ did five minutes ago.
2.  **It doesn't "break" the universe:** Solving the equation doesn't change the value of $x$ for the rest of the page; it simply yields a result.

In programming, we call it **"Pure"** because the function is **unpolluted** by the state of the application. 
*   It is not **"polluted"** by inputs it can't see (like global variables).
*   It does not **"pollute"** the rest of the app by changing things outside its own scope.

---

### 3. Why does NgRx require Reducers to be Pure?

If Reducers were "impure," NgRx would break. Pure functions provide three massive benefits to NgRx:

#### A. Predictability (The "Time Machine")
Because pure functions are deterministic, NgRx can implement **Time-Travel Debugging**. If you have a list of 10 Actions, NgRx can "replay" them from scratch. Because the reducers are pure, it is guaranteed that replaying those actions will result in the exact same state every single time.

#### B. Change Detection Performance
NgRx relies on **Immutability**. Instead of checking every single property in a large object to see if it changed, NgRx just checks: `if (oldState === newState)`. 
Since a pure function *must* return a new object rather than modifying the old one, Angular can detect changes instantly by looking at the object reference.

#### C. Testing
Pure functions are the easiest things in the world to test. You don’t need to "mock" an API or "set up" a complex database state. You just pass in an input and check if the output is correct.

---

### Comparison Summary

| Feature | **Pure Function** (NgRx Reducer) | **Impure Function** (NgRx Effect/Service) |
| :--- | :--- | :--- |
| **Output** | Based only on arguments | Based on arguments + external world |
| **Side Effects** | None | API calls, logging, storage |
| **State** | Returns a **new** state | May **mutate** existing state |
| **Predictable** | 100% | No (API might fail, Random might change) |
| **NgRx Role** | **Reducers** | **Effects** |
---
id: 20260912144519
title: Mastering Browser JavaScript
author: Karl Schmitt
date: 2026-09-12
---

![]()

> [NOTE!]
> Dieser Text widerlegt die Annahme, dass man für das Erlernen von **JavaScript** zwingend moderne Werkzeuge wie Node.js oder Frameworks benötigt. Stattdessen wird der **Browser** als ideale, bereits vorhandene Laufzeitumgebung präsentiert, um die Grundlagen der Programmierung direkt zu meistern. Der Leitfaden führt Anfänger durch den Aufbau einer **Projektstruktur** mit HTML, CSS und JavaScript und erklärt essenzielle Konzepte wie das **DOM**, Event-Handling und die Fetch-API. Durch einen strukturierten **30-Tage-Lernplan** und praxisnahe Beispiele wird gezeigt, wie man interaktive Anwendungen ohne komplexe Zusatzsoftware erstellt. Abschließend wird betont, dass ein tiefes Verständnis der **Web-APIs** und der Kernsprache eine unverzichtbare Basis für die spätere Arbeit mit professionellen Frameworks bildet. Damit fungiert die Quelle als motivierendes Handbuch für einen **puristischen Lernansatz** in der Webentwicklung.


# Mastering Browser JavaScript


Absolutely **not doomed**. 😄 In fact, this is a very good way to learn JavaScript because you are forced to understand **browser JavaScript itself**, rather than immediately relying on Node.js, Deno, npm, bundlers, frameworks, etc.

Your setup is enough:

* 🌐 **Browser** — JavaScript runtime

* 📝 **VS Code** — editor

* ⚡ **PowerShell** — file/project management

* 🚫 **No Node.js**

* 🚫 **No Deno**

* 🚫 **No npm**

* 🚫 **No bundler**

* 🚫 **No framework**

And I would actually recommend learning the fundamentals this way before touching React, Angular, Electron, Node.js, etc.

# JavaScript in the Browser

## Absolute Beginner → Practical Developer Tutorial

The basic architecture is:

```text
┌──────────────────────────────┐
│          VS Code             │
│                              │
│  index.html                  │
│  app.js                      │
│  style.css                   │
└──────────────┬───────────────┘
               │
               │ open index.html
               ▼
┌──────────────────────────────┐
│          Browser             │
│                              │
│  HTML  → structure           │
│  CSS   → appearance          │
│  JS    → behaviour           │
│                              │
│      JavaScript Engine       │
└──────────────────────────────┘
```

The browser **is your JavaScript runtime**.

***

# 1. What exactly is JavaScript?

JavaScript is a programming language.

It can run in several environments:

```text
JavaScript
    │
    ├── Browser
    │     ├── Chrome
    │     ├── Edge
    │     ├── Firefox
    │     └── Safari
    │
    ├── Node.js
    │
    ├── Deno
    │
    └── other runtimes
```

You specifically want:

```text
JavaScript
    ↓
Browser
```

That's perfectly valid.

The important distinction is:

> **JavaScript is the language. The browser is the runtime/environment.**

***

# 2. Your first JavaScript program

Create a directory with PowerShell.

```powershell
mkdir JavaScriptBrowser
cd JavaScriptBrowser
code .
```

Create:

```text
JavaScriptBrowser
│
└── index.html
```

Put this into `index.html`:

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>My First JavaScript Program</title>
</head>

<body>

    <h1>Hello JavaScript!</h1>

    <script>
        console.log("Hello from JavaScript!");
    </script>

</body>

</html>
```

Open the file in Chrome or Edge.

Then open:

```text
F12
```

and select:

```text
Console
```

You should see:

```text
Hello from JavaScript!
```

Congratulations.

You have just written a JavaScript program **without Node.js or Deno**.

***

# 3. The `<script>` element

This:

```html
<script>
    console.log("Hello!");
</script>
```

tells the browser:

> "Here comes JavaScript."

JavaScript can therefore live directly inside HTML.

For example:

```html
<body>

    <h1>Hello</h1>

    <script>
        console.log("JavaScript is running!");
    </script>

</body>
```

But eventually we want JavaScript in a separate file.

***

# 4. Your first real project structure

Create:

```text
JavaScriptBrowser
│
├── index.html
├── app.js
└── style.css
```

PowerShell:

```powershell
New-Item index.html
New-Item app.js
New-Item style.css
```

Or simply create the files from VS Code.

***

# 5. External JavaScript

`index.html`:

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>JavaScript Browser</title>
</head>

<body>

    <h1>JavaScript</h1>

    <script src="app.js"></script>

</body>

</html>
```

`app.js`:

```javascript
console.log("Hello from app.js!");
```

Now the browser loads:

```text
index.html
    ↓
<script src="app.js">
    ↓
app.js
    ↓
JavaScript engine
```

***

# 6. Use `defer`

A very useful pattern is:

```html
<script src="app.js" defer></script>
```

So:

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">

    <title>JavaScript</title>

    <script src="app.js" defer></script>
</head>

<body>

    <h1>Hello</h1>

</body>

</html>
```

`defer` basically tells the browser:

> Load the JavaScript while parsing the HTML, but execute it after the HTML has been parsed.

This becomes important when JavaScript wants to access HTML elements.

***

# 7. The browser Developer Tools

You have an incredibly powerful JavaScript development environment already installed.

Chrome DevTools.

Press:

```text
F12
```

Important tabs:

```text
Elements
Console
Sources
Network
Application
```

For JavaScript learning, concentrate initially on:

```text
Console
Sources
Elements
Network
```

***

# 8. The JavaScript Console

You can actually experiment with JavaScript directly.

Open:

```text
F12 → Console
```

Type:

```javascript
2 + 3
```

Result:

```text
5
```

Try:

```javascript
10 * 20
```

Result:

```text
200
```

Try:

```javascript
"Hello" + " " + "World"
```

Result:

```text
"Hello World"
```

This is your JavaScript laboratory.

***

# 9. Variables

Start with:

```javascript
let name = "Karl";
```

Then:

```javascript
console.log(name);
```

You can change it:

```javascript
name = "Alice";
```

And:

```javascript
console.log(name);
```

Use `const` when you don't intend to reassign the variable:

```javascript
const age = 50;
```

So your basic rule is:

```text
const → default choice

let   → value needs to change

var   → learn it eventually, but don't use it for modern code
```

***

# 10. JavaScript data types

Learn these very well.

## String

```javascript
const name = "Karl";
```

## Number

```javascript
const age = 50;
const price = 19.99;
```

## Boolean

```javascript
const isDeveloper = true;
```

## Undefined

```javascript
let value;

console.log(value);
```

Result:

```text
undefined
```

## Null

```javascript
const result = null;
```

## Object

```javascript
const person = {
    name: "Karl",
    age: 50
};
```

## Array

```javascript
const languages = [
    "Java",
    "JavaScript",
    "C++"
];
```

***

# 11. Operators

Learn:

```javascript
+
-
*
/
%
```

Example:

```javascript
const a = 10;
const b = 3;

console.log(a + b);
console.log(a - b);
console.log(a * b);
console.log(a / b);
console.log(a % b);
```

The `%` operator is the remainder operator.

```javascript
10 % 3
```

gives:

```text
1
```

***

# 12. Comparisons

Learn these carefully:

```javascript
===
!==
>
<
>=
<=
```

For example:

```javascript
const age = 20;

console.log(age >= 18);
```

Result:

```text
true
```

Prefer:

```javascript
===
```

rather than:

```javascript
==
```

while learning modern JavaScript.

***

# 13. `if`

```javascript
const age = 20;

if (age >= 18) {
    console.log("Adult");
} else {
    console.log("Minor");
}
```

Add another condition:

```javascript
const age = 20;

if (age < 13) {
    console.log("Child");
} else if (age < 18) {
    console.log("Teenager");
} else {
    console.log("Adult");
}
```

***

# 14. Functions

Functions are one of the most important JavaScript concepts.

```javascript
function greet() {
    console.log("Hello!");
}

greet();
```

Parameters:

```javascript
function greet(name) {
    console.log("Hello " + name);
}

greet("Karl");
greet("Alice");
```

Return values:

```javascript
function add(a, b) {
    return a + b;
}

const result = add(10, 20);

console.log(result);
```

***

# 15. Arrow functions

Modern JavaScript also uses arrow functions:

```javascript
const add = (a, b) => {
    return a + b;
};
```

Short version:

```javascript
const add = (a, b) => a + b;
```

Don't worry if this initially looks strange.

Learn normal functions first.

Then learn arrow functions.

***

# 16. Arrays

Create an array:

```javascript
const languages = [
    "Java",
    "JavaScript",
    "C++",
    "Python"
];
```

Access an element:

```javascript
console.log(languages[0]);
```

Result:

```text
Java
```

Important:

> JavaScript arrays are zero-indexed.

Therefore:

```text
index
  0 → Java
  1 → JavaScript
  2 → C++
  3 → Python
```

***

# 17. Array methods

Learn these:

```javascript
push()
pop()
shift()
unshift()
includes()
indexOf()
slice()
```

Example:

```javascript
const languages = ["Java", "JavaScript"];

languages.push("C++");

console.log(languages);
```

Result:

```text
["Java", "JavaScript", "C++"]
```

***

# 18. Loops

Classic `for` loop:

```javascript
for (let i = 0; i < 5; i++) {
    console.log(i);
}
```

Result:

```text
0
1
2
3
4
```

`for...of`:

```javascript
const languages = [
    "Java",
    "JavaScript",
    "C++"
];

for (const language of languages) {
    console.log(language);
}
```

***

# 19. Objects

Objects are extremely important.

```javascript
const person = {
    name: "Karl",
    age: 50,
    language: "Java"
};
```

Access properties:

```javascript
console.log(person.name);
```

or:

```javascript
console.log(person["name"]);
```

Change a property:

```javascript
person.age = 51;
```

Add a property:

```javascript
person.city = "Frankfurt";
```

***

# 20. Object methods

Objects can contain functions.

```javascript
const person = {

    name: "Karl",

    greet: function () {
        console.log("Hello!");
    }

};

person.greet();
```

Modern syntax:

```javascript
const person = {

    name: "Karl",

    greet() {
        console.log("Hello!");
    }

};
```

This leads naturally into JavaScript's object-oriented features.

***

# 21. Template literals

Instead of:

```javascript
console.log("Hello " + name);
```

you can write:

```javascript
console.log(`Hello ${name}`);
```

Example:

```javascript
const name = "Karl";
const age = 50;

console.log(`My name is ${name} and I am ${age} years old.`);
```

This is extremely useful.

***

# 22. Now comes the important part: the DOM

This is where browser JavaScript becomes particularly interesting.

DOM means:

> **Document Object Model**

Your HTML:

```html
<h1>Hello</h1>
```

becomes an object structure that JavaScript can manipulate.

Conceptually:

```text
Browser
   │
   └── DOM
        │
        ├── html
        │
        ├── head
        │
        └── body
             │
             └── h1
                  │
                  └── "Hello"
```

JavaScript can manipulate this structure.

***

# 23. `document`

The browser gives JavaScript a global object called:

```javascript
document
```

Try:

```javascript
console.log(document);
```

You'll see the document representing your HTML page.

***

# 24. Find an HTML element

HTML:

```html
<h1 id="title">Hello</h1>
```

JavaScript:

```javascript
const title = document.getElementById("title");

console.log(title);
```

Now you have a JavaScript reference to that HTML element.

***

# 25. Change HTML

```javascript
const title = document.getElementById("title");

title.textContent = "Hello JavaScript!";
```

The browser changes the page.

This is the fundamental pattern:

```text
HTML
 ↓
JavaScript finds element
 ↓
JavaScript changes element
 ↓
Browser displays result
```

***

# 26. Your first interactive application

Create:

```text
hello-app
│
├── index.html
├── app.js
└── style.css
```

`index.html`:

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Hello App</title>
    <script src="app.js" defer></script>
</head>

<body>

    <h1 id="message">Hello!</h1>

    <button id="helloButton">
        Click me
    </button>

</body>

</html>
```

`app.js`:

```javascript
const button = document.getElementById("helloButton");
const message = document.getElementById("message");

button.addEventListener("click", () => {

    message.textContent = "Hello from JavaScript!";

});
```

Click the button.

You have just built a browser application.

***

# 27. Events

This is another fundamental concept.

The browser generates events:

```text
click
keydown
keyup
input
change
submit
mouseover
load
```

JavaScript can listen for them.

Example:

```javascript
button.addEventListener("click", () => {
    console.log("Button clicked!");
});
```

The general pattern is:

```javascript
element.addEventListener("event", handler);
```

This concept is absolutely fundamental for frontend development.

***

# 28. Reading user input

HTML:

```html
<input id="nameInput" type="text">

<button id="button">
    Say Hello
</button>

<p id="output"></p>
```

JavaScript:

```javascript
const input = document.getElementById("nameInput");
const button = document.getElementById("button");
const output = document.getElementById("output");

button.addEventListener("click", () => {

    const name = input.value;

    output.textContent = `Hello ${name}!`;

});
```

You now have:

```text
User
 │
 ▼
HTML input
 │
 ▼
JavaScript
 │
 ▼
DOM
 │
 ▼
HTML output
```

This is the foundation of countless web applications.

***

# 29. Your Celsius → Fahrenheit project

Since you've recently been working on a Celsius/Fahrenheit converter, this is an excellent JavaScript exercise.

Formula:

```text
°F = °C × 9/5 + 32
```

HTML:

```html
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Celsius Converter</title>
    <script src="app.js" defer></script>
</head>

<body>

    <h1>Celsius → Fahrenheit</h1>

    <input
        id="celsius"
        type="number"
        placeholder="Celsius"
    >

    <button id="convertButton">
        Convert
    </button>

    <p id="result"></p>

</body>

</html>
```

JavaScript:

```javascript
const celsiusInput =
    document.getElementById("celsius");

const convertButton =
    document.getElementById("convertButton");

const result =
    document.getElementById("result");


convertButton.addEventListener("click", () => {

    const celsius =
        Number(celsiusInput.value);

    const fahrenheit =
        celsius * 9 / 5 + 32;

    result.textContent =
        `${celsius} °C = ${fahrenheit} °F`;

});
```

Notice how many concepts you have now combined:

```text
variables
functions
numbers
DOM
events
input
type conversion
arithmetic
template literals
```

That's exactly how you should learn.

***

# 30. `Number()`

An important browser-JavaScript detail:

HTML input values are generally obtained as strings.

For example:

```javascript
const value = input.value;
```

might give:

```text
"25"
```

Therefore:

```javascript
Number(input.value)
```

converts it into:

```text
25
```

This distinction between:

```text
"25"
```

and:

```text
25
```

is very important in JavaScript.

***

# 31. Selecting elements

You should eventually learn:

```javascript
document.getElementById()
```

and:

```javascript
document.querySelector()
```

and:

```javascript
document.querySelectorAll()
```

For example:

```html
<p class="message">Hello</p>
```

JavaScript:

```javascript
const message =
    document.querySelector(".message");
```

CSS selectors work here:

```javascript
document.querySelector("#title");
document.querySelector(".message");
document.querySelector("button");
```

***

# 32. Creating HTML elements with JavaScript

JavaScript can create elements too.

```javascript
const paragraph =
    document.createElement("p");

paragraph.textContent =
    "Created by JavaScript!";

document.body.appendChild(paragraph);
```

Now JavaScript isn't merely changing HTML.

It is **creating HTML elements**.

***

# 33. Forms

Next learn forms.

```html
<form id="calculatorForm">

    <input id="number1" type="number">
    <input id="number2" type="number">

    <button type="submit">
        Add
    </button>

</form>

<p id="result"></p>
```

JavaScript:

```javascript
const form =
    document.getElementById("calculatorForm");

form.addEventListener("submit", (event) => {

    event.preventDefault();

    const a =
        Number(document.getElementById("number1").value);

    const b =
        Number(document.getElementById("number2").value);

    const result = a + b;

    document.getElementById("result")
        .textContent = result;

});
```

Notice:

```javascript
event.preventDefault();
```

This prevents the browser from performing the form's normal submission/navigation.

***

# 34. JavaScript modules

Once you understand the basics, learn modules.

Create:

```text
app.js
calculator.js
```

`calculator.js`:

```javascript
export function add(a, b) {
    return a + b;
}
```

`app.js`:

```javascript
import { add } from "./calculator.js";

console.log(add(10, 20));
```

And HTML:

```html
<script
    type="module"
    src="app.js">
</script>
```

This is a major milestone.

You are now learning modern JavaScript without npm, Node.js or Deno.

***

# 35. JSON

Next learn JSON.

Example:

```javascript
const person = {
    name: "Karl",
    age: 50
};
```

Convert to JSON:

```javascript
const json =
    JSON.stringify(person);

console.log(json);
```

Convert JSON back:

```javascript
const personAgain =
    JSON.parse(json);
```

JSON becomes extremely important once you start communicating with APIs.

***

# 36. HTTP and `fetch()`

And here is the part that should make you feel considerably less doomed. 😄

The browser has:

```javascript
fetch()
```

You don't need Node.js.

You don't need Deno.

You don't need Axios.

You don't need Postman.

Example:

```javascript
fetch("https://example.com")
    .then(response => response.text())
    .then(data => {
        console.log(data);
    });
```

Modern async/await:

```javascript
async function loadData() {

    const response =
        await fetch("https://example.com");

    const data =
        await response.text();

    console.log(data);
}

loadData();
```

Now you're doing asynchronous programming.

***

# 37. Promises

You should understand what `fetch()` returns.

```javascript
const response = fetch(url);
```

doesn't immediately give you the HTTP response.

It gives you a:

```text
Promise
```

Conceptually:

```text
fetch()
  │
  ▼
Promise
  │
  │ eventually
  ▼
HTTP Response
```

Then:

```javascript
const response = await fetch(url);
```

waits for that promise to settle.

Promises and `async/await` deserve their own learning phase.

***

# 38. Browser storage

The browser also provides storage APIs.

For example:

```javascript
localStorage.setItem(
    "name",
    "Karl"
);
```

Read it:

```javascript
const name =
    localStorage.getItem("name");

console.log(name);
```

Remove it:

```javascript
localStorage.removeItem("name");
```

This lets you build applications that remember information.

***

# 39. A real project: Todo List

At this point, build a Todo application.

```text
Todo App
│
├── index.html
├── style.css
├── app.js
└── todo.js
```

Features:

```text
[ Add todo ]

☐ Learn JavaScript
☐ Learn DOM
☐ Learn Fetch
☐ Build application
```

You will practice:

```text
DOM
events
arrays
objects
functions
modules
forms
localStorage
```

This one project can teach you a tremendous amount.

***

# 40. Debugging

Don't underestimate this.

Learn to use:

```javascript
console.log()
console.warn()
console.error()
```

For example:

```javascript
const result = calculate();

console.log("result =", result);
```

Also use:

```text
F12
→ Sources
→ breakpoints
```

You can stop execution and inspect:

```text
variables
objects
arrays
call stack
```

Learning the debugger is one of the biggest upgrades you can make as a developer.

***

# 41. Browser APIs

Once the JavaScript language itself becomes comfortable, explore the browser APIs.

You have access to things such as:

```text
DOM
Fetch API
Web Storage
URL API
History API
Timers
Events
WebSockets
Web Workers
Canvas
Geolocation
Clipboard
Web Crypto
```

Important distinction:

```text
JavaScript language
        +
Browser Web APIs
        =
Browser application
```

For example:

```javascript
setTimeout(() => {
    console.log("Hello after 1 second");
}, 1000);
```

`setTimeout` is provided by the environment rather than being the core JavaScript language itself.

That distinction becomes very useful later when comparing browser JavaScript with Node.js.

***

# 42. What you should NOT learn yet

This is important.

Because you are deliberately avoiding Node.js and Deno, don't compensate by immediately jumping into:

```text
React
Angular
TypeScript
Webpack
Vite
npm
Babel
Jest
ESLint
```

Not yet.

First become comfortable with:

```text
JavaScript
   ↓
Browser
   ↓
DOM
   ↓
Events
   ↓
HTTP
   ↓
Web APIs
```

Then frameworks become much easier.

***

# 43. A 30-Day Browser JavaScript Bootcamp

Given your preference for structured bootcamps, I'd learn it like this.

## Week 1 — JavaScript language

### Day 1

```text
What is JavaScript?
Browser DevTools
Console
Statements
Comments
```

Exercises:

```javascript
console.log("Hello");
console.log(2 + 2);
console.log("JavaScript");
```

### Day 2

```text
const
let
strings
numbers
booleans
null
undefined
```

### Day 3

```text
operators
===
!==
>
<
>=
<=
```

### Day 4

```text
if
else
else if
logical operators
```

### Day 5

```text
functions
parameters
return
```

### Day 6

```text
arrays
array indexes
array methods
```

### Day 7

```text
objects
properties
methods
```

**Mini-project:** Number guessing game.

***

# Week 2 — JavaScript + HTML

### Day 8

```text
HTML
<script>
external JavaScript
defer
```

### Day 9

```text
document
DOM
getElementById
querySelector
```

### Day 10

```text
textContent
innerHTML
attributes
classList
```

### Day 11

```text
events
click
input
change
keydown
```

### Day 12

```text
forms
event.preventDefault()
input.value
```

### Day 13

```text
createElement
appendChild
remove
```

### Day 14

**Mini-project:**

# Interactive Calculator

***

# Week 3 — Modern JavaScript

### Day 15

```text
template literals
destructuring
```

### Day 16

```text
spread
rest
```

### Day 17

```text
map()
filter()
find()
some()
every()
reduce()
```

### Day 18

```text
arrow functions
callbacks
```

### Day 19

```text
modules
export
import
type="module"
```

### Day 20

```text
JSON
JSON.parse()
JSON.stringify()
```

### Day 21

**Mini-project:**

# Contact Manager

Store contacts as:

```javascript
[
    {
        name: "Alice",
        email: "alice@example.com"
    },
    {
        name: "Bob",
        email: "bob@example.com"
    }
]
```

***

# Week 4 — Browser APIs

### Day 22

```text
Promises
```

### Day 23

```text
async
await
```

### Day 24

```text
fetch()
HTTP GET
```

### Day 25

```text
HTTP POST
JSON
Request
Response
```

### Day 26

```text
localStorage
```

### Day 27

```text
error handling
try
catch
finally
```

### Day 28

```text
debugging
breakpoints
call stack
DevTools
```

### Day 29

Build:

# Weather/API Dashboard

using:

```text
HTML
CSS
JavaScript
fetch()
async/await
JSON
DOM
```

### Day 30

Build your final project:

# Browser JavaScript Application

No:

```text
Node.js ❌
Deno ❌
npm ❌
React ❌
Angular ❌
```

Only:

```text
HTML
CSS
JavaScript
Browser
VS Code
PowerShell
```

***

# 44. Your project progression

I would actually recommend a sequence like this:

```text
                    JavaScript
                        │
                        ▼
                 Console exercises
                        │
                        ▼
                  Small programs
                        │
                        ▼
                       DOM
                        │
                        ▼
                     Events
                        │
                        ▼
                      Forms
                        │
                        ▼
                     Modules
                        │
                        ▼
                       JSON
                        │
                        ▼
                    Fetch / HTTP
                        │
                        ▼
                   localStorage
                        │
                        ▼
                 Real application
```

Projects:

```text
01  Hello JavaScript
02  Number Guessing Game
03  Celsius → Fahrenheit
04  Calculator
05  Counter
06  Todo List
07  Contact Manager
08  Quiz
09  Expense Tracker
10  API Dashboard
```

***

# 45. And PowerShell is still useful!

PowerShell isn't your JavaScript runtime.

Instead, use it as your **developer toolbox**.

For example:

```powershell
mkdir JavaScript
cd JavaScript

mkdir 01-basics
mkdir 02-dom
mkdir 03-events
mkdir 04-projects

code .
```

You can inspect files:

```powershell
Get-ChildItem
```

Navigate:

```powershell
Set-Location .\01-basics
```

Create files:

```powershell
New-Item index.html
New-Item app.js
```

And open your project:

```powershell
code .
```

You don't need a JavaScript package manager to learn JavaScript.

***

# 46. The most important mental model

I would keep this picture in your Zettelkasten:

```text
                 YOUR COMPUTER
                      │
             ┌────────┴────────┐
             │                 │
        VS Code             PowerShell
             │                 │
             │             manages files
             │
          writes
             │
             ▼
        index.html
          app.js
         style.css
             │
             │
             ▼
          BROWSER
             │
      ┌──────┴───────┐
      │              │
     HTML           CSS
      │              │
      └──────┬───────┘
             │
             ▼
            DOM
             │
             ▲
             │
       JavaScript
             │
      ┌──────┼─────────┐
      │      │         │
    Events   DOM      Fetch
      │      │         │
      └──────┴─────────┘
             │
             ▼
        Web APIs
```

**That is enough to become very good at browser JavaScript.**

And then, when you eventually encounter Node.js, Deno, React, Angular or Electron, you'll have a much stronger foundation because you'll understand **what JavaScript itself is and what the host environment provides**.

So no, Karl — **you are absolutely not doomed.** 😄

Actually, your restriction is a pretty good learning exercise:

> **"I have a browser. Make me learn JavaScript properly."**

That's a surprisingly excellent challenge.

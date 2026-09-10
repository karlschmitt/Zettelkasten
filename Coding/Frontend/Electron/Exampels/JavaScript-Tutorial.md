---
id: 20260909222552
title: Quickstart JavaScript Tutorial
author: Karl Schmitt
date: 2026-09-09
keywords: [ JavaScript ]
---

## 🚀 Quickstart JavaScript Tutorial

This tutorial covers the absolute essentials of JavaScript. You can run all of this code directly inside your web browser.

To test it, right-click anywhere on this webpage, select Inspect, and click the Console tab. Copy and paste the code examples below to see them work.

***

## 1. Variables and Data Types

Variables are containers that store data. Use `let` for values that can change and `const` for values that stay constant.

```javascript
// Storing different types of data
const name = "Alice";       // String (text)
let age = 25;               // Number
const isCoding = true;      // Boolean (true or false)

// Updating a variable
age = 26; 

// Printing the result to the console
console.log(name + " is now " + age + " years old.");
```

***

## 2. Conditionals (Making Decisions)

Conditionals allow your code to make choices based on specific criteria.

```javascript
let time = 14; // 2:00 PM (24-hour format)

if (time < 12) {
    console.log("Good morning!");
} else if (time < 18) {
    console.log("Good afternoon!");
} else {
    console.log("Good evening!");
}
```

***

## 3. Functions

Functions are reusable blocks of code designed to perform a specific task. They take inputs (arguments) and return outputs.

```javascript
// Defining a function
function greetUser(username) {
    return "Welcome back, " + username + "!";
}

// Calling the function and saving the result
let message = greetUser("Alex");
console.log(message); // Outputs: Welcome back, Alex!
```

***

## 4. Arrays and Objects

Arrays store lists of items, while objects store collections of related data using key-value pairs.

```javascript
// Array: A list of items
let programmingLanguages = ["HTML", "CSS", "JavaScript"];
console.log(programmingLanguages[2]); // Outputs: JavaScript (arrays start at index 0)

// Object: A collection of properties
let userProfile = {
    firstName: "Sarah",
    lastName: "Smith",
    completedProjects: 5
};
console.log(userProfile.firstName + " completed " + userProfile.completedProjects + " projects.");
```

***

## 5. Interacting with a Webpage (The DOM)

JavaScript shines when it interacts with HTML. The snippet below shows how JavaScript finds an HTML element, changes its text, and listens for a user interaction.

```javascript
// 1. Find an HTML element on the page (assuming an element with id="my-button" exists)
const button = document.querySelector("#my-button");

// 2. Listen for a user click, then run a function
button.addEventListener("click", function() {
    alert("You clicked the button!");
});
```

***

Would you like to build a simple project next (like a digital clock or a calculator), or should we dive deeper into how to link JavaScript into an actual HTML file?


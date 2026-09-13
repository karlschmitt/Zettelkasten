---
id: 20260912135054
title: JavaScript Promises
author: Karl Schmitt
date: 2026-09-12
---

# JavaScript Promises

In JavaScript, operations like fetching data from a server or reading a file take time to complete. Rather than stopping the entire program while waiting, JavaScript handles these operations asynchronously.

![JavaScript Logo](../Images/JavaScript_Logo.png)

A **Promise** is a placeholder for a value that will be available in the future—representing an operation that hasn't finished yet, but will eventually succeed or fail.



## The Analogy: Ordering at a Restaurant

Imagine ordering food at a fast-food counter:



1. You place your order and receive a **buzzer/receipt**. This is your **Promise**.


2. While waiting, the Promise is **Pending** (food is cooking).


3. If everything goes right, the buzzer lights up with your meal: the Promise is **Fulfilled** (Resolved).


4. If the kitchen runs out of ingredients, you get an error message: the Promise is **Rejected**.



## 1. The 3 States of a Promise

A Promise always exists in one of three states:



```
                  ┌──────────────┐
                  │   PENDING    │
                  └──────┬───────┘
                         │
           ┌─────────────┴─────────────┐
           ▼                           ▼
    ┌──────────────┐            ┌──────────────┐
    │  FULFILLED   │            │   REJECTED   │
    │  (Resolved)  │            │   (Error)    │
    └──────────────┘            └──────────────┘
```

* **Pending:** Initial state, neither fulfilled nor rejected.


* **Fulfilled:** The operation succeeded, and the result value is ready.


* **Rejected:** The operation failed, and an error reason is provided.



## 2. Creating a Promise

You create a Promise using the `new Promise()` constructor, which takes a function with two callback arguments: `resolve` and `reject`.



JavaScript

```
const checkInventory = new Promise((resolve, reject) => {
  const itemInStock = true;

  setTimeout(() => {
    if (itemInStock) {
      resolve("Item is in stock! Ready to ship.");
    } else {
      reject("Out of stock! Order cancelled.");
    }
  }, 2000); // Simulates a 2-second delay
});
```

## 3. Consuming a Promise (`.then()`, `.catch()`, `.finally()`)

To handle the outcome of a Promise, attach handler methods to it:



* `.then()` runs when the Promise is **fulfilled** (resolved).


* `.catch()` runs when the Promise is **rejected** (failed).


* `.finally()` runs regardless of success or failure.



JavaScript

```
checkInventory
  .then((message) => {
    console.log("Success:", message);
  })
  .catch((error) => {
    console.log("Error:", error);
  })
  .finally(() => {
    console.log("Operation completed.");
  });
```

## 4. Promise Chaining

One major advantage of Promises is avoiding nested callbacks (often called "Callback Hell"). You can chain multiple `.then()` calls sequentially:



JavaScript

```
function fetchUser(userId) {
  return new Promise((resolve) => {
    setTimeout(() => resolve({ id: userId, username: "alex99" }), 1000);
  });
}

function fetchUserPosts(username) {
  return new Promise((resolve) => {
    setTimeout(() => resolve(["Post 1", "Post 2", "Post 3"]), 1000);
  });
}

// Chaining promises sequentially
fetchUser(101)
  .then((user) => {
    console.log(`User found: ${user.username}`);
    return fetchUserPosts(user.username); // Returns another promise
  })
  .then((posts) => {
    console.log("User posts:", posts);
  })
  .catch((err) => {
    console.error("Failed to fetch data:", err);
  });
```

## 5. Modern Alternative: `async / await`

Introduced in ES8, `async` and `await` are built on top of Promises to make asynchronous code look and behave like synchronous code.



* `async`: Declares that a function returns a Promise.


* `await`: Pauses function execution until the Promise settles.

JavaScript

```
async function getUserData() {
  try {
    const user = await fetchUser(101);
    console.log(`User found: ${user.username}`);

    const posts = await fetchUserPosts(user.username);
    console.log("User posts:", posts);
  } catch (error) {
    console.error("An error occurred:", error);
  }
}

getUserData();
```

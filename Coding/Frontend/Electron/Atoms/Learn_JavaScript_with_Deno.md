---
id: 20260910190841
title: Learn JavaScript with Deno
author: Karl Schmitt
date: 2026-09-10
keywords: [ JavaScript, Deno ]
---

![JavaScript Logo](../Images/JavaScript-logo.png)

# Learn JavaScript with Deno

> [NOTE!]
>  Feel free to follow the white rabit: [JavaScript](./JavaScript.md)

**Deno** is a modern, fast, and secure environment for running JavaScript outside the browser.

Unlike traditional JavaScript runtimes, Deno requires **zero configuration** to get started and comes with built-in tools for formatting, testing, and modern Web APIs (like `fetch`) out of the box.


## Step 1: Install Deno

Open your system terminal (Terminal on macOS/Linux or PowerShell on Windows) and run the command for your OS:



* **macOS / Linux:**



  Bash

  ```
  curl -fsSL https://deno.land/install.sh | sh
  ```

* **Windows (PowerShell):**



  PowerShell

  ```
  irm https://deno.land/install.ps1 | iex
  ```

Once installed, verify it works by checking the version:



Bash

```
deno --version
```

## Step 2: Write Your First JavaScript File

Create a new directory for your project, open it, and create a file named `app.js`:



Bash

```
mkdir my-deno-app
cd my-deno-app
```

Open `app.js` in a text editor (such as VS Code) and add the following fundamentals:



JavaScript

```
// 1. Variables and Constants
const appName = "Deno Beginner Tutorial";
let userCount = 1;

// 2. Data Types
const user = {
  name: "Alex",
  age: 25,
  isLearning: true,
};

// 3. Functions
function greet(person) {
  return `Welcome ${person.name}! You are learning JavaScript with ${appName}.`;
}

// 4. Console Output
console.log(greet(user));
```

Run your code directly with Deno:



Bash

```
deno run app.js
```

## Step 3: Understand Security & Permissions

Deno is **secure by default**. By default, a script cannot access the disk, network, or environment variables unless explicitly granted permission via command-line flags.



Create a new file called `fetch_data.js` to fetch web data using JavaScript's native `fetch` API:



JavaScript

```
// Fetching data from a public REST API
console.log("Fetching user data...");

const response = await fetch("https://jsonplaceholder.typicode.com/users/1");
const data = await response.json();

console.log(`User Name: ${data.name}`);
console.log(`Email: ${data.email}`);
```

### Try Running Without Permissions

If you run this directly:



Bash

```
deno run fetch_data.js
```

Deno will pause and ask for interactive approval to access the network.



### Grant Network Access

To run it cleanly, provide the `--allow-net` flag:



Bash

```
deno run --allow-net fetch_data.js
```

## Step 4: Build a Simple Web Server

Deno includes a built-in HTTP server module with no third-party package setup required.



Create a file named `server.js`:



JavaScript

```
Deno.serve((req) => {
  return new Response("Hello, World! Powered by Deno.");
});
```

Run the server with network access:



Bash

```
deno run --allow-net server.js
```

Open your browser and navigate to `http://localhost:8000` to view the response.



## Key Deno Commands to Know

* **Run a script:** `deno run app.js`


* **Format code:** `deno fmt`


* **Check for code issues (Linting):** `deno lint`


* **Run built-in tests:** `deno test`


---
id: 20260911201159
---

JavaScript runs inside the browser by default, but **Node.js** lets you run JavaScript on your computer as a backend server or command-line program.



## Phase 1: Environment Setup

1. **Install Node.js:** Download and install the **LTS (Long Term Support)** version from [nodejs.org](https://nodejs.org/).



2. **Verify Installation:** Open your Terminal (Mac/Linux) or Command Prompt / PowerShell (Windows) and type:



   Bash

   ```
   node -v
   ```

   If it prints a version number (e.g., `v20.x.x` or `v22.x.x`), you are ready to go.



## Phase 2: Core JavaScript Fundamentals

Create a new folder on your computer, open it in a text editor (like VS Code), and create a file named `app.js`. Run your code anytime in the terminal using:



Bash

```
node app.js
```

### 1. Variables & Data Types

Use `const` for values that stay constant and `let` for variables that change. Avoid using `var`.



JavaScript

```
// Strings, Numbers, and Booleans
const name = "Alex";
let age = 25;
const isLearningNode = true;

age = 26; // Reassigning a 'let' variable is allowed

console.log(`Hello, my name is ${name} and I am ${age} years old.`);
```

### 2. Conditionals (If/Else)

Control code execution based on specific conditions:



JavaScript

```
const score = 85;

if (score >= 90) {
  console.log("Grade: A");
} else if (score >= 80) {
  console.log("Grade: B");
} else {
  console.log("Grade: C");
}
```

### 3. Arrays & Objects

Store complex data structures using lists (arrays) and key-value pairs (objects):



JavaScript

```
// Arrays (Lists of items)
const fruits = ["Apple", "Banana", "Cherry"];
fruits.push("Date"); // Adds to the end

console.log(fruits[0]); // Prints: Apple

// Objects (Key-value maps)
const user = {
  username: "coder123",
  role: "admin",
  active: true
};

console.log(user.username); // Prints: coder123
```

### 4. Functions

Functions group reusable blocks of logic together:



JavaScript

```
// Arrow function syntax (modern standard)
const greetUser = (userName) => {
  return `Welcome back, ${userName}!`;
};

const message = greetUser("Jordan");
console.log(message);
```

## Phase 3: Node.js Specific Features

Node.js provides built-in modules to interact with the operating system and file system.



### 1. Reading and Writing Files (`fs` Module)

Create a file named `sample.txt` in the same directory, write `Hello from file!` inside it, and load it with this code:



JavaScript

```
const fs = require('fs');

// Reading a file asynchronously
fs.readFile('sample.txt', 'utf8', (err, data) => {
  if (err) {
    console.error("Error reading file:", err);
    return;
  }
  console.log("File Contents:", data);
});
```

### 2. Building a Basic HTTP Web Server

Paste this into `server.js` to create your first backend server:



JavaScript

```
const http = require('http');

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello! Your Node.js server is up and running.');
});

const PORT = 3000;
server.listen(PORT, () => {
  console.log(`Server listening at http://localhost:${PORT}`);
});
```

Run `node server.js` in your terminal and visit `http://localhost:3000` in your web browser.

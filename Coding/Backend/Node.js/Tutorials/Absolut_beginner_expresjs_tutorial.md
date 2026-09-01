---
id: 20260901103203
title: Absolut Beginner express.js Tutorial
author: Karl Schmitt
date: 2026-09-01
---

# Absolut Beginner express.js Tutorial

Now that you know what Node.js is, **Express.js** is the next logical step. 

If Node.js is the "engine" of a car, Express.js is the **steering wheel, dashboard, and pedals**. It’s a framework that makes building web servers much faster and easier than using the built-in Node "http" module.

---

### 1. Setup Your Project
Let’s start a brand new project. Open your terminal and run these commands:

```bash
mkdir my-express-app
cd my-express-app
npm init -y
npm install express
```

This creates a folder, initializes a `package.json` file, and downloads the Express library.

---

### 2. The "Hello World" of Express
Create a file named `index.js` and paste this code:

```javascript
const express = require('express'); // Import express
const app = express();              // Initialize the app
const port = 3000;                  // Define a port

// This is a "Route"
app.get('/', (req, res) => {
  res.send('Welcome to my Express Server!');
});

// Start the server
app.listen(port, () => {
  console.log(`App listening at http://localhost:${port}`);
});
```

**Run it:** `node index.js`  
Go to `http://localhost:3000` in your browser.

---

### 3. Understanding Routing
In the basic Node.js tutorial, handling different URLs (like `/about` or `/contact`) involved a lot of messy `if/else` statements. In Express, it’s very clean.

Update your `index.js` with more routes:

```javascript
app.get('/', (req, res) => {
  res.send('This is the Home Page');
});

app.get('/about', (req, res) => {
  res.send('This is the About Page');
});

app.get('/api/user', (req, res) => {
  // You can also send JSON (perfect for mobile apps or modern web apps)
  res.json({
    username: 'JohnDoe',
    id: 1
  });
});
```
*Restart your server and visit `http://localhost:3000/about` and `http://localhost:3000/api/user`.*

---

### 4. Serving HTML Files
Usually, you don't want to just send strings of text. You want to send whole HTML files.

1. Create a folder named `public`.
2. Inside `public`, create a file named `index.html`.
3. Add some basic HTML to it: `<h1>Hello from HTML!</h1>`.
4. In your `index.js`, add this **one line** of code (put it above your routes):

```javascript
app.use(express.static('public'));
```

Now, if you go to `http://localhost:3000/index.html`, Express will automatically serve any file inside that folder.

---

### 5. Middleware (The "In-Between" Code)
"Middleware" is a fancy word for code that runs **after** the request is received, but **before** the final response is sent. It's like a security guard checking your ID before you enter a club.

Let’s make a simple logger middleware. Add this to `index.js`:

```javascript
app.use((req, res, next) => {
  console.log(`${req.method} request made to: ${req.url}`);
  next(); // This tells Express to move to the next function
});
```

Now, every time you refresh your browser, your terminal will log exactly what page was requested.

---

### 6. The "Developer Pro" Tool: Nodemon
Right now, every time you change your code, you have to stop the server (`Ctrl+C`) and start it again (`node index.js`). This is annoying. 

**Nodemon** is a tool that restarts the server for you automatically whenever you save a file.

1. **Install it globally:**
   ```bash
   npm install -g nodemon
   ```
2. **Run your app with it:**
   ```bash
   nodemon index.js
   ```
*Now, try changing a string in your code and saving. The server restarts instantly!*

---

### Summary: Express vs. Pure Node
| Feature | Pure Node.js (http) | Express.js |
| :--- | :--- | :--- |
| **Routing** | Complex `if/else` on `req.url` | Simple `app.get()`, `app.post()` |
| **JSON** | Manual stringifying | `res.json()` |
| **Static Files** | Manual file reading (fs) | `express.static()` |
| **Code Length** | Long and verbose | Short and readable |

### What to learn next?
1. **Route Parameters:** How to handle URLs like `/users/123` (using `req.params`).
2. **POST Requests:** How to handle data sent from an HTML form.
3. **Template Engines:** Using **EJS** or **Pug** to inject dynamic data into HTML.
4. **Databases:** Connecting Express to **MongoDB** (the most popular choice for Express).
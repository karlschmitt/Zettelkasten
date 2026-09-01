---
id: 20260901103814
title: Absolut Beginner node.js Tutorial
author: Karl Schmitt
date: 2026-09-01
---

# Absolut Beginner node.js Tutorial

Welcome to the world of Node.js! This tutorial is designed for someone who knows a little bit of JavaScript but has never used it outside of a web browser.

---

### 1. What is Node.js?
In the past, JavaScript could only run **inside** a web browser (like Chrome or Firefox) to make websites interactive. 

**Node.js** is a "runtime" that lets you run JavaScript on your **computer** (server-side). This means you can use JavaScript to build tools, manage files, and create web servers.

---

### 2. Installation
1. Go to [nodejs.org](https://nodejs.org/).
2. Download the version labeled **"LTS"** (Long Term Support) — it’s the most stable.
3. Run the installer.
4. To check if it worked, open your **Terminal** (Mac/Linux) or **Command Prompt** (Windows) and type:
   ```bash
   node -v
   ```
   If you see a version number (like `v20.11.0`), you’re ready!

---

### 3. Your First Node.js Script
Unlike the browser, you don't need an HTML file to run Node.js.

1. Create a folder on your computer named `node-tutorial`.
2. Inside that folder, create a file named `app.js`.
3. Open `app.js` in a text editor (like VS Code) and type:
   ```javascript
   const name = "Beginner";
   console.log("Hello, " + name + "! You are running JavaScript on your computer.");
   ```
4. Go back to your terminal, navigate to that folder, and run:
   ```bash
   node app.js
   ```
   You should see the message printed in your terminal!

---

### 4. Modules (Built-in Tools)
Node.js comes with "Modules" — pre-written code to help you do things like read files or handle internet traffic.

Let’s use the **`os`** module to get info about your computer. Update `app.js`:

```javascript
const os = require('os'); // This "imports" the module

console.log("Platform: " + os.platform());
console.log("Free Memory: " + os.freemem() + " bytes");
```
Run `node app.js` again to see the results.

---

### 5. Creating a Simple Web Server
This is the "classic" Node.js example. We will create a server that listens for requests from a browser.

Create a new file named `server.js` and paste this:

```javascript
const http = require('http');

// Create the server
const server = http.createServer((req, res) => {
    // req = the request coming from the user
    // res = the response we send back

    res.statusCode = 200; // Success code
    res.setHeader('Content-Type', 'text/plain');
    res.end('Hello! This is your Node.js server speaking.');
});

// Tell the server to listen on port 3000
server.listen(3000, '127.0.0.1', () => {
    console.log('Server running at http://127.0.0.1:3000/');
});
```

**How to run it:**
1. In your terminal, run: `node server.js`
2. Open your web browser and go to: `http://localhost:3000`
3. You will see your message! To stop the server, press **Ctrl + C** in your terminal.

---

### 6. NPM (Node Package Manager)
When you installed Node, you also installed **NPM**. This is the world’s largest library of free code packages that you can use so you don't have to reinvent the wheel.

**How to use NPM:**
1. In your terminal, inside your folder, type: 
   ```bash
   npm init -y
   ```
   (This creates a `package.json` file, which keeps track of your project settings).

2. Let's install a fun package called `cowsay`:
   ```bash
   npm install cowsay
   ```

3. Create a file called `test-npm.js`:
   ```javascript
   const cowsay = require("cowsay");

   console.log(cowsay.say({
       text : "I am a moo-ing Node module!",
       e : "oO",
       T : "U "
   }));
   ```

4. Run it: `node test-npm.js`.

---

### 7. What should you learn next?
You’ve just scratched the surface! Here is the recommended path for a beginner:

1.  **Express.js:** The most popular framework for Node. It makes building real websites and APIs much easier than the "http" example we did above.
2.  **File System (fs) Module:** Learn how to create, read, and delete files on your hard drive.
3.  **Asynchronous Programming:** Learn about `Promises` and `async/await` (this is crucial for Node.js).
4.  **Databases:** Learn how to connect Node to a database like **MongoDB** or **PostgreSQL**.

### Summary Cheat Sheet
*   **Run a file:** `node filename.js`
*   **Install a package:** `npm install package-name`
*   **Stop a running script:** `Ctrl + C`
*   **Import a module:** `const module = require('module-name');`
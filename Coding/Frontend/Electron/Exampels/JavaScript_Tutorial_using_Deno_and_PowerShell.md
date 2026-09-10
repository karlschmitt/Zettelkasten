---
id: 20260910090716
title: Backend JavaScript Tutorial
author: Karl Schmitt
date: 2026-09-10
keywords: [ JavaScript, Deno, PowerShell, Backend]
---

![JavaScript Logo](../Images/JavaScript-logo.png)

# Backend JavaScript Tutorial

> [NOTE!]
>  Feel free to follow the white rabbit 🐇: [JavaScript](../Atoms/JavaScript.md)

> [NOTE!]
>  Feel free to follow the dinosaur 🦖: [Learn JavaScript with Deno](../Atoms/Learn_JavaScript_with_Deno.md)

## 🦕 Deno + 💻 PowerShell: 


Deno is a modern, secure runtime for JavaScript and TypeScript. Unlike running JavaScript inside a web browser, Deno allows you to write JavaScript code that runs directly on your computer to manage files, build web servers, and create automation scripts.

Using Windows PowerShell, you can install Deno, manage files, and execute your scripts.

***

## Step 1: Install Deno via PowerShell

1. Open PowerShell (Click Start, type `PowerShell`, and hit Enter).
2. Copy and paste the official installation command from [Deno Docs](https://docs.deno.com/runtime/) and press Enter:
   ```powershell
   irm https://deno.land | iex
   ```
3. Restart your PowerShell window so it recognizes the newly added path.
4. Verify the installation by checking the version:
   ```powershell
   deno --version
   ```
***

## Step 2: Create Your First Project Folder

Use PowerShell commands to create a workspace and navigate into it: \[8]

```powershell
mkdir deno_tutorial
cd deno_tutorial
```

***

## Step 3: Write and Run a "Hello World" Script

Create a simple JavaScript file directly from PowerShell.

1. Run this command to create a file named `app.js` containing a log statement:
   ```powershell
   "console.log('Hello from Deno and PowerShell!');" | Out-File -Encoding utf8 app.js
   ```
2. Execute the script using the [Deno CLI](https://docs.deno.com/examples/):
   ```powershell
   deno run app.js
   ```
   _Output:_ `Hello from Deno and PowerShell!` 

***

## Step 4: Understanding Deno's Sandbox Security

Deno is secure by default. It will not allow a script to read files, write files, or access the network unless you explicitly grant permission.

Let's write a script that fetches data from the web using the standard browser `fetch` API.

1. Create a script called `fetch_data.js` to download some placeholder data:
   ```powershell
   @'
   const response = await fetch("https://typicode.com");
   const data = await response.json();
   console.log("Fetched Data:", data);
   '@ | Out-File -Encoding utf8 fetch_data.js
   ```
2. Try running it without permissions:
   ```powershell
   deno run fetch_data.js
   ```
   _Deno will stop execution and prompt you to grant network privileges._
3. Run it correctly by adding the explicit network flag (`--allow-net`):
   ```powershell
   deno run --allow-net fetch_data.js
   ```

***

## Step 5: Read and Write System Files

Let's leverage JavaScript to write a message to a text file locally, and then read it back.

1. Create `file_system.js` using PowerShell:
   ```powershell
   @'
   const text = "Deno allows me to write backend JavaScript!";

   // Write a text file
   await Deno.writeTextFile("output.txt", text);
   console.log("File written successfully!");

   // Read the text file back
   const data = await Deno.readTextFile("output.txt");
   console.log("File Content:", data);
   '@ | Out-File -Encoding utf8 file_system.js
   ```
2. Because this script touches your local hardware, you must grant read and write permissions (`--allow-read` and `--allow-write`):
   ```powershell
   deno run --allow-read --allow-write file_system.js
   ```

***

Would you like to build a local web server next using Deno, or would you like to see how to pass command-line arguments from PowerShell directly into your JavaScript code?


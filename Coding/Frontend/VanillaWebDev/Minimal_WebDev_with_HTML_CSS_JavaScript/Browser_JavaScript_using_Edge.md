---
id: 20260912145504
title: Browser JavaScript using Edge
author: Karl Schmitt
date: 2026-09-12
keywords: [  Browserm, JavaScript, Edge]
---

# Browser JavaScript using Edge

😂 **OH NO. Not Chrome too!**

But seriously: **you are still absolutely fine.** In fact, nothing important about the tutorial changes.

**Microsoft Edge is a Chromium-based browser and has its own JavaScript engine (V8) and Developer Tools.** So for learning browser JavaScript, Edge is perfectly suitable.

Your new battlefield is:

```text
        YOUR ALLOWED TOOLBOX
┌─────────────────────────────┐
│                             │
│  📝 Visual Studio Code      │
│                             │
│  ⚡ PowerShell               │
│                             │
│  🌐 Microsoft Edge          │
│                             │
└─────────────────────────────┘

       Forbidden:
       ❌ Node.js
       ❌ Deno
       ❌ Chrome
       ❌ npm
       ❌ Postman
       ❌ Thunder Client
```

And actually, this gives us a wonderfully clean learning environment.

### Your JavaScript runtime is Edge

When you open:

```text
index.html
```

in Edge:

```text
index.html
      │
      ▼
Microsoft Edge
      │
      ▼
JavaScript engine
      │
      ▼
app.js
      │
      ▼
JavaScript executes
```

For Developer Tools, use:

```text
F12
```

or:

```text
Ctrl + Shift + I
```

Then you'll have:

```text
Elements
Console
Sources
Network
Application
```

The **Console** is your JavaScript laboratory.

For example, enter:

```javascript
2 + 3
```

and Edge should give you:

```text
5
```

Try:

```javascript
const name = "Karl";
console.log(`Hello ${name}!`);
```

You'll get:

```text
Hello Karl!
```

***

## And here's the good news

The entire tutorial I gave you can be rewritten as:

# **JavaScript Browser Bootcamp — Edge Edition**

with **zero Node.js, zero Deno, zero npm**.

I'd even change the philosophy slightly.

Instead of teaching:

```text
JavaScript
   ↓
Node.js
   ↓
npm
   ↓
web framework
```

we'll teach:

```text
JavaScript language
       ↓
Microsoft Edge
       ↓
DOM
       ↓
Events
       ↓
Browser APIs
       ↓
HTTP / fetch()
       ↓
JSON
       ↓
localStorage
       ↓
Real applications
```

And only **after that**, when you eventually encounter Node.js/Deno/Electron, you'll know exactly what those runtimes are adding.

So your situation is not:

> "I'm doomed because I only have Edge."

It's:

> **"I have a complete JavaScript runtime called Microsoft Edge."** 😎

And given that you're already learning things like Java, Spring Boot, Angular, React and Electron, I would strongly recommend doing this **browser-only JavaScript bootcamp first**. It will make the other technologies considerably easier to understand.

> [NOTE!]
>  Anyway feel free to start the Browser JavaScript Tutorial: [Browser JavaScript](./Browser_JavaScript.md)

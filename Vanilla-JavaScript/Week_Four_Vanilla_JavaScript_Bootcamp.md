---
id: 20260420153017
title: Week Four Vanilla JavaScript Bootcamp
author: Karl Schmitt
date: 2026-04-20
keywords: [ Vanilla, JavaScript, Bootcamp]
---
# Week Four Vanilla JavaScript Bootcamp

Now you’re entering **real web development territory** 🌐🔥\
Week 4 is a big step: your app will talk to the internet.

***

# 🚀 Week 4: Vanilla JavaScript Bootcamp (APIs, Async, Real Data)

## 🎯 Goal of Week 4

You will:

* Fetch real data from the internet 🌍

* Understand **async JavaScript**

* Work with **JSON**

* Build your first **real-world app (Weather App)**

***

# 🗓️ Day 1 — What is an API?

## 🧠 Learn

An API is just a URL that returns data.

Example:

```
https://api.github.com/users/octocat
```

👉 Open it in Chrome → you’ll see JSON data.

***

## 🧪 Practice

In DevTools Console:

```javascript
fetch("https://api.github.com/users/octocat")
  .then(response => response.json())
  .then(data => console.log(data));
```

***

## 💡 Key Idea

* `fetch()` → gets data

* `.then()` → waits for result

* `.json()` → converts to JS object

***

# 🗓️ Day 2 — Promises & Async (Simple Explanation)

## 🧠 Learn

Think of async like ordering food:

* You order 🍔

* You don’t block the kitchen

* You get it later

***

## 🔧 Modern syntax (IMPORTANT)

```javascript
async function loadUser() {
  const response = await fetch("https://api.github.com/users/octocat");
  const data = await response.json();

  console.log(data);
}

loadUser();
```

***

## 🎯 Task

Change output:

```javascript
console.log(data.login);
console.log(data.public_repos);
```

***

# 🗓️ Day 3 — Display API Data in HTML

## 🎯 Goal

Show API data on your page

***

### HTML

```html
<h1 id="name"></h1>
<p id="repos"></p>
```

***

### JS

```javascript
async function loadUser() {
  const response = await fetch("https://api.github.com/users/octocat");
  const user = await response.json();

  document.querySelector("#name").textContent = user.login;
  document.querySelector("#repos").textContent = user.public_repos;
}

loadUser();
```

***

# 🗓️ Day 4 — User Input + API

## 🎯 Goal

Search for any GitHub user

***

### HTML

```html
<input id="username" placeholder="GitHub username">
<button id="search">Search</button>

<h2 id="output"></h2>
```

***

### JS

```javascript
const input = document.querySelector("#username");
const button = document.querySelector("#search");

button.addEventListener("click", async function() {
  const username = input.value;

  const response = await fetch(`https://api.github.com/users/${username}`);
  const user = await response.json();

  document.querySelector("#output").textContent = user.login;
});
```

***

# 🗓️ Day 5 — Error Handling (VERY IMPORTANT)

## 🧠 Learn

What if user doesn’t exist?

***

```javascript
try {
  const response = await fetch(url);

  if (!response.ok) {
    throw new Error("User not found");
  }

  const data = await response.json();
} catch (error) {
  console.log(error.message);
}
```

***

## 🎯 Task

Show error in UI instead of console.

***

# 🗓️ Day 6 — Mini Project: Weather App 🌦️

## 🎯 Goal

User enters city → shows weather

***

## 🧠 Use this free API:

👉 [https://wttr.in](https://wttr.in/) (no API key needed)

***

### Example:

```
https://wttr.in/London?format=j1
```

***

### HTML

```html
<input id="city" placeholder="Enter city">
<button id="getWeather">Get Weather</button>

<h2 id="weather"></h2>
```

***

### JS

```javascript
const btn = document.querySelector("#getWeather");
const output = document.querySelector("#weather");

btn.addEventListener("click", async function() {
  const city = document.querySelector("#city").value;

  const response = await fetch(`https://wttr.in/${city}?format=j1`);
  const data = await response.json();

  const temp = data.current_condition[0].temp_C;

  output.textContent = `Temperature: ${temp}°C`;
});
```

***

# 🗓️ Day 7 — Improve Your Weather App

## 🎯 Add Features

* Show:

  * temperature 🌡️

  * weather description ☁️

  * feels like 🤔

***

```javascript
const condition = data.current_condition[0].weatherDesc[0].value;
const feelsLike = data.current_condition[0].FeelsLikeC;
```

***

## 🧪 Bonus Ideas

* Press **Enter** to search

* Show loading text (“Loading…”)

* Handle invalid city

***

# 🧠 End of Week 4 — You Now Understand

🔥 Fetch API\
🔥 Async / await\
🔥 JSON data\
🔥 Error handling\
🔥 Real API integration\
🔥 Building real-world apps

***

# 💪 Practice Ideas

Build:

* 🌍 Country info app (REST Countries API)

* 🐱 Random cat image app

* 🎮 Simple game with API score

***

# 🚀 Week 5 Preview

Now we level up your app quality:

👉 Code organization\
👉 Reusable functions\
👉 Separation of concerns\
👉 LocalStorage (save data!)\
👉 Better UI structure

***

If you're ready:

👉 **“Week 5 please”**

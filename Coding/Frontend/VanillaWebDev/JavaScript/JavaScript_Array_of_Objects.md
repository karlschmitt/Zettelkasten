---
id: 20260414164533
title: Array of Objects
date: 2026-04-16
keywords: [ JavaScript, Array, Objects]
---
#  Array of Objects

Perfect — this is the **next big step** in JavaScript 🚀
Arrays of objects are _everywhere_ (APIs, databases, real apps).

Let’s keep it **simple, practical, and Deno-friendly** 👍

***

# 🧠 1. What is an Array of Objects?

👉 It’s just a **list of objects**:

```javascript
const people = [
  { name: "Luke", role: "Jedi" },
  { name: "Leia", role: "Princess" },
  { name: "Han", role: "Smuggler" }
];
```

👉 Think:

```
Array → []
Objects → {}
```

***

# ▶️ 2. Run with Deno

```bash
deno run array.js
```

***

# 🔍 3. Access Data

```javascript
console.log(people[0]);           // First object
console.log(people[0].name);      // Luke
console.log(people[1].role);      // Princess
```

***

# 🔁 4. Loop Through Array

### Classic loop:

```javascript
for (let i = 0; i < people.length; i++) {
  console.log(people[i].name);
}
```

### Modern (recommended):

```javascript
for (const person of people) {
  console.log(person.name);
}
```

***

# ⚡ 5. Useful Array Methods (VERY IMPORTANT)

## ✅ map() → transform data

```javascript
const names = people.map(p => p.name);
console.log(names);
```

👉 Result:

```
["Luke", "Leia", "Han"]
```

***

## 🔎 filter() → select data

```javascript
const jedis = people.filter(p => p.role === "Jedi");
console.log(jedis);
```

***

## 🎯 find() → get one item

```javascript
const leia = people.find(p => p.name === "Leia");
console.log(leia);
```

***

# ✏️ 6. Add New Object

```javascript
people.push({ name: "Yoda", role: "Master" });
```

***

# ❌ 7. Remove Object

```javascript
const filtered = people.filter(p => p.name !== "Han");
```

***

# 🌐 8. Real World: API Data (SWAPI Style)

This is where it clicks 💡

```javascript
const response = await fetch("https://swapi.dev/api/people/");
const data = await response.json();

const people = data.results;

// Array of objects!
people.forEach(p => {
  console.log(p.name);
});
```

👉 Run with Deno:

```bash
deno run --allow-net app.js
```

***

# 🧪 9. Combine Methods (Power!)

```javascript
const result = people
  .filter(p => p.name.includes("a"))
  .map(p => p.name);

console.log(result);
```

***

# 🧭 Mental Model

```
people (array)
 ├── { name: "Luke", role: "Jedi" }
 ├── { name: "Leia", role: "Princess" }
 └── { name: "Han", role: "Smuggler" }
```

👉 You:

* loop → go through list

* filter → reduce list

* map → transform list

***

# 🧩 Mini Exercise (Try This)

```javascript
const ships = [
  { name: "Falcon", speed: 1050 },
  { name: "X-Wing", speed: 900 },
  { name: "TIE Fighter", speed: 1200 }
];
```

👉 Tasks:

1. Print all ship names

2. Find the fastest ship

3. Create array of speeds only

***

# 🚀 What’s Next (Perfect for You)

Since you already did:

* PowerShell API calls ✅

* JS objects ✅

* Arrays ✅

👉 Next step:

**🔥 Combine everything → Build a CLI tool in Deno**

Example idea:

* Fetch Star Wars characters

* Filter by name

* Print nicely

***

If you want, I can guide you step-by-step to build:

👉 **“Star Wars CLI Tool (Deno)”**\
That would connect _everything you’ve learned so far_ 💪

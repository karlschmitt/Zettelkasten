# 20260413231257 JavaScript Bootcamp Week 2

Great—Week 2 is where JavaScript starts to feel _powerful_. You’ll move from simple values to **working with collections and real data** using Deno.

***

# 🚀 Week 2 — Arrays, Objects, Loops (Deno Bootcamp)

## 🧭 Structure (same as before)

* ⏱️ 30–45 minutes/day

* 🔁 REPL → small file → notes

* 🎯 Focus: _manipulating data_

***

# 📅 Day 8 — Arrays (Lists of data)

## 🎯 Goal

Store and access multiple values

## 🔬 REPL

```js
const fruits = ["apple", "banana", "cherry"];

fruits[0]
fruits.length
```

## 🛠️ Mini Project

```js
// day8-arrays.js
const fruits = ["apple", "banana"];

fruits.push("cherry");

for (const fruit of fruits) {
  console.log(fruit);
}
```

## 🧠 Learn

* `push()` → add item

* `length` → size

* Index starts at **0**

***

# 📅 Day 9 — Array Methods (Superpowers)

## 🎯 Goal

Transform data using built-in methods

## 🔬 REPL

```js
[1, 2, 3].map(x => x * 2)
[1, 2, 3].filter(x => x > 1)
[1, 2, 3].includes(2)
```

## 🛠️ Mini Project

```js
// day9-methods.js
const numbers = [1, 2, 3, 4];

const doubled = numbers.map(n => n * 2);
const filtered = numbers.filter(n => n > 2);

console.log(doubled);
console.log(filtered);
```

## 🧠 Learn

* `map()` → transform

* `filter()` → select

* These are **core JavaScript skills**

***

# 📅 Day 10 — Objects (Key-Value Data)

## 🎯 Goal

Store structured data

## 🔬 REPL

```js
const user = {
  name: "Karl",
  age: 30
};

user.name
user["age"]
```

## 🛠️ Mini Project

```js
// day10-objects.js
const user = {
  name: "Karl",
  age: 30,
  isLearning: true
};

console.log(user.name);
console.log(user.isLearning);
```

## 🧠 Learn

* Objects = real-world data

* Keys → strings

* Values → anything

***

# 📅 Day 11 — Arrays of Objects (Real Data!)

## 🎯 Goal

Combine arrays + objects

## 🔬 REPL

```js
const users = [
  { name: "Karl", age: 30 },
  { name: "Anna", age: 25 }
];

users[0].name
```

## 🛠️ Mini Project

```js
// day11-data.js
const users = [
  { name: "Karl", age: 30 },
  { name: "Anna", age: 25 }
];

for (const user of users) {
  console.log(user.name, user.age);
}
```

***

# 📅 Day 12 — Loops (Control flow)

## 🎯 Goal

Repeat actions

## 🔬 REPL

```js
for (let i = 0; i < 3; i++) {
  console.log(i);
}
```

## 🛠️ Mini Project

```js
// day12-loops.js
const numbers = [10, 20, 30];

for (const num of numbers) {
  console.log(num);
}
```

## 🧠 Learn

* `for` → classic loop

* `for...of` → arrays (preferred 👍)

***

# 📅 Day 13 — Combining Everything

## 🎯 Goal

Use arrays + objects + methods

## 🛠️ Mini Project

```js
// day13-combine.js
const users = [
  { name: "Karl", age: 30 },
  { name: "Anna", age: 25 },
  { name: "Bob", age: 17 }
];

// Adults only
const adults = users.filter(u => u.age >= 18);

// Names only
const names = adults.map(u => u.name);

console.log(names);
```

***

# 📅 Day 14 — Mini Project (Real Practice)

## 🎯 Goal

Think like a developer

## 🛠️ Project: User Analyzer

```js
// day14-project.js
const users = [
  { name: "Karl", age: 30 },
  { name: "Anna", age: 25 },
  { name: "Bob", age: 17 },
  { name: "Lisa", age: 40 }
];

function analyze(users) {
  const adults = users.filter(u => u.age >= 18);

  return {
    total: users.length,
    adults: adults.length,
    names: adults.map(u => u.name)
  };
}

console.log(analyze(users));
```

Run:

```bash
deno run day14-project.js
```

***

# 🧠 What You Just Learned

By the end of Week 2:

* Arrays ✅

* Array methods (`map`, `filter`) ✅

* Objects ✅

* Loops ✅

* Combining everything ✅

👉 This is **real JavaScript thinking**

***

# 💡 Zettelkasten Note Idea

```text
JavaScript / Arrays vs Objects

Array:
- Ordered
- Indexed (0,1,2...)

Object:
- Key-value
- Named properties

Use:
- Array → list of items
- Object → describe one thing
```

***

# 🚀 Next Step (Week 3)

If you’re ready, Week 3 gets exciting:

* 🌐 Fetch APIs (real data from internet)

* ⏳ Async / await

* 🛠️ Build a CLI tool with Deno

Just say the word 👍

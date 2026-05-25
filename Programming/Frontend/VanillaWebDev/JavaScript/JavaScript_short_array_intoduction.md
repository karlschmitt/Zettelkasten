---
id: 20260413234445
title: A short array introduction for JavaScript
date: 2016-04-16
keywords: [ JavaScript, Array ]
---

#  A short array introduction for JavaScript

Absolutely—here’s a **short, practical introduction to JavaScript arrays** (perfect for your Deno learning flow 👇).

***

# 🧠 What is an Array?

An **array** is a list of values stored in a single variable.

```js
const fruits = ["apple", "banana", "cherry"];
```

👉 Think of it like a numbered list:

```
0 → "apple"
1 → "banana"
2 → "cherry"
```

***

# 🔍 Accessing Elements

```js
fruits[0] // "apple"
fruits[1] // "banana"
```

👉 Arrays use **zero-based indexing** (start at 0)

***

# 📏 Length of an Array

```js
fruits.length // 3
```

***

# ➕ Adding Elements

```js
fruits.push("orange");  // add to end
```

Now:

```js
["apple", "banana", "cherry", "orange"]
```

***

# 🔁 Looping Through an Array

```js
for (const fruit of fruits) {
  console.log(fruit);
}
```

👉 This is the **cleanest way** to iterate 👍

***

# ⚡ Useful Array Methods (Core Tools)

## `map()` → transform values

```js
[1, 2, 3].map(x => x * 2)
// [2, 4, 6]
```

## `filter()` → select values

```js
[1, 2, 3].filter(x => x > 1)
// [2, 3]
```

## `includes()` → check existence

```js
fruits.includes("apple")
// true
```

***

# 🛠️ Small Example (Try in Deno)

```js
const numbers = [1, 2, 3, 4];

// double numbers
const doubled = numbers.map(n => n * 2);

// keep numbers > 2
const filtered = numbers.filter(n => n > 2);

console.log(doubled);
console.log(filtered);
```

***

# 🧬 Arrays Can Hold Anything

```js
const mixed = [1, "hello", true, null];
```

👉 Even objects:

```js
const users = [
  { name: "Karl", age: 30 },
  { name: "Anna", age: 25 }
];
```

***

# 💡 Mental Model

* Array = **list of items**

* Object = **one thing with properties**

***

# 🚀 Super Quick Summary

* `[]` → create array

* `[0]` → access element

* `.length` → size

* `.push()` → add item

* `map()` → transform

* `filter()` → select

***

If you want, I can give you **5 small exercises** to really lock this in (they’re quick but powerful).

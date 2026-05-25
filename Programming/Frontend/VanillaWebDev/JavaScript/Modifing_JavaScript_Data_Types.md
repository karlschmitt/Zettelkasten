---
id: 20260415204104
title: Modifying JavaScript Data Types
---

# Modifying JavaScript Data Types

Great question—this is where JavaScript starts to feel _powerful_ 💪\
Let’s explore **how to modify JavaScript data types in Deno** with clear, runnable examples.

***

# 🧠 1. Key Idea First

In JavaScript, data types fall into two groups:

### 🔹 Primitive (immutable)

* `string`, `number`, `boolean`, `null`, `undefined`, `symbol`, `bigint`

👉 You **cannot change them directly** — only replace them.

***

### 🔸 Reference (mutable)

* `object`, `array`, `function`

👉 You **can modify them in place**.

***

# 🔤 2. Modifying Strings (Immutable)

```js
let name = "Karl";

// ❌ This does NOT work
name[0] = "M";

console.log(name); // "Karl"
```

✔️ Correct way:

```js
name = "M" + name.slice(1);
console.log(name); // "Marl"
```

***

# 🔢 3. Modifying Numbers

Numbers are immutable:

```js
let x = 10;

x = x + 5;
console.log(x); // 15
```

👉 You’re creating a **new value**, not modifying the old one.

***

# 🧮 4. Modifying Arrays (Mutable ✅)

Arrays are where things get interesting:

```js
const numbers = [1, 2, 3];

// Modify directly
numbers.push(4);

console.log(numbers); // [1,2,3,4]
```

***

### Common array modifications:

```js
numbers.pop();        // remove last
numbers.shift();      // remove first
numbers.unshift(0);   // add at beginning
numbers[1] = 99;      // change element
```

***

# 🧱 5. Modifying Objects (Mutable ✅)

```js
const user = {
  name: "Karl",
  age: 30
};

// Modify property
user.age = 31;

// Add property
user.city = "Frankfurt";

// Delete property
delete user.name;

console.log(user);
```

***

# 🔁 6. Copy vs Modify (VERY IMPORTANT)

### ❌ Reference copy (linked!)

```js
const a = { x: 1 };
const b = a;

b.x = 99;

console.log(a.x); // 99 😱
```

***

### ✔️ Shallow copy

```js
const a = { x: 1 };
const b = { ...a };

b.x = 99;

console.log(a.x); // 1 ✅
```

***

# 🔬 7. Immutable Style (Best Practice)

Instead of modifying:

```js
const numbers = [1, 2, 3];
numbers.push(4); // modifies original
```

Use:

```js
const newNumbers = [...numbers, 4];
```

***

### Objects:

```js
const user = { name: "Karl" };

const updatedUser = {
  ...user,
  name: "Alice"
};
```

***

# ⚡ 8. Modify Data with Functions

```js
function updateAge(user, newAge) {
  return {
    ...user,
    age: newAge
  };
}

const user = { name: "Karl", age: 30 };

const updated = updateAge(user, 31);

console.log(updated);
```

***

# 🧪 9. Run in Deno (Example Script)

Create `modify.js`:

```js
const data = {
  numbers: [1, 2, 3],
  user: { name: "Karl" }
};

// Modify array
data.numbers.push(4);

// Modify object
data.user.name = "Alice";

console.dir(data, { depth: null });
```

Run:

```bash
deno run modify.js
```

***

# 🔍 10. Deep Copy (Advanced)

```js
const original = {
  nested: { value: 1 }
};

const copy = structuredClone(original);

copy.nested.value = 99;

console.log(original.nested.value); // 1 ✅
```

***

# ⚠️ 11. Common Pitfalls

### ❌ Modifying const?

```js
const arr = [1,2,3];
arr.push(4); // ✅ allowed
```

👉 `const` prevents reassignment, **not mutation**

***

### ❌ Nested objects still shared!

```js
const a = { nested: { x: 1 } };
const b = { ...a };

b.nested.x = 99;

console.log(a.nested.x); // 99 😱
```

***

# 🧩 12. Mini Challenge

Try this in Deno:

```js
// 1. Add an item to an array WITHOUT modifying original
// 2. Update an object property immutably
// 3. Deep clone and modify safely
```

***

# 💡 Key Takeaways

* Primitives → immutable (replace value)

* Arrays/Objects → mutable (modify directly)

* Spread (`...`) → safe copying

* `structuredClone()` → deep copy

* Prefer **immutable patterns** for cleaner code

***

If you want, I can show you a **real mini project** (like a todo app in Deno) where you practice modifying data step by step 🚀

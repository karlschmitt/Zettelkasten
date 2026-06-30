# 20260413225109 Playing around with JavaScript primitive data types


Exploring **primitive data types in JavaScript** is a great way to build a solid foundation. Let’s make this practical and hands-on so you can _learn by doing_.

***

# 🧠 What are primitive data types?

In JavaScript, **primitive types** are simple, immutable values (not objects). The main ones are:

* `string`

* `number`

* `boolean`

* `undefined`

* `null`

* `bigint`

* `symbol`

***

# 🔍 1. Quick exploration in the console

The fastest way to learn is using a REPL like:

* Browser DevTools (F12 → Console)

* Or Deno (which you mentioned earlier 👍)

### Try this:

```js
"Hello world"        // string
42                   // number
true                 // boolean
undefined            // undefined
null                 // null
123n                 // bigint
Symbol("id")         // symbol
```

***

# 🧪 2. Use `typeof` to inspect values

```js
typeof "Hello"     // "string"
typeof 42          // "number"
typeof true        // "boolean"
typeof undefined   // "undefined"
typeof null        // ❗ "object" (historical bug!)
typeof 123n        // "bigint"
typeof Symbol()    // "symbol"
```

👉 Important: `typeof null === "object"` is a **well-known JavaScript quirk**.

***

# 🧩 3. Play with variables

```js
let name = "Karl";
let age = 30;
let isLearning = true;

console.log(typeof name);
console.log(typeof age);
console.log(typeof isLearning);
```

***

# 🔄 4. Type conversion (very important!)

JavaScript automatically converts types (sometimes confusing!).

### Examples:

```js
"5" + 1     // "51"  (string!)
"5" - 1     // 4     (number!)
true + 1    // 2
false + 1   // 1
null + 1    // 1
undefined + 1 // NaN
```

👉 This is called **type coercion**.

***

# ⚡ 5. Equality quirks (`==` vs `===`)

```js
5 == "5"    // true  (loose equality)
5 === "5"   // false (strict equality)
```

👉 Rule of thumb:\
✅ Always use `===` (strict equality)

***

# 🧬 6. Primitive vs Reference (important concept)

Primitives are copied by value:

```js
let a = 10;
let b = a;

b = 20;

console.log(a); // 10 (unchanged)
```

***

# 🛠️ 7. Practice exercises (try in Deno or browser)

### Exercise 1

```js
let x = "10";
let y = 10;

console.log(x == y);   // ?
console.log(x === y);  // ?
```

### Exercise 2

```js
let value;

console.log(value);          // ?
console.log(typeof value);   // ?
```

### Exercise 3

```js
console.log(null == undefined);   // ?
console.log(null === undefined);  // ?
```

***

# 🚀 8. Learn by experimenting (best method)

If you’re using Deno, try:

```bash
deno repl
```

Then explore:

```js
typeof 100
typeof "JS"
typeof null
typeof Symbol("test")
```

***

# 💡 Pro tip

Create a small “type playground” file:

```js
// types.js
const values = [
  "Hello",
  42,
  true,
  undefined,
  null,
  123n,
  Symbol("id")
];

for (const v of values) {
  console.log(v, "=>", typeof v);
}
```

Run it:

```bash
deno run types.js
```

***

# 🧭 How to get really good at this

* Experiment daily (5–10 minutes)

* Predict output before running code

* Break things intentionally 😄

* Write small test snippets

***

If you want, I can give you a **mini training plan (like a bootcamp)** for mastering JavaScript basics step by step.



Nice—that’s actually a very smart choice 👍\
Deno is _perfect_ for learning because it’s simple, modern, and removes a lot of setup pain.

Let’s turn this into a **clear learning workflow** so you can explore JavaScript (especially primitive types) efficiently.

***

# 🚀 1. Start Deno REPL (your playground)

Open your terminal:

```bash
deno repl
```

Now you’re in an interactive JavaScript shell.

***

# 🔍 2. Explore primitive types interactively

Type these one by one:

```js
"Hello"
typeof "Hello"

42
typeof 42

true
typeof true

undefined
typeof undefined

null
typeof null
```

👉 Don’t rush—**predict first, then execute**.

***

# 🧪 3. Build a “type intuition loop”

This is the key habit:

### Step 1: Guess

```js
typeof "5" + 1
```

### Step 2: Run it

```js
typeof "5" + 1   // "string1"
```

### Step 3: Understand WHY

* `typeof "5"` → `"string"`

* `"string" + 1` → `"string1"`

👉 This is how you _really_ learn JavaScript.

***

# 🧠 4. Your first mini “lab”

Copy this into Deno:

```js
let values = [
  "text",
  123,
  true,
  null,
  undefined,
  10n,
  Symbol("id")
];

for (let v of values) {
  console.log(v, "=>", typeof v);
}
```

👉 You’ll see all primitive types in one place.

***

# ⚡ 5. Play with weird JavaScript behavior (important!)

Try these in Deno:

```js
"5" + 2
"5" - 2
true + 1
false + 1
null + 1
undefined + 1
```

Ask yourself each time:\
👉 _Why did that happen?_

***

# 🔐 6. Equality training (VERY important)

```js
5 == "5"
5 === "5"

null == undefined
null === undefined
```

👉 Burn this into memory:

* `==` → loose (dangerous)

* `===` → strict (safe ✅)

***

# 🧬 7. Primitive behavior (copy vs reference)

```js
let a = 10;
let b = a;

b = 99;

console.log(a); // still 10
```

👉 Primitives are **copied**, not shared.

***

# 🗂️ 8. Move from REPL → files (next step)

Create a file:

```bash
touch types.js
```

Add:

```js
console.log(typeof "hello");
console.log(typeof 123);
console.log(typeof null);
```

Run:

```bash
deno run types.js
```

***

# 🧭 9. Your daily 10-minute plan

Do this every day:

1. Open `deno repl`

2. Test 5–10 expressions

3. Predict before running

4. Write 1 small file

***

# 💡 Pro tip (this will accelerate your learning)

Create a note in your Zettelkasten like:

```
JavaScript / Primitive Types / Weird Cases

- typeof null === "object"
- "5" + 1 → "51"
- "5" - 1 → 4
- null + 1 → 1
- undefined + 1 → NaN
```

👉 This connects perfectly with your **lifelong learning system**.

***

If you want, next step I can give you a **structured 7-day Deno + JavaScript bootcamp** tailored exactly to how you like to learn.

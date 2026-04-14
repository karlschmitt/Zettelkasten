# 20260414162741 Introduction to objects

Absolutely — let’s do a **short, 
practical introduction to JavaScript objects using Deno** 🚀
keeping it simple and hands-on, just like your bootcamp style

***

# 🧠 1. What is a JavaScript Object?

An **object** is a collection of **key–value pairs**.

👉 Think of it like a dictionary:

```javascript
const person = {
  name: "Luke Skywalker",
  age: 23,
  isJedi: true
};
```

***

# ▶️ 2. Run with Deno

Create a file:

```bash
touch object.js
```

Run it:

```bash
deno run object.js
```

***

# 🔍 3. Access Properties

```javascript
const person = {
  name: "Luke",
  age: 23
};

console.log(person.name);     // Dot notation
console.log(person["age"]);   // Bracket notation
```

***

# ✏️ 4. Add / Change Properties

```javascript
person.planet = "Tatooine";   // Add
person.age = 24;              // Update

console.log(person);
```

***

# ❌ 5. Delete Properties

```javascript
delete person.age;
console.log(person);
```

***

# 🔁 6. Loop Through an Object

```javascript
for (const key in person) {
  console.log(key, person[key]);
}
```

***

# 📦 7. Objects Can Contain Anything

```javascript
const jedi = {
  name: "Luke",
  skills: ["lightsaber", "force"],
  mentor: {
    name: "Yoda"
  }
};

console.log(jedi.skills[0]);        // lightsaber
console.log(jedi.mentor.name);     // Yoda
```

***

# 🧪 8. Object Methods (Functions inside objects)

```javascript
const droid = {
  name: "R2-D2",
  speak() {
    console.log("Beep boop!");
  }
};

droid.speak();
```

***

# 🧊 9. Destructuring (Very Useful)

```javascript
const person = {
  name: "Leia",
  age: 23
};

const { name, age } = person;

console.log(name);
```

***

# 🔄 10. Convert to/from JSON (Important for APIs)

```javascript
const json = JSON.stringify(person);
console.log(json);

const obj = JSON.parse(json);
console.log(obj.name);
```

***

# 🧭 Mental Model

👉 Object = **container of related data**

```text
person
 ├── name → "Luke"
 ├── age → 23
 └── isJedi → true
```

***

# 🧩 Mini Exercise (Try This)

Create this object and print a sentence:

```javascript
const ship = {
  name: "Millennium Falcon",
  speed: 1050,
  pilot: "Han Solo"
};
```

👉 Output:

```
Han Solo flies the Millennium Falcon at speed 1050
```

***

# 🚀 What’s Next?

If you continue your Deno bootcamp, the natural next steps are:

1. Arrays of objects

2. Fetching API data (like SWAPI 👀)

3. Looping over API results

4. Building small CLI tools

***

If you want, I can give you a **Week 4 (Objects + APIs with Deno)** plan to connect this directly with your PowerShell API work 👍

# 20260414000507 JavaScript Arrays

In JavaScript, an **Array** is a global object used to store a collection of multiple items under a single variable name. 

While primitive types (like strings or numbers) hold a single value, arrays are **objects** designed to handle lists of data.

---

### 1. Key Characteristics
*   **Ordered:** Elements stay in the order you put them in.
*   **Zero-indexed:** The first element is at index `0`, the second at `1`, etc.
*   **Dynamic:** You don't have to define a size; arrays grow and shrink as needed.
*   **Mixed Types:** A single array can hold strings, numbers, booleans, objects, and even other arrays.

### 2. Creating Arrays
The most common way to create an array is using **Array Literals** (square brackets):

```javascript
// An empty array
const empty = [];

// An array of strings
const fruits = ["Apple", "Banana", "Cherry"];

// A mixed array (perfectly valid in JS)
const mixed = ["Deno", 1.4, true, { id: 1 }];
```

### 3. Accessing and Modifying
You use square brackets with the index number to get or change values.

```javascript
const colors = ["Red", "Green", "Blue"];

console.log(colors[0]); // "Red"

colors[1] = "Yellow";   // Changes "Green" to "Yellow"
console.log(colors.length); // 3
```

### 4. Essential Array Methods
JavaScript provides a massive built-in toolkit for arrays. Here are the "must-know" methods:

#### Adding/Removing Elements
*   `.push(item)`: Adds to the **end**.
*   `.pop()`: Removes from the **end**.
*   `.unshift(item)`: Adds to the **start**.
*   `.shift()`: Removes from the **start**.

#### Transforming and Finding
*   `.map()`: Creates a new array by doing something to every element.
*   `.filter()`: Creates a new array containing only items that pass a test.
*   `.find()`: Returns the first element that matches a condition.
*   `.includes(item)`: Returns `true` or `false` if an item exists.

---

### 5. Exploring Arrays in Deno
You can use Deno to experiment with these methods interactively. Create a file called `arrays.js`:

```javascript
// arrays.js
const tools = ["Deno", "Node", "Bun"];

// 1. Add an element
tools.push("TypeScript");

// 2. Transform the list to uppercase
const shoutyTools = tools.map(t => t.toUpperCase());

// 3. Filter for tools that start with 'B'
const bTools = tools.filter(t => t.startsWith("B"));

console.log("Original:", tools);
console.log("Uppercase:", shoutyTools);
console.log("Starts with B:", bTools);
```

**Run it:**
```bash
deno run arrays.js
```

### 6. Are Arrays actually Primitives?
**No.** Arrays are a special type of **Object**. 
If you check an array using `typeof`, it will return `"object"`. To specifically check if something is an array, you use:

```javascript
Array.isArray([1, 2, 3]); // true
Array.isArray({ a: 1 });  // false
```

### Summary for Beginners
Think of an array like a **numbered chest of drawers**. Each drawer (index) holds a piece of data. You can add more drawers, take them away, or look inside them using the number assigned to them.
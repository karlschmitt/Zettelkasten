---
id: 20261121115505
title: JSX Absolute Beginner Step-by-Step Tutorial (with Setup & Testing)
author: Karl Schmitt
date: 2026-11-21
keywords: [ programming, react, jsx, testing, tutorial ]
---

![JSX-Spickzettel für Einsteiger](../Images/JSX-Spickzettel_fuer_Einsteiger.png)

> [!NOTE]
> Diese Anleitung bietet eine umfassende Einführung in **\[\[JSX]]**, eine Syntaxerweiterung für **\[\[JavaScript]]**, die zur Erstellung von Benutzeroberflächen in **\[\[React]]** genutzt wird. Nach der Einrichtung eines Projekts mit **\[\[Vite]]** und der Erklärung der zugrundeliegenden Kompilierung werden die vier grundlegenden Regeln für die Verwendung dieser Markup-Sprache erläutert. Dazu gehören die Notwendigkeit eines einzelnen Wurzelelements oder eines **\[\[React Fragment]]**, das explizite Schließen aller Tags sowie die Verwendung von **camelCase** für Attribute. Zudem wird gezeigt, wie geschweifte Klammern als Schnittstelle für **JavaScript-Ausdrücke**, Bedingungen und das Rendern von Listen dienen. Abschließend wird demonstriert, wie Komponenten mithilfe von **\[\[Vitest]]** und der **\[\[React Testing Library]]** automatisiert getestet werden können.


# JSX Absolute Beginner Tutorial

> **Core Idea:** [[JSX]] (JavaScript XML) is a syntax extension for [[JavaScript]] used in [[React]]. It lets you write HTML-like markup directly inside JavaScript files, making UI code visual, readable, and easy to maintain.

---

## Step 1: Create a React Project (Project Setup)
Before writing JSX, you need a tool that translates JSX into regular JavaScript that web browsers can understand. We use [[Vite]] for this.

1. Make sure [[Node.js]] is installed (check in your terminal with `node -v`).
2. Create a new React project:
   ```bash
   npm create vite@latest jsx-playground -- --template react
   ```
3. Enter the folder, install dependencies, and start the development server:
   ```bash
   cd jsx-playground
   npm install
   npm run dev
   ```
4. Open the `http://localhost:5173` link shown in your terminal.
5. Open the project in your code editor (e.g., [[VS Code]]). You will mostly work inside `src/App.jsx`.

> **Note:** Files containing JSX typically end in `.jsx` (instead of `.js`) so your editor and build tool know to expect HTML-like syntax inside JavaScript.

---

## Step 2: What Is JSX Under the Hood?
Browsers **cannot** read JSX directly. When you run Vite, a compiler (like [[Babel]] or [[SWC]]) transforms your JSX into plain JavaScript function calls (`React.createElement`).

### What You Write (JSX):
```jsx
const heading = <h1 className="title">Hello, World!</h1>;
```

### What the Browser Actually Receives (Compiled JS):
```javascript
const heading = React.createElement(
  "h1",
  { className: "title" },
  "Hello, World!"
);
```

Because JSX compiles into JavaScript objects, **you can store JSX in variables, pass it to functions, and return it from components.**

---

## Step 3: The 4 Golden Rules of JSX
JSX looks like HTML, but because it is actually JavaScript underneath, it has stricter rules. Open `src/App.jsx` and test these rules as you go.

### Rule 1: Return a Single Root Element
A component cannot return two sibling tags side by side. You must wrap them in a single parent tag, or use an empty **[[React Fragment]]** (`<> ... </>`) if you don't want an extra `<div>` in the [[DOM]].

```jsx
// ❌ INVALID: Two sibling elements at the top level
function BadExample() {
  return (
    <h1>Title</h1>
    <p>Paragraph</p>
  );
}

// ✅ VALID: Wrapped in a React Fragment (<>...</>)
function GoodExample() {
  return (
    <>
      <h1>Title</h1>
      <p>Paragraph</p>
    </>
  );
}
```

### Rule 2: Close Every Tag
In HTML, tags like `<br>`, `<hr>`, `<img>`, or `<input>` can stay open. In JSX, **every tag must be explicitly closed**.

```jsx
// ❌ INVALID in JSX
<img src="photo.jpg" alt="Profile">
<br>

// ✅ VALID in JSX (self-closing slash)
<img src="photo.jpg" alt="Profile" />
<br />
```

### Rule 3: Use `camelCase` for Most Attributes
Because JSX becomes JavaScript, reserved JS words (like `class` or `for`) cannot be used as attributes, and hyphenated HTML attributes become `camelCase`.

| HTML | JSX | Why? |
| :--- | :--- | :--- |
| `class="box"` | `className="box"` | `class` is a reserved keyword in JS |
| `for="email"` | `htmlFor="email"` | `for` is a reserved loop keyword in JS |
| `onclick="..."` | `onClick={...}` | Event handlers use `camelCase` |
| `tabindex="0"` | `tabIndex="0"` | Multi-word attributes use `camelCase` |

### Rule 4: Curly Braces `{ }` Open a Window into JavaScript
Inside JSX, anything inside `{ }` is evaluated as a **JavaScript Expression** (something that produces a value).

```jsx
function App() {
  const userName = "Alex";
  const age = 25;
  const formatName = (name) => name.toUpperCase();

  return (
    <div>
      {/* Comments in JSX also go inside curly braces! */}
      <h1>Hello, {formatName(userName)}!</h1>
      <p>Next year you will be {age + 1} years old.</p>
    </div>
  );
}

export default App;
```

> **Crucial Distinction:** You can put **expressions** (`2 + 2`, `user.name`, `items.map(...)`) inside `{ }`, but you **cannot** put **statements** (`if/else` blocks, `for` loops, `let x = 5`).

---

## Step 4: Dynamic Attributes & Inline Styling
You can also use `{ }` to set HTML attributes dynamically—without quotes!

```jsx
function ProfileImage() {
  const imageUrl = "https://via.placeholder.com/150";
  const altText = "Placeholder avatar";

  return (
    // Use { } instead of quotes "" for JS variables
    <img src={imageUrl} alt={altText} />
  );
}
```

### Inline Styles Use Double Curly Braces `{{ }}`
In HTML, `style` is a string (`style="color: red; font-size: 20px;"`). In JSX, `style` expects a **JavaScript object**.
- Outer `{ }` = "I am writing JavaScript inside JSX."
- Inner `{ }` = "This is a JavaScript object."
- CSS properties with dashes become `camelCase` (`background-color` -> `backgroundColor`).

```jsx
function Banner() {
  return (
    <div
      style={{
        backgroundColor: "#f0f4f8",
        color: "#1e293b",
        padding: "16px",
        borderRadius: "8px",
      }}
    >
      Styled directly with a JS object!
    </div>
  );
}
```

---

## Step 5: Conditions & Lists Inside JSX
Since `if` and `for` statements aren't allowed inside `{ }`, JSX uses JavaScript expressions instead.

### 1. Conditional Rendering (`? :` and `&&`)
- **Ternary Operator (`condition ? ifTrue : ifFalse`):** Choose between two options.
- **Logical AND (`condition && element`):** Show something *only* if a condition is true.

```jsx
function StatusBadge({ isOnline, unreadMessages }) {
  return (
    <div>
      {/* Ternary: A or B */}
      <p>Status: {isOnline ? "🟢 Online" : "🔴 Offline"}</p>

      {/* Logical AND: Render only if condition is true */}
      {unreadMessages > 0 && (
        <p>You have {unreadMessages} new messages.</p>
      )}
    </div>
  );
}
```

### 2. Rendering Lists with `.map()`
To turn an array of data into JSX elements, use JavaScript's `.map()` method. Every item in a list must have a unique `key` prop so React can track changes.

```jsx
function SkillList() {
  const skills = ["HTML", "JavaScript", "JSX"];

  return (
    <ul>
      {skills.map((skill) => (
        <li key={skill}>{skill}</li>
      ))}
    </ul>
  );
}
```

---

## Step 6: Testing Your JSX
How do you verify your JSX renders what you expect without manually clicking around the browser every time? You write automated tests using **[[Vitest]]** (the test runner built for Vite) and **[[React Testing Library]]** (which renders your JSX in a simulated browser environment called `jsdom`).

### 1. Install Testing Dependencies
Stop your dev server (`Ctrl + C`) or open a second terminal in your `jsx-playground` folder and run:

```bash
npm install -D vitest jsdom @testing-library/react @testing-library/jest-dom
```

### 2. Configure Vite and `package.json`
Open `vite.config.js` and add the `test` section:

```javascript
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

export default defineConfig({
  plugins: [react()],
  test: {
    environment: "jsdom", // Simulates a browser DOM in Node.js
    globals: true,        // Makes test(), expect(), etc., globally available & enables auto-cleanup
  },
});
```

Open `package.json` and add `"test": "vitest"` inside `"scripts"`:

```json
"scripts": {
  "dev": "vite",
  "build": "vite build",
  "lint": "eslint .",
  "preview": "vite preview",
  "test": "vitest"
}
```

### 3. Create a Component to Test
Create a new file `src/UserCard.jsx`:

```jsx
function UserCard({ name, isAdmin }) {
  return (
    <div className="user-card">
      <h2>{name}</h2>
      {isAdmin ? <span>Admin Access</span> : <span>Standard User</span>}
    </div>
  );
}

export default UserCard;
```

### 4. Write Your First JSX Test
Create a test file right next to it called `src/UserCard.test.jsx`:

```jsx
import { render, screen } from "@testing-library/react";
import "@testing-library/jest-dom";
import UserCard from "./UserCard";

describe("UserCard JSX Component", () => {
  test("renders the user name inside a heading", () => {
    // 1. Render the JSX component in the simulated DOM
    render(<UserCard name="Sarah" isAdmin={false} />);

    // 2. Query what appears on the screen
    const headingElement = screen.getByRole("heading", { name: "Sarah" });

    // 3. Assert that it exists in the document
    expect(headingElement).toBeInTheDocument();
  });

  test("shows 'Admin Access' when isAdmin is true", () => {
    render(<UserCard name="Mike" isAdmin={true} />);

    expect(screen.getByText("Admin Access")).toBeInTheDocument();
    expect(screen.queryByText("Standard User")).not.toBeInTheDocument();
  });

  test("shows 'Standard User' when isAdmin is false", () => {
    render(<UserCard name="Alex" isAdmin={false} />);

    expect(screen.getByText("Standard User")).toBeInTheDocument();
  });
});
```

### 5. Run the Tests
In your terminal, run:

```bash
npm test
```

You should see output confirming that all 3 tests passed! Press `q` in the terminal to exit the test watcher when you are done.

---

## Zettelkasten Breakdown (Atomic Note Ideas)
If you want to break this tutorial into evergreen atomic notes for your vault, consider creating:
- `[[JSX Compiles to React.createElement]]` — Explaining why JSX is syntactic sugar and how browsers read it.
- `[[JSX Golden Rules]]` — Single root/Fragment, self-closing tags, `camelCase` attributes, `{}` expressions.
- `[[JavaScript Expressions vs Statements in JSX]]` — Why ternary/`&&`/`.map()` work inside `{}` while `if`/`for` do not.
- `[[Testing React Components with Vitest and RTL]]` — The `render` → `screen` → `expect` mental model.
~~~~
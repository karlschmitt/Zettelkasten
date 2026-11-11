# React JS Deep-Dive Tutorial

## 1. What Is React?

React is a JavaScript **library** for building user interfaces. It is not a full framework; it focuses on the view layer.

React is used for:

- Single-page applications (SPAs)
- Interactive dashboards
- Web components and widgets
- Mobile apps (via React Native)
- Complex, data-driven UIs

The core idea of React is **components**: small, reusable pieces of UI that describe what the screen should look like for a given state.

```text
State (data)
     ↓
React component
     ↓
Virtual DOM (in-memory UI description)
     ↓
Reconciliation (diffing)
     ↓
Real DOM (what the user sees)
```

When state changes, React recomputes the UI, compares it against the previous version (the **Virtual DOM**), and updates only the parts of the real DOM that changed. This makes updates fast and predictable.

---

## 2. Mental Model: Declarative UI

Traditional (imperative) code tells the browser **how** to change the UI step by step:

```javascript
// Imperative: manually find and update elements
const el = document.getElementById("count");
el.textContent = count + 1;
```

React is **declarative**. You describe **what** the UI should look like for the current data, and React figures out the DOM operations:

```jsx
// Declarative: UI is a function of state
<p>Count: {count}</p>
```

The key formula to remember:

```text
UI = f(state)
```

The UI is a function of state. Change the state, and the UI re-renders automatically.

---

## 3. Install Node.js on Windows

React tooling runs on Node.js. Install it first:

```powershell
winget install --id OpenJS.NodeJS.LTS
```

Verify the installation:

```powershell
node --version
npm --version
```

- `node` runs JavaScript outside the browser.
- `npm` is the Node package manager used to install libraries.

Install the React extensions for VS Code (optional but helpful):

```powershell
code --install-extension dsznajder.es7-react-js-snippets
```

Restart VS Code after installation.

---

## 4. Create Your First React App (Vite)

**Vite** is the modern, fast way to create a React project. Run:

```powershell
npm create vite@latest my-first-app -- --template react
```

Then install dependencies and start the dev server:

```powershell
cd my-first-app
npm install
npm run dev
```

Open the URL shown in the terminal (usually `http://localhost:5173`).

Project structure overview:

```text
my-first-app/
├── index.html          ← single HTML page (the "single page")
├── package.json        ← dependencies and scripts
├── src/
│   ├── main.jsx        ← entry point, mounts React to the DOM
│   ├── App.jsx         ← root component
│   └── App.css         ← styles
└── vite.config.js      ← build tool config
```

---

## 5. JSX: HTML Inside JavaScript

**JSX** is a syntax extension that lets you write HTML-like markup inside JavaScript. It is not a string and not HTML; it compiles to function calls.

```jsx
const element = <h1>Hello, React!</h1>;
```

Rules of JSX:

- Return a **single root element** (wrap siblings in a parent or a fragment `<>...</>`).
- Use `className` instead of `class` (because `class` is a reserved JavaScript word).
- Use `{ }` to embed JavaScript expressions.
- Close every tag, including self-closing ones like `<img />` and `<br />`.

```jsx
function Greeting() {
  const name = "Ada";
  return (
    <>
      <h1>Hello, {name}!</h1>
      <p>Today is {new Date().toDateString()}.</p>
    </>
  );
}
```

---

## 6. Components

A component is a JavaScript function that returns JSX. Component names **must start with a capital letter**.

```jsx
function Welcome() {
  return <h2>Welcome to the app</h2>;
}
```

Use a component like an HTML tag:

```jsx
function App() {
  return (
    <div>
      <Welcome />
      <Welcome />
    </div>
  );
}
```

Each `<Welcome />` is an independent instance. Components let you build large UIs from small, reusable building blocks.

---

## 7. Props: Passing Data In

**Props** (properties) pass data from a parent component to a child. They are read-only inputs.

```jsx
function UserCard(props) {
  return (
    <div className="card">
      <h3>{props.name}</h3>
      <p>Role: {props.role}</p>
    </div>
  );
}

function App() {
  return (
    <div>
      <UserCard name="Ada" role="Engineer" />
      <UserCard name="Linus" role="Maintainer" />
    </div>
  );
}
```

It is common to **destructure** props for cleaner code:

```jsx
function UserCard({ name, role }) {
  return (
    <div className="card">
      <h3>{name}</h3>
      <p>Role: {role}</p>
    </div>
  );
}
```

Think of props like function arguments. A component never modifies its own props.

---

## 8. State with useState

**State** is data that changes over time and belongs to a component. When state changes, React re-renders the component.

State is managed with the `useState` **Hook**:

```jsx
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0);

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>Increment</button>
    </div>
  );
}
```

Breakdown:

- `useState(0)` declares a state variable with an initial value of `0`.
- It returns an array: `[currentValue, setterFunction]`.
- `count` holds the current value.
- `setCount` updates the value **and triggers a re-render**.

**Never mutate state directly.** Always use the setter:

```jsx
// Wrong — React will not re-render
count = count + 1;

// Correct
setCount(count + 1);
```

When the new state depends on the old state, use the **updater function** form to avoid stale values:

```jsx
setCount(prev => prev + 1);
```

---

## 9. Handling Events

React events are named in camelCase and take a function, not a string.

```jsx
function Form() {
  function handleClick() {
    alert("Button clicked!");
  }

  return <button onClick={handleClick}>Click me</button>;
}
```

Reading input values with state (a **controlled component**):

```jsx
import { useState } from "react";

function NameInput() {
  const [name, setName] = useState("");

  return (
    <div>
      <input
        value={name}
        onChange={(e) => setName(e.target.value)}
        placeholder="Type your name"
      />
      <p>Hello, {name || "stranger"}!</p>
    </div>
  );
}
```

The input's value is driven by state, and every keystroke updates that state. This keeps React as the single source of truth.

---

## 10. Conditional Rendering

Because JSX is just JavaScript, you render conditionally using normal expressions.

Using the ternary operator:

```jsx
function Status({ isLoggedIn }) {
  return (
    <p>{isLoggedIn ? "Welcome back!" : "Please log in."}</p>
  );
}
```

Using `&&` to render something or nothing:

```jsx
function Inbox({ unread }) {
  return (
    <div>
      {unread > 0 && <span>You have {unread} new messages</span>}
    </div>
  );
}
```

---

## 11. Rendering Lists

Use the JavaScript `.map()` method to turn an array of data into an array of elements.

```jsx
function TodoList() {
  const todos = ["Learn JSX", "Learn props", "Learn state"];

  return (
    <ul>
      {todos.map((todo, index) => (
        <li key={index}>{todo}</li>
      ))}
    </ul>
  );
}
```

The **`key`** prop is required for list items. It must be a stable, unique identifier so React can track which items changed. Prefer a real ID over the array index when available:

```jsx
const users = [
  { id: 1, name: "Ada" },
  { id: 2, name: "Linus" },
];

return (
  <ul>
    {users.map((user) => (
      <li key={user.id}>{user.name}</li>
    ))}
  </ul>
);
```

---

## 12. Side Effects with useEffect

Some work happens **outside** rendering: fetching data, timers, subscriptions, manually touching the DOM. These are **side effects**, handled with the `useEffect` Hook.

```jsx
import { useState, useEffect } from "react";

function Clock() {
  const [time, setTime] = useState(new Date());

  useEffect(() => {
    const timer = setInterval(() => setTime(new Date()), 1000);

    // Cleanup: runs when the component unmounts
    return () => clearInterval(timer);
  }, []); // empty array = run once after first render

  return <p>{time.toLocaleTimeString()}</p>;
}
```

The second argument is the **dependency array**:

- `[]` — run once, after the first render.
- `[value]` — run again whenever `value` changes.
- omitted — run after **every** render (rarely what you want).

Fetching data on mount:

```jsx
import { useState, useEffect } from "react";

function Users() {
  const [users, setUsers] = useState([]);

  useEffect(() => {
    fetch("https://jsonplaceholder.typicode.com/users")
      .then((res) => res.json())
      .then((data) => setUsers(data));
  }, []);

  return (
    <ul>
      {users.map((u) => (
        <li key={u.id}>{u.name}</li>
      ))}
    </ul>
  );
}
```

---

## 13. Lifting State Up

When two components need to share state, move (**lift**) that state to their nearest common parent and pass it down as props.

```jsx
import { useState } from "react";

function Child({ value, onChange }) {
  return (
    <input value={value} onChange={(e) => onChange(e.target.value)} />
  );
}

function Parent() {
  const [text, setText] = useState("");

  return (
    <div>
      <Child value={text} onChange={setText} />
      <p>You typed: {text}</p>
    </div>
  );
}
```

Data flows **down** via props; changes flow **up** via callback functions. This one-way data flow makes apps easier to reason about.

---

## 14. Styling Components

Several approaches work in React:

**Plain CSS file** — import it and use `className`:

```jsx
import "./App.css";

function Box() {
  return <div className="box">Styled box</div>;
}
```

**Inline styles** — pass an object (note camelCase keys):

```jsx
function Box() {
  return <div style={{ padding: "10px", backgroundColor: "lightblue" }}>Box</div>;
}
```

**CSS Modules** — scoped styles that avoid name clashes (`Box.module.css`):

```jsx
import styles from "./Box.module.css";

function Box() {
  return <div className={styles.box}>Box</div>;
}
```

---

## 15. Common Beginner Mistakes

- **Mutating state directly** instead of using the setter function.
- **Forgetting `key`** props when rendering lists.
- **Using `class`** instead of `className` in JSX.
- **Calling a Hook conditionally** — Hooks must run in the same order every render, so call them at the top level, never inside `if`, loops, or nested functions.
- **Missing dependencies** in `useEffect`, causing stale data.
- **Returning multiple root elements** without a wrapper or fragment.

---

## 16. Build for Production

When your app is ready, create an optimized build:

```powershell
npm run build
```

This outputs static files to the `dist/` folder. Preview the production build locally:

```powershell
npm run preview
```

Deploy the contents of `dist/` to any static host (Netlify, Vercel, GitHub Pages, S3, etc.).

---

## 17. Key Takeaways

- React builds UIs from **components** — functions that return JSX.
- **JSX** mixes markup and JavaScript; expressions go in `{ }`.
- **Props** pass data down; they are read-only.
- **State** (`useState`) holds data that changes; the setter triggers re-renders.
- `UI = f(state)` — the UI is a function of state.
- **`useEffect`** handles side effects like data fetching and timers.
- Data flows **down**, events flow **up** (one-way data flow).
- Always provide a stable **`key`** when rendering lists.

---

## 18. Where to Go Next

- **React Router** — client-side navigation between pages.
- **Context API** — share state without passing props through every level.
- **useReducer** — manage complex state logic.
- **Custom Hooks** — extract and reuse stateful logic.
- **State libraries** — Redux Toolkit, Zustand, or TanStack Query for data fetching.
- **TypeScript** — add static typing to catch errors early.
- **Next.js** — a full framework built on React for routing, server rendering, and APIs.

---

## Related Notes

- [[java-deep-dive]]
- [[cpp-deep-dive]]
- [[javascript-fundamentals]]
- [[frontend-architecture]]

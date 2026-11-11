# React Hooks Deep-Dive Tutorial

## 1. What Are Hooks?

**Hooks** are special functions that let you "hook into" React features — like state and lifecycle — from inside **function components**.

Before Hooks (React 16.8, released 2019), only class components could hold state or run lifecycle code. Hooks brought those abilities to plain functions, and today function components with Hooks are the standard way to write React.

A Hook is just a JavaScript function, but by convention its name always starts with **`use`**:

```text
useState     → local state
useEffect    → side effects
useContext   → shared data
useRef       → mutable values / DOM access
useReducer   → complex state logic
useMemo      → cache a computed value
useCallback  → cache a function
```

---

## 2. The Rules of Hooks

Hooks only work if you follow two strict rules. React relies on the **order** in which Hooks are called to keep track of their state.

**Rule 1 — Only call Hooks at the top level.**
Never call a Hook inside a loop, condition, or nested function.

```jsx
// Wrong — conditional Hook
if (isLoggedIn) {
  const [name, setName] = useState("");
}

// Correct — top level, always runs
const [name, setName] = useState("");
```

**Rule 2 — Only call Hooks from React functions.**
Call them from components or from other custom Hooks, never from regular JavaScript functions.

```text
First render:   useState, useEffect, useRef   (order: 1, 2, 3)
Second render:  useState, useEffect, useRef   (same order: 1, 2, 3)
```

If the order changes between renders, React loses track of which state belongs to which Hook. That is why the rules exist.

---

## 3. useState — Local State

`useState` adds a piece of state to a component. When the state changes, the component re-renders.

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

- `useState(0)` sets the initial value to `0`.
- It returns a pair: `[value, setterFunction]`.
- Calling `setCount` updates the value **and** triggers a re-render.

**Updater function form** — use this when the new value depends on the old one:

```jsx
setCount(prev => prev + 1);
```

This avoids bugs with stale values, especially when updating multiple times in a row.

**Updating objects and arrays** — never mutate; create a new copy:

```jsx
const [user, setUser] = useState({ name: "Ada", age: 36 });

// Correct — spread the old object, override one field
setUser({ ...user, age: 37 });

const [items, setItems] = useState([]);

// Correct — new array, don't push into the old one
setItems([...items, "new item"]);
```

---

## 4. useEffect — Side Effects

A **side effect** is anything outside rendering: fetching data, timers, subscriptions, logging, or manually touching the DOM. `useEffect` runs this code **after** the component renders.

```jsx
import { useState, useEffect } from "react";

function Title() {
  const [count, setCount] = useState(0);

  useEffect(() => {
    document.title = `Clicked ${count} times`;
  }, [count]); // re-run whenever count changes

  return <button onClick={() => setCount(count + 1)}>Click</button>;
}
```

The **dependency array** (second argument) controls when the effect runs:

```text
useEffect(fn)         → after every render
useEffect(fn, [])     → once, after the first render
useEffect(fn, [a, b]) → when a or b changes
```

**Cleanup function** — return a function to undo the effect (stop timers, unsubscribe). It runs before the next effect and when the component unmounts.

```jsx
useEffect(() => {
  const id = setInterval(() => console.log("tick"), 1000);

  return () => clearInterval(id); // cleanup
}, []);
```

**Fetching data on mount:**

```jsx
useEffect(() => {
  fetch("https://jsonplaceholder.typicode.com/users")
    .then((res) => res.json())
    .then((data) => setUsers(data));
}, []);
```

---

## 5. useRef — Persisting Values Without Re-rendering

`useRef` gives you a mutable "box" whose `.current` property survives across renders. Changing it does **not** cause a re-render.

Two main uses:

**Use 1 — Access a DOM element directly:**

```jsx
import { useRef } from "react";

function FocusInput() {
  const inputRef = useRef(null);

  function focusField() {
    inputRef.current.focus();
  }

  return (
    <div>
      <input ref={inputRef} />
      <button onClick={focusField}>Focus the input</button>
    </div>
  );
}
```

**Use 2 — Store a value that should not trigger re-renders** (e.g., a timer ID or a previous value):

```jsx
const renderCount = useRef(0);
renderCount.current += 1; // changes silently, no re-render
```

Key difference from state:

```text
useState  → change triggers re-render  → use for UI data
useRef    → change is silent           → use for non-visual values / DOM
```

---

## 6. useContext — Avoiding Prop Drilling

Passing props through many layers just to reach a deep child is called **prop drilling**. `useContext` lets any component read shared data directly.

Three steps:

**Step 1 — Create a context:**

```jsx
import { createContext } from "react";

export const ThemeContext = createContext("light");
```

**Step 2 — Provide a value at the top:**

```jsx
import { ThemeContext } from "./ThemeContext";

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Toolbar />
    </ThemeContext.Provider>
  );
}
```

**Step 3 — Consume it anywhere below, no props needed:**

```jsx
import { useContext } from "react";
import { ThemeContext } from "./ThemeContext";

function Button() {
  const theme = useContext(ThemeContext);
  return <button className={theme}>I am {theme} themed</button>;
}
```

Context is ideal for app-wide data: theme, current user, language.

---

## 7. useReducer — Structured State Logic

When state has many related fields or complex update rules, `useReducer` is cleaner than multiple `useState` calls. It centralizes updates in a single **reducer** function.

```jsx
import { useReducer } from "react";

function reducer(state, action) {
  switch (action.type) {
    case "increment":
      return { count: state.count + 1 };
    case "decrement":
      return { count: state.count - 1 };
    case "reset":
      return { count: 0 };
    default:
      return state;
  }
}

function Counter() {
  const [state, dispatch] = useReducer(reducer, { count: 0 });

  return (
    <div>
      <p>Count: {state.count}</p>
      <button onClick={() => dispatch({ type: "increment" })}>+</button>
      <button onClick={() => dispatch({ type: "decrement" })}>-</button>
      <button onClick={() => dispatch({ type: "reset" })}>Reset</button>
    </div>
  );
}
```

How it works:

- `reducer(state, action)` returns the **new** state based on the action.
- `dispatch(action)` sends an action to the reducer.
- `state` holds the current value.

Think of it like a tiny state machine. Use it when `useState` logic becomes tangled.

---

## 8. useMemo — Caching a Computed Value

`useMemo` remembers (**memoizes**) the result of an expensive calculation and only recomputes it when its dependencies change.

```jsx
import { useMemo, useState } from "react";

function ProductList({ products }) {
  const [query, setQuery] = useState("");

  const filtered = useMemo(() => {
    console.log("Filtering..."); // only logs when inputs change
    return products.filter((p) => p.name.includes(query));
  }, [products, query]);

  return (
    <div>
      <input value={query} onChange={(e) => setQuery(e.target.value)} />
      <ul>
        {filtered.map((p) => (
          <li key={p.id}>{p.name}</li>
        ))}
      </ul>
    </div>
  );
}
```

Without `useMemo`, the filter would run on every render. With it, the result is reused unless `products` or `query` changes.

Only reach for `useMemo` when a calculation is genuinely expensive — overusing it adds complexity for no gain.

---

## 9. useCallback — Caching a Function

Every render creates new function objects. `useCallback` returns the **same** function instance between renders (until dependencies change). This matters when passing callbacks to optimized child components.

```jsx
import { useCallback, useState } from "react";

function Parent() {
  const [count, setCount] = useState(0);

  // Same function reference across renders
  const handleClick = useCallback(() => {
    console.log("clicked");
  }, []);

  return <Child onClick={handleClick} />;
}
```

Relationship to `useMemo`:

```text
useMemo(() => value, deps)      → caches a VALUE
useCallback(fn, deps)           → caches a FUNCTION
useCallback(fn, deps)  ===  useMemo(() => fn, deps)
```

Like `useMemo`, use it only when it solves a real performance problem (usually paired with `React.memo` on the child).

---

## 10. Custom Hooks — Reusing Logic

A **custom Hook** is your own function that starts with `use` and calls other Hooks. It lets you extract and share stateful logic between components.

Example — a reusable "get window width" Hook:

```jsx
import { useState, useEffect } from "react";

function useWindowWidth() {
  const [width, setWidth] = useState(window.innerWidth);

  useEffect(() => {
    const handleResize = () => setWidth(window.innerWidth);
    window.addEventListener("resize", handleResize);

    return () => window.removeEventListener("resize", handleResize);
  }, []);

  return width;
}
```

Use it like any built-in Hook:

```jsx
function Display() {
  const width = useWindowWidth();
  return <p>Window width: {width}px</p>;
}
```

Another common example — syncing state to `localStorage`:

```jsx
import { useState, useEffect } from "react";

function useLocalStorage(key, initialValue) {
  const [value, setValue] = useState(() => {
    const stored = localStorage.getItem(key);
    return stored ? JSON.parse(stored) : initialValue;
  });

  useEffect(() => {
    localStorage.setItem(key, JSON.stringify(value));
  }, [key, value]);

  return [value, setValue];
}
```

Custom Hooks are the primary way to keep components small and avoid copy-pasting logic.

---

## 11. Choosing the Right Hook

```text
Need…                                   Use…
────────────────────────────────────────────────────
Simple local state                      useState
Many related state fields / rules       useReducer
Run code after render (fetch, timer)    useEffect
Access a DOM node                        useRef
Keep a value without re-rendering       useRef
Share data across the tree              useContext
Cache an expensive calculation          useMemo
Cache a function reference               useCallback
Reuse stateful logic                     custom Hook
```

Start with `useState` and `useEffect` — they cover the vast majority of real-world needs. Add the others only when a specific problem calls for them.

---

## 12. Common Hook Mistakes

- **Calling Hooks conditionally** or inside loops — breaks the rules of Hooks.
- **Mutating state directly** instead of returning a new value via the setter.
- **Wrong `useEffect` dependencies** — missing a dependency causes stale data; adding unstable ones causes infinite loops.
- **Infinite loops** — setting state inside an effect that has no (or wrong) dependency array.
- **Overusing `useMemo` / `useCallback`** — premature optimization that adds noise.
- **Expecting `useRef` changes to re-render** — they never do; use state for visible data.

Example of an accidental infinite loop:

```jsx
// Wrong — effect runs every render, sets state, re-renders, repeats forever
useEffect(() => {
  setCount(count + 1);
}); // no dependency array!
```

---

## 13. Key Takeaways

- Hooks let **function components** use state and lifecycle features.
- Hook names start with **`use`** and must follow the **two rules**: top level only, React functions only.
- **`useState`** for local state; **`useReducer`** for complex state.
- **`useEffect`** runs side effects; its **dependency array** controls when, and the **cleanup function** tears down.
- **`useRef`** persists values without re-rendering and accesses DOM nodes.
- **`useContext`** shares data and avoids prop drilling.
- **`useMemo`** caches values; **`useCallback`** caches functions — use sparingly.
- **Custom Hooks** package reusable logic into your own `use...` function.

---

## 14. Where to Go Next

- **React Router** — navigation with Hooks like `useNavigate` and `useParams`.
- **TanStack Query** — data fetching and caching built on Hooks (`useQuery`).
- **Zustand / Redux Toolkit** — state management with Hook-based APIs.
- **`useLayoutEffect`** — like `useEffect` but runs synchronously before paint.
- **`useImperativeHandle`** and **`forwardRef`** — advanced ref patterns.
- **Testing Hooks** — React Testing Library and `renderHook`.

---

## Related Notes

- [[react-deep-dive]]
- [[javascript-fundamentals]]
- [[frontend-architecture]]
- [[react-state-management]]

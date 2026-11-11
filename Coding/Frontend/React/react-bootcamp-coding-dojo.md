# React Bootcamp — Coding Dojo Edition

> A hands-on, exercise-driven bootcamp for running React Coding Dojos.
> Each section has a short concept, a **live-code demo**, and **katas** to solve together.
> Companion notes: [[react-deep-dive]], [[react-hooks-deep-dive]], [[react-redux-deep-dive]].

---

## 0. How to Run a React Coding Dojo

A **Coding Dojo** is a group practice session where people write code together to improve through deliberate practice. Keep it collaborative, not a lecture.

**Formats:**

- **Randori** — one keyboard, the whole group. A **driver** types, a **navigator** guides, the audience watches. Rotate every 5–7 minutes so everyone drives.
- **Pair programming** — split into pairs, each pair works the same kata, compare solutions at the end.
- **Mob programming** — one screen, whole mob contributes, rotate the driver on a timer.

**The TDD rhythm (Red → Green → Refactor):**

```text
RED      → write a failing test (or a broken UI expectation)
GREEN    → write the minimum code to make it pass
REFACTOR → clean it up without changing behavior
```

**Facilitation rules:**

- Rotate the driver on a timer (use `npm` scripts or a kitchen timer).
- The navigator explains intent; the driver types.
- No judgment — the dojo is for practice, mistakes are the point.
- Timebox every kata. Stop and discuss when the timer rings, even if unfinished.

---

## 1. Dojo Setup (Do This First, Together)

Everyone needs the same starting point. Create a scratch project for the dojo:

```powershell
npm create vite@latest dojo-react -- --template react
cd dojo-react
npm install
npm run dev
```

Add a test runner so katas can be TDD-style. The versions below are pinned to the set verified against Vite 7 / React 19 with zero security advisories:

```powershell
npm install -D vitest@^5.1.0 @testing-library/react@^16.1.0 @testing-library/jest-dom@^6.6.3 jsdom@^25.0.1
```

Add a test script to `package.json`:

```json
{
  "scripts": {
    "dev": "vite",
    "test": "vitest",
    "test:run": "vitest run"
  }
}
```

Create `src/setupTests.js`:

```javascript
import "@testing-library/jest-dom";
```

Point Vitest at it in `vite.config.js`:

```javascript
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

export default defineConfig({
  plugins: [react()],
  test: {
    globals: true,
    environment: "jsdom",
    setupFiles: "./src/setupTests.js",
  },
});
```

Run the tests in watch mode during the dojo:

```powershell
npm run test
```

---

## 2. Warm-Up Kata — Hello Dojo (10 min)

**Concept:** a component is a function returning JSX.

**Demo:**

```jsx
function HelloDojo() {
  return <h1>Hello, Dojo!</h1>;
}
```

**Kata — Red/Green:**
Write a test first, then make it pass.

```jsx
// HelloDojo.test.jsx
import { render, screen } from "@testing-library/react";
import HelloDojo from "./HelloDojo";

test("greets the dojo", () => {
  render(<HelloDojo />);
  expect(screen.getByText("Hello, Dojo!")).toBeInTheDocument();
});
```

**Challenges (rotate drivers):**

1. Make the greeting accept a `name` prop: `<HelloDojo name="Ada" />`.
2. Default the name to `"Dojo"` when no prop is given.
3. Render the current time below the greeting.

---

## 3. Kata — The Counter (15 min)

**Concept:** state with `useState`, event handling.

**Demo:**

```jsx
import { useState } from "react";

function Counter() {
  const [count, setCount] = useState(0);
  return (
    <div>
      <p data-testid="value">{count}</p>
      <button onClick={() => setCount(count + 1)}>+</button>
    </div>
  );
}
```

**Kata — grow it step by step (one feature per driver):**

1. Add a **decrement** button.
2. Add a **reset** button.
3. Prevent the count from going below `0`.
4. Add a **step** input so the user chooses how much to add.
5. Change the color to red when the count is negative (trick: combine with step 3's removal).

**Test to drive step 1:**

```jsx
import { render, screen, fireEvent } from "@testing-library/react";
import Counter from "./Counter";

test("decrements the count", () => {
  render(<Counter />);
  fireEvent.click(screen.getByText("-"));
  expect(screen.getByTestId("value")).toHaveTextContent("-1");
});
```

**Discussion prompt:** when does the updater form `setCount(prev => prev + 1)` matter? (Answer: rapid successive updates.)

---

## 4. Kata — Controlled Form (15 min)

**Concept:** controlled components, `onChange`, single source of truth.

**Demo:**

```jsx
import { useState } from "react";

function LoginForm() {
  const [email, setEmail] = useState("");
  return (
    <input
      aria-label="email"
      value={email}
      onChange={(e) => setEmail(e.target.value)}
    />
  );
}
```

**Kata — build a sign-up form:**

1. Add a password field.
2. Disable the submit button until both fields are non-empty.
3. Show a validation message if the email has no `@`.
4. On submit, display the entered email below the form (prevent default page reload).
5. Reset the form after submit.

**Discussion prompt:** what makes this a "controlled" component, and why is it React's preferred pattern?

---

## 5. Kata — The To-Do List (20 min)

**Concept:** rendering lists, `key`, immutable array updates.

**Demo:**

```jsx
import { useState } from "react";

function TodoList() {
  const [todos, setTodos] = useState([]);
  const [text, setText] = useState("");

  function add() {
    setTodos([...todos, { id: Date.now(), text, done: false }]);
    setText("");
  }

  return (
    <div>
      <input value={text} onChange={(e) => setText(e.target.value)} />
      <button onClick={add}>Add</button>
      <ul>
        {todos.map((t) => (
          <li key={t.id}>{t.text}</li>
        ))}
      </ul>
    </div>
  );
}
```

**Kata — the classic, grown in rounds:**

1. Toggle a todo as done (strike-through when done).
2. Delete a todo.
3. Show a counter: "3 of 5 remaining".
4. Add filter buttons: All / Active / Completed.
5. Persist todos to `localStorage` (bridges into the custom-Hook kata).

**Trap to watch for:** using the array index as `key`. Discuss why `t.id` is safer when items are reordered or deleted.

---

## 6. Kata — useEffect & Data Fetching (20 min)

**Concept:** side effects, dependency array, loading/error states.

**Demo:**

```jsx
import { useState, useEffect } from "react";

function Users() {
  const [users, setUsers] = useState([]);

  useEffect(() => {
    fetch("https://jsonplaceholder.typicode.com/users")
      .then((r) => r.json())
      .then(setUsers);
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

**Kata — make it robust:**

1. Show a "Loading..." message while fetching.
2. Show an error message if the request fails (test by breaking the URL).
3. Add a search box that filters the fetched list (client-side).
4. Add a "Refresh" button that re-fetches.
5. Cancel/ignore the result if the component unmounts mid-fetch (cleanup function).

**Discussion prompt:** what happens with an empty `[]` dependency array vs no array at all? (Live-demo the infinite loop to make it memorable.)

---

## 7. Kata — Build a Custom Hook (20 min)

**Concept:** extracting reusable stateful logic.

**Demo — `useLocalStorage`:**

```jsx
import { useState, useEffect } from "react";

export function useLocalStorage(key, initial) {
  const [value, setValue] = useState(() => {
    const stored = localStorage.getItem(key);
    return stored ? JSON.parse(stored) : initial;
  });

  useEffect(() => {
    localStorage.setItem(key, JSON.stringify(value));
  }, [key, value]);

  return [value, setValue];
}
```

**Kata — write these custom Hooks as a mob:**

1. `useToggle(initial)` → returns `[on, toggle]`.
2. `useCounter(start)` → returns `{ count, inc, dec, reset }`.
3. `usePrevious(value)` → returns the value from the previous render (hint: `useRef`).
4. `useDebounce(value, delay)` → returns the value after it stops changing for `delay` ms.
5. Refactor the To-Do kata (Section 5) to use `useLocalStorage`.

**Discussion prompt:** what makes something a custom Hook vs a normal function? (It calls other Hooks and follows the Rules of Hooks.)

---

## 8. Kata — Lifting State & Composition (15 min)

**Concept:** sharing state between siblings, data down / events up.

**Kata — temperature converter:**

Build two inputs, Celsius and Fahrenheit, that stay in sync.

1. Create a `TemperatureInput` child component with `value` + `onChange` props.
2. Lift the temperature state to a parent.
3. When one input changes, convert and update the other.
4. Add a boiling-water indicator ("Water would boil") above 100°C.

**Discussion prompt:** which component owns the state, and why can't the children own it independently?

---

## 9. Kata — useContext (15 min)

**Concept:** avoiding prop drilling with shared data.

**Kata — theme switcher:**

1. Create a `ThemeContext` with a default of `"light"`.
2. Wrap the app in a `ThemeContext.Provider`.
3. Add a deeply nested button that reads the theme via `useContext`.
4. Add a toggle at the top level that flips light/dark (hint: provide `{ theme, toggle }` as the value).
5. Apply the theme by switching a CSS class on the root element.

**Discussion prompt:** when is Context the right tool, and when is it overkill compared to props?

---

## 10. Boss Kata — Redux Mini-App (30 min)

**Concept:** centralized state with Redux Toolkit. See [[react-redux-deep-dive]] for the deep theory.

**Setup:**

```powershell
npm install @reduxjs/toolkit react-redux
```

**Kata — shopping cart (mob programming recommended):**

1. Create a `cartSlice` with state `{ items: [] }`.
2. Add reducers: `addItem`, `removeItem`, `clearCart`.
3. Configure the store and wrap the app in `<Provider>`.
4. Build a product list; clicking "Add" dispatches `addItem`.
5. Show a cart summary using `useSelector` (item count + total price).
6. **Stretch:** add `increaseQty` / `decreaseQty` reducers.
7. **Stretch:** add an async thunk that loads products from an API.

**Discussion prompt:** which of today's katas actually needed Redux, and which were fine with `useState`?

---

## 11. Lightning Katas (5–10 min each, for filling time)

Quick challenges to drop in between bigger katas or as warm-ups:

- **FizzBuzz in JSX** — render 1–100, replacing multiples of 3/5 with Fizz/Buzz.
- **Star rating** — 5 clickable stars that highlight on hover and select on click.
- **Accordion** — a list of panels where only one is open at a time.
- **Stopwatch** — start / stop / reset using `useEffect` + `setInterval`.
- **Tabs** — switch between tab contents with a single active-index state.
- **Character counter** — a textarea that shows remaining characters out of 280.
- **Light switch** — a button that toggles a div between "on" and "off".

---

## 12. Facilitator Cheat Sheet

```text
Timebox everything.          Ring a bell when time's up.
Rotate drivers every 5–7m.   Everyone types, no spectators.
Navigator speaks intent.     Driver types, doesn't decide alone.
Red → Green → Refactor.      Write the test first when possible.
Smallest step that works.    Resist gold-plating.
Discuss after each kata.     "What surprised you? What's cleaner?"
Keep it blameless.           Bugs are learning, not failure.
```

**Common teachable moments to watch for:**

- Mutating state directly → component won't update.
- Missing `key` on a list → subtle reorder bugs.
- Stale closure in `useEffect` → wrong dependency array.
- `useState` for everything → when to lift, when to Context, when to Redux.

---

## 13. Difficulty Ladder

Order katas by the group's level:

```text
Beginner      →  2 (Hello) · 3 (Counter) · 4 (Form)
Intermediate  →  5 (To-Do) · 6 (Fetch) · 8 (Lifting)
Advanced      →  7 (Custom Hooks) · 9 (Context) · 10 (Redux)
Any time      →  11 (Lightning katas)
```

A single 90-minute dojo might run: Setup → Counter → To-Do → one Lightning kata → retro.

---

## 14. Retro Template (Last 10 min)

End every dojo with a short retrospective:

```text
KEEP     → What worked well? What patterns clicked?
DROP     → What slowed us down or confused us?
TRY      → What do we want to attempt next session?
```

Capture the answers as a note and link it back here for continuity between sessions.

---

## 15. Key Takeaways

- A dojo is **deliberate practice**: small steps, rotation, discussion — not a lecture.
- Use the **Red → Green → Refactor** rhythm to keep katas focused.
- Grow each kata **one feature per driver** so everyone contributes.
- Progress along the **difficulty ladder**: state → lists → effects → custom Hooks → Context → Redux.
- The katas map directly onto the concepts in the companion deep-dive notes.
- End with a **retro** to compound learning across sessions.

---

## Related Notes

- [[react-deep-dive]]
- [[react-hooks-deep-dive]]
- [[react-redux-deep-dive]]
- [[coding-dojo-facilitation]]
- [[tdd-deep-dive]]
- [[react-state-management]]

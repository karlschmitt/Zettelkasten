# React Redux Deep-Dive Tutorial

## 1. What Is Redux?

**Redux** is a predictable **state management** library. It stores your application's shared state in one central place — the **store** — so any component can read or update it without passing props through many layers.

Use Redux when:

- Many components need the same data (user, cart, theme, auth).
- State updates come from many places and get hard to track.
- You want predictable, debuggable, testable state changes.

Do **not** reach for Redux for small apps — React's own `useState` and `useContext` are often enough. Redux earns its place as complexity grows.

```text
Component A ─┐
Component B ─┼──▶  Central Store  ◀── single source of truth
Component C ─┘
```

**Important:** This tutorial uses **Redux Toolkit (RTK)** — the official, modern way to write Redux. The old "hand-written" Redux with lots of boilerplate is no longer recommended.

---

## 2. The Core Idea: One-Way Data Flow

Redux enforces a strict, one-directional cycle. This predictability is its whole point.

```text
   ┌──────────────────────────────────────────┐
   │                                            │
   ▼                                            │
 STORE  ──▶  Component reads state              │
   ▲                                            │
   │                                            │
 REDUCER  ◀──  ACTION  ◀──  dispatch()  ◀───────┘
 (computes new state)      (user does something)
```

The vocabulary:

- **Store** — the single object holding all state.
- **Action** — a plain object describing *what happened* (e.g., "increment").
- **Dispatch** — the only way to send an action to the store.
- **Reducer** — a function that takes the current state + an action and returns the **new** state.

State is **read-only**. The only way to change it is to dispatch an action, which runs a reducer.

---

## 3. Install Redux Toolkit

In an existing React project (see `react-deep-dive` for creating one with Vite):

```powershell
npm install @reduxjs/toolkit react-redux
```

- `@reduxjs/toolkit` — the core Redux logic (store, reducers, actions).
- `react-redux` — the bindings that connect Redux to React components.

Verify they are listed in `package.json`:

```powershell
npm list @reduxjs/toolkit react-redux
```

---

## 4. Create a Slice

A **slice** is a bundle of state plus the reducers that change it, for one feature of your app. `createSlice` generates the actions and reducers for you automatically.

Create `src/features/counter/counterSlice.js`:

```javascript
import { createSlice } from "@reduxjs/toolkit";

const counterSlice = createSlice({
  name: "counter",
  initialState: { value: 0 },
  reducers: {
    increment: (state) => {
      state.value += 1;
    },
    decrement: (state) => {
      state.value -= 1;
    },
    incrementByAmount: (state, action) => {
      state.value += action.payload;
    },
  },
});

export const { increment, decrement, incrementByAmount } = counterSlice.actions;
export default counterSlice.reducer;
```

Notice `state.value += 1` — it looks like mutation, but RTK uses a library called **Immer** under the hood that turns this into a safe, immutable update. This only works inside `createSlice` reducers.

- `name` — a label used as a prefix for action types.
- `initialState` — the starting state for this slice.
- `reducers` — functions that describe how state changes.
- `action.payload` — the data carried by an action.

---

## 5. Configure the Store

The store combines all your slices into one state tree. Create `src/app/store.js`:

```javascript
import { configureStore } from "@reduxjs/toolkit";
import counterReducer from "../features/counter/counterSlice";

export const store = configureStore({
  reducer: {
    counter: counterReducer,
  },
});
```

The keys under `reducer` become the top-level fields of your state:

```text
state = {
  counter: { value: 0 }
}
```

`configureStore` also sets up the Redux DevTools and good default middleware automatically — no extra setup needed.

---

## 6. Provide the Store to React

Wrap your whole app in the `<Provider>` so every component can access the store. Edit `src/main.jsx`:

```jsx
import React from "react";
import ReactDOM from "react-dom/client";
import { Provider } from "react-redux";
import { store } from "./app/store";
import App from "./App";

ReactDOM.createRoot(document.getElementById("root")).render(
  <React.StrictMode>
    <Provider store={store}>
      <App />
    </Provider>
  </React.StrictMode>
);
```

Now any component inside `<App />` can read from and dispatch to the store.

---

## 7. Read State with useSelector

The `useSelector` Hook reads a value from the store. Your component automatically re-renders when that value changes.

```jsx
import { useSelector } from "react-redux";

function CounterDisplay() {
  const count = useSelector((state) => state.counter.value);

  return <p>Current count: {count}</p>;
}
```

The function you pass is a **selector**: it receives the whole state and returns just the piece you care about (`state.counter.value`).

---

## 8. Update State with useDispatch

The `useDispatch` Hook gives you the `dispatch` function. You call it with an action creator (the functions exported from your slice).

```jsx
import { useDispatch } from "react-redux";
import { increment, decrement, incrementByAmount } from "./features/counter/counterSlice";

function CounterButtons() {
  const dispatch = useDispatch();

  return (
    <div>
      <button onClick={() => dispatch(increment())}>+1</button>
      <button onClick={() => dispatch(decrement())}>-1</button>
      <button onClick={() => dispatch(incrementByAmount(5))}>+5</button>
    </div>
  );
}
```

- `increment()` returns the action object `{ type: "counter/increment" }`.
- `incrementByAmount(5)` returns `{ type: "counter/incrementByAmount", payload: 5 }`.
- `dispatch(...)` sends it to the store, which runs the reducer and updates state.

---

## 9. Putting It All Together

A complete counter component using both Hooks:

```jsx
import { useSelector, useDispatch } from "react-redux";
import { increment, decrement, incrementByAmount } from "./features/counter/counterSlice";

function Counter() {
  const count = useSelector((state) => state.counter.value);
  const dispatch = useDispatch();

  return (
    <div>
      <h2>Count: {count}</h2>
      <button onClick={() => dispatch(decrement())}>-1</button>
      <button onClick={() => dispatch(increment())}>+1</button>
      <button onClick={() => dispatch(incrementByAmount(10))}>+10</button>
    </div>
  );
}

export default Counter;
```

The full flow in one picture:

```text
User clicks "+1"
     ↓
dispatch(increment())
     ↓
counterSlice reducer runs → state.value += 1
     ↓
store updates
     ↓
useSelector notices the change
     ↓
Counter re-renders with the new count
```

---

## 10. A Second Slice: Managing a List

Real apps have multiple slices. Here is a todo slice to show state beyond a single number. Create `src/features/todos/todosSlice.js`:

```javascript
import { createSlice } from "@reduxjs/toolkit";

const todosSlice = createSlice({
  name: "todos",
  initialState: { items: [] },
  reducers: {
    addTodo: (state, action) => {
      state.items.push({ id: Date.now(), text: action.payload, done: false });
    },
    toggleTodo: (state, action) => {
      const todo = state.items.find((t) => t.id === action.payload);
      if (todo) todo.done = !todo.done;
    },
    removeTodo: (state, action) => {
      state.items = state.items.filter((t) => t.id !== action.payload);
    },
  },
});

export const { addTodo, toggleTodo, removeTodo } = todosSlice.actions;
export default todosSlice.reducer;
```

Register it in the store alongside the counter:

```javascript
import { configureStore } from "@reduxjs/toolkit";
import counterReducer from "../features/counter/counterSlice";
import todosReducer from "../features/todos/todosSlice";

export const store = configureStore({
  reducer: {
    counter: counterReducer,
    todos: todosReducer,
  },
});
```

Now the state tree looks like:

```text
state = {
  counter: { value: 0 },
  todos:   { items: [] }
}
```

---

## 11. Async Logic with createAsyncThunk

Reducers must be pure and synchronous, so API calls go through a **thunk**. `createAsyncThunk` handles the "loading / success / error" lifecycle for you.

```javascript
import { createSlice, createAsyncThunk } from "@reduxjs/toolkit";

export const fetchUsers = createAsyncThunk("users/fetch", async () => {
  const res = await fetch("https://jsonplaceholder.typicode.com/users");
  return res.json(); // becomes action.payload on success
});

const usersSlice = createSlice({
  name: "users",
  initialState: { list: [], status: "idle" },
  reducers: {},
  extraReducers: (builder) => {
    builder
      .addCase(fetchUsers.pending, (state) => {
        state.status = "loading";
      })
      .addCase(fetchUsers.fulfilled, (state, action) => {
        state.status = "succeeded";
        state.list = action.payload;
      })
      .addCase(fetchUsers.rejected, (state) => {
        state.status = "failed";
      });
  },
});

export default usersSlice.reducer;
```

Dispatch it from a component, usually inside `useEffect`:

```jsx
import { useEffect } from "react";
import { useSelector, useDispatch } from "react-redux";
import { fetchUsers } from "./features/users/usersSlice";

function UserList() {
  const dispatch = useDispatch();
  const { list, status } = useSelector((state) => state.users);

  useEffect(() => {
    dispatch(fetchUsers());
  }, [dispatch]);

  if (status === "loading") return <p>Loading...</p>;
  if (status === "failed") return <p>Something went wrong.</p>;

  return (
    <ul>
      {list.map((u) => (
        <li key={u.id}>{u.name}</li>
      ))}
    </ul>
  );
}
```

The three lifecycle actions — `pending`, `fulfilled`, `rejected` — are generated automatically.

---

## 12. Redux DevTools

Install the **Redux DevTools** browser extension (Chrome/Firefox). Because `configureStore` wires it up by default, you get:

- A live view of the entire state tree.
- A log of every dispatched action with its payload.
- **Time-travel debugging** — step back and forth through state changes.

This visibility is one of the biggest practical reasons teams choose Redux.

---

## 13. Project Structure

A common, feature-based layout (the "ducks" pattern, recommended by the Redux team):

```text
src/
├── app/
│   └── store.js                 ← configureStore
├── features/
│   ├── counter/
│   │   ├── counterSlice.js       ← state + reducers + actions
│   │   └── Counter.jsx           ← component
│   ├── todos/
│   │   ├── todosSlice.js
│   │   └── TodoList.jsx
│   └── users/
│       ├── usersSlice.js
│       └── UserList.jsx
└── main.jsx                      ← <Provider store={store}>
```

Keeping each feature's slice and components together makes the app easy to navigate as it grows.

---

## 14. Common Beginner Mistakes

- **Writing raw Redux** instead of Redux Toolkit — RTK removes most boilerplate; use it.
- **Mutating state outside a slice** — the "mutate" syntax (`state.value += 1`) is only safe inside `createSlice` thanks to Immer.
- **Putting async calls in reducers** — reducers must be pure; use `createAsyncThunk`.
- **Over-selecting** — `useSelector((state) => state)` re-renders on every change. Select only what you need.
- **Using Redux for everything** — local UI state (form inputs, toggles) usually belongs in `useState`.
- **Forgetting `<Provider>`** — components throw an error if the store is not provided.

---

## 15. Redux vs useState vs useContext

```text
Tool          Best for
──────────────────────────────────────────────────────────
useState      Local state inside one component
useContext    Low-frequency shared data (theme, locale)
Redux (RTK)   Complex, frequently-updated, app-wide state
              with many sources of change + DevTools
```

Start simple. Promote state to Redux only when sharing and tracking it becomes painful.

---

## 16. Key Takeaways

- Redux centralizes shared state in a single **store** with strict **one-way data flow**.
- Use **Redux Toolkit** — `createSlice`, `configureStore`, `createAsyncThunk`.
- A **slice** bundles state + reducers + auto-generated actions for one feature.
- Wrap the app in **`<Provider>`** to give components access to the store.
- **`useSelector`** reads state; **`useDispatch`** sends actions.
- "Mutating" state is safe only inside slices (Immer makes it immutable).
- Handle async with **`createAsyncThunk`** and its `pending`/`fulfilled`/`rejected` cases.
- Reach for Redux only when the app's shared state truly needs it.

---

## 17. Where to Go Next

- **RTK Query** — Redux Toolkit's built-in data fetching & caching (often replaces manual thunks).
- **Redux DevTools** — master time-travel debugging.
- **Reselect / `createSelector`** — memoized selectors for derived data.
- **Redux with TypeScript** — typed hooks (`useAppSelector`, `useAppDispatch`).
- **Normalizing state** — `createEntityAdapter` for lists of items.
- **Testing** — unit-testing reducers and thunks.

---

## Related Notes

- [[react-deep-dive]]
- [[react-hooks-deep-dive]]
- [[react-state-management]]
- [[javascript-fundamentals]]
- [[frontend-architecture]]

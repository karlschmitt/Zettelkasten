# dojo-react

A ready-to-use **React Coding Dojo** playground. This project is the companion sandbox for the
`react-bootcamp-coding-dojo.md` tutorial — a place to run katas, pair, and mob-program your way
through React fundamentals with tests already wired up.

> New to the dojo format or the katas? Read the bootcamp note first:
> `../react-bootcamp-coding-dojo.md`

---

## What's Inside

- **React 19** + **Vite 7** — fast dev server with Hot Module Replacement (HMR).
- **Vitest 5** + **Testing Library** + **jsdom** — test runner wired up for TDD katas.
- A first passing kata: `src/HelloDojo.jsx` and `src/HelloDojo.test.jsx`.
- Zero known security advisories (`npm audit` is clean).

---

## Prerequisites

- **Node.js 18+** (built and tested on Node 22). Check with:

  ```powershell
  node --version
  npm --version
  ```

If dependencies are ever missing or out of sync, reinstall them:

```powershell
npm install
```

---

## Quick Start

Start the dev server and open the app in your browser:

```powershell
npm run dev
```

Vite prints a local URL (usually `http://localhost:5173`). Edit any file in `src/` and the page
updates instantly thanks to HMR.

---

## Running Tests (the heart of a dojo)

Run tests in **watch mode** — they re-run automatically every time you save. This is the mode to
use *during* a dojo so you get the Red → Green → Refactor feedback loop:

```powershell
npm run test
```

Run the suite **once** (no watch) — handy for a quick check or CI:

```powershell
npm run test:run
```

Expected output for the starter kata:

```text
 ✓ src/HelloDojo.test.jsx (1 test)
 Test Files  1 passed (1)
      Tests  1 passed (1)
```

---

## All Available Scripts

```text
npm run dev        Start the Vite dev server with HMR
npm run test       Run Vitest in watch mode (use this during dojos)
npm run test:run   Run the whole test suite once and exit
npm run build      Produce an optimized production build in dist/
npm run preview    Serve the production build locally to inspect it
npm run lint       Lint the project with ESLint
```

---

## The TDD Dojo Rhythm

Each kata is practiced in small steps:

```text
RED      → write a failing test that describes the next tiny feature
GREEN    → write the minimum code to make it pass
REFACTOR → clean up without changing behavior (tests stay green)
```

Keep `npm run test` running in a terminal so you see red turn green as you type.

---

## How to Add a New Kata

1. Create the component, e.g. `src/Counter.jsx`:

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

   export default Counter;
   ```

2. Create the test beside it, `src/Counter.test.jsx`:

   ```jsx
   import { render, screen, fireEvent } from "@testing-library/react";
   import Counter from "./Counter";

   test("increments the count", () => {
     render(<Counter />);
     fireEvent.click(screen.getByText("+"));
     expect(screen.getByTestId("value")).toHaveTextContent("1");
   });
   ```

3. Vitest (in watch mode) picks it up automatically. Any file ending in
   `.test.jsx` or `.test.js` is treated as a test.

> Tip: query by what the user sees. Prefer `getByText`, `getByRole`, and `getByLabelText` over
> test IDs where you can — use `data-testid` only when there's no accessible handle.

---

## Project Structure

```text
dojo-react/
├── index.html              ← single HTML entry page
├── package.json            ← scripts & dependencies
├── vite.config.js          ← Vite + Vitest config (jsdom, setupFiles)
├── src/
│   ├── main.jsx            ← app entry point, mounts React
│   ├── App.jsx             ← root component (swap in your kata here)
│   ├── setupTests.js       ← loads jest-dom matchers for every test
│   ├── HelloDojo.jsx       ← starter kata component
│   └── HelloDojo.test.jsx  ← starter kata test (passing)
└── public/                 ← static assets
```

To see a kata in the browser, import it into `src/App.jsx` and render it, for example:

```jsx
import HelloDojo from "./HelloDojo";

function App() {
  return <HelloDojo />;
}

export default App;
```

---

## Test Setup Explained

The test environment is configured in two places:

- **`vite.config.js`** — the `test` block enables `globals` (so `test`/`expect` need no import),
  uses the `jsdom` browser-like environment, and loads `setupFiles` before each run.
- **`src/setupTests.js`** — imports `@testing-library/jest-dom`, which adds friendly matchers like
  `toBeInTheDocument()` and `toHaveTextContent()`.

---

## Troubleshooting

- **Port 5173 already in use** — Vite will offer the next free port, or run `npm run dev -- --port 3000`.
- **Tests don't re-run** — make sure you're using `npm run test` (watch), not `npm run test:run`.
- **`expect(...).toBeInTheDocument is not a function`** — `src/setupTests.js` isn't loading; confirm
  the `setupFiles` path in `vite.config.js`.
- **Stale or broken dependencies** — delete `node_modules` and reinstall:

  ```powershell
  Remove-Item -Recurse -Force node_modules
  npm install
  ```

---

## Reset the Playground

Dojos get messy — that's fine. To start fresh for a new session, delete the kata files you added in
`src/` (keep `main.jsx`, `App.jsx`, `setupTests.js`) and point `App.jsx` back at `HelloDojo`.

---

## Where to Go Next

- Work through the katas in order: Counter → Form → To-Do → useEffect → Custom Hooks → Context → Redux.
- The full kata list, difficulty ladder, and facilitator cheat sheet live in
  `../react-bootcamp-coding-dojo.md`.
- Deep-dive theory: `../react-deep-dive.md`, `../react-hooks-deep-dive.md`, `../react-redux-deep-dive.md`.

Happy coding — rotate the keyboard, keep it blameless, and let the tests guide you.

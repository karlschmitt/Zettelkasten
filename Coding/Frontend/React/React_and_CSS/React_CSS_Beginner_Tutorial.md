---
title: React CSS Beginner Tutorial
created: 2026-11-23
tags: [react, css, styling, frontend, tutorial, beginner]
---

# React CSS Beginner Tutorial (Step by Step)

> **Goal:** Learn the main ways to style a React app, and when to use each.
> **Prerequisites:** [[React Beginner Tutorial]] (components, props, state) and basic CSS (selectors, properties).

---

## 1. Overview: Ways to Style in React

| Method | Best for | Scoped to component? |
|---|---|---|
| Plain CSS file | Small apps, global styles | No |
| Inline styles | Dynamic one-off values | Yes |
| CSS Modules | Most apps, no name clashes | Yes |
| Tailwind CSS | Fast utility-based styling | Yes (via classes) |
| styled-components | CSS-in-JS, dynamic styling | Yes |

This tutorial covers the first four in detail.

---

## 2. Setup

Create a project (see [[React Beginner Tutorial]]):

```bash
npm create vite@latest css-demo -- --template react
cd css-demo
npm install
npm run dev
```

Replace `src/App.jsx` with:

```jsx
function App() {
  return <h1>Styling React</h1>;
}

export default App;
```

---

## 3. Method 1: Plain CSS File

### Step 1: Create the CSS
`src/App.css`:

```css
.title {
  color: royalblue;
  font-family: Arial, sans-serif;
  text-align: center;
}
```

### Step 2: Import and use it
```jsx
import "./App.css";

function App() {
  return <h1 className="title">Styling React</h1>;
}

export default App;
```

**Key rules:**
- Use **`className`**, not `class` (because `class` is a reserved word in JavaScript).
- A CSS file imported anywhere applies **globally** to the whole app. Two components using `.title` will clash.

### Global styles
`src/index.css` (imported in `main.jsx`) is the right place for resets and base styles:

```css
* {
  box-sizing: border-box;
}

body {
  margin: 0;
  font-family: system-ui, sans-serif;
  background: #f5f5f5;
}
```

---

## 4. Method 2: Inline Styles

Pass a JavaScript **object** to `style`.

```jsx
function App() {
  return (
    <h1 style={{ color: "tomato", fontSize: "32px", textAlign: "center" }}>
      Inline styled
    </h1>
  );
}
```

**Why double braces?** Outer `{}` = JavaScript inside JSX. Inner `{}` = the object.

**Rules:**
- Properties are **camelCase**: `background-color` → `backgroundColor`.
- Values are strings: `"20px"`. Plain numbers become pixels: `fontSize: 20`.
- No pseudo-classes (`:hover`) or media queries.

### Good use: dynamic values
```jsx
function Progress({ percent }) {
  return (
    <div style={{ background: "#ddd", width: "200px" }}>
      <div style={{ background: "green", width: `${percent}%`, height: "20px" }} />
    </div>
  );
}
```

Tip: store repeated styles in a variable.

```jsx
const boxStyle = { padding: 16, borderRadius: 8, background: "white" };
<div style={boxStyle}>...</div>
```

---

## 5. Method 3: CSS Modules (Recommended)

CSS Modules make class names **local to the component**, so no clashes.

### Step 1: Name the file `*.module.css`
`src/Button.module.css`:

```css
.button {
  background: royalblue;
  color: white;
  border: none;
  padding: 10px 20px;
  border-radius: 6px;
  cursor: pointer;
}

.button:hover {
  background: navy;
}
```

### Step 2: Import as an object
`src/Button.jsx`:

```jsx
import styles from "./Button.module.css";

function Button({ children }) {
  return <button className={styles.button}>{children}</button>;
}

export default Button;
```

### Step 3: Use it
```jsx
import Button from "./Button";

function App() {
  return <Button>Click me</Button>;
}
```

In the browser, the class becomes something like `Button_button__x7Fa2`, which is unique.

### Multiple classes
```jsx
<button className={`${styles.button} ${styles.large}`}>Big</button>
```

### Names with dashes
Use bracket notation: `styles["primary-button"]`. (Prefer camelCase names in CSS Modules.)

---

## 6. Conditional and Dynamic Styling

### Based on props
```css
/* Button.module.css */
.primary { background: royalblue; }
.danger  { background: crimson; }
```

```jsx
import styles from "./Button.module.css";

function Button({ variant = "primary", children }) {
  return (
    <button className={`${styles.button} ${styles[variant]}`}>
      {children}
    </button>
  );
}

// <Button variant="danger">Delete</Button>
```

### Based on state
```jsx
import { useState } from "react";
import styles from "./Toggle.module.css";

function Toggle() {
  const [on, setOn] = useState(false);

  return (
    <button
      className={on ? styles.on : styles.off}
      onClick={() => setOn(!on)}
    >
      {on ? "ON" : "OFF"}
    </button>
  );
}
```

### Helper library: `clsx` (optional)
```bash
npm install clsx
```

```jsx
import clsx from "clsx";

<button className={clsx(styles.button, on && styles.active)}>Go</button>
```

---

## 7. Layout Basics: Flexbox and Grid

Layout is plain CSS; it works the same in React.

### Flexbox (one dimension)
```css
.row {
  display: flex;
  gap: 16px;
  align-items: center;
  justify-content: space-between;
}
```

### Grid (two dimensions)
```css
.cards {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
  gap: 16px;
}
```

```jsx
<div className={styles.cards}>
  <Card /> <Card /> <Card />
</div>
```

---

## 8. Mini Project: Styled Card

`src/Card.module.css`:

```css
.card {
  background: white;
  border-radius: 12px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.15);
  padding: 20px;
  max-width: 300px;
  transition: transform 0.2s;
}

.card:hover {
  transform: translateY(-4px);
}

.title {
  margin: 0 0 8px;
  color: #222;
}

.text {
  margin: 0;
  color: #666;
}
```

`src/Card.jsx`:

```jsx
import styles from "./Card.module.css";

function Card({ title, text }) {
  return (
    <div className={styles.card}>
      <h2 className={styles.title}>{title}</h2>
      <p className={styles.text}>{text}</p>
    </div>
  );
}

export default Card;
```

`src/App.jsx`:

```jsx
import Card from "./Card";

function App() {
  return (
    <div style={{ display: "flex", gap: 16, padding: 20 }}>
      <Card title="Learn React" text="Components, props and state." />
      <Card title="Learn CSS" text="Layout, colors and spacing." />
    </div>
  );
}

export default App;
```

**Challenges:**
- Add a `variant` prop (`light` / `dark`).
- Make the layout responsive with Grid.
- Add a "like" button that changes color using state.

---

## 9. Responsive Design (Media Queries)

```css
.container {
  padding: 16px;
}

@media (min-width: 768px) {
  .container {
    padding: 32px;
    max-width: 960px;
    margin: 0 auto;
  }
}
```

Media queries work in plain CSS and CSS Modules, **not** in inline styles.

Don't forget in `index.html`:

```html
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
```

---

## 10. CSS Variables (Theming)

`src/index.css`:

```css
:root {
  --primary: royalblue;
  --text: #222;
  --radius: 8px;
}

[data-theme="dark"] {
  --primary: skyblue;
  --text: #eee;
}
```

Use anywhere:

```css
.button {
  background: var(--primary);
  border-radius: var(--radius);
}
```

Toggle a theme from React:

```jsx
document.documentElement.setAttribute("data-theme", "dark");
```

---

## 11. Method 4: Tailwind CSS (Quick Intro)

Tailwind provides small utility classes that you combine in `className`.

```jsx
function Button() {
  return (
    <button className="bg-blue-600 text-white px-4 py-2 rounded hover:bg-blue-800">
      Click me
    </button>
  );
}
```

Pros: fast, no separate CSS files, consistent design.
Cons: long class lists, a learning curve for class names.

Setup instructions change between versions, so follow the official guide for Vite: https://tailwindcss.com/docs/installation

---

## 12. Method 5: styled-components (Quick Intro)

```bash
npm install styled-components
```

```jsx
import styled from "styled-components";

const Button = styled.button`
  background: ${(props) => (props.$primary ? "royalblue" : "gray")};
  color: white;
  padding: 10px 20px;
  border: none;
  border-radius: 6px;
`;

function App() {
  return <Button $primary>Click</Button>;
}
```

Styles live next to the component and can react to props.

---

## 13. Which Should I Choose?

- **Learning / small project:** plain CSS or CSS Modules.
- **Real-world app, many components:** CSS Modules or Tailwind.
- **Highly dynamic, theme-heavy UI:** CSS variables, or styled-components.
- **Single dynamic value (width, color from data):** inline style.

You can mix methods. Common combo: global CSS for resets/variables + CSS Modules for components.

---

## 14. Common Beginner Mistakes

- Using `class` instead of `className`.
- Writing `style="color: red"` (a string) instead of `style={{ color: "red" }}`.
- Using `background-color` in a style object instead of `backgroundColor`.
- Forgetting `.module.css` in the filename, so `styles` is empty or undefined.
- Importing a global CSS file in many components and expecting it to be scoped.
- Trying `:hover` or `@media` inside inline styles.
- Forgetting units: `width: "100"` is invalid, use `"100px"` or `100`.

---

## 15. Cheat Sheet

| Task | Syntax |
|---|---|
| Add class | `<div className="box">` |
| Inline style | `<div style={{ color: "red" }}>` |
| CSS Module | `import s from "./X.module.css"` → `className={s.box}` |
| Multiple classes | `` className={`${s.a} ${s.b}`} `` |
| Conditional class | `className={on ? s.on : s.off}` |
| CSS variable | `color: var(--primary);` |
| Flex row | `display: flex; gap: 16px;` |
| Grid | `display: grid; grid-template-columns: repeat(3, 1fr);` |

---

## 16. Next Steps

1. Learn CSS layout deeply: Flexbox and Grid.
2. Try Tailwind CSS in a small project.
3. Add animations (`transition`, `@keyframes`) and Framer Motion.
4. Explore component libraries: MUI, Chakra UI, shadcn/ui.
5. Learn accessibility: color contrast, focus styles, `prefers-reduced-motion`.

## Resources
- React docs on styling: https://react.dev/learn#adding-styles
- MDN CSS: https://developer.mozilla.org/docs/Learn/CSS
- CSS Tricks Flexbox guide: https://css-tricks.com/snippets/css/a-guide-to-flexbox/
- CSS Tricks Grid guide: https://css-tricks.com/snippets/css/complete-guide-grid/

---

## Zettelkasten Links
- Parent: [[Frontend Development]]
- Prerequisite: [[React Beginner Tutorial]]
- Related: [[CSS Basics]], [[CSS Flexbox]], [[CSS Grid]], [[Tailwind CSS]]
- Next: [[React Component Libraries]], [[CSS Animations]]

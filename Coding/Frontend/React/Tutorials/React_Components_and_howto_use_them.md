---
id: 20261118153935
title: React Components
author: Karl Schmitt
date: 2026-11-18
---


# React Components

In React, **components** are independent, reusable building blocks that make up a user interface (UI). Think of a component as a custom HTML tag—such as `<Navbar/>`, `<Sidebar/>`, or `<ProductCard/>`—that encapsulates its own structure (JSX), styling, and logic.

Instead of building one giant web page, React encourages you to break your GUI down into small, self-contained pieces and compose them together like Lego bricks.

### Anatomy of a React Component

In modern React, components are standard JavaScript functions that follow two strict rules:

1. **Capitalized Name:** Component function names must always start with a capital letter (e.g., `Header`, not `header`) so React can distinguish them from standard HTML tags (`<div>`, `<p>`).


2. **Returns JSX:** The function returns **JSX** (JavaScript XML), an HTML-like syntax that describes what should appear on the screen.

```JavaScript
// A basic functional component
function ActionButton() {
  return <button className="primary-btn">Click Me</button>;
}
```

### How to Build a Web GUI Using Components

Building a graphical user interface in React follows a predictable, four-step architectural workflow:

#### 1. Decompose the UI into a Component Tree

Before writing code, look at your UI design and draw boxes around distinct visual sections. This creates a hierarchy (a **Component Tree**):



* `App` (Root container)



  * `Navbar` (Top navigation bar)



  * `MainContent` (Body area)



    * `UserCard` (Reusable profile widget)


    * `UserCard`



  * `Footer` (Bottom copyright/links)



#### 2. Build Individual Leaf Components

Start from the smallest, bottom-level components (the "leaves" of the tree). Keep each component focused on a single job.

``` JavaScript
// UserCard.jsx
function UserCard({ name, role }) {
  return (
    <div style={{ border: "1px solid #ccc", padding: "12px", margin: "8px" }}>
      <h3>{name}</h3>
      <p>{role}</p>
    </div>
  );
}

export default UserCard;
```

#### 3. Compose Components Together

Import your smaller components into parent layout components and assemble them. You can reuse the same component multiple times with different **props**.

``` JavaScript
// App.jsx
import UserCard from "./UserCard";

function Navbar() {
  return <nav style={{ background: "#222", color: "#fff", padding: "10px" }}>Team Dashboard</nav>;
}

function App() {
  return (
    <div>
      <Navbar />
      <main>
        <h2>Engineering Team</h2>
        {/* Reusing the same component with different data */}
        <UserCard name="Alice" role="Systems Architect" />
        <UserCard name="Bob" role="Frontend Developer" />
      </main>
    </div>
  );
}

export default App;
```

#### 4. Mount the Root Component to the DOM

Finally, React injects your top-level `<App/>` component into a single `<div id="root"></div>` inside your `index.html` file. React takes over from there, efficiently updating the browser's DOM whenever your data changes.



### Why This Approach Works Well for GUIs

* **Isolation:** Fixing a bug or changing the layout inside `UserCard.jsx` won't accidentally break your `Navbar`.


* **Reusability:** Write a modal, button, or data table once and drop it anywhere in your application.


* **Maintainability:** State and event handlers (like `onClick`) live right next to the markup they control.




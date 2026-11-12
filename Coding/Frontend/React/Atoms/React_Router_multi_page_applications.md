---
id: 20261112181143
title: React Router Multi-Page Applications
author: Karl Schmitt
date: 2026-11-12
keywords: [ React, React Router ]
---

# React Router Multi-Page Applications

Because React apps are **Single-Page Applications (SPAs)**—meaning the browser loads a single HTML page and dynamically swaps out content—they don’t natively have traditional multi-page navigation (like clicking a link that triggers a full browser reload).

Instead, React uses **React Router** (specifically the `react-router-dom` library) to handle **client-side routing**. This lets users navigate between different "pages" instantly without the browser ever reloading, giving a smooth, app-like experience.

### Core Concepts of React Router

* **`<BrowserRouter>`:** The wrapper component that listens to the browser's URL and keeps your UI in sync with it. It should wrap your entire application.

* **`<Routes>` and `<Route>`:** The mapping system. `<Routes>` acts like a switch statement, looking through its child `<Route>` elements to render whichever component matches the current URL path.

* **`<Link>` (or `<NavLink>`):** The replacement for standard HTML `<a>` tags. Using `<Link>` prevents the browser from refreshing and instead updates the URL and view seamlessly via JavaScript.

### Practical Example: A Multi-Page App

Here is how you set up a basic router with three pages: **Home**, **About**, and **Contact**.

First, make sure you have the library installed (`npm install react-router-dom`), then structure your code like this:

```JavaScript
import React from 'react';
import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';

// 1. Define your individual "page" components
function Home() {
  return <h2>🏠 Welcome to the Home Page!</h2>;
}

function About() {
  return <h2>📖 Learn more About Us here.</h2>;
}

function Contact() {
  return <h2>📞 Get in touch through our Contact page.</h2>;
}

// 2. Main App component handling the routing structure
function App() {
  return (
    <BrowserRouter>
      {/* Navigation bar that stays visible across all pages */}
      <nav style={{ padding: '15px', background: '#f8f9fa', borderBottom: '1px solid #ddd' }}>
        <Link to="/" style={{ marginRight: '20px', textDecoration: 'none', color: '#007bff' }}>Home</Link>
        <Link to="/about" style={{ marginRight: '20px', textDecoration: 'none', color: '#007bff' }}>About</Link>
        <Link to="/contact" style={{ textDecoration: 'none', color: '#007bff' }}>Contact</Link>
      </nav>

      {/* Content area where matching routes will render */}
      <div style={{ padding: '20px', fontFamily: 'sans-serif' }}>
        <Routes>
          <Route path="/" element={<Home />} />
          <Route path="/about" element={<About />} />
          <Route path="/contact" element={<Contact />} />
        </Routes>
      </div>
    </BrowserRouter>
  );
}

export default App;
```

### Why Client-Side Routing is Powerful?

1. **Blazing Fast Transitions:** Because the server isn't fetched anew for every click, page changes happen in milliseconds.

2. **State Preservation:** Global states (like a logged-in user or shopping cart items) aren't wiped out by page reloads.

3. **Dynamic Routes:** You can easily pass parameters in the URL (e.g., `/products/:id`) to display specific content, like an individual user profile or item details page.

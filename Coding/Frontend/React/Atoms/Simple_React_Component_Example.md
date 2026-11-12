---
id: 20261112175317
title: Simple React Component Example
author: Karl Schmitt
date: 2026-11-12
---

# Simple React Component Example

Here is a complete, simple example of a React functional component. We will build a **Counter** component that demonstrates both **Props** and **State** in action.

### The Code Example

```JavaScript
import React, { useState } from 'react';

// 1. The Component accepting a `title` prop
function Counter({ title }) {
  // 2. State hook to keep track of the current count
  // `count` is the current value, `setCount` is the function to update it
  const [count, setCount] = useState(0);

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif', border: '1px solid #ccc', borderRadius: '8px' }}>
      <h2>{title}</h2>
      <p>Current Count: <strong>{count}</strong></p>
      
      {/* 3. Event handler updating state */}
      <button onClick={() => setCount(count + 1)} style={{ marginRight: '8px' }}>
        Increment
      </button>
      <button onClick={() => setCount(0)}>
        Reset
      </button>
    </div>
  );
}

export default Counter;
```

### Key Concepts Breakdown

* **Props (Short for Properties):**

  * Props are passed _down_ from a parent component into a child component, acting like function arguments.

  * In our code, `{ title }` is a prop. If you render `<Counter title="My Awesome Counter"/>`, the component receives that title dynamically and displays it. Props are **read-only** (immutable) for the receiving component.

* **State (`useState`):**

  * State is data managed _inside_ the component that can change over time (e.g., user input, toggle states, or a counter number).

  * We use the `useState(0)` hook to initialize our count at `0`. Whenever `setCount()` is called, React automatically re-runs the component function and updates the user interface to reflect the new number.


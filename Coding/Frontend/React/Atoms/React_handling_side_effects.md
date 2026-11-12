---
id: 20261112180243
title: React Handling Side Effects
author: Karl Schmitt
date: 2026-11-1218
keywords: [ React, useEffect ]
---

# React Handling Side Effects

The **`useEffect`** hook is React's tool for handling **side effects** in functional components.

In React, rendering a component should ideally be a pure calculation—taking props and state and returning JSX. However, real-world apps need to interact with the outside world. Tasks like fetching data from an API, setting up timers (`setTimeout` or `setInterval`), subscribing to web sockets, or manually modifying the DOM are called **side effects** because they happen outside the normal rendering cycle.

### Anatomy of `useEffect`

`useEffect` takes two arguments:

1. **A callback function:** Contains the code for the side effect you want to run.

2. **A dependency array (optional):** Controls _when_ that effect runs relative to component renders.

```JavaScript
useEffect(() => {
  // Side effect code goes here (e.g., API call)
  
  return () => {
    // Optional cleanup code (e.g., cancel subscriptions or timers)
  };
}, [dependency1, dependency2]);
```

### Practical Example: Fetching Data from an API

Here is a component that fetches user data from a public API when it first loads on the screen:

```JavaScript
import React, { useState, useEffect } from 'react';

function UserProfile() {
  const [user, setUser] = useState(null);
  const [loading, setLoading] = useState(true);

  // useEffect handles the data fetching side effect
  useEffect(() => {
    fetch('https://jsonplaceholder.typicode.com/users/1')
      .then((response) => response.json())
      .then((data) => {
        setUser(data);
        setLoading(false); // Stop loading once data arrives
      })
      .catch((error) => {
        console.error('Error fetching data:', error);
        setLoading(false);
      });
  }, []); // Empty array [] means: run this ONLY ONCE when the component mounts

  if (loading) {
    return <p>Loading user data...</p>;
  }

  return (
    <div style={{ padding: '20px', fontFamily: 'sans-serif', border: '1px solid #ccc', borderRadius: '8px' }}>
      <h3>{user.name}</h3>
      <p>Email: {user.email}</p>
      <p>City: {user.address.city}</p>
    </div>
  );
}

export default UserProfile;
```

### How the Dependency Array Works

The second argument (the array) determines how often your effect runs:

* **No dependency array (`useEffect(() => { ... })`):** Runs after **every single render** (often causes infinite loops if you update state inside it—be careful!).

* **Empty array (`useEffect(() => { ... }, [])`):** Runs **only once** when the component first appears on the screen (mounts). Ideal for initial API fetches.

* **Array with variables (`useEffect(() => { ... }, [userId])`):** Runs on mount, and **every time** any variable inside the array changes its value.

Want to learn how React Router works for building multi-page applications?

Ja

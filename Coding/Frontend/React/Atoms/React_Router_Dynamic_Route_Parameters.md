---
id: 20261112182222
title: React Router Dynamic Route Parameters
author: Karl Schmitt
date: 2026-11-12
keywords: [ React, React Router ]
---

# React Router Dynamic Route Parameters

Handling **dynamic route parameters** allows your application to use the same component template for multiple different items (like loading a specific user profile, product details, or blog post) based on a variable in the URL (e.g., `/users/1`, `/users/2`).

In React Router, this is accomplished using a colon (`:`) in the route path and extracting that variable using the **`useParams`** hook.

### Core Concepts

1. **Dynamic Path Segment (`:paramName`):** When defining your `<Route>`, you prefix a dynamic segment with a colon. For example, `path="/users/:id"` tells React Router that anything after `/users/` should be captured as a variable named `id`.

2. **The `useParams()` Hook:** Inside your component, you call `const params = useParams();` to retrieve an object containing all dynamic parameters defined in the route.

### Practical Example: User Directory with Dynamic Profiles

Here is a complete example showing a user list that links to dynamic user profile pages using React Router:

```JavaScript
import React from 'react';
import { BrowserRouter, Routes, Route, Link, useParams } from 'react-router-dom';

// 1. Mock database of users
const usersData = [
  { id: '1', name: 'Alice Johnson', role: 'Frontend Developer', email: 'alice@example.com' },
  { id: '2', name: 'Bob Smith', role: 'Backend Engineer', email: 'bob@example.com' },
  { id: '3', name: 'Charlie Brown', role: 'UI/UX Designer', email: 'charlie@example.com' }
];

// 2. Component that lists all users
function UserList() {
  return (
    <div>
      <h2>User Directory</h2>
      <p>Click a user to view their dynamic profile page:</p>
      <ul>
        {usersData.map((user) => (
          <li key={user.id} style={{ margin: '8px 0' }}>
            {/* Dynamic link pointing to /users/1, /users/2, etc. */}
            <Link to={`/users/${user.id}`} style={{ color: '#007bff', textDecoration: 'none' }}>
              {user.name}
            </Link>
          </li>
        ))}
      </ul>
    </div>
  );
}

// 3. Component that renders the individual user profile dynamically
function UserDetail() {
  // `useParams` grabs the `:id` value from the current URL
  const { id } = useParams();

  // Find the specific user from our data array using the ID
  const user = usersData.find((u) => u.id === id);

  if (!user) {
    return (
      <div>
        <h3>User not found!</h3>
        <Link to="/">← Back to Directory</Link>
      </div>
    );
  }

  return (
    <div style={{ padding: '20px', border: '1px solid #ccc', borderRadius: '8px', maxWidth: '400px' }}>
      <h3>{user.name}'s Profile</h3>
      <p><strong>User ID:</strong> {id}</p>
      <p><strong>Role:</strong> {user.role}</p>
      <p><strong>Email:</strong> {user.email}</p>
      <br />
      <Link to="/" style={{ color: '#007bff', textDecoration: 'none' }}>← Back to Directory</Link>
    </div>
  );
}

// 4. Main App wrapping routes
function App() {
  return (
    <BrowserRouter>
      <div style={{ padding: '20px', fontFamily: 'sans-serif' }}>
        <Routes>
          {/* Default home route showing the user list */}
          <Route path="/" element={<UserList />} />
          
          {/* Dynamic route where `:id` acts as a placeholder variable */}
          <Route path="/users/:id" element={<UserDetail />} />
        </Routes>
      </div>
    </BrowserRouter>
  );
}

export default App;
```

### How It Works Behind the Scenes

1. When a user clicks a link pointing to `/users/2`, React Router matches that URL against `path="/users/:id"`.

2. It captures the value `2` and stores it under the variable name `id`.

3. The `UserDetail` component mounts, invokes `useParams()`, extracts `{ id: '2' }`, and uses that ID to look up Bob Smith's information from the dataset.

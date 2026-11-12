---
id: 20261112174338
title: React
author: Karl Schmitt
date: 2026-11-12
keywords: [ React, JSX ]
---

![React Logo](../Images/react-logo-dark.png)

# React

**React.js** (commonly called **React**) is an open-source JavaScript library developed and maintained by Meta (formerly Facebook). It is used primarily for building dynamic, high-performance **user interfaces (UIs)** for single-page web and mobile applications.

Instead of manipulating the browser's Document Object Model (DOM) directly—which can be slow and resource-intensive—React relies on a powerful set of architectural concepts:

### Core Concepts

* **Component-Based Architecture:** The UI is broken down into independent, reusable pieces called **components** (e.g., a button, a navigation bar, or a user profile card). Each component manages its own state and logic, making large codebases easier to maintain and scale.


* **The Virtual DOM:** React maintains a lightweight, in-memory representation of the real DOM. When data changes, React updates the Virtual DOM first, calculates the exact mathematical difference (called _reconciliation_ or _diffing_), and updates _only_ the changed parts of the real DOM. This results in blazing-fast rendering speeds.


* **JSX (JavaScript XML):** React uses JSX, a syntax extension that allows developers to write HTML-like markup directly inside JavaScript files. This keeps the structure and logic of a UI element closely coupled.


* **Unidirectional Data Flow:** Data in React flows downward from parent components to child components. This predictable flow makes debugging simpler because you always know where your data is coming from.

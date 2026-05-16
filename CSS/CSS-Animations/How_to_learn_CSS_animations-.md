---
id: 20260512075042
title: How to learn CSS animations?
author: Karl Schmitt
date: 2026-05-12
keyworts: [ CSS, animation ]
---

# How to learn CSS animation?

This tutorial will take you from "instant jumps" to smooth, professional UI movements.

### What is a CSS Transition?

A transition allows you to change a property value **smoothly** over a given duration, rather than having it happen instantly.

**The Golden Rule:** For a transition to work, you need:
1.  A starting state (e.g., `.box`)
2.  An ending state (e.g., `.box:hover`)
3.  The `transition` property defined on the **starting state**.

---

### 1. The Four Properties
There are four components to every transition:

1.  **`transition-property`**: The name of the CSS property you want to animate (e.g., `background-color`, `width`, `transform`).
2.  **`transition-duration`**: How long the change takes (e.g., `0.3s` or `500ms`).
3.  **`transition-timing-function`**: The "speed curve" (e.g., `ease`, `linear`, `ease-in-out`).
4.  **`transition-delay`**: How long to wait before starting the change.

---

### 2. Basic Example: The Color Change

Let's make a button that changes color smoothly when hovered.

**HTML:**
```html
<button class="cool-button">Hover Me</button>
```

**CSS:**
```css
.cool-button {
  background-color: #3498db;
  color: white;
  padding: 15px 30px;
  border: none;
  cursor: pointer;

  /* 1. Tell it WHAT to watch, 2. How LONG to take */
  transition-property: background-color;
  transition-duration: 0.5s;
}

/* The "End State" */
.cool-button:hover {
  background-color: #2ecc71;
}
```

---

### 3. The Shorthand (The Pro Way)
You rarely see developers write out all four lines. Instead, we use the shorthand:
`transition: [property] [duration] [timing-function] [delay];`

**Example:**
```css
/* Apply to all animatable properties, take 0.3s, start smoothly */
transition: all 0.3s ease;

/* Only transition the transform, wait 0.1s before starting */
transition: transform 0.4s ease-in-out 0.1s;
```

---

### 4. Animating Multiple Properties
You can transition two different properties with different speeds by separating them with a comma.

```css
.card {
  background: white;
  transform: scale(1);
  /* Change background fast, but scale slow */
  transition: background 0.2s, transform 0.8s;
}

.card:hover {
  background: #f0f0f0;
  transform: scale(1.1);
}
```

---

### 5. Timing Functions (The "Feel")
The `timing-function` determines how the animation flows.
*   **`linear`**: Same speed from start to finish (looks robotic).
*   **`ease-in`**: Starts slow, ends fast.
*   **`ease-out`**: Starts fast, ends slow (looks more natural for UI).
*   **`ease-in-out`**: Slow start, fast middle, slow end.
*   **`cubic-bezier(n,n,n,n)`**: Allows you to create custom "bouncy" or "snappy" effects.

---

### 6. The Common Beginner Mistake
**The Mistake:** Putting the transition on the `:hover` state.
```css
/* WRONG */
.box { background: red; }
.box:hover { 
  background: blue; 
  transition: 0.3s; /* This will only animate when you mouse IN, not mouse OUT */
}
```
**The Fix:** Always put the transition on the **base class** so the animation works in both directions (entering and leaving).

---

### 7. Performance Checklist
Not all properties are created equal.
*   **Fast (Use these!):** `transform` (scale, rotate, translate) and `opacity`. These use the computer's GPU and stay at 60fps.
*   **Slow (Avoid if possible):** `width`, `height`, `top`, `left`, `margin`. These force the browser to recalculate the layout of the whole page, which can cause lag.

---

### Practice Exercise: The "Lifting Card"
Try to build this. It combines a shadow change and a movement change.

```css
.card {
  width: 200px;
  height: 250px;
  background: white;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0,0,0,0.1);
  
  /* Transition both the shadow and the transform */
  transition: transform 0.3s ease, box-shadow 0.3s ease;
}

.card:hover {
  /* Move it up slightly */
  transform: translateY(-10px);
  /* Make the shadow deeper to look like it's "lifting" */
  box-shadow: 0 15px 30px rgba(0,0,0,0.2);
}
```

### Summary Table
| Goal | Property |
| :--- | :--- |
| **What** is changing? | `transition-property` |
| **How long** is it? | `transition-duration` |
| **What rhythm** does it have? | `transition-timing-function` |
| **When** does it start? | `transition-delay` |
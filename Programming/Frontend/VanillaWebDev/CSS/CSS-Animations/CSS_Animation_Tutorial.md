---
id: 20260512073924
title: CSS Animation Tutorial
author: Karl Schmitt
date: 2026-05-12
keywords: [ CSS, animation, tutorial ]
---

# CSS Animation Tutorial

# 🎬 CSS Animation Tutorial

This tutorial teaches CSS animations from beginner to intermediate level with practical examples you can run directly in the browser.

You will learn:

1. CSS transitions
2. CSS transforms
3. `@keyframes`
4. Timing functions
5. Real animation examples
6. Performance tips
7. Mini projects

---

# 🧱 1. Understanding CSS Animation

CSS animation means:

> Changing CSS values smoothly over time.

There are two main systems:

| System                     | Best For                  |
| -------------------------- | ------------------------- |
| `transition`               | Simple state changes      |
| `animation` + `@keyframes` | Complex multi-step motion |

---

# ✨ 2. CSS Transitions

Transitions animate between two states.

---

## Example 1 — Simple Hover Button

## HTML

```html
<button class="btn">Hover Me</button>
```

## CSS

```css
.btn {
  background: royalblue;
  color: white;
  border: none;
  padding: 12px 24px;
  font-size: 18px;
  border-radius: 8px;

  transition: background 0.3s ease;
}

.btn:hover {
  background: darkblue;
}
```

---

## What Happens?

Without transition:

* instant color change

With transition:

* smooth animated change

---

# 🧠 Transition Syntax

```css
transition: property duration timing-function delay;
```

Example:

```css
transition: all 0.5s ease;
```

---

# 🎯 Common Transition Properties

| Property      | Example           |
| ------------- | ----------------- |
| background    | color fades       |
| opacity       | fade in/out       |
| transform     | movement/rotation |
| box-shadow    | glowing effects   |
| border-radius | morphing          |

---

# 🚀 3. CSS Transform

Transforms move or reshape elements.

---

# Translate (Move)

```css
transform: translateX(50px);
```

Move vertically:

```css
transform: translateY(-20px);
```

---

# Scale

```css
transform: scale(1.2);
```

Makes the element 20% larger.

---

# Rotate

```css
transform: rotate(45deg);
```

---

# Combine Transforms

```css
transform: translateY(-10px) rotate(5deg) scale(1.1);
```

---

# 🎨 Example 2 — Animated Card Hover

## HTML

```html
<div class="card">
  Hover Me
</div>
```

## CSS

```css
.card {
  width: 200px;
  padding: 40px;
  background: white;
  border-radius: 16px;
  box-shadow: 0 5px 20px rgba(0,0,0,0.2);

  transition: all 0.3s ease;
}

.card:hover {
  transform: translateY(-10px);
  box-shadow: 0 15px 40px rgba(0,0,0,0.3);
}
```

---

# 🔥 4. Keyframe Animations

Transitions only animate between two states.

Keyframes allow:

* multiple stages
* loops
* complex movement

---

# Basic Structure

```css
@keyframes animation-name {

  0% {
  }

  50% {
  }

  100% {
  }

}
```

---

# 🏀 Example 3 — Bouncing Ball

## HTML

```html
<div class="ball"></div>
```

## CSS

```css
.ball {
  width: 100px;
  height: 100px;
  background: crimson;
  border-radius: 50%;

  animation: bounce 1s infinite;
}

@keyframes bounce {

  0% {
    transform: translateY(0);
  }

  50% {
    transform: translateY(-120px);
  }

  100% {
    transform: translateY(0);
  }

}
```

---

# 🧠 Animation Property Breakdown

```css
animation: bounce 1s infinite;
```

Means:

| Part     | Meaning       |
| -------- | ------------- |
| bounce   | keyframe name |
| 1s       | duration      |
| infinite | loop forever  |

---

# Full Animation Syntax

```css
animation:
  name
  duration
  timing-function
  delay
  iteration-count
  direction
  fill-mode;
```

---

# ✨ Example

```css
animation: slideIn 1s ease 0s infinite alternate;
```

---

# 🎯 5. Timing Functions

Timing functions control motion feel.

---

# Linear

```css
animation-timing-function: linear;
```

Constant speed.

---

# Ease

```css
animation-timing-function: ease;
```

Natural acceleration/deceleration.

---

# Ease-In

```css
animation-timing-function: ease-in;
```

Starts slowly.

---

# Ease-Out

```css
animation-timing-function: ease-out;
```

Ends slowly.

---

# Ease-In-Out

```css
animation-timing-function: ease-in-out;
```

Smooth start and end.

---

# 🌊 Example 4 — Pulse Animation

## HTML

```html
<div class="pulse"></div>
```

## CSS

```css
.pulse {
  width: 100px;
  height: 100px;
  background: hotpink;
  border-radius: 50%;

  animation: pulse 1.5s infinite;
}

@keyframes pulse {

  0% {
    transform: scale(1);
    opacity: 1;
  }

  50% {
    transform: scale(1.3);
    opacity: 0.5;
  }

  100% {
    transform: scale(1);
    opacity: 1;
  }

}
```

---

# 💨 6. Fade-In Animation

Very common in modern websites.

---

## CSS

```css
.fade-in {
  opacity: 0;
  transform: translateY(20px);

  animation: fadeIn 1s forwards;
}

@keyframes fadeIn {

  to {
    opacity: 1;
    transform: translateY(0);
  }

}
```

---

# 🧠 What Does `forwards` Mean?

```css
animation-fill-mode: forwards;
```

Keeps the final state after animation finishes.

---

# 🔄 7. Infinite Loading Spinner

---

## HTML

```html
<div class="spinner"></div>
```

## CSS

```css
.spinner {
  width: 80px;
  height: 80px;

  border: 8px solid lightgray;
  border-top: 8px solid royalblue;

  border-radius: 50%;

  animation: spin 1s linear infinite;
}

@keyframes spin {

  from {
    transform: rotate(0deg);
  }

  to {
    transform: rotate(360deg);
  }

}
```

---

# 🎮 8. Animation Delay

```css
animation-delay: 2s;
```

Waits before starting.

---

# 🔁 9. Alternate Direction

```css
animation-direction: alternate;
```

Instead of restarting:

* animation reverses direction

---

# ✨ Example

```css
animation: move 2s infinite alternate;
```

---

# 📦 10. Multiple Animations

You can combine animations.

```css
animation:
  fadeIn 1s ease,
  float 3s infinite;
```

---

# 🏎 11. Performance Tips

Best properties to animate:

| Good      | Bad      |
| --------- | -------- |
| transform | width    |
| opacity   | height   |
| translate | top/left |

---

# Why?

`transform` and `opacity`:

* use GPU acceleration
* are smoother
* reduce lag

---

# ❌ Avoid Animating

```css
width
height
top
left
margin
```

when possible.

---

# 🛠 12. Mini Project — Animated Navigation Link

## HTML

```html
<a href="#" class="nav-link">Home</a>
```

## CSS

```css
.nav-link {
  position: relative;
  text-decoration: none;
  color: black;
}

.nav-link::after {
  content: "";

  position: absolute;
  left: 0;
  bottom: -5px;

  width: 0;
  height: 2px;

  background: royalblue;

  transition: width 0.3s ease;
}

.nav-link:hover::after {
  width: 100%;
}
```

---

# 🎨 13. Mini Project — Floating Card

## CSS

```css
.card {
  animation: float 3s ease-in-out infinite;
}

@keyframes float {

  0% {
    transform: translateY(0);
  }

  50% {
    transform: translateY(-15px);
  }

  100% {
    transform: translateY(0);
  }

}
```

---

# 🧩 14. Transform Origin

Controls rotation center.

```css
transform-origin: center;
```

Examples:

```css
transform-origin: top left;
transform-origin: bottom center;
```

---

# 🎯 15. Cubic Bezier

Custom timing curves.

```css
transition:
  all 0.4s cubic-bezier(.17,.67,.83,.67);
```

Useful for:

* realistic motion
* advanced UI effects

---

# 🔬 16. Debugging Animations

## Slow Down Animation

```css
animation-duration: 10s;
```

This helps visualize movement.

---

# Use Browser DevTools

In:

* Chrome DevTools
* Firefox DevTools

You can inspect:

* keyframes
* timing
* transforms

---

# 🏗 17. Practice Projects

## Beginner

* hover buttons
* fade-in cards
* loading spinner
* pulsing dot

---

## Intermediate

* animated navbar
* dropdown menu
* toast notification
* modal animation

---

## Advanced

* CSS-only carousel
* animated dashboard
* parallax hero section
* CSS art

---

# 📚 Recommended Resources

## Documentation

* [MDN CSS Animations](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_animations?utm_source=chatgpt.com)
* [MDN CSS Transforms](https://developer.mozilla.org/en-US/docs/Web/CSS/transform?utm_source=chatgpt.com)
* [MDN CSS Transitions](https://developer.mozilla.org/en-US/docs/Web/CSS/CSS_transitions?utm_source=chatgpt.com)

---

## Inspiration

* [Animista](https://animista.net?utm_source=chatgpt.com)
* [CSS Tricks Animation Articles](https://css-tricks.com/tag/animation/?utm_source=chatgpt.com)
* [CodePen](https://codepen.io?utm_source=chatgpt.com)

---

# 🏁 Final Advice

The fastest way to master CSS animations:

1. Build tiny animations every day
2. Recreate effects from websites
3. Experiment constantly
4. Animate transforms + opacity first
5. Focus on subtle motion

Professional UI animation is usually:

* smooth
* simple
* intentional
* fast
* subtle

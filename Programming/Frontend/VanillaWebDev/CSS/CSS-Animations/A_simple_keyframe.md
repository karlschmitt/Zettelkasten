---
id: 20260514172505
title: A simple keyframe
author: Karl Schmitt
date: 2026-05-14
---

# A simple keyframe

```html
<!DOCTYPE html>
<html>
<head>
<style> 
div {
  width: 100px;
  height: 100px;
  background-color: red;
  animation-name: myAnimation;
  animation-duration: 4s;
}

@keyframes myAnimation {
  from {background-color: red;}
  to {background-color: yellow;}
}
</style>
</head>
<body>

<h1>CSS Animation</h1>

<div></div>

<p><b>Note:</b> When an animation is finished, it goes back to its original style.</p>

</body>
</html>
```
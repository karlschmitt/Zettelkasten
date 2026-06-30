---
id: 20260514173646
title: Rounded Box Example
author: Karl Schmitt
date: 2026-05-14
abstract: You can give any element “rounded corners” by applying a border-radius
---

[border-radius - CSS-Tricks](https://css-tricks.com/almanac/properties/b/border-radius/)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Rounded Box Example</title>
    <style>
        .rounded-box {
            /* 1. Core styling */
            background-color: #3498db;
            color: #ffffff;
            border-radius: 12px;
            
            /* 2. Sizing and spacing */
            width: 300px;
            padding: 20px;
            
            /* 3. Text layout */
            text-align: center;
            font-family: sans-serif;
            line-height: 1.5;
            
            /* 4. Optional aesthetics */
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }
    </style>
</head>
<body>

    <div class="rounded-box">
        This is a rounded box with text inside.
    </div>

</body>
</html>
```
Key Properties Used:

* **`border-radius`**: Controls the roundness of the corners. Higher values mean rounder corners.
* **`padding`**: Creates space between the text and the edges of the box.
* **`background-color`**: Fills the box so the shape and corners are visible.
* **`width`**: Defines the horizontal size of the box. 


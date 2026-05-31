---
id: 20260531110206
title: Arrow Tool
author: Karl Schmitt
date: 2026-05-31
---

# Arrow Tool

To add a sharp, professional red arrow in GIMP, you can use the built-in Arrow Tool script or draw it manually using the Paths Tool.

Here are the two best methods to create a perfect arrow pointing at your button.

## Method 1: Using the Arrow Script (Fastest & Perfect Shapes)

GIMP features a built-in Python script that generates perfect arrows instantly.

1. Set your color: Click your Foreground Color box and choose your bright red.
2. Select the Paths Tool: Press B on your keyboard to activate the Paths tool.
3. Draw a line: Click once where you want the tail of the arrow to start. Click a second time directly on the edge of your red button frame where the head of the arrow should point.
4. Create the arrow: Go to the top menu and select Tools > Arrow... (If you don't see it, go to Edit > Stroke Path instead, though the dedicated Arrow script is standard in recent versions).
5. Adjust the size: A popup window will appear. Set the Length of wings (arrowhead size) to about `20` or `30`, and the width to match your line.
6. Apply: Click OK. GIMP will automatically draw a perfect red arrow along the path you clicked.

## Method 2: Drawing a Thick Arrow Manually (Custom Style)

If you want a thick, bold block arrow, use a new transparent layer and shape it manually.

1. Create a new layer: Press `Shift + Ctrl + N`, name it "Arrow", set it to Transparency, and click OK.

2. Draw the line: Use the Paths Tool (B) to click a starting point and an ending point.

3. Thicken the line: Go to Edit > Stroke Path...

   * Choose Stroke line -> Solid color.
   * Set the Line width to a thick size (e.g., `8 px` or `10 px`).
   * Click Stroke.

4. Add the arrowhead: Switch to the Paintbrush Tool (P). Look at your Tool Options sidebar on the left:

   * Change the brush shape to "Block" or "Triangle" (GIMP has built-in arrowhead brushes).
   * Use the Size slider to make it look proportional to your line.
   * Click once right at the tip of your line to stamp the arrowhead.

If your arrow needs fine-tuning, let me know:

* Is the arrow straight or do you want it to be curved?
* Do you want the arrow to have a white outline so it stands out against dark backgrounds?
* Do you need to add text next to the arrow (like "Click Here")?


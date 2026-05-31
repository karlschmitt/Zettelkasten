---
id: 20260531105459
title: Highlight with a red frame
author: Karl Schmitt
date: 2026-05-31
keywords: [ gimp, frame ]
---

# Highlight a with a red frame

To highlight an important button with a red frame in GIMP, you need to use the Rectangle Select tool and apply a stroke effect to it.

Here is the quickest way to do this without ruining your original screenshot.

## The Best Method: Non-Destructive Framing

Creating the frame on a new layer allows you to move, resize, or delete the red frame later if you change your mind.

1. Create a new layer: Go to Layer > New Layer... (or press `Shift + Ctrl + N`). Name it "Red Frame", ensure Fill with is set to Transparency, and click OK.

2. Select the button: Choose the Rectangle Select Tool (press R). Click and drag a box around the button you want to highlight.

3. Choose your red color: Click the Foreground Color box (the top square on your toolbar), select a bright red, and click OK.

4. Draw the frame: Go to the top menu and select Edit > Stroke Selection...

5. Set the thickness: In the window that pops up:

   * Select Stroke line -> Solid color.
   * Set the Line width to your preferred thickness (around 3 to 5 px usually looks best for screenshots).

6. Apply: Click the Stroke button.

7. Remove the selection box: Go to Select > None (or press `Shift + Ctrl + A`) to see your clean red frame.

## Quick Adjustments

* Need to move it? Choose the Move Tool (press M), make sure "Move the active layer" is selected in tool options, and use your keyboard arrow keys to nudge the red frame perfectly into place.
* Want rounded corners? Before drawing your selection box (Step 2), look at the Tool Options on the left and check the box for Rounded corners. Adjust the radius slider to match the roundness of the button.

To make the highlight stand out even more, let me know if you would like to:

    * Add a red arrow pointing directly at the button.
* Make the rest of the screenshot slightly darker or blurred so the button pops.
* Add a shadow under the red frame to give it a 3D look.


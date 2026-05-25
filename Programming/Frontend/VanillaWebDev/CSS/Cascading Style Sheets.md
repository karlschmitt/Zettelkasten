---
id: 20260504075917
title: Cascading Style Sheets
author: Karl Schmitt
date: 2026-05-04
keywords: [ CSS ]
---

# Cascading Style Sheets

The name **Cascading Style Sheets** was chosen because of how the browser resolves conflicts when multiple rules apply to the same HTML element.

The word **"Cascading"** refers to the specific process of "falling down" through a hierarchy of rules to determine which style eventually "wins."

Here is the breakdown of why that name was necessary and how it works.

---

### 1. The Problem: Who is in charge?

When CSS was being invented in 1994 by **Håkon Wium Lie**, there was a debate about who should control how a website looks. There are three different parties involved:
1.  **The Browser (User-Agent):** Every browser has default styles (e.g., links are blue and underlined).
2.  **The User:** The person viewing the site might have custom settings (e.g., a person with low vision might set their default font size to 24px).
3.  **The Author:** The web developer who wrote the CSS for the website.

If the Browser says text should be black, but the Author says it should be red, and the User says it should be green—**who wins?** The "Cascade" is the set of rules that solves this fight.

---

### 2. The "Waterfall" Effect

Think of the Cascade like water flowing down a series of steps. 
The styles flow down from the top (the most general) to the bottom (the most specific). 
As the styles flow down, they can be overwritten by styles further down the stream.

The browser looks at three main factors to decide which style "wins" the cascade:

#### A. Importance (Origin)
The browser checks where the rule came from. Generally, the order of priority is:
1.  **Author (You):** Your CSS file.
2.  **User:** Settings changed by the person viewing the site.
3.  **User-Agent:** The browser’s default settings.

#### B. Specificity
If two rules come from the same source, the browser looks at how **specific** the selector is. A rule targeting a unique ID will "beat" a rule targeting a general tag.
*   `p { color: red; }` (General - 1 point)
*   `.highlight { color: blue; }` (More specific - 10 points)
*   `#main-header { color: green; }` (Very specific - 100 points)

#### C. Source Order (The Tie-Breaker)
If the importance is the same and the specificity is the same, the **last one written wins**. 
```css
p { color: blue; }
p { color: red; } /* This one wins because it is further down the "cascade" */
```

---

### 3. Inheritance (Passing styles down)
"Cascading" also refers to how styles are passed from a parent element to its children. 
If you set the font of the `<body>` tag to "Arial," every paragraph, list, and heading inside that body will also be "Arial." The style **cascades down** through the HTML structure until it hits a different rule.

### Summary
It is called **Cascading Style Sheets** because:
*   **Cascading:** It follows a hierarchy where rules "fall" through a filter of Importance, Specificity, and Order to resolve conflicts.
*   **Style:** It deals with the visual presentation.
*   **Sheets:** In the early days of publishing, "style sheets" were physical pieces of paper that designers used to specify how a document should look before it went to the printing press.


---
id: 20260428121642 
title: Server-Side Rendering
author: Karl Schmitt
date: 2026-04-28
keywords: [ Angular, SSR ]
---

# Server-Side Rendering

In the wake of the "Angular Renaissance," the framework's approach to Server-Side Rendering (SSR) has been completely overhauled. It is no longer an "add-on" (previously known as Angular Universal) but is now a **core, integrated part of the framework.**

Here is how Angular supports SSR, focusing on the modern implementation (Angular v17+):

---

### 1. The Core Mechanism: `@angular/ssr`
Previously, you had to install a separate package called "Angular Universal." Today, SSR is handled by the official `@angular/ssr` package. When you create a new project, the CLI asks if you want to enable SSR immediately:
```bash
ng new my-app --ssr
```
If you have an existing app, you simply run:
```bash
ng add @angular/ssr
```

### 2. From "Destructive" to "Hydration"
This is the biggest technical shift in how Angular supports SSR.
*   **The Old Way (Destructive):** The server would send HTML to the browser. As soon as the JavaScript loaded, Angular would **wipe out** that HTML and re-render the entire app from scratch. This caused a visible "flicker" and lost user input or scroll position.
*   **The New Way (Hydration):** Angular now uses **Non-Destructive Hydration**. The server sends the HTML, and the client-side Angular app "picks up" the existing DOM. It attaches event listeners and restores the application state without destroying or re-rendering the HTML nodes.

### 3. Event Replay (New in Angular v18)
One major issue with SSR is the "Uncanny Valley"—the period where the page *looks* ready (because of SSR) but isn't interactive yet (because JS is still loading).
*   **How Angular solves it:** Using a library called `event-dispatch` (originally from Google Search), Angular now **records** user events (like clicks) that happen before the app is hydrated. 
*   Once hydration is complete, Angular **replays** those events so the user’s action isn't lost.

### 4. Deferrable Views (`@defer`)
Angular supports SSR optimization through the `@defer` block. This allows developers to specify which parts of a page are "critical" and which are "lazy."
*   In an SSR context, you can tell Angular to render a placeholder on the server and only load/render the heavy component on the client when it enters the viewport.
*   This keeps the initial server-rendered HTML payload small and fast.

### 5. Transfer State
To prevent the "double data fetch" problem (where the server fetches data to render the HTML, and then the client fetches the exact same data again once it boots up), Angular uses **Transfer State**.
*   The server performs the API calls, serializes the result into a small `<script>` tag in the HTML, and the client reads the data from that tag instead of making a new HTTP request.

### 6. Edge Rendering and Pre-rendering
Angular's SSR support isn't limited to a traditional Node.js server:
*   **Static Site Generation (SSG):** During the build process, Angular can crawl your routes and generate static HTML files for every page (ideal for blogs or marketing sites).
*   **Edge Rendering:** The modern build system (using Vite/esbuild) makes Angular light enough to run on "The Edge" (like Cloudflare Workers or Vercel Edge Functions), putting the rendering logic physically closer to the user.

---

### Summary of Benefits
| Feature | Benefit |
| :--- | :--- |
| **SEO** | Search engines see the full content immediately, improving rankings. |
| **Performance** | Users see the "First Contentful Paint" (FCP) much faster, especially on slow mobile devices. |
| **Social Sharing** | Links shared on Twitter/iMessage/LinkedIn show rich previews (meta tags are rendered on the server). |
| **No Flicker** | Thanks to Hydration, the transition from server-HTML to interactive-JS is seamless. |

**In short:** Angular supports SSR by integrating it into the standard build pipeline, using hydration to ensure a smooth user experience, and providing tools like `@defer` and "Event Replay" to bridge the gap between static HTML and a fully interactive application.



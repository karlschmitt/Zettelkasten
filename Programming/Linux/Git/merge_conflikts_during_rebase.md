---
id: 20260520173545
title: Why there are merge conflicts during a rebase?
author: Karl Schmitt
date: 2026-05-20
keywords: [ git, rebase, merge, conflicts]
---

# Why there are merge conflicts during a rebase?

Conflicts occur during a rebase for the same fundamental reason they occur during a merge: **Git doesn't know how to automatically combine two different changes to the same part of a file.**

However, conflicts during a **rebase** feel different—and often more repetitive—because of *how* rebasing works under the hood.

Here is the breakdown of why they happen and why they can be tricky.

---

### 1. The "Commit-by-Commit" Nature

When you **merge**, Git looks at the tip of both branches and tries to combine them in **one single event**. If there is a conflict, you fix it once, and you're done.

When you **rebase**, Git does the following:
1. It "lifts" your commits off your branch and puts them in a temporary area.
2. It resets your branch to match the target branch (e.g., `main`).
3. It tries to **re-apply your commits one by one**, in order.

**The Conflict:** If Commit #1 on your branch changes Line 10 of `app.js`, but someone else already changed Line 10 on the `main` branch, Git will stop at Commit #1 and say: *"I can't apply this specific change because the foundation has changed."*

### 2. You are "Rewriting History"

Think of a rebase like a **series of mini-merges**. 
* Git applies your first commit. If there's a conflict, you fix it.
* Git applies your second commit. If that commit *also* touched the same area, you might have to fix a conflict **again**.

This is why rebasing a branch with 20 commits can sometimes feel like a marathon; you aren't just resolving the final state of the code, you are resolving the conflict for every step of your work's history.

### 3. Common Scenarios for Conflicts
*   **The Same Line was Modified:** You changed a variable name to `userCount`, but someone else changed it to `totalUsers` on the main branch. Git doesn't know which name is correct.
*   **File Deletion:** You modified a file in your branch, but someone else deleted that file on the main branch. Git doesn't know if it should keep your edits or delete the file.
*   **Contextual Changes:** Even if you didn't touch the exact same line, if you added code right next to where someone else added code, Git might get confused about the "context" and ask you to verify the order.

---

### 4. Why Rebase conflicts feel "backwards"

In a standard **Merge**, your branch is the "destination" and `main` is the "source."
In a **Rebase**, it’s the opposite:
*   **`ours` (the current branch):** During a rebase, this is actually the `main` branch (the new base).
*   **`theirs` (the incoming change):** During a rebase, this is **your** work (the commit being re-applied).

This often confuses people because your own changes are labeled as "theirs" in conflict markers.

---

### How to manage Rebase conflicts:
1.  **Check Status:** Use `git status` to see which file is broken.
2.  **Fix the file:** Open the editor, look for the `<<<<<<< HEAD` markers, and pick the code you want to keep.
3.  **Stage:** Use `git add <filename>`. (Note: **Do not** use `git commit`).
4.  **Continue:** Run `git rebase --continue`.
5.  **Repeat:** If you have multiple commits, Git will move to the next one and might ask you to do it again.

**Pro Tip:** If you find yourself resolving the same conflicts over and over, you can look into **`git rerere`** (Reuse Recorded Resolution). It tells Git to remember how you fixed a conflict and apply the same fix automatically if it sees it again during the rebase.
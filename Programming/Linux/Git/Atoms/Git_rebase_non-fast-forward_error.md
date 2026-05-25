---
id: 20260525144839
title: Git non-fast forward error 
author: Karl Schmitt
date: 2026-05-25
keywords: [ git, rebase, non-fast-forward ]
---

# Git non-fast forward error

In Git, a **"non-fast-forward" error** is a safety mechanism. It occurs when you try to `push` your changes to a remote server, but the remote server has commits that you do not have locally.

Git rejects the push because doing so would "overwrite" or lose the history on the server.

---

### 1. Fast-Forward vs. Non-Fast-Forward

#### What is a Fast-Forward?

A fast-forward is possible when your local branch is a **direct descendant** of the remote branch. 
*   Remote: `A --- B`
*   Local: `A --- B --- C --- D`
*   **Action:** When you push, Git just slides the pointer on the server from B to D. This is a "Fast-Forward."

#### What is a Non-Fast-Forward?

This happens when the paths have **diverged**.
*   Remote: `A --- B --- X` (Someone else pushed commit X)
*   Local: `A --- B --- C --- D` (You created C and D)
*   **Result:** Git cannot just "slide" the pointer to D, because commit **X** would be left behind/orphaned. This triggers the error.

🔗 [Diverged Path](./Git_rebase_diverged_path.md)

---

### 2. Why do you see this after a Rebase?

This is the most common reason developers see this error. **Rebase rewrites history.**

Even if no one else has pushed to the server, you will get a non-fast-forward error if you rebase commits that **already exist on the remote.**

**The Scenario:**
1. You push commit `C` to the server.
   * Remote: `A --- B --- C`
   * Local: `A --- B --- C`
2. You realize you made a mistake, so you **rebase** locally to "fixup" commit `C`.
3. Your local commit `C` is replaced by a new commit `C*` (same content, different hash).
   * Local: `A --- B --- C*`
4. You try to push. Git sees that your local branch and the remote branch have different commits (`C*` vs `C`).
5. **Error:** `! [rejected] main -> main (non-fast-forward)`

---

### 3. The Error Message
It usually looks like this in your terminal:
```text
To github.com:user/repo.git
 ! [rejected]        main -> main (non-fast-forward)
error: failed to push some refs to 'github.com:user/repo.git'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
```

---

### 4. How to Fix It

There are two main ways to resolve this, depending on the situation:

#### Method A: The "Safe" Way (Merge/Rebase Pull)

If the error happened because a teammate pushed new work, you need to bring their work into yours first.
*   **Command:** `git pull --rebase origin <branch_name>`
*   **What it does:** This fetches the remote changes, puts your local changes "on top" of them, and then allows you to push normally.

#### Method B: The "Force" Way (Common after a Rebase)

If you intentionally rewrote your history (e.g., via `rebase -i`) and you are the only one working on that branch, you must tell Git to ignore the safety check.
*   **Command:** `git push --force-with-lease`
*   **What it does:** It tells the server: "I know the histories have diverged; replace the server's history with mine."
*   **Why `--force-with-lease`?** It is safer than a standard `--force`. It will fail if someone else pushed new commits you haven't seen yet, preventing you from accidentally deleting a teammate's work.

### Summary

A **non-fast-forward** error means the remote branch has commits that your local branch lacks. Because Git prefers to **never lose data**, it prevents you from pushing until you either incorporate those remote commits (via pull/rebase) or explicitly tell Git to overwrite the remote history (via force push).
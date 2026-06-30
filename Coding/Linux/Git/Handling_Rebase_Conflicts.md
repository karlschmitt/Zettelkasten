---
id: 20260525121615
title: Handling Git rebase conflicts
author: Karl Schmitt
date: 2025-05-25
keywords: [ git, conflict ]
---

# Handling Git rebase conflicts 

>[!NOTE]
>Sometimes Git cannot automatically replay a commit.

You may see a CONFLICT:

```text
CONFLICT (content): Merge conflict in app.js
```
Merge conflicts occur during a rebase for the same reason they do during a merge: _two different commits changed the same line of code in the same file, and Git doesn't know which version to keep_. 

>[!IMPORTANT]
>However, rebase handles conflicts differently than a standard merge.

### 1. Sequential Application 

While a **merge** *combines* the final state of two branches at once, a **rebase** takes your commits and *reapplies* them one by one on top of the new base.

![Git rebase from main 002](./Images/Git_rebase_from_main_002.png)

* **Conflict Trigger**: If your first commit changes a line that was also changed in the "new base" (the target branch), Git pauses.
* **Repeating Conflicts**: You might have to resolve the same conflict multiple times if several of your commits touch that same line.

>[!NOTE]
>In a Git rebase, **Sequential Application** refers to the _step-by-step_ process where Git takes your individual commits and **"re-plays"** them one at a time onto the new base.

Instead of combining everything at once (like a merge), Git treats your work like a **movie reel**, _frame by frame_.

***

### How it Works

* Step 1: **Lifting**: Git identifies the commits unique to your branch and temporarily moves them to a "holding area."
* Step 2: **Resetting**: Your branch "teleports" to the latest commit of the target branch (e.g., `main`).
* Step 3: **Replaying**: Git takes the first commit you made, applies it to the new `main`, and creates a new commit ID. Then it takes the second, and so on.

### ⚓ The Importance of Sequence

* **Conflict Resolution**: If a conflict occurs, Git pauses at the specific commit that caused the problem. You fix it, then tell Git to `continue`.
* **Atomic History**: Because commits are applied one by one, the logical flow of your work is preserved, even though the "starting point" of your branch has changed.
* **New Identities**: Even if the code is the same, each re-applied commit gets a new SHA (ID) because its "parent" commit is now different.

***

### ⚠️ Potential Hurdles

* **Multiple Conflicts**: You might have to fix the same conflict multiple times if it exists across several of your sequential commits.
* **Squashing**: You can choose to "squash" these sequential commits into one single commit during the process to keep history even cleaner.

***

### 2. Rewriting History ✍️

Rebase technically "rewrites" history by creating brand-new commits with different IDs (hashes).

* Because Git is effectively "replay-ing" your work on a new foundation, it checks for compatibility at every single step.
* If you previously resolved a conflict in a merge, rebase may force you to do it again because it ignores that past merge resolution.

In Git, Rewriting History means _changing the record of how, when, or in what order commits were made_. When you rebase, you aren't just moving code; you are technically deleting old commits and creating brand-new ones.

***

#### Why it is considered "Rewriting" ℹ️

* New Parentage: A commit’s identity (SHA-1 hash) is partially based on the commit that came before it. By changing the "base" (the parent), the commit's identity changes.
* New IDs: Even if the code changes are identical, the Commit Hash (e.g., `a1b2c3d`) will be completely different after a rebase.
* Linearizing: It makes the history look like a straight line, hiding the fact that you were working on a separate branch for days.

#### 🛠️ What you can change

During a rebase (especially an interactive one), you can:

* Edit: Change the code within a specific past commit.
* Reword: Change a typo in an old commit message.
* Squash: Combine five small commits into one clean "feature" commit.
* Drop: Completely delete a commit you no longer want.

***

#### 🛑 The Golden Rule 🪙

> [!IMPORTANT]
> Never rewrite history on a public branch.

If you rebase a branch that others have already pulled to their computers:

* Their version of history will conflict with your "new" version.
* It causes massive "merge headaches" for the team.
* You will be forced to use `git push --force`, which can overwrite teammates' work.

***

![Safety Ring](./Images/Safety-Ring2.png)

If you need to move forward, see also:

* How to force push safely using `--force-with-lease`
* How to use interactive rebase (`git rebase -i`)
* What to do if you accidentally rewrote history on the wrong branch



### 3. Diverged Path ⚠️

Conflicts often happen when your branch has **"diverged"** significantly from the main branch.

>[!NOTE]
>If someone else changed a function name in `main` and you called that same function in your feature branch, [Git](https://github.com/) will flag this as a conflict during rebase.

A **Diverged Path** occurs when two versions of the same branch have different commit histories that are no longer compatible.

In the context of a rebase, this happens because you have rewritten history locally, while the original history still exists on the remote server (like GitHub).

#### Why it Happens

* Local Change: You rebase your `feature` branch. This creates new commits with new IDs.
* Remote Record: The remote server still has your old commits with the original IDs.
* The Conflict: Git looks at both and sees they started at the same point but traveled in different "directions." It can't figure out which one is the "truth" without help.

#### 🚩 How You’ll Know

> [!IMPORTANT]
> If you try to run a standard `git push` after a rebase, Git will reject it with an error like:

* `[rejected] feature -> feature (non-fast-forward)`
* `Updates were rejected because the tip of your current branch is behind its remote counterpart.`

#### 🛠️ How to Fix the Path

Since you intentionally changed the history, 
you have to tell the server to replace its old path with your new one:

* The "Hammer" 🔨: `git push --force` (Overwrites the remote branch entirely).
* The "Safety Valve" 🛟: `git push --force-with-lease` (Only overwrites if no one else has added new work to the remote branch). 

***

#### ⚠️ The Risk

If a teammate pulled your `feature` branch before you rebased, their local path is now "diverged" from the server. When they try to pull, they will get a mess of duplicate commits and merge conflicts. 

🔗 [Diverged Path](./Atoms/Git_rebase_diverged_path.md)

***

To help you clear this up, let me know:

* Are you seeing a "non-fast-forward" error right now?
* Are other people working on this same branch?
* Do you want the command to undo the rebase and go back to the old path?

***

#### 💡 Common Rebase Commands

If you hit a conflict, Git will pause and wait for you to:

* Fix the files: Open the file, keep the code you want, and remove conflict markers.
* `git add <file>`: Stage the fixed file.
* `git rebase --continue`: Move on to the next commit in your branch.
* `git rebase --abort`: Completely cancel the rebase and go back to how things were.

Would you like to know how to avoid these conflicts in the first place, or should we look at how to squash commits to make rebasing easier?


***
---
id: 20260523174750 
title: Git rebase conflict resolution
author: Karl Schmitt
date: 2026-05-23
keywords: [ git, rebase, conflict, resolution ]
---

# Git rebase conflict resolution

In a `git rebase`, conflict resolution is _the process of ==manually fixing== overlapping changes when Git cannot automatically merge a commit onto a new base_.

Unlike a standard merge (which happens once), a rebase applies your commits one by one. If multiple commits have conflicts, you may have to resolve them multiple times during a single rebase operation. \

## 🚩 Why it happens

* Overlapping edits: You and another developer changed the same line in the same file.
* Deleted files: You modified a file that the base branch deleted.
* Context shifts: The code around your changes moved or changed significantly.

***

## 🛠 The Resolution Process

1. Rebase Pauses: Git stops at the specific commit that caused the conflict.

2. Locate Markers: Git inserts "conflict markers" into your files:

   * `<<<<<<< HEAD`: The version currently on the branch you are rebasing onto.
   * `=======`: The divider between the two versions.
   * `>>>>>>> [Commit ID]`: Your changes that you are trying to apply. 

3. Manual Edit: You open the file, choose which code to keep (or write a hybrid), and remove the markers.

4. Stage & Resume: You tell Git the file is fixed and continue the process:

   * `git add <file>`
   * `git rebase --continue` 

***

## 💡 Key Differences from Merge

* Linear History: Rebase rewrites history to look like a straight line; merge creates a "knot" (merge commit).
* Commit by Commit: You resolve conflicts for each individual commit in your sequence, not just the final state.
* The "Head" Flip: During a rebase, `HEAD` refers to the upstream branch (the base), while your local changes are considered the "incoming" part.




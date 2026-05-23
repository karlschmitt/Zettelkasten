---
id: 20260523171747
title: What is a basic rebase?
author: Karl Schmitt
date: 2026-05-23
keywords: [ git, rebase ]
---

# What is a basic rebase?

In Git, a rebase is the process of moving or "replaying" a sequence of commits from one branch onto a new base commit.
Instead of combining two branches with a "merge commit," rebasing effectively rewrites your project history so it looks like you started your work from a more recent point in time.

![Git rebase from main](../Images/Git_rebase_from_main_002.png)

------------------------------
## 🛠️ How It Works

When you run git rebase <branch-name>, Git follows these steps: [2, 5] 

   1. Finds the common ancestor between your current branch and the target branch.
   2. Temporarily lifts your new commits and sets them aside.
   3. Resets your current branch to match the target branch's latest commit.
   4. Applies your lifted commits one by one on top of that new base.

------------------------------
## ⚖️ Rebase vs. Merge

The end goal is the same—integrating changes—but the history looks very different: 

| Feature | Git Merge | Git Rebase |
|---|---|---|
| History | Preserves original timeline and branch structure. | Creates a clean, linear, "straight-line" history. |
| Commits | Adds one new "merge commit" to join branches. | Rewrites existing commits with new IDs (hashes). |
| Conflicts | You resolve all conflicts once in the merge commit. | You resolve conflicts commit-by-commit as they are replayed. |

------------------------------
## ⚠️ The Golden Rule

Never rebase a branch that you have already pushed to a shared repository. 
Because rebasing rewrites commit IDs, it will confuse other developers who have already pulled your original commits. This can lead to a messy "duplicate commit" situation for your team.

------------------------------
## 💡 Common Use Cases

* Updating a Feature Branch: Use git rebase main to pull in the latest work from your team so your feature stays compatible with the newest code. 
* Cleaning History: Use interactive rebase (git rebase -i) to "squash" (combine) many small, messy commits into one polished commit before finishing a task. 
* Avoiding Clutter: Many teams prefer rebase because it eliminates "junk" merge commits (like "Merge branch 'main' into 'feature'"), making the git log much easier to read. 

If you'd like, I can show you the exact commands to run for a standard rebase or explain how to handle rebase conflicts. Which would be more helpful? 

1. [Git standard rebase](Git_standard_rebase.md)


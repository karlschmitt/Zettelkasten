---
id: 20260522204504 
title: Git Rebase Bootcamp
author: Karl Schmitt
date: 2026-05-22
---

# Git Rebase Bootcamp (7 Days)

This bootcamp takes you from:

* “What even is rebase?”
  to

* confidently cleaning up branches, rewriting history, and handling conflicts.

You’ll practice using real Git commands every day.

***

# What You Need

Install:

* [Git](https://git-scm.com/?utm_source=chatgpt.com)

* A code editor like [Visual Studio Code](https://code.visualstudio.com/?utm_source=chatgpt.com)

Check Git:

```bash
git --version
```

Create a playground folder:

```bash
mkdir git-rebase-bootcamp
cd git-rebase-bootcamp
git init
```

***

# Day 1 — Understanding Git History

## Goal

Learn:

* commits

* branches

* the commit graph

* why rebase exists

***

# Step 1 — Create Some History

```bash
echo "Hello" > app.txt
git add .
git commit -m "Initial commit"

echo "Feature A" >> app.txt
git commit -am "Add feature A"

echo "Feature B" >> app.txt
git commit -am "Add feature B"
```

***

# Step 2 — Visualize History

```bash
git log --oneline --graph
```

Example:

```text
* c3d4e5 Add feature B
* b2c3d4 Add feature A
* a1b2c3 Initial commit
```

Git history is a chain of commits.

***

# Step 3 — Create a Branch

```bash
git checkout -b feature/login
```

Add work:

```bash
echo "Login Form" >> app.txt
git commit -am "Add login form"
```

Switch back:

```bash
git checkout master
```

Add another commit:

```bash
echo "Hotfix" >> app.txt
git commit -am "Hotfix on master"
```

Now history diverged.

***

# Why Rebase Exists

Your branch started from an older commit.

Rebase lets you:

* replay your commits

* on top of newer commits

* creating a cleaner history

***

# Day 2 — Your First Rebase

## Goal

Understand basic rebasing.

***

# Before Rebase

View history:

```bash
git log --oneline --graph --all
```

You’ll see something like:

```text
* master: Hotfix
|
| * feature/login: Add login form
|/
* Add feature B
```

***

# Step 1 — Rebase Feature Branch

Switch to feature branch:

```bash
git checkout feature/login
```

Rebase onto master:

```bash
git rebase master
```

Git takes:

* your feature commits

* temporarily removes them

* moves branch to master

* reapplies commits

***

# After Rebase

```bash
git log --oneline --graph --all
```

Now history becomes linear:

```text
* Add login form
* Hotfix
* Add feature B
```

***

# Mental Model

Rebase = “Replay my work on top of another branch.”

***

# Day 3 — Merge vs Rebase

## Goal

Understand the difference.

***

# Merge

```bash
git checkout master
git merge feature/login
```

Creates a merge commit.

History:

```text
A---B---C
     \   \
      D---M
```

Pros:

* preserves exact history

* safer for teams

Cons:

* messy history

***

# Rebase

```bash
git checkout feature/login
git rebase master
```

History:

```text
A---B---C---D
```

Pros:

* clean linear history

* easier to read

Cons:

* rewrites history

***

# Golden Rule

Never rebase shared public history unless your team agrees.

***

# Day 4 — Handling Rebase Conflicts

## Goal

Learn conflict resolution.

***

# Create Conflict

On master:

```bash
git checkout master
```

Modify file:

```bash
echo "MASTER VERSION" > conflict.txt
git add .
git commit -m "Master change"
```

On feature branch:

```bash
git checkout -b feature/conflict
```

Modify same file differently:

```bash
echo "FEATURE VERSION" > conflict.txt
git add .
git commit -m "Feature change"
```

***

# Rebase

```bash
git rebase master
```

Git stops with conflict.

***

# Open File

You’ll see:

```text
<<<<<<< HEAD
MASTER VERSION
=======
FEATURE VERSION
>>>>>>> Feature change
```

***

# Resolve Conflict

Choose final content:

```text
MASTER VERSION
FEATURE VERSION
```

Then:

```bash
git add conflict.txt
git rebase --continue
```

***

# Useful Commands

Abort rebase:

```bash
git rebase --abort
```

Skip problematic commit:

```bash
git rebase --skip
```

***

# Day 5 — Interactive Rebase

## Goal

Rewrite commit history cleanly.

This is one of Git’s superpowers.

***

# Create Bad History

```bash
echo "1" >> notes.txt
git add .
git commit -m "WIP"

echo "2" >> notes.txt
git commit -am "Oops"

echo "3" >> notes.txt
git commit -am "Fix stuff"
```

Messy history.

***

# Start Interactive Rebase

```bash
git rebase -i HEAD~3
```

Git opens editor:

```text
pick abc123 WIP
pick def456 Oops
pick ghi789 Fix stuff
```

***

# Squash Commits

Change to:

```text
pick abc123 WIP
squash def456 Oops
squash ghi789 Fix stuff
```

Save and exit.

Now you get:

* one clean commit

* instead of three messy ones

***

# Reword Commit Messages

Change:

```text
pick
```

to:

```text
reword
```

Git lets you rename commit message.

***

# Day 6 — Advanced Rebase Techniques

## Goal

Use rebase professionally.

***

# Rebase Onto Another Branch

Example:

```bash
git rebase develop
```

Moves feature branch onto latest develop branch.

***

# Auto-Stash

If working tree is dirty:

```bash
git rebase --autostash master
```

Git temporarily saves changes.

***

# Preserve Merge Structure

```bash
git rebase --rebase-merges
```

Advanced but useful in large projects.

***

# Recover Mistakes with Reflog

Git secretly tracks everything.

```bash
git reflog
```

Example:

```text
a1b2c3 HEAD@{0}: rebase finished
d4e5f6 HEAD@{1}: commit: bad commit
```

Restore:

```bash
git reset --hard HEAD@{1}
```

Reflog saves lives.

***

# Day 7 — Real Workflow

## Goal

Use rebase like professional teams do.

***

# Typical Feature Workflow

## 1. Create Branch

```bash
git checkout -b feature/navbar
```

***

## 2. Work Normally

```bash
git commit -m "Add navbar component"
```

***

## 3. Update from Main Branch

```bash
git checkout master
git pull
```

***

## 4. Rebase Feature Branch

```bash
git checkout feature/navbar
git rebase master
```

***

## 5. Clean History

```bash
git rebase -i HEAD~5
```

Squash junk commits.

***

## 6. Push

If already pushed before:

```bash
git push --force-with-lease
```

Safer than:

```bash
git push --force
```

***

# Important Safety Rule

Prefer:

```bash
git push --force-with-lease
```

because it prevents overwriting teammates’ work accidentally.

***

# Essential Rebase Commands Cheat Sheet

## Start Rebase

```bash
git rebase master
```

***

## Interactive Rebase

```bash
git rebase -i HEAD~3
```

***

## Continue

```bash
git rebase --continue
```

***

## Abort

```bash
git rebase --abort
```

***

## Skip Commit

```bash
git rebase --skip
```

***

## Show History Graph

```bash
git log --oneline --graph --all
```

***

# Most Important Concepts

## Merge

* preserves real history

* creates merge commits

***

## Rebase

* rewrites history

* creates linear history

* cleaner commit graph

***

# When To Use Rebase

Good:

* updating feature branches

* cleaning commits before PR

* local branches

Avoid:

* rebasing shared public branches

***

# Practice Challenge

Create:

```text
master
feature/a
feature/b
```

Then:

1. create conflicting commits

2. resolve conflicts

3. squash commits

4. recover with reflog

5. compare merge vs rebase history

***

# Excellent Learning Resources

* [Git Documentation — Rebase](https://git-scm.com/docs/git-rebase?utm_source=chatgpt.com)

* [Atlassian Git Rebase Tutorial](https://www.atlassian.com/git/tutorials/rewriting-history/git-rebase?utm_source=chatgpt.com)

* [Pro Git Book](https://git-scm.com/book/en/v2?utm_source=chatgpt.com)

* [Learn Git Branching (Interactive)](https://learngitbranching.js.org/?utm_source=chatgpt.com)

***

# Final Goal

After this bootcamp you should be comfortable with:

* rebasing branches

* fixing conflicts

* interactive rebase

* squashing commits

* recovering mistakes

* professional Git workflows

The next great topic after this is:

* cherry-pick

* reflog deep dive

* bisect

* advanced branching strategies

* Git internals

* rebase in collaborative teams

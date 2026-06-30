---
id: 20260523191349
title: Git merge versus rebase
author: Karl Schmitt
date: 2026-05-23
keywords: [ git, merge, rebase]
---

# Git merge versus rebase

Here you can learn about merge versus rebase:
1. [Learn about Merge versus Rebase ...](https://shiftmag.dev/rebase-over-merge-4014/)
2. [Again learn about Merge versus Rebase ...](https://zapier.com/blog/git-rebase-vs-merge/)

## Merge

```bash
git merge main
```

Creates:

```text
A---B---C---F---G
     \         /
      D---E---M
```
![Imagine git merge](../Images/Imagine_git_merge_001.png)

Advantages:

* preserves exact history

* safe for shared branches

Disadvantages:

* messy history over time

***

## Rebase

```bash
git rebase main
```

Creates:

```text
A---B---C---F---G---D'---E'
```
![Imagine after git rebase main 001](../Images/Imagine_after_git_rebase_main_002.png)

Advantages:

* clean linear history

* easier to read logs

* great before pull requests

Disadvantages:

* rewrites commit history

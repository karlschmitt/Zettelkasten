---
id: 20260523165350
title: Git mini rebase practice exercise
author: Karl Schmitt
date: 2026-05-23
---

# Git mini rebase practice exercise

Create demo repo:

```bash
mkdir git-rebase-demo
cd git-rebase-demo

git init
```

Create commits:

```bash
echo "A" > file.txt
git add .
git commit -m "A"

echo "B" >> file.txt
git commit -am "B"
```

Create branch:

```bash
git checkout -b feature
```

Add commits:

```bash
echo "Feature 1" >> file.txt
git commit -am "Feature 1"
```

Return to main:

```bash
git checkout main
```

Add more commits:

```bash
echo "Main update" >> file.txt
git commit -am "Main update"
```

Now rebase:

```bash
git checkout feature
git rebase main
```

Perfect beginner exercise.

***

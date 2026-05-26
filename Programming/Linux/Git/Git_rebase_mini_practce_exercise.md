---
id: 20260523165350
title: Git mini rebase practice exercise
author: Karl Schmitt
date: 2026-05-23
---

# Git mini rebase practice exercise

### Create demo git repo:

```bash
mkdir git-rebase-demo
cd git-rebase-demo

git init
```
![git init](./Images/practice-exercise-git-init-001.png)


### Create commits on main branch:

```bash
echo "A" > file.txt
git add .
git commit -m "A"

echo "B" >> file.txt
git commit -am "B"
```

![git commit on main branch](./Images/practice-exercise-git-commit-002.png)

![git comimt on master](./Images/Imagine_after_git_init_master_005.png)

### Create feature branch:

```bash
git checkout -b feature
```

Add commits:

```bash
echo "Feature 1" >> file.txt
git commit -am "C"
# or
git commit -am "Feature 1"
```

![practice exercise git checkout feature](./Images/practice-exercise-git-checkout-feature-003.png)

![git commit feature](./Images/Imagine_after_git_commit_feature_003.png)

### Return to main/master:

Sometimes the main branch is called master. 
```bash
git checkout main
# or
git checkout master
```
Add more commits on the main/master branch:
```bash
echo "Main update" >> file.txt
# or
echo "Master update" >> file.txt
git commit -am "D"
# or
git commit -am "D"
```
![git checkout master](./Images/practice-excercise-git-checkout-master-004.png)

![git commit master again](./Images/Imagine_after_git_commit_master_again_004.png)

### Now rebase master onto feature:
```bash
git checkout feature
git rebase main
# or
git rebase master
```
![git rebase master](./Images/practice-exercise-git-rebase-master.png)

Now lets look at the ```git status``` report, here you can see a conflict:
```powershell
git status
```
![git status on feature branch](./Images/practice-exercise-git-status-on-feature-branch.png)

Fixing the conflict using Neovim:
```powershell
nvim file.txt
```

![nvim file.txt](./Images/practice-exercise-nvim-file-001.png)

Now let's continue the rebase:
```powershell
git add file.txt
git rebase --continue
```
![git rebase --continue](./Images/perfect-exercuse-git-rebase-continue-001.png)

Let's do a final ```git status```:

![final git status](./Images/practice-execise-final-git-status-001.png)

Perfect beginner exercise.

***

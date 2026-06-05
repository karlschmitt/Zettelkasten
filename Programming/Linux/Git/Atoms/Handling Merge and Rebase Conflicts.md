---
id: 20260530090038
title: Handling Merge and Rebase Conflicts
author: Karl Schmitt
date: 2026-05-30
keywords: [ git, rebase, merge, meld]
---

# Git and Meld Tutorial: Handling Merge and Rebase Conflicts

**Meld** is an excellent visual merge tool for Git because it lets you compare files side-by-side and choose which changes to keep.

This tutorial covers:

1. Understanding conflicts

2. Handling merge conflicts

3. Handling rebase conflicts

4. Configuring Meld

5. Real-world examples

6. Useful commands

***

# 1. Why Conflicts Happen

Suppose you have:

```text
master
 |
 +---- A ---- B
               \
feature         C ---- D
```

![Imagine_git_master_and_commit_feature_004](../Images/Imagine_git_master_and_commit_feature_004.png)

Both branches modify the same line, here an example:

**master branch ** 🌳

```typescript
const url = "https://www.ecosia.org/";
```

**feature branch** 🦆

```typescript
const url = "https://duckduckgo.com";
```

Git cannot decide automatically which version should survive.

```powershell
git status
```

Result:

```text
CONFLICT (content): Merge conflict
```

***

# 2. Configure Meld as Git Merge Tool

## Linux

```bash
sudo apt install meld
```

## Windows

Install Meld from:

```text
https://meldmerge.org
```

Configure Meld for Git:

```bash
git config --global merge.tool meld
git config --global mergetool.meld.path "C:/Program Files/Meld/Meld.exe"
git config --global mergetool.keepBackup false
```
Verify:
```bash
git config --get merge.tool
```

Expected:
```text
meld
```
![configure meld](../Images/configure-meld.png)
***

# 3. Merge Conflict Tutorial

## Create examle TypeScript file on GitHub

![Git-afraid-to-commit](../Images/GitHub-afraid-to-commit.png)

### Add type script «hello world» file

![GitHub create new files](../Images/GitHub-create-new-files.png)

![GitHub hola carlos](../Images/GitHub-hola-carlos.png)

![GitHub new file listed](../Images/GitHub-new-file-listed.png)

### Let's edit the file to create revision «B»

![GitHub add missing exclamationmark](../Images/GitHub-add-missing-exclamation-mark.png)

![GitHub revision B](../Images/GitHub-revision-B.png)

![GitHug revision B overview](../Images/GitHug-revision-B-overview.png)

### Now we have the following situation on GitHub:

![GitHub master revision A  and B](../Images/Imagine_after_git_rebase_master_006.png)

![Cloning the repostory](../Images/Cloning-it.png)

![GitHub-PowerShell-Clone-It](../Images/GitHub-PowerShell-Clone-It.png)

## Create a conflicting example

On Windows you might have to add this exception:

```powershell
git config --global --add safe.directory D:/playground/meld-sandbox/afraid-to-commit
```
![GitHub git exception](../Images/GitHub_git_exception.png)

Create a new feature branch:

```powershell
git checkout -b feature
```
![GitHub git checkout -b feature](../Images/GitHub_git_checkout_feature.png)

### Let's change the type script file:

```powershell
nvim .\hello-world.ts
```

Modify the typescript file:
```typescript
console.log("Feature Version");
```
![GitHub_Hi_Charls](../Images/GitHub_Hi_Charls.png)

Commit the changes to the feature branch 👩‍🏭:
```powershell
git add .
git commit -m "C"
```
There is a syntax error 😈 in the firstline. Let“s correct it and add anther line:

![GitHub Long live the king](../Images/GitHub_Long_live_the_king.png)

Again commit the changes to the feature branch👩‍🏭:
```powershell
git add .
git commit -m "D"
```

![GitHub_git_commit_D](../Images/GitHub_git_commit_D.png)

Now we have two revisions «C» and «D» in the feature branch:

![git return to master](../Images/Imagine_git_master_and_commit_feature_004.png)

Switch back to the master branch:

```bash
git checkout master
```

![GitHub git checkout master](../Images/GitHub_git_checkout_master.png)

List the content of the master branch:

![Edit TypeScript file in master branch](../Images/Edit_TypeScript_Master.png)

Modify same lines:

```typescript
console.log("Hola Carlos!"); // correct first char
console.log("Master Version E");
console.log("Viva el rey"); 
```

![Modify TypeScript master version E](../Images/Modify_TypeScript_master_version_E.png)

Commit:

```bash
git add .
git commit -m "E"
git push
```
![Commit_and_status_TypeScript_file_version_E](../Images/Commit_and_status_TypeScript_file_version_E.png)

Now we have the following situation:

![git_before_merge_master](../Images/Imagine_after_git_merge_main_003.png)

Let“s merge feature onto master::

```bash
git merge feature
```

🚨 Git tries an auto merge, and informs us about a conflict 💥:

![Merge_conflict_in_hello-world.ts](../Images/Merge_conflict_in_hello-world.ts.png)
```text
Auto-merging hello-world.ts
CONFLICT (content): Merge conflict in hello-world.ts
```
***

# 4. Inspect Conflict 🚨

Let's look what ```git status``` says:

![Git status conflict](../Images/Git_status_conflict.png)

💥 Yes we have a conflict!

Open the TypeScript file:
```typescript
<<<<<<< HEAD
console.log("Hola Carlos!"); // correct first char
console.log("Master Version E");
console.log("Viva el rey"); 
=======
console.log("Hi Charls!");
console.log("Feature Version");
console.log("Long live the king!")
>>>>>>> feature
```
🔬 Let's prick into the file:

![Open_conflicting_file](../Images/Open_conflicting_file_001.png)

✨Meaning:
```text
<<<<<<< HEAD
Current branch

=======
Separator

>>>>>>> feature
Incoming branch
```
***

# 5. Start Meld to resolve the merge conflict 

Our situation now:
![Git merge conflict master](../Images/Git_merge_conflict_master_004.png)

To start meld, please run:
```bash
git mergetool
```

Meld opens:

![Meld first conflict screen shot](../Images/Meld_first_conflict_screen_shot_001.png)

Typical layout:

```text
LEFT        BASE      RIGHT
Master      Common    Feature
```

or

```text
LOCAL     MERGED    REMOTE
```

depending on Git versions.

***

# 6. Resolve in Meld

Buttons typically allow:

```text
← Use Left
→ Use Right
```

Accept right:

![Meld_merge_accept_right](../Images/Meld_merge_accept_right.png)

Accept left:

![Merge_conflict_accept_left](../Images/Merge_conflict_accept_left.png)

Examples:

Choose feature version (right) and adjust:
```typescript
console.log("Hi Charls!");
nsole.log("Master Version F");
console.log("Long live the king!")
```
![Meld_select_feature_version_and adjust](../Images/Meld_select_feature_version_and adjust.png)

Or combine both sides and adjust:
```typescript
console.log("Hi Charls!");
nsole.log("Master Version F");
console.log("Long live the king!")
```

![Meld_merge_use_both_change_sets_and_adjust](../Images/Meld_merge_use_both_change_sets_and_adjust.png)

Save the target file.

Line 1 and 3 are from the right. While line 2 is from the left.

![Meld_resolved_merge_conflict](../Images/Meld_resolved_merge_conflict.png)

Close Meld.

***

# 7. Complete Merge

Check status after conflict resolution:
```bash
git status
```

![Meld_right_after_resolving_the_merge_conflict](../Images/Meld_right_after_resolving_the_merge_conflict.png)

Add this point, you can still abort the merge::

```text
git merge --abort
```

Stage resolved file:
```bash
git add hello-world.ts
```

Finish merge:
```bash
git commit -m "F"
```

Git creates a merge commit (Version F).

Graph:
```text
A---B---E---M
     \       \
      C-------D
```
M = Merge commit

![Git merge conflict master](../Images/Git_merge_conflict_master_004.png)
***

# 8. Rebase Conflict Tutorial

Imagine:

```text
main
 |
 A---B---C

feature
 |
 A---B---D---E
```

Update feature:

```bash
git checkout feature
git rebase main
```

Git tries:

```text
Replay D onto C
Replay E onto C
```

Conflict appears:

```text
CONFLICT
```

***

# 9. What Happens During Rebase

Git stops:

```text
Applying: Feature change
```

Status:

```bash
git status
```

Output:

```text
You are currently rebasing
```

***

# 10. Open Meld During Rebase

Launch:

```bash
git mergetool
```

Resolve visually.

Save.

Close Meld.

***

# 11. Continue Rebase

Stage:

```bash
git add app.ts
```

Continue:

```bash
git rebase --continue
```

Git proceeds to next commit.

If another conflict appears:

```text
Resolve
git add
git rebase --continue
```

Repeat.

***

# 12. Abort Rebase

If things get messy:

```bash
git rebase --abort
```

Everything returns to original state.

***

# 13. Skip Current Commit

Sometimes a commit is no longer needed:

```bash
git rebase --skip
```

Git ignores current commit and continues.

Use carefully.

***

# 14. Difference Between Merge and Rebase Conflict Resolution

## Merge

Command:

```bash
git merge feature
```

History:

```text
A---B---C
     \   \
      D---M
```

Preserves branch history.

***

## Rebase

Command:

```bash
git rebase main
```

History:

```text
A---B---C---D'---E'
```

Cleaner linear history.

Conflict resolution process is nearly identical:

```text
Resolve
git add
Continue
```

Only final command differs:

```bash
git commit
```

vs

```bash
git rebase --continue
```

***

# 15. Useful Status Commands

Show current conflict:

```bash
git status
```

Show conflicted files:

```bash
git diff --name-only --diff-filter=U
```

View graph:

```bash
git log --oneline --graph --all
```

***

# 16. Daily Workflow Example

## Updating Feature Branch

```bash
git checkout feature

git fetch origin

git rebase origin/main
```

Conflict?

```bash
git mergetool
git add .
git rebase --continue
```

Repeat until complete.

Push:

```bash
git push --force-with-lease
```

Because rebase rewrites history.

***

# 17. PowerShell Cheat Sheet

```powershell
git status

git mergetool

git add .

git commit

git rebase --continue

git rebase --abort

git rebase --skip

git log --oneline --graph --all
```

***

# Recommended Learning Path

1. Learn normal merges first.

2. Practice resolving conflicts in Meld.

3. Learn interactive rebase (`git rebase -i`).

4. Practice rebasing feature branches daily.

5. Use `git log --graph --all` after every operation to visualize what happened.

A good next step is a **Git + Meld Conflict Resolution Bootcamp** with hands-on exercises that intentionally create increasingly difficult merge and rebase conflicts and walk through resolving them step by step.

---
id: 20260523181327
title: Git howto handle rebase conflicts?
author: Karl Schmitt
date: 2026-05-23
keywords: [ git, rebase, conflict ]
---

# Git howto handle rebase conflicts?

When you encounter a conflict during a rebase, 
_Git pauses the process and waits for you to fix the "clash" before it applies the next commit in the sequence_.

## 1. Identify the Conflict

Git will tell you which files are broken. You can always see the status by typing:

```bash
git status
```

Look for files under the heading "==Both modified==."

***

## 2. Fix the Code

Open the conflicted files in your code editor. You will see markers that look like this:

```text
<<<<<<< HEAD
(This is the code currently on the main branch)
=======
(This is the new code you wrote in your feature branch)
>>>>>>> Your Commit Message
```

* Delete the markers (`<<<<`, `====`, `>>>>`).
* Edit the code so it looks exactly how you want the final version to be.

***

## 3. Stage and Continue

Once the file is fixed, you need to tell Git you're ready to move on:

1. Add the fixed file:
   ```bash
   git add <file-name>
   ```
2. Resume the rebase:
   ```bash
   git rebase --continue
   ```

⚠️ Note: If you had 5 commits on your branch, you might have to repeat this process for each commit if they all touch the same lines of code.

***

## 4. The "Panic" Commands

If the conflict is too messy and you want to stop everything and return your branch to exactly how it was before you started:

```bash
git rebase --abort
```

If you want to completely ignore your changes and just keep what is on the `main` branch for a specific file:

```bash
git checkout --ours <file-name>  # Keep the "main" version
git checkout --theirs <file-name> # Keep "your" version
```

***

## 💡 Summary Workflow

1. `git status` (Find the mess)
2. Edit code (Fix the mess)
3. `git add .` (Stage the fix)
4. `git rebase --continue` (Keep going)

Do you want to know how to use a visual merge tool (like VS Code or ==Meld)== to make resolving these conflicts much easier?


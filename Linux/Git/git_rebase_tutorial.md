---
id: 20260520175909
title: Git rebase tutorial
author: Karl Schmitt
date: 2026-05-20
keywords: [ git, rebase ]
---

# Git Rebase Tutorial

`git rebase` is one of the most useful — and most misunderstood — Git commands.

It helps you:

* keep a clean commit history

* move your work onto newer commits

* avoid unnecessary merge commits

* edit/squash/reorder commits before sharing them

***

# 1. What Is Rebase?


Git rebase is a command that moves or "replays" a sequence of commits from one branch onto a new base commit.

Instead of combining two branches with a "merge commit," rebasing rewrites the project history so that your changes appear to have been built sequentially on top of the latest work from another branch (like main).

![Git rebase from main](./Images/Git_rebase_from_main.png)

#### Why Use Rebase?

* Clean History: It creates a linear, straight-line path of commits that is much easier to read than a "spaghetti" history of merges.
* Avoid Merge Commits: It prevents the "Merge branch 'main' into 'feature'" commits that often clutter logs.
* Polished Commits: You can use "interactive rebase" (git rebase -i) to squash small fixes into one clean commit or reword old messages.
* Simpler Conflict Resolution: Conflicts are resolved one commit at a time during the replay, rather than all at once in a massive merge. [3, 4, 5, 6, 7, 8, 9, 10] 

------------------------------
### How It Works

   1. Detach: Git temporarily "parks" your unique commits in a safe place.
   2. Reset: Your branch is reset to match the latest state of the target branch (e.g., main).
   3. Replay: Git takes your parked commits and applies them one-by-one onto the new tip of the branch.
   4. Rewrite: Because the base has changed, Git creates brand new commits with different IDs (hashes). [1, 2, 3, 4, 11, 12, 13] 

------------------------------
### ⚠️ The Golden Rule of Rebasing

Never rebase commits that you have already pushed to a public/shared branch. [14, 15] 
Since rebase rewrites history by creating new commit IDs, anyone else working on that branch will see their history as diverged and broken. Only rebase local branches that only you are working on. [11, 16, 17, 18] 

| Feature [2, 3, 4, 11, 14, 19, 20, 21] | Git Merge | Git Rebase |
|---|---|---|
| History | Preserves exact chronological history | Creates a clean, linear history |
| Traceability | Keeps "Merge commits" as context | No extra merge commits; looks like a straight line |
| Risk | Safe and non-destructive | Riskier; rewrites history (use only locally) |

------------------------------
If you'd like, I can show you:

* The exact commands to run for a standard rebase.
* How interactive rebase works for "squashing" commits.
* How to fix conflicts if the rebase stops halfway. [22] 


[1] [https://git-scm.com](https://git-scm.com/docs/git-rebase)
[2] [https://www.youtube.com](https://www.youtube.com/watch?v=yTFC_MvwJvQ&t=47)
[3] [https://www.gitkraken.com](https://www.gitkraken.com/learn/git/git-rebase)
[4] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/git/rebasing-of-branches-in-git/)
[5] [https://stackoverflow.com](https://stackoverflow.com/questions/13193787/why-would-i-want-to-do-git-rebase)
[6] [https://www.reddit.com](https://www.reddit.com/r/programming/comments/1mn85pw/git_rebase_explained_like_youre_new_to_git/)
[7] [https://www.reddit.com](https://www.reddit.com/r/git/comments/t5dctv/am_i_not_understanding_how_git_rebase_work/)
[8] [https://docs.github.com](https://docs.github.com/en/get-started/using-git/about-git-rebase)
[9] [https://www.youtube.com](https://www.youtube.com/watch?v=_UZEXUrj-Ds)
[10] [https://shiftmag.dev](https://shiftmag.dev/rebase-over-merge-4014/)
[11] [https://www.youtube.com](https://www.youtube.com/watch?v=KrJxJklLTjk)
[12] [https://www.youtube.com](https://www.youtube.com/watch?v=qZDF7EPiS0g&t=30)
[13] [https://git-scm.com](https://git-scm.com/docs/git-rebase/2.52.0)
[14] [https://www.reddit.com](https://www.reddit.com/r/git/comments/1kwf4nr/what_git_rebase_is_for/)
[15] [https://www.reddit.com](https://www.reddit.com/r/git/comments/1jirf1q/i_dont_quite_understand_the_risks_of_rebase/)
[16] [https://zapier.com](https://zapier.com/blog/git-rebase-vs-merge/)
[17] [https://intellipaat.com](https://intellipaat.com/blog/git-rebase/)
[18] [https://medium.com](https://medium.com/@shekharsomani98/git-rebase-the-complete-guide-to-maintaining-clean-linear-history-28b88b3ef0d6)
[19] [https://git-scm.com](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)
[20] [https://www.youtube.com](https://www.youtube.com/watch?v=zOnwgxiC0OA&t=7)
[21] [https://docs.gitlab.com](https://docs.gitlab.com/topics/git/git_rebase/)
[22] [https://dojofive.com](https://dojofive.com/blog/the-git-cherry-pick-and-git-rebase-interactive-combo/)



Imagine this history:

```text
main
A---B---C

feature
     \
      D---E
```

Meanwhile, `main` receives new commits:

```text
main
A---B---C---F---G

feature
     \
      D---E
```

You want your feature branch to look like it started from `G`.

With rebase:

```bash
git checkout feature
git rebase main
```

Git rewrites your commits (`D`, `E`) onto the latest `main`.

Result:

```text
main
A---B---C---F---G

feature
                 \
                  D'---E'
```

Notice:

* `D'` and `E'` are NEW commits

* history becomes linear

* no merge commit is created

***

# 2. Merge vs Rebase

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

Advantages:

* clean linear history

* easier to read logs

* great before pull requests

Disadvantages:

* rewrites commit history

***

# 3. Basic Rebase Workflow

## Step 1 — Switch to your branch

```bash
git checkout feature
```

***

## Step 2 — Update main

```bash
git checkout main
git pull
```

***

## Step 3 — Rebase feature onto main

```bash
git checkout feature
git rebase main
```

Git now replays your commits on top of `main`.

***

# 4. Handling Rebase Conflicts

Sometimes Git cannot automatically replay a commit.

You may see:

```text
CONFLICT (content): Merge conflict in app.js
```
Merge conflicts occur during a rebase for the same reason they do during a merge: _two different commits changed the same line of code in the same file, and Git doesn't know which version to keep_. \[1, 2]

However, rebase handles conflicts differently than a standard merge. \[3]

### 1. Sequential Application \[4]

While a merge combines the final state of two branches at once, a rebase takes your commits and reapplies them one by one on top of the new base. \[3, 5]

* Conflict Trigger: If your first commit changes a line that was also changed in the "new base" (the target branch), Git pauses.
* Repeating Conflicts: You might have to resolve the same conflict multiple times if several of your commits touch that same line. \[1, 6, 7, 8]

### 2. Rewriting History

Rebase technically "rewrites" history by creating brand-new commits with different IDs (hashes). \[5, 9]

* Because Git is effectively "replay-ing" your work on a new foundation, it checks for compatibility at every single step.
* If you previously resolved a conflict in a merge, rebase may force you to do it again because it ignores that past merge resolution. \[10, 11]

### 3. Diverged Path

Conflicts often happen when your branch has "diverged" significantly from the main branch. \[12]

* If someone else changed a function name in `main` and you called that same function in your feature branch, [Git](https://github.com/) will flag this as a conflict during rebase. \[6]

***

### 💡 Common Rebase Commands

If you hit a conflict, Git will pause and wait for you to: \[13]

* Fix the files: Open the file, keep the code you want, and remove conflict markers.
* `git add <file>`: Stage the fixed file.
* `git rebase --continue`: Move on to the next commit in your branch.
* `git rebase --abort`: Completely cancel the rebase and go back to how things were. \[1, 5, 14, 15, 16]

Would you like to know how to avoid these conflicts in the first place, or should we look at how to squash commits to make rebasing easier?



\[1] [https://www.youtube.com](https://www.youtube.com/watch?v=OXtdxHTh2oY\&t=32)

\[2] [https://docs.github.com](https://docs.github.com/articles/about-merge-conflicts)

\[3] [https://www.aviator.co](https://www.aviator.co/blog/rebase-vs-merge-pros-and-cons/)

\[4] [https://docs.gitlab.com](https://docs.gitlab.com/topics/git/git_rebase/)

\[5] [https://www.youtube.com](https://www.youtube.com/watch?v=DkWDHzmMvyg\&t=105)

\[6] [https://algomaster.io](https://algomaster.io/learn/git/rebase-conflicts)

\[7] [https://stackoverflow.com](https://stackoverflow.com/questions/34298273/does-git-rebase-create-more-conflicts-than-git-merge)

\[8] [https://jhall.io](https://jhall.io/archive/2024/01/10/when-rebasing-is-better-than-merging/)

\[9] [https://stackoverflow.com](https://stackoverflow.com/questions/31401754/why-does-the-same-conflict-reappear-when-i-use-git-rebase)

\[10] [https://www.reddit.com](https://www.reddit.com/r/git/comments/1dzafey/merge_vs_rebase/)

\[11] [https://dev.to](https://dev.to/bitethecode/git-tutorials-understanding-of-rebase-and-merge-2cg4)

\[12] [https://graphite.com](https://graphite.com/guides/git-merge-rebase-differences-benefits)

\[13] [https://medium.com](https://medium.com/@annxsa/mastering-git-merge-and-rebase-to-avoid-code-conflicts-in-2026-3baa7e86010c)

\[14] [https://docs.github.com](https://docs.github.com/en/get-started/using-git/resolving-merge-conflicts-after-a-git-rebase)

\[15] [https://graphite.com](https://graphite.com/guides/git-rebase-conflicts)

\[16] [https://docs.github.com](https://docs.github.com/en/get-started/using-git/resolving-merge-conflicts-after-a-git-rebase)

***

## Step 1 — Open conflicted files

Git marks conflicts like this:

```text
<<<<<<< HEAD
new code from main
=======
your feature code
>>>>>>> feature
```

Edit the file manually.

***

## Step 2 — Mark resolved

```bash
git add app.js
```

***

## Step 3 — Continue rebase

```bash
git rebase --continue
```

***

## Abort rebase

If things go badly:

```bash
git rebase --abort
```

Everything returns to the previous state.

***

# 5. Interactive Rebase (The Superpower)

Interactive rebase lets you:

* squash commits

* rename commits

* reorder commits

* remove commits

* split commits

***

## Start interactive rebase

Rebase the last 3 commits:

```bash
git rebase -i HEAD~3
```

Git opens an editor:

```text
pick a1b2 First commit
pick c3d4 Second commit
pick e5f6 Third commit
```

***

# 6. Interactive Rebase Commands

## pick

Keep commit unchanged.

```text
pick a1b2 Add login page
```

***

## reword

Change commit message.

```text
reword a1b2 Add login page
```

***

## squash

Combine commit with previous one.

```text
pick   a1b2 Add login page
squash c3d4 Fix typo
```

Result:

* one cleaner commit

***

## fixup

Like squash, but discards commit message.

```text
pick  a1b2 Add login page
fixup c3d4 Fix typo
```

***

## drop

Delete a commit.

```text
drop a1b2 Temporary debug logs
```

***

# 7. Squashing Example

Before:

```text
Add navbar
Fix navbar typo
Fix CSS
Fix spacing
```

After interactive rebase:

```text
Add navbar component
```

Much cleaner for pull requests.

***

# 8. Rebase Onto Another Branch

You can move a branch to a completely different base.

```bash
git rebase --onto new-main old-main feature
```

Advanced but powerful.

***

# 9. Golden Rule of Rebase

## NEVER rebase public/shared commits

Bad:

```bash
git push
git rebase
git push --force
```

This rewrites history other people may already use.

***

## Safe places to rebase

Good:

* local feature branches

* before opening PRs

* cleaning commits before pushing

***

# 10. Force Push After Rebase

Because commits changed:

```bash
git push --force-with-lease
```

Prefer:

```bash
--force-with-lease
```

instead of plain:

```bash
--force
```

It is safer.

***

# 11. Useful Rebase Commands

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

## Skip problematic commit

```bash
git rebase --skip
```

***

## Rebase current branch onto main

```bash
git rebase main
```

***

# 12. Visual Example

## Before

```text
main:
A---B---C

feature:
     \
      D---E
```

***

## After `git merge main`

```text
A---B---C---F
     \      \
      D---E--M
```

***

## After `git rebase main`

```text
A---B---C---F---D'---E'
```

***

# 13. Recommended Beginner Workflow

For personal feature branches:

```bash
git checkout main
git pull

git checkout feature
git rebase main
```

Then:

```bash
git push --force-with-lease
```

ONLY if the branch was already pushed.

***

# 14. Understanding HEAD~3

```bash
HEAD~1
```

\= previous commit

```bash
HEAD~3
```

\= three commits back

Useful with interactive rebase:

```bash
git rebase -i HEAD~5
```

***

# 15. Real-World Example

You made these commits:

```text
Add form
Fix typo
Debug output
Remove debug output
Fix CSS
```

Interactive rebase can turn this into:

```text
Add user form UI
```

This makes team history far easier to read.

***

# 16. Rebase Cheat Sheet

## Basic rebase

```bash
git rebase main
```

***

## Interactive rebase

```bash
git rebase -i HEAD~5
```

***

## Continue after conflicts

```bash
git rebase --continue
```

***

## Abort

```bash
git rebase --abort
```

***

## Safe force push

```bash
git push --force-with-lease
```

***

# 17. When To Use Rebase

Use rebase when:

* updating feature branches

* cleaning commits

* preparing pull requests

* keeping history linear

Avoid rebase when:

* commits are already shared publicly

* multiple developers depend on the branch

***

# 18. Recommended Learning Path

Practice in this order:

1. Basic rebase

2. Conflict resolution

3. Interactive rebase

4. Squash/fixup

5. Reordering commits

6. Advanced `--onto`

***

# 19. Mini Practice Exercise

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

# 20. Most Important Takeaway

Rebase does NOT “move commits.”

It:

1. copies commits

2. replays them elsewhere

3. creates NEW commit hashes

That is why rebasing shared history is dangerous.

---

You can perform a Git rebase in Visual Studio Code using either the built-in Source Control menu or specialized extensions like [GitLens](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens) for a more visual experience. \[1, 2, 3]

### Standard Method (Built-in)

VS Code has native support for basic rebasing through the command palette or the Source Control view. \[4, 5]

1. Checkout the branch you want to rebase (e.g., your feature branch).
2. Open the Source Control view (`Ctrl+Shift+G`).
3. Click the three dots (...) at the top of the Source Control panel.
4. Select Branch > Rebase Branch....
5. Choose the target branch (e.g., `main` or `master`) you want to rebase onto. \[6, 7, 8]

***

## Interactive Rebase with GitLens \[1]

For complex tasks like squashing, dropping, or reordering commits, the GitLens extension provides a dedicated visual editor. \[9]

1. Install GitLens from the VS Code Marketplace. \[10, 11]

2. Enable the Interactive Rebase Editor via the Command Palette (`Ctrl+Shift+P` > `GitLens: Enable Interactive Rebase Editor`). \[12]

3. Start the rebase by typing `git rebase -i <branch-name>` in the integrated terminal. \[13, 14]

4. A visual UI will open where you can:

   * Drag and drop to reorder commits.
   * Change actions (Pick, Squash, Drop, Reword) using dropdown menus. \[1, 15, 16, 17]

5. Click Start Rebase to execute the changes. \[1, 13]

[VS Code tips — Interactive rebase editor from the GitLens ...](https://www.youtube.com/watch?v=P5p71fguFNI), YouTube · Code 2020 · 2020 M12 16

***

## Handling Conflicts

If Git encounters conflicts during the rebase, VS Code will pause and alert you. \[18, 19, 20, 21]

* Resolve files: Open the conflicted files and use the Merge Editor to pick changes.
* Continue: Once resolved, stage the files (`+` icon) and click Continue in the rebase banner or run `git rebase --continue` in the terminal.
* Abort: If things go wrong, select Abort Rebase from the command palette or run `git rebase --abort`. \[1, 22, 23, 24, 25]

***

💡 Pro Tip: After a successful rebase, you will likely need to perform a Force Push (`git push --force-with-lease`) to update your remote branch, as the commit history has been rewritten. \[6, 25]

Would you like help with resolving specific merge conflicts or learning how to squash commits manually?



\[1] [https://blog.delpuppo.net](https://blog.delpuppo.net/why-i-love-gitlens-in-my-vscode-interactive-rebase)

\[2] [https://www.techielass.com](https://www.techielass.com/how-to-push-code-from-vs-code-to-github/)

\[3] [https://www.linkedin.com](https://www.linkedin.com/learning/using-git-with-visual-studio-code/gitlens)

\[4] [https://simplanova.com](https://simplanova.com/blog/guidelines-for-partners-git-with-vs-code/)

\[5] [https://stackoverflow.com](https://stackoverflow.com/questions/51381826/git-rebase-in-visual-studio-code)

\[6] [https://docs.fivem.net](https://docs.fivem.net/docs/contributing/git/rebase-guide/)

\[7] [https://code.visualstudio.com](https://code.visualstudio.com/docs/sourcecontrol/quickstart)

\[8] [https://stackoverflow.com](https://stackoverflow.com/questions/65153013/how-to-fetch-all-branches-and-tags-in-visual-studio-git)

\[9] [https://www.youtube.com](https://www.youtube.com/watch?v=P5p71fguFNI)

\[10] [https://www.gitkraken.com](https://www.gitkraken.com/blog/revamp-your-code-reviews-with-gitlens)

\[11] [https://docs.superoffice.com](https://docs.superoffice.com/contribute/tutorial.html)

\[12] [https://github.com](https://github.com/gitkraken/vscode-gitlens/discussions/1260)

\[13] [https://dev.to](https://dev.to/colbygarland/using-vs-code-to-git-rebase-1lc)

\[14] [https://www.youtube.com](https://www.youtube.com/watch?v=3o_01F04bZ4)

\[15] [https://stuartleeks.com](https://stuartleeks.com/posts/working-with-git-rebase-in-visual-studio-code/)

\[16] [https://blog.delpuppo.net](https://blog.delpuppo.net/why-i-love-gitlens-in-my-vscode-interactive-rebase)

\[17] [https://marketplace.visualstudio.com](https://marketplace.visualstudio.com/items?itemName=WMBGmbH.intellij-git-ext)

\[18] [https://learn.microsoft.com](https://learn.microsoft.com/en-us/azure/devops/repos/git/rebase?view=azure-devops)

\[19] [https://www.datacamp.com](https://www.datacamp.com/tutorial/git-rebase)

\[20] [https://www.gitkraken.com](https://www.gitkraken.com/learn/git/problems/git-interactive-rebase)

\[21] [https://medium.com](https://medium.com/novumlogic/git-pull-rebase-or-merge-resolving-diverged-branch-made-easy-%EF%B8%8F-%EF%B8%8F-e1b83a99f254)

\[22] [https://www.reddit.com](https://www.reddit.com/r/devops/comments/wm17jc/git_rebase/)

\[23] [https://www.youtube.com](https://www.youtube.com/watch?v=T1puiPJgP_0)

\[24] [https://git-scm.com](https://git-scm.com/book/en/v2/Appendix-A:-Git-in-Other-Environments-Git-in-Visual-Studio-Code)

\[25] [https://learn.microsoft.com](https://learn.microsoft.com/de-de/azure/devops/repos/git/rebase?view=azure-devops)


***

If you'd like, I can also provide:

* a **Git Rebase Bootcamp (7 days)**

* an **Interactive Rebase Deep Dive**

* a **visual conflict-resolution tutorial**

* a **Merge vs Rebase guide**

* a **Git branching workflow tutorial**

* a **Git for Angular/React developers guide**

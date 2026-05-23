---
id: 20260523180437
title: Git standard rebase
author: Karl Schmitt
date: 2026-05-23
keywords: [ git, rebase]
---

# Git standard rebase

To perform a standard rebase—typically used to update your feature branch with the latest changes from the `main` branch—follow these exact steps. \[1, 2, 3]

## 1. Update your local main branch \[3]

First, ensure your local copy of the target branch (usually `main` or `master`) is up to date with the remote server. \[4, 5]

```bash
git checkout main
git pull origin main
```

## 2. Start the rebase

Switch back to your feature branch and begin the rebase process. \[6, 7]

```bash
git checkout your-feature-branch
git rebase main
```

* What happens now: Git will "set aside" your unique commits, bring in the new commits from `main`, and then try to re-apply your commits on top. \[8, 9]

***

## 3. Handle any conflicts (If they occur) \[2]

If Git stops and says there are conflicts, you must resolve them manually:

1. Open the conflicted files and fix the code.
2. Stage the fixed files:
   ```bash
   git add <file-name>
   ```
3. Continue the rebase:
   ```bash
   git rebase --continue
   ```
   _Note: If you get stuck or everything goes wrong, you can always go back to the start with `git rebase --abort`._ \[10, 11, 12, 13]

***

## 4. Push your changes

Because rebasing rewrites history, a standard `git push` will likely be rejected if you've pushed this branch before. You must use a "force" push: \[7, 14, 15]

```bash
git push --force-with-lease
```

🚀 Pro Tip: Use `--force-with-lease` instead of just `--force`. It is safer because it won't overwrite the remote if someone else has pushed new work to your branch while you were rebasing. \[2, 7, 11]

***

## Alternative: The "All-in-One" Command \[2]

If you want to pull and rebase in a single step without switching branches, you can use: \[16, 17]

```bash
git pull --rebase origin main
```

This fetches the changes from `main` and immediately starts rebasing your current branch onto them. \[18]

Would you like to see how to use interactive rebase to clean up your commit messages before pushing?



\[1] [https://git-scm.com](https://git-scm.com/book/de/v2/Git-Branching-Rebasing)

\[2] [https://medium.com](https://medium.com/@shruti.latthe/understanding-git-rebase-a-user-friendly-guide-0e810200725a)

\[3] [https://www.youtube.com](https://www.youtube.com/watch?v=0chZFIZLR_0\&t=24)

\[4] [https://javascript.plainenglish.io](https://javascript.plainenglish.io/why-git-still-confuses-developers-rebase-vs-merge-vs-pull-vs-fetch-6e289fa4a70a)

\[5] [https://docs.gitlab.com](https://docs.gitlab.com/topics/git/git_rebase/)

\[6] [https://git-scm.com](https://git-scm.com/book/en/v2/Git-Branching-Rebasing)

\[7] [https://www.youtube.com](https://www.youtube.com/watch?v=FQSbiDeA5hA)

\[8] [https://medium.com](https://medium.com/@ashishsamal100/git-pull-vs-git-rebase-c11ea0c7ab85)

\[9] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/git/rebasing-of-branches-in-git/)

\[10] [https://docs.github.com](https://docs.github.com/en/get-started/using-git/resolving-merge-conflicts-after-a-git-rebase)

\[11] [https://docs.gitlab.com](https://docs.gitlab.com/topics/git/git_rebase/)

\[12] [https://www.lineserve.net](https://www.lineserve.net/blog/resolving-git-merge-conflicts-definitive-guide)

\[13] [https://algomaster.io](https://algomaster.io/learn/git/rebase-conflicts)

\[14] [https://www.centron.de](https://www.centron.de/en/tutorial/git-rebase-tutorial-interactive-merge-options-explained/)

\[15] [https://medium.com](https://medium.com/@shruti.latthe/understanding-git-rebase-a-user-friendly-guide-0e810200725a)

\[16] [https://medium.com](https://medium.com/@DGabeau/git-pull-rebase-vs-git-pull-c2b352fe53aa)

\[17] [https://www.gitkraken.com](https://www.gitkraken.com/learn/git/git-rebase)

\[18] [https://graphite.com](https://graphite.com/guides/git-pull-vs-rebase)

---
id: 20260523164306
title: How to process a git rebase using Visual Studio Code?
author: Karl Schmitt
date: 2026-05-23
kewords: [ git, visual studio code ]
---
![Der ultimative Rebase Workflow](./Images/Der_ultimative_Rebase_Workflow.png )


# How to process a git rebase using Visual Studio Code?

You can perform a Git rebase in Visual Studio Code using either the built-in Source Control menu or specialized extensions like [GitLens](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens) for a more visual experience.

### Standard Method (Built-in)

VS Code has native support for basic rebasing through the command palette or the Source Control view.

1. Checkout the branch you want to rebase (e.g., your feature branch).
2. Open the Source Control view (`Ctrl+Shift+G`).
3. Click the three dots (...) at the top of the Source Control panel.
4. Select Branch > Rebase Branch....
5. Choose the target branch (e.g., `main` or `master` or `master` ) you want to rebase onto. 

***

## Git Merge with Meld

[Using Meld as Your Git Merge Tool](./Atoms/Using_meld_for_git_rebase.md)

***

## Handling Conflicts

If Git encounters conflicts during the rebase, VS Code will pause and alert you.

* _List_ conflicting files: [Conflicting Files](./Atoms/List_conflicting_files.md)
* _Resolve_ files: Open the conflicted files and use the Merge Editor to pick changes.
* _Continue_: Once resolved, stage the files (`+` icon) and click Continue in the rebase banner or run `git rebase --continue` in the terminal.
* _Abort_: If things go wrong, select Abort Rebase from the command palette or run `git rebase --abort`.

Follow the white rabit 🐇: [Handle Conflict](./Atoms/Git_handle_rebase_conflicts.md)
***

💡 Pro Tip: After a successful rebase, you will likely need to perform a Force Push (`git push --force-with-lease`) to update your remote branch, as the commit history has been rewritten. 

```powershell
git push --force-with-ease
```
##
## Tutorial

🔗 [Git Rebase Tutorial with Visual Studio Code](./Atoms/Git_Rebase_Tutorial_with_Visual_Studio_Code.md)

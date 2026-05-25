---
id: 20260523164306
title: How to do a git rebase using Visual Studio Code?
author: Karl Schmitt
date: 2026-05-23
kewords: [ git, visual studio code ]
---

# How to do a git rebase using Visual Studio Code?

You can perform a Git rebase in Visual Studio Code using either the built-in Source Control menu or specialized extensions like [GitLens](https://marketplace.visualstudio.com/items?itemName=eamodio.gitlens) for a more visual experience.

### Standard Method (Built-in)

VS Code has native support for basic rebasing through the command palette or the Source Control view.

1. Checkout the branch you want to rebase (e.g., your feature branch).
2. Open the Source Control view (`Ctrl+Shift+G`).
3. Click the three dots (...) at the top of the Source Control panel.
4. Select Branch > Rebase Branch....
5. Choose the target branch (e.g., `main` or `master`) you want to rebase onto. 

***

## Interactive Rebase with GitLens

For complex tasks like squashing, dropping, or reordering commits, the GitLens extension provides a dedicated visual editor. \[9]

1. Install GitLens from the VS Code Marketplace. \[10, 11]

2. Enable the Interactive Rebase Editor via the Command Palette (`Ctrl+Shift+P` > `GitLens: Enable Interactive Rebase Editor`). \[12]

3. Start the rebase by typing `git rebase -i <branch-name>` in the integrated terminal. 

4. A visual UI will open where you can:

   * Drag and drop to reorder commits.
   * Change actions (Pick, Squash, Drop, Reword) using dropdown menus.

5. Click Start Rebase to execute the changes. 

[VS Code tips — Interactive rebase editor from the GitLens ...](https://www.youtube.com/watch?v=P5p71fguFNI),

***

## Handling Conflicts

If Git encounters conflicts during the rebase, VS Code will pause and alert you.

* ==List== conflicting files: [Conflicting Files](./Atoms/List_conflicting_files.md)
* ==Resolve== files: Open the conflicted files and use the Merge Editor to pick changes.
* ==Continue==: Once resolved, stage the files (`+` icon) and click Continue in the rebase banner or run `git rebase --continue` in the terminal.
* ==Abort==: If things go wrong, select Abort Rebase from the command palette or run `git rebase --abort`.

Follow the white rabit 🐇: [Handle Conflict](./Atoms/Git_handle_rebase_conflicts.md)
***

💡 Pro Tip: After a successful rebase, you will likely need to perform a Force Push (`git push --force-with-lease`) to update your remote branch, as the commit history has been rewritten. 

```powershell
git push --force-with-ease
```

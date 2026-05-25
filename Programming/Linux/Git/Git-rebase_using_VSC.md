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

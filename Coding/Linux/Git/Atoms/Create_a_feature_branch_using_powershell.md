---
id: 20260527181433
title: How to create a feature branch using powershell?
author: Karl Schmitt
date: 2026-05-27
keywords: [ Git, PowerShell, switch, branch]
---

To create a feature branch using PowerShell, you run standard Git CLI commands directly within the PowerShell console.

The most efficient command to create and immediately switch to a new feature branch is `git switch -c feature/your-feature-name`.

## 🛠️ Standard Method (Recommended)

Modern versions of Git use the `switch` command, which is safer and easier to remember than the older `checkout` syntax.

1. Open PowerShell and navigate to your local Git repository folder.
2. Ensure your local `main` or `develop` branch is active and completely up to date:
   ```powershell
   git switch main
   git pull origin main
   ```
3. Create and switch to your new feature branch:
   ```powershell
   git switch -c feature/add-login-page
   ```
   _(Note: The `-c` flag stands for create)._

***

## 🪵 Alternative Methods

## Using the Older `checkout` Command

If you are running an older version of Git (pre-2.23), use the `-b` flag with `git checkout` to create and switch branches simultaneously:

```powershell
git checkout -b feature/add-login-page
```

## Creating a Branch Without Switching

If you want to build the branch structure but remain on your current branch:

```powershell
git branch feature/add-login-page
```

***

## 🚀 Publishing Your Feature Branch

Because you created the branch locally, it does not exist on your remote server (like [GitHub](https://github.com/) or Azure DevOps) yet.

The first time you attempt to push changes from this new branch, configure the upstream tracking using the `-u` flag:

```powershell
git push -u origin feature/add-login-page
```

***

## 💡 PowerShell Pro-Tip: Native Autocompletion

By default, standard PowerShell will not show what Git branch you are actively working on. To make your PowerShell prompt look like Git Bash and automatically display your active branch, install the `posh-git` module:

```powershell
Install-Module posh-git -Scope CurrentUser
Add-PoshGitToProfile
```

If you need help with this, let me know:

* Do you want to base your new feature branch off a commit hash instead of the main branch?
* Are you facing any script execution policy errors in PowerShell?

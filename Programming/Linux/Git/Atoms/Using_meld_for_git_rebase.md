---
id: 20260527170456
title: Using Meld as Your Git Merge Tool
author: Karl Schmitt
date: 2026-05-27
keywords: [ Git, rebase, Meld]
---

To use [Meld](https://meldmerge.org/) for a git rebase, you must configure it as your default Git merge tool to easily resolve any conflicts that arise when Git replays your commits.

------------------------------

## 1. Configure Meld as Your Git Merge Tool

Run these commands in your terminal to set up Meld globally:

git config --global merge.tool meld
git config --global mergetool.meld.path "/path/to/meld"
git config --global mergetool.prompt false


Note: Replace "/path/to/meld" with your actual installation path if it is not in your system's PATH variables 
(e.g., C:/Program Files/Meld/Meld.exe on Windows).

------------------------------

## 2. Launch Your Rebase

Start your standard or interactive rebase against your target branch (e.g., main):

```powershell
    git rebase main
```
------------------------------
## 3. Open Meld to Resolve Conflicts

If Git encounters a conflict, the rebase will pause. Launch Meld immediately by typing:

git mergetool

This command automatically triggers Meld and opens a 3-pane window for every conflicted file.

------------------------------

## 4. Understand the Panes in Git Rebase

During a rebase, the standard meaning of "Local" and "Remote" is reversed compared to a normal git merge. This is because Git checks out the upstream target branch first and tries to replay your changes on top of it. [9, 12, 13] 

| Pane | Meld Name | What it Represents in a Rebase |
|---|---|---|
| Left | LOCAL | The upstream branch you are rebasing onto (e.g., the latest main branch code). |
| Middle | BASE / Merged | The final file you are editing. This is where you save your resolved code. |
| Right | REMOTE | Your personal branch containing the commit that Git is currently trying to apply. |

Use Meld's side arrows to pull valid code from the Left or Right panes into the Middle pane, or type directly into the middle pane to fix things manually.

------------------------


## 5. Continue the Rebase

   1. Save and Close Meld once the middle pane looks correct.
   2. Stage the resolved file:
   ```powershell
    git add <filename>
   ```
   
   
   3. Continue the rebase process:
   ```powershell
    git rebase --continue
  ```

If there are more conflicting commits, Git will pause again, and you just need to repeat steps 3 through 5 until the rebase completes.

------------------------------

To set up Meld for Git using PowerShell on Windows 11, you need to ensure the Git configuration can correctly locate and execute the Meld application.

## 1. Confirm Meld's Installation Path

By default, Meld installs to your `Program Files` directory. Open your PowerShell window and run this command to verify its location:

```powershell
Test-Path "C:\tools\tools41\Meld\Meld.exe"
```

* If this returns `True`, proceed to the next step.
* If it returns `False`, find where you installed Meld and update the path in the commands below accordingly.

***

## 2. Configure Git via PowerShell

Run these three commands in your PowerShell terminal to configure Meld globally.

Because PowerShell uses specific quote rules, wrap the inner Windows paths in escaped double quotes (`\"`) inside single quotes (`'`) so Git reads the spaces in "Program Files" correctly:

```powershell
git config --global merge.tool meld
git config --global mergetool.meld.path '"C:\Program Files\Meld\Meld.exe"'
git config --global mergetool.prompt false
```

***

## 3. Verification

To verify that your PowerShell commands successfully wrote to your global Git config file, run:

```powershell
git config --global --list
```

Look for these exact lines in the output:

```text
merge.tool=meld
mergetool.meld.path=C:\Program Files\Meld\Meld.exe
mergetool.prompt=false
```

***

## 4. Optional: Set Meld as Your Diff Tool

If you also want Meld to pop open when you type `git diff` (and not just during merge/rebase conflicts), run these additional commands in PowerShell:

```powershell
git config --global diff.tool meld
git config --global difftool.meld.path '"C:\Program Files\Meld\Meld.exe"'
git config --global difftool.prompt false
```

***

Here is a quick script to generate a fake rebase conflict right inside your PowerShell terminal. This will let you test if Meld launches properly.

## 1. Create a Test Repository

Copy and paste this entire block into your PowerShell window. It creates a new folder, initializes Git, and sets up two conflicting branches:

```powershell
# Create and enter a temporary folder
mkdir git-meld-test; cd git-meld-test

# Initialize repository
git init

# Create the base file on 'main' branch
"Line 1: Original Text" | Out-File -FilePath test.txt -Encoding utf8
git add test.txt
git commit -m "Initial commit"

# Create a feature branch and modify the file
git checkout -b feature-branch
"Line 1: Feature Branch Edits" | Out-File -FilePath test.txt -Encoding utf8
git add test.txt
git commit -m "Feature commit"

# Go back to main and modify the exact same line
git checkout main
"Line 1: Main Branch Edits" | Out-File -FilePath test.txt -Encoding utf8
git add test.txt
git commit -m "Main commit"

# Go back to feature branch to prepare for the rebase
git checkout feature-branch
```

***

## 2. Trigger the Conflict

Now, attempt to rebase your feature branch on top of `main`:

```powershell
git rebase main
```

Your terminal will show an error stating that automatic merge failed and left Conflict markers inside `test.txt`.

***

## 3. Launch Meld

To fix it using your new setup, type:

```powershell
git mergetool
```

***

## What to Look For:

* If it works: Meld will instantly pop open in a 3-pane window.

  * Left Pane (`LOCAL`): Will show "Main Branch Edits".
  * Right Pane (`REMOTE`): Will show "Feature Branch Edits".
  * Middle Pane: Pick the version you want, save, and exit Meld. Then run `git rebase --continue` in PowerShell to finish.

* If it fails: PowerShell will give you an error like `The merge tool meld is not available`.

Did Meld pop open successfully, or did you get a specific error message in your PowerShell window?


***


Now that Meld is open, you can practice pulling changes into that middle pane using the black side arrows.

Once you save and close Meld, you just need to run these final two commands in your PowerShell window to wrap up your test rebase:

```powershell
git add test.txt
git rebase --continue
```

If you ever want to get rid of this experiment, you can just safely delete the `git-meld-test` folder from your computer.

When Git resolves conflicts using a graphical tool like Meld, it automatically creates a safety backup copy of the conflicted file with a `.orig` extension.

You can handle these files in two ways: clean them up manually when needed, or stop Git from creating them entirely.

***

## 1. Delete Existing `.orig` Files Globally

To quickly find and delete all `.orig` files recursively in your current project folder, run this command in your PowerShell terminal:

```powershell
Get-ChildItem -Recurse -Filter *.orig | Remove-Item
```

***

## 2. Stop Git from Creating `.orig` Files Permanently

If you trust your tool and do not want these backup files cluttering your workspace in the future, you can tell Git to stop generating them by running:

```powershell
git config --global mergetool.keepBackup false
```

***

## 3. Alternative: Ignore Them in Git

If you want to keep them as a safety net but don't want them showing up as untracked files when you type `git status`, add them to your global ignore rules:

```powershell
# Create a global gitignore file if you don't have one
git config --global core.excludesfile "~/.gitignore_global"

# Add *.orig to that file
"*.orig" | Out-File -FilePath ~/.gitignore_global -Append -Encoding utf8
```

Are you ready to use this setup on your actual development project, or do you need help with any other Git configurations like setting up aliases for faster workflows?


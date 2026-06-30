---
id: 20260525194144
title:
author: Karl Schmitt
date: 2026-05-25
keywords: []
---

When a rebase stops because of a conflict, you can list the conflicting files using several methods, depending on how much detail you need.

### 1. The Most Readable Way: `git status`

This is the standard way to see what is going on. Git will group conflicting files under the header **"Unmerged paths"**.
```bash
git status
```
Look for files labeled **`both modified`**. These are your conflicting files.

---

### 2. The Quick List (Filenames Only)

If you want a clean list of just the filenames (useful for piping into another command or a text editor), use `git diff` with a filter:

```bash
git diff --name-only --diff-filter=U
```
*   `--name-only`: Only shows the file path.
*   `--diff-filter=U`: Only shows **U**nmerged (conflicting) files.

---

### 3. The "Plumbing" Way: `git ls-files`

If you want to see the "stages" of the conflict (the common ancestor, the version from the branch you are rebasing onto, and your version), use:

```bash
git ls-files -u
```
You will see the same filename listed three times with different stage numbers:
*   **Stage 1:** Common Ancestor
*   **Stage 2:** The "target" branch (e.g., `main`)
*   **Stage 3:** Your branch (the one being rebased)

---

### Summary of Workflow

Once you have identified the conflicting files:

1.  **Open the files** and search for the conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`).
2.  **Resolve the conflicts** by editing the code.
3.  **Stage the resolved files:**
    ```bash
    git add <file-name>
    ```
4.  **Continue the rebase:**
    ```bash
    git rebase --continue
    ```

**Pro Tip:** If you have a merge tool configured (like VS Code, Meld, or KDiff3), you can run `git mergetool`. It will automatically cycle through every conflicting file for you one by one.
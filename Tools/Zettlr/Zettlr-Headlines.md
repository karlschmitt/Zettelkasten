
# 20260405131607 Zettr-Headlines

In **Zettlr** (and almost all Markdown editors), headlines are created using the **hash symbol (`#`)**.

The most important rule in Zettlr is that there **must be a space** between the `#` and your text.

### 1. The Standard Way (Markdown)
Type the following directly into your note:

*   `# Headline 1` (The main title of your note)
*   `## Headline 2` (A sub-section)
*   `### Headline 3` (A sub-sub-section)

> **Pro Tip:** In a Zettelkasten system, you usually only have **one** `# Headline 1` at the very top to serve as the title of the note.

---

### 2. Keyboard Shortcuts (The Fastest Way)
Since you are using Windows, you can use these shortcuts while your cursor is on a line of text:

*   **Ctrl + 1**: Level 1 Headline (`#`)
*   **Ctrl + 2**: Level 2 Headline (`##`)
*   **Ctrl + 3**: Level 3 Headline (`###`)
*   ...and so on up to **Ctrl + 6**.

---

### 3. Important Zettlr Tip: The "ID" vs. The "Headline"
Since you are building a **Zettelkasten**, Zettlr often expects a unique ID (like `202310271030`) and a Headline. 

Most Zettelkasten users format their notes like this:
```markdown
# 202310271030 Your Note Title Here
```
Zettlr will then recognize the ID for linking and the text as the name of the note in your sidebar.

### 4. How to see if it worked?
If you look at the **Table of Contents** icon (usually on the right sidebar in Zettlr), your headlines should appear there. If they don't appear, check if you remembered the **space** after the `#`.

**Incorrect:** `#MyHeadline` (Zettlr treats this as a tag)
**Correct:** `# My Headline` (Zettlr treats this as a headline)

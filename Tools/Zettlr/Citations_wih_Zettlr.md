# 20260413135140 Citations with Zettr

To reference a book in [Zettlr](https://www.zettlr.com/), you must first connect a citation database (like a `.bib` or `.json` file) and then use the @citekey syntax within your text. \[1, 2]

## 1. Connect Your Library

Zettlr does not store books itself; it reads from a file exported from a reference manager like Zotero or JabRef. \[3, 4]

1. Export your library: In Zotero, right-click your collection, select Export Library, and choose CSL JSON or Better BibTeX.

   * _Tip:_ Check "Keep updated" to sync new books automatically.

2. Link to Zettlr: Open Zettlr's Preferences → Citations and select your exported file in the Citation Database field. \[2, 4, 5]

## 2. Insert the Citation

Once linked, you can cite books directly in your Markdown editor: \[6]

* Basic Citation: Type `@` followed by the author's name or title. An autocomplete list will appear; press Tab or Enter to select the book.
* Parenthetical: `[@citekey]` renders as _(Author, Year)_.
* In-text: `@citekey` renders as _Author (Year)_.
* With Page Numbers: `[@citekey, p. 42]` renders as _(Author, Year, p. 42)_. \[1, 2, 5, 7, 8]

## 3. Generate the Bibliography

Zettlr automatically tracks your citations in the References tab of the right-hand sidebar. \[9, 10]

* To ensure the bibliography appears at the end of your exported document, add a header like `# References` at the very bottom of your file.
* If you need the bibliography to appear in a specific spot (e.g., before an appendix), insert the following code: `::: {#refs} :::`. \[1, 4, 11]

Are you using Zotero with the Better BibTeX plugin, or would you like help setting up that automated sync? \[12, 13]



\[1] [https://docs.zettlr.com](https://docs.zettlr.com/en/editor/citations/)

\[2] [https://docs.zettlr.com](https://docs.zettlr.com/ru/core/citations/)

\[3] [https://www.zettlr.com](https://www.zettlr.com/)

\[4] [https://docs.zettlr.com](https://docs.zettlr.com/de/academic/citations/)

\[5] [https://research-memex.org](https://research-memex.org/implementation/foundational-setup/zettlr-setup-guide)

\[6] [https://docs.zettlr.com](https://docs.zettlr.com/de/academic/citations/)

\[7] [https://docs.zettlr.com](https://docs.zettlr.com/ru/core/citations/)

\[8] [https://research-memex.org](https://research-memex.org/implementation/foundational-setup/zettlr-setup-guide)

\[9] [https://docs.zettlr.com](https://docs.zettlr.com/en/sidebar/bibliography/)

\[10] [https://docs.zettlr.com](https://docs.zettlr.com/en/sidebar/bibliography/#:~:text=References%C2%B6%20The%20references%20tab%20contains%20a%20bibliography,which%20allows%20you%20to%20copy%20the%20references.)

\[11] [https://docs.zettlr.com](https://docs.zettlr.com/ru/core/citations/)

\[12] [https://docs.zettlr.com](https://docs.zettlr.com/de/academic/citations/)

\[13] [https://forum.zettlr.com](https://forum.zettlr.com/d/83-citation-referencing-literature-does-not-work)

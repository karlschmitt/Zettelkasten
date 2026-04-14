# 20260413140600 First Steps with Zotero

Starting with Zotero involves a simple setup: you _install the software, add a plugin to help it "talk" to Zettlr, and then link them together_. \[1, 2]

## 1. Install Zotero and the Connector

* Download Zotero: Go to the [Zotero Download Page](https://www.zotero.org/download/) and install the app for your computer (Windows, Mac, or Linux).
* Install the Browser Connector: On the same page, install the "Zotero Connector" for your browser (Chrome, Firefox, or Safari). This adds a button to your browser so you can save books with one click.
* Create an Account (Optional): You can [register](https://www.zotero.org/user/register/) for a free account to sync your library across different computers. \[1, 3, 4, 5, 6]

## 2. Install the "Better BibTeX" Plugin

Zettlr works best when [Zotero](https://www.zotero.org/) uses a plugin called Better BibTeX. It ensures your "citekeys" (like `@Smith2023`) stay consistent. \[2, 7, 8, 9]

1. Download the latest `.xpi` file from the [Better BibTeX releases](https://retorque.re/zotero-better-bibtex/installation/).
2. In Zotero, go to Tools → Add-ons (or Plugins).
3. Click the gear icon (top right) and select Install Add-on From File.... Select the `.xpi` file you just downloaded.
4. Restart Zotero when prompted. \[10, 11, 12]

## 3. Link Zotero to Zettlr

Now you need to create the "bridge file" that Zettlr will read:

1. Export Your Library: In Zotero, right-click My Library and select Export Library....
2. Choose Format: Select Better CSL JSON as the format.
3. Important: Check the box that says Keep updated. This means every time you add a book to Zotero, it automatically updates the file for Zettlr.
4. Save the file: Save it somewhere easy to find (e.g., your Documents folder).
5. Set Zettlr: Open Zettlr, go to Preferences → Citations, and click the folder icon to select that `.json` file. \[2, 11, 13, 14]

Try it out: Open a note in Zettlr and type `@`. You should see a list of any books you've saved to Zotero!

Would you like to know how to save your first book into Zotero using the browser button?



\[1] [https://guides.library.brandeis.edu](https://guides.library.brandeis.edu/zotero)

\[2] [https://docs.zettlr.com](https://docs.zettlr.com/en/guides/reference-manager-integration/)

\[3] [https://libguides.unm.edu](https://libguides.unm.edu/Zotero)

\[4] [https://library.montevallo.edu](https://library.montevallo.edu/ZoteroTutorial/Install)

\[5] [https://guides.hsict.library.utoronto.ca](https://guides.hsict.library.utoronto.ca/zotero)

\[6] [https://davidson.libguides.com](https://davidson.libguides.com/zotero/set-up)

\[7] [https://forums.zotero.org](https://forums.zotero.org/discussion/108523/manually-entering-unique-ids-to-library-items)

\[8] [https://retorque.re](https://retorque.re/zotero-better-bibtex/#:~:text=Better%20BibTeX%20%28BBT%29%20is%20an%20extension%20for,toolchains%20%28e.g.%20based%20on%20LaTeX%20/%20Markdown%29.)

\[9] [https://docs.zettlr.com](https://docs.zettlr.com/en/editor/citations/)

\[10] [https://retorque.re](https://retorque.re/zotero-better-bibtex/installation/)

\[11] [https://www.foodlawworkshop.com](https://www.foodlawworkshop.com/docs/toolbox/bibtex/)

\[12] [https://retorque.re](https://retorque.re/zotero-better-bibtex/index.print.html)

\[13] [https://www.zotero.org](https://www.zotero.org/support/kb/exporting)

\[14] [https://docs.zettlr.com](https://docs.zettlr.com/en/reference/settings/)

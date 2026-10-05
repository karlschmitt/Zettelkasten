---
id: 20260929201339
title: How AWK thinks
author: Karl Schmitt
date: 2026-09-29
keywords: [ AWK ]
---



> [NOTE!]
> AWK ist ein kompaktes und ausdrucksstarkes Unix-Werkzeug, das sich ideal zur strukturierten Verarbeitung von Textdateien wie Protokollen oder CSV-Tabellen eignet. Die grundlegende Funktionsweise basiert auf einer Datenfilterung nach dem Schema **Muster und Aktion**, bei der jede Zeile automatisch in einzelne **Datenfelder** unterteilt wird. Während optionale **BEGIN- und END-Blöcke** für die Vor- beziehungsweise Nachbereitung genutzt werden, steuern Bedingungen und integrierte Variablen den genauen Ablauf. Dank integrierter Funktionen, assoziativer Arrays und variabler Trennzeichen lassen sich selbst komplexe Auswertungen mühelos in einer einzigen Programmierschleife umsetzen.


# AWK deep dive for absolute beginners

AWK is a tiny, expressive language for transforming text—especially line‑based, column‑like data such as logs, tables, and CSV‑ish files. It’s built into almost every Unix/Linux system and often replaces small Python or shell scripts once you “get” its model.

![Tux](../Images/Tux.png)

## 1. Mental model: how AWK thinks

**Core idea:** AWK is a _data‑driven_ filter. You write **rules** of the form:

bash

```
awk 'pattern { action }' file
```

For every input line (called a _record_), AWK:

1. Splits the line into **fields** (`$1`, `$2`, …, `$NF`).

2. Checks whether the **pattern** matches.

3. If it matches, runs the **action** block.

**Key points:**

* **Record:** usually one line of input.

* **Field:** a column within that line.

* **Default separator:** any whitespace; configurable via `-F` or `FS`.

## 2. First contact: minimal examples

### 2.1 Print every line

bash

```
awk '{ print }' file
```

* No pattern → action runs on every line.

* `print` with no arguments → prints the whole line (`$0`).

### 2.2 Print specific columns

bash

```
awk '{ print $1 }' file        # first column
awk '{ print $1, $3 }' file    # first and third columns
awk '{ print $NF }' file       # last column
```

* `$1`, `$2`, … → numbered fields.

* `$0` → entire line.

* `$NF` → “number of fields” → last field.

### 2.3 Filter by pattern

bash

```
awk '/error/' logfile          # print lines containing "error"
awk '/Failed password/ { print $11 }' auth.log
```

* Pattern only → default action is `print $0`.

* Pattern + action → run action only on matching lines.

## 3. Records, fields, and separators

### 3.1 Field separator (`FS` / `-F`)

By default, AWK splits on whitespace. For structured files, you often set a custom separator:

bash

```
awk -F: '{ print $1, $3 }' /etc/passwd   # colon-separated
awk -F',' '{ print $1, $2 }' data.csv    # comma-separated
```

* `-F` sets the **input field separator**.

* Internally, this is `FS`.

### 3.2 Output field separator (`OFS`)

When you print multiple fields, AWK joins them with `OFS` (default: space):

bash

```
awk -F: 'BEGIN { OFS=" -> " } { print $1, $3 }' /etc/passwd
```

* `BEGIN` block runs once before any input.

* `OFS` controls how `print` separates fields.

## 4. The pattern–action structure

### 4.1 General shape

bash

```
awk 'pattern { action }' file
```

Variants:

* **Only action:** `{ action }` → run on every line.

* **Only pattern:** `pattern` → print matching lines.

* **Multiple rules:** AWK can have many `pattern { action }` blocks; all are checked for each line.

### 4.2 Common patterns

* **Regex:** `/error/` → lines containing “error”.

* **Relational:** `$3 > 100` → numeric comparison on field 3.

* **Range:** `/start/,/end/` → lines between two patterns.

Example:

bash

```
awk '$3 > 100 { print $1, $3 }' data.txt
```

## 5. Special blocks: `BEGIN` and `END`

These are “meta‑rules”:

bash

```
awk '
BEGIN { print "Header" }
      { print $1, $2 }
END   { print "Done" }
' file
```

* `BEGIN`: runs once before reading input (setup, headers, FS/OFS).

* Main block: runs for each record.

* `END`: runs once after all input (totals, summaries).

## 6. Built‑in variables you’ll use constantly

Some of the most useful:

* `NR` – current record (line) number.

* `NF` – number of fields in current record.

* `FILENAME` – current file name.

* `FNR` – record number within current file.

Examples:

bash

```
awk '{ print NR, $0 }' file          # prefix each line with its number
awk 'NF == 0' file                   # print empty lines
awk 'NF > 5' file                    # lines with more than 5 fields
```

## 7. Actions: `print`, `printf`, and control flow

### 7.1 `print`

* Simple, automatic spacing via `OFS`.

* Good for quick column extraction.

bash

```
awk '{ print $1, $2 }' file
```

### 7.2 `printf`

* C‑style formatting, no automatic newline:

bash

```
awk '{ printf "%-10s %5d\n", $1, $2 }' file
```

### 7.3 Control statements

Inside actions, you can use:

* `if`, `else`

* `while`, `for`

* `next` – skip to next record.

* `exit` – stop processing early.

Example:

bash

```
awk '$3 < 0 { next } { print $1, $3 }' file   # skip negative values
```

## 8. Associative arrays (the secret weapon)

AWK’s arrays are **associative**: keys are strings, not just numbers. Perfect for counting and grouping in one pass.

### 8.1 Counting occurrences

bash

```
awk '
{ count[$1]++ }           # increment bucket for field 1
END {
    for (k in count)
        print k, count[k]
}
' file
```

Use cases:

* Count IPs in logs.

* Count usernames, status codes, etc.

## 9. String functions and text surgery

Common built‑ins:

* `length(s)` – length of string.

* `substr(s, start, len)` – substring.

* `split(s, arr, sep)` – split into array.

* `sub(regex, repl, s)` – replace first match.

* `gsub(regex, repl, s)` – replace all matches.

* `tolower(s)`, `toupper(s)` – case conversion.

Example:

bash

```
echo "User: Karl" | awk '{ sub("User: ", "", $0); print $0 }'
# -> Karl
```

## 10. AWK in pipelines and scripts

### 10.1 In pipelines

bash

```
journalctl -u ssh.service |
awk '/Failed password/ { print $11 }'
```

* AWK happily reads from stdin.

* Great for log parsing and quick reports.

### 10.2 From a file (`-f`)

Put your program in `script.awk`:

awk

```
# script.awk
BEGIN { OFS="," }
{ print $1, $3 }
```

Run:

bash

```
awk -f script.awk data.txt
```

## 11. Passing shell variables into AWK

Use `-v` to avoid quoting hell:

bash

```
limit=40000
awk -v lim="$limit" '$4 > lim { print $1, $4 }' salaries.txt
```

* `-v lim="$limit"` defines an AWK variable `lim` before processing.

* Safer than embedding shell variables directly in the program string.

## 12. Zettelkasten‑friendly summary

**Core pattern:**

bash

```
awk 'pattern { action }' file
```

**Always remember:**

* **Input is records (lines).**

* **Records are split into fields (**`$1`**,&#x20;**`$2`**, …,&#x20;**`$NF`**,&#x20;**`$0`**).**

* **Patterns decide&#x20;**_**which**_**&#x20;lines; actions decide&#x20;**_**what**_**&#x20;to do.**

* `BEGIN`**/**`END`**&#x20;wrap setup and summary.**

* **Associative arrays = one‑pass counting/grouping.**

If you want, I can help you turn this into a series of smaller Zettelkasten notes—each focusing on one concept (patterns, fields, arrays, etc.) with your own examples.

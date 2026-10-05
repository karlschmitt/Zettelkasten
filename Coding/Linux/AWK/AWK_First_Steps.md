---
id: 20260929191236
title: AWK First Steps
author: Karl Schmitt
date: 2026-09-29
keywords: [ AWK ]
---

# AWK: An Absolute Beginner's Tutorial

Welcome to your first steps with **AWK**, a powerful text-processing programming language found by default on almost every Unix and Linux system. If you ever need to slice, dice, filter, or reformat text files, logs, or CSVs, AWK is your best friend.



## What is AWK?

Think of AWK as a specialized tool designed to read text line by line, split each line into smaller pieces (called **fields**), let you perform operations on those pieces, and print the results.



The name "AWK" comes from the last names of its creators: Alfred **A**ho, Peter **W**einberger, and Brian **K**ernighan.



## How AWK Views the World

By default, AWK looks at text files through a very specific lens:



1. **Records (Rows):** By default, AWK reads a file one line at a time. Each line is called a record.



2. **Fields (Columns):** AWK automatically splits each line into separate words or columns based on whitespace (spaces or tabs).



   * The first column is called `$1`.


   * The second column is called `$2`.


   * And so on...


   * **`$0`** represents the entire line.



## Your First AWK Command

Let's imagine you have a text file named `fruits.txt` with the following content:



```
apple red 10
banana yellow 5
grape purple 15
```

To print just the first column (the fruit names), run this command in your terminal:



```
awk '{print $1}' fruits.txt
```

**Output:**



```
apple
banana
grape
```

### What just happened?

* `awk`: Calls the AWK program.


* `'...'`: Encloses your AWK program (always put it in single quotes).


* `{print $1}`: The action block. For every line, print field number 1.


* `fruits.txt`: The input file.



## Printing Multiple Fields

You can print multiple columns by separating them with commas.



```
awk '{print $1, $3}' fruits.txt
```

**Output:**



```
apple 10
banana 5
grape 15
```

_(Notice that AWK automatically inserts a space between the columns when you use a comma.)_



## Changing the Field Separator (`-F`)

What if your file isn't separated by spaces, but by commas (like a CSV file) or colons (like `/etc/passwd`)?



Meet the `-F` flag, which lets you define a custom **Field Separator**.



Imagine `prices.csv`:



```
Item,Price,Quantity
Apple,$1.20,10
Banana,$0.50,25
```

To print the item and its price using a comma as the separator:



```
awk -F',' '{print $1, $2}' prices.csv
```

**Output:**



```
Item Price
Apple $1.20
Banana $0.50
```

## Filtering Text with Patterns

AWK isn't just for printing; it's also amazing at filtering. You can tell AWK to only run an action if a condition is met.



### Example 1: Match a specific word

Let's print lines from `fruits.txt` where the second column is `yellow`:



```
awk '$2 == "yellow" {print $1}' fruits.txt
```

**Output:**



```
banana
```

### Example 2: Numeric comparisons

Let's print fruits where the quantity (the 3rd column) is greater than 8:



```
awk '$3 > 8 {print $1, "has quantity", $3}' fruits.txt
```

**Output:**



```
apple has quantity 10
grape has quantity 15
```

## Special Blocks: `BEGIN` and `END`

Sometimes you want to run code _before_ AWK reads the file (like printing a header) or _after_ AWK finishes reading the file (like printing a total summary).



You can use `BEGIN { ... }` and `END { ... }` blocks for this!



```
awk 'BEGIN { print "--- START OF REPORT ---" } { print $1 } END { print "--- END OF REPORT ---" }' fruits.txt
```

**Output:**



```
--- START OF REPORT ---
apple
banana
grape
--- END OF REPORT ---
```

## Summary Cheat Sheet

|                                    |                                                         |
| ---------------------------------- | ------------------------------------------------------- |
| **Command / Concept**              | **What it does**                                        |
| `awk '{print $0}' file.txt`        | Prints every line of the file.                          |
| `awk '{print $1, $2}' file.txt`    | Prints the 1st and 2nd columns.                         |
| `awk -F':' '{print $1}' file.txt`  | Uses a colon `:` as the column separator.               |
| `awk '$2 == "match"' file.txt`     | Prints lines where column 2 equals `"match"`.           |
| `BEGIN { ... } END { ... }`        | Code blocks that run before and after file processing.  |

## Next Steps

Now that you know the basics, try practicing on a real log file or system file on your computer (like `cat /etc/passwd | awk -F':' '{print $1}'`). Happy scripting!

Edit directly or with Gemini

Click anywhere to type and edit directly, or select text to prompt Gemini for changes.

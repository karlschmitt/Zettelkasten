---
id: 20260929195942
title: Absolute Beginner AWK Tutorial
author: Karl Schmitt
date: 2026-09-29
---



> [NOTE!]
> Diese Quelle bietet eine umfassende Einführung in die Programmiersprache **AWK** und richtet sich an absolute Anfänger, die das Verarbeiten von Textdateien, Spalten und einfachen Berichten erlernen möchten. Das Tutorial erklärt grundlegende Konzepte wie **Datensätze**, **Felder**, **Muster** sowie **Aktionen** und demonstriert deren praktische Anwendung an Beispielen wie Log-Dateien oder CSV-Daten. Darüber hinaus werden fortgeschrittene Themen wie **Kontrollstrukturen**, **assoziative Arrays** und **benutzerdefinierte Skripte** behandelt, um strukturierte Auswertungen zu ermöglichen. Das Dokument schließt mit einer nützlichen Übersicht sowie praxisnahen Übungen ab, um den Lernfortschritt gezielt zu unterstützen.


# Absolute Beginner AWK Tutorial

> **Goal:** Learn AWK from zero and become comfortable processing text files, columns, patterns, and simple reports.
>
> **Environment:** Windows 11 + PowerShell. We will use AWK from the command line and avoid Unix-specific assumptions where possible.

***

## 1. What is AWK?

**AWK** is a small programming language designed for processing **text**.

It is especially good at working with structured text such as:

```text
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
```

For example, AWK can easily print the second column:

```text
25
31
22
```

Or calculate an average:

```text
26
```

AWK is therefore often used for:

* Log-file analysis

* CSV-like data

* Text filtering

* Extracting columns

* Searching for patterns

* Generating reports

* Simple calculations

* Command-line automation

***

# 2. Why is AWK called AWK?

AWK was created by:

* **A**lfred Aho

* **P**eter Weinberger

* **B**rian Kernighan

The name **AWK** comes from their surnames.

AWK first appeared in the 1970s and became an important Unix text-processing tool.

***

# 3. The basic idea

The fundamental AWK model is:

```text
INPUT
  ↓
read a line
  ↓
split the line into fields
  ↓
test a pattern
  ↓
execute an action
  ↓
read the next line
```

You can think of AWK as:

```text
for each line:
    if the line matches:
        do something
```

This is the most important concept to understand.

***

# 4. A first AWK program

Suppose we have this file:

```text
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
```

Call it:

```text
people.txt
```

An AWK command can look like this:

```powershell
awk '{ print $1 }' people.txt
```

The result is:

```text
Alice
Bob
Charlie
```

Congratulations! 🎉

You have written your first AWK program.

***

# 5. Understanding `{ print $1 }`

Let's break this down:

```text
{ print $1 }
```

The `{ }` contain the **action**.

```text
print
```

means:

> Print something.

And:

```text
$1
```

means:

> The first field of the current line.

Therefore:

```text
{ print $1 }
```

means:

> Print the first column.

***

# 6. AWK fields

Given this line:

```text
Alice 25 Berlin
```

AWK normally sees:

```text
$1       $2       $3
Alice    25       Berlin
```

There is also:

```text
$0
```

which means:

> The entire current line.

So:

```text
$0
```

is:

```text
Alice 25 Berlin
```

while:

```text
$1
```

is:

```text
Alice
```

and:

```text
$2
```

is:

```text
25
```

and:

```text
$3
```

is:

```text
Berlin
```

***

# 7. The most important AWK variables

| AWK variable | Meaning                    |
| ------------ | -------------------------- |
| `$0`         | Entire current line        |
| `$1`         | First field                |
| `$2`         | Second field               |
| `$3`         | Third field                |
| `$NF`        | Last field                 |
| `NF`         | Number of fields           |
| `NR`         | Current record/line number |
| `FS`         | Input field separator      |
| `OFS`        | Output field separator     |

These variables are extremely important.

***

# 8. Printing different columns

Print the first column:

```powershell
awk '{ print $1 }' people.txt
```

Print the second:

```powershell
awk '{ print $2 }' people.txt
```

Print the third:

```powershell
awk '{ print $3 }' people.txt
```

Print the first and third:

```powershell
awk '{ print $1, $3 }' people.txt
```

Result:

```text
Alice Berlin
Bob Hamburg
Charlie Munich
```

***

# 9. Printing the entire line

Use:

```powershell
awk '{ print $0 }' people.txt
```

Result:

```text
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
```

In fact:

```powershell
awk '{ print }' people.txt
```

does the same thing.

***

# 10. The last column

AWK provides a very useful variable:

```text
$NF
```

`NF` means:

> Number of Fields

Therefore:

```text
$NF
```

means:

> The last field.

For:

```text
Alice 25 Berlin
```

we have:

```text
NF = 3
```

and therefore:

```text
$NF = $3
```

So:

```powershell
awk '{ print $NF }' people.txt
```

produces:

```text
Berlin
Hamburg
Munich
```

***

# 11. Counting fields with `NF`

Try:

```powershell
awk '{ print NF }' people.txt
```

Output:

```text
3
3
3
```

Each line contains three fields.

***

# 12. Counting lines with `NR`

`NR` means:

> Number of Records

For normal text processing, you can think of it as the current line number.

Run:

```powershell
awk '{ print NR, $0 }' people.txt
```

Output:

```text
1 Alice 25 Berlin
2 Bob 31 Hamburg
3 Charlie 22 Munich
```

This is very useful when investigating files.

***

# 13. Patterns

So far we have only used:

```text
{ action }
```

But AWK can also use:

```text
pattern { action }
```

For example:

```powershell
awk '$2 > 25 { print $1 }' people.txt
```

Output:

```text
Bob
```

The pattern is:

```text
$2 > 25
```

The action is:

```text
{ print $1 }
```

AWK asks for every line:

```text
Is column 2 greater than 25?
```

If yes:

```text
print column 1
```

***

# 14. Another pattern

Find people from Berlin:

```powershell
awk '$3 == "Berlin" { print $1 }' people.txt
```

Result:

```text
Alice
```

The operator:

```text
==
```

means:

> is equal to

***

# 15. Comparison operators

AWK supports familiar comparison operators.

| Operator | Meaning               |
| -------- | --------------------- |
| `==`     | Equal                 |
| `!=`     | Not equal             |
| `>`      | Greater than          |
| `<`      | Less than             |
| `>=`     | Greater than or equal |
| `<=`     | Less than or equal    |

Examples:

```awk
$2 > 25
```

```awk
$2 < 30
```

```awk
$3 == "Berlin"
```

```awk
$3 != "Berlin"
```

***

# 16. Logical operators

You can combine conditions.

### AND

```awk
$2 > 20 && $2 < 30
```

Means:

```text
age > 20 AND age < 30
```

### OR

```awk
$3 == "Berlin" || $3 == "Hamburg"
```

Means:

```text
Berlin OR Hamburg
```

### NOT

```awk
!($3 == "Berlin")
```

Means:

```text
NOT Berlin
```

***

# 17. `BEGIN`

AWK has a special section called:

```text
BEGIN
```

It runs **before the first input line**.

Example:

```powershell
awk 'BEGIN { print "People:" } { print $1 }' people.txt
```

Output:

```text
People:
Alice
Bob
Charlie
```

Think of:

```text
BEGIN
```

as:

> Do this before processing the file.

***

# 18. `END`

There is also:

```text
END
```

It runs **after the last input line**.

Example:

```powershell
awk '{ total += $2 } END { print total }' people.txt
```

Output:

```text
78
```

AWK adds:

```text
25 + 31 + 22
```

***

# 19. AWK's basic structure

A typical AWK program can therefore look like:

```awk
BEGIN {
    # initialization
}

pattern {
    # process input
}

END {
    # final calculation
}
```

For example:

```powershell
awk '
BEGIN {
    print "People"
}
{
    print $1
}
END {
    print "Finished"
}
' people.txt
```

***

# 20. Variables

AWK supports variables.

Example:

```powershell
awk '
{
    total = total + $2
}
END {
    print total
}
' people.txt
```

You can also use the shorter form:

```text
total += $2
```

So:

```powershell
awk '
{
    total += $2
}
END {
    print total
}
' people.txt
```

***

# 21. Calculating an average

We can calculate the average age.

```powershell
awk '
{
    total += $2
}
END {
    print total / NR
}
' people.txt
```

The calculation is:

```text
(25 + 31 + 22) / 3
```

Result:

```text
26
```

***

# 22. Formatting output

AWK supports:

```text
printf
```

For example:

```powershell
awk '{ printf "%s is %d years old\n", $1, $2 }' people.txt
```

Output:

```text
Alice is 25 years old
Bob is 31 years old
Charlie is 22 years old
```

`printf` gives you much more control over formatting than `print`.

***

# 23. Strings

AWK can work with strings.

For example:

```powershell
awk '{ print "Hello " $1 }' people.txt
```

Output:

```text
Hello Alice
Hello Bob
Hello Charlie
```

You can combine strings and fields:

```text
"Hello " $1
```

***

# 24. String comparison

You can write:

```powershell
awk '$1 == "Alice" { print $0 }' people.txt
```

Result:

```text
Alice 25 Berlin
```

***

# 25. Regular expressions

One of AWK's powerful features is pattern matching.

For example:

```powershell
awk '/Berlin/ { print $0 }' people.txt
```

Result:

```text
Alice 25 Berlin
```

The pattern:

```text
/Berlin/
```

means:

> Does this line contain "Berlin"?

***

# 26. Searching for text

Suppose we have:

```text
INFO Server started
ERROR Database unavailable
INFO User logged in
ERROR Connection failed
```

AWK can find errors:

```powershell
awk '/ERROR/ { print $0 }' application.log
```

Result:

```text
ERROR Database unavailable
ERROR Connection failed
```

This is one reason AWK is so useful for log files.

***

# 27. Negating a pattern

You can find lines that don't contain `ERROR`:

```powershell
awk '!/ERROR/ { print $0 }' application.log
```

***

# 28. Field separators

AWK normally assumes fields are separated by whitespace.

For:

```text
Alice 25 Berlin
```

AWK automatically recognizes:

```text
Alice
25
Berlin
```

But real-world data often uses:

```text
;
```

or:

```text
,
```

or:

```text
|
```

***

# 29. CSV-like data

Imagine:

```text
Alice,25,Berlin
Bob,31,Hamburg
Charlie,22,Munich
```

The separator is:

```text
,
```

We can tell AWK:

```powershell
awk -F',' '{ print $1 }' people.csv
```

Result:

```text
Alice
Bob
Charlie
```

`-F` means:

> Field separator

***

# 30. Semicolon-separated data

For:

```text
Alice;25;Berlin
Bob;31;Hamburg
Charlie;22;Munich
```

use:

```powershell
awk -F';' '{ print $1, $3 }' people.txt
```

Result:

```text
Alice Berlin
Bob Hamburg
Charlie Munich
```

***

# 31. Changing the output separator

By default:

```text
print $1, $3
```

uses a space between the fields.

You can change this with:

```text
OFS
```

For example:

```powershell
awk 'BEGIN { OFS=";" } { print $1, $3 }' people.txt
```

Result:

```text
Alice;Berlin
Bob;Hamburg
Charlie;Munich
```

***

# 32. Input separator vs output separator

This distinction is important.

### `FS`

Means:

```text
Field Separator
```

It tells AWK how to **read** fields.

### `OFS`

Means:

```text
Output Field Separator
```

It tells AWK how to **write** fields.

Think:

```text
FS  → input
OFS → output
```

***

# 33. A practical example

Let's create:

```text
employees.txt
```

with:

```text
Alice 25 Developer 60000
Bob 31 Manager 75000
Charlie 22 Tester 50000
Diana 45 Architect 90000
```

AWK sees:

```text
$1       $2   $3         $4
Alice    25   Developer  60000
Bob      31   Manager    75000
Charlie  22   Tester     50000
Diana    45   Architect  90000
```

***

# 34. Print employee names

```powershell
awk '{ print $1 }' employees.txt
```

***

# 35. Print names and salaries

```powershell
awk '{ print $1, $4 }' employees.txt
```

***

# 36. Find salaries greater than 70000

```powershell
awk '$4 > 70000 { print $1, $4 }' employees.txt
```

Result:

```text
Bob 75000
Diana 90000
```

***

# 37. Calculate total salaries

```powershell
awk '{ total += $4 } END { print total }' employees.txt
```

Result:

```text
275000
```

***

# 38. Calculate average salary

```powershell
awk '{ total += $4 } END { print total / NR }' employees.txt
```

Result:

```text
68750
```

***

# 39. Add a header

```powershell
awk '
BEGIN {
    print "Name Salary"
}
{
    print $1, $4
}
' employees.txt
```

Result:

```text
Name Salary
Alice 60000
Bob 75000
Charlie 50000
Diana 90000
```

***

# 40. AWK and PowerShell

Since you are working on Windows, an important question is:

> How do I actually get `awk`?

AWK is traditionally part of Unix-like environments.

Depending on your organization's environment, you may encounter AWK through tools such as:

* Git Bash

* MSYS2

* Cygwin

* WSL

* other Unix-compatible environments

For a Windows learning environment, **Git Bash** is often a convenient place to experiment with AWK if it is available in your installation.

You can check:

```bash
awk --version
```

or:

```bash
awk -W version
```

***

# 41. AWK is not a replacement for PowerShell

It is useful to understand the relationship.

PowerShell is a general-purpose shell and automation environment.

AWK is much more specialized.

For example:

```text
PowerShell
    ↓
general automation
files
processes
objects
.NET
Windows
APIs
```

while:

```text
AWK
    ↓
text processing
fields
patterns
reports
calculations
```

AWK's specialization is actually its strength.

***

# 42. AWK's programming model

A useful mental model is:

```text
             AWK
              │
       ┌──────┴──────┐
       │             │
    Pattern        Action
       │             │
 "Should I?"     "What do I do?"
```

For example:

```awk
$2 > 30 {
    print $1
}
```

means:

```text
Pattern:
    Is field 2 greater than 30?

Action:
    Print field 1.
```

***

# 43. Multiple rules

AWK allows multiple rules.

```powershell
awk '
$2 < 30 {
    print $1, "is younger than 30"
}

$2 >= 30 {
    print $1, "is 30 or older"
}
' people.txt
```

This demonstrates that an AWK program can contain multiple:

```text
pattern { action }
```

rules.

***

# 44. `if`

AWK also supports normal programming constructs.

For example:

```powershell
awk '
{
    if ($2 >= 30)
        print $1, "adult"
    else
        print $1, "young"
}
' people.txt
```

The general structure is:

```awk
if (condition) {
    ...
} else {
    ...
}
```

***

# 45. `for` loops

AWK supports loops.

For example:

```powershell
awk '
{
    for (i = 1; i <= NF; i++)
        print $i
}
' people.txt
```

For each line, AWK prints every field.

For:

```text
Alice 25 Berlin
```

it prints:

```text
Alice
25
Berlin
```

***

# 46. Arrays

AWK also has associative arrays.

For example:

```awk
cities["Alice"] = "Berlin"
```

An associative array works somewhat like a dictionary/map.

You can write:

```powershell
awk '
{
    city[$1] = $3
}
END {
    print city["Alice"]
}
' people.txt
```

Result:

```text
Berlin
```

***

# 47. Counting values

Arrays become particularly useful for counting.

Suppose:

```text
Alice Berlin
Bob Hamburg
Charlie Berlin
Diana Munich
Eve Berlin
```

We can count people per city:

```powershell
awk '
{
    count[$2]++
}
END {
    for (city in count)
        print city, count[city]
}
' people.txt
```

You might get:

```text
Berlin 3
Hamburg 1
Munich 1
```

The order of associative-array output is not something you should rely on.

***

# 48. A very useful log example

Suppose a log contains:

```text
INFO Application started
INFO User logged in
ERROR Database unavailable
INFO Request received
ERROR Connection failed
INFO Application stopped
```

Count errors:

```powershell
awk '/ERROR/ { count++ } END { print count }' application.log
```

Result:

```text
2
```

***

# 49. Count INFO messages

```powershell
awk '/INFO/ { count++ } END { print count }' application.log
```

Result:

```text
4
```

This is a very practical AWK pattern:

```text
/pattern/ {
    counter++
}

END {
    print counter
}
```

***

# 50. AWK comments

You can add comments with:

```awk
# This is a comment
```

Example:

```powershell
awk '
# Print names
{
    print $1
}
' people.txt
```

***

# 51. Putting AWK into a file

You don't have to put the entire program on the command line.

You can create:

```text
people.awk
```

with:

```awk
{
    print $1
}
```

Then execute it:

```bash
awk -f people.awk people.txt
```

The:

```text
-f
```

means:

> Read the AWK program from a file.

This becomes much more convenient as your AWK programs grow.

***

# 52. A complete AWK report

Let's create:

```text
employees.txt
```

```text
Alice 25 Developer 60000
Bob 31 Manager 75000
Charlie 22 Tester 50000
Diana 45 Architect 90000
```

Now create:

```text
report.awk
```

with:

```awk
BEGIN {
    print "EMPLOYEE REPORT"
    print "==============="
}

{
    total += $4

    printf "%-10s %-12s %8d\n", $1, $3, $4
}

END {
    print "==============="
    printf "Total: %d\n", total
    printf "Average: %.2f\n", total / NR
}
```

Run:

```bash
awk -f report.awk employees.txt
```

You have now created a small text-processing application.

***

# 53. AWK's built-in functions

AWK contains many useful functions.

For example:

```text
length()
```

gets the length of a string.

```powershell
awk '{ print $1, length($1) }' people.txt
```

***

# 54. `tolower()`

Convert text to lowercase:

```awk
tolower($1)
```

Example:

```powershell
awk '{ print tolower($1) }' people.txt
```

***

# 55. `toupper()`

Convert text to uppercase:

```powershell
awk '{ print toupper($1) }' people.txt
```

Result:

```text
ALICE
BOB
CHARLIE
```

***

# 56. `substr()`

Extract part of a string:

```awk
substr(string, start, length)
```

Example:

```powershell
awk '{ print substr($1, 1, 2) }' people.txt
```

Result:

```text
Al
Bo
Ch
```

***

# 57. `index()`

Find the position of text:

```awk
index("Hello World", "World")
```

Result:

```text
7
```

***

# 58. Mathematical functions

AWK also supports mathematical operations:

```text
+
-
*
/
%
```

For example:

```powershell
awk '{ print $2 * 12 }' people.txt
```

If `$2` is age, this would multiply the age by 12.

***

# 59. The modulo operator

The `%` operator gives the remainder.

For example:

```text
10 % 3
```

produces:

```text
1
```

This can be useful for determining whether a number is even:

```awk
$2 % 2 == 0
```

***

# 60. Headers

Real-world files often contain headers.

For example:

```text
Name Age City
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
```

We may want to skip the first line.

One way is:

```powershell
awk 'NR > 1 { print $1 }' people.txt
```

The condition:

```text
NR > 1
```

means:

> Process only lines after line 1.

***

# 61. Skip a header with `next`

Another common technique is:

```powershell
awk '
NR == 1 {
    next
}

{
    print $1
}
' people.txt
```

`next` means:

> Stop processing this line and continue with the next input line.

***

# 62. Important AWK concepts to remember

At this point, the most important concepts are:

```text
$0
$1
$2
$3
$NF
NF
NR
FS
OFS
BEGIN
END
```

Try to memorize this little table:

| Concept | Meaning             |
| ------- | ------------------- |
| `$0`    | Whole line          |
| `$1`    | First field         |
| `$2`    | Second field        |
| `$NF`   | Last field          |
| `NF`    | Number of fields    |
| `NR`    | Current line number |
| `FS`    | Input separator     |
| `OFS`   | Output separator    |
| `BEGIN` | Before input        |
| `END`   | After input         |

***

# 63. The AWK "sentence"

A very useful way to read AWK code is:

```awk
pattern {
    action
}
```

Read this as:

> **If this pattern matches, perform this action.**

For example:

```awk
$3 == "Berlin" {
    print $1
}
```

Read it as:

> If field 3 equals Berlin, print field 1.

This mental model will take you a long way.

***

# 64. AWK cheat sheet

## Print

```awk
{ print }
```

Print whole line.

```awk
{ print $1 }
```

Print first field.

```awk
{ print $1, $2 }
```

Print fields 1 and 2.

***

## Conditions

```awk
$2 > 10
```

```awk
$2 == 10
```

```awk
$2 != 10
```

```awk
$2 >= 10
```

***

## Text matching

```awk
/ERROR/
```

```awk
!/ERROR/
```

***

## Counters

```awk
count++
```

***

## Sum

```awk
total += $2
```

***

## Number of fields

```awk
NF
```

***

## Line number

```awk
NR
```

***

## Last field

```awk
$NF
```

***

## Input separator

```awk
FS=","
```

or:

```bash
awk -F',' '...'
```

***

## Output separator

```awk
OFS=","
```

***

## Start

```awk
BEGIN {
}
```

***

## Finish

```awk
END {
}
```

***

# 65. A good AWK learning progression

I recommend learning AWK in this order:

```text
Level 1
│
├── $0
├── $1
├── $2
├── $NF
│
Level 2
│
├── print
├── NR
├── NF
│
Level 3
│
├── patterns
├── comparisons
├── regular expressions
│
Level 4
│
├── BEGIN
├── END
├── variables
│
Level 5
│
├── FS
├── OFS
├── CSV/text formats
│
Level 6
│
├── if
├── for
├── while
│
Level 7
│
├── arrays
├── functions
├── reports
│
Level 8
│
└── real-world log processing
```

Don't try to memorize everything at once.

***

# 66. Absolute Beginner Exercises

## Exercise 1 — Print names

Given:

```text
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
```

Write an AWK command that prints:

```text
Alice
Bob
Charlie
```

**Solution:**

```bash
awk '{ print $1 }' people.txt
```

***

## Exercise 2 — Print cities

Expected:

```text
Berlin
Hamburg
Munich
```

**Solution:**

```bash
awk '{ print $3 }' people.txt
```

***

## Exercise 3 — Print names and ages

Expected:

```text
Alice 25
Bob 31
Charlie 22
```

**Solution:**

```bash
awk '{ print $1, $2 }' people.txt
```

***

## Exercise 4 — Find people older than 25

Expected:

```text
Bob
```

**Solution:**

```bash
awk '$2 > 25 { print $1 }' people.txt
```

***

## Exercise 5 — Find Berlin

Expected:

```text
Alice
```

**Solution:**

```bash
awk '$3 == "Berlin" { print $1 }' people.txt
```

***

## Exercise 6 — Count people

**Solution:**

```bash
awk 'END { print NR }' people.txt
```

***

## Exercise 7 — Calculate total age

**Solution:**

```bash
awk '{ total += $2 } END { print total }' people.txt
```

***

## Exercise 8 — Calculate average age

**Solution:**

```bash
awk '{ total += $2 } END { print total / NR }' people.txt
```

***

# 67. Mini Project — AWK Log Analyzer

Let's finish with a small project.

Create:

```text
application.log
```

containing:

```text
INFO Application started
INFO User Alice logged in
ERROR Database unavailable
INFO User Bob logged in
WARN Disk space low
ERROR Connection failed
INFO Application stopped
```

Your goal is to create a report:

```text
Log Report
----------
INFO: 4
WARN: 1
ERROR: 2
TOTAL: 7
```

An AWK solution could be:

```awk
{
    count[$1]++
    total++
}

END {
    print "Log Report"
    print "----------"
    print "INFO:", count["INFO"]
    print "WARN:", count["WARN"]
    print "ERROR:", count["ERROR"]
    print "TOTAL:", total
}
```

Save it as:

```text
logreport.awk
```

Then:

```bash
awk -f logreport.awk application.log
```

This little project introduces several important AWK concepts at once:

```text
$1
arrays
++
END
print
variables
```

***

# 68. The big picture

If you remember only one thing from this tutorial, remember this:

```text
AWK processes text one record at a time.
```

For every input line:

```text
┌─────────────────────────────┐
│        Input line            │
│ Alice 25 Berlin              │
└──────────────┬──────────────┘
               │
               ▼
       ┌───────────────┐
       │ Split fields  │
       └───────┬───────┘
               │
       ┌───────┼────────┐
       ▼       ▼        ▼
      $1      $2       $3
    Alice     25      Berlin
       │
       ▼
 ┌───────────────┐
 │ Check pattern │
 └───────┬───────┘
         │
         ▼
 ┌───────────────┐
 │ Perform action│
 │  print $1     │
 └───────────────┘
```

And the fundamental AWK structure is:

```awk
pattern {
    action
}
```

Once this becomes natural, AWK starts to become surprisingly powerful.

***

# 69. Your AWK beginner vocabulary

| Term                   | Meaning                                      |
| ---------------------- | -------------------------------------------- |
| **record**             | Usually one input line                       |
| **field**              | A piece of a record                          |
| **pattern**            | Condition determining whether a rule applies |
| **action**             | Code executed when a pattern matches         |
| **`$0`**               | Entire record                                |
| **`$1`**               | First field                                  |
| **`$NF`**              | Last field                                   |
| **`NF`**               | Number of fields                             |
| **`NR`**               | Current record number                        |
| **`FS`**               | Field separator                              |
| **`OFS`**              | Output field separator                       |
| **`BEGIN`**            | Initialization code                          |
| **`END`**              | Finalization code                            |
| **array**              | Key/value data structure                     |
| **regular expression** | Pattern used to search text                  |

***

# 70. Suggested next step

For your learning style, I would turn this into a **7-Day AWK Absolute Beginner Bootcamp**:

```text
Day 1  → AWK fundamentals and fields
Day 2  → Patterns and conditions
Day 3  → BEGIN, END and variables
Day 4  → Text processing and regular expressions
Day 5  → CSV, FS and OFS
Day 6  → Arrays, loops and functions
Day 7  → Real-world log analyzer project
```

That would give you a much more hands-on progression from:

```text
awk '{ print $1 }'
```

all the way to a useful **log-analysis/reporting program**.

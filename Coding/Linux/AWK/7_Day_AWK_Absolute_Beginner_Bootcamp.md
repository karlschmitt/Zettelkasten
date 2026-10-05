---
id: 20260929204846
title: 7-Day AWK Absolute Beginner Bootcamp
author: Karl Schmitt
date: 2026-09-29
---

# 7-Day AWK Absolute Beginner Bootcamp

Absolutely! 😊 Since you like hands-on bootcamps, here is a **7-Day AWK Absolute Beginner Bootcamp** designed to take you from your very first AWK command to a small real-world log analyzer.

# AWK Absolute Beginner Bootcamp — 7 Days

> **Goal:** By the end of Day 7, you will be able to read text files, extract columns, filter data, calculate statistics, use regular expressions, work with CSV files, use arrays and loops, and build a practical AWK log analyzer.

## 🧰 Environment

We will keep the toolchain deliberately small:

```text
Windows 11
    │
    ├── PowerShell
    ├── Visual Studio Code
    └── AWK
```

If AWK is available through your Git Bash installation, you can run the exercises there.

Check:

```bash
awk --version
```

or:

```bash
awk -W version
```

***

# 🗺️ Bootcamp Roadmap

| Day       | Topic                      | Main Skills                           |
| --------- | -------------------------- | ------------------------------------- |
| **Day 1** | AWK Fundamentals           | `$0`, `$1`, `$2`, `$NF`, `print`      |
| **Day 2** | Patterns & Conditions      | comparisons, filtering, `if`          |
| **Day 3** | Variables & Calculations   | variables, `NR`, `NF`, `BEGIN`, `END` |
| **Day 4** | Text & Regular Expressions | searching, strings, regex             |
| **Day 5** | CSV & Field Separators     | `FS`, `OFS`, CSV processing           |
| **Day 6** | Programming with AWK       | loops, arrays, functions              |
| **Day 7** | Final Project              | Log Analyzer                          |

***

# Day 1 — AWK Fundamentals

## 🎯 Goal

Understand the most important AWK concept:

> **AWK reads input one line at a time and gives you access to the individual fields.**

***

## 1. Create your training directory

In PowerShell:

```powershell
mkdir awk-bootcamp
cd awk-bootcamp
```

Create a directory for Day 1:

```powershell
mkdir day1
cd day1
```

***

# 2. Create `people.txt`

In VS Code create:

```text
people.txt
```

with:

```text
Alice 25 Berlin
Bob 31 Hamburg
Charlie 22 Munich
Diana 45 Frankfurt
Eric 29 Cologne
```

***

# 3. Your first AWK command

Run:

```bash
awk '{ print $1 }' people.txt
```

Expected:

```text
Alice
Bob
Charlie
Diana
Eric
```

Congratulations. 🎉

You've written an AWK program.

***

# 4. Understand `$1`

AWK sees:

```text
Alice 25 Berlin
```

as:

```text
$1       $2       $3
Alice    25       Berlin
```

So:

```awk
$1
```

means:

> First field.

***

# 5. Experiment

Try:

```bash
awk '{ print $2 }' people.txt
```

Then:

```bash
awk '{ print $3 }' people.txt
```

Then:

```bash
awk '{ print $1, $3 }' people.txt
```

***

# 6. `$0`

Try:

```bash
awk '{ print $0 }' people.txt
```

`$0` means:

> The complete current line.

***

# 7. `$NF`

Now try:

```bash
awk '{ print $NF }' people.txt
```

`NF` means:

> Number of fields.

Therefore:

```text
$NF
```

means:

> Last field.

***

# 8. `NF`

Try:

```bash
awk '{ print NF }' people.txt
```

You should get:

```text
3
3
3
3
3
```

Every line contains three fields.

***

# 9. `NR`

Try:

```bash
awk '{ print NR, $0 }' people.txt
```

Result:

```text
1 Alice 25 Berlin
2 Bob 31 Hamburg
3 Charlie 22 Munich
4 Diana 45 Frankfurt
5 Eric 29 Cologne
```

`NR` means:

> Current record number.

For normal text processing, you can think of it as the line number.

***

# 🧪 Day 1 Exercises

### Exercise 1

Print only the names.

```text
Alice
Bob
Charlie
Diana
Eric
```

### Exercise 2

Print:

```text
Alice Berlin
Bob Hamburg
...
```

### Exercise 3

Print the line number followed by the name.

```text
1 Alice
2 Bob
3 Charlie
...
```

### Exercise 4

Print the last field.

***

## 🧠 Day 1 Cheat Sheet

```text
$0     entire line
$1     first field
$2     second field
$3     third field
$NF    last field
NF     number of fields
NR     current record number
```

***

# Day 2 — Patterns & Conditions

## 🎯 Goal

Learn to tell AWK:

> "Only process this line if it satisfies this condition."

***

# 1. Filter people by age

Run:

```bash
awk '$2 > 30 { print $1 }' people.txt
```

Result:

```text
Bob
Diana
```

The AWK structure is:

```awk
pattern {
    action
}
```

In our example:

```awk
$2 > 30 {
    print $1
}
```

Read it as:

> If field 2 is greater than 30, print field 1.

***

# 2. Comparison operators

Learn these:

```text
==     equal
!=     not equal
>      greater
<      less
>=     greater or equal
<=     less or equal
```

Examples:

```bash
awk '$2 == 25 { print $1 }' people.txt
```

```bash
awk '$2 < 30 { print $1 }' people.txt
```

```bash
awk '$2 >= 30 { print $1 }' people.txt
```

***

# 3. String comparison

Find people from Berlin:

```bash
awk '$3 == "Berlin" { print $1 }' people.txt
```

***

# 4. Regular expression pattern

Try:

```bash
awk '/Berlin/ { print $0 }' people.txt
```

This means:

> Print lines containing `Berlin`.

***

# 5. NOT

Try:

```bash
awk '!/Berlin/ { print $0 }' people.txt
```

This means:

> Print lines that don't contain Berlin.

***

# 6. Logical AND

Find people between 25 and 40:

```bash
awk '$2 >= 25 && $2 <= 40 { print $1 }' people.txt
```

***

# 7. Logical OR

Find people from Berlin or Hamburg:

```bash
awk '$3 == "Berlin" || $3 == "Hamburg" { print $1 }' people.txt
```

***

# 8. `if`

AWK is also a programming language.

```bash
awk '
{
    if ($2 >= 30)
        print $1, "30 or older"
    else
        print $1, "younger than 30"
}
' people.txt
```

***

# 🧪 Day 2 Exercises

1. Find everyone older than 25.

2. Find everyone younger than 30.

3. Find everyone from Munich.

4. Find everyone **not** from Berlin.

5. Find people aged between 20 and 30.

6. Print `adult` if age >= 30, otherwise `young`.

***

# Day 3 — Variables, BEGIN and END

## 🎯 Goal

Move from simple filtering into calculations.

***

# 1. Variables

Create:

```bash
awk '
{
    total = total + $2
}
END {
    print total
}
' people.txt
```

You can shorten:

```awk
total += $2
```

So:

```bash
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

# 2. Calculate average age

```bash
awk '
{
    total += $2
}
END {
    print total / NR
}
' people.txt
```

***

# 3. `BEGIN`

`BEGIN` runs before processing the file.

```bash
awk '
BEGIN {
    print "PEOPLE"
    print "======"
}
{
    print $1
}
' people.txt
```

***

# 4. `END`

`END` runs after processing the file.

```bash
awk '
{
    total += $2
}
END {
    print "Total:", total
}
' people.txt
```

***

# 5. Complete report

```bash
awk '
BEGIN {
    print "PEOPLE REPORT"
    print "-------------"
}
{
    total += $2
    print $1, $2
}
END {
    print "-------------"
    print "Total age:", total
    print "Average:", total / NR
}
' people.txt
```

***

# 6. `printf`

For more control:

```bash
awk '
{
    printf "%-10s %3d\n", $1, $2
}
' people.txt
```

***

# 🧪 Day 3 Exercises

Create:

```text
products.txt
```

```text
Laptop 1200
Monitor 400
Keyboard 80
Mouse 30
Headset 100
```

Then:

1. Print product names.

2. Print product prices.

3. Calculate total price.

4. Calculate average price.

5. Find products above 100.

6. Create a formatted report.

***

# Day 4 — Strings & Regular Expressions

## 🎯 Goal

Learn how AWK can search and manipulate text.

Create:

```text
application.log
```

```text
INFO Application started
INFO User Alice logged in
WARN Disk space low
ERROR Database unavailable
INFO User Bob logged in
ERROR Connection failed
INFO Application stopped
```

***

# 1. Find errors

```bash
awk '/ERROR/ { print $0 }' application.log
```

***

# 2. Find warnings

```bash
awk '/WARN/ { print $0 }' application.log
```

***

# 3. Count errors

```bash
awk '/ERROR/ { count++ } END { print count }' application.log
```

***

# 4. Count INFO messages

```bash
awk '/INFO/ { count++ } END { print count }' application.log
```

***

# 5. `toupper()`

```bash
awk '{ print toupper($1) }' application.log
```

***

# 6. `tolower()`

```bash
awk '{ print tolower($1) }' application.log
```

***

# 7. `length()`

```bash
awk '{ print length($0), $0 }' application.log
```

***

# 8. `substr()`

Try:

```bash
awk '{ print substr($1, 1, 2) }' application.log
```

***

# 9. Combining conditions

Find lines containing `User`:

```bash
awk '/User/ { print $0 }' application.log
```

Find lines containing either `ERROR` or `WARN`:

```bash
awk '/ERROR|WARN/ { print $0 }' application.log
```

***

# 🧪 Day 4 Exercises

Build a small log report:

```text
INFO messages: ?
WARN messages: ?
ERROR messages: ?
```

Hint:

```awk
/INFO/  { info++ }
```

and:

```awk
END {
    print "INFO:", info
}
```

***

# Day 5 — CSV and Field Separators

## 🎯 Goal

Learn how AWK handles structured data that isn't separated by spaces.

***

# 1. Create `employees.csv`

```text
Name,Age,City,Department,Salary
Alice,25,Berlin,Development,60000
Bob,31,Hamburg,Management,75000
Charlie,22,Munich,Testing,50000
Diana,45,Frankfurt,Architecture,90000
Eric,29,Cologne,Development,65000
```

***

# 2. The problem

If we simply execute:

```bash
awk '{ print $1 }' employees.csv
```

AWK won't treat commas as field separators.

We need:

```text
-F
```

***

# 3. CSV field separator

Run:

```bash
awk -F',' '{ print $1 }' employees.csv
```

Result:

```text
Name
Alice
Bob
Charlie
Diana
Eric
```

Now:

```text
$1
$2
$3
$4
$5
```

represent:

```text
Name
Age
City
Department
Salary
```

***

# 4. Skip the header

```bash
awk -F',' 'NR > 1 { print $1, $5 }' employees.csv
```

***

# 5. Find high salaries

```bash
awk -F',' 'NR > 1 && $5 > 70000 { print $1, $5 }' employees.csv
```

***

# 6. Calculate total salaries

```bash
awk -F',' '
NR > 1 {
    total += $5
}
END {
    print total
}
' employees.csv
```

***

# 7. `OFS`

Let's output CSV:

```bash
awk -F',' '
BEGIN {
    OFS=","
}
NR > 1 {
    print $1, $3, $5
}
' employees.csv
```

Result:

```text
Alice,Berlin,60000
Bob,Hamburg,75000
Charlie,Munich,50000
Diana,Frankfurt,90000
Eric,Cologne,65000
```

***

# 🧪 Day 5 Exercises

1. Print names and cities.

2. Print names and departments.

3. Find salaries above 60000.

4. Calculate total salary.

5. Calculate average salary.

6. Output a new CSV containing only:

```text
Name,City,Salary
```

***

# Day 6 — AWK Programming

## 🎯 Goal

Today AWK becomes a real programming language.

You'll learn:

```text
if
for
while
arrays
functions
```

***

# 1. `for`

Print every field individually:

```bash
awk '
{
    for (i = 1; i <= NF; i++)
        print $i
}
' people.txt
```

***

# 2. A better way to understand `for`

This:

```awk
for (i = 1; i <= NF; i++)
```

means:

```text
i starts at 1

while i <= number of fields:

    do something

    increase i
```

***

# 3. Arrays

Suppose:

```text
Alice Berlin
Bob Hamburg
Charlie Berlin
Diana Munich
Eric Berlin
```

We can count cities:

```bash
awk '
{
    city[$2]++
}
END {
    for (c in city)
        print c, city[c]
}
' cities.txt
```

Possible result:

```text
Berlin 3
Hamburg 1
Munich 1
```

***

# 4. Understanding the array

This:

```awk
city[$2]++
```

means:

> Find the array element whose key is the current city and increase its value.

For Berlin:

```text
city["Berlin"]
```

might become:

```text
1
2
3
```

***

# 5. Functions

You can create your own function:

```awk
function square(x) {
    return x * x
}
```

Example:

```bash
awk '
function square(x) {
    return x * x
}
{
    print $2, square($2)
}
' people.txt
```

***

# 6. A reusable function

Another example:

```awk
function greet(name) {
    return "Hello " name
}
```

Then:

```bash
awk '
function greet(name) {
    return "Hello " name
}
{
    print greet($1)
}
' people.txt
```

***

# 7. Combine everything

```bash
awk '
BEGIN {
    print "CITY REPORT"
    print "==========="
}
{
    city[$3]++
}
END {
    for (c in city)
        print c, city[c]
}
' people.txt
```

You are now doing actual data processing.

***

# 🧪 Day 6 Exercises

Create:

```text
orders.txt
```

```text
Alice Laptop 1200
Bob Monitor 400
Alice Keyboard 80
Charlie Laptop 1200
Bob Mouse 30
Alice Monitor 400
```

Write AWK programs to:

1. Print all customers.

2. Print all products.

3. Calculate total sales.

4. Count orders per customer.

5. Calculate sales per customer.

6. Find the most expensive order.

7. Create a small sales report.

***

# Day 7 — 🚀 Final Project: AWK Log Analyzer

Today we combine everything.

## 🎯 Final Goal

Build a program that analyzes an application log.

***

# 1. Create `application.log`

```text
INFO Application started
INFO User Alice logged in
INFO User Bob logged in
WARN Disk space low
ERROR Database unavailable
INFO User Charlie logged in
ERROR Connection failed
INFO Request processed
WARN Memory usage high
ERROR Service unavailable
INFO Application stopped
```

***

# 2. Requirements

Your program should report:

```text
====================
APPLICATION LOG REPORT
====================

INFO: 6
WARN: 2
ERROR: 3

TOTAL: 11
```

***

# 3. First version

Create:

```text
logreport.awk
```

Start with:

```awk
{
    count[$1]++
    total++
}

END {
    print "===================="
    print "APPLICATION LOG REPORT"
    print "===================="

    print ""

    print "INFO:", count["INFO"]
    print "WARN:", count["WARN"]
    print "ERROR:", count["ERROR"]

    print ""

    print "TOTAL:", total
}
```

Run:

```bash
awk -f logreport.awk application.log
```

***

# 4. Add percentages

Now calculate the percentage of errors.

```awk
errorPercentage = count["ERROR"] / total * 100
```

Then:

```awk
printf "ERROR: %.2f%%\n", errorPercentage
```

***

# 5. Add timestamps

Let's make the log more realistic.

Change the log to:

```text
2026-09-29 18:00:01 INFO Application started
2026-09-29 18:00:05 INFO User Alice logged in
2026-09-29 18:00:07 INFO User Bob logged in
2026-09-29 18:00:10 WARN Disk space low
2026-09-29 18:00:12 ERROR Database unavailable
2026-09-29 18:00:15 INFO User Charlie logged in
2026-09-29 18:00:18 ERROR Connection failed
2026-09-29 18:00:20 INFO Request processed
2026-09-29 18:00:22 WARN Memory usage high
2026-09-29 18:00:25 ERROR Service unavailable
2026-09-29 18:00:30 INFO Application stopped
```

Now the fields are:

```text
$1       $2        $3       $4 ...
date     time      level    message...
```

So:

```text
$3
```

is:

```text
INFO
WARN
ERROR
```

***

# 6. Analyze the new format

```awk
{
    count[$3]++
    total++
}
```

Then:

```awk
END {
    print "INFO:", count["INFO"]
    print "WARN:", count["WARN"]
    print "ERROR:", count["ERROR"]
    print "TOTAL:", total
}
```

***

# 7. Find all errors

```bash
awk '$3 == "ERROR" { print $0 }' application.log
```

***

# 8. Find all warnings

```bash
awk '$3 == "WARN" { print $0 }' application.log
```

***

# 9. Count errors

```bash
awk '$3 == "ERROR" { count++ } END { print count }' application.log
```

***

# 10. Final project version

Your final `logreport.awk` can look like:

```awk
BEGIN {
    print "=============================="
    print "   APPLICATION LOG REPORT"
    print "=============================="
    print ""
}

{
    level = $3

    count[level]++
    total++
}

END {
    print "INFO :", count["INFO"]
    print "WARN :", count["WARN"]
    print "ERROR:", count["ERROR"]
    print "TOTAL:", total

    print ""

    if (total > 0) {
        printf "Error rate: %.2f%%\n", \
               count["ERROR"] / total * 100
    }
}
```

Run:

```bash
awk -f logreport.awk application.log
```

🎉 **You have built your first AWK application!**

***

# 🏆 What You Should Know After 7 Days

At the end of the bootcamp, you should understand this:

```text
                    AWK
                     │
       ┌─────────────┼─────────────┐
       │             │             │
     INPUT         PATTERN        ACTION
       │             │             │
       ▼             ▼             ▼
    text file    condition       print
       │                           │
       ├── $0                      ├── print $1
       ├── $1                      ├── printf
       ├── $2                      ├── variables
       ├── $NF                     └── calculations
       ├── NF
       └── NR
```

And then:

```text
BEGIN
  ↓
read line
  ↓
split into fields
  ↓
test pattern
  ↓
execute action
  ↓
next line
  ↓
END
```

***

# 📚 Your AWK Core Vocabulary

By the end of the week, aim to be comfortable with:

```text
$0
$1
$2
$NF

NR
NF

FS
OFS

BEGIN
END

print
printf

if
else

for
while

++
+=

arrays

functions

regular expressions
```

***

# 🧠 The 10 AWK Commands I'd Memorize First

If you want a compact learning target, memorize these:

### 1. Print first field

```bash
awk '{ print $1 }' file.txt
```

### 2. Print last field

```bash
awk '{ print $NF }' file.txt
```

### 3. Print line numbers

```bash
awk '{ print NR, $0 }' file.txt
```

### 4. Filter

```bash
awk '$2 > 100 { print $0 }' file.txt
```

### 5. Search

```bash
awk '/ERROR/ { print $0 }' file.txt
```

### 6. Count

```bash
awk '/ERROR/ { count++ } END { print count }' file.txt
```

### 7. Sum

```bash
awk '{ total += $2 } END { print total }' file.txt
```

### 8. Average

```bash
awk '{ total += $2 } END { print total / NR }' file.txt
```

### 9. CSV

```bash
awk -F',' '{ print $1, $3 }' file.csv
```

### 10. Array counting

```bash
awk '{ count[$1]++ } END { for (x in count) print x, count[x] }' file.txt
```

***

# 🎓 Final Challenge

After completing Day 7, try building this **without looking at the solution**:

Create `server.log`:

```text
2026-09-29 10:01:01 INFO GET /api/users 200
2026-09-29 10:01:02 INFO GET /api/products 200
2026-09-29 10:01:03 ERROR GET /api/orders 500
2026-09-29 10:01:04 INFO GET /api/users 200
2026-09-29 10:01:05 WARN GET /api/products 404
2026-09-29 10:01:06 ERROR GET /api/orders 500
2026-09-29 10:01:07 INFO GET /api/users 200
```

Your AWK program should produce:

```text
SERVER LOG REPORT
-----------------

INFO: 4
WARN: 1
ERROR: 2

HTTP 200: 4
HTTP 404: 1
HTTP 500: 2

TOTAL REQUESTS: 7
```

**Hint:** the important fields are:

```text
$1 = date
$2 = time
$3 = level
$4 = HTTP method
$5 = URL
$6 = status code
```

This final exercise is particularly useful for a **Java/Spring Boot backend developer**, because it gets you thinking about AWK in the same way you would approach analyzing application and HTTP logs in a backend environment.

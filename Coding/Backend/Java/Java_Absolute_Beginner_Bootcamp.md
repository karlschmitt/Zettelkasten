---
ie: 20260822152234
title: Java Absolute Beginner Bootcamp
author: Karl Schmitt
date: 2026-08-22
---

Absolutely! Let's build a **Java Absolute Beginner Bootcamp** that starts from the very beginning and gradually takes you to the point where you can write small Java programs confidently.

Since you are interested in Spring Boot, this bootcamp will also prepare you for understanding what happens **underneath Spring Boot**.

# ☕ Java Absolute Beginner Bootcamp

## The goal

By the end of this bootcamp, you should be able to:

* Read basic Java code

* Write your own Java programs

* Understand variables and data types

* Make decisions with `if` statements

* Repeat code with loops

* Create and use methods

* Understand arrays and collections

* Understand classes and objects

* Use constructors

* Understand encapsulation

* Understand inheritance and polymorphism

* Understand interfaces

* Handle exceptions

* Build a small console application

***

# 🗓️ Bootcamp Overview

| Day | Topic                    | Main Goal                            |
| --- | ------------------------ | ------------------------------------ |
| 1   | Java Fundamentals        | Understand how a Java program starts |
| 2   | Variables and Data Types | Store information                    |
| 3   | Operators and Decisions  | Make programs think and decide       |
| 4   | Loops                    | Repeat operations                    |
| 5   | Methods                  | Organize and reuse code              |
| 6   | Arrays and ArrayList     | Work with multiple values            |
| 7   | Classes and Objects      | Learn the foundation of OOP          |
| 8   | Constructors and `this`  | Create properly initialized objects  |
| 9   | Encapsulation            | Protect object data                  |
| 10  | Inheritance              | Reuse behavior                       |
| 11  | Polymorphism             | Work with objects flexibly           |
| 12  | Interfaces               | Define contracts                     |
| 13  | Exceptions               | Handle errors                        |
| 14  | Collections              | Work with `List`, `Set`, and `Map`   |
| 15  | Mini Project             | Build a small Java application       |

***

# Day 1 — Your First Java Program

## Goal

Understand:

* What a Java class is

* What `main()` is

* How Java starts a program

* How to print text

Create:

```text
Main.java
```

Add:

```java
public class Main {

    public static void main(String[] args) {

        System.out.println("Hello, Java!");

    }

}
```

Output:

```text
Hello, Java!
```

## What happens?

When you run your program:

```text
Java starts
    ↓
Looks for main()
    ↓
Runs main()
    ↓
System.out.println()
    ↓
Text appears in the console
```

### Exercise

Change the program so it prints:

```text
Hello!
My name is Karl.
I am learning Java.
```

***

# Day 2 — Variables and Data Types

## Goal

Learn how programs store information.

```java
String name = "Karl";
int age = 30;
double height = 1.80;
boolean learningJava = true;
```

Think of a variable like a labeled box:

```text
┌─────────────┐
│ name        │
│ "Karl"      │
└─────────────┘
```

## Your exercise

Create variables for:

* Your name

* Your age

* Your favorite number

* Whether you like programming

Then print them.

Example:

```java
public class Main {

    public static void main(String[] args) {

        String name = "Karl";
        int age = 30;
        int favoriteNumber = 42;
        boolean likesProgramming = true;

        System.out.println(name);
        System.out.println(age);
        System.out.println(favoriteNumber);
        System.out.println(likesProgramming);

    }

}
```

***

# Day 3 — Making Decisions with `if`

Programs often need to choose what to do.

```java
int age = 20;

if (age >= 18) {

    System.out.println("You are an adult.");

}
```

The program asks:

```text
Is age >= 18?
```

The result is:

```text
true
```

Therefore:

```text
"You are an adult."
```

is printed.

## `if` + `else`

```java
int age = 16;

if (age >= 18) {

    System.out.println("Adult");

} else {

    System.out.println("Minor");

}
```

### Exercise

Create a variable:

```java
int temperature = 25;
```

Print:

```text
It's warm.
```

if the temperature is above `20`.

Otherwise print:

```text
It's cold.
```

***

# Day 4 — Loops

Loops repeat code.

```java
for (int i = 1; i <= 5; i++) {

    System.out.println(i);

}
```

Output:

```text
1
2
3
4
5
```

## Understanding the `for` loop

```java
for (int i = 1; i <= 5; i++)
```

means:

```text
1. Create i = 1
2. Is i <= 5?
3. Run the code
4. Increase i
5. Repeat
```

### Exercise

Print:

```text
Hello 1
Hello 2
Hello 3
Hello 4
Hello 5
```

Try:

```java
for (int i = 1; i <= 5; i++) {

    System.out.println("Hello " + i);

}
```

***

# Day 5 — Methods

A method is a reusable piece of code.

```java
public static void sayHello() {

    System.out.println("Hello!");

}
```

Call it:

```java
sayHello();
```

Complete example:

```java
public class Main {

    public static void main(String[] args) {

        sayHello();
        sayHello();
        sayHello();

    }

    public static void sayHello() {

        System.out.println("Hello!");

    }

}
```

Output:

```text
Hello!
Hello!
Hello!
```

## Methods with parameters

```java
public static void greet(String name) {

    System.out.println("Hello " + name);

}
```

Use it:

```java
greet("Karl");
greet("Anna");
```

### Exercise

Create a method:

```text
sayAge()
```

Give it an `int age` parameter and print:

```text
You are 30 years old.
```

***

# Day 6 — Arrays and ArrayList

Sometimes you need to store multiple values.

## Arrays

```java
String[] names = {
    "Karl",
    "Anna",
    "Peter"
};
```

Memory model:

```text
Index     Value

0         Karl
1         Anna
2         Peter
```

Print one element:

```java
System.out.println(names[0]);
```

## Loop through an array

```java
for (String name : names) {

    System.out.println(name);

}
```

## `ArrayList`

Unlike an array, an `ArrayList` can grow.

```java
import java.util.ArrayList;

ArrayList<String> names = new ArrayList<>();

names.add("Karl");
names.add("Anna");
names.add("Peter");
```

### Exercise

Create an `ArrayList` containing five programming languages.

Print all of them using a loop.

***

# Day 7 — Classes and Objects

This is one of the most important days.

A **class** is a blueprint.

```text
Class: Person
```

The blueprint describes:

```text
Person
 ├── name
 ├── age
 └── sayHello()
```

Java:

```java
public class Person {

    String name;
    int age;

    public void sayHello() {

        System.out.println("Hello, my name is " + name);

    }

}
```

Now create an object:

```java
Person person = new Person();
```

Set its values:

```java
person.name = "Karl";
person.age = 30;
```

Call its method:

```java
person.sayHello();
```

The important idea:

```text
Class
  ↓
Blueprint
  ↓
Object
  ↓
Actual instance
```

### Exercise

Create a class called:

```text
Book
```

Give it:

```text
title
author
```

Create two `Book` objects.

***

# Day 8 — Constructors

A constructor helps us create an object with its initial values.

Instead of:

```java
Person person = new Person();

person.name = "Karl";
person.age = 30;
```

we can write:

```java
Person person = new Person("Karl", 30);
```

## The class

```java
public class Person {

    String name;
    int age;

    public Person(String name, int age) {

        this.name = name;
        this.age = age;

    }

}
```

The flow:

```text
new Person("Karl", 30)
          ↓
Constructor runs
          ↓
name = "Karl"
age = 30
```

### Exercise

Add a constructor to your `Book` class.

Then create a book like this:

```java
Book book = new Book(
    "The Hobbit",
    "J.R.R. Tolkien"
);
```

***

# Day 9 — Encapsulation

Usually, object data should not be directly accessible.

Instead of:

```java
person.age = -500;
```

we can protect the data.

```java
public class Person {

    private int age;

    public int getAge() {

        return age;

    }

    public void setAge(int age) {

        if (age >= 0) {

            this.age = age;

        }

    }

}
```

Now:

```text
Outside world
      ↓
setAge()
      ↓
Validation
      ↓
private age
```

### Exercise

Create a `BankAccount` class.

It should contain:

```text
private double balance
```

Create methods:

```text
deposit()
withdraw()
getBalance()
```

***

# Day 10 — Inheritance

Suppose we have:

```text
Animal
```

And:

```text
Dog
Cat
Bird
```

They have things in common.

```text
Animal
   │
   ├── Dog
   ├── Cat
   └── Bird
```

Java:

```java
public class Animal {

    public void eat() {

        System.out.println("The animal is eating.");

    }

}
```

A `Dog` can inherit from `Animal`:

```java
public class Dog extends Animal {

    public void bark() {

        System.out.println("Woof!");

    }

}
```

Usage:

```java
Dog dog = new Dog();

dog.eat();
dog.bark();
```

### Exercise

Create:

```text
Vehicle
    │
    ├── Car
    └── Motorcycle
```

Give `Vehicle` a method:

```text
start()
```

Give `Car` a method:

```text
openTrunk()
```

***

# Day 11 — Polymorphism

Polymorphism sounds complicated, but the basic idea is simple:

> Different objects can be treated as the same general type.

Example:

```java
Animal animal = new Dog();
```

Even though the actual object is a:

```text
Dog
```

we can store it in an:

```text
Animal
```

variable.

Example:

```java
Animal[] animals = {
    new Dog(),
    new Cat()
};
```

Then:

```java
for (Animal animal : animals) {

    animal.makeSound();

}
```

Each object can behave differently.

```text
Dog → Woof!
Cat → Meow!
```

***

# Day 12 — Interfaces

An interface is a contract.

```java
public interface Printable {

    void print();

}
```

Any class implementing this interface must provide:

```text
print()
```

Example:

```java
public class Document implements Printable {

    @Override
    public void print() {

        System.out.println("Printing document");

    }

}
```

Another class:

```java
public class Photo implements Printable {

    @Override
    public void print() {

        System.out.println("Printing photo");

    }

}
```

Both classes fulfill the same contract:

```text
Printable
    │
    └── print()
          │
     ┌────┴────┐
     ↓         ↓
Document    Photo
```

***

# Day 13 — Exceptions

Programs can encounter problems.

Example:

```java
int result = 10 / 0;
```

This causes an exception.

We can handle it:

```java
try {

    int result = 10 / 0;

} catch (ArithmeticException e) {

    System.out.println("Something went wrong!");

}
```

The basic model:

```text
try
 │
 ├── Try to execute code
 │
 ├── Problem?
 │
 └── catch
        ↓
     Handle it
```

### Exercise

Create a program that safely divides two numbers.

If division by zero happens, print an error message.

***

# Day 14 — Collections

The three most important collections for beginners are:

```text
List
Set
Map
```

## List

Stores ordered elements.

```java
List<String> names = new ArrayList<>();

names.add("Karl");
names.add("Anna");
names.add("Peter");
```

A `List` allows duplicates:

```text
Karl
Karl
Anna
```

***

## Set

A `Set` stores unique values.

```java
Set<String> names = new HashSet<>();

names.add("Karl");
names.add("Karl");
names.add("Anna");
```

Result:

```text
Karl
Anna
```

***

## Map

A `Map` stores:

```text
Key → Value
```

Example:

```java
Map<String, Integer> ages = new HashMap<>();

ages.put("Karl", 30);
ages.put("Anna", 25);
```

Retrieve a value:

```java
System.out.println(ages.get("Karl"));
```

***

# Day 15 — Final Mini Project

## 🎯 Project: Simple Contact Manager

We will build a program that manages contacts.

A contact has:

```text
Contact
 ├── name
 ├── phoneNumber
 └── email
```

Create:

```text
Contact.java
```

```java
public class Contact {

    private String name;
    private String phoneNumber;
    private String email;

    public Contact(
            String name,
            String phoneNumber,
            String email
    ) {

        this.name = name;
        this.phoneNumber = phoneNumber;
        this.email = email;

    }

    public void printContact() {

        System.out.println("Name: " + name);
        System.out.println("Phone: " + phoneNumber);
        System.out.println("Email: " + email);

    }

}
```

Then create:

```text
Main.java
```

```java
import java.util.ArrayList;

public class Main {

    public static void main(String[] args) {

        ArrayList<Contact> contacts =
                new ArrayList<>();

        contacts.add(
                new Contact(
                        "Karl",
                        "123456",
                        "karl@example.com"
                )
        );

        contacts.add(
                new Contact(
                        "Anna",
                        "987654",
                        "anna@example.com"
                )
        );

        for (Contact contact : contacts) {

            contact.printContact();

            System.out.println();

        }

    }

}
```

***

# 🧠 The Big Picture

At the end of the bootcamp, Java should look something like this:

```text
Java Application
       │
       ▼
┌───────────────┐
│     main()    │
│ Program starts│
└───────┬───────┘
        │
        ▼
┌───────────────┐
│   VARIABLES   │
│ Store data    │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    METHODS    │
│ Do things     │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    CLASSES    │
│ Blueprints    │
└───────┬───────┘
        │
        ▼
┌───────────────┐
│    OBJECTS    │
│ Actual data   │
└───────────────┘
```

## 🚀 How I suggest we continue

We can now do this as a **real interactive bootcamp**.

### Lesson 1

**How Java programs actually start**

We would explore, step by step:

```java
public class Main {

    public static void main(String[] args) {

        System.out.println("Hello, World!");

    }

}
```

We would not just memorize:

```java
public static void main(String[] args)
```

Instead, we would gradually answer:

* What is a `class`?

* Why is it called `Main`?

* What does `public` mean?

* What does `static` mean?

* What is a `method`?

* Why is it called `main`?

* What are `String[] args`?

* What happens when Java starts the program?

* What exactly does `System.out.println()` do?

Then each lesson can include:

1. **Concept explanation**

2. **Mental model**

3. **Code example**

4. **Step-by-step execution**

5. **Exercises**

6. **Small challenge**

7. **Solutions and explanations**

This approach should give you a much stronger foundation before moving into more advanced Java and Spring Boot.

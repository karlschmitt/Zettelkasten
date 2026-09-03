---
id: 20260903134408
title: Thymeleaf Absolute Beginner Tutorial
author: Karl Schmitt
date: 2026-09-03
---

# Thymeleaf Absolute Beginner Tutorial

Absolutely. Since you are working with **Spring Boot and Java**, Thymeleaf is a very good next step: it lets you build server-rendered HTML pages directly from your Spring Boot application.

Feel free to follow the white Rabbit: [What is Thymeleaf?](./What_is_Thymeleaf.md)

## 🌱 Welcome to the Spring Boot and Thymeleaf Absolute Beginner Tutorial

We will build a small application step by step:

```text
Browser
   │
   │ HTTP GET /hello
   ▼
Spring Boot Controller
   │
   │ Model
   ▼
Thymeleaf Template
   │
   │ rendered HTML
   ▼
Browser
```

By the end, you will understand:

* what Thymeleaf is

* how Thymeleaf works with Spring Boot

* Controllers

* `Model`

* Thymeleaf templates

* `${...}` expressions

* displaying Java variables

* `th:text`

* `th:if`

* `th:each`

* links with `th:href`

* HTML forms

* `@{...}` URLs

* `th:object` / `th:field`

* template fragments

* a small CRUD-style example

***

# 1. What is Thymeleaf?

**Thymeleaf is a server-side HTML templating engine.**

The important idea is:

> Java creates data → Thymeleaf puts the data into HTML → Spring Boot sends the resulting HTML to the browser.

For example, suppose Java provides:

```text
name = "Karl"
```

Your Thymeleaf template might contain:

```html
<h1 th:text="${name}">Name</h1>
```

Thymeleaf transforms that into ordinary HTML:

```html
<h1>Karl</h1>
```

The browser doesn't need to know anything about Thymeleaf.

***

# 2. Thymeleaf vs JavaScript

This is an important distinction.

With a traditional Spring Boot + Thymeleaf application:

```text
Browser
   │
   │ GET /hello
   ▼
Spring Boot
   │
   ├── Controller
   │
   ├── Java objects
   │
   └── Thymeleaf
          │
          ▼
       HTML
          │
          ▼
       Browser
```

With a typical SPA such as Angular or React:

```text
Browser
   │
   │ GET /api/users
   ▼
Spring Boot
   │
   ▼
   JSON
   │
   ▼
Angular / React
   │
   ▼
DOM
```

So:

**Thymeleaf = server-side rendering**

**Angular/React = client-side rendering**

This makes Thymeleaf particularly useful for learning the traditional Spring MVC model.

***

# 3. Create the Spring Boot project

Create a Spring Boot project with:

```text
Spring Web
Thymeleaf
Spring Boot Starter Data JPA 
PostgreSQL
```

For example:

```text
Group:
    com.example

Artifact:
    thymeleaf-demo

Java:
    21
```

Your dependencies will include something similar to:

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-web</artifactId>
</dependency>

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```

***

# 4. Project structure

A simple project looks like this:

```text
thymeleaf-demo
│
├── src
│   └── main
│       ├── java
│       │   └── com.example.thymeleafdemo
│       │       ├── ThymeleafDemoApplication.java
│       │       └── HelloController.java
│       │
│       └── resources
│           ├── static
│           │
│           └── templates
│               └── hello.html
│
└── pom.xml
```

The important directory is:

```text
src/main/resources/templates
```

**Thymeleaf templates normally live here.**

***

# 5. Your first Controller

Create:

```java
package com.example.thymeleafdemo;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

@Controller
public class HelloController {

    @GetMapping("/hello")
    public String hello(Model model) {

        model.addAttribute("name", "Karl");

        return "hello";
    }
}
```

There are several important things here.

***

## `@Controller`

```java
@Controller
```

This tells Spring:

> This class contains MVC controller methods.

Notice that we are **not** using:

```java
@RestController
```

A `RestController` normally returns data such as JSON.

A normal `Controller` can return the name of a view.

***

# 6. The `Model`

This line is extremely important:

```java
model.addAttribute("name", "Karl");
```

Think of `Model` as a container for data.

We put:

```text
name → Karl
```

into the model.

Conceptually:

```text
Model

┌───────────────┐
│ name          │
│ "Karl"        │
└───────────────┘
```

Thymeleaf can then access this data.

***

# 7. Returning the template

The Controller says:

```java
return "hello";
```

This means approximately:

> Render the Thymeleaf template called `hello`.

Spring Boot looks for:

```text
src/main/resources/templates/hello.html
```

So:

```java
return "hello";
```

maps to:

```text
templates/hello.html
```

***

# 8. Create the Thymeleaf template

Create:

```text
src/main/resources/templates/hello.html
```

with:

```html
<!DOCTYPE html>
<html lang="en" xmlns:th="http://www.thymeleaf.org">

<head>
    <meta charset="UTF-8">
    <title>Hello Thymeleaf</title>
</head>

<body>

    <h1>Hello!</h1>

    <p>
        My name is
        <span th:text="${name}">Unknown</span>.
    </p>

</body>

</html>
```

Now start Spring Boot.

Open:

```text
http://localhost:8080/hello
```

You should see:

```text
Hello!

My name is Karl.
```

🎉 You have created your first Spring Boot + Thymeleaf application.

***

# 9. Understanding `${name}`

This:

```html
${name}
```

is a **Thymeleaf expression**.

It means:

> Get the value called `name` from the model.

Remember the Controller:

```java
model.addAttribute("name", "Karl");
```

and the template:

```html
<span th:text="${name}">
```

The relationship is:

```text
Controller

model.addAttribute("name", "Karl")
                │
                │
                ▼
             Model
                │
                │
                ▼
Template

${name}
                │
                ▼
             "Karl"
```

This is the fundamental Thymeleaf mechanism.

***

# 10. What does `th:text` mean?

Consider:

```html
<span th:text="${name}">
    Unknown
</span>
```

`th:text` is a **Thymeleaf attribute**.

It says:

> Replace the text inside this HTML element with the result of this expression.

So:

```html
<span th:text="${name}">Unknown</span>
```

becomes:

```html
<span>Karl</span>
```

The browser receives ordinary HTML.

***

# 11. Why is there `Unknown`?

This is interesting:

```html
<span th:text="${name}">Unknown</span>
```

The `Unknown` is the normal HTML text.

This is one of Thymeleaf's nice properties.

The template is still valid HTML.

Without Thymeleaf processing:

```text
Unknown
```

would be displayed.

With Thymeleaf processing:

```text
Karl
```

is displayed.

This is sometimes called **natural templating**.

***

# 12. Multiple model attributes

You aren't limited to one value.

Controller:

```java
@GetMapping("/person")
public String person(Model model) {

    model.addAttribute("firstName", "Karl");
    model.addAttribute("lastName", "Schmitt");
    model.addAttribute("age", 50);

    return "person";
}
```

Template:

```html
<h1>Person</h1>

<p>
    First name:
    <span th:text="${firstName}">First name</span>
</p>

<p>
    Last name:
    <span th:text="${lastName}">Last name</span>
</p>

<p>
    Age:
    <span th:text="${age}">Age</span>
</p>
```

***

# 13. Expressions can appear directly in HTML

For example:

```html
<h1 th:text="'Hello ' + ${name}">
    Hello
</h1>
```

Or more simply:

```html
<h1>Hello <span th:text="${name}">Karl</span></h1>
```

You will frequently see expressions such as:

```html
${name}
${user.name}
${user.email}
${product.price}
```

***

# 14. Working with Java objects

Suppose we create:

```java
public class Person {

    private String firstName;
    private String lastName;

    public Person(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }
}
```

Controller:

```java
@GetMapping("/person")
public String person(Model model) {

    Person person = new Person("Karl", "Schmitt");

    model.addAttribute("person", person);

    return "person";
}
```

Thymeleaf can access JavaBean properties:

```html
<p th:text="${person.firstName}">
    First name
</p>

<p th:text="${person.lastName}">
    Last name
</p>
```

Notice:

```text
Java

person.getFirstName()
```

can be accessed in Thymeleaf as:

```text
${person.firstName}
```

Thymeleaf uses property access.

***

# 15. `th:if`

You can conditionally display HTML.

Controller:

```java
model.addAttribute("loggedIn", true);
```

Template:

```html
<p th:if="${loggedIn}">
    Welcome back!
</p>
```

If:

```text
loggedIn = true
```

the paragraph is rendered.

If:

```text
loggedIn = false
```

it isn't rendered.

For example:

```html
<p th:if="${age >= 18}">
    You are an adult.
</p>
```

***

# 16. `th:unless`

The opposite is:

```html
<p th:unless="${loggedIn}">
    Please log in.
</p>
```

Meaning:

> Display this element unless `loggedIn` is true.

***

# 17. Lists and `th:each`

This is one of the most important Thymeleaf features.

Suppose the Controller creates:

```java
List<String> names = List.of(
    "Alice",
    "Bob",
    "Charlie"
);

model.addAttribute("names", names);
```

The template:

```html
<ul>

    <li th:each="name : ${names}"
        th:text="${name}">
        Name
    </li>

</ul>
```

Thymeleaf essentially repeats the `<li>`.

Result:

```html
<ul>
    <li>Alice</li>
    <li>Bob</li>
    <li>Charlie</li>
</ul>
```

The syntax:

```text
th:each="name : ${names}"
```

means:

> For every element in `names`, create an iteration variable called `name`.

***

# 18. `th:each` is similar to a Java enhanced for loop

Java:

```java
for (String name : names) {
    System.out.println(name);
}
```

Thymeleaf:

```html
<li th:each="name : ${names}"
    th:text="${name}">
</li>
```

So you can think of:

```text
th:each
```

as the template equivalent of:

```java
for (...)
```

***

# 19. Displaying an object list

Suppose:

```java
List<Person> people = List.of(
    new Person("Alice", "Smith"),
    new Person("Bob", "Jones"),
    new Person("Charlie", "Brown")
);

model.addAttribute("people", people);
```

Template:

```html
<table>

    <thead>
        <tr>
            <th>First name</th>
            <th>Last name</th>
        </tr>
    </thead>

    <tbody>

        <tr th:each="person : ${people}">

            <td th:text="${person.firstName}">
                First name
            </td>

            <td th:text="${person.lastName}">
                Last name
            </td>

        </tr>

    </tbody>

</table>
```

This produces:

```text
First name     Last name
-------------------------
Alice          Smith
Bob            Jones
Charlie        Brown
```

***

# 20. Links with `th:href`

Suppose we have:

```java
@GetMapping("/users")
public String users() {
    return "users";
}
```

You can create a link:

```html
<a th:href="@{/users}">
    Users
</a>
```

The Thymeleaf syntax:

```text
@{...}
```

is used for URLs.

So:

```html
@{/users}
```

means:

```text
/users
```

***

# 21. Path variables

Suppose you have:

```java
@GetMapping("/users/{id}")
public String user(
        @PathVariable Long id,
        Model model) {

    model.addAttribute("id", id);

    return "user";
}
```

You can create a link:

```html
<a th:href="@{/users/{id}(id=${id})}">
    Show user
</a>
```

If:

```text
id = 42
```

the resulting URL is:

```text
/users/42
```

***

# 22. Query parameters

Suppose you want:

```text
/search?name=Karl
```

You can write:

```html
<a th:href="@{/search(name=${name})}">
    Search
</a>
```

If:

```text
name = Karl
```

the generated URL is:

```text
/search?name=Karl
```

***

# 23. HTML forms

Now we get into a very important Spring MVC + Thymeleaf combination.

Controller:

```java
@GetMapping("/person-form")
public String showForm(Model model) {

    model.addAttribute("person", new PersonForm());

    return "person-form";
}
```

A form object:

```java
public class PersonForm {

    private String name;
    private String email;

    // getters and setters
}
```

Template:

```html
<form th:action="@{/person-form}"
      th:object="${person}"
      method="post">

    <label>Name:</label>

    <input type="text"
           th:field="*{name}">

    <label>Email:</label>

    <input type="email"
           th:field="*{email}">

    <button type="submit">
        Save
    </button>

</form>
```

There are three important Thymeleaf concepts here:

```text
th:action
th:object
th:field
```

***

# 24. Understanding `th:object`

This:

```html
th:object="${person}"
```

means:

> This form is working with the `person` object.

Then:

```html
th:field="*{name}"
```

means:

> Bind this input to the `name` property of the current object.

Conceptually:

```text
th:object="${person}"
           │
           ▼
       PersonForm
       ┌─────────────┐
       │ name        │
       │ email       │
       └─────────────┘
          ▲       ▲
          │       │
      *{name}  *{email}
```

This is one of the most useful features when working with Spring MVC forms.

***

# 25. Processing the form

The Controller can receive the form object:

```java
@PostMapping("/person-form")
public String submitForm(
        @ModelAttribute PersonForm person) {

    System.out.println(person.getName());
    System.out.println(person.getEmail());

    return "success";
}
```

So the complete flow is:

```text
Browser
   │
   │ GET /person-form
   ▼
Controller
   │
   │ creates PersonForm
   ▼
Thymeleaf
   │
   ▼
HTML form
   │
   │ POST /person-form
   ▼
Controller
   │
   ▼
PersonForm
```

This is the classic **Spring MVC form-processing cycle**.

***

# 26. Thymeleaf's most important expressions

As a beginner, I recommend learning these first:

| Syntax   | Meaning                         |
| -------- | ------------------------------- |
| `${...}` | Read a value                    |
| `@{...}` | Build a URL                     |
| `*{...}` | Access a form object's property |
| `#{...}` | Message/i18n lookup             |
| `~{...}` | Template fragment               |

For example:

```html
<span th:text="${name}">
```

```html
<a th:href="@{/users}">
```

```html
<input th:field="*{name}">
```

Don't try to memorize everything at once.

Start with:

```text
${...}
@{...}
th:text
th:if
th:each
th:href
th:object
th:field
```

***

# 27. Template fragments

As applications become larger, you don't want to repeat:

```html
<header>
...
</header>
```

and:

```html
<footer>
...
</footer>
```

on every page.

Thymeleaf supports **fragments**.

For example:

```text
templates/
│
├── fragments/
│   ├── header.html
│   └── footer.html
│
├── home.html
└── users.html
```

`header.html`:

```html
<header th:fragment="header">

    <h1>My Application</h1>

    <nav>
        <a th:href="@{/}">Home</a>
        <a th:href="@{/users}">Users</a>
    </nav>

</header>
```

Then another page can include it:

```html
<header th:replace="~{fragments/header :: header}">
</header>
```

This gives you reusable HTML components.

***

# 28. Thymeleaf + Spring Boot mental model

This is the mental model I recommend remembering:

```text
                  HTTP Request
                       │
                       ▼
              ┌─────────────────┐
              │ Spring Controller│
              └────────┬────────┘
                       │
                       │ creates
                       ▼
                  ┌─────────┐
                  │  Model  │
                  └────┬────┘
                       │
                       │ data
                       ▼
              ┌─────────────────┐
              │    Thymeleaf    │
              │    Template     │
              └────────┬────────┘
                       │
                       │ rendered HTML
                       ▼
                  ┌─────────┐
                  │ Browser │
                  └─────────┘
```

The most important relationship is:

```java
model.addAttribute("name", "Karl");
```

↓

```html
<span th:text="${name}">
```

↓

```html
<span>Karl</span>
```

***

# 29. Thymeleaf vs REST

Since you're also learning Spring Boot REST APIs, it is useful to compare the two.

### REST controller

```java
@RestController
public class UserController {

    @GetMapping("/api/users")
    public List<User> users() {
        return users;
    }
}
```

Response:

```json
[
    {
        "name": "Alice"
    },
    {
        "name": "Bob"
    }
]
```

The client is responsible for displaying it.

***

### Thymeleaf controller

```java
@Controller
public class UserController {

    @GetMapping("/users")
    public String users(Model model) {

        model.addAttribute("users", users);

        return "users";
    }
}
```

Thymeleaf produces:

```html
<table>
    ...
</table>
```

The browser receives the finished HTML.

***

# 30. A small complete application

Let's put the concepts together.

### Controller

```java
@Controller
public class UserController {

    @GetMapping("/users")
    public String users(Model model) {

        List<String> users = List.of(
            "Alice",
            "Bob",
            "Charlie"
        );

        model.addAttribute("users", users);

        return "users";
    }
}
```

### Template

```html
<!DOCTYPE html>
<html lang="en"
      xmlns:th="http://www.thymeleaf.org">

<head>
    <meta charset="UTF-8">
    <title>Users</title>
</head>

<body>

<h1>Users</h1>

<ul>

    <li th:each="user : ${users}"
        th:text="${user}">
        User
    </li>

</ul>

</body>

</html>
```

Request:

```text
GET /users
```

Controller:

```text
users
```

Model:

```text
users
 ├── Alice
 ├── Bob
 └── Charlie
```

Thymeleaf:

```text
th:each
```

Generated HTML:

```html
<ul>
    <li>Alice</li>
    <li>Bob</li>
    <li>Charlie</li>
</ul>
```

Browser:

```text
Users

• Alice
• Bob
• Charlie
```

***

# 31. The Thymeleaf learning path I recommend for you

Since you're already working with **Spring Boot**, I would learn Thymeleaf in this order:

### Phase 1 — Foundations

```text
1. What is Thymeleaf?
2. Spring MVC
3. @Controller
4. Model
5. View
6. templates/
7. th:text
8. ${...}
```

### Phase 2 — Dynamic HTML

```text
9. th:if
10. th:unless
11. th:each
12. Objects and properties
13. th:href
14. @{...}
```

### Phase 3 — Forms

```text
15. HTML forms
16. th:action
17. th:object
18. th:field
19. @ModelAttribute
20. GET + POST
```

### Phase 4 — Real applications

```text
21. Validation
22. Error messages
23. BindingResult
24. Redirects
25. Flash attributes
26. Template fragments
27. Layouts
28. CSS / static resources
```

### Phase 5 — Database application

Finally:

```text
Browser
   │
   ▼
Thymeleaf
   │
   ▼
Spring MVC Controller
   │
   ▼
Service
   │
   ▼
Spring Data JPA
   │
   ▼
Database
```

That would lead naturally to a complete **Spring Boot + Thymeleaf CRUD application**.

***

# 32. One important concept to keep in mind

Because you've been learning Angular, React and NgRx, I would especially emphasize this difference:

### Angular / React

```text
State
  ↓
JavaScript
  ↓
DOM
```

### Spring Boot + Thymeleaf

```text
Java Model
  ↓
Thymeleaf
  ↓
HTML
  ↓
Browser
```

In other words, Thymeleaf doesn't replace Spring MVC.

It is the **view technology used by Spring MVC**.

```text
Spring MVC
│
├── Controller
│
├── Model
│
└── View
       │
       └── Thymeleaf
```

That is probably the single most important architectural idea to understand before going further.

***

## 🚀 Suggested next step

I would turn this into a **hands-on Spring Boot + Thymeleaf Bootcamp** rather than trying to learn the Thymeleaf syntax in isolation.

A very good progression would be:

```text
Day 1  → First Thymeleaf page
Day 2  → Model + expressions
Day 3  → Lists + th:each
Day 4  → Links + path variables
Day 5  → Forms + th:object + th:field
Day 6  → Validation + error handling
Day 7  → Mini CRUD application
```

The final project could be a **Person Management application**:

```text
              ┌────────────────────┐
              │  Person Management  │
              └─────────┬──────────┘
                        │
          ┌─────────────┼─────────────┐
          ▼             ▼             ▼
       List          Create         Edit
          │             │             │
          └─────────────┼─────────────┘
                        ▼
                     Delete
                        │
                        ▼
                   Spring Data JPA
                        │
                        ▼
                    Database
```

That would connect **Spring Boot + Spring MVC + Thymeleaf + Forms + Validation + JPA** into one coherent application.

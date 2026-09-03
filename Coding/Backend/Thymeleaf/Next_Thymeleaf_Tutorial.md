---
id: 20260903141401
title: Next Thymeleaf Tutorial
author: Karl Schmitt
date: 2026-09-03
---

This tutorial will guide you through creating a simple **Student Management** page using Spring Boot and Thymeleaf. We will cover displaying data, loops, conditionals, and layouts.

### Step 1: Project Setup

Go to [start.spring.io](https://start.spring.io) and add these dependencies:
*   **Spring Web**
*   **Thymeleaf**
*   **Spring Boot Starter Data JPA**
*   **PostgreSQL**

---

### Step 2: Create the Model
Create a simple Java class to hold your data.

```java
// Student.java
public class Student {
    private int id;
    private String name;
    private String email;
    private boolean enrolled;

    // Constructor, Getters, and Setters
    public Student(int id, String name, String email, boolean enrolled) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.enrolled = enrolled;
    }
    // ... Getters and Setters ...
}
```

---

### Step 3: Create the Controller
The controller handles the URL request and passes data to the HTML page.

```java
// StudentController.java
@Controller
public class StudentController {

    @GetMapping("/students")
    public String listStudents(Model model) {
        List<Student> studentList = Arrays.asList(
            new Student(1, "Alice", "alice@example.com", true),
            new Student(2, "Bob", "bob@example.com", false),
            new Student(3, "Charlie", "charlie@example.com", true)
        );

        model.addAttribute("allStudents", studentList);
        model.addAttribute("title", "University Roster");
        
        return "students"; // refers to students.html
    }
}
```

---

### Step 4: Create the View (Thymeleaf HTML)
Create a file at `src/main/resources/templates/students.html`.

```html
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<head>
    <title>Student List</title>
    <style>
        .enrolled { color: green; }
        .not-enrolled { color: red; }
    </style>
</head>
<body>

    <!-- 1. Simple Text Replacement -->
    <h1 th:text="${title}">Default Title</h1>

    <table border="1">
        <thead>
            <tr>
                <th>ID</th>
                <th>Name</th>
                <th>Email</th>
                <th>Status</th>
            </tr>
        </thead>
        <tbody>
            <!-- 2. Iteration (Looping) -->
            <tr th:each="student : ${allStudents}">
                <td th:text="${student.id}">0</td>
                <td th:text="${student.name}">Name</td>
                <td th:text="${student.email}">Email</td>
                
                <!-- 3. Conditionals (if/else) -->
                <td>
                    <span th:if="${student.enrolled}" class="enrolled">Active</span>
                    <span th:unless="${student.enrolled}" class="not-enrolled">Inactive</span>
                </td>
            </tr>
        </tbody>
    </table>

</body>
</html>
```

---

### Step 5: Essential Thymeleaf Syntax Explained

#### 1. Variable Expressions: `${...}`
Used to access variables passed from the Controller via the `Model`.
*   `th:text="${student.name}"` replaces the tag's inner text.

#### 2. Iteration: `th:each`
Works like a Java for-each loop.
*   `th:each="item : ${list}"` repeats the HTML element for every item in the collection.

#### 3. Conditionals: `th:if` and `th:unless`
*   `th:if="${condition}"`: Render this tag only if the condition is **true**.
*   `th:unless="${condition}"`: Render this tag only if the condition is **false**.

#### 4. Links and URLs: `@{...}`
For links to CSS, images, or other pages.
*   `<a th:href="@{/students/delete(id=${student.id})}">Delete</a>`
*   This automatically handles context paths (the root URL of your app).

---

### Step 6: Fragments (Reusable Components)
Usually, you want the same Header and Footer on every page. Thymeleaf uses **Fragments**.

1.  Create `fragments.html`:
    ```html
    <div th:fragment="navbar">
        <nav>
            <a href="/students">Home</a> | <a href="/about">About</a>
        </nav>
    </div>
    ```

2.  Use it in `students.html`:
    ```html
    <!-- This inserts the navbar from the fragments file -->
    <div th:replace="~{fragments :: navbar}"></div>
    ```

---

### Step 7: Run the Application
1.  Run your Spring Boot application.
2.  Navigate to `http://localhost:8080/students`.
3.  You will see your table populated with the data from the Controller!

### Summary Checklist
*   **Templates location:** `src/main/resources/templates`
*   **Static files (CSS/JS):** `src/main/resources/static`
*   **Namespace:** Always include `xmlns:th="http://www.thymeleaf.org"` in your `<html>` tag to get IDE autocomplete.
*   **Attributes:** Most HTML attributes have a `th:` equivalent (e.g., `th:src`, `th:value`, `th:action`, `th:style`).
---
id: 20260903135339
title: What is Thymeleaf?
author: Karl Schmitt
date: 2026-09-03
---

# What is Thymeleaf?

In the context of Spring Boot, **Thymeleaf** is a modern server-side Java template engine used to create dynamic web pages. 

It is the most popular choice for server-side rendering in the Spring ecosystem, largely replacing older technologies like JSP (JavaServer Pages).

Here is a breakdown of what makes Thymeleaf unique and how it works:

---

### 1. Key Feature: "Natural Templates"

The most significant advantage of Thymeleaf is that it allows for **Natural Templates**. 
*   Thymeleaf files are standard HTML files with additional attributes (starting with `th:`).
*   Because they are valid HTML, you can open a Thymeleaf template directly in a web browser (like Chrome) as a static file, and it will look like a normal webpage. 
*   **JSP files**, by contrast, cannot be opened in a browser without a running server; they just look like broken code.

### 2. Integration with Spring Boot

Thymeleaf is a "first-class citizen" in Spring Boot. If you add the `spring-boot-starter-thymeleaf` dependency, Spring Boot automatically configures:
*   **The Template Resolver:** It looks for HTML files in `src/main/resources/templates`.
*   **The View Resolver:** It maps controller returns (strings) to those HTML files.
*   **Spring Expression Language (SpEL):** It allows you to access Java objects and methods directly within your HTML.

### 3. How it Works (The MVC Flow)

Thymeleaf acts as the **View** in the Model-View-Controller (MVC) pattern:

1.  **Controller:** A Java class handles a web request, fetches data (the **Model**), and returns the name of a template.
2.  **Engine:** Thymeleaf takes the HTML template and the Model data.
3.  **Processing:** It replaces the "dummy" values in the HTML with real data from the Java objects.
4.  **Output:** It produces a pure HTML string and sends it to the user's browser.

### 4. Basic Syntax Example

In a Thymeleaf template, you use the `th:` prefix to perform logic.

**Java Controller:**
```java
@Controller
public class HelloController {
    @GetMapping("/welcome")
    public String welcome(Model model) {
        model.addAttribute("message", "Hello, World!");
        return "welcome"; // This points to welcome.html
    }
}
```

**Thymeleaf Template (`welcome.html`):**

```html
<!DOCTYPE html>
<html xmlns:th="http://www.thymeleaf.org">
<body>
    <!-- If running as a static file, it shows "Static Text" -->
    <!-- If running via Spring, it shows the value of "message" -->
    <h1 th:text="${message}">Static Text</h1>
</body>
</html>
```

### 5. Why use Thymeleaf instead of JSP?

1.  **Browser-Friendly:** As mentioned, designers can work on HTML files without needing a Java environment.
2.  **No Compilation:** JSPs are translated into Servlets and compiled, which can be slow and hard to debug. Thymeleaf is parsed directly.
3.  **Modern Standards:** It is designed for HTML5 and supports fragments (reusable headers/footers) very efficiently.
4.  **Spring Security Integration:** It has excellent built-in support for showing/hiding UI elements based on user roles.

### When should you *not* use Thymeleaf?

If you are building a **Single Page Application (SPA)** using React, Vue, or Angular, you typically won't use Thymeleaf. In those cases, Spring Boot acts only as a REST API (sending JSON data), and the frontend framework handles the rendering. 

Thymeleaf is best for "traditional" web applications where the server handles the navigation and page generation.

Feel free to continue with the [Thymeleaf Tutorial](./Thymeleaf_Tutorial.md).
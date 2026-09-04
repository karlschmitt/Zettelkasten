---
id: 20260904205306
title: Content-Based File Router
author: Karl Schmitt
date: 2026-09-04
keywords: [Spring Boot, Apache Camel, CBR]
---

# Content-Based File Router

To run a complete example of this Content-Based Route in Spring Boot, follow these steps. This example will monitor a folder named `data/input`, read the files, and move them based on their text content.

### 1. Project Dependencies (`pom.xml`)

You need the Spring Boot Starter for Camel and the Camel File component.

```xml
<dependencies>
    <!-- Apache Camel Spring Boot Starter -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-spring-boot-starter</artifactId>
        <version>4.8.0</version> <!-- Use the latest version -->
    </dependency>

    <!-- File component is included in camel-core, 
         but for Spring Boot it's best to have the starter -->
    <dependency>
        <groupId>org.apache.camel</groupId>
        <artifactId>camel-file</artifactId>
        <version>4.8.0</version>
    </dependency>
</dependencies>
```

### 2. The Route Builder (`FileRouter.java`)

Create a class annotated with `@Component`. This is where your logic lives. I have added logging so you can see what's happening in the console.

```java
import org.apache.camel.builder.RouteBuilder;
import org.springframework.stereotype.Component;

@Component
public class FileRouter extends RouteBuilder {

    @Override
    public void configure() throws Exception {
        // Source: folder named 'data/input'
        // 'noop=true' prevents Camel from deleting the source file (useful for testing)
        from("file:data/input?noop=true")
            .routeId("content-based-file-route")
            .log("Processing file: ${file:name}")
            .choice()
                .when(simple("${body} contains 'important'"))
                    .log("Condition matched: Sending to IMPORTANT")
                    .to("file:data/important")
                
                .otherwise()
                    .log("No match: Sending to NORMAL")
                    .to("file:data/normal")
            .end();
    }
}
```

### 3. Spring Boot Application (`Application.java`)

This is the standard entry point for a Spring Boot app.

```java
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class CamelCbrApplication {
    public static void main(String[] args) {
        SpringApplication.run(CamelCbrApplication.class, args);
    }
}
```

---

### How to test it:

1.  **Create the directories**: In your project root, create a folder structure like this:
    *   `data/input`
    *   `data/important`
    *   `data/normal`

2.  **Run the application**: Start the Spring Boot app (via your IDE or `mvn spring-boot:run`).

3.  **Create Test Files**:
    *   **File 1**: Create a file named `test1.txt` inside `data/input` with the text: 
        > "This is an **important** message."
    *   **File 2**: Create a file named `test2.txt` inside `data/input` with the text: 
        > "This is just a regular message."

4.  **Observe the results**:
    *   Camel will detect the files immediately.
    *   Look at your console logs; you will see Camel routing the files.
    *   Check the `data/important` folder; it should contain `test1.txt`.
    *   Check the `data/normal` folder; it should contain `test2.txt`.

### Key technical notes for this example:

*   **`${body}`**: In Camel's **Simple Language**, this refers to the content of the file. Camel automatically converts the file stream to a String to perform the `contains` check.
*   **`noop=true`**: This is a configuration option for the File component. It stands for "No Operation." By default, Camel moves files to a `.camel` folder or deletes them after processing. `noop=true` ensures the original file stays in `input` for easy debugging.
*   **`.end()`**: This is critical. It tells Camel where the "if/else" logic stops. If you wanted to add more steps that happen to *every* file after the choice logic, you would place them after `.end()`.
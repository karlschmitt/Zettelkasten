# Apache Camel REST DSL with Spring Boot 4.1 & Java 25: An Absolute Beginner Deep Dive

Welcome! In this deep dive tutorial, you will learn how to build modern, lightweight RESTful web services using **Apache Camel's REST DSL** integrated into **Spring Boot 4.1** running on **Java 25**.

---

## 1. Why Camel REST DSL on Spring Boot 4.1 and Java 25?

### What is the REST DSL?
Apache Camel's **REST DSL** (Domain Specific Language) allows you to define RESTful services directly inside your Camel routes using an intuitive, fluent API. Instead of writing standard Spring Controllers (`@RestController`), you can map HTTP endpoints (`GET`, `POST`, `PUT`, `DELETE`) directly into Camel integration workflows.

### Why Spring Boot 4.1 & Java 25?
* **Spring Boot 4.1**: Provides standard Servlet, HTTP/3, and Jakarta EE support with streamlined auto-configuration.
* **Java 25**: Unlocks language features like **Record Patterns**, **Enhanced Virtual Threads (Project Loom)** for high-throughput concurrent I/O, and modern pattern matching.
* **Apache Camel 4**: Fully tuned for modern Java, offering lightweight execution and Jackson 3 JSON binding out of the box.

---

## 2. Setting Up Your Project

### Project Configuration (`pom.xml`)

Ensure your Maven configuration targets **Java 25** and utilizes **Spring Boot 4.1** alongside Camel 4.x components.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 
                             https://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>

    <parent>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-parent</artifactId>
        <version>4.1.0</version>
        <relativePath/>
    </parent>

    <groupId>com.example</groupId>
    <artifactId>camel-rest-demo</artifactId>
    <version>1.0.0-SNAPSHOT</version>
    <name>camel-rest-demo</name>
    <description>Apache Camel REST DSL with Spring Boot 4.1 and Java 25</description>

    <properties>
        <java.version>25</java.version>
        <camel.version>4.10.0</camel.version>
    </properties>

    <dependencies>
        <!-- Spring Boot Starter Web -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>

        <!-- Camel Spring Boot Engine -->
        <dependency>
            <groupId>org.apache.camel.springboot</groupId>
            <artifactId>camel-spring-boot-starter</artifactId>
            <version>${camel.version}</version>
        </dependency>

        <!-- Camel REST & Servlet Components -->
        <dependency>
            <groupId>org.apache.camel.springboot</groupId>
            <artifactId>camel-rest-starter</artifactId>
            <version>${camel.version}</version>
        </dependency>
        <dependency>
            <groupId>org.apache.camel.springboot</groupId>
            <artifactId>camel-servlet-starter</artifactId>
            <version>${camel.version}</version>
        </dependency>

        <!-- Camel Jackson JSON Marshalling -->
        <dependency>
            <groupId>org.apache.camel.springboot</groupId>
            <artifactId>camel-jackson-starter</artifactId>
            <version>${camel.version}</version>
        </dependency>
    </dependencies>

    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-compiler-plugin</artifactId>
                <configuration>
                    <release>25</release>
                </configuration>
            </plugin>
        </plugins>
    </build>
</project>
```

---

## 3. Configuring Application Properties

Configure Camel's REST engine and underlying servlet host inside `src/main/resources/application.properties`:

```properties
# Spring Boot Configuration
server.port=8080

# Camel REST Configuration
camel.rest.component=servlet
camel.rest.context-path=/api/v1
camel.rest.binding-mode=json
camel.servlet.mapping.context-path=/api/v1/*
```

* **`camel.rest.component=servlet`**: Uses Spring's embedded servlet engine (Tomcat/Undertow) to handle incoming HTTP requests.
* **`camel.rest.binding-mode=json`**: Enables automatic marshaling (serialization) and unmarshaling (deserialization) between incoming JSON and Java Records/POJOs.

---

## 4. Modeling Data with Java 25 Records

Leverage Java 25 Records to define concise, immutable data transfer objects (DTOs).

```java
package com.example.camelrestdemo.model;

public record UserDto(
    Long id, 
    String name, 
    String email, 
    String status
) {}
```

---

## 5. Building the Service Layer

Create a Spring Bean component to simulate business logic using Java 25 features:

```java
package com.example.camelrestdemo.service;

import com.example.camelrestdemo.model.UserDto;
import org.springframework.stereotype.Service;

import java.util.Map;
import java.util.Optional;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicLong;

@Service("userService")
public class UserService {

    private final Map<Long, UserDto> userDb = new ConcurrentHashMap<>();
    private final AtomicLong idGenerator = new AtomicLong(100);

    public UserService() {
        userDb.put(101L, new UserDto(101L, "Alice Smith", "alice@example.com", "ACTIVE"));
        userDb.put(102L, new UserDto(102L, "Bob Jones", "bob@example.com", "INACTIVE"));
    }

    public UserDto getUserById(Long id) {
        return Optional.ofNullable(userDb.get(id))
            .orElseThrow(() -> new IllegalArgumentException("User with ID " + id + " not found."));
    }

    public UserDto createUser(UserDto input) {
        Long newId = idGenerator.incrementAndGet();
        UserDto newUser = new UserDto(newId, input.name(), input.email(), "ACTIVE");
        userDb.put(newId, newUser);
        return newUser;
    }
}
```

---

## 6. Defining Routes using REST DSL

Create `UserRestRoute.java` by extending `RouteBuilder`. Annotate it with `@Component` so Spring Boot picks up the routes automatically.

```java
package com.example.camelrestdemo.route;

import com.example.camelrestdemo.model.UserDto;
import com.example.camelrestdemo.service.UserService;
import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestParamType;
import org.springframework.stereotype.Component;

@Component
public class UserRestRoute extends RouteBuilder {

    @Override
    public void configure() throws Exception {

        // Global REST Configuration
        restConfiguration()
            .component("servlet")
            .bindingMode("json")
            .dataFormatProperty("prettyPrint", "true");

        // REST DSL Endpoints Definition
        rest("/users")
            .description("User Management API")

            // 1. GET /api/v1/users/{id}
            .get("/{id}")
                .description("Get user by ID")
                .param().name("id").type(RestParamType.path).dataType("integer").endParam()
                .outType(UserDto.class)
                .to("direct:getUserById")

            // 2. POST /api/v1/users
            .post()
                .description("Create a new user")
                .type(UserDto.class)
                .outType(UserDto.class)
                .to("direct:createUser");

        // --- Route Implementations ---

        // Route: Fetch User By ID
        from("direct:getUserById")
            .routeId("getUserByIdRoute")
            .log("Fetching user with ID: ${header.id}")
            .bean(UserService.class, "getUserById(${header.id})")
            .log("Successfully retrieved user: ${body}");

        // Route: Create User with Java 25 Pattern Matching Logic
        from("direct:createUser")
            .routeId("createUserRoute")
            .log("Received payload for new user creation")
            .process(exchange -> {
                Object body = exchange.getMessage().getBody();
                // Java 25 Record Pattern Matching
                if (body instanceof UserDto(Long id, String name, String email, String status)) {
                    if (email == null || !email.contains("@")) {
                        throw new IllegalArgumentException("Invalid user email provided.");
                    }
                }
            })
            .bean(UserService.class, "createUser")
            .setHeader(Exchange.HTTP_RESPONSE_CODE, constant(201))
            .log("Successfully created user with ID: ${body.id}");
    }
}
```

---

## 7. Main Application Entry Point

```java
package com.example.camelrestdemo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class CamelRestDemoApplication {

    public static void main(String[] args) {
        SpringApplication.run(CamelRestDemoApplication.class, args);
    }
}
```

---

## 8. Testing the Endpoints

Start your Spring Boot application on Java 25 and test the REST endpoints via `curl` or HTTP client.

### Test 1: Fetch Existing User (`GET`)
```bash
curl -X GET http://localhost:8080/api/v1/users/101
```

**Response (`200 OK`)**:
```json
{
  "id": 101,
  "name": "Alice Smith",
  "email": "alice@example.com",
  "status": "ACTIVE"
}
```

### Test 2: Create a New User (`POST`)
```bash
curl -X POST http://localhost:8080/api/v1/users \
  -H "Content-Type: application/json" \
  -d '{"name": "Charlie Brown", "email": "charlie@example.com"}'
```

**Response (`201 Created`)**:
```json
{
  "id": 103,
  "name": "Charlie Brown",
  "email": "charlie@example.com",
  "status": "ACTIVE"
}
```

---

## 9. Next Steps

To build upon this foundation, consider exploring:
1. **OpenAPI / Swagger Generation**: Add `camel-openapi-java-starter` to auto-generate REST documentation.
2. **Global Exception Handling**: Configure `onException(IllegalArgumentException.class)` in Camel to return clean custom JSON HTTP 400 error payloads.
3. **Security Integration**: Secure endpoints with Spring Security and OAuth2/JWT tokens.
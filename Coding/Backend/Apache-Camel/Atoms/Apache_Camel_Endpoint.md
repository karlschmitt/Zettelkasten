---
id: 20260830202830
title: Apache Camel Endpoint
author: Karl Schmitt
date: 2026-08-30
---

# Apache Camel Endpoint

In the context of **Apache Camel** (especially when used with **Spring Boot**), an **Endpoint** is a fundamental building block.
It represents the "start" or the "end" of a message channel.

Think of an endpoint as a **standardized address** that allows Camel to communicate with external systems or internal services, regardless of the protocol they use.

---

### 1. The Anatomy of an Endpoint (The URI)

In Camel, endpoints are defined using a **URI (Uniform Resource Identifier)**. The structure looks like this:

`scheme:contextPath?options`

*   **Scheme:** The component being used (e.g., `file`, `http`, `jms`, `kafka`, `direct`).
*   **Context Path:** The specific location (e.g., a file path, a queue name, or a URL).
*   **Options:** Configuration parameters (e.g., `noop=true`, `delay=5000`).

**Example:**
`file:C:/orders/input?delay=1000`
*   **Scheme:** `file` (uses the File Component).
*   **Path:** `C:/orders/input`.
*   **Option:** Polls every 1000ms.

---

### 2. The Two Roles of an Endpoint

An endpoint acts in one of two ways depending on where it sits in a Camel **Route**:

#### A. Consumer Endpoint (The Source)

This is used at the beginning of a route using the `from()` method. It **receives** or **polls** messages from an external system and brings them into the Camel engine.
*   *Example:* `from("timer:tick?period=5000")` — This endpoint "consumes" a trigger every 5 seconds.

#### B. Producer Endpoint (The Destination)

This is used later in the route using the `to()` method. It **sends** the processed message to an external system.
*   *Example:* `.to("jms:queue:orders")` — This endpoint "produces" a message and sends it to an ActiveMQ queue.

---

### 3. How it looks in Spring Boot

In a Spring Boot application, you typically define these inside a `RouteBuilder` class.

```java
@Component
public class MyRoute extends RouteBuilder {
    @Override
    public void configure() {
        // 1. Consumer Endpoint: Watching a folder for files
        from("file:data/input")
          .log("Processing file: ${header.CamelFileName}")
          
        // 2. Producer Endpoint: Sending the content to a REST API
          .to("http://api.myservice.com/v1/data");
    }
}
```

---

### 4. Relationship: Component vs. Endpoint

It is helpful to understand the hierarchy:
1.  **Component:** A factory for endpoints (e.g., the `JmsComponent`). In Spring Boot, these are often auto-configured via `application.properties`.
2.  **Endpoint:** A specific instance created by the component based on a URI (e.g., `jms:queue:myQueue`).
3.  **Exchange:** The actual message container that travels between endpoints.

---

### 5. Common Endpoint Types

*   **Direct:** `direct:startName` (Internal synchronous calling between routes).
*   **Seda:** `seda:nextStep` (Internal asynchronous calling using a blocking queue).
*   **Bean:** `bean:myService?method=doSomething` (Calls a Spring-managed bean).
*   **Rest:** `rest:get:/users` (Exposes a REST service).
*   **Log:** `log:myLogger` (Prints the message to the console/file).

### Summary
An **Endpoint** is the connection point between Apache Camel and the rest of the world. By using a URI-based configuration, Camel abstracts away the complexity of different protocols, allowing you to treat a file on a disk, a message in a queue, and a row in a database all as uniform "endpoints."
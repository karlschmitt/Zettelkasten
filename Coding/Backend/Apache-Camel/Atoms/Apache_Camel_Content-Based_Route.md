---
id: 20260904202048
title: Content-Based Route
author: Karl Schmitt
date: 2026-09-04
keywords: [ Spring Boot, Apache Camel, CBR, EIP]
---

# Content-Based Route

In the context of **Apache Camel** and **Spring Boot**, a **Content-Based Route (CBR)** is a fundamental Enterprise Integration Pattern (EIP). 

It acts like a **logical router** that inspects the content of a message (its body, headers, or properties) and directs it to a specific destination based on predefined criteria.

Think of it as the **`if-else`** or **`switch`** statement for message integration.

---

### 1. How it works

The CBR evaluates a **Predicate** (a condition that returns true or false). 
- If the predicate is true, the message is sent to that specific endpoint.
- If it is false, it moves to the next condition.
- If no conditions match, it can be sent to a default "otherwise" destination.

### 2. The DSL Syntax (Java)

In Apache Camel, you implement this using the `choice()`, `when()`, and `otherwise()` methods.

```java
import org.apache.camel.builder.RouteBuilder;
import org.springframework.stereotype.Component;

@Component
public class MyOrderRouter extends RouteBuilder {
    @Override
    public void configure() throws Exception {
        from("direct:processOrder")
            .choice()
                .when(header("type").isEqualTo("widget"))
                    .to("jms:queue:widget-orders")
                
                .when(simple("${body.priority} == 'high'"))
                    .to("jms:queue:priority-orders")
                
                .otherwise()
                    .to("jms:queue:general-orders")
            .end(); // Marks the end of the choice block
    }
}
```

### 3. Key Components of the CBR

1.  **`choice()`**: Starts the routing block.
2.  **`when(Predicate)`**: Defines a condition. You can use various "Languages" to evaluate the message:
    *   **Simple Language**: `${body.name} == 'John'` (Most common).
    *   **XPath**: To route based on XML content.
    *   **JSONPath**: To route based on JSON content.
    *   **Header/Property**: Checking metadata.
3.  **`otherwise()`**: (Optional) The "else" block. If no `when` matches, the message goes here.
4.  **`end()`**: Closes the choice block so you can continue the route with logic that applies to *all* messages regardless of which branch they took.

### 4. Why use it in Spring Boot?

Spring Boot provides the runtime and dependency management for Camel. Using CBRs within Spring Boot allows you to:
*   **Decouple Systems**: The sender doesn't need to know where the message is going; the router decides.
*   **Dynamic Routing**: You can change routing logic by updating a single RouteBuilder class.
*   **Integration**: Easily route messages between different Spring Beans, databases, or external APIs (REST, Kafka, MQ).

### 5. Common Use Cases

*   **Sorting Files**: Moving `.txt` files to one folder and `.xml` files to another.
*   **Priority Processing**: Routing "VIP" customers to a fast-track processing service.
*   **Regional Routing**: Sending data to different databases based on a `region` header in a JSON payload.
*   **Error Handling**: Routing malformed messages to a "Dead Letter Channel" for manual review.

### Summary

A **Content-Based Route** is Apache Camel's way of making decisions. It looks inside the "envelope" (the message) and decides which path it should take based on what it finds inside.
---
id: 20260903093742
title: Exposing and Consuming REST APIs with Spring Boot and Apache Camel
author: Karl Schmitt
date: 2026-09-03
---

# Exposing and Consuming REST APIs with Spring Boot and Apache Camel

To use Apache Camel with Spring Boot for REST operations, you typically use the **Rest DSL** for exposing APIs and the **HTTP component** for consuming external APIs.

Here is a complete example.

### 1. Project Dependencies (Maven)

You will need the `camel-spring-boot-starter`, the `servlet` component (to expose the API), and the `http` component (to consume the API).

```xml
<dependencies>
    <!-- Camel Spring Boot Starter -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-spring-boot-starter</artifactId>
        <version>4.8.0</version> <!-- Use the latest version -->
    </dependency>

    <!-- For Exposing REST APIs via Servlet -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-servlet-starter</artifactId>
        <version>4.8.0</version>
    </dependency>

    <!-- For Consuming External APIs -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-http-starter</artifactId>
        <version>4.8.0</version>
    </dependency>

    <!-- For JSON Marshalling/Unmarshalling -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-jackson-starter</artifactId>
        <version>4.8.0</version>
    </dependency>

    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-web</artifactId>
    </dependency>
</dependencies>
```

---

### 2. Configuration (`application.properties`)

Tell Camel to map its REST service to a specific context path (like `/camel/*`).

```properties
# Set the context path for Camel Servlet
camel.servlet.mapping.context-path=/api/*
```

---

### 3. The Route Definition

This single class handles both **Exposing** a local endpoint and **Consuming** the Star Wars API (SWAPI).

```java
import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;
import org.springframework.stereotype.Component;

@Component
public class StarWarsRoute extends RouteBuilder {

    @Override
    public void configure() throws Exception {

        // 1. Configure the REST DSL
        restConfiguration()
            .component("servlet")
            .bindingMode(RestBindingMode.json);

        // 2. EXPOSE the REST API
        // This creates an endpoint: GET http://localhost:8080/api/sw/character/{id}
        rest("/sw")
            .get("/character/{id}")
                .description("Fetch a Star Wars character by ID")
                .to("direct:fetchFromSwapi");

        // 3. CONSUME the External API (SWAPI)
        from("direct:fetchFromSwapi")
            // Step A: Set up headers for the external call
            .removeHeader(Exchange.HTTP_PATH) // Clear path to avoid conflicts
            .setHeader(Exchange.HTTP_METHOD, constant("GET"))
            
            // Step B: Call the external API
            // we use toD (dynamic to) to inject the ID from the path parameter
            .toD("https://swapi.dev/api/people/${header.id}/?bridgeEndpoint=true")
            
            // Step C: Log the response
            .log("Response from SWAPI: ${body}")
            
            // Optional: You could unmarshal the JSON into a Java POJO here
            // .unmarshal().json(JsonLibrary.Jackson, MyCharacterDto.class)
            .process(exchange -> {
                // You can manipulate the response here if needed
                String body = exchange.getIn().getBody(String.class);
                exchange.getIn().setBody(body);
            });
    }
}
```

---

### 4. How it works

1.  **Exposing (`rest("/sw").get(...)`)**: 
    *   Camel starts a listener on `/api/sw/character/{id}`. 
    *   The `{id}` is automatically stored in a Camel Header named `id`.

2.  **Bridging**: 
    *   The `to("direct:fetchFromSwapi")` sends the message to an internal route.

3.  **Consuming (`toD("https://...")`)**: 
    *   `toD` stands for "To Dynamic." It allows us to use the Simple language (`${header.id}`) to construct the URL.
    *   `bridgeEndpoint=true` is a standard practice when proxying APIs to ensure that the URI sent to the external server is correct and doesn't include the local context path.

### 5. Testing the API

1. Run your Spring Boot application.
2. Open your browser or [PowerShell](../Atoms/Querying_REST_APIs_with_Invoke-RestMethod.md).
3. Call your local API: `GET http://localhost:8080/api/sw/character/1`

**Expected Result:**
You will receive the JSON response for Luke Skywalker directly from the Star Wars API, proxied through your Spring Boot application.

### Key Advantages of using Camel here:

*   **Protocol Agnostic**: You can change the external call from HTTP to `activemq` or `ftp` by changing one line of code.
*   **Error Handling**: You can easily add `.onException(Exception.class).retryAttemptedLogLevel(LoggingLevel.WARN).maximumRedeliveries(3)` to handle external API downtime.
*   **Data Transformation**: You can easily convert the SWAPI JSON into XML or a different JSON schema using Camel's `marshal/unmarshal` features.
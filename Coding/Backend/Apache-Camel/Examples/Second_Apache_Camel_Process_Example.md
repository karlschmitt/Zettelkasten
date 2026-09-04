---
id: 20260904121702
title: Bridging the Galaxy with Apache Camel
author: Karl Schmitt
date: 2026-09-04
---

# Bridging the Galaxy with Apache Camel

This is a perfect scenario for a Coding Dojo! 
It covers **REST DSL**, **External API Integration**, **Data Transformation (Processor)**, and **Database Connectivity**.

### Prerequisites

1. **PostgreSQL**: Ensure you have a database named `dojo_db`.
2. **Table Schema**: Run this SQL to prepare your database:
```sql
CREATE TABLE star_wars_characters (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255),
    height VARCHAR(50),
    mass VARCHAR(50),
    processed_at TIMESTAMP
);
```
> [NOTE!]
> Feel free to create your database like this: [The Jedi Archives](./The_Jedi_Archives.md)

---

### 1. Project Dependencies (`pom.xml`)
You need the starters for Web, REST, HTTP (to call SWAPI), and SQL (for Postgres).

```xml
<dependencies>
    <!-- Camel & Spring Boot -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-spring-boot-starter</artifactId>
        <version>4.0.0</version>
    </dependency>
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-rest-starter</artifactId>
        <version>4.0.0</version>
    </dependency>
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-servlet-starter</artifactId>
        <version>4.0.0</version>
    </dependency>
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-http-starter</artifactId>
        <version>4.0.0</version>
    </dependency>
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-sql-starter</artifactId>
        <version>4.0.0</version>
    </dependency>
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-jackson-starter</artifactId>
        <version>4.0.0</version>
    </dependency>

    <!-- Postgres Driver -->
    <dependency>
        <groupId>org.postgresql</groupId>
        <artifactId>postgresql</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>
```

---

### 2. Configuration (`application.properties`)
Configure your database connection and the Camel REST port.

```properties
# Server Port
server.port=8080

# PostgreSQL Connection
spring.datasource.url=jdbc:postgresql://localhost:5432/dojo_db
spring.datasource.username=postgres
spring.datasource.password=yourpassword
spring.datasource.driver-class-name=org.postgresql.Driver

# Camel REST Configuration
camel.rest.context-path=/api/*
```

---

### 3. The Processor (`StarWarsProcessor.java`)
This processor takes the raw JSON string from the Star Wars API, converts it into a Map, and prepares the parameters for the SQL query.

```java
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.stereotype.Component;
import java.util.Map;
import java.util.HashMap;

@Component
public class StarWarsProcessor implements Processor {

    private final ObjectMapper objectMapper = new ObjectMapper();

    @Override
    public void process(Exchange exchange) throws Exception {
        // 1. Read the JSON body from SWAPI response
        String json = exchange.getIn().getBody(String.class);
        
        // 2. Parse JSON to Map
        Map<String, Object> data = objectMapper.readValue(json, Map.class);
        
        // 3. Extract specific fields
        Map<String, Object> dbParams = new HashMap<>();
        dbParams.put("name", data.get("name"));
        dbParams.put("height", data.get("height"));
        dbParams.put("mass", data.get("mass"));
        
        // 4. Set as body - The SQL component will use this Map to fill the query
        exchange.getIn().setBody(dbParams);
        
        // Bonus: Log what we found
        System.out.println("Processor transformed data for: " + data.get("name"));
    }
}
```

---

### 4. The Camel Route (`StarWarsRoute.java`)
This is the heart of the Dojo. It defines the REST endpoint, calls the external API, processes the result, and saves it.

```java
import org.apache.camel.Exchange;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.model.rest.RestBindingMode;
import org.springframework.stereotype.Component;

@Component
public class StarWarsRoute extends RouteBuilder {

    @Override
    public void configure() throws Exception {
        
        // Configure REST DSL
        restConfiguration()
            .component("servlet")
            .bindingMode(RestBindingMode.auto);

        // Expose endpoint: GET http://localhost:8080/api/swapi/person/{id}
        rest("/swapi")
            .get("/person/{id}")
            .to("direct:fetchAndStore");

        from("direct:fetchAndStore")
            .routeId("swapi-fetcher")
            // 1. Remove headers to avoid side-effects when calling external API
            .removeHeader(Exchange.HTTP_PATH) 
            
            // 2. Call Star Wars API (SWAPI)
            // ${header.id} comes from the REST path parameter
            .setHeader(Exchange.HTTP_METHOD, constant("GET"))
            .toD("https://swapi.dev/api/people/${header.id}/?bridgeEndpoint=true")
            
            // 3. Pass the JSON response to our Processor
            .process("starWarsProcessor")
            
            // 4. Insert into PostgreSQL using the SQL component
            // The Named Parameters (:#name, etc) match the keys in our Processor's Map
            .to("sql:INSERT INTO star_wars_characters (name, height, mass, processed_at) " +
                "VALUES (:#name, :#height, :#mass, NOW())")
            
            // 5. Final Response to the user
            .setBody(constant("Character successfully imported to Database!"));
    }
}
```

---

### How to run the Dojo exercise:

1.  **Start your Postgres database.**
2.  **Run the Spring Boot application.**
3.  **Trigger the flow:** Open your browser or use `curl`:
    ```bash
    curl http://localhost:8080/api/swapi/person/1
    ```
    *(ID 1 is Luke Skywalker)*
4.  **Verify the DB:**
    ```sql
    SELECT * FROM star_wars_characters;
    ```

### Why this is a good Dojo example:
1.  **Header Management**: Show participants how Camel passes headers from the REST request all the way to the HTTP call, and why we sometimes need to clean them.
2.  **Dynamic To (`toD`)**: Demonstrate how to inject variables into an endpoint URI.
3.  **Processor Responsibility**: Explain that the Processor is used to bridge the gap between the *Format of the API* (JSON) and the *Format of the Database* (SQL Map).
4.  **Error Handling (Next Step)**: You can challenge the group to add an `onException` block in case the Star Wars API is down or the ID doesn't exist.
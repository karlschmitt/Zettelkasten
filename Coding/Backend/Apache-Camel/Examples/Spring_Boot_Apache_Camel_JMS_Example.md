---
id: 20260829200203
title: Spring Boot and Apache Camel JMS Integration Guide
author: Karl Schmitt
date: 2026-08-29
---

> [NOTE!]
> Dieser Text bietet eine praktische Einführung in die Integration von **Spring Boot, Apache Camel und JMS** mithilfe von ActiveMQ Artemis. Der Autor erläutert den Aufbau einer funktionalen Pipeline, die **HTTP-Anfragen** empfängt und diese über **Camel-Routen** an eine JMS-Queue weiterleitet. Ein zentraler Aspekt ist die Unterscheidung zwischen **Produzenten und Konsumenten**, wobei Camel als Vermittler zwischen verschiedenen Protokollen agiert. Zudem wird das Konzept des **JMS-Bridges** thematisiert, das den Datenaustausch zwischen verschiedenen Messaging-Systemen ermöglicht. Abschließend verdeutlicht der Text die wichtige technische Differenzierung zwischen einem **Camel-Exchange** und der tatsächlichen **JMS-Nachricht**.

# Spring Boot and Apache Camel JMS Integration Guide

Let's build a **small but realistic Spring Boot + Apache Camel JMS example**.

I'll deliberately show the flow in a way that makes the relationship between **HTTP → Camel → JMS** very clear.

# Spring Boot + Apache Camel + JMS

We will build this:

```text
             HTTP
              │
              │ POST /api/orders
              ▼
       ┌───────────────┐
       │ Apache Camel  │
       │ REST endpoint │
       └───────┬───────┘
               │
               ▼
       ┌───────────────┐
       │ Camel Route   │
       │               │
       │ transform     │
       │ JSON          │
       └───────┬───────┘
               │
               ▼
       ┌───────────────┐
       │ JMS Producer  │
       └───────┬───────┘
               │
               │ JMS message
               ▼
       ┌────────────────┐
       │ JMS Queue      │
       │                │
       │ ORDER.QUEUE    │
       └───────┬────────┘
               │
               ▼
       ┌───────────────┐
       │ JMS Consumer  │
       │ Camel Route   │
       └───────────────┘
```

The nice thing is that we can see **both sides of JMS**:

```text
Camel → JMS Queue
JMS Queue → Camel
```

***

# 1. The application

We'll use:

* Spring Boot

* Apache Camel

* JMS

* ActiveMQ Artemis

![Image](https://images.openai.com/static-rsc-4/ML_1pnyAw7HHjbi2qMTtbl3JnYYDPr-Kt2YO7BDzEnL-e_YVgRbVO7QCIsg0pONYGsbfd8MQ_nu6qP9wuNhB6kgsERhpvgQMNJN-cK8y3iGkJOTWAXZmsSJMnkz5-WZNAanFlMj1pVnOjIvl3Y-0477mLsEz55OPk-dIqSHbL1yyYUAC6GIT1D1zFSNA1-c7?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/HfMS5wrUSMnGYPqUaZzjWBjyd1aQ4VbszvazmNVmw7i_NKajHDRvjX304HiozESvCzQTV72VD4_tCbP-emkw_YAFW7ey30X2IdYR0NHRJNYnYcC0P8e5OWAAR0LnVoOHW5UUjECR5Nw8pySypT4yaKsHhWB1P2-L1bQ95Favb2pWbohr7ZPt9drcUIto1y8e?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/xCV-j6khgb4S1uPPZKF5mszm5-EoMrlqBuEinT6WCZqnwcsm33zj7OkdWwb9C8sCFklYDMe4qvH_k-ohSQkfoNSlKMR-H6DJ4zdpeS0AocDpjRJV7l_rfLG0pVPey1iuo3bzKSrrl8t67i8rPAHRAMq24NHU3uNmsK2G-XKeG_mCSm_2Fga4tfsCeRHHTkcI?purpose=fullsize)

The important point is that **Camel doesn't itself provide the JMS broker**.

We have:

```text
Spring Boot
     │
     ▼
Apache Camel
     │
     ▼
JMS component
     │
     ▼
ActiveMQ Artemis
     │
     ▼
JMS Queue
```

***

# 2. Maven dependencies

For a Maven project, add:

```xml
<dependencies>

    <!-- Spring Boot -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter</artifactId>
    </dependency>

    <!-- Camel -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-spring-boot-starter</artifactId>
    </dependency>

    <!-- Camel REST -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-rest-starter</artifactId>
    </dependency>

    <!-- Camel Servlet -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-servlet-starter</artifactId>
    </dependency>

    <!-- Camel JMS -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-jms-starter</artifactId>
    </dependency>

    <!-- ActiveMQ Artemis -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-artemis</artifactId>
    </dependency>

</dependencies>
```

For a real project, use a single compatible Spring Boot/Camel version set, ideally generated or managed through the appropriate BOM.

***

# 3. Start ActiveMQ Artemis

For learning, Docker is an easy way to run the JMS broker.

For example:

```powershell
docker run `
  --name artemis `
  -p 61616:61616 `
  -p 8161:8161 `
  apache/activemq-artemis:latest-alpine
```

Conceptually:

```text
Windows
  │
  └── Docker
        │
        └── ActiveMQ Artemis
                │
                └── port 61616
```

The JMS connection will use:

```text
tcp://localhost:61616
```

***

# 4. Configure the JMS connection

Create:

```text
src/main/resources/application.properties
```

```properties
spring.artemis.broker-url=tcp://localhost:61616
spring.artemis.user=admin
spring.artemis.password=admin

camel.servlet.mapping.context-path=/camel/*
```

Now Spring Boot creates/configures the JMS infrastructure.

***

# 5. Our HTTP request

We'll send this:

```http
POST /api/orders
```

with:

```json
{
    "orderId": "ORD-1001",
    "customer": "Karl",
    "product": "Laptop",
    "quantity": 2
}
```

We want Camel to put that JSON into:

```text
ORDER.QUEUE
```

***

# 6. Create the Camel route

Create:

```text
src/main/java/alice/alice/camel/routes/OrderRoute.java
```

```java
package alice.alice.camel.routes;

import org.apache.camel.builder.RouteBuilder;
import org.springframework.stereotype.Component;

@Component
public class OrderRoute extends RouteBuilder {

    @Override
    public void configure() {

        rest("/api")
            .post("/orders")
            .consumes("application/json")
            .produces("text/plain")
            .to("direct:orders");

        from("direct:orders")
            .routeId("http-to-jms")
            .log(">>> HTTP order received <<<")
            .log("Order: ${body}")

            .setHeader("JMSCorrelationID")
                .simple("${header.CamelHttpRequestId}")

            .to("jms:queue:ORDER.QUEUE")

            .setBody(constant("Order sent to JMS"));
    }
}
```

This is our first important integration route:

```text
HTTP
 │
 ▼
direct:orders
 │
 ▼
jms:queue:ORDER.QUEUE
```

***

# 7. Understanding `jms:queue:ORDER.QUEUE`

This line:

```java
.to("jms:queue:ORDER.QUEUE")
```

is the important part.

It means:

> Send the current Camel message to the JMS queue named `ORDER.QUEUE`.

So:

```text
Camel message
     │
     ▼
.to("jms:queue:ORDER.QUEUE")
     │
     ▼
JMS message
     │
     ▼
ORDER.QUEUE
```

Camel performs the conversion between its internal message representation and the JMS message.

***

# 8. What is actually inside the JMS message?

Suppose the HTTP request contains:

```json
{
    "orderId": "ORD-1001",
    "customer": "Karl",
    "product": "Laptop",
    "quantity": 2
}
```

Camel receives an `Exchange`.

Conceptually:

```text
Exchange
│
├── Message
│   │
│   ├── Headers
│   │
│   └── Body
│       │
│       └── JSON
│
└── Properties
```

The body is:

```text
{
    "orderId": "ORD-1001",
    "customer": "Karl",
    "product": "Laptop",
    "quantity": 2
}
```

Then:

```java
.to("jms:queue:ORDER.QUEUE")
```

creates a JMS message.

For example, conceptually:

```text
JMS Message
│
├── JMSMessageID
├── JMSCorrelationID
├── JMSDestination
├── JMSPriority
├── JMSType
│
└── Body
      │
      └── JSON
```

***

# 9. Now let's consume the JMS message

This is the other direction.

Add another route to `OrderRoute`:

```java
from("jms:queue:ORDER.QUEUE")
    .routeId("jms-order-consumer")
    .log(">>> JMS message received <<<")
    .log("JMS Message ID: ${header.JMSMessageID}")
    .log("JMS Correlation ID: ${header.JMSCorrelationID}")
    .log("JMS Body: ${body}");
```

Now our application contains **two routes**.

### Producer

```java
from("direct:orders")
    .to("jms:queue:ORDER.QUEUE");
```

### Consumer

```java
from("jms:queue:ORDER.QUEUE")
    .log("JMS Body: ${body}");
```

***

# 10. Complete example

The whole `OrderRoute.java` is therefore:

```java
package alice.alice.camel.routes;

import org.apache.camel.builder.RouteBuilder;
import org.springframework.stereotype.Component;

@Component
public class OrderRoute extends RouteBuilder {

    @Override
    public void configure() {

        // HTTP -> Camel
        rest("/api")
            .post("/orders")
            .consumes("application/json")
            .produces("text/plain")
            .to("direct:orders");


        // Camel -> JMS
        from("direct:orders")
            .routeId("http-to-jms")
            .log(">>> HTTP order received <<<")
            .log("Order: ${body}")

            .setHeader("JMSCorrelationID")
                .simple("${header.CamelHttpRequestId}")

            .to("jms:queue:ORDER.QUEUE")

            .setBody(constant("Order sent to JMS"));


        // JMS -> Camel
        from("jms:queue:ORDER.QUEUE")
            .routeId("jms-order-consumer")
            .log(">>> JMS message received <<<")
            .log("JMS Message ID: ${header.JMSMessageID}")
            .log("JMS Correlation ID: ${header.JMSCorrelationID}")
            .log("JMS Body: ${body}");
    }
}
```

***

# 11. Test it with PowerShell

Start your Spring Boot application:

```powershell
.\mvnw.cmd spring-boot:run
```

Then send:

```powershell
curl.exe `
  -X POST `
  http://localhost:8080/camel/api/orders `
  -H "Content-Type: application/json" `
  -d '{\"orderId\":\"ORD-1001\",\"customer\":\"Karl\",\"product\":\"Laptop\",\"quantity\":2}'
```

Or using PowerShell:

```powershell
$body = @{
    orderId  = "ORD-1001"
    customer = "Karl"
    product  = "Laptop"
    quantity = 2
} | ConvertTo-Json

Invoke-RestMethod `
    -Method Post `
    -Uri "http://localhost:8080/camel/api/orders" `
    -ContentType "application/json" `
    -Body $body
```

The HTTP response should be:

```text
Order sent to JMS
```

***

# 12. Look at the Camel logs

You should see something conceptually like:

```text
>>> HTTP order received <<<
Order: {
    "orderId": "ORD-1001",
    "customer": "Karl",
    "product": "Laptop",
    "quantity": 2
}

>>> JMS message received <<<
JMS Message ID: ID:...
JMS Correlation ID: ...
JMS Body: {
    "orderId": "ORD-1001",
    "customer": "Karl",
    "product": "Laptop",
    "quantity": 2
}
```

So the complete flow is:

```text
┌─────────────────┐
│ PowerShell/curl │
└────────┬────────┘
         │
         │ POST JSON
         ▼
┌─────────────────────┐
│ Camel REST endpoint │
│ /api/orders         │
└──────────┬──────────┘
           │
           ▼
     direct:orders
           │
           ▼
┌─────────────────────┐
│ Camel JMS component │
└──────────┬──────────┘
           │
           │ JMS
           ▼
┌─────────────────────┐
│ ActiveMQ Artemis    │
│                     │
│ ORDER.QUEUE         │
└──────────┬──────────┘
           │
           │ JMS
           ▼
┌─────────────────────┐
│ Camel JMS consumer  │
└──────────┬──────────┘
           │
           ▼
          log
```

***

# 13. The really important Camel concept

There is a very useful pattern hiding here:

```java
from("jms:queue:ORDER.QUEUE")
```

is a **JMS consumer**.

Whereas:

```java
.to("jms:queue:ORDER.QUEUE")
```

is a **JMS producer**.

So:

| Camel code                      | Meaning          |
| ------------------------------- | ---------------- |
| `from("jms:queue:ORDER.QUEUE")` | Receive from JMS |
| `.to("jms:queue:ORDER.QUEUE")`  | Send to JMS      |

This is worth memorizing.

### Consumer

```java
from("jms:queue:ORDER.QUEUE")
```

means:

> "Camel, listen to this JMS queue."

### Producer

```java
.to("jms:queue:ORDER.QUEUE")
```

means:

> "Camel, send this message to this JMS queue."

***

# 14. And this connects directly to a JMS Bridge

This is where Apache Camel becomes particularly interesting for your use case.

Imagine:

```text
              JMS Broker A
              ActiveMQ
                  │
                  │
                  ▼
        ┌───────────────────┐
        │   Camel Bridge    │
        │                   │
        │ from("jms:...")   │
        │        │          │
        │        ▼          │
        │     transform     │
        │        │          │
        │        ▼          │
        │   to("jms:...")   │
        └─────────┬─────────┘
                  │
                  ▼
              JMS Broker B
                 Tibco
```

In code, the fundamental pattern is simply:

```java
from("jms:queue:SOURCE.QUEUE")
    .to("jms:queue:TARGET.QUEUE");
```

That's essentially the **heart of a JMS-to-JMS bridge**.

You can then add:

```java
.log(...)
.choice()
.when(...)
.transform(...)
.setHeader(...)
.removeHeader(...)
.onException(...)
```

around that basic flow.

***

## One subtle but important distinction

There are actually **three different things** in our example:

```text
HTTP
 │
 ▼
Camel Exchange
 │
 ▼
JMS Message
```

The **Camel Exchange is not the JMS message**.

Camel receives the HTTP request and creates/processes an `Exchange`. When we execute:

```java
.to("jms:queue:ORDER.QUEUE")
```

Camel's JMS component takes the Camel message and creates/sends a JMS message to the broker.

Likewise, when:

```java
from("jms:queue:ORDER.QUEUE")
```

receives a JMS message, Camel creates an `Exchange` around that incoming message.

That distinction—**Exchange ↔ JMS Message ↔ Broker Queue**—is one of the key concepts to understand before going deeper into Camel JMS.

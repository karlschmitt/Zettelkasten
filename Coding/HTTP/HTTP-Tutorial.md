---
id: 20260902113038
title: HTTP Tutorial
author: Karl Schmitt
date: 2026-09-02
keywords: [ HTTP, Node.js, Express.js, PowerShell, Wireshark]
---

# HTTP Tutorial

Absolutely. Since you're learning **Node.js/Express.js** and also working with **HTTP, Spring Boot, and Apache Camel**, this is a very useful exercise: we'll build a tiny HTTP server and then use **PowerShell as the HTTP client** and **Wireshark to see what actually travels over the network**.

## HTTP with Node.js + Express.js + PowerShell + Wireshark

We'll build this progressively:

```text
┌──────────────┐
│  PowerShell  │
│    client    │
└──────┬───────┘
       │
       │ HTTP request
       │ GET /hello
       ▼
┌──────────────────┐
│ Node.js          │
│ Express.js       │
│                  │
│ HTTP Server      │
└────────┬─────────┘
         │
         │ HTTP response
         ▼
┌──────────────┐
│  PowerShell  │
└──────────────┘

          ▲
          │
     Wireshark
     observes
     packets
```

The goal is **not just to learn Express**. The goal is to understand HTTP from the bottom up:

```text
HTTP
  ↓
TCP
  ↓
IP
  ↓
Ethernet / Wi-Fi
  ↓
Network
```

***

# 1. What you will learn

By the end, you should understand:

* what an HTTP server is

* what an HTTP client is

* what Node.js does

* what Express.js does

* what an HTTP request looks like

* what an HTTP response looks like

* HTTP methods: `GET`, `POST`, `PUT`, `DELETE`

* URL paths

* query parameters

* HTTP headers

* HTTP status codes

* HTTP request bodies

* JSON

* TCP vs. HTTP

* ports

* `localhost`

* how PowerShell can act as an HTTP client

* how to inspect HTTP traffic with Wireshark

* the relationship between HTTP and TCP

And we'll deliberately compare this with the concepts you have already encountered in **Spring Boot** and **Apache Camel**.

***

# 2. The mental model

Start with this simple picture:

```text
CLIENT                         SERVER

PowerShell                    Node.js
    │                            │
    │──── HTTP Request ─────────>│
    │                            │
    │<─── HTTP Response ─────────│
    │                            │
```

For example:

```http
GET /hello HTTP/1.1
Host: localhost:3000
```

The server might answer:

```http
HTTP/1.1 200 OK
Content-Type: text/plain

Hello from Node.js!
```

That's the fundamental HTTP conversation.

***

# 3. Prerequisites

You need:

### Node.js

Check:

```powershell
node --version
```

and:

```powershell
npm --version
```

You should get something similar to:

```text
v24.x.x
11.x.x
```

The exact versions aren't important for this tutorial.

### PowerShell

You already have this.

We'll use commands such as:

```powershell
Invoke-WebRequest
```

and:

```powershell
Invoke-RestMethod
```

rather than [Bruno](https://www.usebruno.com/).

### Wireshark

Install [Wireshark](https://www.wireshark.org/) if you haven't already.

Once installed, we'll use it to watch:

```text
PowerShell
   │
   ▼
localhost:3000
   │
   ▼
Node.js
```

***

# 4. Create our first Node.js project

Create a directory:

```powershell
mkdir http-node-tutorial
cd http-node-tutorial
```

Initialize npm:

```powershell
npm init -y
```

You now have:

```text
http-node-tutorial/
└── package.json
```

Install Express:

```powershell
npm install express
```

Now:

```text
http-node-tutorial/
├── node_modules/
├── package-lock.json
└── package.json
```

***

# 5. Our first Express server

Create:

```text
server.js
```

Put this into it:

```javascript
const express = require("express");

const app = express();

const PORT = 3000;

app.get("/hello", (req, res) => {
    res.send("Hello from Express!");
});

app.listen(PORT, () => {
    console.log(`HTTP server listening on port ${PORT}`);
});
```

Start it:

```powershell
node server.js
```

You should see:

```text
HTTP server listening on port 3000
```

Our architecture is now:

```text
             localhost
                │
                │
        ┌───────▼────────┐
        │ Node.js        │
        │                │
        │ Express        │
        │                │
        │ port 3000      │
        └───────┬────────┘
                │
             /hello
```

***

# 6. What does Express actually do?

This line:

```javascript
const express = require("express");
```

loads Express.

This:

```javascript
const app = express();
```

creates an Express application.

And this:

```javascript
app.get("/hello", ...)
```

means:

> When an HTTP `GET` request arrives for `/hello`, execute this function.

Conceptually:

```text
HTTP GET /hello
       │
       ▼
┌─────────────────┐
│ Express routing │
└────────┬────────┘
         │
         │ matches
         ▼
      "/hello"
         │
         ▼
   JavaScript function
```

This should look familiar from Spring Boot.

### Express

```javascript
app.get("/hello", (req, res) => {
    res.send("Hello!");
});
```

### Spring Boot

Conceptually:

```java
@GetMapping("/hello")
public String hello() {
    return "Hello!";
}
```

Same fundamental idea:

```text
HTTP Request
     ↓
URL mapping
     ↓
application code
     ↓
HTTP Response
```

***

# 7. Your first HTTP request with PowerShell

Leave the Node.js server running.

Open a **second PowerShell window**.

Execute:

```powershell
Invoke-WebRequest http://localhost:3000/hello
```

You should get a response containing something similar to:

```text
StatusCode        : 200
StatusDescription : OK
Content           : Hello from Express!
```

Congratulations.

You have just performed an HTTP request.

***

# 8. Use curl instead

PowerShell also gives you access to `curl`.

On modern Windows:

```powershell
curl.exe http://localhost:3000/hello
```

You'll see:

```text
Hello from Express!
```

I recommend using `curl.exe` explicitly because PowerShell historically aliases `curl` to `Invoke-WebRequest`.

***

# 9. What actually happened?

When you execute:

```powershell
curl.exe http://localhost:3000/hello
```

conceptually this happens:

```text
curl
 │
 │ HTTP request
 ▼
localhost:3000
 │
 ▼
Node.js
 │
 ▼
Express
 │
 ▼
GET /hello
 │
 ▼
res.send(...)
 │
 ▼
HTTP response
 │
 ▼
curl
```

The request is approximately:

```http
GET /hello HTTP/1.1
Host: localhost:3000
User-Agent: curl/...
Accept: */*
```

The response is approximately:

```http
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 20

Hello from Express!
```

**This is HTTP.**

***

# 10. HTTP request anatomy

Let's examine:

```http
GET /hello HTTP/1.1
Host: localhost:3000
User-Agent: curl/8.x
Accept: */*
```

There are several important pieces.

## HTTP method

```text
GET
```

means:

> I want to retrieve something.

***

## Request target

```text
/hello
```

This is the path.

***

## HTTP version

```text
HTTP/1.1
```

***

## Header

```text
Host: localhost:3000
```

The HTTP header provides additional information.

Another header:

```text
Accept: */*
```

means roughly:

> I can accept any media type.

***

# 11. HTTP response anatomy

The server responds:

```http
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 20

Hello from Express!
```

The first line:

```text
HTTP/1.1 200 OK
```

contains:

```text
HTTP version
     │
     ▼
HTTP/1.1  200  OK
         │
         └── status code
```

`200` means:

> The request succeeded.

***

# 12. Add another endpoint

Modify `server.js`:

```javascript
const express = require("express");

const app = express();

const PORT = 3000;

app.get("/hello", (req, res) => {
    res.send("Hello from Express!");
});

app.get("/goodbye", (req, res) => {
    res.send("Goodbye!");
});

app.listen(PORT, () => {
    console.log(`HTTP server listening on port ${PORT}`);
});
```

Restart Node.js.

Then:

```powershell
curl.exe http://localhost:3000/goodbye
```

Result:

```text
Goodbye!
```

You now have two HTTP endpoints:

```text
GET /hello
GET /goodbye
```

***

# 13. HTTP status codes

Let's deliberately create a `404`.

Request:

```powershell
curl.exe http://localhost:3000/does-not-exist
```

Express returns:

```text
404 Not Found
```

Important status-code families:

| Code  | Meaning               |
| ----- | --------------------- |
| `200` | OK                    |
| `201` | Created               |
| `204` | No Content            |
| `301` | Moved Permanently     |
| `400` | Bad Request           |
| `401` | Unauthorized          |
| `403` | Forbidden             |
| `404` | Not Found             |
| `500` | Internal Server Error |

The first digit is particularly useful:

```text
2xx → success
3xx → redirection
4xx → client error
5xx → server error
```

***

# 14. Create a JSON endpoint

Now things become more interesting.

Add:

```javascript
app.get("/api/person", (req, res) => {
    res.json({
        id: 1,
        name: "Karl",
        language: "JavaScript"
    });
});
```

Call it:

```powershell
curl.exe http://localhost:3000/api/person
```

You should receive:

```json
{
  "id": 1,
  "name": "Karl",
  "language": "JavaScript"
}
```

Express automatically generates an appropriate JSON response.

***

# 15. PowerShell as a JSON client

Instead of `curl.exe`, use:

```powershell
Invoke-RestMethod http://localhost:3000/api/person
```

PowerShell understands JSON and converts the response into a PowerShell object.

You can then do:

```powershell
$response = Invoke-RestMethod http://localhost:3000/api/person
```

and:

```powershell
$response.name
```

Result:

```text
Karl
```

This is a very useful technique for testing REST APIs.

***

# 16. Query parameters

Let's create:

```text
GET /hello?name=Karl
```

Add:

```javascript
app.get("/hello", (req, res) => {
    const name = req.query.name || "World";

    res.send(`Hello, ${name}!`);
});
```

Now:

```powershell
curl.exe "http://localhost:3000/hello?name=Karl"
```

Result:

```text
Hello, Karl!
```

The URL:

```text
http://localhost:3000/hello?name=Karl
                              │
                              └── query parameter
```

Express makes it available through:

```javascript
req.query.name
```

***

# 17. Path parameters

Now create:

```javascript
app.get("/users/:id", (req, res) => {
    res.json({
        id: req.params.id
    });
});
```

Request:

```powershell
curl.exe http://localhost:3000/users/42
```

Response:

```json
{
  "id": "42"
}
```

The important distinction:

```text
/users/42
   │
   └── path parameter


/users?id=42
      │
      └── query parameter
```

***

# 18. POST requests

So far we've used:

```text
GET
```

Now let's use:

```text
POST
```

A POST request usually sends data to the server.

First enable JSON parsing:

```javascript
app.use(express.json());
```

Then:

```javascript
app.post("/api/person", (req, res) => {
    console.log(req.body);

    res.status(201).json({
        message: "Person created",
        person: req.body
    });
});
```

Our complete server now looks like:

```javascript
const express = require("express");

const app = express();

const PORT = 3000;

app.use(express.json());

app.get("/hello", (req, res) => {
    const name = req.query.name || "World";

    res.send(`Hello, ${name}!`);
});

app.get("/api/person", (req, res) => {
    res.json({
        id: 1,
        name: "Karl",
        language: "JavaScript"
    });
});

app.get("/users/:id", (req, res) => {
    res.json({
        id: req.params.id
    });
});

app.post("/api/person", (req, res) => {
    console.log(req.body);

    res.status(201).json({
        message: "Person created",
        person: req.body
    });
});

app.listen(PORT, () => {
    console.log(`HTTP server listening on port ${PORT}`);
});
```

***

# 19. Send JSON from PowerShell

Use:

```powershell
$body = @{
    name = "Alice"
    language = "Java"
} | ConvertTo-Json
```

Then:

```powershell
Invoke-RestMethod `
    -Uri http://localhost:3000/api/person `
    -Method Post `
    -ContentType "application/json" `
    -Body $body
```

The server receives:

```json
{
    "name": "Alice",
    "language": "Java"
}
```

and responds:

```json
{
    "message": "Person created",
    "person": {
        "name": "Alice",
        "language": "Java"
    }
}
```

***

# 20. Now comes the really interesting part: Wireshark

Everything we've done so far can be observed at the network level.

Start Wireshark.

You'll see network interfaces such as:

```text
Ethernet
Wi-Fi
...
```

For localhost traffic, depending on your Windows/Wireshark setup, the relevant interface is typically **Npcap Loopback Adapter**.

Start capturing on the loopback interface.

Then execute:

```powershell
curl.exe http://localhost:3000/hello
```

Wireshark should begin showing packets.

***

# 21. Your first Wireshark filter

Try:

```text
tcp.port == 3000
```

This means:

> Show TCP traffic involving port 3000.

You should see communication between:

```text
client
   │
   │ TCP
   ▼
localhost:3000
```

***

# 22. The most important conceptual discovery

You might expect Wireshark to show:

```text
HTTP
GET /hello
```

But remember:

**HTTP is not the same thing as TCP.**

The stack is approximately:

```text
┌──────────────────────┐
│ HTTP                 │
├──────────────────────┤
│ TCP                  │
├──────────────────────┤
│ IP                   │
├──────────────────────┤
│ Ethernet / Loopback   │
└──────────────────────┘
```

HTTP is an **application-layer protocol**.

TCP is a **transport-layer protocol**.

***

# 23. Follow the TCP conversation

In Wireshark, select one of the packets.

Right-click:

```text
Follow
   ↓
TCP Stream
```

This is one of the most useful Wireshark features for learning HTTP.

You should be able to see the HTTP conversation.

Conceptually:

```text
CLIENT → SERVER

GET /hello HTTP/1.1
Host: localhost:3000
...
```

and:

```text
SERVER → CLIENT

HTTP/1.1 200 OK
Content-Type: ...
...

Hello, World!
```

Now you can **see the HTTP protocol rather than just reading about it**.

***

# 24. The TCP connection

Before HTTP data can be exchanged, TCP establishes a connection.

You will see the famous:

```text
SYN
   ↓
SYN + ACK
   ↓
ACK
```

This is the TCP three-way handshake.

Conceptually:

```text
CLIENT                         SERVER

   │
   │ SYN
   ├──────────────────────────>
   │
   │ SYN + ACK
   │<──────────────────────────
   │
   │ ACK
   ├──────────────────────────>
   │
   │
   │     TCP connection
   │     established
   │
   │ HTTP GET
   ├──────────────────────────>
   │
   │ HTTP response
   │<──────────────────────────
```

This distinction is extremely important:

```text
TCP connection
       ↓
HTTP request
       ↓
HTTP response
```

***

# 25. HTTP vs TCP

This is one of the most important concepts in the entire tutorial.

### TCP answers:

> How do two machines exchange a reliable stream of bytes?

### HTTP answers:

> What do those bytes mean at the application level?

For example:

```text
TCP:
"Here is a stream of bytes."

HTTP:
"Those bytes represent a GET request for /hello."
```

***

# 26. Ports

Our server listens on:

```text
3000
```

So:

```text
localhost:3000
```

means:

```text
host = localhost
port = 3000
```

You can think of a port as a numbered entrance to a machine.

```text
localhost
│
├── :22       SSH
├── :80       HTTP
├── :443      HTTPS
├── :3000     our Express server
└── :8080     another possible application
```

This is also directly relevant to your Spring Boot work.

For example:

```text
Spring Boot → 8080
Express     → 3000
```

***

# 27. A very useful experiment

Run your Express application:

```text
localhost:3000
```

Then start another server on port `3001`.

For example:

```javascript
app.listen(3001);
```

Now:

```text
localhost:3000
```

and:

```text
localhost:3001
```

are two different TCP endpoints.

Wireshark can distinguish them:

```text
tcp.port == 3000
```

versus:

```text
tcp.port == 3001
```

***

# 28. Experiment with headers

Add an endpoint:

```javascript
app.get("/headers", (req, res) => {
    console.log(req.headers);

    res.json(req.headers);
});
```

Call:

```powershell
curl.exe http://localhost:3000/headers
```

You'll see headers such as:

```json
{
    "host": "localhost:3000",
    "user-agent": "...",
    "accept": "*/*"
}
```

Now capture the request in Wireshark.

You can connect the two worlds:

```text
PowerShell
    │
    │ User-Agent
    │ Accept
    │ Host
    ▼
   HTTP
    │
    ▼
Wireshark
    │
    ▼
Express
    │
    ▼
req.headers
```

***

# 29. Content-Type

One particularly important header is:

```http
Content-Type
```

For JSON:

```http
Content-Type: application/json
```

This tells the server:

> The body contains JSON.

For example:

```http
POST /api/person HTTP/1.1
Host: localhost:3000
Content-Type: application/json

{
    "name": "Alice"
}
```

Express parses that because we configured:

```javascript
app.use(express.json());
```

***

# 30. HTTP body

An HTTP request can contain a body.

For example:

```http
POST /api/person HTTP/1.1
Host: localhost:3000
Content-Type: application/json
Content-Length: 36

{
    "name": "Alice",
    "language": "Java"
}
```

Notice the separation:

```text
HTTP headers
     │
     │
     ▼

Content-Type: application/json
Content-Length: ...

     │
     │
     ▼
   empty line
     │
     ▼

HTTP body
```

The empty line is important.

It separates:

```text
headers
```

from:

```text
body
```

***

# 31. A complete HTTP learning experiment

I recommend doing this exercise several times.

## Experiment A — GET

PowerShell:

```powershell
curl.exe http://localhost:3000/hello
```

Wireshark:

```text
tcp.port == 3000
```

Look for:

```http
GET /hello HTTP/1.1
```

***

## Experiment B — Query parameter

```powershell
curl.exe "http://localhost:3000/hello?name=Karl"
```

Find:

```http
GET /hello?name=Karl HTTP/1.1
```

***

## Experiment C — JSON GET

```powershell
curl.exe http://localhost:3000/api/person
```

Look at:

```http
Content-Type: application/json
```

***

## Experiment D — POST

PowerShell:

```powershell
$body = '{"name":"Alice","language":"Java"}'

curl.exe `
    -X POST `
    http://localhost:3000/api/person `
    -H "Content-Type: application/json" `
    -d $body
```

Wireshark:

Look for:

```http
POST /api/person HTTP/1.1
```

Then inspect the body.

***

# 32. HTTP methods

Extend your Express server with:

```javascript
app.put("/api/person/:id", (req, res) => {
    res.json({
        message: "Person updated",
        id: req.params.id,
        person: req.body
    });
});

app.delete("/api/person/:id", (req, res) => {
    res.status(204).send();
});
```

Now you have:

```text
GET     /api/person
POST    /api/person
PUT     /api/person/:id
DELETE  /api/person/:id
```

This is the basic CRUD pattern:

```text
Create  → POST
Read    → GET
Update  → PUT
Delete  → DELETE
```

***

# 33. Compare this with Spring Boot

Because you're learning Spring Boot, this is particularly useful.

### Express

```javascript
app.get("/api/person/:id", (req, res) => {
    ...
});
```

### Spring Boot

```java
@GetMapping("/api/person/{id}")
public Person getPerson(@PathVariable Long id) {
    ...
}
```

And:

```text
Express                 Spring Boot

app.get()               @GetMapping
app.post()              @PostMapping
app.put()               @PutMapping
app.delete()            @DeleteMapping

req                     request
res                     response
req.params              @PathVariable
req.query               @RequestParam
req.body                @RequestBody
res.json()              return object
res.status(201)         ResponseEntity.status(201)
```

Seeing the same HTTP concepts implemented in two different frameworks is an excellent way to learn.

***

# 34. Where Apache Camel fits

This also connects directly to your recent Apache Camel work.

Imagine:

```text
HTTP Client
    │
    │ HTTP
    ▼
Express
    │
    │ application logic
    ▼
something else
```

With Camel you might instead have:

```text
HTTP Client
    │
    ▼
HTTP Endpoint
    │
    ▼
Camel Route
    │
    ▼
JMS
```

For example conceptually:

```text
from("http://...")
    .to("jms:queue:orders");
```

The HTTP part is still fundamentally:

```text
HTTP request
      ↓
HTTP endpoint
      ↓
HTTP response
```

Camel simply gives you an integration/routing layer around it.

***

# 35. The complete picture

At this point you should be able to see all these layers simultaneously:

```text
                     APPLICATION
┌────────────────────────────────────────────┐
│ PowerShell / curl                          │
│                                            │
│ GET /api/person HTTP/1.1                   │
└─────────────────────┬──────────────────────┘
                      │
                      │ HTTP
                      ▼
┌────────────────────────────────────────────┐
│ Express.js                                 │
│                                            │
│ app.get("/api/person", ...)                │
└─────────────────────┬──────────────────────┘
                      │
                      │
                 Node.js
                      │
                      ▼
┌────────────────────────────────────────────┐
│ TCP                                        │
│                                            │
│ port 3000                                  │
└─────────────────────┬──────────────────────┘
                      │
                      ▼
┌────────────────────────────────────────────┐
│ IP / Loopback                              │
│                                            │
│ 127.0.0.1                                  │
└─────────────────────┬──────────────────────┘
                      │
                      ▼
                  Wireshark
```

Wireshark lets you inspect the lower layers while Node/Express and PowerShell operate at the application layer.

***

# 36. Suggested 7-day HTTP Bootcamp

I would recommend doing this as a **7-day hands-on bootcamp** rather than trying to learn everything at once.

### Day 1 — HTTP fundamentals

Learn:

```text
Client
Server
Request
Response
URL
Method
Header
Body
Status code
```

Build:

```text
GET /hello
```

***

### Day 2 — Node.js + Express

Learn:

```text
Node.js
npm
Express
Routes
Middleware
req
res
```

Build:

```text
GET /hello
GET /goodbye
GET /api/person
```

***

### Day 3 — REST

Learn:

```text
GET
POST
PUT
DELETE
```

Build a small:

```text
Person REST API
```

***

### Day 4 — PowerShell HTTP client

Master:

```powershell
Invoke-WebRequest
Invoke-RestMethod
curl.exe
```

Practice:

```text
GET
POST
PUT
DELETE
headers
JSON
query parameters
```

***

### Day 5 — Wireshark

Learn to identify:

```text
Ethernet / Loopback
IP
TCP
TCP handshake
TCP port
HTTP
```

Practice:

```text
tcp.port == 3000
```

and:

```text
Follow → TCP Stream
```

***

### Day 6 — HTTP deep dive

Investigate:

```text
Content-Type
Content-Length
Accept
User-Agent
Host

200
201
204
400
401
403
404
500
```

Use Wireshark to **see every one of them**.

***

### Day 7 — Final project

Build:

```text
PowerShell
     │
     │ HTTP
     ▼
Node.js
     │
     ▼
Express REST API
     │
     ▼
In-memory data
```

with:

```text
GET    /api/persons
GET    /api/persons/:id
POST   /api/persons
PUT    /api/persons/:id
DELETE /api/persons/:id
```

Then test **every operation with PowerShell** while simultaneously observing the traffic with **Wireshark**.

That final exercise will give you a very solid understanding of HTTP because you'll see the same request at three levels:

```text
PowerShell
   │
   │ "I am sending POST /api/persons"
   ▼
Express
   │
   │ "I received req.body"
   ▼
Wireshark
   │
   │ "Here are the actual bytes/packets"
   ▼
TCP/IP
```

**That is the approach I'd recommend for you:** don't learn HTTP merely as a list of REST concepts. Use **PowerShell → Express → Wireshark** so you can connect the API-level concepts you're already learning in Spring Boot/Camel with what is actually happening on the network.

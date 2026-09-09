---
id: 20260907151341
title: REST as a standardized interface for web communication
author: Karl Schmitt
date: 2026-09-07
keywords: [ REST, API]
---

# The Architectural Style for Distributed Web Services

To understand **REST**, it helps to think of it as a set of "design rules" for how computers talk to each other over the internet.

### 1. What is REST?

**REST** stands for **Representational State Transfer**. 

It is **not** a programming language or a piece of software. 
It is an **architectural style**. It defines a set of constraints that, if followed, make a web service fast, scalable, and easy to use.

If HTTP is the "language" (the grammar and vocabulary), REST is the "etiquette" or the "standard way" of using that language to build a system.

---

### 2. What is a REST API?

A **REST API** (or RESTful API) is a web service that follows the REST rules. It allows one software application (the Client) to ask another application (the Server) for data or to perform an action.

#### The Core Concept: "Resources"

In REST, everything is a **Resource**. A resource is any object or data the API can provide. 
*   Instead of thinking about "running a function," you think about "accessing a thing."
*   Every resource has a unique address called a **URL** (Uniform Resource Locator).

**Example (A Bookstore API):**
*   `https://api.books.com/books` (The collection of all books)
*   `https://api.books.com/books/123` (A specific book with ID 123)
*   `https://api.books.com/authors/mark-twain` (A specific author)

---

### 3. The 4 Key Rules of REST

To be truly "RESTful," an API must follow these principles:

#### A. Use of HTTP Methods (The Verbs)
REST maps actions to the standard HTTP methods we discussed earlier:
*   **GET** `/books` → Fetch the list of books.
*   **POST** `/books` → Add a new book to the library.
*   **PUT** `/books/123` → Update the details of book 123.
*   **DELETE** `/books/123` → Remove book 123.

#### B. Statelessness

The server does not "remember" previous requests. Every single request from the client must contain all the information necessary to understand and process it (e.g., the API key or the user ID).

#### C. Uniform Interface

No matter what resource you are accessing, the way you interact with the API stays consistent. You always use URLs and standard HTTP status codes (like 200 OK or 404 Not Found).

#### D. JSON Data Format

While REST can technically use XML or Text, almost all modern REST APIs use **JSON** (JavaScript Object Notation) to send and receive data because it is lightweight and easy for humans to read.

---

### 4. How it looks in practice

Imagine you are building a Weather App.
1.  **Request:** Your app sends a **GET** request to `https://api.weather.com/v1/london`.
2.  **Processing:** The server sees the request, identifies the resource (`london`), and fetches the data.
3.  **Response:** The server sends back a **200 OK** status and a **JSON body**:
    ```json
    {
      "city": "London",
      "temperature": "15C",
      "condition": "Cloudy"
    }
    ```
---

### Comparison: HTTP vs. REST

*   **HTTP** is the **Protocol** (The transport truck carrying the goods).
*   **REST** is the **Architecture** (The warehouse layout and the standardized shipping labels).

---

**Recommended Atomic Statement:** 
> "REST is an architectural style that uses HTTP methods to manage resources via unique URLs in a stateless manner."
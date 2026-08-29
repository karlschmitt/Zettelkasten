---
id: 20260829201827
title: Spring Boot Apache Camel File-Endpoint Example
author: Karl Schmitt
date: 2026-08-29
---

# Spring Boot Apache Camel File-Endpoint Example

The **Apache Camel File component** is one of the most frequently used components. It allows you to read files from a directory (Consumer) or write files to a directory (Producer).

In a Spring Boot environment, you define these rules inside a `RouteBuilder` class.

### 1. Prerequisites (Maven Dependencies)

To use Camel with Spring Boot and the File component, add these to your `pom.xml`:

```xml
<dependencies>
    <!-- Camel Spring Boot Starter -->
    <dependency>
        <groupId>org.apache.camel.springboot</groupId>
        <artifactId>camel-spring-boot-starter</artifactId>
        <version>4.x.x</version> <!-- Use the latest version -->
    </dependency>

    <!-- Camel File Component -->
    <dependency>
        <groupId>org.apache.camel</groupId>
        <artifactId>camel-file</artifactId>
        <version>4.x.x</version>
    </dependency>
</dependencies>
```

---

### 2. The Code Example

This example creates a route that **polls** an `input` folder, logs the content, and **moves** the file to an `output` folder.

```java
import org.apache.camel.builder.RouteBuilder;
import org.springframework.stereotype.Component;

@Component
public class FileRoute extends RouteBuilder {

    @Override
    public void configure() throws Exception {
        
        // 1. Consumer: Read files from 'data/input'
        // noop=true means 'No Operation' (don't delete or move the source file)
        // delay=5000 means poll every 5 seconds
        from("file:data/input?noop=true&delay=5000")
            .routeId("fileCopyRoute")
            .log("Reading file: ${header.CamelFileName}")
            
            // 2. Processing (Optional)
            // You can transform the content here
            .setBody(simple("${body} - Processed by Camel"))
            
            // 3. Producer: Write file to 'data/output'
            .to("file:data/output")
            .log("File moved to output directory.");
    }
}
```

---

### 3. Understanding the URI Options

The File component uses a URI format: `file:directoryName?options`.

#### **Common Consumer Options (Reading)**

*   **`noop=true`**: Camel will not modify the source file. It is used for testing.
*   **`delete=true`**: Once the file is processed successfully, it is deleted from the source.
*   **`move=done`**: Instead of deleting, move the file to a subfolder named `done`.
*   **`preMove=work`**: Move the file to a `work` folder while it is being processed (prevents other processes from grabbing it).
*   **`include=.*.csv`**: Only pick up files ending in `.csv` (uses Regex).
*   **`delay=1000`**: How often to poll the folder (in milliseconds).

#### **Common Producer Options (Writing)**

*   **`fileName=report.txt`**: Overrides the name of the file being written.
*   **`fileExist=Append`**: If the file already exists, append the data instead of overwriting (`Override`, `Fail`, `Ignore` are other options).

---

### 4. Important Concepts

#### **The Exchange**

When Camel reads a file, it creates an **Exchange** object. 
*   **Message Body:** The content of the file (usually as a `GenericFile` or `InputStream`).
*   **Headers:** Camel automatically adds metadata to headers, such as:
    *   `${header.CamelFileName}`: The name of the file.
    *   `${header.CamelFileAbsolutePath}`: The full path.
    *   `${header.CamelFileLastModified}`: The timestamp.

#### **Idempotency**

By default, Camel is smart. If you are reading files and **not** deleting them (`noop=true`), Camel uses an **Idempotent Repository** (in-memory by default) to keep track of which files it has already processed so it doesn't read the same file over and over in an infinite loop.

---

### 5. Running the Example

1.  Start your Spring Boot application.
2.  Create a folder structure in your project root: `data/input`.
3.  Drop a text file (e.g., `test.txt`) into `data/input`.
4.  Check your console; you will see the logs.
5.  Check the `data/output` folder; the file will appear there.

### When to use the File Component?

*   **Batch Processing:** Picking up CSV/XML files for database import.
*   **Integration:** Communicating with legacy systems that only export data via folders.
*   **Log Processing:** Monitoring logs and sending alerts if specific patterns are found.
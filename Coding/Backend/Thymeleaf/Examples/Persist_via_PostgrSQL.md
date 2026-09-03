---
id: 20260903145652
---


To persist data with **PostgreSQL** in a modern Spring Boot environment, you need to transition from a static list to a Database-driven approach using **Spring Data JPA**.

*Note: As of early 2024, Spring Boot 3.x is the current standard and Java 21 is the current LTS. Spring Boot 4.x and Java 25 are future releases, but the following steps use the modern Jakarta Persistence (JPA) standards that will be applicable then.*

### 1. Add Dependencies
In your `pom.xml`, add the Spring Data JPA starter and the PostgreSQL driver:

```xml
<dependencies>
    <!-- JPA for Database Interaction -->
    <dependency>
        <groupId>org.springframework.boot</groupId>
        <artifactId>spring-boot-starter-data-jpa</artifactId>
    </dependency>

    <!-- PostgreSQL Driver -->
    <dependency>
        <groupId>org.postgresql</groupId>
        <artifactId>postgresql</artifactId>
        <scope>runtime</scope>
    </dependency>
</dependencies>
```

---

### 2. Configure the Database
In `src/main/resources/application.properties`, tell Spring how to connect to your PostgreSQL instance:

```properties
spring.datasource.url=jdbc:postgresql://localhost:5432/university_db
spring.datasource.username=postgres
spring.datasource.password=yourpassword

# Hibernate settings
spring.jpa.hibernate.ddl-auto=update
spring.jpa.show-sql=true
spring.jpa.properties.hibernate.dialect=org.hibernate.dialect.PostgreSQLDialect
```

---

### 3. Update the Model (The Entity)
JPA requires your class to be annotated with `@Entity`. Note that while Java 25 supports advanced **Records**, JPA Entities still work best as standard classes because Hibernate needs to proxy them.

```java
import jakarta.persistence.*;

@Entity
@Table(name = "students")
public class Student {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false)
    private String name;

    @Column(unique = true, nullable = false)
    private String email;

    private boolean enrolled;

    // Default constructor (Required by JPA)
    public Student() {}

    // Constructor, Getters, and Setters
    public Student(String name, String email, boolean enrolled) {
        this.name = name;
        this.email = email;
        this.enrolled = enrolled;
    }

    // ... Getters and Setters ...
}
```

---

### 4. Create the Repository
This is the "magic" of Spring Data JPA. By extending `JpaRepository`, Spring automatically creates all the SQL for Saving, Deleting, and Finding students.

```java
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface StudentRepository extends JpaRepository<Student, Long> {
    // You can add custom queries here later
}
```

---

### 5. Update the Controller
Now, inject the repository into your controller to fetch data from the database.

```java
@Controller
public class StudentController {

    private final StudentRepository studentRepository;

    // Constructor Injection
    public StudentController(StudentRepository studentRepository) {
        this.studentRepository = studentRepository;
    }

    @GetMapping("/students")
    public String listStudents(Model model) {
        // Fetch all students from PostgreSQL
        List<Student> studentList = studentRepository.findAll();
        
        model.addAttribute("allStudents", studentList);
        return "students";
    }

    // Example: Simple method to add a student
    @PostMapping("/students/add")
    public String addStudent(@ModelAttribute Student student) {
        studentRepository.save(student);
        return "redirect:/students";
    }
}
```

---

### 6. Modernizing with Java 25 Features
If you are using **Java 25**, you can take advantage of cleaner syntax.

**String Templates (Preview feature in early versions, likely standard in 25):**
Instead of messy concatenation for logging or dynamic queries, you can use modern string handling.

**Scoped Values or Virtual Threads:**
If your application handles thousands of concurrent database requests, ensure your Spring Boot 4 application is configured to use **Virtual Threads** (Project Loom), which became standard in Java 21 and will be highly optimized by Java 25.

In `application.properties`:
```properties
spring.threads.virtual.enabled=true
```

### 7. How to test it
1.  **Create the Database:** Ensure you have a database named `university_db` in PostgreSQL.
2.  **Run the App:** Spring Boot will see `spring.jpa.hibernate.ddl-auto=update` and automatically create the `students` table for you.
3.  **Add Data:** Use a tool like **PostgreSQL pgAdmin** or a SQL script to insert a few rows:
    ```sql
    INSERT INTO students (name, email, enrolled) VALUES ('Alice', 'alice@test.com', true);
    ```
4.  **Refresh:** Visit `http://localhost:8080/students` and you will see the data pulled directly from PostgreSQL.

### Summary of Workflow
1.  **Dependency:** `spring-boot-starter-data-jpa` + `postgresql`.
2.  **Entity:** `@Entity` and `@Id`.
3.  **Repository:** `interface StudentRepository extends JpaRepository`.
4.  **Service/Controller:** Use `repository.findAll()` or `repository.save()`.
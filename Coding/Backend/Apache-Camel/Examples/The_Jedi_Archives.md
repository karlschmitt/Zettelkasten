---
id: 20260904123120
title: The Jedi Archives
author: Karl Schmitt
date: 2026-09-04
---

# The Jedi Archives

To set up your database quickly for the Coding Dojo, the best approach is to use **Docker Compose**. This ensures every participant has the exact same environment with one command.

### 1. Create a Folder for the Dojo

Create a directory (e.g., `camel-dojo-db`) and create two files inside it.

### 2. Create the Initialization Script (`init.sql`)

The official Postgres Docker image automatically executes any `.sql` files found in the `/docker-entrypoint-initdb.d/` folder upon startup.

Create a file named **`init.sql`**:
```sql
-- This script runs automatically on startup
CREATE TABLE IF NOT EXISTS star_wars_characters (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255),
    height VARCHAR(50),
    mass VARCHAR(50),
    processed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### 3. Create the Docker Compose File (`docker-compose.yml`)

Create a file named **`docker-compose.yml`**:
```yaml
services:
  postgres-db:
    image: postgres:15-alpine
    container_name: dojo-postgres
    environment:
      - POSTGRES_USER=postgres
      - POSTGRES_PASSWORD=yourpassword
      - POSTGRES_DB=dojo_db
    ports:
      - "5432:5432"
    volumes:
      # Map our local init.sql into the container's auto-init folder
      - ./init.sql:/docker-entrypoint-initdb.d/init.sql
    restart: always
```

---

### 4. Run the Database

Open your terminal in that folder and run:
```bash
docker-compose up -d
```

### 5. Verify it's working
To check if the database and table were created correctly, run this command:
```bash
docker exec -it dojo-postgres psql -U postgres -d dojo_db -c "\dt"
```
*It should show the `star_wars_characters` table in the list.*

---

### Integration with Spring Boot

Now, update your `src/main/resources/application.properties` in your Spring Boot project to match these settings:
```properties
spring.datasource.url=jdbc:postgresql://localhost:5432/dojo_db
spring.datasource.username=postgres
spring.datasource.password=yourpassword
spring.datasource.driver-class-name=org.postgresql.Driver
```

### Why use this method for a Dojo?

1. **Automation**: No manual SQL execution is required.
2. **Consistency**: Everyone has the same `POSTGRES_DB` name and credentials.
3. **Clean Slate**: If someone messes up their data, they can just run `docker-compose down -v` and `docker-compose up -d` to get a brand new, empty database in seconds.
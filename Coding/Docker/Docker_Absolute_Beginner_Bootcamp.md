---
id: 20260823165251
title: Docker Absolute Beginner Bootcamp
author: Karl Schmitt
date: 2026-08-23
keywords: [ Docker, Bootcamp]
---

![](./Images/)

> {NOTE!}
> Dieser Text präsentiert einen strukturierten **Vier-Wochen-Lehrplan**, der speziell darauf ausgelegt ist, Anfänger methodisch in die Welt von **Docker** einzuführen. Der Kurs beginnt mit den **fundamentalen Konzepten** von Images und Containern und steigert sich schrittweise bis hin zur **Containerisierung von Java-Anwendungen** mit Spring Boot. Ein besonderer Schwerpunkt liegt auf der **praktischen Anwendung**, wobei die Lernenden durch tägliche Übungen wichtige Befehle und das Management von **Netzwerken sowie Datenvolumen** verinnerlichen. Fortgeschrittene Themen wie **Docker Compose** und die Orchestrierung von Multi-Container-Anwendungen bilden den Abschluss des Programms. Ziel ist es, ein tiefes **mentales Modell** der Technologie aufzubauen, um komplexe Entwicklungsumgebungen eigenständig zu verwalten. Das Training endet mit einem **finalen Projekt**, welches die theoretischen Kenntnisse in einer realistischen Software-Architektur zusammenführt.


Absolutely. Since you're already working with **Java and Spring Boot**, I'll make this bootcamp start at absolute zero and gradually lead toward **Dockerizing Spring Boot applications**.

# 🐳 Docker Absolute Beginner Bootcamp

**Duration:** 4 weeks\
**Level:** Absolute beginner → solid practical Docker knowledge\
**Environment:** Windows 11 + PowerShell + Docker Desktop\
**Approach:** Learn → type commands → observe → experiment → build something

The most important rule:

> **Don't just read the commands. Type them yourself and observe what Docker does.**

***

# 🎯 Bootcamp Goal

At the end, you should be able to look at this:

```text
┌───────────────────────────────────────────┐
│                  Docker                   │
│                                           │
│  ┌─────────────────┐   ┌───────────────┐  │
│  │ Spring Boot     │   │ PostgreSQL    │  │
│  │ Container       │──▶│ Container     │  │
│  │                 │   │               │  │
│  │ Java            │   │ Database      │  │
│  │ Spring Boot     │   │               │  │
│  └─────────────────┘   └───────────────┘  │
│                                           │
└───────────────────────────────────────────┘
              ▲
              │
        localhost:8080
              │
           Browser
```

and understand **every important part of it**.

***

# 🗺️ The 4-Week Roadmap

| Week       | Topic                       | Main Goal                                |
| ---------- | --------------------------- | ---------------------------------------- |
| **Week 1** | Docker Fundamentals         | Understand images and containers         |
| **Week 2** | Dockerfiles                 | Build your own images                    |
| **Week 3** | Volumes, Networks & Compose | Build multi-container applications       |
| **Week 4** | Java & Spring Boot          | Dockerize a real Spring Boot application |

***

# 🟢 WEEK 1 — Docker Fundamentals

## Goal

Understand:

```text
Docker
Docker Engine
Image
Container
Docker Hub
docker run
docker ps
docker stop
docker rm
ports
logs
exec
```

Don't worry about Dockerfiles yet.

***

# Day 1 — What Is Docker?

### Learn

Understand the basic problem Docker solves.

Without Docker:

```text
Application
   │
   ├── Java
   ├── PostgreSQL
   ├── Redis
   ├── configuration
   └── libraries
```

Different computers may have different versions.

Docker gives us a reproducible environment:

```text
Docker
   │
   └── Container
        │
        ├── Application
        ├── Libraries
        └── Configuration
```

### Learn these terms

**Image**

> A packaged blueprint used to create containers.

**Container**

> A running instance of an image.

A useful analogy:

```text
Java class     → Java object
Docker image   → Docker container
```

***

# Day 1 Hands-On

Check Docker:

```powershell
docker --version
```

Then:

```powershell
docker info
```

Then:

```powershell
docker run hello-world
```

Now inspect:

```powershell
docker images
```

and:

```powershell
docker ps
```

and:

```powershell
docker ps -a
```

### Important observation

`docker ps` might show nothing.

Why?

Because `hello-world` finished.

But:

```powershell
docker ps -a
```

shows the stopped container.

This gives you your first important distinction:

```text
docker ps
     ↓
RUNNING containers

docker ps -a
     ↓
ALL containers
```

***

# Day 2 — Your First Real Container

We'll use nginx.

Run:

```powershell
docker run nginx
```

Notice that your terminal is occupied.

Stop it:

```text
Ctrl + C
```

Now run:

```powershell
docker run -d nginx
```

The `-d` means:

> detached

Now:

```powershell
docker ps
```

You should see nginx running.

***

# Day 2 Exercise

Start nginx with a name:

```powershell
docker run -d --name my-nginx nginx
```

Check:

```powershell
docker ps
```

Stop it:

```powershell
docker stop my-nginx
```

Start it again:

```powershell
docker start my-nginx
```

Restart it:

```powershell
docker restart my-nginx
```

Finally:

```powershell
docker stop my-nginx
docker rm my-nginx
```

***

# Day 3 — Docker Images

Now concentrate on **images**.

Run:

```powershell
docker images
```

You'll see something similar to:

```text
REPOSITORY    TAG       IMAGE ID
nginx         latest    ...
```

Learn:

```text
Repository
Tag
Image ID
```

For example:

```text
nginx:latest
```

means:

```text
repository = nginx
tag        = latest
```

You can explicitly download an image:

```powershell
docker pull nginx
```

Then:

```powershell
docker images
```

***

# Day 3 Exercise

Try:

```powershell
docker pull redis
```

Then:

```powershell
docker images
```

You should now have at least:

```text
nginx
redis
```

Don't start Redis yet.

Just understand:

```text
docker pull
```

means:

> Download an image.

Where does the image normally come from?

A container registry such as Docker Hub.

***

# Day 4 — Container Lifecycle

Learn this model:

```text
             docker run
                 │
                 ▼
              Created
                 │
                 ▼
              Running
                 │
            docker stop
                 │
                 ▼
              Stopped
                 │
             docker rm
                 │
                 ▼
              Deleted
```

Experiment.

Create:

```powershell
docker run -d --name test-nginx nginx
```

Check:

```powershell
docker ps
```

Stop:

```powershell
docker stop test-nginx
```

Check:

```powershell
docker ps
```

Then:

```powershell
docker ps -a
```

Start:

```powershell
docker start test-nginx
```

Finally delete:

```powershell
docker stop test-nginx
docker rm test-nginx
```

***

# Day 5 — Ports

This is extremely important for web developers.

Start nginx:

```powershell
docker run -d --name my-nginx -p 8080:80 nginx
```

Understand:

```text
-p 8080:80
   │    │
   │    └── Container port
   │
   └─────── Host port
```

So:

```text
Windows
localhost:8080
       │
       ▼
Docker
       │
       ▼
Container
       │
       ▼
nginx:80
```

Open:

```text
http://localhost:8080
```

You should see the nginx welcome page.

🎉

***

# Day 5 Exercise

Try another port.

First:

```powershell
docker stop my-nginx
docker rm my-nginx
```

Then:

```powershell
docker run -d --name my-nginx -p 9000:80 nginx
```

Open:

```text
http://localhost:9000
```

You should get the same nginx page.

You've just learned:

> The host port does not have to equal the container port.

***

# Day 6 — Logs and Exec

Start:

```powershell
docker run -d --name my-nginx nginx
```

Look at logs:

```powershell
docker logs my-nginx
```

Follow logs:

```powershell
docker logs -f my-nginx
```

Press:

```text
Ctrl + C
```

The container continues running.

Now enter it:

```powershell
docker exec -it my-nginx bash
```

You are now inside the container.

Try:

```bash
ls
```

Then:

```bash
pwd
```

Then:

```bash
cat /etc/os-release
```

Then:

```bash
exit
```

***

# Day 7 — Week 1 Mini Project

Build this:

```text
Browser
   │
   ▼
localhost:8080
   │
   ▼
Docker
   │
   ▼
nginx container
   │
   ▼
HTML page
```

You should be able to:

```powershell
docker run
docker ps
docker logs
docker exec
docker stop
docker start
docker rm
```

without looking them up.

***

# 🟡 WEEK 2 — Dockerfiles & Building Images

Now things get much more interesting.

## Goal

Learn:

```text
Dockerfile
FROM
COPY
RUN
CMD
ENTRYPOINT
WORKDIR
EXPOSE
.dockerignore
docker build
image layers
```

***

# Day 8 — Your First Dockerfile

Create:

```text
docker-bootcamp/
└── hello/
    ├── Dockerfile
    └── index.html
```

`index.html`:

```html
<!DOCTYPE html>
<html>
<body>
    <h1>Hello Docker!</h1>
</body>
</html>
```

Dockerfile:

```dockerfile
FROM nginx

COPY index.html /usr/share/nginx/html/index.html
```

Build:

```powershell
docker build -t hello-docker .
```

Run:

```powershell
docker run -d --name hello-docker-container -p 8080:80 hello-docker
```

Open:

```text
http://localhost:8080
```

***

# Day 9 — Understand `FROM`

This:

```dockerfile
FROM nginx
```

means:

> Start building my image from the nginx image.

For Java we'll eventually have something like:

```dockerfile
FROM eclipse-temurin:21
```

or another suitable Java runtime image.

Conceptually:

```text
Base image
     │
     ▼
Your Dockerfile
     │
     ▼
Your image
```

***

# Day 10 — `COPY`

Learn:

```dockerfile
COPY source destination
```

For example:

```dockerfile
COPY index.html /usr/share/nginx/html/index.html
```

The file:

```text
index.html
```

from your build context gets copied into the image.

***

# Day 11 — `RUN`

`RUN` executes a command **during image construction**.

For example:

```dockerfile
FROM ubuntu

RUN apt-get update
RUN apt-get install -y curl
```

The distinction is important:

```text
RUN
 ↓
build time
```

whereas:

```text
CMD
 ↓
container runtime
```

***

# Day 12 — `CMD`

Example:

```dockerfile
FROM ubuntu

CMD ["echo", "Hello Docker"]
```

Build:

```powershell
docker build -t hello-cmd .
```

Run:

```powershell
docker run hello-cmd
```

The command runs when the container starts.

***

# Day 13 — Docker Image Layers

This is where Docker starts becoming more interesting.

A Dockerfile:

```dockerfile
FROM nginx
COPY index.html /usr/share/nginx/html/
```

produces layers.

Conceptually:

```text
┌──────────────────────────┐
│ Your HTML layer          │
├──────────────────────────┤
│ nginx layer              │
├──────────────────────────┤
│ Base image layers        │
└──────────────────────────┘
```

This contributes to Docker's efficient image reuse and caching.

***

# Day 14 — Week 2 Mini Project

Build your own website image.

Requirements:

```text
☐ Dockerfile
☐ HTML
☐ docker build
☐ docker run
☐ Port mapping
☐ Custom container name
```

The final result:

```text
Browser
   │
   ▼
localhost:8080
   │
   ▼
Your Docker container
   │
   ▼
Your HTML
```

***

# 🔵 WEEK 3 — Volumes, Networks & Docker Compose

Now we'll move from:

```text
one container
```

to:

```text
multiple containers
```

This is where Docker becomes extremely useful for backend development.

***

# Day 15 — Container Filesystems

Start a container:

```powershell
docker run -it ubuntu bash
```

Inside:

```bash
echo "Hello" > test.txt
```

Check:

```bash
cat test.txt
```

Exit:

```bash
exit
```

Now remove the container.

Create another container.

The file is gone.

Why?

Because container storage is tied to the container.

***

# Day 16 — Volumes

Create a volume:

```powershell
docker volume create my-data
```

List volumes:

```powershell
docker volume ls
```

Inspect:

```powershell
docker volume inspect my-data
```

Now we can attach it to a container.

Conceptually:

```text
Container
    │
    ▼
Volume
    │
    ▼
Persistent data
```

This is essential for databases.

***

# Day 17 — Bind Mounts

A bind mount connects a directory on your Windows machine to a directory in the container.

Conceptually:

```text
Windows folder
      │
      ▼
Docker container
```

For example:

```powershell
docker run --rm -it `
  -v ${PWD}:/workspace `
  ubuntu bash
```

Now your current directory is available inside:

```text
/workspace
```

This is especially useful during development.

***

# Day 18 — Docker Networks

Create a network:

```powershell
docker network create my-network
```

List:

```powershell
docker network ls
```

Now imagine:

```text
my-network
    │
    ├── application
    │
    └── database
```

Containers on the same Docker network can communicate with each other.

***

# Day 19 — Container-to-Container Communication

Run Redis:

```powershell
docker run -d `
  --name redis `
  --network my-network `
  redis
```

Now another container can communicate with Redis through the Docker network.

The important idea:

```text
application
     │
     │ redis:6379
     ▼
redis container
```

Notice that we're using:

```text
redis
```

as a hostname.

This becomes very important with Spring Boot + PostgreSQL.

***

# Day 20 — Docker Compose

Now introduce:

```text
compose.yaml
```

For example:

```yaml
services:

  redis:
    image: redis

  nginx:
    image: nginx
    ports:
      - "8080:80"
```

Start:

```powershell
docker compose up
```

Stop:

```powershell
docker compose down
```

You have just described a multi-container environment declaratively.

***

# Day 21 — Week 3 Project

Build:

```text
Docker Compose
│
├── nginx
│
└── redis
```

Your goal is to understand:

```text
compose.yaml
      │
      ▼
docker compose up
      │
      ├── nginx container
      │
      └── redis container
```

And:

```powershell
docker compose down
```

removes the running containers and network created for the Compose application.

***

# 🔴 WEEK 4 — Docker + Java + Spring Boot

Now we connect everything to your existing Java/Spring Boot knowledge.

This is the most important week for you.

***

# Day 22 — Dockerize a Java Application

Start with a tiny Java application:

```java
public class HelloDocker {

    public static void main(String[] args) {
        System.out.println("Hello from Docker!");
    }
}
```

Compile it.

Then create a Docker image containing the application.

You'll learn the relationship:

```text
Java source
    │
    ▼
Maven
    │
    ▼
JAR
    │
    ▼
Dockerfile
    │
    ▼
Docker image
    │
    ▼
Container
    │
    ▼
Java application
```

***

# Day 23 — Dockerize Spring Boot

Now create a tiny Spring Boot application.

For example:

```java
@RestController
public class HelloController {

    @GetMapping("/hello")
    public String hello() {
        return "Hello from Spring Boot in Docker!";
    }
}
```

Your application normally runs on:

```text
localhost:8080
```

Then we'll put it inside a container.

Conceptually:

```text
Browser
   │
   ▼
localhost:8080
   │
   ▼
Docker
   │
   ▼
Spring Boot container
   │
   ▼
Spring Boot :8080
```

***

# Day 24 — Spring Boot Dockerfile

You'll learn a Dockerfile such as:

```dockerfile
FROM eclipse-temurin:21-jre

WORKDIR /app

COPY target/app.jar app.jar

ENTRYPOINT ["java", "-jar", "app.jar"]
```

Don't worry if this looks complicated right now.

We'll understand every line.

Especially:

```text
FROM
WORKDIR
COPY
ENTRYPOINT
```

***

# Day 25 — Spring Boot + PostgreSQL

Now we'll create:

```text
┌─────────────────────────────────────┐
│             Docker                  │
│                                     │
│ ┌────────────────┐                  │
│ │ Spring Boot    │                  │
│ │                │                  │
│ │ :8080          │                  │
│ └───────┬────────┘                  │
│         │                            │
│         │ JDBC                       │
│         ▼                            │
│ ┌────────────────┐                  │
│ │ PostgreSQL     │                  │
│ │                │                  │
│ │ :5432          │                  │
│ └────────────────┘                  │
│                                     │
└─────────────────────────────────────┘
```

We'll learn why Spring Boot should **not** connect to:

```text
localhost:5432
```

when PostgreSQL is in another container.

Instead, Docker Compose gives us a service name such as:

```text
postgres:5432
```

That's a very important Docker networking lesson.

***

# Day 26 — Spring Boot + PostgreSQL + Compose

Our `compose.yaml` will eventually look conceptually like:

```yaml
services:

  app:
    build: .
    ports:
      - "8080:8080"
    depends_on:
      - postgres

  postgres:
    image: postgres
    environment:
      POSTGRES_DB: demo
      POSTGRES_USER: demo
      POSTGRES_PASSWORD: secret
```

Then:

```powershell
docker compose up --build
```

And we get:

```text
             Docker Compose
                   │
        ┌──────────┴──────────┐
        │                     │
        ▼                     ▼
 Spring Boot              PostgreSQL
 container                container
        │                     │
        └──────────┬──────────┘
                   │
                 network
```

***

# Day 27 — Debugging Docker

This day is extremely important.

Learn to investigate problems rather than randomly changing things.

Your toolbox:

```powershell
docker ps
```

```powershell
docker ps -a
```

```powershell
docker logs CONTAINER
```

```powershell
docker inspect CONTAINER
```

```powershell
docker exec -it CONTAINER bash
```

```powershell
docker images
```

```powershell
docker network ls
```

```powershell
docker volume ls
```

And with Compose:

```powershell
docker compose ps
```

```powershell
docker compose logs
```

***

# Day 28 — Final Project 🚀

Build a complete application:

```text
                    Browser
                       │
                       │
                localhost:8080
                       │
                       ▼
              ┌────────────────┐
              │ Spring Boot    │
              │ Container      │
              └───────┬────────┘
                      │
                      │ JDBC
                      ▼
              ┌────────────────┐
              │ PostgreSQL     │
              │ Container      │
              └───────┬────────┘
                      │
                      ▼
                 Docker Volume
```

Everything is started with:

```powershell
docker compose up --build
```

And stopped with:

```powershell
docker compose down
```

***

# 🧠 The Mental Model You Should Have After 4 Weeks

By the end, I want you to be able to mentally follow this:

```text
Dockerfile
     │
     │ docker build
     ▼
┌───────────────┐
│ Docker Image  │
└───────┬───────┘
        │
        │ docker run
        ▼
┌────────────────┐
│   Container    │
│                │
│ Application    │
└───────┬────────┘
        │
        │ network
        ▼
┌────────────────┐
│ Other container│
│                │
│ PostgreSQL     │
└───────┬────────┘
        │
        │
        ▼
     Volume
```

And for Compose:

```text
compose.yaml
     │
     │ docker compose up
     ▼
┌──────────────────────────────┐
│          Docker              │
│                              │
│ ┌────────────┐ ┌───────────┐ │
│ │ Spring Boot│ │ PostgreSQL│ │
│ │ container  │ │ container │ │
│ └─────┬──────┘ └─────┬─────┘ │
│       │              │       │
│       └──────network─┘       │
│                              │
│          volume              │
└──────────────────────────────┘
```

***

# 📚 Your Docker Command Vocabulary

By the end of the bootcamp, these should be familiar:

### Docker basics

```powershell
docker --version
docker info
docker version
```

### Images

```powershell
docker images
docker pull
docker build
docker rmi
```

### Containers

```powershell
docker run
docker ps
docker ps -a
docker start
docker stop
docker restart
docker rm
```

### Debugging

```powershell
docker logs
docker exec
docker inspect
```

### Volumes

```powershell
docker volume ls
docker volume create
docker volume inspect
docker volume rm
```

### Networks

```powershell
docker network ls
docker network create
docker network inspect
docker network rm
```

### Compose

```powershell
docker compose up
docker compose down
docker compose ps
docker compose logs
docker compose build
```

***

# 🏆 Final Bootcamp Challenge

At the end, don't simply say:

> "I know Docker commands."

Instead, try to explain this diagram **without looking at your notes**:

```text
                         Docker
                           │
              ┌────────────┴────────────┐
              │                         │
              ▼                         ▼
       Spring Boot                  PostgreSQL
       Container                    Container
              │                         │
              └──────────┬──────────────┘
                         │
                    Docker Network
                         │
                         ▼
                    PostgreSQL
                      Volume
```

Then explain:

1. What is an **image**?

2. What is a **container**?

3. What does `docker run` do?

4. What does `docker build` do?

5. What is a **Dockerfile**?

6. What does `-p 8080:8080` mean?

7. Why do containers need networks?

8. Why does PostgreSQL need a volume?

9. What does Docker Compose solve?

10. Why would Spring Boot use `postgres:5432` instead of `localhost:5432`?

If you can answer those ten questions, you've moved well beyond the absolute-beginner stage.

***

## 🚀 How I recommend we do this together

Rather than giving you four weeks of theory all at once, we can turn this into a **hands-on bootcamp**, just like your Java and Kubernetes learning.

I'd start with **Day 1: Docker Fundamentals**, where we actually work through:

```text
docker run hello-world
        ↓
docker images
        ↓
docker ps
        ↓
docker ps -a
        ↓
docker run nginx
        ↓
docker run -d nginx
        ↓
docker stop
        ↓
docker rm
```

and, importantly, **I can explain what Docker is doing internally after every command**. That will give you the solid foundation needed before we move on to Dockerfiles.

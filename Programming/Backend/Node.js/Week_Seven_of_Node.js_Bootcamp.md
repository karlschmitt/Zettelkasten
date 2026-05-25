---
id: 20260419173649
title: Week Seven of Node.js Bootcamp
author: Karl Schmitt
date: 2026-04-19
keywords: [ Node.js, node, npm, JavaScript]
---

# Week Seven of Node.js Bootcamp

Awesome—now you’re entering **real-time systems**, which is a big step toward modern backend engineering ⚡

Week 7 is all about **WebSockets + live communication**. You’ll build a **real-time chat system**—no page reloads, instant updates.

***

# 🚀 Week 7: Real-Time Apps with WebSockets

## 🎯 Goal of Week 7

* Understand **WebSockets**

* Use **Socket.IO**

* Build a **real-time chat server**

* Handle live events (messages, users)

***

# 🧠 What Makes This Different?

### ❌ HTTP (what you used so far)

* Request → Response → Done

### ✅ WebSockets

* Persistent connection

* Server ↔ Client can talk anytime

👉 Think: chat apps, games, notifications

***

# 📅 Day 1 — WebSocket Basics

## 📦 Install

```bash
npm install socket.io
```

***

## ⚡ Basic Server

```js
import { createServer } from "http";
import { Server } from "socket.io";

const httpServer = createServer();

const io = new Server(httpServer);

io.on("connection", (socket) => {
  console.log("User connected:", socket.id);

  socket.on("disconnect", () => {
    console.log("User disconnected");
  });
});

httpServer.listen(3000);
```

***

## 🧠 Learn

* `connection` event

* Each user = unique socket

* Persistent connection

***

## 💪 Exercise

* Log connection time

* Count connected users

***

# 📅 Day 2 — Sending Messages

## 💬 Emit Events

```js
io.on("connection", (socket) => {
  socket.on("chat message", (msg) => {
    console.log("Message:", msg);

    io.emit("chat message", msg); // send to all
  });
});
```

***

## 🧠 Learn

* `emit` = send event

* `on` = receive event

***

## 💪 Exercise

* Add username to messages

***

# 📅 Day 3 — Simple Client (HTML)

Create `index.html`:

```html
<!DOCTYPE html>
<html>
<body>
  <input id="msg" />
  <button onclick="send()">Send</button>

  <ul id="messages"></ul>

  <script src="/socket.io/socket.io.js"></script>
  <script>
    const socket = io();

    socket.on("chat message", (msg) => {
      const li = document.createElement("li");
      li.textContent = msg;
      document.getElementById("messages").appendChild(li);
    });

    function send() {
      const msg = document.getElementById("msg").value;
      socket.emit("chat message", msg);
    }
  </script>
</body>
</html>
```

***

## 🧠 Learn

* Browser connects via Socket.IO

* Real-time updates without refresh

***

## 💪 Exercise

* Clear input after send

* Add timestamps

***

# 📅 Day 4 — Rooms (Private Chats)

## 🏠 Join Room

```js
socket.join("room1");
```

***

## 📤 Send to Room

```js
io.to("room1").emit("chat message", "Hello Room!");
```

***

## 🧠 Learn

* Rooms = groups of users

* Enables private chats

***

## 💪 Exercise

* Create dynamic rooms (chat channels)

***

# 📅 Day 5 — User Management 👥

## 🧠 Track Users

```js
const users = {};

io.on("connection", (socket) => {
  users[socket.id] = "Anonymous";

  socket.on("set username", (name) => {
    users[socket.id] = name;
  });
});
```

***

## 💪 Exercise

* Broadcast when user joins/leaves

* Show username with messages

***

# 📅 Day 6 — Secure WebSockets 🔐

## 🧠 Idea

Reuse your JWT auth from Week 4

***

## 🔐 Example

```js
io.use((socket, next) => {
  const token = socket.handshake.auth.token;

  try {
    const user = jwt.verify(token, process.env.JWT_SECRET);
    socket.user = user;
    next();
  } catch {
    next(new Error("Unauthorized"));
  }
});
```

***

## 💪 Exercise

* Reject users without token

* Attach user ID to messages

***

# 📅 Day 7 — Final Chat App 🔥

## 🧱 Features

Build a **real-time chat system**:

* ✅ Users join with username

* ✅ Send/receive messages instantly

* ✅ Rooms (channels)

* ✅ JWT authentication

* ✅ Show connected users

***

## 🧪 Test Without GUI (Your Preference 💪)

### Option 1: Use curl (limited for WebSockets)

👉 curl is not ideal for WebSockets

***

### ✅ Better CLI Tool

Install:

```bash
npm install -g wscat
```

***

### 🧪 Connect

```bash
wscat -c ws://localhost:3000
```

***

### 💬 Send Message

```bash
{"event":"chat message","data":"Hello"}
```

***

## 💪 Exercise

* Connect 2 terminals

* Send messages between them

***

# 🧠 End of Week 7 — You Now Know

✅ WebSockets\
✅ Real-time communication\
✅ Socket.IO\
✅ Rooms & users\
✅ Authenticated sockets

👉 You can now build:

* Chat apps 💬

* Live dashboards 📊

* Multiplayer games 🎮

***

# 🚀 What You’ve Achieved (Big Picture)

You went from:

* Scripts → APIs → Databases → Auth → Deployment → Testing → Real-time

👉 That’s basically a **full backend engineer path**

***

# 🔥 If You Want Next Level

Week 8 ideas:

* Scaling WebSockets (Redis)

* Event-driven architecture

* Message queues (RabbitMQ)

* Microservices

***

If you want, I can build:

👉 **Week 8: Scaling & System Design**

Just say:\
**“Week 8 please”**

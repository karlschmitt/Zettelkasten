---
id: 20260419152337
title: Week Five of Node.js Bootcamp
author: Karl Schmitt
date: 2026-04-19
keywords: [ Node.js, node, npm, JavaScript]
---

# Week Five of Node.js Bootcamp

Excellent—Week 5 is where you go from “it works” → **it’s production-ready** 🔥\
You’ll learn how to **configure, secure, monitor, and deploy** your API.

***

# 🚀 Week 5: Production Readiness & Deployment

## 🎯 Goal of Week 5

* Use environment variables (`.env`)

* Add logging & error handling

* Implement rate limiting & security

* Containerize with Docker

* Deploy your API

***

# 📅 Day 1 — Environment Variables (.env)

## 📦 Install

```bash
npm install dotenv
```

***

## 📁 Create `.env`

```env
PORT=3000
JWT_SECRET=my_super_secret_key
```

***

## 🔌 Use in Code

```js
import dotenv from "dotenv";
dotenv.config();

const PORT = process.env.PORT || 3000;
const SECRET = process.env.JWT_SECRET;
```

***

## 🧠 Why This Matters

* No hardcoded secrets ❌

* Different configs per environment ✅

***

## 💪 Exercise

* Move all secrets into `.env`

* Remove `"secretkey"` from your code

***

# 📅 Day 2 — Logging (Know What Happens)

## 📦 Install Logger

```bash
npm install morgan
```

***

## 🔍 Use It

```js
import morgan from "morgan";

app.use(morgan("dev"));
```

***

## 🧠 Learn

* Logs every request

* Helps debugging & monitoring

***

## 💪 Exercise

* Create custom logger middleware:

  * Method

  * URL

  * Timestamp

***

# 📅 Day 3 — Security Basics 🔐

## 📦 Install

```bash
npm install helmet cors
```

***

## 🛡️ Use Them

```js
import helmet from "helmet";
import cors from "cors";

app.use(helmet());
app.use(cors());
```

***

## 🧠 Learn

* `helmet` → protects headers

* `cors` → controls access from frontend

***

## 💪 Exercise

* Restrict CORS to one origin

***

# 📅 Day 4 — Rate Limiting 🚦

## 📦 Install

```bash
npm install express-rate-limit
```

***

## ⏱️ Limit Requests

```js
import rateLimit from "express-rate-limit";

const limiter = rateLimit({
  windowMs: 60 * 1000, // 1 min
  max: 5
});

app.use(limiter);
```

***

## 🧪 Test with curl

```bash
for i in {1..10}; do curl http://localhost:3000; done
```

👉 You should get blocked after a few requests

***

## 💪 Exercise

* Apply limiter only to `/login`

***

# 📅 Day 5 — Error Handling (Professional Level)

## ❌ Central Error Handler

```js
app.use((err, req, res, next) => {
  console.error(err.stack);

  res.status(500).json({
    error: "Something went wrong"
  });
});
```

***

## 🧠 Learn

* Never expose internal errors

* Always send clean responses

***

## 💪 Exercise

* Throw custom errors in routes

* Catch them in middleware

***

# 📅 Day 6 — Docker (Game Changer 🐳)

## 📁 Create `Dockerfile`

```Dockerfile
FROM node:18

WORKDIR /app

COPY package*.json ./
RUN npm install

COPY . .

CMD ["node", "index.js"]
```

***

## 🐳 Build Image

```bash
docker build -t node-api .
```

***

## ▶️ Run Container

```bash
docker run -p 3000:3000 node-api
```

***

## 🧠 Learn

* Same environment everywhere

* No “works on my machine” problems

***

## 💪 Exercise

* Add `.dockerignore`

***

# 📅 Day 7 — Deployment 🌍

## 🚀 Options

* Render

* Railway

* Fly.io

***

## 🧭 Basic Steps

1. Push code to GitHub

2. Connect repo to platform

3. Set environment variables

4. Deploy

***

## 🧪 Test Your Live API

```bash
curl https://your-api-url.com/notes
```

***

## 💪 Exercise

* Deploy your Notes API

* Test login + protected route

***

# 🧠 End of Week 5 — You Now Know

✅ Environment configs (`.env`)\
✅ Logging (morgan)\
✅ Security (helmet, cors)\
✅ Rate limiting\
✅ Error handling\
✅ Docker basics\
✅ Deployment

👉 You now have **production-ready backend skills**

***

# ⚡ Final Project (🔥 BIG ONE)

## 🧱 Production-Ready Notes API

Must include:

* Auth (JWT)

* SQLite DB

* Clean architecture

* `.env` config

* Logging

* Security middleware

* Rate limiting

* Docker support

* Deployed online

***

# 🧪 Test ONLY with

### curl

```bash
curl -H "Authorization: Bearer TOKEN" https://your-api-url.com/notes
```

### PowerShell

```powershell
Invoke-RestMethod -Uri "https://your-api-url.com/notes" -Headers @{Authorization="Bearer TOKEN"}
```

***

# 🚀 What You’ve Achieved

You went from:\
👉 “What is Node?”\
to\
👉 **Building & deploying secure APIs**

That’s huge.

***

# 🔥 If You Want to Go Further

Next level topics:

* Testing (Jest)

* TypeScript with Node

* WebSockets

* Microservices

* GraphQL

***

If you want, I can design:

👉 **Week 6: Testing + TypeScript + Clean Architecture**

Just say:\
**“Week 6 please”**

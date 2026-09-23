---
id: 20260923152148
---

# Docker Nodejs Example

To swap Python out for Node.js, we will build a minimal Express web server inside a container.

Follow these steps in a new, empty directory to containerize a Node.js application.

## Step 1: Create the Node.js Application

First, set up your project files. You don't even need Node.js installed on your host machine to do this.

1. Create a file named `package.json` to define your project dependencies:
   ```json
   {
     "name": "docker-node-demo",
     "version": "1.0.0",
     "main": "server.js",
     "dependencies": {
       "express": "^4.19.0"
     }
   }
   ```
2. Create a file named `server.js` and add a basic HTTP route:
   ```javascript
   const express = require('express');
   const app = express();
   const PORT = 3000;

   app.get('/', (req, res) => {
     res.send('Hello from your custom Node.js Docker container! 🚀');
   });

   app.listen(PORT, () => {
     console.log(`Server is running on port ${PORT}`);
   });
   ```

***

## Step 2: Write the Dockerfile

Create a file named `Dockerfile` (with no file extension) in the same directory and add the following configuration:

```dockerfile
# Step 1: Use the official lightweight Node.js image
FROM node:20-slim

# Step 2: Set the working directory inside the container
WORKDIR /usr/src/app

# Step 3: Copy package files and install production dependencies
COPY package*.json ./
RUN npm install --only=production

# Step 4: Copy the rest of your application code
COPY . .

# Step 5: Expose the port the app runs on
EXPOSE 3000

# Step 6: Define the command to run the app
CMD ["node", "server.js"]
```

***

## Step 3: Add a Docker Ignore File (Best Practice)

To prevent copying bulky, unnecessary local files (like `node_modules` if you happen to install them locally later) into your image, create a `.dockerignore` file in the same folder:

```text
node_modules
npm-debug.log
```

***

## Step 4: Build and Run Your Container

Open your terminal inside your project folder and execute these commands:

1. Build the Node.js image:
   ```bash
   docker build -t my-node-app .
   ```
2. Run the container:
   ```bash
   docker run -d -p 3000:3000 --name running-node-app my-node-app
   ```

Test it: Open your browser and navigate to `http://localhost:3000`. You will see the live response from your containerized Express server.

Would you like to see how to use Docker Compose to link this Node.js app to a database (like MongoDB or PostgreSQL), or should we look into Docker Volumes so your container code updates automatically when you make local edits?


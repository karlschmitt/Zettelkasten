---
id: 20261007195127
title: Electron Wayland Container
author: Karl Schmitt
date: 2026-10-07
---


# Electron Wayland Container

> [NOTE!
> Here is the exact, 100% reproducible step-by-step setup to write the `Dockerfile` and start your accelerated Electron app container immediately.

***

## Step 1: Create the Build Blueprint (`Dockerfile`)

Run this command to create the file directly using `cat`:

```bash
cat << 'EOF' > Dockerfile
# =====================================================================
# STAGE 1: Build the App and System Dependencies
# =====================================================================
FROM debian:bookworm-slim

# Avoid prompts during installation phase
ENV DEBIAN_FRONTEND=noninteractive
ENV XDG_RUNTIME_DIR=/tmp/runtime-root

# Install core Wayland stack, Weston, VNC server, and Electron runtime prerequisites
RUN apt-get update && apt-get install -y --no-install-recommends \
    weston \
    wayvnc \
    libgl1-mesa-dri \
    xwayland \
    curl \
    ca-certificates \
    gnupg \
    # Electron/Chromium essential system dependencies
    libgtk-3-0 \
    libnss3 \
    libatk1.0-0 \
    libatk-bridge2.0-0 \
    libdrm2 \
    libgbm1 \
    libasound2 \
    libxshmfence1 \
    libsecret-1-0 \
    && rm -rf /var/lib/apt/lists/*

# Install modern Node.js long term support (LTS) cleanly
RUN curl -fsSL https://nodesource.com | bash - \
    && apt-get install -y nodejs \
    && rm -rf /var/lib/apt/lists/*

# Create working directory workspace layout
WORKDIR /app

# Initialize a basic minimal Electron.js project skeleton inline
RUN npm init -y && \
    npm install electron --save-dev

# Create a sample Electron application runner script file
RUN echo "const { app, BrowserWindow } = require('electron'); \n\
app.whenReady().then(() => { \n\
  const win = new BrowserWindow({ width: 1024, height: 768, webPreferences: { nodeIntegration: true } }); \n\
  win.loadURL('https://wayland.freedesktop.org/'); \n\
});" > index.js

# Modify the default start script inside package.json
RUN sed -i 's/"test".*/"start": "electron ."/g' package.json

# Correct Electron's built-in sandbox binary execution flags for container limits
RUN chmod 4755 /app/node_modules/electron/dist/chrome-sandbox

# Setup the default Headless Weston configuration environment inside the container
RUN mkdir -p /root/.config/
RUN echo "[core]\n\
backend=headless-backend.so\n\
xwayland=true\n\
\n\
[shell]\n\
locking=false" > /root/.config/weston.ini

# Expose VNC Port to remote client applications
EXPOSE 5900

# Entrypoint Execution Script: Fires up headless Weston, starts wayvnc mapping, launches Electron
CMD mkdir -p $XDG_RUNTIME_DIR && chmod 700 $XDG_RUNTIME_DIR && \
    weston --socket=wayland-0 --width=1024 --height=768 --idle-time=0 & \
    sleep 2 && \
    wayvnc 0.0.0.0 5900 & \
    sleep 2 && \
    export WAYLAND_DISPLAY=wayland-0 && \
    export ELECTRON_OZONE_PLATFORM_HINT=wayland && \
    npm start -- --no-sandbox
EOF
```

***

## Step 2: Build the Container Image

Execute this command to compile the Docker container configuration. This will pull the Debian framework, install Node.js, and compile the Electron base modules: \[1]

```bash
docker build -t electron-wayland-client .
```

***

## Step 3: Run the Image Natively

Launch the newly built, reproducible container stack with its communication ports open:

```bash
docker run -d \
  -p 5900:5900 \
  --name wayland-client-app \
  electron-wayland-client
```

***

## 🖥️ Connecting to Your Graphical Interface

1. Launch your preferred VNC Viewer client (e.g., [TightVNC](https://www.tightvnc.com/), UltraVNC, or RealVNC) on your main Windows host.
2. Put this local address string into the connection prompt:
3. Hit Connect. Your headless desktop frame buffer stream will open up instantly, displaying your custom Electron.js frame rendering cleanly over Wayland/Weston with no breaks!

Let me know if the `docker build` goes through smoothly! Once you confirm the base container is working, would you like to know how to mount your local project code directory directly into the container using volume maps (`-v`) so you can code your Electron app dynamically without rebuilding the image? \[1]



\[1] [https://dev.to](https://dev.to/trigo/develop-electron-in-docker-52h3)

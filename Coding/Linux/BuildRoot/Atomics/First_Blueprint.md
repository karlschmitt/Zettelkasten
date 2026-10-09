---
id: 20261009114209
title: First Configuration Blueprint
author: Karl Schmitt
date: 2026-10-04
keywords: [ Buildroot ]
---

# 🟦 First Configuratin Blueprint 🏗️


## Install Buildroot prerequisites

![Debian](../../Images/Debian_Logo.png)

Install the necessary tools inside your WSL Debian instance using a GNU Bash terminal:

![Gnu Bash Logo](../../Images/Gnu-bash-logo.png)
```bash
sudo apt update
sudo apt upgrade -y
sudo apt install -y \
    build-essential \
    git \
    bc \
    unzip \
    python3 \
    wget \
    cpio \
    rsync \
    libncurses-dev \
    libncursesw5-dev \
    file \
    dos2unix \
    xclip \
    libelf-dev \
    qemu-system-x86 \
    qemu-utils \
    libgl1-mesa-dri \ 
    libvirglrenderer1 \ 
    virgl-server \
    libegl1 \ 
    libgbm1 \ 
    libgl1 \ 
    libgles2 \ 
    libglx-mesa0 \ 
    libgl1-mesa-dri

```
## Let's begin

Let“s do it in small steps. Create a new directory and clone the Buildroot repository:

```bash
mkdir -p ~/Second_Chance/First_Blueprin
```
```bash
cd ~/Second_Chance/First_Blueprint
```
```bash
git clone https://github.com/buildroot/buildroot.git
```
```bash
cd buildroot
```

This blueprint project contains only Buildroot plus Wayland to test your build environmet on Debian WSL:
```bash
# 1. Create your stable, reproducible defconfig blueprint file
cat << 'EOF' > configs/wayland_client_x86_64_defconfig
# QEMU x86_64 Virtual Board Target Layout Mapping
BR2_x86_64=y
BR2_x86_x86_64=y

# Toolchain (Standard GLIBC with C++ for Wayland/Electron requirements)
BR2_TOOLCHAIN_BUILDROOT_GLIBC=y
BR2_INSTALL_LIBSTDCPP=y
BR2_TOOLCHAIN_BUILDROOT_CXX=y

# Core Init System Options (SysVinit + Eudev avoids Sandbox Compilation Bugs)
BR2_INIT_SYSV=y
BR2_ROOTFS_DEVICE_CREATION_DYNAMIC_EUDEV=y

# Linux Kernel Source (Tied natively to the virtual machine board pipeline)
BR2_LINUX_KERNEL=y
BR2_LINUX_KERNEL_USE_CUSTOM_CONFIG=y
BR2_LINUX_KERNEL_CUSTOM_CONFIG_FILE="board/qemu/x86_64/linux.config"

# Graphics Framework Stack (Mesa3D serving Accelerated OpenGL ES & EGL)
BR2_PACKAGE_MESA3D=y
BR2_PACKAGE_MESA3D_GALLIUM_DRIVER_VIRGL=y
BR2_PACKAGE_MESA3D_OPENGL_EGL=y
BR2_PACKAGE_MESA3D_OPENGL_ES=y

# Wayland & Headless Weston Ecosystem Applications
BR2_PACKAGE_WAYLAND=y
BR2_PACKAGE_WESTON=y
BR2_PACKAGE_WESTON_DEFAULT_COMPOSITOR_DRM=y
BR2_PACKAGE_WESTON_SIMPLE_CLIENTS=y
BR2_PACKAGE_WESTON_DEMO_CLIENTS=y

# Core Utilities Framework
BR2_PACKAGE_UTIL_LINUX=y
BR2_PACKAGE_UTIL_LINUX_BINARIES=y

# Filesystem Packaging Target Limits (Expanded to 1GB to support assets)
BR2_TARGET_ROOTFS_EXT2=y
BR2_TARGET_ROOTFS_EXT2_4=y
BR2_TARGET_ROOTFS_EXT2_SIZE="1G"
EOF

# 2. Apply your configuration blueprint to generate the master .config
make wayland_client_x86_64_defconfig

# 3. Launch your clean compilation sequence
make
```
Create the start script ```./output/images/start-qemu.sh```:
```bash
cat << 'EOF' > output/images/start-qemu.sh
#!/bin/sh
IMAGE_DIR="$(dirname "$0")"

exec qemu-system-x86_64 \
    -M q35 \
    -m 2G \
    -smp 2 \
    -kernel "${IMAGE_DIR}/bzImage" \
    -drive file="${IMAGE_DIR}/rootfs.ext4",if=virtio,format=raw \
    -append "root=/dev/vda ro console=ttyS0 quiet" \
    -net nic,model=virtio -net user \
    -device virtio-vga-gl \
    -display gtk,gl=on \
    -serial stdio
EOF

# Make the script executable
chmod +x output/images/start-qemu.sh
```
🚀 Boot up! 

```bash
./output/images/start-qemu.sh
```

🖥️ You should see now:

![First Blueprint QEMU](../../Images/First_Blueprint_QEMU_001.png)

📨 We need to tell the kernel to send output to _both_ the serial port and the virtual screen:
```bash
cat << 'EOF' > output/images/start-qemu.sh
#!/bin/sh
IMAGE_DIR="$(dirname "$0")"

exec qemu-system-x86_64 \
    -M q35 \
    -m 2G \
    -smp 2 \
    -kernel "${IMAGE_DIR}/bzImage" \
    -drive file="${IMAGE_DIR}/rootfs.ext4",if=virtio,format=raw \
    -append "root=/dev/vda ro console=tty1 console=ttyS0 quiet" \
    -net nic,model=virtio -net user \
    -device virtio-vga-gl \
    -display gtk,gl=on \
    -serial stdio
EOF

chmod +x output/images/start-qemu.sh
```
🛠️ Create the Weston Configuration File

```bash
cat << 'EOF' > board/custom_client/rootfs-overlay/etc/xdg/weston/weston.ini
[core]
backend=drm-backend.so
renderer=gl
xwayland=true

[shell]
locking=false
panel-position=top

[launcher]
icon=/usr/share/weston/icon_terminal.png
path=/usr/bin/weston-terminal
EOF
```
Re-Package Your Image File
```
make
```


🚀 Generate the startup script:
```bash
# 1. Create the boot script directory layout
mkdir -p board/custom_client/rootfs-overlay/etc/init.d/

# 2. Write the automated Weston startup service script
cat << 'EOF' > board/custom_client/rootfs-overlay/etc/init.d/S90weston
#!/bin/sh
case "$1" in
  start)
    echo "Starting Weston Display Server..."
    export XDG_RUNTIME_DIR=/tmp/runtime-root
    mkdir -p $XDG_RUNTIME_DIR
    chmod 700 $XDG_RUNTIME_DIR
    
    # Run Weston dynamically on the active virtual console
    weston --tty=1 --backend=drm-backend.so &
    ;;
  stop)
    echo "Stopping Weston..."
    killall weston
    ;;
  *)
    echo "Usage: $0 {start|stop}"
    exit 1
esac
exit 0
EOF

# 3. Make the startup script executable
chmod +x board/custom_client/rootfs-overlay/etc/init.d/S90weston
```
📦Re-Package the Image:
```bash
# Force the overlay variable into the defconfig if it isn't there already
if ! grep -q "BR2_ROOTFS_OVERLAY" configs/wayland_client_x86_64_defconfig; then
    echo 'BR2_ROOTFS_OVERLAY="board/custom_client/rootfs-overlay"' >> configs/wayland_client_x86_64_defconfig
fi

# Reload the configuration file blueprint and re-run make to merge the overlay
make wayland_client_x86_64_defconfig
make
```

🚀 Boot Up Agan
```bash
./output/images/start-qemu.sh
```



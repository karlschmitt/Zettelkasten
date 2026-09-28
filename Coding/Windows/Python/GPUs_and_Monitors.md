---
id: 20260923195605
title: Linux GPU and Monitor Output Discovery
author: Karl Schmitt
date: 2026-09-23
---

# Linux GPU and Monitor Output Discovery (Non-Vulkan Alternatives)

On Linux, you can bypass the Vulkan API completely to inspect graphics topology. The operating system exposes this data via command-line utilities and the `/sys/class/drm/` kernel subsystem.

### 1. 🛠️ Native Linux Command Line Tools

If you need a quick query via the terminal, use these built-in utilities:

* **`lspci` (GPU Hardware)**: Lists all PCI devices. Filter it for graphics controllers.
  ```bash
  lspci -vnn | grep -E -i "VGA|3D|Display"
  ```
* **`xrandr` (Monitors via X11)**: Shows all active video ports and attached monitors if you are running an X11 server desktop session.
  ```bash
  xrandr --listmonitors
  ```
* **`wlr-randr` or `gnome-monitor-secrets` (Monitors via Wayland)**: If your Linux distro uses Wayland instead of X11, use your compositor's tool:
  ```bash
  wlr-randr
  ```

---

### 2. 💻 Python Linux Kernel Kernel Parser (Zero Dependencies)

Linux exposes the **Direct Rendering Manager (DRM)** under the `/sys` virtual directory. The script below reads this filesystem directory to discover exactly how many GPU cards are installed and which video output connectors (HDMI, DisplayPort, eDP) have an active monitor status.

Save this script as `linux_hardware_scan.py`:

```python
import os
import re

def discover_linux_graphics():
    drm_path = "/sys/class/drm"
    if not os.path.exists(drm_path):
        print("❌ Error: DRM subsystem not found. This script must run natively on Linux.")
        return

    print("\n=======================================================")
    print("🐧 Linux DRM Graphics & Monitor Port Scanner")
    print("=======================================================")

    # 1. Locate GPU Cards (labeled as 'card0', 'card1', etc.)
    all_nodes = os.listdir(drm_path)
    cards = sorted([n for n in all_nodes if re.match(r'^card\d+$', n)])
    
    print(f"📊 Found {len(cards)} Physical GPU device node(s).")

    # 2. Match Connectors to their respective Cards
    for card in cards:
        print(f"\n[GPU Card Node]: /dev/dri/{card}")
        
        # Connectors for a card look like 'card0-HDMI-A-1', 'card1-DP-2', etc.
        connector_pattern = re.compile(rf'^{card}-.*')
        connectors = sorted([n for n in all_nodes if connector_pattern.match(n)])
        
        active_monitors = 0
        ports_found = []

        for conn in connectors:
            # Human readable port label (e.g., HDMI-A-1)
            port_name = conn.replace(f"{card}-", "")
            
            # Read the 'status' file in the sysfs node to check for a monitor hookup
            status_file_path = os.path.join(drm_path, conn, "status")
            
            if os.path.exists(status_file_path):
                with open(status_file_path, "r") as f:
                    status = f.read().strip()
                
                if status == "connected":
                    # Try to fetch screen resolution dimensions if available
                    modes_file_path = os.path.join(drm_path, conn, "modes")
                    res = "Unknown Resolution"
                    if os.path.exists(modes_file_path):
                        with open(modes_file_path, "r") as mf:
                            modes = mf.read().splitlines()
                            if modes:
                                res = modes[0] # Grab preferred/top resolution
                    
                    ports_found.append(f"     📍 Port {port_name} -> 🖥️  MONITOR CONNECTED ({res})")
                    active_monitors += 1
                else:
                    ports_found.append(f"     📍 Port {port_name} -> Disconnected")

        print(f"  🔹 Total Video Output Ports Found: {len(connectors)}")
        print(f"  🔹 Active Monitors Driven by this GPU: {active_monitors}")
        for port_info in ports_found:
            print(port_info)

    print(f"\n=======================================================\n")

if __name__ == "__main__":
    discover_linux_graphics()
```

---

### 🔍 System Mechanics Explained

* **`/sys/class/drm/`**: This is a direct pipeline to the Linux kernel graphics stack. It does not rely on Vulkan, OpenGL, X11, or Wayland being up and running, meaning this script works even in a headless Linux server environment or SSH session.
* **`status` file**: Contains either `connected` or `disconnected`. The Linux kernel automatically flags this using hot-plug detection (HPD) pins inside your physical HDMI or DisplayPort cables.
* **`modes` file**: Lists all available resolutions the EDID chip of your monitor told the Linux graphics card it could safely display.

---

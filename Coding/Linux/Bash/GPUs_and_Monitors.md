---
id: 20260923200418
title: GPU and Monitor Discovery via Bash
author: Karl Schmitt
date: 2026-09-23
keywords: [ Linux, GPU, Monitor, Bash]
---

# Linux GPU and Monitor Discovery via Bash

This script provides a pure Bash alternative to query graphics devices and monitor outputs on Linux [2026 update]. It combines native kernel file parsing with fallback checks for common display servers (X11/Wayland).

### 💻 System Topology Bash Script

Save this script as `discover_hardware.sh`:

```bash
#!/usr/bin/env bash

# Colors for scannable output
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "BLUE======================================================={NC}"
echo -e "🐧 Linux GPU & Monitor Discovery Tool"
echo -e "BLUE======================================================={NC}"

# 1. Discover Graphics Cards via PCI bus
echo -e "\n\${YELLOW}📦 Physical GPU Hardware (via lspci):\${NC}"
if command -v lspci &> /dev/null; then
    lspci | grep -E -i "VGA|3D|Display" | while read -r line; do
        echo -e "  🔹 \$line"
    done
else
    echo "  ⚠️  lspci utility not found. Skipping hardware device name lookup."
fi

# 2. Parse Kernel DRM State for Monitor Layout (Works headless/SSH)
echo -e "\n\${YELLOW}🔌 Kernel DRM Video Port Connections:\${NC}"
DRM_PATH="/sys/class/drm"

if [ -d "\$DRM_PATH" ]; then
    # Find unique card directories (e.g., card0, card1)
    for card_dir in "\$DRM_PATH"/card[0-9]; do
        [ -e "\$card_dir" ] || continue
        card_name=(basename "card_dir")
        echo -e "  \${GREEN}[\(card_name Link Status]\){NC}"
        
        # Match all connector subfolders for this card (e.g., card0-HDMI-A-1)
        active_count=0
        for conn_dir in "\(DRM_PATH"/"\)card_name"-*; do
            [ -e "\$conn_dir" ] || continue
            port_name=\({conn_dir#*"\)card_name"-}
            
            if [ -f "\$conn_dir/status" ]; then
                status=(cat "conn_dir/status")
                if [ "\$status" = "connected" ]; then
                    # Fetch preferred target display mode/resolution
                    resolution="Unknown Resolution"
                    if [ -f "\$conn_dir/modes" ]; then
                        resolution=(head -n 1 "conn_dir/modes")
                    fi
                    echo -e "     📍 Port \(port_name ->\){GREEN}🖥️  CONNECTEDNC (resolution)"
                    ((active_count++))
                else
                    echo -e "     📍 Port \$port_name -> Disconnected"
                fi
            fi
        done
        echo -e "  Total displays actively rendering on \(card_name:\)active_count\n"
    done
else
    echo -e "  ❌ /sys/class/drm directory missing. Cannot parse kernel monitor connections."
fi

# 3. Environment Display Client Check
echo -e "\${YELLOW}🖥️  Active Session Window Managers (Display Server View):\${NC}"
if [ -n "\$WAYLAND_DISPLAY" ]; then
    echo -e "  🔹 Protocol running: Wayland (\$WAYLAND_DISPLAY)"
    if command -v wlr-randr &> /dev/null; then
        wlr-randr | grep -E "Enabled|current" | sed 's/^/     /'
    fi
elif [ -n "\$DISPLAY" ]; then
    echo -e "  🔹 Protocol running: X11 (\$DISPLAY)"
    if command -v xrandr &> /dev/null; then
        xrandr --listmonitors | sed 's/^/     /'
    fi
else
    echo -e "  🔹 Server State: Headless / No GUI Display Server Active"
fi

echo -e "\nBLUE======================================================={NC}"
```

### ⚙️ How to Run the Script

1. Make the file executable:
   ```bash
   chmod +x discover_hardware.sh
   ```
2. Execute the script:
   ```bash
   ./discover_hardware.sh
   ```

---

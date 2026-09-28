---
id: 20260923202721
---

# Wayland 4-Monitor Layout Management via Bash

On a Linux **Wayland** system, you address and arrange all four monitors across your dual-GPU setup using layout toolchains specific to your active desktop environment (Compositor). Wayland maps your screens into a unified global pixel grid.

Because tool integration varies by compositor, you can use these Bash script options to target and format your 4-monitor array.

---

### Option 1: For `wlroots` Compositors (Sway, Hyprland) using `wlr-randr`

The `wlr-randr` tool acts similarly to X11's `xrandr` for Wayland implementations that leverage the standard layout management protocol. 

Save this script as `set_wlroots_4monitors.sh`:

```bash
#!/usr/bin/env bash
# Arranges 4 monitors side-by-side on a continuous horizontal canvas layout

# Identify output strings using: wlr-randr
MON1="DP-1"
MON2="DP-2"
MON3="HDMI-A-1"
MON4="HDMI-A-2"

echo "🔄 Programming Wayland global canvas alignment..."

# Monitor 1 (GPU 0) - Placed at local origin
wlr-randr --output "$MON1" --custom-mode 1920x1080@60Hz --pos 0,0 --on

# Monitor 2 (GPU 0) - Shifted right by 1920 pixels
wlr-randr --output "$MON2" --custom-mode 1920x1080@60Hz --pos 1920,0 --on

# Monitor 3 (GPU 1) - Shifted right by 3840 pixels
wlr-randr --output "$MON3" --custom-mode 1920x1080@60Hz --pos 3840,0 --on

# Monitor 4 (GPU 1) - Shifted right by 5760 pixels
wlr-randr --output "$MON4" --custom-mode 1920x1080@60Hz --pos 5760,0 --on

echo "✅ Canvas mapped successfully."
```

---

### Option 2: For GNOME Compositor (`mutter`) using `gnome-monitor-config`

GNOME uses its own `mutter` window architecture on Wayland. To address individual monitors on a pixel grid from a bash script, utilize the utility tool `gnome-monitor-config`.

Save this script as `set_gnome_4monitors.sh`:

```bash
#!/usr/bin/env bash
# Configures a 2x2 grid topology layout using GNOME's native config tool

# Identify output strings using: gnome-monitor-config list
M1="DP-1"
M2="DP-2"
M3="HDMI-1"
M4="HDMI-2"

echo "🔄 Arranging 4-Display Layout Grid under GNOME Shell..."

gnome-monitor-config set \
  -LpM "$M1" --mode 1920x1080@60.000 --x 0    --y 0    --transform normal \
  -LM  "$M2" --mode 1920x1080@60.000 --x 1920 --y 0    --transform normal \
  -LM  "$M3" --mode 1920x1080@60.000 --x 0    --y 1080 --transform normal \
  -LM  "$M4" --mode 1920x1080@60.000 --x 1920 --y 1080 --transform normal

echo "✅ GNOME monitors update complete."
```
*(Note: `-LpM` flags the primary target viewport where your core taskbar and desktop environment center by default.)*

---

### Option 3: For KDE Plasma (`KWin`) using `kscreen-doctor`

KDE desktops use `kscreen-doctor` to control coordinate placement across separate GPU hardware outputs on Wayland.

Save this script as `set_kde_4monitors.sh`:

```bash
#!/usr/bin/env bash
# Linearly binds 4 displays using ID strings from: kscreen-doctor --outputs

kscreen-doctor \
  output.1.mode.1920x1080@60 output.1.position.0,0 \
  output.2.mode.1920x1080@60 output.2.position.1920,0 \
  output.3.mode.1920x1080@60 output.3.position.3840,0 \
  output.4.mode.1920x1080@60 output.4.position.5760,0

echo "✅ KDE virtual window placement configured."
```

---
#linux #wayland #bash #automation #multi-monitor #compositor

# Sway on WSL (Windows 11 + WSLg) — Setup Summary

A working [Sway](https://swaywm.org/) tiling Wayland compositor running nested inside
WSLg on Windows 11 with Ubuntu. This document summarizes the full setup, the problems
encountered, how they were fixed, and a keybinding reference.

- **OS:** Windows 11 (provides WSLg automatically)
- **Distro:** Ubuntu 26.04.1 LTS (in WSL2)
- **Compositor:** Sway 1.11 (wlroots 0.19.1)
- **Terminal:** foot
- **Launcher:** wmenu
- **Status bar:** waybar

---

## How it works (the key concept)

Sway is a Wayland compositor. WSLg already runs its own Wayland compositor in the
background, so Sway can't grab real hardware — it must run **nested** inside WSLg's
Wayland session. This is enabled by an environment variable:

```
WLR_BACKENDS=wayland
```

This tells wlroots (Sway's backend) to render into WSLg's existing Wayland session
instead of looking for GPU/DRM hardware (which does not exist in WSL).

It was made permanent by adding this line to `~/.bashrc`:

```bash
export WLR_BACKENDS=wayland
```

Then Sway is launched simply with:

```bash
sway
```

---

## Packages installed

```bash
sudo apt update
sudo apt install -y sway foot wmenu waybar xwayland gnome-clocks
```

(`suckless-tools`/`dmenu` was tried first but does not work under WSLg — see
troubleshooting below.)

---

## Problems encountered and fixes

### 1. Keybindings did nothing (black window, no response)
**Cause:** Two issues — (a) the Sway window didn't have keyboard focus, and (b) the
default modifier key `Super` (Windows key) is intercepted by Windows/WSLg.

**Fix:**
- **Click the Sway window first** so WSLg gives it keyboard focus. This is a recurring
  WSLg quirk: if keys ever stop responding, click the window once.
- Changed the modifier from `Super` (`Mod4`) to **`Alt` (`Mod1`)** in the config:
  ```
  set $mod Mod1
  ```

### 2. Xwayland error flood at startup
**Symptom:** dozens of lines of `sticky bit not set on /tmp/.X11-unix` ending in
`Failed to start Xwayland`.

**Cause:** WSL's `/tmp/.X11-unix` lacks the sticky-bit permission Xwayland requires.
Only affects X11 apps; native Wayland apps are unaffected.

**Fix:** Disabled Xwayland (we only run Wayland apps). Added to config:
```
xwayland disable
```
> Note: `xwayland disable` only takes effect on a **full Sway restart**, not a reload.

### 3. Editing the config kept failing from the terminal
**Symptom:** Pasting multi-line config into `nano` / here-docs in the terminal dropped
content; the config never actually changed.

**Cause:** The terminal was not reliably receiving multi-line pastes.

**Fix (the breakthrough):** Edit the config directly from **Windows** via the UNC path,
which maps to the WSL home directory:
```
\\wsl$\Ubuntu\home\karl\.config\sway\config
```
(equivalent to `~/.config/sway/config` inside Ubuntu). Open it in Notepad/VS Code, edit,
save. This completely avoids the terminal paste problem. To copy a file from the D:
drive into WSL instead, a single short command works:
```bash
cp /mnt/d/Learning/Wayland/Config/config ~/.config/sway/config
```

### 4. App launcher (`Alt+d`) failed with "cannot grab keyboard"
**Symptom:** `dmenu` printed `cannot grab keyboard` repeatedly and did nothing.

**Cause:** `dmenu` is X11-oriented and uses an exclusive keyboard grab that a nested
WSLg Wayland session won't grant.

**Fix:** Switched to **wmenu** (native Wayland, uses layer-shell):
```
set $menu wmenu-run
```

### 5. GUI apps (gnome-clocks) showed EGL/GPU errors and were slow
**Symptom:** `libEGL warning: failed to get driver name`, `MESA: ZINK: failed to choose
pdev`, `failed to create dri2 screen`.

**Cause:** No GPU acceleration under WSLg; apps try GPU first, fail, then fall back to
software rendering (slow startup + error spam).

**Fix:** Force software rendering for GPU-using apps by prefixing the launch command:
```
env LIBGL_ALWAYS_SOFTWARE=1 GALLIUM_DRIVER=llvmpipe <app>
```
This is a reusable trick for **any** GUI app that shows `libEGL` errors under WSLg
(browsers, file managers, editors, etc.).

---

## File locations

| Purpose | WSL path | Windows path |
|---|---|---|
| Sway config | `~/.config/sway/config` | `\\wsl$\Ubuntu\home\karl\.config\sway\config` |
| Waybar config | `~/.config/waybar/config` | `\\wsl$\Ubuntu\home\karl\.config\waybar\config` |
| Waybar style | `~/.config/waybar/style.css` | `\\wsl$\Ubuntu\home\karl\.config\waybar\style.css` |
| Original default backup | `~/.config/sway/config.bak` | — |
| This backup/reference | — | `D:\Learning\Wayland\Config\` |

> On Windows 11 you may also use `\\wsl.localhost\Ubuntu\...` instead of `\\wsl$\Ubuntu\...`.

---

## Everyday workflow

1. **Launch:** open Ubuntu terminal, run `sway`.
2. **Focus:** click the Sway window so it receives the keyboard (WSLg quirk).
3. **Edit config:** from Windows at `\\wsl$\Ubuntu\home\karl\.config\sway\config`.
4. **Apply changes:** press `Alt+Shift+C` to reload.
   - Exception: `xwayland disable` and the bar command need a full restart
     (`Alt+Shift+E` to exit, then `sway` again).

---

## Keybinding reference (`$mod` = `Alt`)

| Shortcut | Action |
|---|---|
| `Alt+Enter` | Open terminal (foot) |
| `Alt+d` | App launcher (wmenu) |
| `Alt+c` | Open GNOME Clocks (software-rendered) |
| `Alt+Shift+Q` | Close focused window |
| `Alt+h/j/k/l` or arrows | Move focus between windows |
| `Alt+Shift+h/j/k/l` | Move a window |
| `Alt+1`–`Alt+0` | Switch to workspace 1–10 |
| `Alt+Shift+1`–`5` | Move window to workspace 1–5 |
| `Alt+b` / `Alt+v` | Split horizontal / vertical |
| `Alt+s` / `Alt+w` / `Alt+e` | Layout: stacking / tabbed / toggle-split |
| `Alt+f` | Fullscreen toggle |
| `Alt+Shift+Space` | Toggle floating |
| `Alt+Space` | Focus between tiling/floating |
| `Alt+a` | Focus parent container |
| `Alt+Shift+minus` | Move window to scratchpad |
| `Alt+minus` | Show/hide scratchpad |
| `Alt+r` | Resize mode (arrows to resize, `Esc`/`Enter` to exit) |
| `Print` | Screenshot to `~/screenshot.png` (via grim) |
| `Alt+Shift+C` | Reload config |
| `Alt+Shift+E` | Exit Sway (with confirmation) |

---

## Appearance

- **Background:** solid blue `#1e66f5` (`output * bg #1e66f5 solid_color`)
- **Gaps:** 8px inner, 4px outer
- **Borders:** 2px
- **Waybar:** dark bar, blue bottom border; left = workspaces + mode,
  center = window title, right = CPU %, RAM %, clock (date + time).

---

## Notes / harmless messages

These appear at startup and are safe to ignore under WSLg:

- `Environment variable $XDG_CURRENT_DESKTOP not set, ignoring.`
- `Found config * for output WL-1` (means the output/background line applied)
- `compositor does not implement the XDG toplevel icon protocol` (from foot; icons
  aren't supported)
- waybar: `Unable to receive desktop appearance: ...portal.Desktop was not provided`
  (no desktop portal in WSL; the CSS colors are used directly)
- gnome-clocks: `Failed to connect to GeoClue2 service: Timeout` (no location services
  in WSL; world-clock auto-location unavailable, manual city entry still works)

---

## Possible next steps

- Replace the solid background with a wallpaper image (`swaybg` + an image file).
- Add Font Awesome icons to waybar (`sudo apt install -y fonts-font-awesome`).
- Autostart apps on Sway launch (`exec` / `exec_always` lines in the config).
- Add more app keybindings (browser, file manager) using the software-render prefix.

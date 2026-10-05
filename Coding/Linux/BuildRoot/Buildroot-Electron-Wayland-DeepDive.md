# Deep Dive: Building a Buildroot Image with Wayland/Sway + Node.js + Electron for WSL2 and Docker

**Date:** 2026-10-05
**Goal:** Produce a single Buildroot-generated root filesystem containing a Wayland + Sway
graphics stack (software-rendered), Node.js, and a prebuilt Electron runtime, plus a minimal
Electron "Hello World" that proves the graphics pipeline — usable as **both** a WSL2 distro
**and** a Docker image.

**Outcome:** ✅ Fully achieved and verified. The same `rootfs.tar` renders an Electron window
through Chromium → software GL (llvmpipe) → Wayland → Sway (headless) in both WSL2 and Docker,
confirmed by captured PNG screenshots (including full-color emoji after a final enhancement).

---

## 1. Executive summary

| Item | Result |
|---|---|
| Build host | Existing **Ubuntu 26.04** WSL2 distro (20 cores, 31 GB RAM) |
| Buildroot | **LTS 2025.02.x** |
| Target arch / libc | **x86_64 / glibc** (required for Electron prebuilts) |
| Init system | **systemd** (Buildroot's `sway` depends on sd-bus) |
| Graphics | **Mesa llvmpipe** software GL + **Sway** headless (`WLR_BACKENDS=headless`, `WLR_RENDERER=pixman`) |
| Node.js | **22.23.2** (Buildroot package) |
| Electron | **33.2.1** prebuilt, fetched by host npm at build time, baked into `/opt/electron-hello` |
| Verification | Electron `webContents.capturePage()` → PNG; non-blank check = PASS |
| WSL2 result | `RESULT: PASS`, ~117–120 KB rendered PNG |
| Docker result | `RESULT: PASS`, ~300 KB rendered PNG |
| Emoji | **Noto Color Emoji** added via overlay + fontconfig; 🚀 renders in color |
| Final `rootfs.tar` | ~642 MB (`.tar.gz` ~222 MB); Docker image ~610 MB |

---

## 2. Architecture and the reasoning behind each decision

### 2.1 One rootfs, two delivery targets
Buildroot's `BR2_TARGET_ROOTFS_TAR` produces a plain root filesystem tarball. That single
artifact serves both consumers:
- **WSL2:** `wsl --import <name> <dir> rootfs.tar --version 2`
- **Docker:** `FROM scratch` + `ADD rootfs.tar /` (ADD auto-extracts a local tar)

This avoids maintaining two separate image definitions and guarantees bit-for-bit parity
between the WSL and Docker environments.

### 2.2 Why glibc (not musl)
Electron ships **prebuilt** binaries linked against glibc and a specific set of shared
libraries. A musl/uClibc toolchain would not run them. Hence
`BR2_TOOLCHAIN_BUILDROOT_GLIBC=y` and `BR2_x86_64=y`.

### 2.3 Why systemd init
Buildroot's `sway` package declares `depends on BR2_PACKAGE_SYSTEMD` because it uses the
sd-bus provider. Selecting Sway therefore forces `BR2_INIT_SYSTEMD=y`. Importantly, the
runtime launcher does **not** require systemd to be PID 1 — it starts Sway and a session
D-Bus itself — so the image still works when launched via `wsl -d ... -- bash -c '...'`
or as a Docker `CMD`.

### 2.4 Why software rendering + headless Sway
Neither headless WSL2 nor a plain Docker container exposes a GPU/DRM device. The robust,
deterministic choice is pure software:
- Mesa **gallium swrast / llvmpipe**: `BR2_PACKAGE_MESA3D_GALLIUM_DRIVER_SWRAST`,
  `BR2_PACKAGE_MESA3D_LLVM`, `..._OPENGL_EGL`, `..._OPENGL_ES`, `..._GBM`.
- Sway headless: `WLR_BACKENDS=headless`, `WLR_RENDERER=pixman`,
  `WLR_RENDERER_ALLOW_SOFTWARE=1`, `LIBGL_ALWAYS_SOFTWARE=1`, `GALLIUM_DRIVER=llvmpipe`.

This behaves identically in WSL2 and Docker and needs no `/dev/dri`.

### 2.5 Why verify with Electron's own `capturePage()`
The usual Wayland screenshot tool `grim` is **not packaged** in Buildroot. Rather than add a
custom screencopy tool, the app itself calls `webContents.capturePage()` and writes a PNG.
This is a *stronger* proof than an external screenshot: it confirms the entire
Chromium → GL → Wayland path produced real pixels inside Electron. A size threshold (>3 KB)
distinguishes a rendered gradient from a blank frame.

### 2.6 How Electron gets into the rootfs
The custom Buildroot package `electron-hello` uses the **host** `npm` during the build to
`npm install` Electron into the app's `node_modules`, then installs the whole tree to
`/opt/electron-hello` on the target. Because the build host and the target are **both
x86_64/glibc**, the Electron binary npm downloads for the host is ABI-correct for the target.
The result is an offline-capable image with Electron pre-baked.

---

## 3. Project layout (the BR2_EXTERNAL tree)

```
~/br-electron/
├── buildroot/                      # Buildroot LTS 2025.02.x (git clone)
└── br_electron_ext/                # BR2_EXTERNAL tree (our code)
    ├── external.desc               # name: ELECTRON
    ├── external.mk                 # includes package/*/*.mk
    ├── Config.in                   # sources the electron-hello menu
    ├── README.md                   # full step-by-step guide
    ├── configs/
    │   └── electron_wayland_defconfig
    ├── package/
    │   └── electron-hello/
    │       ├── Config.in
    │       ├── electron-hello.mk   # generic-package; host npm install
    │       └── app/
    │           ├── main.js         # creates window, capturePage() -> PNG
    │           ├── index.html      # gradient UI + 🚀 + version line
    │           └── package.json    # pins electron 33.2.1
    └── board/electron/
        ├── post-build.sh           # perms, /tmp sticky bit, motd
        └── rootfs_overlay/
            ├── etc/sway/config                       # headless output
            ├── etc/fonts/conf.d/75-noto-color-emoji.conf
            ├── usr/bin/run-electron.sh               # launch + verify
            └── usr/share/fonts/noto/NotoColorEmoji.ttf
```

**Windows staging copy** (where the files were authored and the tar/Docker artifacts live):
`D:\Users\BKU\karlschmitt\br-electron-staging\` (mounted as `/mnt/d/...` in WSL).

---

## 4. The defconfig (key selections)

```ini
# Arch + toolchain
BR2_x86_64=y
BR2_x86_corei7=y
BR2_TOOLCHAIN_BUILDROOT_GLIBC=y
BR2_TOOLCHAIN_BUILDROOT_CXX=y

# Init
BR2_INIT_SYSTEMD=y
BR2_PACKAGE_SYSTEMD=y
BR2_ROOTFS_MERGED_USR=y

# Node.js
BR2_PACKAGE_NODEJS=y
BR2_PACKAGE_NODEJS_NPM=y

# Software OpenGL (llvmpipe)
BR2_PACKAGE_MESA3D=y
BR2_PACKAGE_MESA3D_LLVM=y
BR2_PACKAGE_MESA3D_GALLIUM_DRIVER_SWRAST=y
BR2_PACKAGE_MESA3D_OPENGL_EGL=y
BR2_PACKAGE_MESA3D_OPENGL_ES=y
BR2_PACKAGE_MESA3D_GBM=y
BR2_PACKAGE_MESA3D_OSMESA_GALLIUM=y

# Wayland + Sway
BR2_PACKAGE_WAYLAND=y
BR2_PACKAGE_WAYLAND_PROTOCOLS=y
BR2_PACKAGE_LIBXKBCOMMON=y
BR2_PACKAGE_WLROOTS=y
BR2_PACKAGE_WLROOTS_XWAYLAND=y
BR2_PACKAGE_SWAY=y
BR2_PACKAGE_FOOT=y

# Electron/Chromium runtime deps
BR2_PACKAGE_LIBGTK3=y            # NB: package is 'libgtk3', not 'gtk3'
BR2_PACKAGE_LIBGTK3_WAYLAND=y
BR2_PACKAGE_LIBGTK3_X11=y
BR2_PACKAGE_LIBNSS=y             # NB: package is 'libnss', not 'nss'
BR2_PACKAGE_AT_SPI2_CORE=y
BR2_PACKAGE_CUPS=y              # provides libcups.so.2 (Electron links it)
BR2_PACKAGE_DBUS=y
# + cairo, pango, harfbuzz, expat, libpng/jpeg, fontconfig, dejavu, liberation,
#   and the X client libs (libX11, libXext, libXrandr, libXcomposite, ...)

# Our app
BR2_PACKAGE_ELECTRON_HELLO=y

# Output + overlay + post-build
BR2_TARGET_ROOTFS_TAR=y
BR2_TARGET_ROOTFS_TAR_GZIP=y
BR2_ROOTFS_OVERLAY="$(BR2_EXTERNAL_ELECTRON_PATH)/board/electron/rootfs_overlay"
BR2_ROOTFS_POST_BUILD_SCRIPT="$(BR2_EXTERNAL_ELECTRON_PATH)/board/electron/post-build.sh"
```

**Package-name gotchas discovered by grepping the Buildroot tree:**
- GTK3 → `libgtk3` (`BR2_PACKAGE_LIBGTK3`)
- NSS → `libnss` (`BR2_PACKAGE_LIBNSS`)
- `grim` → **not packaged** (drove the capturePage verification design)
- `libcups` → required by the Electron binary even if printing is never used

---

## 5. The Electron app and verification flow

`main.js` (essentials):
```js
const { app, BrowserWindow } = require('electron');
// ...
win.webContents.on('did-finish-load', async () => {
  setTimeout(async () => {
    const image = await win.webContents.capturePage();
    fs.writeFileSync(process.env.SHOT_PATH || '/tmp/electron-shot.png', image.toPNG());
    if (process.env.ELECTRON_VERIFY === '1') app.quit();
  }, 1500);
});
```

`run-electron.sh verify` sequence:
1. Prepare runtime: `XDG_RUNTIME_DIR`, machine-id (`dbus-uuidgen`), `chmod 1777 /tmp/.X11-unix`.
2. Export software-GL + headless env vars.
3. Launch a session D-Bus (`dbus-launch`).
4. Start **Sway** headless; wait for the `wayland-*` socket; export `WAYLAND_DISPLAY`.
5. Run **Electron** with `--no-sandbox --disable-gpu --ozone-platform=wayland
   --enable-features=UseOzonePlatform`.
6. Check the PNG exists and is > 3 KB → print `RESULT: PASS`.

---

## 6. Delivery

### 6.1 WSL2
```powershell
wsl --import ElectronBR "$env:USERPROFILE\ElectronBR" `
    "D:\Users\BKU\karlschmitt\br-electron-staging\rootfs.tar" --version 2
wsl -d ElectronBR -- bash -c "run-electron verify"
```

### 6.2 Docker
```dockerfile
FROM scratch
ADD rootfs.tar /
ENV XDG_RUNTIME_DIR=/tmp/xdg LIBGL_ALWAYS_SOFTWARE=1 GALLIUM_DRIVER=llvmpipe \
    WLR_RENDERER=pixman WLR_BACKENDS=headless \
    WLR_LIBINPUT_NO_DEVICES=1 WLR_RENDERER_ALLOW_SOFTWARE=1
CMD ["/usr/bin/run-electron.sh", "verify"]
```
```powershell
docker build -t electron-br:latest .
docker run --rm electron-br:latest        # -> RESULT: PASS
```

---

## 7. Problems encountered and how they were solved

This is the part most likely to save future time. Each item was diagnosed from real tool
output, not assumed.

### 7.1 PowerShell → wsl → bash variable stripping
**Symptom:** Inline `wsl -d Ubuntu -- bash -c '... $var ...'` silently lost shell variables
(e.g. a tool-detection loop printed empty names), and pipes like `| tail` were intercepted by
PowerShell.
**Root cause:** Multiple layers of quoting between PowerShell, `wsl.exe`, and bash.
**Fix (adopted as a standing pattern):** author bash scripts as files in the `/mnt/d` staging
dir and execute them with `wsl -d <distro> -- bash "/mnt/d/.../script.sh"`, redirecting output
to a log file inside WSL and reading it back. No inline variable expansion through PowerShell.

### 7.2 Buildroot refuses a PATH containing spaces
**Symptom:** `Your PATH contains spaces, TABs, and/or newline (\n) characters. This doesn't
work.` immediately at the dependency check.
**Root cause:** WSL appends the **Windows PATH** (`C:\Program Files\...`) to the Linux PATH.
**Fix:** export a clean Linux-only PATH in every build script:
`PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"`. (Alternative:
`/etc/wsl.conf` → `[interop] appendWindowsPath=false` + `wsl --shutdown`.)

### 7.3 Ubuntu 26.04 `uutils` coreutils break Buildroot
**Symptom:** `You have an uutils 'install' version installed which is affected by
https://github.com/uutils/coreutils/issues/12166`.
**Root cause:** Ubuntu now defaults `/usr/bin/install` to the Rust uutils implementation.
**Fix:**
```bash
sudo update-alternatives --install /usr/bin/install install /usr/bin/gnuinstall 100
sudo update-alternatives --set install /usr/bin/gnuinstall   # GNU coreutils 9.7
```

### 7.4 Download failures: IPv6-only mirror + corporate VPN proxy
**Symptom:** During the build, `host-patchelf` download failed with `Connection timed out`
on IPv4 and `Network is unreachable` on IPv6. Later, raw TCP/443 was fully blocked.
**Root causes (two, in sequence):**
1. `sources.buildroot.net` sometimes resolves **IPv6-only**, but WSL2 had no IPv6 route.
2. The machine was on a **corporate VPN** (`*.db.de`) whose proxy
   (`WSL_PAC_URL=https://wwwproxy.tech.db.de/PAC/Internet.pac`) blocked direct outbound 443.
   (Earlier packages had downloaded before the network changed over a weekend suspend/resume.)
**Fixes:**
- Forced IPv4 in `~/.wgetrc` (`inet4_only = on`, `prefer-family = IPv4`) plus retries/timeouts.
- Pre-fetched the blocked tarball from upstream GitHub into Buildroot's `dl/patchelf/` and
  verified its sha256 against `package/patchelf/patchelf.hash`.
- The user **left the VPN**, restoring direct internet; the build was then resumed
  (Buildroot resumes from the last completed step) and completed.

### 7.5 Electron shared-library closure — one missing lib
**Method:** `readelf -d` on the Electron binary to list `DT_NEEDED`, then checked each against
the target rootfs (`/lib`, `/usr/lib`, and Electron's bundled `dist/`).
**Result:** 34/35 satisfied; the single gap was **`libcups.so.2`**.
**Fix:** add `BR2_PACKAGE_CUPS=y`, incremental rebuild → **0 missing**.

### 7.6 Harmless runtime warnings (hardened for clean output)
- `sticky bit not set on /tmp/.X11-unix` / `Failed to start Xwayland` — Electron used native
  Wayland anyway; launcher now `chmod 1777 /tmp/.X11-unix`.
- Empty `/etc/machine-id` — launcher now runs `dbus-uuidgen`.
- `Failed to connect to .../system_bus_socket` — harmless; Electron renders without the
  system bus (a session bus from `dbus-launch` is provided).

### 7.7 Noto Color Emoji sourcing (Git-LFS trap)
**Symptom:** `🚀` rendered as a missing-glyph box; the GitHub `raw`/`.../raw/main` URLs
returned a 14-byte LFS pointer or an HTML page, not a TTF.
**Root cause:** the font is stored via **Git LFS** in the upstream repo.
**Fix:** obtained the real `NotoColorEmoji.ttf` (v2.051, 11 MB, TrueType with CBDT color
tables) from the Ubuntu `fonts-noto-color-emoji` package via `apt-get download` +
`dpkg-deb -x`, placed it in the overlay, and added a fontconfig fallback
(`/etc/fonts/conf.d/75-noto-color-emoji.conf`) preferring "Noto Color Emoji" for the
`emoji`/`sans-serif`/`serif`/`monospace` families. Verified with `fc-match emoji`.

---

## 8. Verification evidence

| Target | Command | Result | PNG size | Visual |
|---|---|---|---|---|
| WSL2 (initial) | `run-electron verify` | `RESULT: PASS` | 117,568 B | Gradient card + text ✓ (🚀 as box) |
| Docker (initial) | `docker run --rm electron-br:latest` | `RESULT: PASS` | 300,038 B | Gradient card + text ✓ |
| WSL2 (with emoji) | `run-electron verify` | `RESULT: PASS` | 119,527 B | 🚀 full-color emoji ✓ |
| Docker (with emoji) | `docker run --rm electron-br:latest` | `RESULT: PASS` | 301,354 B | ✓ |

`fc-match emoji` inside the image → `NotoColorEmoji.ttf: "Noto Color Emoji" "Regular"`.
Electron library closure → **0 missing** of 35 `DT_NEEDED` entries.

---

## 9. Build commands (clean replay)

```bash
# Host prep (Ubuntu build host)
sudo apt-get update
sudo apt-get install -y build-essential gcc g++ make cpio unzip rsync bc file wget git \
  libncurses-dev python3 python3-dev perl patch sed binutils bzip2 gzip tar xz-utils \
  ca-certificates graphviz
sudo update-alternatives --install /usr/bin/install install /usr/bin/gnuinstall 100
sudo update-alternatives --set install /usr/bin/gnuinstall

# Get Buildroot
mkdir -p ~/br-electron && cd ~/br-electron
git clone --depth 1 --branch 2025.02.x https://gitlab.com/buildroot.org/buildroot.git buildroot

# (copy br_electron_ext tree into ~/br-electron/, strip CRLF, chmod scripts)

# Build (clean PATH + IPv4 wget)
cd ~/br-electron/buildroot
export PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
printf 'inet4_only = on\nprefer-family = IPv4\ntries = 10\ntimeout = 30\nretry_connrefused = on\n' > ~/.wgetrc
make BR2_EXTERNAL=~/br-electron/br_electron_ext electron_wayland_defconfig
make BR2_EXTERNAL=~/br-electron/br_electron_ext -j"$(nproc)"
# -> output/images/rootfs.tar (+ .gz)
```

---

## 10. Key artifacts and locations

| Artifact | Location |
|---|---|
| Buildroot source | `~/br-electron/buildroot` (in the Ubuntu WSL distro) |
| External tree (config, package, overlay, README) | `~/br-electron/br_electron_ext` |
| `rootfs.tar` / `rootfs.tar.gz` | `~/br-electron/buildroot/output/images/` |
| Windows staging (source + scripts + tar + Dockerfile + screenshots) | `D:\Users\BKU\karlschmitt\br-electron-staging\` |
| WSL2 distro | `ElectronBR` (installed at `%USERPROFILE%\ElectronBR`) |
| Docker image | `electron-br:latest` (~610 MB) |
| Proof screenshots | `electron-shot.png` (WSL), `electron-shot-docker.png` (Docker), `electron-shot-emoji.png` (emoji) |

---

## 11. Possible next steps

- **Interactive GUI on the Windows desktop** via WSLg (nested Sway or Electron directly on
  WSLg's Wayland socket) instead of headless capture.
- **Shrink the image** (strip docs/locales, drop XWayland if native Wayland suffices,
  consider BR2 size-optimisation and removing debug tools).
- **Package the Electron app** as a proper Buildroot package tarball instead of a `local`
  site, and pin the Electron download via a hash for fully offline reproducible builds.
- **CI integration**: run `docker run --rm electron-br:latest` as a pipeline gate that fails
  the build if `RESULT: PASS` is not emitted.
- **Color-emoji font subset** to reclaim most of the ~11 MB if image size matters.

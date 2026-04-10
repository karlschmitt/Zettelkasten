# 20260409171034 Decrease size of an image

To **decrease the size of a PNG** with ImageMagick on Windows, you have a few good options depending on what you mean by “size”:

***

# 🧭 1. Reduce dimensions (biggest impact)

This is the most effective way.

```powershell
magick input.png -resize 50% output.png
```

Or set an exact size:

```powershell
magick input.png -resize 800x600 output.png
```

👉 Keeps aspect ratio automatically unless forced.

***

# 🎨 2. Reduce color depth (great for PNGs)

PNG size heavily depends on number of colors:

```powershell
magick input.png -colors 256 output.png
```

Even smaller:

```powershell
magick input.png -colors 64 output.png
```

👉 Ideal for icons, diagrams, UI graphics.

***

# 🗜️ 3. Optimize compression

PNG is lossless, but compression can still be improved:

```powershell
magick input.png -strip -define png:compression-level=9 output.png
```

* `-strip` → removes metadata (often surprisingly large)

* compression level: 0–9 (9 = smallest, slower)

***

# ⚡ 4. Combine best options (recommended)

This is usually what you want:

```powershell
magick input.png -resize 50% -colors 256 -strip -define png:compression-level=9 output.png
```

***

# 📂 5. Batch process all PNGs in a folder

```powershell
magick mogrify -resize 50% -colors 256 -strip -define png:compression-level=9 *.png
```

⚠️ This **overwrites** originals\
👉 Safer version:

```powershell
magick mogrify -path output -resize 50% -colors 256 -strip -define png:compression-level=9 *.png
```

***

# 🧠 Quick guideline

* Photos → resizing helps most

* Icons/UI → reduce colors

* Always → use `-strip`

***

If you want, I can tailor a **perfect command for your use case** (e.g., Zettelkasten images, web performance, or lossless-only optimization).



# 20260410225615 Import an image

In Krita, when you import an image, it usually creates its own **new layer** rather than "filling" an empty layer you have already created. 

Here are the three best ways to get your PNG into your project:

### Method 1: The "Layer" Menu (Recommended)
This is the standard way to bring an image in as a layer.
1. Go to the top menu and select **Layer**.
2. Hover over **Import/Export**.
3. Click **Import Layer...**
4. Select your PNG file and click **Open**.
5. Krita will create a **new layer** containing your PNG. You can then delete the empty layer you created previously if you no longer need it.

---

### Method 2: Drag and Drop (Fastest)
1. Open your computer's file folder where the PNG is located.
2. Drag the PNG file directly onto the Krita canvas.
3. A small menu will pop up. Select **Insert as New Layer**.

---

### Method 3: Copy and Paste
If you have the PNG open in another program (like a web browser or image viewer):
1. Right-click the image and select **Copy**.
2. Go to Krita and press **Ctrl + V** (Paste).
3. This will create a new "Paste Layer."

---

### Important: How to Resize or Move the PNG
Once the PNG is imported, it might be too big or in the wrong spot. To fix this:
1. Make sure the PNG layer is selected in your Layers Docker (usually on the right).
2. Press **Ctrl + T** (the Transform Tool).
3. Use the handles on the corners of the image to resize it.
4. Click and drag the image to move it.
5. Press **Enter** to apply the changes.

### "I really want it on my specific empty layer!"
Krita doesn't "fill" an existing empty layer with an imported file. If you want the PNG content to be on one of the specific layers you already created:
1. Import the PNG using Method 1 or 2 (it will show up as a new layer).
2. Make sure the PNG layer is **directly above** your empty layer.
3. Select the PNG layer.
4. Press **Ctrl + E** (Merge Down). This merges the PNG into the empty layer below it.
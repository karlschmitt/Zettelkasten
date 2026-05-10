---
id: 20260510191359
title: How to make the background tranceparent?
author: Karl Schmitt
date: 2026-05-10
keywords: []
---

# How to make the background transparent?

To make a background transparent in GIMP, you need to ensure your image has an **Alpha Channel** (which handles transparency) and then select and delete the background.

Here are the three most common ways to do it, depending on your image.

---

### Step 0: The Most Important Step
Before doing anything, you must tell GIMP to allow transparency:
1. Look at the **Layers** dialog on the right.
2. **Right-click** your current layer.
3. Select **Add Alpha Channel**. (If it’s greyed out, your image already has one).

---

### Method 1: The "Fuzzy Select" Tool (Best for solid colors)
Use this if your background is a single color (like a white or blue studio backdrop).

1. Select the **Fuzzy Select Tool** (the magic wand icon) from the Toolbox.
2. Click on the background color you want to remove.
3. If it didn't select enough (or selected too much), click and drag your mouse left or right to adjust the **Threshold**.
4. Press **Delete** on your keyboard.
5. Go to **Select > None** to see your result.

---

### Method 2: "Color to Alpha" (Best for white/black backgrounds)
This is the cleanest way to remove a solid color background while keeping the edges smooth.

1. Go to the top menu: **Colors > Color to Alpha...**
2. Click the color picker (usually defaults to white). 
3. Select the background color of your image.
4. Click **OK**. The background will instantly become transparent.

---

### Method 3: The "Paths Tool" (Best for complex/busy backgrounds)
If your background is messy (like a street or a park), you have to manually cut out the object.

1. Select the **Paths Tool** (fountain pen icon) or press `B`.
2. Click points around the object you want to **keep**. Click and drag to create curves.
3. Once you've gone all the way around, hold `Ctrl` and click the very first point you made to close the loop.
4. In the Tool Options (usually on the left), click **Selection from Path**.
5. Go to **Select > Invert** (this selects the background instead of the object).
6. Press **Delete**.

---

### Step 4: Saving the Result (Crucial!)
You cannot save a transparent image as a JPEG because JPEGs do not support transparency (they will turn the background back to white or black).

1. Go to **File > Export As...**
2. Give your file a name and end it with **.png** (e.g., `my_image.png`).
3. Click **Export**.
4. In the settings window that pops up, make sure **"Save gamma"** and **"Save color values from transparent pixels"** are checked.
5. Click **Export** again.

### Pro Tip for smooth edges:
After making a selection (before you hit delete), go to **Select > Feather...** and enter a small amount (like 2 or 3 pixels). This prevents the edges from looking "jagged" or "crunchy."

---

Kein Problem! Hier sind die gleichen Schritte mit den deutschen Begriffen, damit du dich in deinem GIMP zurechtfindest.

### Schritt 0: Der wichtigste Schritt (Alphakanal)
Bevor du Transparenz hinzufügen kannst, muss die Ebene das unterstützen.
1. Schau rechts in den **Ebenen-Dialog** (Layers).
2. Klicke mit der **rechten Maustaste** auf deine aktuelle Ebene.
3. Wähle **„Alphakanal hinzufügen“**. (Wenn es ausgegraut ist, hat das Bild schon einen).

---

### Methode 1: Der „Zauberstab“ (Für einfarbige Hintergründe)
1. Wähle den **Zauberstab** (Fuzzy Select) aus dem Werkzeugkasten (Symbol sieht aus wie ein Zauberstab).
2. Klicke auf die Hintergrundfarbe, die weg soll.
3. In den Werkzeugeinstellungen (meist links) kannst du den **„Schwellwert“** (Threshold) anpassen, um mehr oder weniger Details zu erfassen.
4. Drücke die **Entf-Taste** (Delete) auf deiner Tastatur.
5. Gehe oben auf **Auswahl > Nichts**.

---

### Methode 2: „Farbe zu Alpha“ (Der sauberste Weg)
Ideal, wenn der Hintergrund komplett weiß oder schwarz ist.
1. Gehe im Menü oben auf **Farben > Farbe zu Alpha...**
2. In dem Fenster klickst du auf den Farbbalken (meist steht dort Weiß).
3. Wähle die Farbe deines Hintergrunds.
4. Klicke auf **OK**. Der Hintergrund wird sofort transparent.

---

### Methode 3: Das „Pfad-Werkzeug“ (Für komplexe Fotos)
Wenn der Hintergrund unruhig ist (z. B. eine Landschaft).
1. Wähle das **Pfad-Werkzeug** (Symbol sieht aus wie eine Füllfeder) oder drücke die Taste `B`.
2. Klicke Punkte um das Objekt, das du **behalten** willst.
3. Schließe den Kreis, indem du `Strg` gedrückt hältst und auf den ersten Punkt klickst.
4. Klicke in den Werkzeugeinstellungen auf den Button **„Auswahl aus Pfad“**.
5. Gehe oben auf **Auswahl > Invertieren** (damit wählst du den Hintergrund aus, nicht das Objekt).
6. Drücke die **Entf-Taste**.

---

### Schritt 4: Richtig speichern (Ganz wichtig!)
JPEGs können keine Transparenz speichern (sie machen den Hintergrund wieder weiß).
1. Gehe auf **Datei > Exportieren als...**
2. Gib der Datei einen Namen, der auf **.png** endet (z. B. `bild.png`).
3. Klicke auf **Exportieren**.
4. Im nächsten Fenster klickst du einfach nochmal auf **Exportieren**.

---

**Tipp für weiche Kanten:**
Bevor du „Entf“ drückst, kannst du auf **Auswahl > Ausblenden...** gehen und einen Wert von ca. 2 bis 3 Pixeln eingeben. Das verhindert, dass die Ränder „treppig“ oder hart aussehen.

**Zusatz-Tipp:** Falls du GIMP doch lieber auf **Englisch** hättest, kannst du das hier ändern:
*Bearbeiten > Einstellungen > Oberfläche > Sprache.*
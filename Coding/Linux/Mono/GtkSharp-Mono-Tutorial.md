# Building Desktop GUIs with Gtk# on Mono — A Practical Tutorial

This tutorial teaches you how to build **cross-platform desktop applications** with **Gtk#** (pronounced "GTK sharp"), the C# binding for the **GTK** toolkit, running on **Mono**. GTK is the same widget toolkit behind GNOME, GIMP, and many Linux desktop apps.

It fits into the *C# with Mono* series: bring the language skills from the [Beginner](./CSharp-Mono-Beginner-Tutorial.md), [Intermediate/OOP](./CSharp-Mono-Intermediate-OOP-Tutorial.md), and [Advanced](./CSharp-Mono-Advanced-Tutorial.md) tutorials into a real windowed application. It also connects to the graphics tutorials — Gtk# uses **Cairo** for custom drawing, and you can host [GDI+](./GDIPlus-Mono-Tutorial.md) or [SkiaSharp](./SkiaSharp-Tutorial.md) output inside a widget.

> **A note on versions.** There are two generations of Gtk#:
> - **Gtk# 2.x** (GTK 2) — the classic, most widely documented version on Mono. This tutorial targets it because it's the smoothest "install Mono, compile with `mcs`" experience.
> - **Gtk# 3 / GtkSharp (GTK 3+)** — newer, distributed as NuGet packages for modern .NET. A short section covers the differences.
>
> The concepts (windows, widgets, containers, signals) are the same across both.

---

## Table of Contents

1. [What Is Gtk#?](#1-what-is-gtk)
2. [Installing Gtk# on Mono](#2-installing-gtk-on-mono)
3. [Your First Window](#3-your-first-window)
4. [Understanding the Main Loop and Signals](#4-understanding-the-main-loop-and-signals)
5. [Core Widgets](#5-core-widgets)
6. [Layout with Containers](#6-layout-with-containers)
7. [A Working Example: A Simple Form](#7-a-working-example-a-simple-form)
8. [Menus, Toolbars, and Dialogs](#8-menus-toolbars-and-dialogs)
9. [Custom Drawing with Cairo](#9-custom-drawing-with-cairo)
10. [A Complete App: Notes Editor](#10-a-complete-app-notes-editor)
11. [Designing UIs Visually with Glade](#11-designing-uis-visually-with-glade)
12. [Gtk# 3 / Modern .NET](#12-gtk-3--modern-net)
13. [Troubleshooting](#13-troubleshooting)
14. [Where to Go Next](#14-where-to-go-next)

---

## 1. What Is Gtk#?

Gtk# is a set of .NET bindings that let you use the native **GTK** widget toolkit from C#. You write C#, and GTK draws real, native-feeling windows, buttons, text boxes, menus, and dialogs.

- **Cross-platform:** the same code runs on Linux, macOS, and Windows.
- **Event-driven:** you build a UI, then respond to *signals* (events) like button clicks.
- **Widget-based:** everything on screen is a **widget** — windows, buttons, labels, layout containers.

---

## 2. Installing Gtk# on Mono

### Linux (Debian / Ubuntu)

```bash
sudo apt update
sudo apt install mono-complete gtk-sharp2
```

### Linux (Fedora)

```bash
sudo dnf install mono-complete gtk-sharp2
```

### macOS

Install Mono (which bundles Gtk# on the classic MDK), then GTK via Homebrew if needed:

```bash
brew install mono
brew install gtk+   # native GTK libraries
```

### Windows

Install the Mono MDK from the [official download page](https://www.mono-project.com/download/stable/); it includes Gtk#. Alternatively use the modern GtkSharp NuGet packages (see [section 12](#12-gtk-3--modern-net)).

### Verify

The Gtk# assemblies register with the compiler under package names. Confirm they're visible:

```bash
pkg-config --list-all | grep gtk-sharp
```

You should see entries like `gtk-sharp-2.0`. This is the name you'll pass to the compiler with `-pkg:`.

---

## 3. Your First Window

Create `Hello.cs`:

```csharp
using System;
using Gtk;

class HelloWorld
{
    static void Main()
    {
        // Initialize GTK.
        Application.Init();

        // Create a top-level window.
        Window window = new Window("Hello Gtk#");
        window.SetDefaultSize(300, 200);
        window.SetPosition(WindowPosition.Center);

        // Add a label inside it.
        Label label = new Label("Hello, Gtk# on Mono!");
        window.Add(label);

        // Handle the window's close button so the app can quit.
        window.DeleteEvent += (o, args) => Application.Quit();

        // Show every widget in the window.
        window.ShowAll();

        // Enter the GTK main loop (blocks until Application.Quit()).
        Application.Run();
    }
}
```

### Compile and run

The `-pkg:gtk-sharp-2.0` flag tells the compiler to reference the Gtk# assemblies:

```bash
mcs Hello.cs -pkg:gtk-sharp-2.0
mono Hello.exe
```

A centered 300×200 window titled "Hello Gtk#" appears with your greeting. Closing it quits the program.

---

## 4. Understanding the Main Loop and Signals

Every GTK app follows the same lifecycle:

1. **`Application.Init()`** — start up GTK.
2. **Build the UI** — create widgets, arrange them, connect signal handlers.
3. **`window.ShowAll()`** — make widgets visible.
4. **`Application.Run()`** — enter the *main loop*, which waits for events and dispatches them.
5. **`Application.Quit()`** — leave the loop and end the program.

### Signals = events

GTK widgets emit **signals** when things happen. In Gtk# these are exposed as C# **events** you subscribe to with `+=`.

```csharp
Button button = new Button("Click me");

// Subscribe to the "clicked" signal.
button.Clicked += (sender, e) =>
{
    Console.WriteLine("Button was clicked!");
};
```

Common signals: `Clicked` (buttons), `Changed` (entries), `Toggled` (checkboxes), `DeleteEvent` (window close), `Destroyed`.

> Because the main loop blocks on `Application.Run()`, long operations in a signal handler freeze the UI. For slow work, use async/await or a background thread and marshal results back with `Application.Invoke(...)`.

---

## 5. Core Widgets

```csharp
// Label — static text
Label label = new Label("Some text");

// Button — clickable
Button button = new Button("OK");
button.Clicked += (s, e) => Console.WriteLine("clicked");

// Entry — single-line text input
Entry entry = new Entry();
entry.PlaceholderText = "Type here...";
string text = entry.Text;

// CheckButton — a checkbox
CheckButton check = new CheckButton("Enable feature");
bool isChecked = check.Active;

// ComboBox — a dropdown of strings
ComboBox combo = new ComboBox(new[] { "Red", "Green", "Blue" });
combo.Active = 0;   // select the first item

// TextView — multi-line editable text
TextView textView = new TextView();
textView.Buffer.Text = "Line 1\nLine 2";

// Image — display a picture
Image image = new Image("logo.png");
```

Widgets share useful members: `Sensitive` (enabled/disabled), `Visible`, `TooltipText`, and styling via CSS providers (GTK 3).

---

## 6. Layout with Containers

GTK doesn't use absolute pixel positioning by default. Instead you nest widgets inside **container** widgets that arrange them automatically and adapt to resizing.

### VBox / HBox — stack vertically or horizontally

```csharp
// A vertical stack; homogeneous=false, spacing=6px.
VBox vbox = new VBox(false, 6);

vbox.PackStart(new Label("Name:"), false, false, 0);
vbox.PackStart(new Entry(),        false, false, 0);
vbox.PackStart(new Button("Save"), false, false, 0);

window.Add(vbox);
```

`PackStart(child, expand, fill, padding)`:
- `expand` — should the child grab extra space?
- `fill` — should it fill that space or stay its natural size?
- `padding` — pixels of space around it.

### Grid — rows and columns

```csharp
Grid grid = new Grid();
grid.RowSpacing = 6;
grid.ColumnSpacing = 6;

//        widget,            left, top, width, height
grid.Attach(new Label("User:"), 0, 0, 1, 1);
grid.Attach(new Entry(),        1, 0, 1, 1);
grid.Attach(new Label("Pass:"), 0, 1, 1, 1);
grid.Attach(new Entry(),        1, 1, 1, 1);
```

Other handy containers: `HBox`, `Frame` (a titled border), `ScrolledWindow` (adds scrollbars around a large child), and `Notebook` (tabbed pages).

---

## 7. A Working Example: A Simple Form

This app collects a name and greets the user. Save as `Form.cs`.

```csharp
using System;
using Gtk;

class FormApp
{
    static Entry _nameEntry;
    static Label _output;

    static void Main()
    {
        Application.Init();

        Window window = new Window("Greeter");
        window.SetDefaultSize(320, 160);
        window.SetPosition(WindowPosition.Center);
        window.DeleteEvent += (o, e) => Application.Quit();

        VBox vbox = new VBox(false, 8) { BorderWidth = 12 };

        vbox.PackStart(new Label("What is your name?"), false, false, 0);

        _nameEntry = new Entry { PlaceholderText = "Enter your name" };
        vbox.PackStart(_nameEntry, false, false, 0);

        Button greetButton = new Button("Greet me");
        greetButton.Clicked += OnGreetClicked;
        vbox.PackStart(greetButton, false, false, 0);

        _output = new Label("");
        vbox.PackStart(_output, false, false, 0);

        window.Add(vbox);
        window.ShowAll();
        Application.Run();
    }

    static void OnGreetClicked(object sender, EventArgs e)
    {
        string name = _nameEntry.Text.Trim();
        _output.Text = string.IsNullOrEmpty(name)
            ? "Please enter a name."
            : $"Hello, {name}! 👋";
    }
}
```

Compile and run:

```bash
mcs Form.cs -pkg:gtk-sharp-2.0
mono Form.exe
```

---

## 8. Menus, Toolbars, and Dialogs

### A menu bar

```csharp
MenuBar menuBar = new MenuBar();

Menu fileMenu = new Menu();
MenuItem fileItem = new MenuItem("File") { Submenu = fileMenu };

MenuItem openItem = new MenuItem("Open");
openItem.Activated += (s, e) => Console.WriteLine("Open clicked");
fileMenu.Append(openItem);

MenuItem quitItem = new MenuItem("Quit");
quitItem.Activated += (s, e) => Application.Quit();
fileMenu.Append(quitItem);

menuBar.Append(fileItem);
// Add menuBar to the top of a VBox that fills the window.
```

### Message dialogs

```csharp
MessageDialog dialog = new MessageDialog(
    parentWindow,
    DialogFlags.Modal,
    MessageType.Info,
    ButtonsType.OkCancel,
    "Do you want to continue?");

ResponseType response = (ResponseType)dialog.Run();
if (response == ResponseType.Ok)
    Console.WriteLine("User clicked OK");

dialog.Destroy();   // always destroy dialogs when done
```

### File chooser

```csharp
var chooser = new FileChooserDialog(
    "Open a file", parentWindow, FileChooserAction.Open,
    "Cancel", ResponseType.Cancel,
    "Open",   ResponseType.Accept);

if ((ResponseType)chooser.Run() == ResponseType.Accept)
{
    string path = chooser.Filename;
    Console.WriteLine($"Selected: {path}");
}
chooser.Destroy();
```

---

## 9. Custom Drawing with Cairo

For custom graphics (charts, diagrams, game boards), use a `DrawingArea` and draw with **Cairo**, GTK's 2D vector graphics library. This is the GTK-native counterpart to the GDI+/SkiaSharp tutorials.

### Gtk# 2 (draw in the `ExposeEvent`)

```csharp
using System;
using Gtk;
using Cairo;

class DrawingDemo
{
    static void Main()
    {
        Application.Init();
        Window window = new Window("Cairo Drawing");
        window.SetDefaultSize(400, 300);
        window.DeleteEvent += (o, e) => Application.Quit();

        DrawingArea area = new DrawingArea();
        area.ExposeEvent += OnExpose;

        window.Add(area);
        window.ShowAll();
        Application.Run();
    }

    static void OnExpose(object sender, ExposeEventArgs args)
    {
        DrawingArea area = (DrawingArea)sender;
        using (Context cr = Gdk.CairoHelper.Create(area.GdkWindow))
        {
            // Background
            cr.SetSourceRGB(1, 1, 1);
            cr.Paint();

            // A filled blue circle
            cr.SetSourceRGB(0.2, 0.4, 0.8);
            cr.Arc(200, 150, 60, 0, 2 * Math.PI);
            cr.Fill();

            // A red rectangle outline
            cr.SetSourceRGB(0.8, 0.1, 0.1);
            cr.LineWidth = 3;
            cr.Rectangle(50, 50, 120, 80);
            cr.Stroke();

            // Some text
            cr.SetSourceRGB(0, 0, 0);
            cr.SelectFontFace("Sans", FontSlant.Normal, FontWeight.Bold);
            cr.SetFontSize(18);
            cr.MoveTo(50, 260);
            cr.ShowText("Drawn with Cairo");
        }
    }
}
```

```bash
mcs DrawingDemo.cs -pkg:gtk-sharp-2.0
mono DrawingDemo.exe
```

> In **Gtk# 3** the signal is `Drawn` (not `ExposeEvent`), and the `Cairo.Context` is provided directly in `DrawnArgs.Cr` — no `CairoHelper` needed. The drawing calls (`Arc`, `Rectangle`, `Fill`, `Stroke`, `ShowText`) are identical.

---

## 10. A Complete App: Notes Editor

A small but real text editor with a menu, a scrollable text area, and open/save file dialogs. Save as `Notes.cs`.

```csharp
using System;
using System.IO;
using Gtk;

class NotesEditor
{
    static Window _window;
    static TextView _textView;
    static string _currentPath;

    static void Main()
    {
        Application.Init();

        _window = new Window("Notes Editor");
        _window.SetDefaultSize(600, 400);
        _window.SetPosition(WindowPosition.Center);
        _window.DeleteEvent += (o, e) => Application.Quit();

        // Root vertical layout: menu on top, text area filling the rest.
        VBox root = new VBox(false, 0);

        root.PackStart(BuildMenu(), false, false, 0);

        _textView = new TextView { WrapMode = WrapMode.Word };
        ScrolledWindow scroll = new ScrolledWindow();
        scroll.Add(_textView);
        root.PackStart(scroll, true, true, 0);   // expand + fill

        _window.Add(root);
        _window.ShowAll();
        Application.Run();
    }

    static MenuBar BuildMenu()
    {
        MenuBar bar = new MenuBar();
        Menu fileMenu = new Menu();
        MenuItem fileItem = new MenuItem("File") { Submenu = fileMenu };

        MenuItem open = new MenuItem("Open");
        open.Activated += OnOpen;
        fileMenu.Append(open);

        MenuItem save = new MenuItem("Save");
        save.Activated += OnSave;
        fileMenu.Append(save);

        fileMenu.Append(new SeparatorMenuItem());

        MenuItem quit = new MenuItem("Quit");
        quit.Activated += (s, e) => Application.Quit();
        fileMenu.Append(quit);

        bar.Append(fileItem);
        return bar;
    }

    static void OnOpen(object sender, EventArgs e)
    {
        var chooser = new FileChooserDialog(
            "Open file", _window, FileChooserAction.Open,
            "Cancel", ResponseType.Cancel,
            "Open",   ResponseType.Accept);

        if ((ResponseType)chooser.Run() == ResponseType.Accept)
        {
            _currentPath = chooser.Filename;
            _textView.Buffer.Text = File.ReadAllText(_currentPath);
            _window.Title = $"Notes Editor — {Path.GetFileName(_currentPath)}";
        }
        chooser.Destroy();
    }

    static void OnSave(object sender, EventArgs e)
    {
        if (_currentPath == null)
        {
            var chooser = new FileChooserDialog(
                "Save file", _window, FileChooserAction.Save,
                "Cancel", ResponseType.Cancel,
                "Save",   ResponseType.Accept);

            if ((ResponseType)chooser.Run() == ResponseType.Accept)
                _currentPath = chooser.Filename;

            chooser.Destroy();
            if (_currentPath == null) return;
        }

        File.WriteAllText(_currentPath, _textView.Buffer.Text);
        _window.Title = $"Notes Editor — {Path.GetFileName(_currentPath)} (saved)";
    }
}
```

Compile and run:

```bash
mcs Notes.cs -pkg:gtk-sharp-2.0
mono Notes.exe
```

You now have a working editor: open a text file, edit it, and save. It combines menus, a scrolled text view, file dialogs, and `System.IO` from the earlier tutorials.

---

## 11. Designing UIs Visually with Glade

Hand-coding layouts gets tedious. **Glade** is a visual designer that produces an XML `.glade`/`.ui` file describing your interface, which you load at runtime with `Gtk.Builder`.

```csharp
using Gtk;

class Program
{
    static void Main()
    {
        Application.Init();

        Builder builder = new Builder();
        builder.AddFromFile("window.glade");

        Window window = (Window)builder.GetObject("main_window");
        Button button = (Button)builder.GetObject("my_button");
        button.Clicked += (s, e) => System.Console.WriteLine("clicked");

        // Connect signal handlers defined in the .glade file automatically.
        builder.Autoconnect(new Program());

        window.DeleteEvent += (o, e) => Application.Quit();
        window.ShowAll();
        Application.Run();
    }
}
```

This separates *design* (the `.glade` file) from *logic* (your C#), much like HTML/CSS vs. JavaScript. Install Glade from your package manager (`sudo apt install glade`).

---

## 12. Gtk# 3 / Modern .NET

For new projects on modern .NET, use the **GtkSharp** NuGet package (GTK 3):

```bash
dotnet new console -n GtkApp
cd GtkApp
dotnet add package GtkSharp
```

```csharp
using Gtk;

class Program
{
    static void Main()
    {
        Application.Init();
        var app = new Application("org.example.GtkApp", GLib.ApplicationFlags.None);
        app.Register(GLib.Cancellable.Current);

        var win = new Window("Gtk# 3 on .NET");
        win.SetDefaultSize(300, 200);
        win.DeleteEvent += (o, e) => Application.Quit();
        win.Add(new Label("Hello from GTK 3!"));
        win.ShowAll();

        Application.Run();
    }
}
```

Key differences from Gtk# 2:

| Aspect | Gtk# 2 | Gtk# 3 / GtkSharp |
|--------|--------|-------------------|
| Distribution | Mono package (`-pkg:gtk-sharp-2.0`) | NuGet (`GtkSharp`) |
| Custom drawing signal | `ExposeEvent` + `CairoHelper` | `Drawn` with `Cr` supplied |
| Styling | limited | full CSS support |
| Layout | `VBox`/`HBox` common | `Box` with orientation, `Grid` preferred |
| Runtime | Mono | modern .NET (and Mono) |

The widget and signal model is otherwise the same, so what you learn here transfers.

---

## 13. Troubleshooting

### `The specified framework/package 'gtk-sharp-2.0' was not found`

Gtk# isn't installed or `pkg-config` can't find it. Install the package (`gtk-sharp2`) and verify with `pkg-config --list-all | grep gtk-sharp`.

### `DllNotFoundException: libgtk-...`

The **native** GTK libraries are missing (separate from the C# bindings). On Linux install `libgtk2.0-0`; on macOS `brew install gtk+`; on Windows use the Mono MDK which bundles them.

### The window appears but is empty

You probably forgot `window.ShowAll()`, or added widgets after calling it. Call `ShowAll()` after building the UI, or call `.Show()` on newly added widgets.

### The UI freezes during long work

The main loop is blocked. Move slow work off the UI thread (Task/async) and update widgets back on the UI thread via `Application.Invoke(() => { ... })`.

### Fonts/text look wrong or missing (Cairo)

Ensure a font is installed and referenced by a name that exists (e.g. `"Sans"`), similar to the font notes in the GDI+/SkiaSharp tutorials.

---

## 14. Where to Go Next

- **TreeView & ListStore:** GTK's powerful (and initially tricky) widget for tables and lists.
- **CSS theming (GTK 3):** style your app with CSS providers.
- **Async in the UI:** combine `async`/`await` (from the [Advanced tutorial](./CSharp-Mono-Advanced-Tutorial.md)) with `Application.Invoke` for responsive apps.
- **Embed custom graphics:** render with [SkiaSharp](./SkiaSharp-Tutorial.md) into a bitmap and display it in an `Image`/`DrawingArea`, or draw directly with Cairo.
- **Package your app:** bundle Mono + your assemblies, or publish a self-contained modern .NET GTK app.
- **Official docs:** the [Gtk# documentation](https://www.mono-project.com/docs/gui/gtksharp/) and the [GtkSharp GitHub project](https://github.com/GtkSharp/GtkSharp).

### Quick Reference

```csharp
using Gtk;

Application.Init();                                  // 1. start GTK

Window w = new Window("Title");                      // 2. build UI
w.SetDefaultSize(400, 300);
w.DeleteEvent += (o, e) => Application.Quit();

VBox box = new VBox(false, 6);
Button b = new Button("Click");
b.Clicked += (s, e) => { /* handle event */ };
box.PackStart(b, false, false, 0);
w.Add(box);

w.ShowAll();                                         // 3. show widgets
Application.Run();                                   // 4. main loop
```

Compile: `mcs App.cs -pkg:gtk-sharp-2.0` → run: `mono App.exe`

Happy GUI building! 🖼️

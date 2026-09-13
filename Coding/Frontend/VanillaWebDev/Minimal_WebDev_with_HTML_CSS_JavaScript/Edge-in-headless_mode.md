---
id: 20260912153406
title: Edge in headless mode
---

# Edge in headless mode

You can run your JavaScript files in Microsoft Edge’s headless mode directly from Visual Studio Code using the **Code Runner** extension.



Because browsers expect HTML files rather than raw `.js` files, Edge will load a lightweight HTML wrapper around your script, run it in the background (without opening a window), and output your `console.log()` statements directly into the VS Code Output panel.



Here is the complete setup guide.



## Part 1: How Edge Headless Works from PowerShell

Before setting up VS Code, test how Edge runs in headless mode via PowerShell.



1. Open **PowerShell**.



2. Run this command to execute an HTML file in Edge without opening a UI window:



   PowerShell

   ```
   & "C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe" --headless=new --dump-dom "file:///C:/path/to/your/index.html"
   ```

* `--headless=new`: Tells Edge to run strictly in the background.


* `--dump-dom`: Tells Edge to evaluate the HTML/JS and print the resulting document straight to the terminal standard output.



## Part 2: Configure Code Runner in VS Code

The **Code Runner** extension (`formulahendry.code-runner`) allows you to map custom execution commands for any file extension (`.js`, `.html`, etc.).



### Step 1: Install Code Runner

1. In VS Code, open the Extensions tab (**Ctrl + Shift + X**).


2. Search for **Code Runner** and click **Install**.



### Step 2: Configure `settings.json`

We will configure Code Runner to create an on-the-fly HTML wrapper around your active `.js` file, execute it using Edge Headless, and clean up automatically.



1. Open the VS Code Command Palette (**Ctrl + Shift + P**).


2. Type `Preferences: Open User Settings (JSON)` and press **Enter**.


3. Add the following configuration inside your `settings.json` file:



JSON

```
{
  "code-runner.executorMap": {
    "javascript": "powershell -Command \"$tmp = [System.IO.Path]::GetTempFileName() + '.html'; '<!DOCTYPE html><html><body><script>' + (Get-Content '$fileName' -Raw) + '</script></body></html>' | Set-Content $tmp; & 'C:\\Program Files (x86)\\Microsoft\\Edge\\Application\\msedge.exe' --headless=new --dump-dom file:///$tmp; Remove-Item $tmp\""
  },
  "code-runner.runInTerminal": false,
  "code-runner.clearPreviousOutput": true,
  "code-runner.showExecutionMessage": false
}
```

#### What this PowerShell script does:

1. Creates a temporary `.html` file in your system's temp folder.


2. Injects your `.js` code inside `<script>` tags.


3. Launches `msedge.exe` in headless mode.


4. Prints the result directly into VS Code’s **Output** tab.


5. Deletes the temporary HTML file immediately after execution.



## Part 3: Test Your Setup

1. Create or open a file named `test.js` in VS Code.



2. Paste this JavaScript code:



   JavaScript

   ```
   let name = "Developer";
   let skills = ["HTML", "CSS", "Vanilla JS"];

   console.log(`Hello, ${name}!`);
   console.log("Your current toolkit:", skills.join(", "));
   ```

3. Run the code:



   * Press **Ctrl + Alt + N** (or right-click anywhere in the editor and select **Run Code**).



Check the **Output** tab at the bottom of VS Code. You will see the result executed by Edge's headless V8 engine!

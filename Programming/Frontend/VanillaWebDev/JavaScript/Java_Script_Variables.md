# 20260412220229 JavaScript Variales



Exploring variables in Deno can be done in several ways, ranging from quick interactive checks to professional debugging.

Here are the best methods to explore JavaScript variables in Deno.

---

### 1. The Interactive REPL (Best for quick experiments)
Deno comes with a built-in **REPL** (Read-Eval-Print Loop). This is the fastest way to test code and see what’s inside a variable.

1.  Open your terminal and type `deno`.
2.  Create a variable and simply type its name to see its value.

```typescript
> const user = { id: 1, name: "Alice", roles: ["admin", "editor"] };
> user
{ id: 1, name: "Alice", roles: [ "admin", "editor" ] }
```

**Pro Tip:** In the REPL, you can press **Tab** after a variable name (e.g., `user.`) to see all available properties and methods.

---

### 2. Advanced Console Methods
Deno’s `console` object is highly optimized for readability.

*   **`console.log()`**: Standard output. In Deno, this automatically color-codes types (strings are green, numbers are yellow, etc.).
*   **`console.table()`**: Perfect for exploring arrays of objects.
    ```typescript
    const users = [{ name: "Bob", age: 30 }, { name: "Sara", age: 25 }];
    console.table(users);
    ```
*   **`console.dir()`**: Shows an object's structure. You can use the `depth` option to see deeply nested objects.
    ```typescript
    console.dir(myDeepObject, { depth: 10 });
    ```

---

### 3. Using `Deno.inspect()`
If you want to convert a variable into a readable string (including its colors) without printing it immediately, use `Deno.inspect`. This is what `console.log` uses under the hood.

```typescript
const complexObject = { a: 1, b: { c: 3 } };
const output = Deno.inspect(complexObject, { colors: true, depth: 4 });
console.log("The object looks like this: " + output);
```

---

### 4. Exploring the "Global" Scope
If you want to see what variables and functions are built into the Deno environment, explore the global objects:

*   **`globalThis`**: The top-level object containing everything available globally.
*   **`Deno`**: The specific namespace for Deno-only features (file system, network, etc.).

In the REPL, just type `Deno` and hit Enter to see the massive list of system tools available to you.

---

### 5. Debugging with Chrome DevTools (The "Pro" Way)
If you have a complex script and want to "pause time" to look at variables, you can use the Chrome debugger.

1.  Run your script with the inspect flag:
    ```bash
    deno run --inspect-brk my_script.ts
    ```
2.  Open Chrome or Edge and go to `chrome://inspect`.
3.  Click **"Open dedicated DevTools for Node"** (it works for Deno too).
4.  Your code will pause on the first line. You can set breakpoints, hover over variables to see their values, and use the "Console" tab to interact with the live state of your app.

---

### 6. Using VS Code "Variables" View
If you use Visual Studio Code with the **Deno extension**:

1.  Open a `.ts` file.
2.  Click in the margin to the left of the line numbers to set a **Breakpoint** (red dot).
3.  Press **F5** (Select "Deno" if prompted).
4.  When the code hits your breakpoint, look at the **"Variables"** pane on the left side of the screen. You can expand every object and see the current state of every variable in your program.

---

### Summary: Which one to use?
*   **REPL (`deno`):** Use when you are learning syntax or testing a single function.
*   **`console.table`:** Use when you have a list of data.
*   **`--inspect-brk`:** Use when you have a bug in a large script and need to see how variables change over time.
*   **VS Code Debugger:** The best experience for day-to-day development.
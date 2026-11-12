---
id: 20261112133041
title: 30-Day Absolute Beginner React Bootcamp 
author: Karl Schmitt
date: 2026-11-12
keywords: [ React, JSX ]
---

# 30-Day Absolute Beginner React Bootcamp

Welcome! This bootcamp takes you from the first React concepts to a
small, practical application.

**Daily routine**

1.  Read the lesson.
2.  Type the example yourself.
3.  Run it in your browser.
4.  Complete the exercise without copying the solution immediately.
5.  Write down one thing you learned in your Zettelkasten.

**Target environment:** Windows 11, Visual Studio Code, PowerShell, and
Microsoft Edge.

> Important: This bootcamp uses React through browser CDN scripts so you
> can learn the fundamentals without installing Node.js or Deno. This is
> a learning setup, not the recommended setup for a production
> application. Your organisation's browser and network policies may also
> restrict CDN access.

------------------------------------------------------------------------

# 1. Learning environment

## Create your project folder

Open PowerShell:

``` powershell
New-Item -ItemType Directory -Force -Path D:\codingdojo\ReactBootcamp
Set-Location D:\codingdojo\ReactBootcamp
code .
```

If the `code` command is unavailable, open Visual Studio Code from the
Start menu and choose **File → Open Folder**.

Create a file named `index.html` with this content:

``` html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>React Bootcamp</title>
</head>
<body>
  <div id="root"></div>

  <script src="https://unpkg.com/react@18/umd/react.development.js"></script>
  <script src="https://unpkg.com/react-dom@18/umd/react-dom.development.js"></script>
  <script src="https://unpkg.com/@babel/standalone/babel.min.js"></script>

  <script type="text/babel" src="./app.js"></script>
</body>
</html>
```

Create a second file named `app.js`:

``` javascript
function App() {
  return <h1>Hello, React!</h1>;
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);
```

Open `index.html` in Microsoft Edge. You should see **Hello, React!**

If your organisation blocks the CDN addresses, ask whether an approved
local React learning environment is available. Do not bypass workplace
security restrictions.

## How the setup works

-   **React** provides the component and UI functionality.
-   **ReactDOM** connects React to the browser's DOM.
-   **Babel Standalone** transforms JSX in the browser for this learning
    setup.
-   The element with `id="root"` is where React displays the
    application.
-   `app.js` contains your React code.

Keep this setup for the bootcamp. Replace the contents of `app.js` for
each day's exercise, unless a lesson says otherwise.

------------------------------------------------------------------------

# Week 1 --- React foundations

## Day 1 --- What is React?

### Lesson

React is a JavaScript library for building user interfaces.

A user interface is made of things people see and interact with:

-   Headings
-   Buttons
-   Forms
-   Navigation
-   Lists
-   Dialogs
-   Data displays

React encourages you to build interfaces from small, reusable pieces
called **components**.

Without React, you might manually find HTML elements and change them.
With React, you describe what the interface should look like for the
current application data. React updates the displayed interface when
that data changes.

A React application is often structured as a tree of components:

``` text
App
├── Header
├── Navigation
└── Main
    ├── WelcomeMessage
    └── Footer
```

### Exercise

1.  Open `app.js`.
2.  Display a heading that says `My First React Application`.
3.  Add a paragraph explaining what you want to learn.
4.  Add a second paragraph showing today's date.

Example starting point:

``` javascript
function App() {
  return (
    <div>
      <h1>My First React Application</h1>
      <p>I am learning React.</p>
      <p>Today I am practising components.</p>
    </div>
  );
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<App />);
```

**Zettelkasten note:**
`React — A JavaScript library for building user interfaces`

## Day 2 --- JSX

### Lesson

JSX is a syntax extension commonly used with React. It lets you write
markup-like expressions inside JavaScript.

JSX example:

``` jsx
const heading = <h1>Hello, React!</h1>;
```

JSX is not HTML, even though it looks similar. A few important
differences:

-   Use `className` instead of `class`.
-   Return one parent element, or use a Fragment.
-   Close elements such as `img` and `input`.
-   Use curly braces to insert JavaScript expressions.

JavaScript expression inside JSX:

``` jsx
const name = "Ada";

function App() {
  return <h1>Hello, {name}!</h1>;
}
```

A Fragment groups elements without adding an extra HTML element:

``` jsx
function App() {
  return (
    <>
      <h1>Welcome</h1>
      <p>Learning JSX.</p>
    </>
  );
}
```

### Exercise

Create a profile panel with:

-   Your chosen display name
-   A heading
-   A short description
-   A favourite programming language
-   A paragraph containing a JavaScript expression, such as `2 + 3`

Use JSX expressions inside curly braces.

**Zettelkasten note:** `React — JSX and JavaScript expressions`

## Day 3 --- Your first functional component

### Lesson

A component is a reusable part of the user interface. In modern React,
components are usually JavaScript functions that return JSX.

``` jsx
function Welcome() {
  return <h2>Welcome to my application!</h2>;
}
```

Use a component by writing it as a JSX element:

``` jsx
function App() {
  return (
    <div>
      <h1>My Application</h1>
      <Welcome />
    </div>
  );
}
```

Component naming rules:

-   Component names start with an uppercase letter.
-   A component returns JSX.
-   Components can be composed from other components.

### Exercise

Create three components:

1.  `Header` --- displays the application title.
2.  `MainContent` --- displays a welcome paragraph.
3.  `Footer` --- displays a copyright message.

Render all three inside `App`.

**Zettelkasten note:** `React — Functional components`

## Day 4 --- Component composition

### Lesson

Composition means building a larger component by combining smaller
components.

For example:

``` jsx
function Header() {
  return <header><h1>Learning Portal</h1></header>;
}

function MainContent() {
  return <main><p>Choose a topic and start learning.</p></main>;
}

function Footer() {
  return <footer><small>Learning Portal</small></footer>;
}

function App() {
  return (
    <>
      <Header />
      <MainContent />
      <Footer />
    </>
  );
}
```

This makes code easier to understand, test, reuse, and maintain.

A useful guideline: a component should have a clear responsibility.
Avoid putting an entire application into one enormous component.

### Exercise

Build a simple book page using these components:

-   `BookHeader`
-   `BookDetails`
-   `AuthorDetails`
-   `BookFooter`

Compose them inside `App`.

**Zettelkasten note:** `React — Component composition`

## Day 5 --- Props

### Lesson

Props are inputs passed from a parent component to a child component.

``` jsx
function Greeting(props) {
  return <h2>Hello, {props.name}!</h2>;
}

function App() {
  return (
    <>
      <Greeting name="Ada" />
      <Greeting name="Grace" />
    </>
  );
}
```

You can also destructure props:

``` jsx
function Greeting({ name }) {
  return <h2>Hello, {name}!</h2>;
}
```

Props are read-only from the component's point of view. A child
component should not modify its props.

### Exercise

Create a reusable `BookCard` component. Pass these props:

-   `title`
-   `author`
-   `year`

Render three different books by using the same component three times.

**Zettelkasten note:** `React — Props pass data from parent to child`

## Day 6 --- The children prop

### Lesson

The special `children` prop contains content placed between a
component's opening and closing tags.

``` jsx
function Panel({ children }) {
  return (
    <section className="panel">
      {children}
    </section>
  );
}

function App() {
  return (
    <Panel>
      <h2>Learning React</h2>
      <p>This content is passed as children.</p>
    </Panel>
  );
}
```

This pattern is useful for reusable layout components such as panels,
cards, dialogs, and page sections.

### Exercise

Create a `Card` component that renders its `children` inside a bordered
section. Use it to display:

1.  A welcome message.
2.  A book description.
3.  A programming tip.

**Zettelkasten note:** `React — The children prop`

## Day 7 --- JavaScript fundamentals for React

### Lesson

React relies on ordinary JavaScript. Make sure you understand these
concepts:

**Variables**

``` javascript
const language = "JavaScript";
let score = 0;
score = score + 1;
```

**Arrow functions**

``` javascript
const add = (a, b) => a + b;
```

**Template literals**

``` javascript
const message = `I am learning ${language}.`;
```

**Array methods**

``` javascript
const languages = ["Java", "JavaScript", "C++"];
const upperCaseLanguages = languages.map(
  language => language.toUpperCase()
);
```

**Destructuring**

``` javascript
const book = { title: "Example", year: 2026 };
const { title, year } = book;
```

### Exercise

Create an array of five books. Each book should have a title and an
author. Use `map()` to create a new array containing only the book
titles.

Display the resulting titles in the browser using JSX.

**Zettelkasten note:** `JavaScript — Array map and destructuring`

------------------------------------------------------------------------

# Week 2 --- State and interaction

## Day 8 --- Rendering lists and using keys

### Lesson

Use JavaScript's `map()` method to render a list of elements.

``` jsx
function App() {
  const languages = ["Java", "JavaScript", "C++"];

  return (
    <ul>
      {languages.map(language => (
        <li key={language}>{language}</li>
      ))}
    </ul>
  );
}
```

React uses the `key` prop to identify list items between renders. Keys
should be stable and unique among siblings. Avoid using an array index
as a key when items can be inserted, deleted, or reordered.

### Exercise

Create an array of five favourite books. Render them as an ordered list.
Give each item a stable key. Then add an author property to each book
and display both title and author.

**Zettelkasten note:** `React — Rendering lists and keys`

## Day 9 --- State with useState

### Lesson

State is data that belongs to a component and can change over time.

The `useState` Hook gives you a state value and a function to update it.

``` jsx
function Counter() {
  const [count, setCount] = React.useState(0);

  return (
    <div>
      <p>Count: {count}</p>
      <button onClick={() => setCount(count + 1)}>
        Increase
      </button>
    </div>
  );
}
```

When state changes, React renders the component again so the interface
reflects the new value.

Important points:

-   Call Hooks at the top level of a component.
-   Do not call Hooks inside loops or conditions.
-   Use the setter function to update state.
-   Do not directly modify state.

### Exercise

Build a counter with three buttons:

-   Increase
-   Decrease
-   Reset

The counter should start at zero.

**Zettelkasten note:** `React — State and the useState Hook`

## Day 10 --- Handling events

### Lesson

React event handlers let your application respond to user interaction.

``` jsx
function App() {
  function handleClick() {
    alert("Button clicked!");
  }

  return <button onClick={handleClick}>Click me</button>;
}
```

Notice that `onClick` receives the function itself:

``` jsx
<button onClick={handleClick}>Click</button>
```

Do not call it while rendering:

``` jsx
// Incorrect: calls the function immediately.
<button onClick={handleClick()}>Click</button>
```

You can pass arguments with an arrow function:

``` jsx
<button onClick={() => greet("Ada")}>Greet Ada</button>
```

### Exercise

Create a small interface with:

-   A button that displays an alert.
-   A button that changes a message on the page.
-   A button that increases a counter.

**Zettelkasten note:** `React — Event handling`

## Day 11 --- Updating state safely

### Lesson

When the next state depends on the previous state, use the functional
updater form.

``` jsx
setCount(previousCount => previousCount + 1);
```

This is safer than relying on a value captured by an event handler,
especially when multiple updates are queued.

For example:

``` jsx
function Counter() {
  const [count, setCount] = React.useState(0);

  function increaseThreeTimes() {
    setCount(value => value + 1);
    setCount(value => value + 1);
    setCount(value => value + 1);
  }

  return (
    <>
      <p>{count}</p>
      <button onClick={increaseThreeTimes}>
        Increase by 3
      </button>
    </>
  );
}
```

### Exercise

Extend your counter with an `Increase by 5` button. Use the functional
updater form for every update that depends on the previous counter
value.

**Zettelkasten note:** `React — Functional state updates`

## Day 12 --- Conditional rendering

### Lesson

Sometimes an interface should display different content depending on
application state.

Use a normal JavaScript condition:

``` jsx
function App() {
  const [loggedIn, setLoggedIn] = React.useState(false);

  return (
    <div>
      {loggedIn ? <h2>Welcome back!</h2> : <h2>Please log in.</h2>}

      <button onClick={() => setLoggedIn(value => !value)}>
        Toggle login
      </button>
    </div>
  );
}
```

You can also use `&&` when you only want to display something when a
condition is true:

``` jsx
{loggedIn && <p>You are logged in.</p>}
```

### Exercise

Build a visibility toggle:

-   Initially, a paragraph is hidden.
-   Clicking `Show details` displays it.
-   Clicking `Hide details` hides it again.

Use state and conditional rendering.

**Zettelkasten note:** `React — Conditional rendering`

## Day 13 --- Forms and controlled inputs

### Lesson

A controlled input is an input whose displayed value is controlled by
React state.

``` jsx
function NameForm() {
  const [name, setName] = React.useState("");

  return (
    <div>
      <label>
        Your name:
        <input
          value={name}
          onChange={event => setName(event.target.value)}
        />
      </label>

      <p>Hello, {name || "stranger"}!</p>
    </div>
  );
}
```

The important relationship is:

1.  React state supplies the input's `value`.
2.  The user types.
3.  `onChange` receives the change event.
4.  The event handler updates state.
5.  React renders the new value.

### Exercise

Create a form with:

-   A name input.
-   An email input.
-   A submit button.

Prevent the browser's default form submission with
`event.preventDefault()`. When the form is submitted, display the
entered name on the page.

**Zettelkasten note:** `React — Controlled form inputs`

## Day 14 --- Mini-project: Todo list

### Lesson

Today you combine components, props, state, events, lists, and forms.

A Todo item can be represented as an object:

``` javascript
{
  id: 1,
  text: "Learn React",
  completed: false
}
```

A list of Todo items is an array of these objects. When adding an item,
create a new array rather than modifying the existing array.

``` javascript
setTodos(previousTodos => [
  ...previousTodos,
  newTodo
]);
```

The spread syntax (`...`) copies the existing array elements into a new
array.

### Exercise

Build a basic Todo application:

-   An input for a task.
-   An Add button.
-   A list of tasks.
-   A way to mark a task as completed.
-   A way to remove a task.

Suggested component structure:

``` text
App
└── TodoList
    └── TodoItem
```

Do not worry about perfect styling. Focus on correct state updates.

**Zettelkasten note:** `React — Todo list mini-project`

------------------------------------------------------------------------

# Week 3 --- Data flow and application structure

## Day 15 --- Derived state and searching

### Lesson

Derived data is calculated from existing props or state. You usually do
not need separate state for values that can be calculated during
rendering.

For example:

``` jsx
function App() {
  const [query, setQuery] = React.useState("");
  const books = ["Clean Code", "The Pragmatic Programmer", "Refactoring"];

  const filteredBooks = books.filter(book =>
    book.toLowerCase().includes(query.toLowerCase())
  );

  return (
    <>
      <input
        value={query}
        onChange={event => setQuery(event.target.value)}
        placeholder="Search books"
      />

      <ul>
        {filteredBooks.map(book => <li key={book}>{book}</li>)}
      </ul>
    </>
  );
}
```

The filtered list is derived from `books` and `query`.

### Exercise

Add a search field to your book list. It should filter books by title as
the user types. Display a message when no books match.

**Zettelkasten note:** `React — Derived state`

## Day 16 --- Styling React components

### Lesson

React components produce HTML elements, and you can style those elements
with CSS.

Create a file named `styles.css` and add:

``` css
body {
  font-family: Arial, sans-serif;
  margin: 2rem;
  background: #f4f4f4;
}

.card {
  background: white;
  border: 1px solid #ddd;
  border-radius: 8px;
  padding: 1rem;
  margin-bottom: 1rem;
}
```

Add this inside the `head` element of `index.html`:

``` html
<link rel="stylesheet" href="./styles.css">
```

Use the CSS class in JSX:

``` jsx
function BookCard() {
  return (
    <article className="card">
      <h2>Clean Code</h2>
      <p>Robert C. Martin</p>
    </article>
  );
}
```

Remember: JSX uses `className`, not `class`.

### Exercise

Style your Todo application:

-   Add spacing between tasks.
-   Give completed tasks a different appearance.
-   Make buttons easy to distinguish.
-   Add a clear page heading.

**Zettelkasten note:** `React — Styling with CSS`

## Day 17 --- Lifting state up

### Lesson

Sometimes two or more components need the same data. In that case, move
the shared state to their closest common parent. This is called
**lifting state up**.

Example structure:

``` text
App (owns selected book state)
├── BookList (selects a book)
└── BookDetails (displays selected book)
```

The parent owns the state and passes data and callback functions to its
children through props.

``` jsx
function BookList({ onSelect }) {
  return (
    <button onClick={() => onSelect("Clean Code")}>
      Select Clean Code
    </button>
  );
}

function BookDetails({ selectedBook }) {
  return <p>Selected: {selectedBook}</p>;
}

function App() {
  const [selectedBook, setSelectedBook] = React.useState("None");

  return (
    <>
      <BookList onSelect={setSelectedBook} />
      <BookDetails selectedBook={selectedBook} />
    </>
  );
}
```

### Exercise

Create a parent component that stores a selected programming language. A
child component displays buttons for Java, JavaScript, and C++. Another
child displays the selected language.

**Zettelkasten note:** `React — Lifting state up`

## Day 18 --- Context API

### Lesson

Passing props through many component levels can become inconvenient.
Context allows components to read shared values without passing props
through every intermediate component.

A simplified example:

``` jsx
const ThemeContext = React.createContext("light");

function Toolbar() {
  const theme = React.useContext(ThemeContext);
  return <p>Current theme: {theme}</p>;
}

function App() {
  return (
    <ThemeContext.Provider value="dark">
      <Toolbar />
    </ThemeContext.Provider>
  );
}
```

Context is useful for values needed by many components, such as a theme
or current user information.

Do not use Context for every value. For local component state,
`useState` is usually simpler.

### Exercise

Create a `LanguageContext` that provides the value `"JavaScript"`. Read
that value in a deeply nested component.

**Zettelkasten note:** `React — Context API and useContext`

## Day 19 --- useReducer

### Lesson

`useReducer` is another way to manage component state. It can be useful
when state transitions are more complex or when several actions affect
the same state.

A reducer receives the current state and an action, then returns the
next state.

``` jsx
function counterReducer(state, action) {
  switch (action.type) {
    case "increment":
      return { count: state.count + 1 };
    case "decrement":
      return { count: state.count - 1 };
    case "reset":
      return { count: 0 };
    default:
      return state;
  }
}
```

Use it in a component:

``` jsx
function Counter() {
  const [state, dispatch] = React.useReducer(
    counterReducer,
    { count: 0 }
  );

  return (
    <>
      <p>{state.count}</p>
      <button onClick={() => dispatch({ type: "increment" })}>
        Increase
      </button>
      <button onClick={() => dispatch({ type: "decrement" })}>
        Decrease
      </button>
      <button onClick={() => dispatch({ type: "reset" })}>
        Reset
      </button>
    </>
  );
}
```

### Exercise

Replace the state handling in your Todo application with `useReducer`.
Define actions for adding, completing, and removing tasks.

**Zettelkasten note:** `React — useReducer and reducer functions`

## Day 20 --- useEffect fundamentals

### Lesson

`useEffect` lets a component synchronize with something outside React,
such as a browser API, a timer, or a network connection.

``` jsx
function App() {
  React.useEffect(() => {
    document.title = "React Bootcamp";
  }, []);

  return <h1>Welcome</h1>;
}
```

The dependency array matters:

-   No dependency array: the Effect runs after every render.
-   Empty array (`[]`): the Effect runs after the initial mount, with
    development-mode nuances.
-   `[value]`: the Effect re-runs when `value` changes.

Do not use Effects for values that can simply be calculated during
rendering.

### Exercise

Create a component that updates the browser tab title when a user enters
a name. Use `useEffect` with the name as a dependency. Consider
restoring the previous title in the cleanup function.

**Zettelkasten note:** `React — useEffect and dependencies`

## Day 21 --- Effect cleanup and timers

### Lesson

Some Effects create resources that must be cleaned up, such as timers or
event listeners.

``` jsx
function Clock() {
  const [seconds, setSeconds] = React.useState(0);

  React.useEffect(() => {
    const timerId = setInterval(() => {
      setSeconds(value => value + 1);
    }, 1000);

    return () => {
      clearInterval(timerId);
    };
  }, []);

  return <p>Seconds: {seconds}</p>;
}
```

The function returned from the Effect is the cleanup function. React
calls it when the component is removed and before re-running an Effect
whose dependencies have changed.

### Exercise

Build a stopwatch with:

-   Start
-   Stop
-   Reset

Use `useEffect` and `setInterval`. Always clear the interval when it is
no longer needed. Avoid creating multiple intervals accidentally.

**Zettelkasten note:** `React — Effect cleanup`

------------------------------------------------------------------------

# Week 4 --- APIs and practical React skills

## Day 22 --- REST APIs and JSON

### Lesson

A REST API lets an application communicate with a server over HTTP. An
API often returns JSON data.

Example JSON:

``` json
{
  "id": 1,
  "name": "Luke Skywalker",
  "height": "172"
}
```

JSON represents data using objects, arrays, strings, numbers, booleans,
and `null`.

In a React application, you commonly:

1.  Send an HTTP request.
2.  Receive a response.
3.  Parse the response as JSON.
4.  Store the data in state.
5.  Render the data.

### Exercise

Read the JSON example above. Create a JavaScript object with the same
information. Display the character's name and height in a React
component.

**Zettelkasten note:** `Web development — REST APIs and JSON`

## Day 23 --- Fetch API

### Lesson

The browser provides the Fetch API for making HTTP requests.

A basic example:

``` javascript
fetch("https://jsonplaceholder.typicode.com/users/1")
  .then(response => {
    if (!response.ok) {
      throw new Error("HTTP error: " + response.status);
    }
    return response.json();
  })
  .then(data => {
    console.log(data);
  })
  .catch(error => {
    console.error("Request failed:", error);
  });
```

`fetch()` returns a Promise. The response body must be parsed, for
example with `response.json()`.

### Exercise

Use `fetch()` to request:

`https://jsonplaceholder.typicode.com/users/1`

Inspect the returned object in the Edge developer tools console.
Identify the user's name, email, and city.

**Zettelkasten note:** `JavaScript — Fetch API`

## Day 24 --- Loading and error states

### Lesson

A network request takes time and can fail. A user interface should
communicate what is happening.

Typical states include:

-   Loading
-   Success
-   Error

Example:

``` jsx
function UserInfo() {
  const [user, setUser] = React.useState(null);
  const [loading, setLoading] = React.useState(true);
  const [error, setError] = React.useState("");

  React.useEffect(() => {
    async function loadUser() {
      try {
        const response = await fetch(
          "https://jsonplaceholder.typicode.com/users/1"
        );

        if (!response.ok) {
          throw new Error(`HTTP error: ${response.status}`);
        }

        const data = await response.json();
        setUser(data);
      } catch (err) {
        setError(err.message);
      } finally {
        setLoading(false);
      }
    }

    loadUser();
  }, []);

  if (loading) return <p>Loading...</p>;
  if (error) return <p>Error: {error}</p>;
  if (!user) return <p>No user found.</p>;

  return <h2>{user.name}</h2>;
}
```

### Exercise

Build a component that fetches a user from the same JSONPlaceholder
endpoint. Display:

-   `Loading...` while waiting.
-   The user's name and email after success.
-   A helpful error message if the request fails.

**Zettelkasten note:** `React — Loading, success, and error states`

## Day 25 --- Custom Hooks

### Lesson

A custom Hook is a JavaScript function whose name begins with `use` and
that can call other Hooks.

Custom Hooks help you reuse stateful logic between components.

Example:

``` jsx
function useCounter(initialValue = 0) {
  const [count, setCount] = React.useState(initialValue);

  function increase() {
    setCount(value => value + 1);
  }

  function reset() {
    setCount(initialValue);
  }

  return { count, increase, reset };
}
```

Use the custom Hook:

``` jsx
function Counter() {
  const { count, increase, reset } = useCounter(10);

  return (
    <>
      <p>{count}</p>
      <button onClick={increase}>Increase</button>
      <button onClick={reset}>Reset</button>
    </>
  );
}
```

Custom Hooks share logic, not one shared state instance. Each component
calling the Hook gets its own Hook state unless the logic connects to a
shared external store or Context.

### Exercise

Create a custom Hook named `useToggle`. It should return a boolean value
and a function that toggles it. Use it in a component to show and hide a
paragraph.

**Zettelkasten note:** `React — Building custom Hooks`

## Day 26 --- useRef

### Lesson

`useRef` stores a value that persists between renders without causing a
re-render when it changes. It is also commonly used to access a DOM
element.

``` jsx
function SearchBox() {
  const inputRef = React.useRef(null);

  function focusInput() {
    inputRef.current.focus();
  }

  return (
    <>
      <input ref={inputRef} placeholder="Search..." />
      <button onClick={focusInput}>Focus input</button>
    </>
  );
}
```

Use state when a value affects what should be displayed. Use a ref for
values that need to persist but do not themselves need to trigger
rendering, or for DOM access.

### Exercise

Create an input and a button labelled `Focus`. Clicking the button
should move the cursor into the input. Use `useRef`.

**Zettelkasten note:** `React — useRef`

## Day 27 --- Performance fundamentals

### Lesson

Start by writing clear, correct React code. Performance optimizations
should be introduced when there is a real need.

Three concepts:

-   `React.memo` can skip rendering a component when its props have not
    changed.
-   `useMemo` can cache a calculated value between renders.
-   `useCallback` can cache a function definition between renders.

Example of `useMemo`:

``` jsx
function App() {
  const [number, setNumber] = React.useState(10);

  const doubled = React.useMemo(() => {
    return number * 2;
  }, [number]);

  return (
    <>
      <p>Doubled: {doubled}</p>
      <button onClick={() => setNumber(value => value + 1)}>
        Increase
      </button>
    </>
  );
}
```

Do not add memoization everywhere. It adds complexity and is most useful
when it addresses a measured or understood performance issue.

### Exercise

Create a list of numbers and a function that calculates their sum.
Display the sum. Then use `useMemo` to calculate it from the list.
Explain in a note which value should be in the dependency array.

**Zettelkasten note:**
`React — Memoization with useMemo and useCallback`

## Day 28 --- Accessibility

### Lesson

Accessible applications can be used by people with different abilities
and different ways of interacting with a computer.

Important practices:

-   Use semantic HTML elements such as `main`, `nav`, `button`, and
    `label`.
-   Give form inputs accessible labels.
-   Make interactive elements usable with a keyboard.
-   Use meaningful text for buttons and links.
-   Provide alternative text for informative images.
-   Do not communicate information using colour alone.

Example:

``` jsx
function SearchForm() {
  const [query, setQuery] = React.useState("");

  return (
    <form onSubmit={event => event.preventDefault()}>
      <label htmlFor="search">Search books</label>
      <input
        id="search"
        value={query}
        onChange={event => setQuery(event.target.value)}
      />
      <button type="submit">Search</button>
    </form>
  );
}
```

### Exercise

Review your Todo application:

1.  Add labels to its inputs.
2.  Make sure buttons have descriptive text.
3.  Check that you can use the interface with the keyboard.
4.  Use headings in a logical order.
5.  Make completed tasks understandable without relying only on colour.

**Zettelkasten note:** `Web development — Accessibility fundamentals`

------------------------------------------------------------------------

# Final project --- Star Wars Explorer

## Day 29 --- Plan the application

### Lesson

Today you plan a small application that displays Star Wars character
information. The aim is to bring together the React concepts from the
previous 28 days.

A possible component structure:

``` text
App
├── Header
├── SearchForm
├── CharacterList
│   └── CharacterCard
└── CharacterDetails
```

Possible state:

-   Search text
-   Character data
-   Loading status
-   Error message
-   Selected character

Plan the data flow:

1.  `App` owns the important shared state.
2.  `SearchForm` receives the search text and a callback.
3.  `CharacterList` receives the character data.
4.  `CharacterCard` displays one character.
5.  `CharacterDetails` displays the selected character.

For this learning project, you can use the public Star Wars API at
`https://swapi.dev/`. Availability and network access may vary.

### Exercise

Before writing code:

1.  Draw the component tree.
2.  Write down the state your application needs.
3.  Decide which component owns each piece of state.
4.  Sketch the user interface on paper or in a Markdown note.
5.  Write down the API endpoint you intend to use.

**Zettelkasten note:** `React project — Star Wars Explorer architecture`

## Day 30 --- Build Star Wars Explorer

### Lesson

Now implement your planned application in small steps.

Recommended order:

1.  Create the `App` component and page layout.
2.  Create a search input.
3.  Add loading, success, and error states.
4.  Fetch character data from the API.
5.  Render the characters with `map()` and stable keys.
6.  Create a reusable `CharacterCard`.
7.  Add selection and a details panel.
8.  Add CSS styling.
9.  Test the application with valid and invalid searches.

A request to the Star Wars API can look like this:

``` javascript
const response = await fetch("https://swapi.dev/api/people/1/");

if (!response.ok) {
  throw new Error(`HTTP error: ${response.status}`);
}

const character = await response.json();
console.log(character.name);
```

Build incrementally. Test after each step instead of writing the entire
application at once.

### Exercise

Complete your Star Wars Explorer with at least these features:

-   Search for a character.
-   Display the character's name.
-   Display height and gender when available.
-   Show a loading message.
-   Show an error message when the request fails.
-   Allow the user to select a character and view its details.

**Zettelkasten note:** `React project — Star Wars Explorer`

------------------------------------------------------------------------

# 5. Progress tracker

Use this checklist to track your progress. You can tick each day in
Zettlr as you complete it.

## Week 1 --- Foundations

-   [ ] Day 1 --- What is React?
-   [ ] Day 2 --- JSX
-   [ ] Day 3 --- Functional components
-   [ ] Day 4 --- Component composition
-   [ ] Day 5 --- Props
-   [ ] Day 6 --- The children prop
-   [ ] Day 7 --- JavaScript fundamentals

## Week 2 --- State and interaction

-   [ ] Day 8 --- Lists and keys
-   [ ] Day 9 --- useState
-   [ ] Day 10 --- Event handling
-   [ ] Day 11 --- Functional state updates
-   [ ] Day 12 --- Conditional rendering
-   [ ] Day 13 --- Controlled forms
-   [ ] Day 14 --- Todo list mini-project

## Week 3 --- Data flow and structure

-   [ ] Day 15 --- Derived state and searching
-   [ ] Day 16 --- CSS styling
-   [ ] Day 17 --- Lifting state up
-   [ ] Day 18 --- Context API
-   [ ] Day 19 --- useReducer
-   [ ] Day 20 --- useEffect
-   [ ] Day 21 --- Effect cleanup and timers

## Week 4 --- Practical skills

-   [ ] Day 22 --- REST APIs and JSON
-   [ ] Day 23 --- Fetch API
-   [ ] Day 24 --- Loading and error states
-   [ ] Day 25 --- Custom Hooks
-   [ ] Day 26 --- useRef
-   [ ] Day 27 --- Performance fundamentals
-   [ ] Day 28 --- Accessibility
-   [ ] Day 29 --- Star Wars Explorer planning
-   [ ] Day 30 --- Star Wars Explorer implementation

------------------------------------------------------------------------

# 6. Suggested Zettelkasten structure

You can organize your React notes like this:

``` text
C:\React
│
├── 00-React-Overview.md
│
├── 01-Fundamentals
│   ├── What-is-React.md
│   ├── JSX.md
│   ├── Functional-Components.md
│   ├── Component-Composition.md
│   ├── Props.md
│   └── Children-Prop.md
│
├── 02-State-and-Events
│   ├── useState.md
│   ├── Event-Handling.md
│   ├── Conditional-Rendering.md
│   └── Controlled-Inputs.md
│
├── 03-Data-Flow
│   ├── Lifting-State-Up.md
│   ├── Context-API.md
│   ├── useReducer.md
│   └── Derived-State.md
│
├── 04-React-Hooks
│   ├── useEffect.md
│   ├── Effect-Cleanup.md
│   ├── Custom-Hooks.md
│   └── useRef.md
│
├── 05-APIs
│   ├── REST-and-JSON.md
│   ├── Fetch-API.md
│   └── Loading-and-Error-States.md
│
└── 06-Projects
    ├── Todo-List.md
    └── Star-Wars-Explorer.md
```

The folder names are suggestions. Adapt them to your existing
Zettelkasten structure.

## A useful note template

Use this template when turning a lesson into a permanent Zettelkasten
note:

``` markdown
# Topic

## What is it?

Explain the concept in your own words.

## Why is it useful?

Describe the problem it solves.

## Example

Add a small code example that you understand.

## Related concepts

- [[Related note 1]]
- [[Related note 2]]

## Questions

- What do I still need to understand?
```

------------------------------------------------------------------------

# 7. What to learn after the bootcamp

After completing the 30 days, continue with these topics:

1.  **Modern React project setup** --- learn an approved build tool when
    your environment permits it.
2.  **React Router** --- navigation and multiple pages.
3.  **TypeScript with React** --- types for props, state, events, and
    API data.
4.  **Testing** --- component and application testing.
5.  **State management** --- understand when Context, reducers, or an
    external state library are appropriate.
6.  **Backend integration** --- connect a React frontend to a Spring
    Boot REST API.
7.  **Build and deployment** --- understand how a React application is
    prepared and delivered.

## Final advice

Do not rush through the 30 days. It is perfectly fine to spend two or
three days on a difficult topic. The most important concepts to
understand deeply are:

-   Components
-   Props
-   State
-   Events
-   Lists and keys
-   Hooks
-   Data flow
-   Effects
-   API requests

You do not need to memorize every API. Learn how to reason about
component responsibilities, data flow, and state changes. Practise by
typing the code yourself and changing it to see what happens.

**You can do this one day at a time. Happy learning!**

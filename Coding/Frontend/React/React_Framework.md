---
id: 20261112085148
title: React Framework – Deep Dive Tutorial
author: Karl Schmitt
date: 2026-11-12
summary: The tutorial will take you from understanding what React is to building your own interactive applications. 
keywords: [ React, JavaScript, JSX, Functional Components, Hooks ]
---

![React Logo](./Images/react-logo-dark.png)

# React Framework – Deep Dive Tutorial

## Absolute Beginner to Practical Developer

**Tags:** #React #JavaScript #Frontend #WebDevelopment #Programming #Tutorial

**Learning level:** Absolute Beginner\
**Goal:** Understand React fundamentals and build interactive web applications.\
**Prerequisites:** Basic HTML, CSS and JavaScript knowledge (we will explain the important JavaScript concepts along the way).

### Abstract

* JavaScript as the programming language.

* React with functional components and Hooks.

* HTML, CSS and JSX for the frontend.

* Visual Studio Code as the editor.

* PowerShell and Microsoft Edge for working and testing.

***

# 1. What is React?

React is a JavaScript library for building user interfaces (UIs).

It was originally developed by Facebook (now Meta) and is widely used for creating modern web applications.

Without React, you typically manipulate the HTML DOM directly using JavaScript.

For example:

```
const heading = document.createElement("h1");
heading.textContent = "Hello World";

document.body.appendChild(heading);
```

With React, you describe what the user interface should look like:

```
function App() {
    return <h1>Hello World!</h1>;
}
```

React takes care of updating the user interface when application data changes.

## 1.1 Why use React?

React provides several important advantages:

* Component-based architecture.

* Reusable UI elements.

* Declarative programming.

* Efficient UI updates.

* One-way data flow.

* A large ecosystem.

* Support for complex applications.

## 1.2 The component-based approach

Imagine building a Star Wars information application.

Instead of creating one enormous HTML document, we divide the application into smaller components.

```
StarWarsApp
│
├── Header
│
├── Navigation
│
├── CharacterList
│   │
│   ├── CharacterCard
│   ├── CharacterCard
│   └── CharacterCard
│
└── Footer
```

Each component has a specific responsibility.

For example:

* `Header` displays the application heading.

* `Navigation` displays navigation links.

* `CharacterList` displays multiple characters.

* `CharacterCard` displays an individual character.

* `Footer` displays copyright information.

**Important concept:** A React application is essentially a tree of components.

***

# 2. Setting Up Your React Learning Environment

There are two common approaches.

## 2.1 Traditional React development

A typical professional React development environment consists of:

| Tool               | Purpose                           |
| ------------------ | --------------------------------- |
| Visual Studio Code | Code editor                       |
| Node.js            | JavaScript runtime                |
| npm                | Package management                |
| Vite               | Development server and build tool |
| React              | UI library                        |
| Edge               | Browser                           |

A typical project is created with:

```
npm create vite@latest my-react-app -- --template react
cd my-react-app
npm install
npm run dev
```

This is the recommended approach when Node.js is permitted.

## 2.2 Browser-based React without Node.js

For learning React without installing Node.js, we can use React through CDN scripts.

Create a directory:

```
mkdir ReactLearning
cd ReactLearning
code .
```

Create a file named:

```
index.html
```

Insert the following code:

```
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>React Learning</title>

    <script src="https://unpkg.com/react@18/umd/react.development.js"></script>

    <script src="https://unpkg.com/react-dom@18/umd/react-dom.development.js"></script>

    <script src="https://unpkg.com/@babel/standalone/babel.min.js"></script>
</head>

<body>

    <div id="root"></div>

    <script type="text/babel">

        function App() {
            return (
                <h1>Hello React!</h1>
            );
        }

        const root = ReactDOM.createRoot(
            document.getElementById("root")
        );

        root.render(<App />);

    </script>

</body>
</html>
```

Open the HTML file in Microsoft Edge.

You should see:

**Hello React!**

What are these three libraries?

| Library   | Responsibility                                |
| --------- | --------------------------------------------- |
| React     | Creates React components and manages UI logic |
| React DOM | Connects React to the browser DOM             |
| Babel     | Transforms JSX into JavaScript                |

The CDN approach is excellent for learning fundamentals, but it is not recommended for production applications.

It also requires an internet connection.

***

# 3. Understanding JSX

JSX stands for JavaScript XML.

It allows us to write HTML-like syntax inside JavaScript.

Example:

```
function App() {

    const name = "Luke Skywalker";

    return (
        <div>
            <h1>Hello {name}!</h1>
            <p>Welcome to the Star Wars application.</p>
        </div>
    );
}
```

The result:

```
Hello Luke Skywalker!
Welcome to the Star Wars application.
```

## 3.1 JSX expressions

JavaScript expressions can be embedded inside JSX using curly braces.

```
function App() {

    const firstName = "Luke";
    const lastName = "Skywalker";

    return (
        <h1>
            {firstName} {lastName}
        </h1>
    );
}
```

You can also perform calculations:

```
function App() {

    const price = 100;
    const tax = 19;

    return (
        <p>Total: {price + tax} EUR</p>
    );
}
```

## 3.2 JSX rules

Important JSX rules:

1. Return one parent element.

2. Close every HTML element.

3. Use `className` instead of `class`.

4. Use curly braces for JavaScript expressions.

5. Use camelCase for most JSX event attributes.

Example:

```
function App() {
    return (
        <div className="container">
            <h1>React Tutorial</h1>
            <input type="text" />
        </div>
    );
}
```

## 3.3 React Fragment

Sometimes we want to return multiple elements without adding another HTML element.

Use a Fragment:

```
function App() {
    return (
        <>
            <h1>React</h1>
            <p>Learning React is fun!</p>
        </>
    );
}
```

***

# 4. React Components

Components are the building blocks of React applications.

A component is normally a JavaScript function that returns JSX.

Example:

```
function Welcome() {
    return <h1>Welcome to React!</h1>;
}
```

Use the component:

```
function App() {
    return (
        <div>
            <Welcome />
            <Welcome />
            <Welcome />
        </div>
    );
}
```

The output contains three welcome headings.

## 4.1 Component naming conventions

React component names should start with an uppercase letter.

Correct:

```
function Header() {
    return <h1>My Application</h1>;
}
```

Incorrect:

```
function header() {
    return <h1>My Application</h1>;
}
```

## 4.2 Creating reusable components

Let's create a character card.

```
function CharacterCard() {

    return (
        <div>
            <h2>Luke Skywalker</h2>
            <p>Species: Human</p>
            <p>Homeworld: Tatooine</p>
        </div>
    );

}
```

Now reuse it:

```
function App() {

    return (
        <>
            <CharacterCard />
            <CharacterCard />
        </>
    );

}
```

In a real application, we would pass different character information through props.

***

# 5. Props – Passing Data Between Components

Props means properties.

Props allow a parent component to pass information to a child component.

Think of props as function arguments.

## 5.1 Basic example

```
function Welcome(props) {

    return (
        <h1>Hello {props.name}!</h1>
    );

}

function App() {

    return (
        <>
            <Welcome name="Luke" />
            <Welcome name="Leia" />
            <Welcome name="Han Solo" />
        </>
    );

}
```

Output:

```
Hello Luke!
Hello Leia!
Hello Han Solo!
```

## 5.2 Destructuring props

Instead of writing `props.name`, we can destructure the object.

```
function Welcome({ name }) {

    return (
        <h1>Hello {name}!</h1>
    );

}
```

This is a common React coding style.

## 5.3 Multiple props

```
function CharacterCard({ name, species, planet }) {

    return (
        <div>
            <h2>{name}</h2>
            <p>Species: {species}</p>
            <p>Planet: {planet}</p>
        </div>
    );

}

function App() {

    return (
        <CharacterCard
            name="Luke Skywalker"
            species="Human"
            planet="Tatooine"
        />
    );

}
```

## 5.4 Props are read-only

A child component should never directly modify its props.

Props are inputs to a component.

If a component needs to manage changing information, use state.

Remember:

* Props: Data received from a parent.

* State: Data managed by a component.

***

# 6. State – Managing Changing Data

State is one of the most important concepts in React.

State represents information that can change during the lifetime of a component.

Examples:

* Counter values.

* User input.

* Shopping cart contents.

* Selected products.

* Login status.

* Application settings.

React provides the `useState` Hook to manage component state.

## 6.1 Your first React counter

```
function Counter() {

    const [count, setCount] = React.useState(0);

    return (
        <div>

            <h1>Counter: {count}</h1>

            <button onClick={() => setCount(count + 1)}>
                Increase
            </button>

        </div>
    );

}
```

Let's understand this line:

```
const [count, setCount] = React.useState(0);
```

It creates two things:

| Element    | Meaning                  |
| ---------- | ------------------------ |
| `count`    | Current state value      |
| `setCount` | Function to update state |
| `0`        | Initial state value      |

The state flow:

```
User clicks button
       |
       v
setCount(count + 1)
       |
       v
React updates state
       |
       v
React renders component again
       |
       v
New counter value appears
```

## 6.2 Complete counter

```
function Counter() {

    const [count, setCount] = React.useState(0);

    function increase() {
        setCount(previous => previous + 1);
    }

    function decrease() {
        setCount(previous => previous - 1);
    }

    function reset() {
        setCount(0);
    }

    return (
        <div>

            <h1>Counter: {count}</h1>

            <button onClick={increase}>Increase</button>

            <button onClick={decrease}>Decrease</button>

            <button onClick={reset}>Reset</button>

        </div>
    );

}
```

Notice this syntax:

```
setCount(previous => previous + 1);
```

This is called a functional state update.

It calculates the next state using the previous state. This is particularly useful when updates depend on previous values.

## 6.3 Multiple state variables

A component can have multiple state variables.

```
function UserProfile() {

    const [name, setName] = React.useState("Karl");

    const [age, setAge] = React.useState(30);

    return (
        <div>
            <h2>{name}</h2>
            <p>Age: {age}</p>

            <button onClick={() => setAge(age + 1)}>
                Increase age
            </button>
        </div>
    );

}
```

**Important:** Never modify React state directly.

Wrong:

```
count = count + 1;
```

Correct:

```
setCount(count + 1);
```

***

# 7. Event Handling

React allows components to respond to user interactions.

Examples:

* Clicking buttons.

* Typing into input fields.

* Submitting forms.

* Selecting options.

* Moving the mouse.

## 7.1 Click events

```
function App() {

    function sayHello() {
        alert("Hello React!");
    }

    return (
        <button onClick={sayHello}>
            Click me
        </button>
    );

}
```

Notice:

```
onClick={sayHello}
```

We pass the function reference, not the result of calling the function.

Incorrect:

```
<button onClick={sayHello()}>
```

## 7.2 Passing arguments to event handlers

```
function App() {

    function greet(name) {
        alert("Hello " + name);
    }

    return (
        <button onClick={() => greet("Luke")}>
            Greet Luke
        </button>
    );

}
```

## 7.3 Common React events

| React event    | Description            |
| -------------- | ---------------------- |
| `onClick`      | Mouse click            |
| `onChange`     | Input value changes    |
| `onSubmit`     | Form submission        |
| `onMouseEnter` | Mouse enters element   |
| `onMouseLeave` | Mouse leaves element   |
| `onKeyDown`    | Keyboard key pressed   |
| `onFocus`      | Element receives focus |
| `onBlur`       | Element loses focus    |

***

# 8. Conditional Rendering

Sometimes a component should display different content depending on application state.

Example: Show a welcome message only when a user is logged in.

## 8.1 Using if statements

```
function WelcomeMessage({ loggedIn }) {

    if (loggedIn) {
        return <h1>Welcome back!</h1>;
    }

    return <h1>Please log in.</h1>;

}
```

## 8.2 Using the ternary operator

```
function App() {

    const [loggedIn, setLoggedIn] = React.useState(false);

    return (
        <div>

            {loggedIn
                ? <h1>Welcome back!</h1>
                : <h1>Please log in.</h1>
            }

            <button onClick={() => setLoggedIn(!loggedIn)}>
                Toggle login
            </button>

        </div>
    );

}
```

## 8.3 Using logical AND

```
function App() {

    const [visible, setVisible] = React.useState(false);

    return (
        <div>

            <button onClick={() => setVisible(!visible)}>
                Toggle message
            </button>

            {visible && <p>Hello from React!</p>}

        </div>
    );

}
```

***

# 9. Rendering Lists

React applications frequently display collections of information.

For example:

* Products.

* Customers.

* Employees.

* Star Wars characters.

* Orders.

JavaScript's `map()` method is commonly used to generate lists.

## 9.1 Your first list

```
function App() {

    const characters = [
        "Luke Skywalker",
        "Leia Organa",
        "Han Solo",
        "Darth Vader"
    ];

    return (
        <ul>

            {characters.map(character => (
                <li key={character}>
                    {character}
                </li>
            ))}

        </ul>
    );

}
```

## 9.2 Rendering objects

```
function App() {

    const characters = [
        { id: 1, name: "Luke Skywalker", planet: "Tatooine" },
        { id: 2, name: "Leia Organa", planet: "Alderaan" },
        { id: 3, name: "Han Solo", planet: "Corellia" }
    ];

    return (
        <div>

            {characters.map(character => (

                <div key={character.id}>

                    <h2>{character.name}</h2>

                    <p>{character.planet}</p>

                </div>

            ))}

        </div>
    );

}
```

## 9.3 Understanding the key property

React needs a stable identity for each item in a rendered list.

That is why we use:

```
key={character.id}
```

Keys help React identify which items were added, removed, or changed.

Prefer unique, stable IDs.

Avoid using array indexes as keys when list items can be reordered, inserted, or deleted.

***

# 10. Handling Forms and User Input

Forms are essential for interactive applications.

Examples:

* Login forms.

* Registration forms.

* Search fields.

* Contact forms.

* Configuration forms.

## 10.1 Controlled components

A controlled input is an input whose value is managed by React state.

```
function App() {

    const [name, setName] = React.useState("");

    return (
        <div>

            <input
                type="text"
                value={name}
                onChange={event => setName(event.target.value)}
                placeholder="Enter your name"
            />

            <h2>Hello {name}!</h2>

        </div>
    );

}
```

The data flow:

```
User types text
       |
       v
onChange event
       |
       v
setName(event.target.value)
       |
       v
React updates state
       |
       v
Component renders again
       |
       v
Updated text appears
```

## 10.2 Handling form submission

```
function App() {

    const [name, setName] = React.useState("");

    function handleSubmit(event) {

        event.preventDefault();

        alert("Hello " + name);

    }

    return (
        <form onSubmit={handleSubmit}>

            <input
                value={name}
                onChange={event => setName(event.target.value)}
                placeholder="Your name"
            />

            <button type="submit">
                Submit
            </button>

        </form>
    );

}
```

Why use:

```
event.preventDefault();
```

Because the browser normally submits a form using its default behavior, which can reload the page.

We prevent that behavior and handle the submission with React.

***

# 11. The useEffect Hook

`useEffect` is used to synchronize a component with external systems.

Examples:

* Fetching data from an API.

* Subscribing to events.

* Working with timers.

* Connecting to external services.

* Synchronizing with browser APIs.

Importantly, not every calculation belongs in an effect. Values that can be calculated from existing props or state should normally be calculated during rendering.

## 11.1 Basic example

```
function App() {

    React.useEffect(() => {

        console.log("Component effect executed");

    }, []);

    return <h1>Hello React!</h1>;

}
```

The empty dependency array means the effect is set up after the component is initially mounted.

In development, React Strict Mode can intentionally run an additional setup-and-cleanup cycle to help identify problems.

## 11.2 Dependency array

Consider:

```
React.useEffect(() => {

    console.log("Count changed:", count);

}, [count]);
```

The effect runs after the initial mount and whenever `count` changes.

Comparison:

| Dependency          | Behavior                             |
| ------------------- | ------------------------------------ |
| `[]`                | Initial mount                        |
| `[count]`           | Initial mount and when count changes |
| No dependency array | After every render                   |

## 11.3 Cleanup function

Some effects need cleanup.

For example, when using timers or event listeners.

```
function App() {

    React.useEffect(() => {

        const timer = setInterval(() => {
            console.log("Timer running...");
        }, 1000);

        return () => {
            clearInterval(timer);
        };

    }, []);

    return <h1>Timer example</h1>;

}
```

The cleanup function prevents the timer from continuing after the component is removed.

***

# 12. Fetching Data from an API

Real applications frequently retrieve data from backend services.

React works very well with REST APIs.

We can use the JavaScript Fetch API.

Let's use the public Star Wars API (SWAPI).

Website:

<https://swapi.dev/>

## 12.1 Fetching characters

```
function App() {

    const [people, setPeople] = React.useState([]);

    const [loading, setLoading] = React.useState(true);

    React.useEffect(() => {

        async function loadPeople() {

            try {

                const response = await fetch(
                    "https://swapi.dev/api/people/"
                );

                if (!response.ok) {
                    throw new Error("API request failed");
                }

                const data = await response.json();

                setPeople(data.results);

            } catch (error) {

                console.error(error);

            } finally {

                setLoading(false);

            }

        }

        loadPeople();

    }, []);

    if (loading) {
        return <h1>Loading...</h1>;
    }

    return (
        <div>

            <h1>Star Wars Characters</h1>

            {people.map(person => (

                <div key={person.url}>

                    <h2>{person.name}</h2>

                    <p>Height: {person.height} cm</p>

                </div>

            ))}

        </div>
    );

}
```

## 12.2 Understanding the data flow

```
React component mounts
          |
          v
      useEffect
          |
          v
    Fetch API request
          |
          v
    Backend API / SWAPI
          |
          v
      JSON response
          |
          v
      setPeople()
          |
          v
      State changes
          |
          v
    React re-renders
          |
          v
    Characters displayed
```

This is a fundamental pattern in modern frontend development.

***

# 13. The useRef Hook

`useRef` provides a way to hold a value between renders without triggering a re-render when that value changes.

It is also commonly used to access DOM elements.

Example:

```
function App() {

    const inputRef = React.useRef(null);

    function focusInput() {

        inputRef.current.focus();

    }

    return (
        <div>

            <input
                ref={inputRef}
                placeholder="Enter text"
            />

            <button onClick={focusInput}>
                Focus input
            </button>

        </div>
    );

}
```

The button places the cursor inside the input field.

Important difference:

| Hook        | Purpose                                              |
| ----------- | ---------------------------------------------------- |
| `useState`  | Stores changing UI state                             |
| `useEffect` | Synchronizes with external systems                   |
| `useRef`    | Stores persistent values and references DOM elements |

***

# 14. Sharing State Between Components

Suppose two child components need the same information.

Where should the state live?

A common solution is called **lifting state up**.

Example:

```
          App
           |
       count state
           |
      +----+----+
      |         |
  Counter   Display
      |         |
  setCount   count
```

Implementation:

```
function Counter({ count, setCount }) {

    return (
        <button onClick={() => setCount(count + 1)}>
            Increase
        </button>
    );

}

function Display({ count }) {

    return <h2>Count: {count}</h2>;

}

function App() {

    const [count, setCount] = React.useState(0);

    return (
        <div>

            <Counter
                count={count}
                setCount={setCount}
            />

            <Display count={count} />

        </div>
    );

}
```

Now both components share the same state.

This is an important React architectural principle.

***

# 15. The useContext Hook

Passing props through many layers can become inconvenient.

This is sometimes called prop drilling.

React Context provides another way to share information across a component tree.

## 15.1 Creating a context

```
const ThemeContext = React.createContext();

function App() {

    const [theme, setTheme] = React.useState("light");

    return (
        <ThemeContext.Provider value={{ theme, setTheme }}>

            <Toolbar />

        </ThemeContext.Provider>
    );

}
```

## 15.2 Consuming context

```
function Toolbar() {

    const { theme, setTheme } =
        React.useContext(ThemeContext);

    return (
        <div>

            <h2>Current theme: {theme}</h2>

            <button
                onClick={() =>
                    setTheme(theme === "light" ? "dark" : "light")
                }
            >
                Change theme
            </button>

        </div>
    );

}
```

Context is useful for information such as:

* Current user.

* Application theme.

* Language preferences.

* Authentication information.

Do not use Context automatically for every state variable. Local state is often simpler.

***

# 16. The useReducer Hook

When state logic becomes more complicated, `useReducer` can be useful.

It follows a pattern similar to Redux.

The main elements are:

* State.

* Action.

* Reducer.

* Dispatch.

## 16.1 Basic reducer

```
function reducer(state, action) {

    switch (action.type) {

        case "INCREMENT":
            return { count: state.count + 1 };

        case "DECREMENT":
            return { count: state.count - 1 };

        case "RESET":
            return { count: 0 };

        default:
            return state;

    }

}
```

## 16.2 Using useReducer

```
function App() {

    const [state, dispatch] = React.useReducer(
        reducer,
        { count: 0 }
    );

    return (
        <div>

            <h1>Count: {state.count}</h1>

            <button onClick={() => dispatch({ type: "INCREMENT" })}>
                Increase
            </button>

            <button onClick={() => dispatch({ type: "DECREMENT" })}>
                Decrease
            </button>

            <button onClick={() => dispatch({ type: "RESET" })}>
                Reset
            </button>

        </div>
    );

}
```

## 16.3 Understanding the reducer flow

```
User interaction
       |
       v
dispatch(action)
       |
       v
    Reducer
       |
       v
New state returned
       |
       v
React updates component
       |
       v
Updated UI
```

This pattern is particularly useful when multiple actions can modify related state.

***

# 17. Component Lifecycle

React components have a lifecycle.

A simplified conceptual model contains three phases:

```
      MOUNT
        |
        v
      UPDATE
        |
        v
     UNMOUNT
```

**Mount:** The component is added to the UI.

**Update:** The component renders again because its props or state changed.

**Unmount:** The component is removed from the UI.

Function components use Hooks such as `useEffect` to synchronize with external systems during this lifecycle.

Remember that React rendering and effect execution are separate concepts.

***

# 18. Styling React Components

React supports several ways of styling components.

## 18.1 Normal CSS

Create a file:

```
style.css
```

Example:

```
.container {
    max-width: 800px;
    margin: auto;
    padding: 20px;
}

.heading {
    color: darkblue;
}

.button {
    padding: 10px 20px;
    background-color: steelblue;
    color: white;
    border: none;
    cursor: pointer;
}
```

In a Vite project:

```
import "./style.css";
```

In the browser-only CDN example, add a normal `<link>` element in the HTML `<head>`:

```
<link rel="stylesheet" href="style.css">
```

Use the classes in JSX:

```
function App() {

    return (
        <div className="container">

            <h1 className="heading">
                My React Application
            </h1>

            <button className="button">
                Click me
            </button>

        </div>
    );

}
```

## 18.2 Inline styling

```
function App() {

    return (
        <h1 style={{ color: "red", fontSize: "30px" }}>
            Hello React!
        </h1>
    );

}
```

Notice that CSS properties use camelCase:

```
fontSize
backgroundColor
marginTop
```

***

# 19. React Project Structure

A typical Vite React application looks like this:

```
my-react-app/
│
├── public/
│
├── src/
│   │
│   ├── assets/
│   │
│   ├── components/
│   │   ├── Header.jsx
│   │   ├── Footer.jsx
│   │   └── CharacterCard.jsx
│   │
│   ├── App.jsx
│   │
│   ├── main.jsx
│   │
│   └── index.css
│
├── index.html
├── package.json
└── vite.config.js
```

Important files:

| File           | Responsibility                   |
| -------------- | -------------------------------- |
| `main.jsx`     | Application entry point          |
| `App.jsx`      | Main application component       |
| `index.css`    | Global CSS                       |
| `components/`  | Reusable UI components           |
| `package.json` | Project dependencies and scripts |
| `index.html`   | HTML entry document              |

## 19.1 Understanding main.jsx

A typical React entry point:

```
import React from "react";
import ReactDOM from "react-dom/client";

import App from "./App.jsx";

import "./index.css";

ReactDOM.createRoot(
    document.getElementById("root")
).render(
    <React.StrictMode>
        <App />
    </React.StrictMode>
);
```

This is where React connects your application to the HTML document.

***

# 20. React Best Practices

Some important principles to remember:

1. Keep components small and focused.

2. Use meaningful component names.

3. Avoid unnecessary state.

4. Never modify state directly.

5. Use stable keys when rendering lists.

6. Keep components reusable.

7. Separate business logic from presentation when appropriate.

8. Avoid unnecessary effects.

9. Handle loading and error states when fetching data.

10. Keep your application structure understandable.

## 20.1 The single responsibility principle

A component should ideally have one clear responsibility.

For example:

```
CharacterPage
    |
    +-- CharacterList
            |
            +-- CharacterCard
```

This is easier to maintain than one giant component containing everything.

***

# 21. Practical Exercises

Work through these exercises before looking at the solutions.

## Exercise 1 – Hello React

Create a component that displays:

```
Hello React!
I am learning frontend development.
```

Requirements:

* Create an `App` component.

* Use JSX.

* Display two HTML elements.

## Exercise 2 – Personal Profile

Create a component that displays:

* Name.

* Age.

* Profession.

* Country.

Requirements:

* Use props.

* Create a reusable `Profile` component.

## Exercise 3 – Counter Application

Build a counter with:

* Increase button.

* Decrease button.

* Reset button.

Requirements:

* Use `useState`.

* Use event handlers.

* Display the current counter value.

## Exercise 4 – Todo Application

Build a simple todo list.

Requirements:

* Input field.

* Add button.

* Display tasks.

* Delete tasks.

* Use state.

Hint: Store your tasks in an array.

## Exercise 5 – Star Wars Character List

Create a list of characters.

Requirements:

* Use an array of objects.

* Use `map()`.

* Create a reusable `CharacterCard`.

* Use props.

* Use stable keys.

## Exercise 6 – API Integration

Retrieve Star Wars characters from:

<https://swapi.dev/api/people/>

Requirements:

* Use Fetch API.

* Use `useEffect`.

* Display loading information.

* Handle errors.

* Display character names.

***

# 22. Mini Project – Star Wars Character Explorer

Now combine everything you have learned.

## Project goal

Build a small Star Wars application.

The application should display characters retrieved from SWAPI.

### Features

* Display a heading.

* Retrieve characters from the API.

* Display character names.

* Display character height.

* Display character gender.

* Show a loading message.

* Handle API errors.

* Provide a search field.

### Suggested component structure

```
StarWarsApp
│
├── Header
│
├── SearchBar
│
├── CharacterList
│   │
│   └── CharacterCard
│
└── Footer
```

### Suggested development steps

1. Create the React project.

2. Create the `Header` component.

3. Create the `CharacterCard` component.

4. Create the `CharacterList` component.

5. Retrieve data using Fetch API.

6. Add loading and error handling.

7. Add search functionality.

8. Add CSS styling.

### Challenge

Extend the application with:

* Character detail views.

* Planet information.

* Sorting by height.

* Pagination.

* A dark mode.

***

# 23. Important React Terminology

| Term             | Explanation                                           |
| ---------------- | ----------------------------------------------------- |
| React            | JavaScript UI library                                 |
| Component        | Reusable UI building block                            |
| JSX              | HTML-like syntax inside JavaScript                    |
| Props            | Data passed from parent to child                      |
| State            | Component-managed changing data                       |
| Hook             | Function providing React capabilities                 |
| useState         | Manages component state                               |
| useEffect        | Synchronizes with external systems                    |
| useRef           | Stores persistent values and DOM references           |
| useContext       | Reads shared context                                  |
| useReducer       | Manages state using a reducer                         |
| Rendering        | Producing the component UI                            |
| Re-rendering     | Rendering again after relevant changes                |
| DOM              | Document Object Model                                 |
| Virtual DOM      | Common conceptual model for React's UI reconciliation |
| Reconciliation   | React's process of determining necessary UI updates   |
| Key              | Stable identity for list items                        |
| Prop drilling    | Passing props through intermediate components         |
| Lifting state up | Moving shared state to a common parent                |

***

# 24. Recommended Learning Roadmap

Follow this sequence:

| Phase | Topic                      | Priority     |
| ----- | -------------------------- | ------------ |
| 1     | JavaScript fundamentals    | Essential    |
| 2     | JSX                        | Essential    |
| 3     | Functional components      | Essential    |
| 4     | Props                      | Essential    |
| 5     | useState                   | Essential    |
| 6     | Event handling             | Essential    |
| 7     | Conditional rendering      | Essential    |
| 8     | Lists and keys             | Essential    |
| 9     | Forms                      | Essential    |
| 10    | useEffect                  | Essential    |
| 11    | Fetch API                  | Essential    |
| 12    | useRef                     | Intermediate |
| 13    | useContext                 | Intermediate |
| 14    | useReducer                 | Intermediate |
| 15    | Project architecture       | Intermediate |
| 16    | React Router               | Advanced     |
| 17    | Performance optimization   | Advanced     |
| 18    | Testing                    | Advanced     |
| 19    | TypeScript with React      | Advanced     |
| 20    | State management libraries | Advanced     |

***

# 25. Recommended Official Resources

Use these resources as your primary references.

1. [React Official Documentation](https://react.dev/)

2. [React – Learn](https://react.dev/learn)

3. [React – Quick Start](https://react.dev/learn)

4. [Vite Documentation](https://vite.dev/)

5. [JavaScript MDN Documentation](https://developer.mozilla.org/en-US/docs/Web/JavaScript)

6. [SWAPI – Star Wars API](https://swapi.dev/)

**My recommendation:** Spend most of your initial learning time on the official React documentation, especially the sections about components, JSX, props, state, and Hooks.

***

# 26. Zettelkasten Notes – Suggested Structure

I recommend splitting this large tutorial into smaller interconnected notes.

```
React/
│
├── 00 - React Learning Roadmap.md
│
├── 01 - What is React.md
├── 02 - React Environment Setup.md
├── 03 - Understanding JSX.md
├── 04 - React Components.md
├── 05 - Understanding Props.md
├── 06 - Understanding State.md
├── 07 - React Event Handling.md
├── 08 - Conditional Rendering.md
├── 09 - Rendering Lists and Keys.md
├── 10 - React Forms.md
├── 11 - useEffect Hook.md
├── 12 - Fetching API Data.md
├── 13 - useRef Hook.md
├── 14 - Lifting State Up.md
├── 15 - useContext Hook.md
├── 16 - useReducer Hook.md
├── 17 - React Component Lifecycle.md
├── 18 - React Styling.md
├── 19 - React Project Structure.md
├── 20 - React Best Practices.md
│
└── Projects/
    ├── 01 - Hello React.md
    ├── 02 - Counter Application.md
    ├── 03 - Todo Application.md
    └── 04 - Star Wars Explorer.md
```

## Suggested Zettelkasten connections

Connect your React notes to existing knowledge:

```
JavaScript
    |
    +-- Functions
    +-- Arrow Functions
    +-- Objects
    +-- Arrays
    +-- Array.map()
    +-- Destructuring
    +-- Promises
    +-- async/await
    +-- Fetch API
          |
          v
        React
          |
          +-- JSX
          +-- Components
          +-- Props
          +-- State
          +-- Hooks
          +-- API Integration
```

This creates a knowledge network instead of a collection of isolated tutorials.

***

# Final Learning Advice

Do not try to memorize all React Hooks immediately.

Start with these five concepts:

1. JSX

2. Components

3. Props

4. State (`useState`)

5. Events

Once you understand these five concepts, React becomes considerably easier to understand.

**The most important thing:** Write code yourself. Change examples, break them, fix them, and experiment.

Happy learning! 🚀

## My suggested next step

I recommend turning this tutorial into a 30-Day React Absolute Beginner Bootcamp, with one practical lesson and coding exercise per day.

That way, you'll gradually build your own Star Wars Explorer while creating interconnected Zettelkasten notes.

Happy coding! 😊

Would you like a fresh React exercise delivered every morning?

⚛️Daily React learning exerciseZum Einrichten tippen

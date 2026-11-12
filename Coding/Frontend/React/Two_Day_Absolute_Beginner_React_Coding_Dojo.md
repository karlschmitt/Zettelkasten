---
id: 20261112141246
title: Two-Day Absolute Beginner React Coding Dojo
author: Karl Schmitt
date: 2026-11-12
keywords: [ React ]
---

# Two-Day Absolute Beginner React Coding Dojo

**From zero to a working React application**

* Level: Absolute beginner

* Duration: 2 days

* Approach: Learn by coding

* Tools: Visual Studio Code, PowerShell, Microsoft Edge

* Runtime: React 18 through browser CDN scripts

* Final project: React Developer Dashboard

***

# 1. Coding Dojo — How to work

A Coding Dojo is a practical programming workshop. Instead of only reading tutorials, you solve small programming challenges.

For each exercise, follow this cycle:

1. **Understand:** Read the task.

2. **Plan:** Think about the solution.

3. **Code:** Write the solution yourself.

4. **Run:** Open the application in Edge.

5. **Test:** Try different inputs and actions.

6. **Improve:** Refactor your code.

7. **Reflect:** Write down what you learned.

Don't worry about making mistakes. Debugging is part of programming!

## Learning objectives

By the end of these two days, you should understand:

* What React is and why it is useful.

* JSX and functional components.

* Component composition.

* Props and the `children` prop.

* State and the `useState` Hook.

* Event handling.

* Conditional rendering.

* Rendering lists with `map()`.

* Controlled form inputs.

* The `useEffect` Hook.

* Fetching data from a REST API.

* Basic React application architecture.

***

# 2. Prepare your development environment

## Step 1 — Create a project directory

Open PowerShell:

```
New-Item -ItemType Directory -Force -Path D:\CodingDojo\ReactDojo
Set-Location D:\CodingDojo\ReactDojo
code .
```

If the `code` command is unavailable, open Visual Studio Code and select the folder manually.

## Step 2 — Create index.html

Create a file named `index.html`:

```
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>React Coding Dojo</title>
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

## Step 3 — Create app.js

Create a file named `app.js`:

```
function App() {
    return (
        <div>
            <h1>React Coding Dojo</h1>
            <p>My first React application!</p>
        </div>
    );
}

const root = ReactDOM.createRoot(
    document.getElementById("root")
);

root.render(<App />);
```

## Step 4 — Run the application

Open `index.html` in Microsoft Edge.

You should see:

```
React Coding Dojo

My first React application!
```

**Important:** This CDN setup is for learning React fundamentals without installing Node.js or Deno. It is not the recommended setup for production applications. It also requires network access to the CDN addresses. Follow your organisation's security policies if any resources are blocked.

***

# DAY 1 — React Fundamentals and Interaction

\<time>Suggested duration: 5–6 hours, including breaks\</time>

## Mission 1 — Understand React and JSX

**Learning objective:** Understand how React displays an interface.

### Challenge 1.1 — Your first React component

Replace the contents of `app.js`:

```
function App() {
    return (
        <div>
            <h1>Welcome to React!</h1>
            <h2>My Coding Dojo</h2>
            <p>I am learning React step by step.</p>
        </div>
    );
}

const root = ReactDOM.createRoot(
    document.getElementById("root")
);

root.render(<App />);
```

### Your task

* Change the heading.

* Add three paragraphs.

* Add an unordered list containing three programming languages.

* Display a JavaScript expression inside JSX.

Example:

```
<p>Calculation: {10 + 20}</p>
```

### Questions

1. What is JSX?

2. Why do we use curly braces in JSX?

3. What is the purpose of the `App` function?

4. What does `root.render()` do?

***

## Mission 2 — Functional components

**Learning objective:** Divide an application into reusable components.

### Challenge 2.1 — Create three components

Implement the following components:

```
function Header() {
    return <h1>Developer Dashboard</h1>;
}

function MainContent() {
    return <p>Welcome to your dashboard.</p>;
}

function Footer() {
    return <small>React Coding Dojo</small>;
}
```

Now compose them inside `App`:

```
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

### Your task

Create an additional component named `WelcomeMessage`.

It should display:

```
Hello, Developer!
Welcome to your learning dashboard.
```

Add it to `App`.

### Questions

1. What is a React component?

2. Why do component names begin with uppercase letters?

3. What is component composition?

4. What is a Fragment?

***

## Mission 3 — Props

**Learning objective:** Pass data from parent components to child components.

### Challenge 3.1 — Create a reusable profile component

```
function DeveloperProfile(props) {
    return (
        <div>
            <h2>{props.name}</h2>
            <p>Programming language: {props.language}</p>
        </div>
    );
}
```

Use the component:

```
function App() {
    return (
        <>
            <DeveloperProfile
                name="Ada"
                language="JavaScript"
            />

            <DeveloperProfile
                name="Grace"
                language="Java"
            />

            <DeveloperProfile
                name="Linus"
                language="C++"
            />
        </>
    );
}
```

### Your task

Extend the component with two additional props:

* `experience`

* `country`

Display all four properties.

### Bonus challenge

Rewrite the component using destructuring:

```
function DeveloperProfile({ name, language }) {
    return (
        <div>
            <h2>{name}</h2>
            <p>{language}</p>
        </div>
    );
}
```

### Questions

1. What are props?

2. Which component passes the props?

3. Which component receives the props?

4. Should a child component modify its props?

***

## Mission 4 — State and useState

**Learning objective:** Understand how React handles changing data.

This is one of the most important React concepts!

### Challenge 4.1 — Build a counter

```
function Counter() {

    const [count, setCount] = React.useState(0);

    function increase() {
        setCount(count + 1);
    }

    return (
        <div>
            <h2>Counter: {count}</h2>

            <button onClick={increase}>
                Increase
            </button>
        </div>
    );
}
```

Render it:

```
function App() {
    return (
        <>
            <h1>React Counter</h1>
            <Counter />
        </>
    );
}
```

### Your task

Add three buttons:

* Increase

* Decrease

* Reset

The counter should start at zero.

### Bonus challenge

Implement an `Increase by 5` button using a functional state update:

```
setCount(previousCount => previousCount + 5);
```

### Questions

1. What is state?

2. What does `useState()` return?

3. What is the purpose of `setCount()`?

4. Why should you not directly modify state?

5. Why does React render the component again after a state update?

***

## Mission 5 — Event handling

**Learning objective:** React to user interaction.

### Challenge 5.1 — Create a greeting application

```
function Greeting() {

    const [message, setMessage] = React.useState(
        "Press the button!"
    );

    function sayHello() {
        setMessage("Hello from React!");
    }

    return (
        <div>
            <h2>{message}</h2>

            <button onClick={sayHello}>
                Say Hello
            </button>
        </div>
    );
}
```

### Your task

Add:

* A button that displays `Good morning!`

* A button that displays `Good evening!`

* A button that resets the message.

### Questions

1. What is an event handler?

2. What does `onClick` do?

3. Why do we write `onClick={sayHello}` instead of `onClick={sayHello()}`?

***

## Mission 6 — Conditional rendering

**Learning objective:** Display different content depending on state.

### Challenge 6.1 — Build a login status component

```
function LoginStatus() {

    const [loggedIn, setLoggedIn] = React.useState(false);

    return (
        <div>
            {loggedIn
                ? <h2>Welcome back!</h2>
                : <h2>Please log in.</h2>
            }

            <button
                onClick={() => setLoggedIn(value => !value)}
            >
                Toggle Login
            </button>
        </div>
    );
}
```

### Your task

Create a component that displays:

* `System offline` when the application is offline.

* `System online` when the application is online.

Add a button to switch between these states.

### Questions

1. What is conditional rendering?

2. What is the ternary operator?

3. How can you use `&&` in JSX?

***

## Mission 7 — Day 1 final challenge

\<badge color="success">Day 1 practical project\</badge>

### Build a Developer Profile Dashboard

Create a small dashboard with the following structure:

```
App
├── Header
├── DeveloperProfile
├── SkillList
├── Counter
└── Footer
```

### Requirements

**Header**

Display:

```
My Developer Dashboard
```

**DeveloperProfile**

Display:

* Developer name

* Programming language

* Learning goal

Use props.

**SkillList**

Display at least four programming skills.

**Counter**

Display the number of completed exercises.

Add buttons to increase and reset the counter.

**Footer**

Display:

```
Day 1 completed!
```

### Day 1 review

* I understand JSX.

* I can create functional components.

* I can compose components.

* I understand props.

* I understand state.

* I can use `useState`.

* I can handle button clicks.

* I understand conditional rendering.

* I completed the Developer Dashboard.

***

# DAY 2 — Lists, Forms, Hooks, APIs and Architecture

\<time>Suggested duration: 5–6 hours, including breaks\</time>

## Mission 8 — Rendering lists with map()

**Learning objective:** Render dynamic lists from JavaScript arrays.

### Challenge 8.1 — Create a programming language list

```
function LanguageList() {

    const languages = [
        "Java",
        "JavaScript",
        "C++",
        "Python"
    ];

    return (
        <ul>
            {languages.map(language => (
                <li key={language}>
                    {language}
                </li>
            ))}
        </ul>
    );
}
```

### Your task

Create a list of five programming books.

Each book should contain:

* ID

* Title

* Author

Display all books using `map()`.

### Bonus challenge

Add a search input to filter the books by title.

### Questions

1. What does `map()` do?

2. Why does React need keys?

3. Why should keys be stable and unique among siblings?

***

## Mission 9 — Controlled forms

**Learning objective:** Connect HTML inputs to React state.

### Challenge 9.1 — Build a name input

```
function NameForm() {

    const [name, setName] = React.useState("");

    return (
        <div>
            <label>
                Your name:

                <input
                    value={name}
                    onChange={event =>
                        setName(event.target.value)
                    }
                />
            </label>

            <p>Hello, {name || "stranger"}!</p>
        </div>
    );
}
```

### Your task

Build a developer registration form with:

* Name

* Email

* Programming language

* Submit button

Display the submitted information on the page.

Remember to prevent the browser's default form submission:

```
function handleSubmit(event) {
    event.preventDefault();

    // Handle the form data here.
}
```

### Questions

1. What is a controlled input?

2. What does `onChange` do?

3. What is `event.target.value`?

4. Why do we use `preventDefault()`?

***

## Mission 10 — useReducer

**Learning objective:** Understand an alternative way to manage state.

A reducer receives the current state and an action. It returns the next state.

### Challenge 10.1 — Create a reducer counter

```
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

Use the reducer:

```
function Counter() {

    const [state, dispatch] = React.useReducer(
        counterReducer,
        { count: 0 }
    );

    return (
        <div>
            <h2>{state.count}</h2>

            <button
                onClick={() => dispatch({ type: "increment" })}
            >
                Increase
            </button>

            <button
                onClick={() => dispatch({ type: "decrement" })}
            >
                Decrease
            </button>

            <button
                onClick={() => dispatch({ type: "reset" })}
            >
                Reset
            </button>
        </div>
    );
}
```

### Your task

Add a new action:

```
case "increaseByFive":
    return { count: state.count + 5 };
```

Create a button that dispatches this action.

### Questions

1. What is a reducer?

2. What is an action?

3. What does `dispatch()` do?

4. When might `useReducer` be preferable to `useState`?

***

## Mission 11 — useEffect

**Learning objective:** Understand Effects and synchronization with external systems.

### Challenge 11.1 — Update the browser title

```
function App() {

    const [name, setName] = React.useState("");

    React.useEffect(() => {
        document.title = name
            ? `Hello ${name}`
            : "React Coding Dojo";
    }, [name]);

    return (
        <div>
            <h1>Welcome!</h1>

            <input
                value={name}
                onChange={event =>
                    setName(event.target.value)
                }
                placeholder="Enter your name"
            />
        </div>
    );
}
```

### Your task

Build a simple clock or timer.

Requirements:

* Display elapsed seconds.

* Start the timer.

* Stop the timer.

* Reset the timer.

* Clear the interval when it is no longer needed.

Important: use the cleanup function returned from `useEffect` to clear the interval. Avoid creating multiple intervals accidentally.

### Questions

1. What is `useEffect` used for?

2. What is a dependency array?

3. When does an Effect run?

4. What is an Effect cleanup function?

5. Why must timers be cleaned up?

***

## Mission 12 — Fetch data from a REST API

**Learning objective:** Connect React to an external data source.

We will use JSONPlaceholder, a public testing API.

Endpoint:

```
https://jsonplaceholder.typicode.com/users/1
```

### Challenge 12.1 — Fetch a user

First, understand this JavaScript example:

```
async function loadUser() {

    const response = await fetch(
        "https://jsonplaceholder.typicode.com/users/1"
    );

    if (!response.ok) {
        throw new Error("HTTP error: " + response.status);
    }

    const user = await response.json();

    console.log(user);
}
```

### Challenge 12.2 — Display API data in React

```
function UserProfile() {

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
                    throw new Error(
                        "HTTP error: " + response.status
                    );
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

    if (loading) {
        return <p>Loading...</p>;
    }

    if (error) {
        return <p>Error: {error}</p>;
    }

    if (!user) {
        return <p>No user found.</p>;
    }

    return (
        <div>
            <h2>{user.name}</h2>
            <p>Email: {user.email}</p>
            <p>City: {user.address.city}</p>
        </div>
    );
}
```

### Your task

Extend the user profile:

* Display the user's username.

* Display the user's website.

* Display the company name.

* Display the city.

* Show a loading message.

* Show an error message if the request fails.

### Questions

1. What is a REST API?

2. What is JSON?

3. What does `fetch()` return?

4. Why do we use `await response.json()`?

5. Why do we check `response.ok`?

6. Why do we need loading and error states?

***

## Mission 13 — Build a reusable custom Hook

**Learning objective:** Extract reusable stateful logic.

### Challenge 13.1 — Create useToggle

```
function useToggle(initialValue = false) {

    const [value, setValue] = React.useState(initialValue);

    function toggle() {
        setValue(previousValue => !previousValue);
    }

    return {
        value,
        toggle
    };
}
```

Use it:

```
function Details() {

    const { value, toggle } = useToggle(false);

    return (
        <div>
            <button onClick={toggle}>
                Toggle Details
            </button>

            {value && (
                <p>Here are the hidden details!</p>
            )}
        </div>
    );
}
```

### Your task

Create a custom Hook called `useCounter`.

It should:

* Accept an initial value.

* Provide the current counter.

* Provide an increase function.

* Provide a decrease function.

* Provide a reset function.

### Questions

1. What is a custom Hook?

2. Why do custom Hook names start with `use`?

3. Can multiple components call the same custom Hook?

4. Does calling the same custom Hook automatically share state between components?

***

# 3. Final Day 2 Project — React Developer Dashboard

\<badge color="success">Final coding challenge\</badge>

Now combine everything you have learned.

## Project mission

Build a small Developer Dashboard that displays developer information, learning tasks, and data retrieved from an API.

## Suggested component architecture

```
App
│
├── Header
│
├── DeveloperProfile
│
├── SkillList
│   └── SkillItem
│
├── TodoApp
│   └── TodoItem
│
├── UserProfile
│
└── Footer
```

## Functional requirements

### 1. Header

Display:

```
Developer Learning Dashboard
```

### 2. DeveloperProfile

Display:

* Name

* Favourite programming language

* Current learning goal

Use props.

### 3. SkillList

Display a list of programming skills using `map()`.

### 4. TodoApp

Allow the user to:

* Add a task.

* Display all tasks.

* Mark a task as completed.

* Remove a task.

Use React state.

### 5. UserProfile

Fetch user information from:

```
https://jsonplaceholder.typicode.com/users/1
```

Display:

* Name

* Email

* City

* Company

Include loading and error handling.

### 6. Footer

Display:

```
Two-Day React Coding Dojo — Completed!
```

## Suggested project layout

```
ReactDojo
│
├── index.html
├── app.js
└── styles.css
```

For this beginner CDN project, keep the components in `app.js`. In a modern React project, you would normally split components into separate modules.

***

# 4. Bonus challenges

If you finish early, try these additional tasks.

## Bonus 1 — Dark mode

Add a button that switches between light and dark themes.

Concepts:

* `useState`

* Event handling

* Conditional styling

## Bonus 2 — Character search

Use the Star Wars API:

```
https://swapi.dev/api/people/1/
```

Display the character's name, height, and gender.

Concepts:

* `fetch`

* `useEffect`

* Loading and error states

## Bonus 3 — Persistent Todo list

Use the browser's `localStorage` to keep tasks between page reloads.

Concepts:

* `useState`

* `useEffect`

* Browser storage

Only store non-sensitive practice data.

## Bonus 4 — Component refactoring

Take your Developer Dashboard and move each component into a separate file in a modern React project when an approved build environment becomes available.

***

# 5. Two-Day Progress Tracker

## Day 1 — Fundamentals

* Mission 1 — React and JSX

* Mission 2 — Functional components

* Mission 3 — Props

* Mission 4 — State and useState

* Mission 5 — Event handling

* Mission 6 — Conditional rendering

* Mission 7 — Developer Profile Dashboard

## Day 2 — Practical React

* Mission 8 — Lists and map()

* Mission 9 — Controlled forms

* Mission 10 — useReducer

* Mission 11 — useEffect

* Mission 12 — Fetch and REST APIs

* Mission 13 — Custom Hooks

* Final Project — Developer Dashboard

***

# 6. Zettelkasten Notes

Suggested note titles:

```
React — What Is React?
React — JSX
React — Functional Components
React — Component Composition
React — Props
React — useState
React — Event Handling
React — Conditional Rendering
React — Rendering Lists with map()
React — Controlled Forms
React — useReducer
React — useEffect
React — Effect Cleanup
React — Fetch API Integration
React — Custom Hooks
React — Developer Dashboard Project
```

## Suggested note template

```
# React — Topic

## What is it?

Explain the concept in your own words.

## Why is it useful?

What problem does it solve?

## Example

Add a small code example.

## What did I learn?

Write down your own observations.

## Related concepts

- [[Related React concept]]
- [[JavaScript concept]]

## Open questions

- What do I still need to understand?
```

***

# 7. Final knowledge check

Try answering these questions without looking at the lessons.

1. What is React?

2. What is JSX?

3. What is a component?

4. What is the difference between props and state?

5. What does `useState` return?

6. What is an event handler?

7. Why does React need keys when rendering lists?

8. What is a controlled input?

9. What is the difference between `useState` and `useReducer`?

10. What is `useEffect` used for?

11. Why do Effects sometimes need cleanup?

12. What is a custom Hook?

13. How does React fetch data from a REST API?

14. Why should we display loading and error states?

15. What is component composition?

## Congratulations!

You have completed the two-day React Coding Dojo!

Remember:

* Don't just copy code. Type it yourself.

* Change examples and observe the result.

* Break the code intentionally and practise debugging.

* Explain each concept in your own words.

* Keep your Zettelkasten notes small, focused, and connected.

**The goal is not to memorize React. The goal is to understand how React applications work.**

Happy coding! 🚀

One useful next step would be to work through the dojo interactively, with me acting as your coding mentor and reviewing your solutions after each mission.

Would you like me to prepare a fresh React coding challenge for tomorrow?

💻Daily React coding challengeZum Einrichten tippen

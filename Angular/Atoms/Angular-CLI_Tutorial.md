---
id: 20260425165150
title: Angular CLI Tutorial
author: Karl Schmitt
date: 2026-04-2026
keywords: [ Angular, CLI ]
---

# Einführung

Kein Problem! Wir fangen ganz am Anfang an. Die **Angular CLI** ist ein Werkzeug für deine Kommandozeile (Terminal), das dir hilft, Angular-Websites zu erstellen, zu verwalten und zu testen. Sie nimmt dir die komplizierte Hintergrundarbeit ab, damit du dich direkt auf das Programmieren konzentrieren kannst.

Um loszulegen, sind drei Dinge auf deinem Rechner wichtig:

1. **Node.js**: Die Basis, damit alles läuft.
2. **npm**: Ein Paketmanager, der meist direkt mit Node.js installiert wird.
3. **Ein Texteditor**: Visual Studio Code wird hierfür empfohlen.

Sobald diese Voraussetzungen erfüllt sind, installierst du die CLI mit einem einfachen Befehl in deinem Terminal: `npm install -g @angular/cli`

Soll ich dir zeigen, wie du prüfst, ob Node.js bereits auf deinem Rechner ist, oder möchtest du direkt wissen, wie man das erste Projekt startet?


# Angular CLI Tutorial

The Angular Command Line Interface (CLI) is the essential tool for initializing, developing, scaffolding, and maintaining Angular applications. This tutorial provides the necessary steps and commands to get started with the Angular CLI. [1, 2, 3, 4] 
## 1. Prerequisites
Before installing the CLI, ensure you have the following installed:

* Node.js: The JavaScript runtime.
* npm: The Node package manager, which is included with Node.js.
* Text Editor: [Visual Studio Code](https://code.visualstudio.com/) is highly recommended for Angular development. [5, 6, 7, 8] 

## 2. Installation
To install the Angular CLI globally on your system, open your terminal and run: [9] 

npm install -g @angular/cli


* The -g flag ensures the CLI is available for all projects on your machine.
* Verify Installation: Check the installed version by running ng version or ng v. [2, 5, 10] 

## 3. Creating a New Project
To start a new project, use the ng new command: [11] 

ng new my-angular-app


* The CLI will prompt you for configuration settings, such as adding Angular routing and selecting a stylesheet format (CSS, SCSS, etc.).
* Navigate into your new project directory: cd my-angular-app. [12, 13, 14] 

## 4. Basic Development Commands
Once inside your project folder, use these core commands to manage your application: [15] 

| Command [1, 5, 11, 16, 17, 18, 19] | Shortened Version | Description |
|---|---|---|
| ng serve | ng s | Starts a local development server with hot-reloading at http://localhost:4200. |
| ng build | ng b | Compiles the app into an output directory for production. |
| ng generate <type> <name> | ng g <t> <n> | Scaffolds files like components, services, and modules. |
| ng test | ng t | Runs unit tests using a runner like Karma. |
| ng update | N/A | Updates your application and its dependencies. |

## 5. Generating Core Elements
The ng generate command is used to create specific app parts with the correct boilerplate: [20] 

* Component: ng generate component my-component (or ng g c my-component).
* Service: ng generate service my-service (or ng g s my-service).
* Module: ng generate module my-module.
* Standalone: To generate a standalone component (available in newer versions), add the --standalone flag: ng g c my-comp --standalone. [16, 21, 22, 23, 24] 

### [Hands on Angular CLI tutorial](./Hands_on_Angular_CLI_tutorial.md)

### Video Tutorials

These video tutorials provide visual guidance for setting up the environment, installing the CLI, and running your first project:

[Angular 20 Tutorial for Beginners | Setup Environment ...](https://www.youtube.com/watch?v=oInuPuLVB6Y&t=137), YouTube · LEARNING PARTNER · 1970 M01 1
[The Ultimate Angular Tutorial for Beginners: Getting Started ...](https://www.youtube.com/watch?v=NlGkd7TlBDs&t=0), YouTube · TubeGuruji · 1970 M01 1
[How to Install Angular CLI | VsCode](https://www.youtube.com/watch?v=cyIwRaAH9tQ&t=256), YouTube · Tech Coffee Break · 1970 M01 1
[Intro to Angular #1: Getting Started and Installation!](https://www.youtube.com/watch?v=-R5PFoJhpGI&t=356), YouTube · Ajay Gandecha · 1970 M01 1

Would you like to see how to use the CLI specifically for creating standalone components or configuring routing in your project?

[1] [https://angular.dev](https://angular.dev/tools/cli)
[2] [https://www.tutorialspoint.com](https://www.tutorialspoint.com/angular_cli/index.htm)
[3] [https://www.javappa.com](https://www.javappa.com/courses/initialize-angular-project#:~:text=Step%20into%20the%20world%20of%20Angular%20development,essential%20knowledge%20to%20kick%2Dstart%20your%20Angular%20journey.)
[4] [https://www.youtube.com](https://www.youtube.com/watch?v=7rL_mozmnBA)
[5] [https://www.freecodecamp.org](https://www.freecodecamp.org/news/angular-9-for-beginners-how-to-install-your-first-app-with-angular-cli/)
[6] [https://code.visualstudio.com](https://code.visualstudio.com/docs/nodejs/angular-tutorial)
[7] [https://blog.doubleslash.de](https://blog.doubleslash.de/en/software-technologien/quick-start-webfrontend-with-the-angular-cli/#:~:text=NodeJS%20is%20required%20for%20development%20with%20the,in%20Angular%20%28%20Angular%20framework%20%29%20.)
[8] [https://javascript.plainenglish.io](https://javascript.plainenglish.io/angular-from-zero-to-somewhere-introduction-2d6278efd93d#:~:text=Tools%20You%27ll%20need%20an%20IDE%20to%20build,Angular%20applications%20is%20%E2%80%9C%20Visual%20Studio%20code%E2%80%9D.)
[9] [https://jhapriti09.medium.com](https://jhapriti09.medium.com/how-to-create-first-angular-project-how-to-create-angular-project-in-visual-studio-code-ec87c8416d79#:~:text=Angular%20CLI:%20Install%20Angular%20CLI%20globally%20using,your%20terminal%20or%20command%20prompt%20and%20run:)
[10] [https://www.youtube.com](https://www.youtube.com/shorts/T8RVw6hGVpY)
[11] [https://github.com](https://github.com/dinanathsj29/angularcli-angualr-cli-tutorial)
[12] [https://medium.com](https://medium.com/@aayushidoshi97/angular-cli-made-simple-a-beginners-guide-to-angular-development-4feff742e31c)
[13] [https://ej2.syncfusion.com](https://ej2.syncfusion.com/angular/documentation/markdown-editor/getting-started)
[14] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/angular-js/angular-cli-angular-project-setup/)
[15] [https://witscad.com](https://witscad.com/course/complete-angular/chapter/command-line-interface)
[16] [https://medium.com](https://medium.com/@nubecolectiva/mastering-angular-cli-essential-commands-for-professional-developers-a8d99695ac50)
[17] [https://angular.dev](https://angular.dev/cli/build)
[18] [https://angular.dev](https://angular.dev/cli/update)
[19] [https://www.youtube.com](https://www.youtube.com/watch?v=pC01YWp8aOQ&t=43)
[20] [https://codinglatte.com](https://codinglatte.com/posts/angular/angular-6-angular-cli-workspaces/#:~:text=This%20will%20look%20like%20any%20other%20angular,to%20generate%20new%20components%2C%20services%2C%20classes%20etc.)
[21] [https://www.ganatan.com](https://www.ganatan.com/en/tutorials/getting-started-with-angular-cli)
[22] [https://github.com](https://github.com/dinanathsj29/angularcli-angualr-cli-tutorial#:~:text=Table:%20Angular%20CLI%20generate%20commands%20Angular%20CLI,generated%20component%20folder%20in%20a%20specific/different%20folder)
[23] [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org/videos/angular-cli-angular-project-setup/#:~:text=For%20example%2C%20to%20generate%20a%20component%2C%20you,by%20minifying%20files%20and%20bundling%20them%20together.)
[24] [https://www.sitepoint.com](https://www.sitepoint.com/angular-2-tutorial/#:~:text=You%20can%20create%20a%20service%20using%20the,by%20adding%20it%20to%20the%20component%27s%20constructor.)



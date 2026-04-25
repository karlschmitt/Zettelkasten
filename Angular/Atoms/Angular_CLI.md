---
id: 20260425164137
title: Angular CLI
author: Karl Schmitt
date: 2026-04-25
keywords: [ Angular, CLI ]
---

# Vorschau

Das **Angular CLI** fungiert als ein unverzichtbares **Kommandozeilenwerkzeug**, das den gesamten Lebenszyklus der Softwareentwicklung für Angular-Projekte automatisiert und vereinfacht. Durch gezielte Befehle ermöglicht es Entwicklern, neue **Arbeitsbereiche zu initialisieren** und notwendigen **Quellcode**, wie Komponenten oder Services, effizient zu generieren. Neben der Bereitstellung eines **lokalen Entwicklungsservers** mit Echtzeit-Aktualisierung übernimmt das Tool auch die **Optimierung für den Produktivbetrieb** sowie die Durchführung automatisierter Tests. Ein wesentlicher Vorteil besteht darin, dass komplexe Konfigurationen im Hintergrund verwaltet werden, wodurch ein einheitlicher Standard gemäß **bewährter Praktiken** gewährleistet wird. Somit erleichtert das Interface nicht nur die **Wartung und Aktualisierung** von Abhängigkeiten, sondern erlaubt es Programmierern auch, sich vollkommen auf die Logik ihrer Anwendung zu konzentrieren.


# Angular CLI

The **Angular CLI** (Command Line Interface) is a powerful tool provided by the Angular team to initialize, develop, scaffold, and maintain Angular applications directly from your terminal.

It is the standard way to build Angular apps because it automates many repetitive tasks and ensures your project follows recommended best practices.

### Key Features and Commands:

* **Project Creation:** ng new \<project-name> sets up a complete, ready-to-run Angular workspace with all necessary configurations (TypeScript, Webpack/Vite, testing frameworks).

* **Scaffolding (Code Generation):** ng generate (or ng g) allows you to quickly create boilerplate code for components, services, modules, pipes, and more. For example, ng generate component my-button.

* **Development Server:** ng serve compiles the application and starts a local web server with live reloading, so you can see changes in real-time.

* **Production Building:** ng build optimizes your application for production, performing tasks like minification and tree-shaking to reduce the bundle size.

* **Testing:** ng test runs unit tests using Karma or alternative runners, and ng e2e runs end-to-end tests.

* **Updates:** ng update helps keep your dependencies up to date, automatically managing complex migrations between Angular versions.

**Why use it?**\
Without the CLI, you would have to manually configure complex build tools, TypeScript compilers, and folder structures. The CLI handles all of that "under the hood," allowing you to focus on writing your application logic rather than configuration.

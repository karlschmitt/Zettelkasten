---
id: 20260425180731
title: Angular CLI Reference
author: Karl Schmitt
date: 2026-04-25
keywords: [  Angular, CLI ]
---

# Angular CLI Reference

The Angular Command Line Interface (CLI) is a powerful tool to initialize, develop, scaffold, and maintain Angular applications.

## Essential Commands

### 1. Initialize
```bash
ng new my-app
```
Creates a new Angular workspace.

### 2. Development Server
```bash
ng serve --open
```
Builds and serves your app, rebuilding on file changes.

### 3. Scaffolding (Generate)
```bash
ng generate component my-component
# Shorthand:
ng g c my-component
```
Common blueprints:
- `c`: Component
- `s`: Service
- `d`: Directive
- `p`: Pipe
- `g`: Guard
- `m`: Module (Legacy)

### 4. Build
```bash
ng build
```
Compiles the application into an output directory (`dist/`) for production.
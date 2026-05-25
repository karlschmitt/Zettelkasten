---
id: 20260425182938
title: The Power of the CLI
author: Karl Schmitt
date: 2026-04-25
keywords: []
---

# The Power of the CLI

The Angular CLI is a command-line interface tool that you use to initialize, develop, scaffold, and maintain Angular applications directly from a command shell.

>[!Note]
> PowerShell Terminal:

```
# Install the CLI globally
npm install -g @angular/cli

# Create a new project
ng new awesome-app
```

## Core Workflow

#### Development

`ng serve`

Runs local dev server with HMR.

#### Build

`ng build`

Compiles prod-ready assets.

## Generating Code (Scaffolding)

Instead of creating files manually, use `ng generate` (or `ng g`) to create blueprints with boilerplate and tests automatically.

schematics

```
# Generate a component
ng g component components/user-profile

# Generate a service
ng g service services/auth

# Generate a signal-based component (latest)
ng g c features/dashboard --standalone
```

#### Dry Run

Use the `--dry-run` flag to see what files would be created without actually writing them to disk.

Previous

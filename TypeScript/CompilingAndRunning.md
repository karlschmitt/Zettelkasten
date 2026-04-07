# 20260406190414 Compiling and running TypeScript

To compile and run TypeScript in a single command, you have several options 
depending on whether you want to use a dedicated runner or native Node.js support. [1, 2, 3] 

## 1. Using a Runner (Recommended for Speed)

Runners handle the compilation in memory and execute the code immediately, which is the fastest way to iterate during development. [4] 

* [tsx](https://nodejs.org/en/learn/typescript/run) (Fastest): Modern, fast, and requires zero config. It uses esbuild under the hood.

npx tsx main.ts

* [ts-node](https://www.digitalocean.com/community/tutorials/typescript-running-typescript-ts-node) (Standard): The classic choice for running TypeScript directly in [Node.js](https://nodejs.org/en).

npx ts-node main.ts

[5, 6, 7] 

## 2. Using Native Node.js (Version 22.6+)

Recent versions of [Node.js](https://nodejs.org/en/learn/typescript/run-natively) can execute TypeScript files directly by stripping type annotations. [7, 8, 9] 

* Node.js v22.18+ / v23.0+: Support is automatic for "erasable" syntax.

node main.ts

* Node.js v22.6 to v22.17: Requires an experimental flag.

node --experimental-strip-types main.ts


## 3. Using Standard Commands (No Extra Tools)

If you prefer not to install additional runners, you can chain the TypeScript compiler (tsc) and node using standard terminal syntax: [8, 10] 

* macOS / Linux / PowerShell:

tsc main.ts && node main.js

* Windows (Command Prompt):

tsc main.ts & node main.js

[11] 

## Comparison Table

| Method [12, 13, 14, 15, 16] | Speed | Type Checking | Best For |
|---|---|---|---|
| tsx | Very Fast | No (by default) | Rapid development |
| ts-node | Fast | Yes | General development |
| Native Node | Fast | No | Quick scripts (no dependencies) |
| tsc && node | Slower | Yes | Verifying builds/Production |


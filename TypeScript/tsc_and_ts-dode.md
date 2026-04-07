# 20260406191146 How to install tsc and ts-node globaly

To install `tsc` (the TypeScript compiler) and `ts-node` globally, you use the Node Package Manager (npm), which comes bundled with Node.js. \[1, 2]


## 20260406191656 Global Installation Commands tsc and ts-node

Open your terminal or command prompt and run the following command:

```bash
npm install -g typescript ts-node
```

* `-g` / `--global`: This flag ensures the packages are installed globally on your system rather than just in your current project folder.
* Permissions: On macOS or Linux, you may need to prefix the command with `sudo` if you encounter permission errors:
*  `sudo npm install -g typescript ts-node`. \[1, 3]


## 20260406221042 Verify the Installation

After the installation finishes, you can check that both are working correctly by requesting their versions: \[2]

* Check TypeScript (`tsc`):
  ```bash
  tsc --version
  ```
* Check `ts-node`:
  ```bash
  ts-node --version
  ```
  \[4, 5]

## Why use `ts-node` for your bootcamp?

During your web dev bootcamp, you will likely use `ts-node` to run your TypeScript files directly in one step (e.g., `ts-node main.ts`) instead of manually compiling to JavaScript first with `tsc`. \[6, 7, 8]

Pro-tip for Bootcamps: While global installs are great for quick scripts, most professional projects prefer local installations (using `npm install --save-dev typescript ts-node`) to ensure everyone on a team uses the exact same version. \[3, 9]

Do you have Node.js already installed, or do you need the steps to set that up first?



\[1] [https://www.youtube.com](https://www.youtube.com/watch?v=PBFAz51-cro\&t=145)

\[2] [https://www.youtube.com](https://www.youtube.com/watch?v=ZpXl5pQmi88\&t=114)

\[3] [https://blog.appsignal.com](https://blog.appsignal.com/2022/01/19/how-to-set-up-a-nodejs-project-with-typescript.html)

\[4] [https://www.youtube.com](https://www.youtube.com/watch?v=KUzqy77uBVM\&t=114)

\[5] [https://stackoverflow.com](https://stackoverflow.com/questions/46946205/how-to-use-global-node-packages-with-typescript)

\[6] [https://www.npmjs.com](https://www.npmjs.com/package/ts-node)

\[7] [https://www.digitalocean.com](https://www.digitalocean.com/community/tutorials/typescript-running-typescript-ts-node#:~:text=To%20use%20ts%2Dnode%2C%20you%20need:%20*%20The,JavaScript%20without%20checking%20for%20any%20TypeScript%20errors)

\[8] [https://www.robinwieruch.de](https://www.robinwieruch.de/typescript-node-js/)

\[9] [https://www.typescriptlang.org](https://www.typescriptlang.org/download/)

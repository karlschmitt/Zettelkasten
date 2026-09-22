---
id: 
title: Secure Pointer Tutorial
author: Karl Schmitt
date: 2026-09-22
keywords: [ C++, g++, cmake ]
---

# Secure Pointer Tutorial

Here is a secure pointer tutorial tailored to your environment using modern C++ smart pointers, CMake, and VS Code.
## Key Security Takeaways

* 
* Never use new or delete: Always prefer std::make_unique and std::make_shared. They safeguard against partial construction memory leaks.
* std::unique_ptr: Use by default for exclusive ownership. Costs zero performance overhead compared to raw pointers.
* std::shared_ptr: Use only when multiple distinct entities must control the asset lifetime.
* std::weak_ptr: Use to break reference cycles (e.g., Parent-Child or Graph nodes pointing back to each other) that would otherwise permanently freeze memory allocations.
* 

Would you like me to show you how to write a custom safe container using these smart pointers, or would you like assistance configuring VS Code debug scripts (launch.json) to catch memory issues?


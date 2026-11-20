---
id: 202611201703
title: "AI Agent Fundamentals: An Absolute Beginner's Step-by-Step Guide"
author: Karl Schmitt
date: 2026-11-20
keywords: [ai, agents, llm, tutorial, zettelkasten, architecture, python]
---

# AI Agent Fundamentals: An Absolute Beginner's Step-by-Step Guide

## 1. Core Concept: Chatbot vs. AI Agent

To understand AI agents from first principles, compare how a standard Large Language Model (LLM) operates versus an AI agent:

* **Standard LLM (Passive):** You provide a prompt, and the model predicts the most likely text response based on its training data. It cannot interact with the outside world, check live data, or execute code on its own.
* **AI Agent (Active):** An LLM wrapped in a continuous **control loop** with access to **Tools** (functions) and **Memory**. Instead of just answering, the LLM *reasons* about a goal, decides which tool to call, observes the result, and repeats the process until the task is complete.

| Feature | Standard Chatbot | AI Agent |
| :--- | :--- | :--- |
| **Primary Action** | Generates text | Reasons, plans, and executes actions |
| **External World Access** | None (cutoff date limited) | Uses APIs, file systems, terminals, web search |
| **Execution Flow** | Single turn (`Input -> Output`) | Iterative loop (`Think -> Act -> Observe`) |
| **State & Memory** | Current chat window only | Short-term scratchpad + long-term storage |

---

## 2. The Four Pillars of an AI Agent

Every AI agent—regardless of the framework—consists of four foundational components:

1. **The Brain (LLM):** The reasoning engine (e.g., Gemini, Claude, GPT, or a local Llama model) that breaks down goals into steps and decides what to do next.
2. **Tools (Capabilities):** Python functions, shell commands, or API calls the LLM is permitted to invoke (e.g., `read_file()`, `calculate()`, `web_search()`).
3. **Memory (Context):**
   * *Short-term:* The running log of thoughts, tool calls, and tool outputs within the current task.
   * *Long-term:* External databases, vector stores, or Markdown files (like a Zettelkasten) queried for persistent knowledge.
4. **The Control Loop (ReAct Pattern):** The orchestration script that feeds the LLM's requested tool calls into actual code execution and passes the output back to the LLM.

---

## 3. How the Agent Loop Works (The ReAct Pattern)

Most beginner agents use the **ReAct** (**Rea**son + **Act**) architecture. When you give an agent a goal, the loop runs like this:

```text
User Goal: "Check the disk usage of my home directory and summarize it."
   │
   ▼
[1. THOUGHT] LLM: "I need to check disk usage. I have a 'run_command' tool."
   │
   ▼
[2. ACTION]  LLM outputs structured request: run_command(cmd="df -h ~")
   │
   ▼
[3. OBSERVE] Host script executes `df -h ~` and feeds stdout back to LLM.
   │
   ▼
[4. THOUGHT] LLM: "I have the raw numbers (45G used of 100G). I can now answer."
   │
   ▼
[5. FINAL]   LLM outputs human-readable summary to the user.
````

## 4. Step-by-Step Build: A Zero-Framework Python Agent

Frameworks (like LangChain or CrewAI) hide how agents actually work. Building one from scratch in pure Python using standard HTTP requests or an official SDK gives you complete deterministic control.



### Step 1: Define Your Tools

A "tool" is just a normal function paired with a clear description so the LLM knows when and how to use it.



Python

```
import os
import subprocess

def list_files(directory: str = ".") -> str:
    """Lists all files in a given directory."""
    try:
        return "\n".join(os.listdir(directory))
    except Exception as e:
        return f"Error: {e}"

def get_system_uptime() -> str:
    """Returns the current system uptime."""
    result = subprocess.run(["uptime", "-p"], capture_output=True, text=True)
    return result.stdout.strip()

# Registry mapping tool names to actual Python functions
TOOLS = {
    "list_files": list_files,
    "get_system_uptime": get_system_uptime,
}
```

### Step 2: Craft the System Prompt (The Rules)

Because an LLM only outputs text, we instruct it to follow a strict output format whenever it wants to run a tool.



Python

```
SYSTEM_PROMPT = """
You are an autonomous AI agent. You solve tasks by alternating between Thought, Action, and Observation.

Available Tools:
- list_files(directory): Lists all files in a directory.
- get_system_uptime(): Returns how long the machine has been running.

When you need to use a tool, reply ONLY with this exact format:
THOUGHT: <your reasoning>
ACTION: <tool_name>|<argument>

When you have the final answer for the user, reply ONLY with:
FINAL: <your final response>
"""
```

### Step 3: Build the Control Loop

This `while` loop connects the LLM's text output to your Python functions. _(Replace `call_llm()` with your preferred API call, such as `google-genai`, `openai`, or a local Ollama endpoint)._



Python

```
def run_agent(user_goal: str, max_steps: int = 5):
    # Maintain conversation history as the agent's short-term memory
    memory = [
        {"role": "system", "content": SYSTEM_PROMPT},
        {"role": "user", "content": f"Goal: {user_goal}"}
    ]

    for step in range(max_steps):
        print(f"--- Step {step + 1} ---")
        
        # 1. Send current memory to the LLM
        response = call_llm(memory) 
        print(response)
        memory.append({"role": "assistant", "content": response})

        # 2. Check if the agent reached a final answer
        if "FINAL:" in response:
            return response.split("FINAL:")[1].strip()

        # 3. Parse and execute the requested Action
        if "ACTION:" in response:
            action_line = [line for line in response.splitlines() if line.startswith("ACTION:")][0]
            _, payload = action_line.split("ACTION:", 1)
            tool_name, arg = [part.strip() for part in payload.split("|", 1)]

            if tool_name in TOOLS:
                # Execute the Python function
                observation = TOOLS[tool_name](arg) if arg else TOOLS[tool_name]()
            else:
                observation = f"Error: Tool '{tool_name}' does not exist."

            print(f"OBSERVATION: {observation}\n")
            
            # 4. Feed the result back into memory for the next loop iteration
            memory.append({"role": "user", "content": f"OBSERVATION: {observation}"})

    return "Agent stopped: Maximum steps reached."
```

### Step 4: Native Function Calling (Modern Production Approach)

In production systems, rather than parsing strings like `ACTION: tool|arg` with `.split()`, modern LLM APIs support **Native Tool Calling (Structured Outputs)**:



1. You pass a JSON schema describing your functions alongside your prompt.

2. The LLM returns a structured JSON object (`{"tool_call": {"name": "list_files", "args": {"directory": "."}}}`) instead of raw text.

3. Your code executes the function and sends back a `tool_response` message object.

## 5. Key Engineering Guardrails for Beginners

When building agents that interact with your local system, enforce strict boundaries:

* **Always Set `max_steps`:** LLMs can get stuck in infinite loops if a tool returns an unexpected error. Always cap the `for`/`while` loop (e.g., `max_steps = 10`).

* **Sandbox Destructive Tools:** Never give an experimental agent unrestricted `rm`, `sudo`, or database write access without a **Human-in-the-Loop (HITL)** confirmation step (`input("Allow execution? [y/n]: ")`).

* **Keep Context Small:** Tool outputs (like reading a large log file) quickly fill up the LLM's context window, increasing latency and cost. Truncate long outputs before appending them to `memory`.

## 6. Suggested Next Zettelkasten Notes

* `[[20261120-function-calling-schemas]]` — Writing JSON schemas for native LLM tool use.

* `[[20261120-local-llm-ollama-api]]` — Connecting a Python agent loop to a local offline model.

* `[[20261120-multi-agent-orchestration]]` — Splitting complex workflows into specialized sub-agents (Planner, Coder, Reviewer).

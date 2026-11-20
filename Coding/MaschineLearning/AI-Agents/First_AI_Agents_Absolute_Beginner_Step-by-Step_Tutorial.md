---
id: 20261120165329
title: AI Agents for Absolute Beginner a Step-by-Step Tutorial 
---


# **AI Agents for Absolute Beginner a Step-by-Step Tutorial**

Absolute beginner

Hands-on

Markdown / Zettelkasten

[Introduction to AI Agents for PMs - by Paweł Huryn](https://images.openai.com/static-rsc-4/PjyP0-dUyWNFsSLrUmaEJWM5fCLPBiJpFOSXAe-gWaIUWwB5LIf5crvATWelz5DrAIl_p-GDCHCyAF0rTQclqSN_PuM0axXH_UYg6Q2iJmN5Mhal0WMrT2Hp67qjZkIsmbe9daoPT0NvnN4SKlhJ0pib0rO6wNQpmK04CDIX5ls?purpose=inline)

[productcompass.pm](https://www.productcompass.pm/p/ai-agents?utm_source=chatgpt.com)

## **1. Learning objectives**

By the end of this tutorial, you will understand:

* What artificial intelligence (AI) is.

* What a Large Language Model (LLM) is.

* What an AI agent is.

* The difference between an ordinary chatbot and an AI agent.

* How AI agents use tools.

* How agents work with memory.

* What the ReAct pattern means.

* How to build a small AI agent in Python.

* How multiple AI agents can cooperate.

* What frameworks such as LangChain, LangGraph, and AutoGen are.

**Our final project:** Build a simple personal AI research assistant that receives a task, decides what to do, uses tools, and produces a result.

## **2. What is Artificial Intelligence?**

Artificial Intelligence (AI) is a field of computer science concerned with creating systems that can perform tasks that normally require human intelligence.

Examples:

* Understanding natural language.

* Recognizing objects in images.

* Translating languages.

* Generating text.

* Solving problems.

* Making predictions.

Some familiar AI applications:

* ChatGPT

* Microsoft Copilot

* Google Gemini

* GitHub Copilot

* Image recognition systems

### **2.1 Traditional programming vs. AI**

Traditional programming:

```
INPUT
  |
  v
PROGRAMMED RULES
  |
  v
OUTPUT
```

AI-based processing:

```
INPUT
  |
  v
AI MODEL
  |
  v
PREDICTION / RESPONSE
```

Traditional programs generally follow explicitly programmed rules. AI models learn patterns from data and use those patterns to generate predictions or responses.

### **Exercise 1**

Answer these questions:

1. What does AI stand for?

2. Name three tasks that AI can perform.

3. What is the difference between traditional programming and AI?

## **3. What is a Large Language Model (LLM)?**

A Large Language Model (LLM) is an AI model trained on large amounts of text.

It can process and generate human language.

Examples:

* GPT

* Claude

* Gemini

* Llama

* Mistral

An LLM can:

* Answer questions.

* Explain programming concepts.

* Generate Java code.

* Translate text.

* Summarize documents.

* Generate structured data.

### **3.1 How does an LLM work?**

An LLM predicts likely next tokens based on the preceding context.

A token can be:

* A complete word.

* Part of a word.

* A punctuation character.

* Another text unit.

For example:

```
The capital of Germany is ...
```

The model predicts a likely continuation:

```
Berlin.
```

This is a simplified explanation. Modern LLMs use complex neural network architectures, particularly Transformers.

### **3.2 Important terminology**

| Term          | Meaning                                                |
| ------------- | ------------------------------------------------------ |
| LLM           | Large Language Model                                   |
| Token         | A unit of text processed by a model                    |
| Prompt        | Instructions or input given to a model                 |
| Context       | Information available to the model                     |
| Inference     | Generating a response using a trained model            |
| Hallucination | Generated information that is incorrect or unsupported |

### **Exercise 2**

Ask an LLM:

```
Explain what a Java interface is.
Give me a beginner-friendly example.
```

Observe how the model generates its answer.

## **4. What is an AI Agent?**

This is the most important concept in our tutorial.

An AI agent is a software system that uses an AI model to pursue a goal, decide on actions, interact with tools or its environment, and evaluate results.

Unlike a simple chatbot, an agent can perform multiple steps to accomplish a task.

Imagine asking an AI:

```
Find information about Spring Boot,
summarize the results, and save the summary.
```

A simple chatbot might explain how you could do this.

An AI agent could potentially:

1. Understand the task.

2. Search for information.

3. Read relevant results.

4. Summarize the information.

5. Save the summary to a file.

6. Report that it has completed the task.

### **4.1 Chatbot vs. AI agent**

| Chatbot                    | AI agent                   |
| -------------------------- | -------------------------- |
| Answers questions          | Pursues goals              |
| Primarily generates text   | Can perform actions        |
| Usually responds directly  | Can execute multiple steps |
| May not use external tools | Can use tools              |
| Often conversational       | Often task-oriented        |

An important distinction: an agent does not necessarily act autonomously all the time. Some agents require human approval before performing actions.

### **4.2 Basic AI agent architecture**

[AI und LLM Agents: So funktionieren intelligente KI-Assistenten wirklich | XPACE GmbH](https://images.openai.com/static-rsc-4/R_NNUQ1L6AzoMphtIS8ZF4JPZgZxDXTYrgFlGCV7qCAl2KhP9oLjpJ69TOVPnCSqEg9znUi9o99qvj7Y_SraZ1t147ktYmjcKQLRhfY-ERvdXphlWBAEaSztkM2n2KS_9Q8xMLxyEmCn7_i03w79ZgUN7g3rWNFoTgWO8XZwYRM?purpose=inline)

[xpace.de](https://www.xpace.de/de/blog/llm-agents-overview/?utm_source=chatgpt.com)

The main components are:

1. **Input:** Receives a task.

2. **LLM:** Interprets the task and helps decide what to do.

3. **Planning:** Determines the next steps.

4. **Tools:** Executes actions.

5. **Memory:** Stores useful information.

6. **Observation:** Examines the results.

7. **Output:** Provides the final answer.

### **Exercise 3**

Imagine you want an AI agent to organize your programming notes.

Write down:

* What is the goal?

* Which tools does the agent need?

* What information should it remember?

* What should the final result look like?

## **5. The building blocks of an AI agent**

Let's examine the individual components in more detail.

### **5.1 The LLM – The brain**

The LLM is responsible for interpreting instructions and helping the agent decide what to do.

Example:

```
User:
Find the latest information about Docker.

LLM:
I should search for Docker information.
```

The LLM does not automatically have access to the internet. It needs an appropriate tool.

### **5.2 Tools – The hands**

Tools allow an agent to interact with external systems.

Examples:

| Tool        | Purpose                       |
| ----------- | ----------------------------- |
| Web search  | Search the internet           |
| Calculator  | Perform calculations          |
| File reader | Read documents                |
| File writer | Create documents              |
| Database    | Retrieve or store information |
| HTTP client | Communicate with REST APIs    |
| Email       | Read or send emails           |

Consider this example:

```
User
 |
 v
AI Agent
 |
 v
LLM decides: I need a calculation.
 |
 v
Calculator Tool
 |
 v
Result: 42
 |
 v
AI Agent
 |
 v
User receives the answer
```

### **5.3 Memory – The memory of an agent**

An agent can use memory to retain information between steps or conversations.

There are different kinds of memory:

| Memory type         | Explanation                              |
| ------------------- | ---------------------------------------- |
| Short-term memory   | Information from the current task        |
| Long-term memory    | Information retained across tasks        |
| Conversation memory | Previous messages                        |
| Working memory      | Information needed while solving a task  |
| External memory     | Information stored in databases or files |

Example:

```
User:
My favorite programming language is Java.

Agent:
Stores this information.

User:
Which language should I use for my backend project?

Agent:
Can use the stored preference when preparing its answer.
```

Important: Not every AI agent automatically has persistent memory. It must be implemented.

### **5.4 Planning – The ability to break down tasks**

A complex task can be divided into smaller tasks.

Example:

```
GOAL:
Create a Spring Boot REST API.

PLAN:

1. Create a Spring Boot project.
2. Create a REST controller.
3. Implement a GET endpoint.
4. Test the endpoint.
5. Document the API.
```

This is called task decomposition.

### **Exercise 4**

You want an AI agent to create a Markdown tutorial about Docker.

Identify:

1. Which LLM is needed?

2. Which tools could be useful?

3. What information should be stored in memory?

4. Which steps should the agent perform?

## **6. How does an AI agent work?**

Let's look at a typical agent execution cycle.

This is sometimes called an agent loop.

[How to Master Gen AI: Volume 3— Agentic AI (Part 1: Foundations) | by Martin Jurado Pedroza | Apr, 2026 | Medium](https://images.openai.com/static-rsc-4/D0qE85vcEsVpZtIrhvdHZljaL4_qhZSNDnHR8OmU_pxbdoB2wZ3hfsSKK_3bcM9bqGM84gJsl05gvEGeUaLi_g803PVcK2IE4Y2p6HLhoNVAUIFEn1kvgkU7nPpALLx8MZg_Rs5XfRQLuXaeKkv_aY3X8hnYuhZHGRIXIxXksTI?purpose=inline)

[medium.com](https://medium.com/%40martin.jurado.p/how-to-master-gen-ai-volume-3-agentic-ai-part-1-foundations-333062d41db3?utm_source=chatgpt.com)

The basic process:

1. Receive a task.

2. Analyze the task.

3. Decide what action to take.

4. Execute the action.

5. Observe the result.

6. Decide whether another action is necessary.

7. Return the final result.

### **6.1 Example: Research assistant**

User request:

```
Find three useful resources about Spring Boot.
Summarize them.
```

The agent might perform these steps:

```
STEP 1: Receive task

STEP 2: Understand task

STEP 3: Search for Spring Boot resources

STEP 4: Examine search results

STEP 5: Select relevant resources

STEP 6: Summarize information

STEP 7: Return summary
```

Notice that the agent performs several actions rather than simply generating one response.

### **6.2 The ReAct pattern**

ReAct stands for:

**Reasoning + Acting**

It is a pattern in which an LLM alternates between reasoning about a task and taking actions through tools.

A simplified example:

```
Thought:
I need to calculate 25 * 4.

Action:
Use calculator.

Observation:
100

Thought:
I have the result.

Final Answer:
25 * 4 = 100.
```

The cycle looks like this:

```
THOUGHT
   |
   v
ACTION
   |
   v
OBSERVATION
   |
   v
THOUGHT
   |
   v
FINAL ANSWER
```

The example is illustrative; actual implementations may use structured tool calls rather than exposing private reasoning.

### **Exercise 5**

Create your own ReAct example.

Task:

```
Find the size of a folder and report it in MB.
```

Write down:

* The agent's decision.

* The tool it needs.

* The observation.

* The final answer.

## **7. Your first practical AI agent – Python**

Now let's write some code!

We will start with a very small agent that can select and execute tools.

**Important:** This first project is a simulated, rule-based agent. It does not use a real LLM yet. This allows us to understand the agent architecture before introducing APIs, model costs, and more complicated frameworks.

### **7.1 Requirements**

You need:

* Python 3

* Visual Studio Code

* PowerShell (Windows)

We will only use Python's standard library. No external packages are necessary.

### **7.2 Create the project**

Open PowerShell.

Create a project directory:

```
mkdir AI-Agent-Beginner
cd AI-Agent-Beginner
```

Create a Python file:

```
New-Item agent.py
```

Open the folder in Visual Studio Code:

```
code .
```

Your project structure:

```
AI-Agent-Beginner/
|
+-- agent.py
```

### **7.3 Create your first tool**

Open `agent.py`.

Enter the following code:

```
def calculator_tool(a, b):
    return a + b


result = calculator_tool(10, 20)

print(result)
```

Run the program:

```
python agent.py
```

Expected output:

```
30
```

Congratulations! You have created your first tool.

The calculator is a simple function that performs an action and returns a result.

### **7.4 Add a second tool**

Let's create a tool that retrieves information.

Add this code:

```
def information_tool():
    return "Python is a programming language."


print(information_tool())
```

Expected output:

```
Python is a programming language.
```

We now have two tools:

* Calculator

* Information provider

### **7.5 Create an agent**

Now we need a central function that decides which tool to use.

Replace your code with:

```
def calculator_tool(a, b):
    return a + b


def information_tool():
    return "Python is a programming language."


def ai_agent(user_task):

    print("Agent received:", user_task)

    if "calculate" in user_task.lower():

        print("Agent selected calculator tool.")

        result = calculator_tool(10, 20)

        return result

    elif "python" in user_task.lower():

        print("Agent selected information tool.")

        result = information_tool()

        return result

    else:

        return "I don't know which tool to use."


task = input("What should the agent do? ")

answer = ai_agent(task)

print("Agent result:", answer)
```

Run:

```
python agent.py
```

Try:

```
What should the agent do? Calculate something
```

Output:

```
Agent received: Calculate something
Agent selected calculator tool.
Agent result: 30
```

Try another task:

```
What should the agent do? Tell me about Python
```

Output:

```
Agent received: Tell me about Python
Agent selected information tool.
Agent result: Python is a programming language.
```

### **7.6 Understanding the architecture**

Let's examine what we have built.

```
              USER
                |
                v
          USER TASK
                |
                v
          +-----------+
          | AI AGENT  |
          +-----------+
                |
          +-----+-----+
          |           |
          v           v
     CALCULATOR   INFORMATION
       TOOL          TOOL
          |           |
          v           v
        RESULT      RESULT
          |           |
          +-----+-----+
                |
                v
          FINAL OUTPUT
```

Our agent has:

* An input.

* A decision mechanism.

* Multiple tools.

* An output.

However, the decision mechanism is just an `if/elif` statement. A real LLM-powered agent would use an AI model to interpret tasks and select tools more flexibly.

## **8. Understanding LLM-powered agents**

Now let's introduce the missing component: the actual language model.

Our previous example:

```
if "calculate" in user_task.lower():
```

This is traditional programming.

An LLM-powered agent instead sends the task and available tool descriptions to an LLM.

For example:

```
USER TASK:
Calculate 100 + 250.

AVAILABLE TOOLS:

1. calculator
   Description: Performs mathematical calculations.

2. information
   Description: Provides programming information.
```

The model can select the calculator tool.

### **8.1 Function calling / tool calling**

Modern LLMs can support structured tool calls.

For example, the model might return a request like:

```
{
    "tool": "calculator",
    "arguments": {
        "a": 100,
        "b": 250
    }
}
```

Your application then:

1. Receives the tool request.

2. Checks whether the tool is allowed.

3. Validates the arguments.

4. Executes the function.

5. Sends the result back to the model.

6. Receives the final response.

**Important:** The LLM does not normally execute your local Python function itself. Your application executes the function on the model's behalf.

### **8.2 Architecture**

```
              USER
                |
                v
          +-----------+
          |   AGENT   |
          +-----------+
                |
                v
          +-----------+
          |    LLM    |
          +-----------+
                |
                v
          TOOL REQUEST
                |
                v
          +-----------+
          |   TOOLS   |
          +-----------+
                |
                v
           TOOL RESULT
                |
                v
          +-----------+
          |    LLM    |
          +-----------+
                |
                v
          FINAL ANSWER
```

This is the basic architecture behind many tool-using AI agents.

## **9. AI agent frameworks**

When you start building more sophisticated agents, you will encounter specialized frameworks.

These frameworks provide reusable components for building agent systems.

[LangChain - Partner Ecosystem | MongoDB](https://images.openai.com/static-rsc-4/XFgDhJXhGfSAGUFZeG8KDYHPCvHBDtPNtRoNH4-j_ThOcv1TfVbAv-vLM99Wi5g6yksscqygP9bXC-9EjIvfq92LVcR3rRSCWZUT5FxM-XUoAzdtQcikAXJmB0LMbidgqKoKHs5xWVsQnIHyEF43mufdsEU5FehmA_h-FIVEWQo?purpose=inline)

**1.&#x20;**__LangChain__

A framework for connecting language models with tools, data sources, and other application components.

Website: [LangChain](https://www.langchain.com/?utm_source=chatgpt.com)

[Qbit Labs | AI-First MVP Studio](https://images.openai.com/static-rsc-4/6uTjTK_ypWUnb5yDrFgHDv0HqGzlcy9xVeQguw4rJ4a5INGFhiqlR2mwBCLUtxr556fgwceESoauyytugtSZazCS99REkZhL2dzXQ7kgnOnm6d8dN6uovsm8Vy4QoN8PKMG32VORvYjTacS-iuEN0OHRQ0cAqnMUH-bKdzw1LFw?purpose=inline)

**2.&#x20;**__LangGraph__

Helps build agents using graphs, nodes, state, and conditional transitions. Particularly useful for workflows with multiple steps.

Website: [LangGraph](https://www.langchain.com/langgraph?utm_source=chatgpt.com)

[Microsoft AutoGen Everything you need to know to get started](https://images.openai.com/static-rsc-4/O1WlHcRfR05JG2wxN5p0gjJg9K96iKsrBEk3kUuv8kVhX-t4UhJHQliAxfwRyXRPID-bfDdM7zQHzvFqJiB1gPq1o_YRu63D4pp1sAqFFBnqBXsZgF2q6JJvJ7HgCQPPmKELlaQxw5Rd95pZuJ5FFdQxoa_z29PkPE71hBaYaPg?purpose=inline)

**3.&#x20;**__Microsoft AutoGen__

A framework for creating applications in which multiple AI agents can communicate and cooperate.

Website: [AutoGen](https://microsoft.github.io/autogen/?utm_source=chatgpt.com)

[Crew AI Pricing & Reviews 2025 | Techjockey.com](https://images.openai.com/static-rsc-4/JNb7QCnH_dz14wuRNyg6WT0MMpWuF05uhvd27FT-9kRIlDRbNc3W8wiBRs3nfxx4Gng3B312S5M9kQxftb6G6-yIBSecwsRC4uwtvL16Jc2M4lvvEHdi4IwlJ-CG9KuuYQHEt4ErL2_Dd1vh1sYoGNPBMoVEzXQjrxJxAaICp1I?purpose=inline)

**4.&#x20;**__CrewAI__

Focuses on organizing agents into teams with different roles and responsibilities.

Website: [CrewAI](https://www.crewai.com/?utm_source=chatgpt.com)

### **9.1 When should you use these frameworks?**

| Framework | Typical use                           |
| --------- | ------------------------------------- |
| LangChain | LLM applications and tool integration |
| LangGraph | Stateful agent workflows              |
| AutoGen   | Multi-agent collaboration             |
| CrewAI    | Role-based agent teams                |

My recommendation: Learn the fundamental concepts first. You do not need a framework to understand how an AI agent works.

## **10. What are multi-agent systems?**

So far, we have worked with one agent.

But what happens when we have multiple agents?

A multi-agent system consists of multiple agents that cooperate to achieve a common goal.

Imagine a software development team.

[AI Agents & Software Engineering: New Patterns or Old Tricks? | by Patrick Koss | Medium](https://images.openai.com/static-rsc-4/tWux73ljJBtBT5bvwUjd2xAumv89WYt0YN6XK3SprYM-xVuwPPxqwdp9ZbWcizKSctst86d53cCQlKiBIDIVcIl7JFCZe6jeg3leHlRRB2JRfYmPGqLjKUQHNwBlrtWvzyqcKSKAvxChpyIIyW7L0jY8AQHFyYpbId-xdYE3MmM?purpose=inline)

[medium.com](https://medium.com/%40patrickkoss/ai-agents-software-engineering-new-patterns-or-old-tricks-122fc9ab2eee?utm_source=chatgpt.com)

We could create four specialized agents:

| Agent           | Responsibility           |
| --------------- | ------------------------ |
| Planner Agent   | Breaks down the task     |
| Research Agent  | Searches for information |
| Developer Agent | Generates code           |
| Tester Agent    | Reviews and tests code   |

### **10.1 Example workflow**

Goal:

```
Create a simple Spring Boot REST API.
```

Workflow:

```
              USER
                |
                v
          PLANNER AGENT
                |
          +-----+-----+
          |           |
          v           v
     RESEARCHER    DEVELOPER
          |           |
          +-----+-----+
                |
                v
           TESTER AGENT
                |
                v
          FINAL RESULT
```

Each agent has a different responsibility.

This approach can be useful for complex tasks, although multiple agents also introduce additional complexity, cost, and opportunities for errors.

### **Exercise 6**

Design your own multi-agent system.

Scenario:

```
Build a personal programming tutor.
```

Create three agents and define:

* Their names.

* Their responsibilities.

* Their inputs.

* Their outputs.

## **11. AI agent safety and security**

This is an important topic, especially when agents can interact with real systems.

An AI agent can potentially:

* Read files.

* Modify files.

* Execute commands.

* Access databases.

* Send emails.

* Communicate with external APIs.

This creates security risks.

### **11.1 Important risks**

| Risk                  | Explanation                                   |
| --------------------- | --------------------------------------------- |
| Hallucination         | The agent produces incorrect information      |
| Prompt injection      | Malicious instructions manipulate the agent   |
| Data leakage          | Private information is exposed                |
| Unauthorized actions  | The agent performs actions without permission |
| Infinite loops        | The agent repeatedly executes actions         |
| Excessive permissions | The agent has more access than necessary      |

### **11.2 Security best practices**

1. Give agents only the permissions they need.

2. Validate tool arguments.

3. Restrict access to sensitive files.

4. Set execution limits.

5. Require human approval for important actions.

6. Log tool executions.

7. Never expose API keys in source code.

8. Test agents in isolated environments.

For example:

```
Agent wants to delete a file.

             |
             v

       HUMAN APPROVAL
             |
        +----+----+
        |         |
        v         v
      APPROVE   REJECT
        |         |
        v         v
      DELETE    CANCEL
```

An agent should not automatically be trusted simply because it uses an advanced AI model.

## **12. Practical project – Build a personal AI research assistant**

Now let's combine what we have learned.

Our final project will be a personal research assistant.

### **12.1 Project requirements**

The agent should:

1. Accept a research task.

2. Analyze the task.

3. Select an appropriate tool.

4. Retrieve information.

5. Generate a summary.

6. Save the result as a Markdown file.

Example:

```
USER:

Research the basic concepts of Docker.
Create a beginner-friendly Markdown summary.
```

Expected workflow:

```
USER
 |
 v
AI RESEARCH ASSISTANT
 |
 v
ANALYZE TASK
 |
 v
CREATE RESEARCH PLAN
 |
 v
SEARCH FOR INFORMATION
 |
 v
SUMMARIZE RESULTS
 |
 v
CREATE MARKDOWN FILE
 |
 v
REPORT COMPLETION
```

### **12.2 Suggested project structure**

```
AI-Research-Assistant/
|
+-- main.py
|
+-- agents/
|   |
|   +-- research_agent.py
|   +-- summary_agent.py
|
+-- tools/
|   |
|   +-- search_tool.py
|   +-- file_tool.py
|
+-- memory/
|   |
|   +-- agent_memory.json
|
+-- output/
|   |
|   +-- docker-summary.md
|
+-- README.md
```

### **12.3 Development stages**

| Stage | Task                 | What you learn     |
| ----- | -------------------- | ------------------ |
| 1     | Create a basic agent | Agent architecture |
| 2     | Add tools            | Tool calling       |
| 3     | Connect an LLM       | Model integration  |
| 4     | Add memory           | Context management |
| 5     | Add planning         | Task decomposition |
| 6     | Add file operations  | External actions   |
| 7     | Add safety checks    | Permissions        |
| 8     | Test the application | Reliability        |

Don't try to implement everything at once. Complete one stage before moving to the next.

## **13. Important AI agent terminology**

Keep this section as a Zettelkasten reference note.

| Term               | Explanation                                                                                  |
| ------------------ | -------------------------------------------------------------------------------------------- |
| AI                 | Artificial Intelligence                                                                      |
| LLM                | Large Language Model                                                                         |
| Agent              | System that uses a model to pursue goals and perform actions                                 |
| Agent loop         | Repeated decision, action, and observation cycle                                             |
| Prompt             | Instructions provided to an AI model                                                         |
| Tool               | Function or external capability available to an agent                                        |
| Tool calling       | Model requests execution of a tool                                                           |
| Function calling   | Structured invocation of application functions                                               |
| Memory             | Information retained for later use                                                           |
| Context window     | Amount of context a model can process                                                        |
| Token              | Unit of text processed by an LLM                                                             |
| RAG                | Retrieval-Augmented Generation                                                               |
| ReAct              | Reasoning and Acting pattern                                                                 |
| Planning           | Breaking a task into smaller steps                                                           |
| Multi-agent system | Multiple agents cooperating                                                                  |
| Orchestration      | Coordinating agents, tools, and workflows                                                    |
| Human-in-the-loop  | Human involvement in decisions or approvals                                                  |
| Hallucination      | Incorrect or unsupported generated information                                               |
| MCP                | Model Context Protocol, a standard for connecting AI applications to external tools and data |

### **13.1 What is RAG?**

RAG stands for Retrieval-Augmented Generation.

It combines information retrieval with LLM-generated responses.

Imagine you have 500 Markdown files in your Zettelkasten.

You ask:

```
Explain everything I have learned about Docker.
```

A RAG application can:

1. Search your Markdown notes.

2. Retrieve relevant passages.

3. Provide those passages as context to an LLM.

4. Generate an answer based on the retrieved information.

[Building RAG Applications with LangChain(Part-4) - DEV Community](https://images.openai.com/static-rsc-4/ChgqsgmNsBh96BnBai7IALibUKLzO-JvB2iCf2t2Dox_N1mFzb6W-Aeyi5fRcdo29Rl5moe4FKWWG6yKQv_M24YCZUBk1nAYV6_HPNw1MWmIduERRvZvVvWlplj7LnX_-xTJvIs59CMhNIBCRpH_UkHfhENNF9oUUzCL6dUMAXk?purpose=inline)

[dev.to](https://dev.to/dharmendra_singh_786/building-rag-applications-with-langchainpart-4-38i0?utm_source=chatgpt.com)

RAG is particularly interesting for personal knowledge management systems.

## **14. Final knowledge check**

Test what you have learned.

**AI Agent Beginner Quiz**

0 / 6 answered

**1**__.&#x20;__**What is the main purpose of an AI agent?**

Display static information

Pursue goals and perform actions

Only translate text

**2**__.&#x20;__**What is an LLM?**

A database

A programming language

A Large Language Model

**3**__.&#x20;__**What is the purpose of a tool?**

Allow an agent to perform an action

Replace the LLM

Store passwords

**4**__.&#x20;__**What does ReAct stand for?**

Read and Calculate

Reasoning and Acting

React and Code

**5**__.&#x20;__**What is RAG?**

A programming framework

A database language

Retrieval-Augmented Generation

**6**__.&#x20;__**Why should an agent have limited permissions?**

To improve its font size

To reduce security risks

To make it generate longer answers

Check my answers

## **15. Recommended 7-day AI agent learning plan**

I recommend spending one day on each topic. Don't rush. Understanding the concepts is more important than writing lots of code.

| Day | Topic                       | Practical exercise               |
| --- | --------------------------- | -------------------------------- |
| 1   | Introduction to AI and LLMs | Experiment with prompts          |
| 2   | AI agent architecture       | Draw an agent architecture       |
| 3   | Tools and function calling  | Build two Python tools           |
| 4   | Agent loops and ReAct       | Implement a decision loop        |
| 5   | Memory and RAG              | Store and retrieve information   |
| 6   | LLM integration             | Connect an actual language model |
| 7   | Personal AI assistant       | Build a small research assistant |

## **16. Zettelkasten organization**

I suggest creating a dedicated folder for this subject.

```
C:\LifeLongLearning\
|
+-- ArtificialIntelligence\
    |
    +-- 00_AI_Overview.md
    +-- 01_What_is_AI.md
    +-- 02_Large_Language_Models.md
    +-- 03_What_is_an_AI_Agent.md
    +-- 04_AI_Agent_Architecture.md
    +-- 05_AI_Agent_Tools.md
    +-- 06_AI_Agent_Memory.md
    +-- 07_AI_Agent_Loops.md
    +-- 08_ReAct_Pattern.md
    +-- 09_Function_Calling.md
    +-- 10_Multi_Agent_Systems.md
    +-- 11_RAG.md
    +-- 12_AI_Agent_Security.md
    +-- 13_Python_AI_Agent_Project.md
    +-- 14_AI_Agent_Glossary.md
```

**My Zettelkasten recommendation:** Keep individual concepts in separate Markdown files. Link related notes together rather than putting everything into one enormous document.

For example:

```
# What is an AI Agent?

An AI agent is a software system that uses
an AI model to pursue goals and perform actions.

## Related notes

- [[Large Language Models]]
- [[AI Agent Architecture]]
- [[AI Agent Tools]]
- [[AI Agent Memory]]
- [[ReAct Pattern]]
- [[Multi-Agent Systems]]

## My own thoughts

An AI agent combines an AI model with tools
and an execution process to accomplish tasks.
```

## **17. Where to continue learning**

Here are some useful resources:

* [Hugging Face Learn](https://huggingface.co/learn?utm_source=chatgpt.com) – AI and machine learning learning materials.

* [DeepLearning.AI](https://www.deeplearning.ai/?utm_source=chatgpt.com) – AI and LLM courses.

* [OpenAI Developer Documentation](https://platform.openai.com/docs?utm_source=chatgpt.com) – LLM APIs and tool integration.

* [Model Context Protocol](https://modelcontextprotocol.io/?utm_source=chatgpt.com) – Connecting AI applications to tools and data.

* [LangChain Documentation](https://python.langchain.com/docs/introduction/?utm_source=chatgpt.com) – Building LLM applications.

## **18. My recommended next steps**

Given your Java and Spring Boot background, there is an interesting progression:

## **Your AI agent learning roadmap**

1. **AI fundamentals**

   Understand LLMs, prompts, tokens and context.

2. **Python agent fundamentals**

   Build your first tool-using agent.

3. **LLM integration**

   Connect a real AI model to your application.

4. **Agent frameworks**

   Explore LangGraph and other orchestration frameworks.

5. **Java and Spring AI**

   Transfer your knowledge to the Java ecosystem and build AI-powered Spring Boot applications.

6. **Advanced agent development**

   Explore RAG, MCP, multi-agent systems and production security.

**One important piece of advice:** Don't start with LangChain, LangGraph or complex multi-agent frameworks. First understand the relationship between an LLM, an agent, tools, memory and the agent loop.

Once those concepts make sense, the frameworks become much easier to understand.

Happy learning and have fun building your first AI agent! 😊

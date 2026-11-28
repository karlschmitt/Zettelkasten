---
id: 20261128104044
title: Large language models
author: Karl Schmitt
date: 2026-11-2
---

_**Large language models (LLMs) are deep learning AI systems trained on massive text datasets to understand, process, and generate human-like language**_**.** They are the core technology behind modern AI chatbots, writing assistants, and coding tools. 

How LLMs Work

* **Next-word prediction.** At their core, LLMs operate like advanced autocomplete systems. When given a prompt, they calculate the statistical probability of which word—or piece of a word, called a **token**—should come next, generating responses one piece at a time.
* **Transformer architecture.** Almost all modern LLMs are built on a neural network design called a **Transformer**, introduced by Google researchers in 2017. Transformers use a mechanism called **self-attention** to weigh the relationships between all words in a sentence simultaneously, allowing the model to grasp context, tone, and grammar rather than reading word-by-word.
* **Parameters.** The "large" in LLM refers to the model's size, measured in billions or even trillions of **parameters**—the internal adjustable settings the model tweaks during training to learn patterns and store knowledge. 

How They Are Trained

1. **Pre-training.** The model analyzes petabytes of public text (books, websites, articles, and code) in a self-supervised process to learn grammar, facts, and reasoning patterns. 
2. **Fine-tuning and alignment.** Engineers refine the base model using curated question-and-answer examples and **Reinforcement Learning from Human Feedback (RLHF)**. This teaches the AI to follow instructions, converse naturally, and avoid harmful outputs. 

Common Uses & Limitations

While LLMs excel at **drafting content, summarizing documents, translating languages, and writing code**, they have notable constraints:

* **Hallucinations.** Because LLMs predict what sounds statistically probable rather than verifying facts against a database, they can occasionally invent plausible-sounding but false information.
* **Knowledge cutoffs and bias.** An LLM only knows what was in its training data, meaning it can inherit human biases or lack awareness of recent events unless connected to live search tools.

For a deeper technical breakdown, check out [Hugging Face's LLM overview](https://huggingface.co/learn/agents-course/en/unit1/what-are-llms) or Harvard Business School's guide on how LLMs work.

Would you like to explore a specific angle, such as:

* **Everyday applications** and how to use them effectively
* **Technical concepts** like tokens, embeddings, and transformers
* **Comparisons** between popular models (like Gemini, GPT, and Claude)

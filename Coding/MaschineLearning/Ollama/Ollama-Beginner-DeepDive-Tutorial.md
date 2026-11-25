---
id: 202611251311
title: Ollama - Absolute Beginner Deep Dive
author: Karl Schmitt
aliases: [Ollama Tutorial, Local LLM Tutorial]
type: tutorial
date: 2026-11-25
keywords: [ollama, llm, local-ai, python, powershell, windows, tutorial]
environment: Windows 11, PowerShell 7, Python 3.13
---

# Ollama - Absolute Beginner Deep Dive

A step-by-step, hands-on guide to running **large language models (LLMs) on your own Windows PC** with Ollama. You will install it, chat with a model, call it from PowerShell and Python, customize it, extract structured data, and build a small semantic search over your own notes.

Written for **Windows, PowerShell and Python**. It is also formatted for a **Zettelkasten**: front matter with an ID, a one-sentence **Zettel** (key idea) at the end of each chapter, and a list of atomic notes to extract at the end ([chapter 19](#19-atomic-notes-to-extract)).

> **What was verified?** The API, Python, Modelfile, structured-output and embedding steps were run against Ollama **0.40.18** (in a Docker container, CPU only) with tiny stand-in models, plus PowerShell 7.6 and Python 3.13. The Windows installer, tray app and GPU acceleration were **not** run. Details in [chapter 20](#20-how-this-tutorial-was-verified).

---

## Table of Contents

1. [What Is Ollama?](#1-what-is-ollama)
2. [Prerequisites and Hardware Check](#2-prerequisites-and-hardware-check)
3. [Installing Ollama on Windows](#3-installing-ollama-on-windows)
4. [Your First Conversation](#4-your-first-conversation)
5. [Managing Models](#5-managing-models)
6. [Choosing a Model](#6-choosing-a-model)
7. [The Server and the REST API](#7-the-server-and-the-rest-api)
8. [Using Ollama from Python](#8-using-ollama-from-python)
9. [Customizing Models with a Modelfile](#9-customizing-models-with-a-modelfile)
10. [Structured Outputs](#10-structured-outputs)
11. [Embeddings and Semantic Search over Your Notes](#11-embeddings-and-semantic-search-over-your-notes)
12. [Configuration and Performance](#12-configuration-and-performance)
13. [Privacy, Cloud Models and Security](#13-privacy-cloud-models-and-security)
14. [Ollama in Docker](#14-ollama-in-docker)
15. [Troubleshooting](#15-troubleshooting)
16. [Uninstall and Cleanup](#16-uninstall-and-cleanup)
17. [Exercises](#17-exercises)
18. [Quick Reference](#18-quick-reference)
19. [Atomic Notes to Extract](#19-atomic-notes-to-extract)
20. [How This Tutorial Was Verified](#20-how-this-tutorial-was-verified)

---

## 1. What Is Ollama?

**Ollama** is a free, open-source program that downloads and runs LLMs locally. Think of it as "Docker for language models": you `pull` a model once, then `run` it.

Key vocabulary:

| Term | Meaning |
|---|---|
| **LLM** | Large language model. A neural network that predicts the next piece of text (token). |
| **Model** | The downloaded weights file, e.g. `llama3.2`. |
| **Inference** | Running a model to produce an answer (as opposed to training it). |
| **Token** | A word piece. Models read and write tokens, roughly 3/4 of a word in English. |
| **Context window** | How many tokens the model can "see" at once (your prompt plus its answer). |
| **Quantization** | Compressing the weights (e.g. to 4 bit) so the model needs less memory. |
| **Embedding** | A list of numbers that represents the *meaning* of a text. |
| **Server** | Ollama runs a local HTTP server on `http://localhost:11434`. The CLI and libraries talk to it. |

Architecture in one picture:

```text
 PowerShell (ollama run ...)  --\
 Python (ollama library)      ---+-->  Ollama server  -->  model (RAM / GPU)
 Any app (HTTP, port 11434)   --/         localhost:11434
```

Why use it locally?

- **Privacy:** prompts and answers stay on your PC when you use local models.
- **Cost:** no per-token fees.
- **Offline:** works without internet after the model is downloaded.
- **Control:** change the system prompt, temperature, context size.

Trade-off: local models are smaller than the biggest cloud models, so they are less capable, and speed depends on your hardware.

> **Zettel:** Ollama is a local server that loads model weights into memory and exposes them through one HTTP API, so the CLI, Python and any other program use the same engine.
> Links: [[LLM]], [[Local-First Software]], [[REST API]]

---

## 2. Prerequisites and Hardware Check

You need:

- Windows 11 (Ollama requires Windows 10 22H2 or newer)
- PowerShell (7 recommended; `pwsh`)
- Python 3.8+ (this tutorial used 3.13)
- Free disk space: about 4 GB for the program plus the models (one small model is 1-5 GB; larger ones tens of GB)
- An NVIDIA GPU needs driver **551.61 or newer**. AMD Radeon GPUs are also supported. Without a GPU, Ollama runs on the CPU, only slower.

### 2.1 Check your machine

```powershell
# GPU name, video memory (VRAM) and driver version (NVIDIA only)
nvidia-smi --query-gpu=name,memory.total,driver_version --format=csv

# Installed RAM in GB
[math]::Round((Get-CimInstance Win32_ComputerSystem).TotalPhysicalMemory / 1GB)

# Free disk space per drive
Get-PSDrive -PSProvider FileSystem | Select-Object Name, @{n='FreeGB'; e={[math]::Round($_.Free / 1GB)}}

# Python
python --version
pip --version
```

Why this matters: a model runs fastest when it fits entirely in **VRAM**. If it does not fit, Ollama splits it between GPU and system RAM, which still works but is slower.

A rough rule of thumb (approximate, it varies by model and context size): a 4-bit quantized model needs a bit more than half a gigabyte per billion parameters, plus memory for the context. Use `ollama ps` ([chapter 5](#5-managing-models)) to see where a model actually landed.

> **Zettel:** Local LLM speed is decided by whether the model fits in VRAM; RAM and CPU are the fallback, not the goal.
> Links: [[VRAM]], [[Quantization]]

---

## 3. Installing Ollama on Windows

### 3.1 Install

1. Download `OllamaSetup.exe` from <https://ollama.com/download>.
2. Run it. **No Administrator rights are needed**; it installs into your user profile.
3. Ollama starts in the background (tray icon near the clock) and adds `ollama` to your `PATH`.

Install to a different folder (for example drive D:) by starting the installer with a flag:

```powershell
.\OllamaSetup.exe /DIR="D:\Ollama"
```

### 3.2 Verify

Open a **new** PowerShell window (the PATH change is not visible in windows opened before the install):

```powershell
ollama --version
```

If you see a version number, the CLI works. Check that the server answers:

```powershell
Invoke-RestMethod http://localhost:11434/api/version
```

You should get an object with a `version` property.

### 3.3 Where things live

| What | Location |
|---|---|
| Program | `%LOCALAPPDATA%\Programs\Ollama` |
| Logs and updates | `%LOCALAPPDATA%\Ollama` (`server.log`, `app.log`, `upgrade.log`) |
| Models and config | `%USERPROFILE%\.ollama` (models in `.ollama\models`) |

Open any of them from PowerShell:

```powershell
explorer "$env:LOCALAPPDATA\Ollama"
explorer "$env:USERPROFILE\.ollama"
```

### 3.4 Put the models on another drive (optional)

Models are big. If your C: drive is small, store them on D: by setting the user environment variable `OLLAMA_MODELS`:

```powershell
[Environment]::SetEnvironmentVariable('OLLAMA_MODELS', 'D:\Ollama\models', 'User')
```

Then **quit Ollama from the tray icon and start it again** from the Start menu (or open a new terminal), so it reads the new value. Models you already downloaded stay in the old folder; move them or pull again.

### 3.5 Startup and updates

- Ollama registers as a login item. To stop that: **Task Manager, Startup apps, ollama, Disable**.
- Ollama updates itself. Click the tray icon and choose **Restart to update** when offered.

> **Zettel:** Ollama on Windows is a per-user install that runs a background server; paths and the model folder are configured through user environment variables.
> Links: [[Windows Environment Variables]]

---

## 4. Your First Conversation

### 4.1 Download and run a model

`llama3.2` is a small, widely used model, a good first choice (a download of roughly 2 GB):

```powershell
ollama run llama3.2
```

The first time, Ollama downloads the model ("pulling"), then opens an interactive prompt:

```text
>>> Why is the sky blue?
```

Type a question and press Enter. To leave, type `/bye` (or press `Ctrl+D`).

### 4.2 Useful chat commands

Inside the `>>>` prompt:

| Command | Effect |
|---|---|
| `/?` | List all slash commands |
| `/bye` | Exit |
| `/set parameter num_ctx 8192` | Change a parameter for this session (here: the context window) |
| `"""` | Start and end a **multi-line** message |

Multi-line example:

```text
>>> """Summarize this:
... Zettelkasten is a method where each note holds one idea
... and notes are linked together.
... """
```

### 4.3 One-shot questions

Without the interactive prompt, pass the question as an argument. The answer prints and the command ends:

```powershell
ollama run llama3.2 "Explain what a Zettelkasten is in two sentences."
```

You can also pipe text in, which is handy for notes. PowerShell has no `<` file redirect, so use `Get-Content`:

```powershell
Get-Content -Raw .\my-note.md | ollama run llama3.2 "Summarize this note in one sentence:"
```

### 4.4 What to expect

- The first answer is slower because the model must be loaded into memory.
- Models make mistakes and invent facts ("hallucinate"). Small models do so more often. Always verify important answers.
- The model only knows what it was trained on plus what you put in the conversation.

> **Zettel:** `ollama run <model>` is both a downloader and a chat client; the same call works interactively, one-shot, or with piped input.
> Links: [[Prompting]], [[Hallucination]]

---

## 5. Managing Models

### 5.1 The essential commands

| Command | Purpose |
|---|---|
| `ollama pull <model>` | Download a model without chatting |
| `ollama list` (or `ollama ls`) | Show downloaded models and their sizes |
| `ollama show <model>` | Show details: architecture, parameters, context length, quantization |
| `ollama ps` | Show models currently **loaded in memory** |
| `ollama stop <model>` | Unload a model from memory right now |
| `ollama cp <src> <dst>` | Copy (rename) a model |
| `ollama rm <model>` | Delete a model from disk |
| `ollama serve` | Start the server manually (the Windows app normally does this) |

Try them:

```powershell
ollama pull llama3.2
ollama list
ollama show llama3.2
ollama ps
```

### 5.2 Reading `ollama ps`

```text
NAME           ID            SIZE     PROCESSOR   CONTEXT   RUNNER     UNTIL
llama3.2:latest  a80c4f17acd5  2.8 GB   100% GPU    4096      llamacpp   4 minutes from now
```

(The numbers are illustrative; columns can differ between versions.) The key column is **PROCESSOR**:

- `100% GPU`: loaded entirely into VRAM (fastest)
- `100% CPU`: loaded in system RAM only
- `48%/52% CPU/GPU`: split between both

**UNTIL** shows when the model is unloaded. By default a model stays in memory for **5 minutes** after the last request. Unload immediately with `ollama stop llama3.2`.

### 5.3 Model names and tags

A model name looks like `name:tag`, for example `llama3.2:1b`. The tag usually selects a **size** or a **variant**. Without a tag, Ollama uses `latest`. Browse the catalog at <https://ollama.com/search>.

> **Zettel:** `pull`, `list`, `ps`, `stop`, `rm` map to download, disk, memory, unload and delete; knowing the difference between "on disk" and "loaded in memory" explains most surprises.
> Links: [[Ollama CLI]]

---

## 6. Choosing a Model

There is no single best model. Decide by task and hardware.

| Question | Guidance |
|---|---|
| How big? | Pick a size that fits your VRAM (see [chapter 2](#2-prerequisites-and-hardware-check)). Smaller (1-4 billion parameters) is fast; larger (7-14B+) is smarter but needs more memory. |
| What task? | General chat, coding, vision (images), embeddings (search), tool calling. Model pages on ollama.com list the capabilities. |
| Which language? | Many small models are strongest in English. Test with your own language (for example German). |
| Which license? | Check the license on the model page if you plan commercial use. |

Examples mentioned in the official docs: `llama3.2`, `gemma4`, `gpt-oss`, `qwen3.5`, and embedding models like `embeddinggemma` and `nomic-embed-text`. New models arrive frequently, so check the catalog instead of trusting any fixed list.

### 6.1 Quantization in practice

Most models in the catalog are already quantized (typically 4-bit). A tag can select a different quantization. Lower bits means less memory and speed gains but slightly lower quality. For a beginner, use the default tag.

### 6.2 A simple method to compare models

1. Write 5 prompts you really care about (summarize a note, suggest tags, explain a concept).
2. Run each prompt on 2-3 candidate models.
3. Keep the smallest model that gives answers you accept.

> **Zettel:** Choose the smallest model that does your task acceptably; hardware fit beats raw model size.
> Links: [[Model Selection]], [[Quantization]]

---

## 7. The Server and the REST API

Everything you did in the CLI goes through the HTTP API at `http://localhost:11434`. Learning it lets you use Ollama from any language.

### 7.1 Two main endpoints

| Endpoint | Use |
|---|---|
| `POST /api/generate` | Single prompt in, text out |
| `POST /api/chat` | A list of messages (with roles) in, assistant message out |

Other useful ones: `GET /api/tags` (installed models), `GET /api/ps` (loaded models), `GET /api/version`, `POST /api/embed` (embeddings, see [chapter 11](#11-embeddings-and-semantic-search-over-your-notes)).

### 7.2 Calling it from PowerShell

List installed models and check the version:

```powershell
(Invoke-RestMethod -Uri http://localhost:11434/api/tags).models | Select-Object name, size
(Invoke-RestMethod -Uri http://localhost:11434/api/version).version
```

Generate text. Build the body as a PowerShell hashtable and let `ConvertTo-Json` do the JSON quoting:

```powershell
$body = @{
    model  = 'llama3.2'
    prompt = 'Say hi in three words.'
    stream = $false
} | ConvertTo-Json

$r = Invoke-RestMethod -Uri http://localhost:11434/api/generate `
     -Method Post -Body $body -ContentType 'application/json'

$r.response
```

`stream = $false` returns the complete answer as **one** JSON object. Without it, the server sends many small JSON objects (one per line) while it generates.

Chat with roles. Pass `-Depth` so nested objects are not cut off:

```powershell
$body = @{
    model    = 'llama3.2'
    messages = @(
        @{ role = 'system'; content = 'Be brief.' },
        @{ role = 'user';   content = 'Say hi' }
    )
    stream   = $false
    options  = @{ temperature = 0 }
} | ConvertTo-Json -Depth 5

$r = Invoke-RestMethod -Uri http://localhost:11434/api/chat `
     -Method Post -Body $body -ContentType 'application/json'

$r.message.content
```

The official docs show this one-liner style as well:

```powershell
(Invoke-WebRequest -Method POST -Uri http://localhost:11434/api/generate `
  -Body '{"model":"llama3.2", "prompt":"Why is the sky blue?", "stream": false}').Content | ConvertFrom-Json
```

### 7.3 Messages and roles

| Role | Purpose |
|---|---|
| `system` | Instructions that shape behavior ("You are a concise assistant") |
| `user` | What the human says |
| `assistant` | What the model said earlier |

The model has **no memory** between requests. For a conversation you must send the whole history every time. This is the most important idea for building chat apps.

### 7.4 `curl.exe`

In PowerShell 7, `curl` runs the real `curl.exe` (in Windows PowerShell 5.1 it is an alias for `Invoke-WebRequest`, so type `curl.exe`). The safest way to send JSON is to pipe it in:

```powershell
$body = @{ model = 'llama3.2'; prompt = 'hi'; stream = $false } | ConvertTo-Json -Compress
$body | curl.exe -s http://localhost:11434/api/generate -H 'Content-Type: application/json' -d '@-'
```

`-d '@-'` means "read the request body from standard input".

### 7.5 Streaming

For streaming, the Python library is much easier than PowerShell ([chapter 8](#8-using-ollama-from-python)).

> **Zettel:** The Ollama API is stateless: every request must carry the entire conversation, so "memory" is just a list you keep and resend.
> Links: [[REST API]], [[Stateless Protocols]], [[PowerShell]]

---

## 8. Using Ollama from Python

### 8.1 Set up a virtual environment

A virtual environment keeps this project's packages separate from the rest of your system.

```powershell
mkdir $HOME\ollama-tutorial
Set-Location $HOME\ollama-tutorial

python -m venv .venv
.\.venv\Scripts\Activate.ps1

pip install ollama
```

Your prompt now starts with `(.venv)`. To leave later: `deactivate`.

> If PowerShell refuses to run `Activate.ps1` ("running scripts is disabled"), allow local scripts for your user once: `Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned`.

Make sure Ollama is running and the model is downloaded (`ollama pull llama3.2`).

### 8.2 First script

Create `chat_basic.py`:

```python
from ollama import chat

MODEL = "llama3.2"

response = chat(
    model=MODEL,
    messages=[{"role": "user", "content": "Explain what an LLM is in one sentence."}],
)

print(response.message.content)
```

Run it:

```powershell
python chat_basic.py
```

`response` is an object. `response.message.content` is the text. (Dictionary style, `response["message"]["content"]`, also works.)

### 8.3 Streaming

Print the answer word by word instead of waiting. Create `chat_stream.py`:

```python
from ollama import chat

MODEL = "llama3.2"

stream = chat(
    model=MODEL,
    messages=[{"role": "user", "content": "Count from 1 to 5."}],
    stream=True,
)

for chunk in stream:
    print(chunk.message.content, end="", flush=True)
print()
```

### 8.4 A chat with memory

Remember: the server forgets everything between calls, so the script keeps a `history` list. Create `chat_history.py`:

```python
from ollama import chat

MODEL = "llama3.2"

history = [{"role": "system", "content": "You are a concise assistant. Answer in one short sentence."}]

print("Type 'exit' to quit.")
while True:
    user_text = input("You: ").strip()
    if user_text.lower() in {"", "exit", "quit"}:
        break
    history.append({"role": "user", "content": user_text})
    reply = chat(model=MODEL, messages=history)
    answer = reply.message.content
    print("AI:", answer)
    history.append({"role": "assistant", "content": answer})

print(f"Conversation had {len(history)} messages.")
```

Try: "My name is Karl." then "What is my name?". With a capable model the second answer uses the first message because both are in `history`.

### 8.5 Options, model list, errors

Create `options_errors.py`:

```python
import ollama

MODEL = "llama3.2"

# 1) Options: control randomness and context size
response = ollama.chat(
    model=MODEL,
    messages=[{"role": "user", "content": "Name one planet."}],
    options={"temperature": 0, "num_ctx": 4096},
)
print("Answer:", response.message.content)
print("Tokens in/out:", response.prompt_eval_count, response.eval_count)

# 2) List local models
for m in ollama.list().models:
    print(f"{m.model:25} {m.size / 1e6:8.0f} MB")

# 3) Error handling: model that does not exist
try:
    ollama.chat(model="does-not-exist", messages=[{"role": "user", "content": "hi"}])
except ollama.ResponseError as e:
    print("Error:", e.error, "| status:", e.status_code)

# 4) Which models are loaded in memory right now?
print("Running models:", [m.model for m in ollama.ps().models])
```

What the options mean:

| Option | Meaning |
|---|---|
| `temperature` | Randomness. `0` is the most deterministic; higher (e.g. `1`) is more creative. |
| `num_ctx` | Context window size in tokens. Bigger needs more memory. |
| `top_p`, `min_p` | Other sampling controls that limit which tokens may be chosen. |

If the Ollama server is not running, Python raises a connection error instead of `ResponseError`. A `ResponseError` with status `404` means the model name is wrong or not pulled.

### 8.6 Other things the library can do

The library mirrors the REST API: `ollama.generate`, `ollama.show`, `ollama.pull`, `ollama.copy`, `ollama.delete`, `ollama.embed`, plus `Client` (custom host) and `AsyncClient` (async/await):

```python
from ollama import Client
client = Client(host="http://localhost:11434")
```

> **Zettel:** The Python library is a thin wrapper over the REST API; a chat "session" is nothing more than a list of messages that your code appends to and resends.
> Links: [[Python]], [[Virtual Environments]], [[Chat Memory]]

---

## 9. Customizing Models with a Modelfile

A **Modelfile** is a small recipe that builds a new model on top of an existing one: it sets a system prompt, parameters, or example messages. Nothing is retrained; you only change defaults.

### 9.1 Create one

In PowerShell 7, a here-string writes the file without a byte-order mark (BOM). The closing `'@` must be at the start of its line:

```powershell
@'
FROM llama3.2
PARAMETER temperature 0.2
PARAMETER num_ctx 4096
SYSTEM """You are Zetti, a helpful assistant for Zettelkasten users. Always answer in one short sentence."""
'@ | Set-Content -Path Modelfile -Encoding utf8
```

Instructions you will use most:

| Instruction | Purpose |
|---|---|
| `FROM` | **Required.** Base model (e.g. `llama3.2`), or a local GGUF file path. |
| `PARAMETER` | Default setting such as `temperature`, `num_ctx`, `top_p`. |
| `SYSTEM` | The system message. |
| `MESSAGE` | Example conversation turns (`MESSAGE user ...`, `MESSAGE assistant ...`). |
| `TEMPLATE` | The raw prompt template (advanced; model specific). |

Instruction names are not case sensitive, and `#` starts a comment.

### 9.2 Build and run it

```powershell
ollama create zetti -f Modelfile
ollama list
ollama run zetti "What is a Zettelkasten?"
```

Inspect what you built:

```powershell
ollama show zetti
ollama show zetti --modelfile
```

`--modelfile` prints the full resolved recipe, including the template and license inherited from the base model.

### 9.3 Delete or copy

```powershell
ollama cp zetti zetti-v2
ollama rm zetti-v2
```

A custom model is only a small layer of settings on top of the base model, so it takes almost no extra disk space.

### 9.4 Using it from Python

```python
from ollama import chat
r = chat(model="zetti", messages=[{"role": "user", "content": "What is a Zettelkasten?"}])
print(r.message.content)
```

Python can also create models: `ollama.create(model='example', from_='llama3.2', system='You are Mario.')`.

> **Zettel:** A Modelfile does not train anything; it bundles a base model with default parameters and a system prompt under a new name.
> Links: [[Prompt Engineering]], [[System Prompt]]

---

## 10. Structured Outputs

Free text is hard to process in code. **Structured outputs** force the model to answer in JSON that matches a schema.

### 10.1 With Pydantic

Create `structured.py`:

```python
from ollama import chat
from pydantic import BaseModel

MODEL = "llama3.2"


class Note(BaseModel):
    title: str
    tags: list[str]
    summary: str


text = (
    "The Zettelkasten method stores ideas as small, linked notes. "
    "Each note holds exactly one idea, and links connect related notes."
)

response = chat(
    model=MODEL,
    messages=[{"role": "user", "content": f"Turn this text into a note:\n{text}"}],
    format=Note.model_json_schema(),
    options={"temperature": 0},
)

note = Note.model_validate_json(response.message.content)
print(note)
print(type(note.tags), note.title)
```

How it works:

1. `Note` describes the shape of the answer.
2. `format=Note.model_json_schema()` tells Ollama to constrain the output to that schema.
3. `Note.model_validate_json(...)` parses it back into a real Python object and raises an error if it does not fit.

(`pydantic` is installed automatically together with `ollama`.)

### 10.2 Tips

- Use `temperature` `0` for repeatable results.
- The schema forces the **format**, not the **truth**. Facts can still be wrong.
- Mention what you want in the prompt as well; the schema alone is a weaker hint than schema plus instructions.
- Plain `format="json"` asks for any valid JSON without a schema.

### 10.3 Zettelkasten idea

Change `text` to read a note file and ask for `tags` and a `summary`. Review the suggestions yourself before you write them into your notes ([chapter 17](#17-exercises)).

> **Zettel:** A JSON schema turns an LLM from a text writer into a function that returns typed data, which makes it usable inside programs.
> Links: [[Pydantic]], [[JSON Schema]]

---

## 11. Embeddings and Semantic Search over Your Notes

An **embedding** model turns text into a vector (a long list of numbers). Texts with similar *meaning* get similar vectors, even without shared words. Compare vectors with **cosine similarity** (closer to 1 means more similar).

This is the basis of semantic search and RAG (retrieval-augmented generation), and it fits a Zettelkasten well: "find notes related to this idea".

### 11.1 Get an embedding model

```powershell
ollama pull embeddinggemma
```

Try it from the CLI (the output is a JSON array of numbers):

```powershell
ollama run embeddinggemma "Hello world"
```

### 11.2 In Python

```python
import ollama

single = ollama.embed(model="embeddinggemma", input="The quick brown fox")
print(len(single["embeddings"][0]))     # length of one vector

batch = ollama.embed(model="embeddinggemma", input=["one text", "another text"])
print(len(batch["embeddings"]))         # 2 vectors
```

Rules: use the **same** embedding model for the notes and for the query, and never mix vectors from different models.

### 11.3 A semantic search for a folder of Markdown notes

Create `search_notes.py`:

```python
import math
import sys
from pathlib import Path

import ollama

EMBED_MODEL = "embeddinggemma"


def cosine(a, b):
    dot = sum(x * y for x, y in zip(a, b))
    norm_a = math.sqrt(sum(x * x for x in a))
    norm_b = math.sqrt(sum(y * y for y in b))
    return dot / (norm_a * norm_b)


def main(folder, query):
    files = sorted(Path(folder).rglob("*.md"))
    if not files:
        sys.exit(f"No .md files found in {folder}")

    # Only the first 2000 characters of each note are embedded (keeps requests small).
    texts = [f.read_text(encoding="utf-8")[:2000] for f in files]

    note_vectors = ollama.embed(model=EMBED_MODEL, input=texts).embeddings
    query_vector = ollama.embed(model=EMBED_MODEL, input=query).embeddings[0]

    scored = sorted(
        ((cosine(query_vector, vec), f) for vec, f in zip(note_vectors, files)),
        key=lambda pair: pair[0],
        reverse=True,
    )
    for score, f in scored[:5]:
        print(f"{score:.3f}  {f.name}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        sys.exit('Usage: python search_notes.py <folder> "<query>"')
    main(sys.argv[1], sys.argv[2])
```

Run it against a folder of notes:

```powershell
python search_notes.py D:\CodingDojo\Tutorials "how do I run software in isolation"
```

A quick test with three small notes (one about the Zettelkasten method, one about Docker containers, one about sourdough bread) ranked the right note first for both "how do I organise my knowledge" (Zettelkasten, 0.54) and "running software in isolation" (Docker, 0.50), even though the query words do not appear in the notes. That is semantic search.

### 11.4 Limits of this simple version

- It re-embeds every note on every run. For hundreds of notes, save the vectors to a file (for example JSON or SQLite) and only embed new or changed notes.
- It cuts each note at 2000 characters. Long notes should be split into chunks first.
- Very large batches may hit memory or request limits; embed in groups of, say, 32 notes.

> **Zettel:** Embeddings convert meaning into geometry: similar ideas are close vectors, so "related notes" becomes a nearest-neighbour search.
> Links: [[Embeddings]], [[Cosine Similarity]], [[RAG]], [[Zettelkasten]]

---

## 12. Configuration and Performance

Ollama is configured with **environment variables**. On Windows, set them for your user, then quit and restart Ollama:

```powershell
[Environment]::SetEnvironmentVariable('OLLAMA_KEEP_ALIVE', '30m', 'User')
```

(Quit Ollama from the tray icon first, then start it from the Start menu so it picks up the change. A terminal opened before the change does not see it.)

Read a value back, or remove it:

```powershell
[Environment]::GetEnvironmentVariable('OLLAMA_KEEP_ALIVE', 'User')
[Environment]::SetEnvironmentVariable('OLLAMA_KEEP_ALIVE', $null, 'User')
```

### 12.1 The important variables

| Variable | Purpose | Default |
|---|---|---|
| `OLLAMA_HOST` | Address and port the server listens on | `127.0.0.1:11434` |
| `OLLAMA_MODELS` | Folder where models are stored | `%USERPROFILE%\.ollama\models` |
| `OLLAMA_KEEP_ALIVE` | How long a model stays loaded after use | 5 minutes |
| `OLLAMA_CONTEXT_LENGTH` | Default context window (tokens) | 4096 (per the FAQ) |
| `OLLAMA_MAX_LOADED_MODELS` | Models loaded at the same time | 3 per GPU (3 on CPU) |
| `OLLAMA_NUM_PARALLEL` | Parallel requests per model | 1 on most backends |
| `OLLAMA_MAX_QUEUE` | Queued requests before returning errors | 512 |
| `OLLAMA_FLASH_ATTENTION` | Force Flash Attention on (`1`) or off (`0`) | automatic |
| `OLLAMA_KV_CACHE_TYPE` | Memory saving for the context cache (`f16`, `q8_0`, `q4_0`) | `f16` |
| `OLLAMA_NO_CLOUD` | Disable Ollama's cloud features (`1`) | off |
| `HTTPS_PROXY` | Proxy for model downloads | none |

Run `ollama serve --help` for the list your version supports.

### 12.2 Context length

The context window holds your prompt, the history, and the answer. If you exceed it, the oldest content is cut off. A larger window needs more memory, so raise it only when needed:

- per session: `/set parameter num_ctx 8192`
- per request: `options={"num_ctx": 8192}` in Python
- per model: `PARAMETER num_ctx 8192` in a Modelfile
- globally: `OLLAMA_CONTEXT_LENGTH`

### 12.3 Keep a model loaded or unload it

Per request, `keep_alive` accepts a duration (`"10m"`), seconds, `-1` (keep loaded forever), or `0` (unload immediately after answering). It overrides `OLLAMA_KEEP_ALIVE`.

Preload a model (loads it without generating text):

```powershell
$body = @{ model = 'llama3.2'; keep_alive = -1 } | ConvertTo-Json
Invoke-RestMethod -Uri http://localhost:11434/api/generate -Method Post -Body $body -ContentType 'application/json'
```

Unload it:

```powershell
ollama stop llama3.2
```

### 12.4 Is my GPU used?

```powershell
ollama ps
```

Look at the **PROCESSOR** column. If you expected `100% GPU` but see CPU, the model is probably too large for your VRAM, the GPU driver is too old, or the GPU is not supported. See [troubleshooting](#15-troubleshooting).

> **Zettel:** Ollama behavior is steered by environment variables read at server start, so a change only takes effect after restarting the server.
> Links: [[Environment Variables]], [[Context Window]]

---

## 13. Privacy, Cloud Models and Security

### 13.1 Local by default

When you run local models, the prompts and answers stay on your machine; Ollama states that it does not see your prompts or data in that case. Downloading a model does contact ollama.com.

### 13.2 Cloud models (optional)

Ollama can also offload to hosted "cloud" models after you sign in (`ollama signin`); cloud model names carry a `-cloud` suffix. Those requests go to Ollama's servers. If you want a strictly local setup, disable the cloud features:

```powershell
[Environment]::SetEnvironmentVariable('OLLAMA_NO_CLOUD', '1', 'User')
```

Restart Ollama afterwards. According to the docs, the logs then show `Ollama cloud disabled: true`.

### 13.3 Network exposure

By default the server listens only on `127.0.0.1` (your own computer). That is the safe setting. If you set `OLLAMA_HOST=0.0.0.0` the API is reachable from your network, and **there is no authentication**. Anyone who can reach the port can use your models and your hardware. Only do that on a trusted network, behind a firewall or a reverse proxy with access control.

### 13.4 Other safety points

- Treat model output as untrusted text. Do not run generated code or shell commands without reading them.
- Downloaded models come from third parties; check the license and the source.
- Do not paste secrets into prompts for hosted/cloud services.

> **Zettel:** Local-only is the default privacy guarantee of Ollama; it ends the moment you enable cloud models or bind the server to a non-local address.
> Links: [[Privacy]], [[Network Security]]

---

## 14. Ollama in Docker

You can run the server in a container instead of installing the Windows app (useful for isolation or experiments). See [[Docker-in-Docker-Beginner-DeepDive-Tutorial]] for Docker basics.

```powershell
docker run -d --name ollama -p 11434:11434 -v ollama-data:/root/.ollama ollama/ollama

docker exec -it ollama ollama pull llama3.2
docker exec -it ollama ollama run llama3.2
```

- `-v ollama-data:/root/.ollama` keeps your models in a Docker volume so they survive container removal.
- The container above uses the **CPU**. GPU use in Docker on Windows (WSL 2 backend) needs the NVIDIA container toolkit and the `--gpus=all` flag; see the `ollama/ollama` page on Docker Hub. This was not tested here.
- If the Windows Ollama app is also running, port `11434` is already taken. Publish a different host port, for example `-p 11435:11434`, and point clients to `http://localhost:11435` (`OLLAMA_HOST` in Python).
- Clean up when you are done:

```powershell
docker rm -f ollama
docker volume rm ollama-data
```

> **Zettel:** The Ollama API is the same inside or outside a container; Docker only changes where the models live and whether the GPU is reachable.
> Links: [[Docker]], [[Containers]]

---

## 15. Troubleshooting

| Symptom | Likely cause | Fix |
|---|---|---|
| `ollama : The term 'ollama' is not recognized` | Terminal opened before install, so PATH is old | Open a **new** PowerShell window; check `%LOCALAPPDATA%\Programs\Ollama` exists |
| `Error: could not connect to ollama server` / Python connection error | Server not running | Start Ollama from the Start menu, or run `ollama serve` in a separate window |
| `Invoke-RestMethod` times out or refuses connection | Server not running, wrong port, or `OLLAMA_HOST` changed | `Invoke-RestMethod http://localhost:11434/api/version`; check the variable |
| Python `ResponseError` with status 404 | Model name wrong or not pulled | `ollama list`; `ollama pull <model>` |
| Port 11434 already in use | Another Ollama instance (app or Docker) | Quit one of them or use a different port (`OLLAMA_HOST`) |
| Very slow answers | Model runs on CPU or is split CPU/GPU | `ollama ps`; use a smaller model/tag; update the GPU driver (NVIDIA 551.61+) |
| Out-of-memory errors | Model plus context too large | Smaller model, smaller `num_ctx`, `OLLAMA_KV_CACHE_TYPE=q8_0`, close other GPU programs |
| First answer slow, later ones fast | Model load time | Normal; use `OLLAMA_KEEP_ALIVE` to keep the model loaded longer |
| Model "forgets" the conversation | You did not resend history | Send the full `messages` list each call ([chapter 8.4](#84-a-chat-with-memory)) |
| Answers cut off or ignore early parts of a long text | Context window exceeded | Raise `num_ctx` (memory cost) or shorten the input |
| Download fails behind a proxy | Proxy not configured | Set `HTTPS_PROXY`; do **not** set `HTTP_PROXY` (Ollama pulls over HTTPS) |
| Strange squares instead of progress bars | Old terminal font | Use Windows Terminal or change the font |
| `Activate.ps1 cannot be loaded` | Script execution policy | `Set-ExecutionPolicy -Scope CurrentUser -ExecutionPolicy RemoteSigned` |
| Modelfile error about unexpected characters | File saved with a BOM or odd encoding | Create it with `Set-Content -Encoding utf8` in PowerShell 7 |
| `OLLAMA_MODELS` change has no effect | Ollama not restarted, or old terminal | Quit from tray, start again, open a new terminal |
| Browser `localhost:11434` unreachable while Ollama runs | Firewall, VPN, or proxy interfering | Test with `Invoke-RestMethod`; check security software |

### 15.1 Read the logs

```powershell
Get-Content "$env:LOCALAPPDATA\Ollama\server.log" -Tail 50
Get-Content "$env:LOCALAPPDATA\Ollama\server.log" -Tail 20 -Wait   # follow live; Ctrl+C to stop
```

`server.log` has server messages (including GPU detection), `app.log` has the tray app, `upgrade.log` has updates.

### 15.2 Quick health checklist

```powershell
ollama --version
Invoke-RestMethod http://localhost:11434/api/version
ollama list
ollama ps
```

> **Zettel:** Most Ollama problems fall into four buckets: server not running, model not pulled, model too big for memory, or context too small.
> Links: [[Troubleshooting Method]]

---

## 16. Uninstall and Cleanup

### 16.1 Remove models you no longer need

```powershell
ollama list
ollama rm <model>
```

### 16.2 Remove the tutorial files

```powershell
deactivate                     # leave the virtual environment first
Set-Location ~
Remove-Item -Recurse -Force $HOME\ollama-tutorial
```

### 16.3 Uninstall Ollama

Use **Windows Settings, Apps, Installed apps, Ollama, Uninstall**. If you changed `OLLAMA_MODELS`, the uninstaller does **not** delete those downloaded models; delete that folder yourself. Remove leftover user variables if you set any:

```powershell
foreach ($v in 'OLLAMA_MODELS','OLLAMA_KEEP_ALIVE','OLLAMA_NO_CLOUD','OLLAMA_HOST') {
    [Environment]::SetEnvironmentVariable($v, $null, 'User')
}
```

---

## 17. Exercises

1. **Smallest useful model:** Pull `llama3.2:1b` and `llama3.2` (if available). Compare speed (`ollama ps`) and answer quality on three of your own prompts.
2. **Stateless proof:** In PowerShell, call `/api/chat` twice, the second time *without* the first message. Show that the model forgets your name. Then send both messages and show that it remembers.
3. **Persona:** Create a Modelfile named `german-tutor` that answers only in simple German. Test it from the CLI and from Python.
4. **Tag suggester:** Extend `structured.py` to read a Markdown note path from `sys.argv`, and return `tags` (3 to 5 items) and a one-sentence `summary`. Print the result as YAML front matter.
5. **Related notes:** Run `search_notes.py` on your Zettelkasten folder with five queries. Are the top results what you expect? Which note should have been found but was not?
6. **Cache the vectors:** Modify `search_notes.py` to save embeddings in a `vectors.json` file and only re-embed notes whose modification time changed.
7. **Context experiment:** Paste a long text, ask about its *first* paragraph, and compare results with `num_ctx` 2048, 4096 and 8192. Watch memory in `ollama ps`.
8. **Local-only audit:** Set `OLLAMA_NO_CLOUD=1`, restart Ollama and confirm in `server.log` that the cloud is disabled.
9. **Docker twin:** Run Ollama in Docker on port 11435 next to the Windows app and call both from one Python script using two `Client(host=...)` objects.

---

## 18. Quick Reference

```powershell
# --- Setup / info -------------------------------------------------
ollama --version
Invoke-RestMethod http://localhost:11434/api/version

# --- Models -------------------------------------------------------
ollama pull llama3.2              # download
ollama list                       # on disk
ollama show llama3.2              # details
ollama ps                         # loaded in memory (+ GPU/CPU)
ollama stop llama3.2              # unload now
ollama cp llama3.2 my-copy
ollama rm my-copy

# --- Chat ---------------------------------------------------------
ollama run llama3.2                              # interactive (/bye to exit)
ollama run llama3.2 "One-shot question"
Get-Content -Raw note.md | ollama run llama3.2 "Summarize:"

# --- Custom model -------------------------------------------------
ollama create zetti -f Modelfile
ollama show zetti --modelfile

# --- Python -------------------------------------------------------
python -m venv .venv; .\.venv\Scripts\Activate.ps1; pip install ollama

# --- Environment variable (user level; restart Ollama afterwards) -
[Environment]::SetEnvironmentVariable('OLLAMA_KEEP_ALIVE', '30m', 'User')

# --- Logs ---------------------------------------------------------
Get-Content "$env:LOCALAPPDATA\Ollama\server.log" -Tail 50
```

```python
from ollama import chat, embed
chat(model="llama3.2", messages=[{"role": "user", "content": "Hi"}]).message.content
chat(model="llama3.2", messages=[...], stream=True)              # iterate over chunks
chat(model="llama3.2", messages=[...], format=Schema.model_json_schema())
chat(model="llama3.2", messages=[...], options={"temperature": 0, "num_ctx": 4096})
embed(model="embeddinggemma", input=["text 1", "text 2"]).embeddings
```

| Concept | Remember |
|---|---|
| Port | `11434`, bound to localhost by default |
| `ollama ps` | What is in memory, and on GPU or CPU |
| Keep-alive | 5 minutes by default |
| Chat memory | You resend the full `messages` list |
| Context length | 4096 tokens by default (per the FAQ); raise with `num_ctx` |
| Embeddings | Same model for notes and queries; compare with cosine similarity |
| Environment variables | Set at user level, then restart Ollama |
| `ollama pull` vs `run` | `run` downloads automatically if the model is missing |

---

## 19. Atomic Notes to Extract

Candidates for permanent notes in your Zettelkasten, each containing **one idea** in your own words. The Zettel sentence at the end of each chapter is a draft.

| Proposed note title | One-line idea | Link to |
|---|---|---|
| Ollama is a local model server | One server, many clients, one HTTP API | [[LLM]], [[REST API]] |
| Model fit decides speed | A model that fits in VRAM is fast; spill-over to RAM is slow | [[VRAM]] |
| On disk vs loaded in memory | `list` shows disk, `ps` shows memory, `stop` unloads | [[Ollama CLI]] |
| LLM APIs are stateless | The caller owns and resends the conversation | [[Stateless Protocols]] |
| Temperature controls randomness | 0 deterministic, higher more varied | [[Sampling]] |
| Context window limits memory | Anything beyond the window is forgotten | [[Context Window]] |
| A Modelfile is configuration, not training | Base model plus system prompt plus parameters | [[Prompt Engineering]] |
| Schemas make LLM output machine-readable | Constrain format, still verify facts | [[JSON Schema]] |
| Embeddings turn meaning into vectors | Similar meaning means small angle | [[Embeddings]] |
| Semantic search finds notes without shared words | Nearest neighbours in embedding space | [[Zettelkasten]] |
| Local-first privacy has limits | Cloud models and open ports end the guarantee | [[Privacy]] |
| LLM output is untrusted input | Verify facts, read code before running | [[Hallucination]] |

Template for a permanent note:

```markdown
---
id: <YYYYMMDDHHmm>
title: <one idea as a statement>
tags: [ollama]
source: "[[Ollama-Beginner-DeepDive-Tutorial]]"
---

<The idea in 2-5 sentences, in your own words.>

## Why it matters
<How it connects to what you already know.>

## Links
- [[related note 1]]
- [[related note 2]]
```

---

## 20. How This Tutorial Was Verified

Honest scope of what was tested, so you know what to double-check on your machine.

**Tested** (against Ollama **0.40.18** in a Docker container, CPU only, with tiny stand-in models `smollm2:135m` and `embeddinggemma`; Python 3.13 and PowerShell 7.6):

- CLI: `pull`, `list`, `show`, `show --modelfile`, `ps`, `stop`, `cp`, `rm`, `create`, `run` with a prompt, embeddings from the CLI.
- REST API from PowerShell: `/api/tags`, `/api/version`, `/api/ps`, `/api/generate`, `/api/chat` (including `-Depth`, `stream = $false`, and the `Invoke-WebRequest` one-liner).
- Python (`ollama` library): basic chat, streaming, a multi-turn history loop, options, `ollama.list()`, `ollama.ps()`, `ResponseError` (404 for an unknown model), structured output with Pydantic, and the embedding search (the right note was ranked first).
- Modelfile built from a PowerShell 7 here-string (no BOM), then created and run.
- `curl.exe` JSON quoting in PowerShell 7 (inline single-quoted JSON, and piping with `-d '@-'`).
- On your PC: Python 3.13 venv creation and activation (execution policy `RemoteSigned`), `pip install ollama`, hardware check commands.

**Not tested:**

- The Windows installer, tray app, auto-start, updates, `OLLAMA_MODELS` and other environment variable changes on the real app.
- GPU acceleration on your NVIDIA card and the `ollama ps` GPU/CPU output on Windows.
- The real `llama3.2` model; answers shown in this tutorial are therefore described, not quoted. Tiny models gave low-quality answers in the tests, which is expected.
- Windows PowerShell 5.1 (the built-in `powershell.exe`).
- GPU in Docker, cloud models and sign-in.

**Environment notes from testing:**

- From the sandbox where the tests ran, ports published by Docker Desktop were not reachable on `localhost`, so the Docker-hosted server was reached from other containers. This does not affect the normal Windows app, which listens on `localhost:11434` directly.
- Facts about Windows paths, requirements, defaults and variables come from the official Ollama documentation (Windows, FAQ, CLI, Modelfile, Structured Outputs, Embeddings pages and the `ollama-python` README) at the time of writing. Model names and defaults change quickly; verify against <https://docs.ollama.com> if something differs.

Sources: <https://docs.ollama.com>, <https://github.com/ollama/ollama-python>, <https://ollama.com/search>.

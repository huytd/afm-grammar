# afm-grammar

Grammar and spelling-fixing tool using Apple's Foundation Model, run locally on any Apple Silicon Macs.

## Prerequisites

- **macOS 26** or later
- **Command Line Tools for Xcode 26.5** or later (provides the `FoundationModels` framework)
- **Apple Intelligence** must be enabled (the on-device language model requires it)

### Install Command Line Tools

Check your current version:

```
$ xcode-select --version
```

Install or update via CLI:

```
$ softwareupdate --install 'Command Line Tools for Xcode 26.5-26.5'
```

Alternatively, download from [Apple Developer Downloads](https://developer.apple.com/download/all/).

### Enable Apple Intelligence

1. Open **System Settings** → **Apple Intelligence & Siri**
2. Turn on **Apple Intelligence**
3. Wait for the on-device language model to download (may take a few minutes)

You can verify the model is ready by running the command — it will work once Apple Intelligence finishes its initial setup.

## How to compile

Build the binary with:

```
$ make
```

You will need to have Xcode installed to compile the Swift LLM bridge. The output of the build process is a `grammar-fix` binary that you can run.

## How to use

Run the command and pass the input string:

```
$ ./grammar-fix "he eat two apple"
# output: He ate two apples.
```

Or fix grammar for text in a file:

```
$ ./grammar-fix --file ./tests/fmf.txt
# output: (corrected text from fmf.txt)
```

```diff
-This package add extra utilities for working with LLMs via the Foundation Models framework, such as custom skills, context management helper, and a chat completions client that connects to a hosted model of your choi
+This package adds extra utilities for working with LLMs via the Foundation Models framework, such as custom skills, context management helper, and a chat completions client that connects to a hosted model of your choice.
```

## What is this and how does it work?

For a while now, Apple devices shipped with an [on-device language model](https://developer.apple.com/documentation/foundationmodels/systemlanguagemodel). The model can be used for some writing tasks, but it's only accessible for Swift via the Foundation Models framework.

This project [bridged](https://github.com/huytd/afm-grammar/blob/main/LLMBridge.swift) the API and expose it as a [C function](https://github.com/huytd/afm-grammar/blob/main/LLMBridge.h), so we can use it for simple tasks like fixing grammar.

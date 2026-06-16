# afm-grammar

Grammar and spelling-fixing tool using Apple's Foundation Model, run locally on any Apple Silicon Macs.

## How to compile

Build the binary with:

```
$ make
```

You will need to have Xcode installed to compile the Swift LLM bridge. The output of the build process is a `grammar-fix` binary that you can run.

## How to use

Run the command and pass the input string:

```
$ /grammar-fix "He ate two apples."
```

## What is this and how does it work?

For a while now, Apple devices shipped with an [on-device language model](https://developer.apple.com/documentation/foundationmodels/systemlanguagemodel). The model can be used for some writing tasks, but it's only accessible for Swift via the Foundation Models framework.

This project [bridged](https://github.com/huytd/afm-grammar/blob/main/LLMBridge.swift) the API and expose it as a [C function](https://github.com/huytd/afm-grammar/blob/main/LLMBridge.h), so we can use it for simple tasks like fixing grammar.

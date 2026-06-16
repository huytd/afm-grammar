# afm-grammar

Grammar and spelling fixing tool using Apple's Foundation Model, run locally on any Apple Silicon Macs.

## How to compile

Build the binary with:

```
$ make
```

You will need to have Xcode installed to compile the Swift LLM bridge. The output of the build process is a `grammar-fix` binary that you can run.

## How to use

Run the command and pass the input string:

```
$ /grammar-fix "he eat two apple"

# output: 
# He ate two apples.
```

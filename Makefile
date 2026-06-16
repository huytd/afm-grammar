# Compiler settings
CC = clang
SWIFTC = swiftc

# Detect macOS SDK path dynamically
SDK_PATH = $(shell xcrun --show-sdk-path)

# Compilation flags
# Note: -sdk is required for swiftc to find the Foundation frameworks
SWIFTFLAGS = -c -parse-as-library -sdk $(SDK_PATH)
CFLAGS = -Wall -Wextra -O2 -I.

# Linker flags to pull in the Swift runtime
LDFLAGS = -L/usr/lib/swift \
          -lswiftCore \
          -lswiftFoundation \
          -Xlinker -rpath -Xlinker /usr/lib/swift

# Target executable name
TARGET = grammar-fix

# Source files
C_SRCS = main.c
SWIFT_SRCS = LLMBridge.swift

# Object files
OBJS = $(C_SRCS:.c=.o) $(SWIFT_SRCS:.swift=.o)

# Default rule
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile Swift bridge source into object file
LLMBridge.o: LLMBridge.swift
	$(SWIFTC) $(SWIFTFLAGS) $< -o $@

# Compile C source into object file
%.o: %.c LLMBridge.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

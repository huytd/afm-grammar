#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include "LLMBridge.h"

char* create_system_prompt(const char* input_text) {
    const char* instruction = "Fix all grammar, spelling, and punctuation issues in the following text. "
                              "Keep all the original quotation marks and dashes, do not replace them. Do not warp the response in any quotation."
                              "Return only the corrected text without any extra commentary or explanations:\n\n";
    
    size_t total_length = strlen(instruction) + strlen(input_text) + 1;
    char* full_prompt = (char*)malloc(total_length);
    
    if (full_prompt == NULL) {
        return NULL;
    }
    
    strcpy(full_prompt, instruction);
    strcat(full_prompt, input_text);
    
    return full_prompt;
}

static char* read_file_contents(const char* path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", path);
        return NULL;
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size < 0) {
        fprintf(stderr, "Error: Could not determine file size.\n");
        close(fd);
        return NULL;
    }
    lseek(fd, 0, SEEK_SET);

    char* buf = (char*)malloc((size_t)size + 1);
    if (buf == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        close(fd);
        return NULL;
    }

    ssize_t bytes_read = read(fd, buf, (size_t)size);
    close(fd);

    if (bytes_read < 0) {
        fprintf(stderr, "Error: Failed to read file.\n");
        free(buf);
        return NULL;
    }

    buf[bytes_read] = '\0';
    return buf;
}

static void print_usage(const char* prog) {
    fprintf(stderr, "Usage: %s \"text to fix\"\n", prog);
    fprintf(stderr, "       %s --file <path>\n", prog);
}

int main(int argc, char* argv[]) {
    char* input_text = NULL;
    int allocated_input = 0;

    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "--file") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Error: --file requires a path argument.\n");
            print_usage(argv[0]);
            return 1;
        }
        input_text = read_file_contents(argv[2]);
        if (input_text == NULL) {
            return 1;
        }
        allocated_input = 1;
    } else {
        input_text = argv[1];
    }

    if (input_text == NULL || strlen(input_text) == 0) {
        fprintf(stderr, "Error: No input text provided.\n");
        if (allocated_input) free(input_text);
        return 1;
    }

    char* prompt = create_system_prompt(input_text);
    char* corrected_text = generate_text_from_apple_model(prompt);

    free(prompt);
    if (allocated_input) {
        free(input_text);
    }
    
    if (corrected_text != NULL) {
        printf("%s\n", corrected_text);
        free(corrected_text); 
    } else {
        fprintf(stderr, "Error: Failed to generate text from AFM.\n");
        return 1;
    }
    
    return 0;
}

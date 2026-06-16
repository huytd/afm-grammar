#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char* argv[]) {
    char* input_text = NULL;
    int allocated_input = 0;

    if (argc < 1) {
        fprintf(stderr, "Error: No arguments found.\n");
        return 1;
    }

    input_text = argv[1];
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

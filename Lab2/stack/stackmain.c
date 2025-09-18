// gcc -o stackmain stackmain.c arrstack.o -DARRAY_STACK
// gcc -o stackmain stackmain.c llstack.o
// ./stackmain -p a -p b -p c -p d -o -o -i -p e -i

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct stack {
    void *stackData;  // Generic pointer to either array or linked list implementation
    int size;
};

void printUsage() {
    printf("Usage: stackmain -p c|-o|-i\n");
    printf("where -p c means push character c into the stack,\n");
    printf("-o means pop the top of the stack, and\n");
    printf("-i means print stack info including top of the stack, and the size.\n");
}

int main(int argc, char *argv[]) {
    // Create a stack
    struct stack s;
    create(&s);
    printf("Created stack. [0]\n");
    
    // Parse command line arguments
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            // Push character to stack
            char c = argv[i+1][0];
            push(&s, c);
            printf("Pushed %c. [%d]\n", c, size(&s));
            i += 2;
        } else if (strcmp(argv[i], "-o") == 0) {
            // Pop character from stack
            char c = pop(&s);
            printf("Pop, returning %c [%d]\n", c, size(&s));
            i++;
        } else if (strcmp(argv[i], "-i") == 0) {
            // Print stack info
            if (!isEmpty(&s)) {
                char topChar = peek(&s);
                
                // Determine which implementation is being used
                #ifdef ARRAY_STACK
                    printf("[Stack info: array-based stack, top=%c, size=%d]\n", topChar, size(&s));
                #else
                    printf("[Stack info: ll-based stack, top=%c, size=%d]\n", topChar, size(&s));
                #endif
            } else {
                #ifdef ARRAY_STACK
                    printf("[Stack info: array-based stack, empty]\n");
                #else
                    printf("[Stack info: ll-based stack, empty]\n");
                #endif
            }
            i++;
        } else {
            // Unknown option
            printUsage();
            return 1;
        }
    }
    
    return 0;
}


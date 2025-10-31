#include <stdio.h>
#include <stdlib.h>

int main() {
    // Code segment: address of the main function
    printf("Code segment: %p\n", (void*)&main);
    
    // Heap: allocate memory on the heap
    int *heap_ptr = malloc(sizeof(int));
    printf("Heap: %p\n", (void*)heap_ptr);
    free(heap_ptr);
    
    // Stack: address of a local variable
    int stack_var;
    printf("Stack: %p\n", (void*)&stack_var);
    
    return 0;
}

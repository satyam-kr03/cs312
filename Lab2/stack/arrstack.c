#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define MAX_SIZE 100

// Define the stack structure
typedef struct stack {
    char arr[MAX_SIZE];
    int top;
} stack;

// Create stack
void create(stack *s) {
    s->top = -1;  // Initialize top to -1 (empty stack)
}

// Push a char into stack
void push(stack *s, char x) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    s->arr[++(s->top)] = x;
}

// Pop the top of the stack
char pop(stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return '\0';  // Return null character for error
    }
    return s->arr[(s->top)--];
}

// Return the top of the stack, without popping
char peek(stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return '\0';  // Return null character for error
    }
    return s->arr[s->top];
}

// Is the stack empty?
int isEmpty(stack *s) {
    return (s->top == -1);
}

// Return the size of the stack
int size(stack *s) {
    return (s->top + 1);
}
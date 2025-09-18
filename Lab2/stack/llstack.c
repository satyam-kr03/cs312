#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Define the node structure for linked list
typedef struct node {
    char data;
    struct node *next;
} node;

// Define the stack structure
typedef struct stack {
    node *top;
    int count;
} stack;

// Create stack
void create(stack *s) {
    s->top = NULL;
    s->count = 0;
}

// Push a char into stack
void push(stack *s, char x) {
    // Create a new node
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Set data and link the node to current top
    newNode->data = x;
    newNode->next = s->top;
    
    // Update top pointer and increment count
    s->top = newNode;
    s->count++;
}

// Pop the top of the stack
char pop(stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return '\0';  // Return null character for error
    }
    
    // Save the top node and its data
    node *temp = s->top;
    char value = temp->data;
    
    // Update top pointer and free the old top node
    s->top = s->top->next;
    free(temp);
    
    // Decrement count and return the popped value
    s->count--;
    return value;
}

// Return the top of the stack, without popping
char peek(stack *s) {
    if (isEmpty(s)) {
        printf("Stack is empty\n");
        return '\0';  // Return null character for error
    }
    
    return s->top->data;
}

// Is the stack empty?
int isEmpty(stack *s) {
    return (s->top == NULL);
}

// Return the size of the stack
int size(stack *s) {
    return s->count;
}
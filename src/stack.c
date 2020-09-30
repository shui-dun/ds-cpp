#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* stack_init(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->len = 0;
    stack->capacity = size;
    stack->data = (StackType*)malloc(sizeof(StackType) * size);
    return stack;
}

void stack_destroy(Stack** ptr) {
    Stack* stack = *ptr;
    free(stack->data);
    free(stack);
    *ptr = NULL;
}

int stack_push(Stack* stack, StackType data) {
    if (stack->len == stack->capacity) {
        if ((stack->data = (StackType*)realloc(stack->data, 2 * stack->len * sizeof(StackType))) == NULL)
            return -1;
        stack->capacity *= 2;
    }
    stack->data[stack->len++] = data;
    return 1;
}

StackType stack_pop(Stack* stack) {
    if (stack->len == 0)
        return 0;
    stack->len--;
    return stack->data[stack->len];
}

StackType stack_peek(Stack* stack) {
    if (stack->len == 0)
        return 0;
    return stack->data[stack->len - 1];
}

void stack_print(Stack* stack) {
    for (int i = 0; i < stack->len; i++)
        printf("%d ", *(int*)(stack->data[i]));
    putchar('\n');
}

int stack_empty(Stack* stack) {
    return stack->len == 0;
}

int stack_full(Stack* stack) {
    return stack->len == stack->capacity;
}

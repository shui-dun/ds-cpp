#pragma once

typedef void *StackType;

typedef struct {
	int len;
	int capacity;
	StackType *data;
}Stack;

Stack *stack_init(int size);

void stack_destroy(Stack **ptr);

int stack_push(Stack *stack, StackType data);

StackType stack_pop(Stack *stack);

StackType stack_peek(Stack *stack);

void stack_print(Stack *stack);

int stack_empty(Stack *stack);

int stack_full(Stack *stack);

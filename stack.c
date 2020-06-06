#include "stack.h"


void init_stack(struct stack *stack_head, int val){
	if(stack_head == NULL){
		stack_head = (struct stack*) malloc(sizeof(struct stack));
	}
	stack_head->stack_top = NULL;
	init_node(&(stack_head->stack_top), val, NULL, NULL);
}


void push(struct stack *stack_head, int val){
	insert_node(&(stack_head->stack_top), val);
}

int pop(struct stack *stack_head){
	int ret_val = stack_head->stack_top->val;
	remove_node(&(stack_head->stack_top));
	return ret_val;
}


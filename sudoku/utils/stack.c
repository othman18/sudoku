#include "stack.h"


void init_stack(struct stack **stack_head, int val){
	if(*stack_head == NULL){
		*stack_head = (struct stack*) malloc(sizeof(struct stack));
	}
	(*stack_head)->stack_top = NULL;
	init_node(&((*stack_head)->stack_top), val, NULL, NULL);
}


void push(struct stack *stack_head, int val){
	insert_node(&(stack_head->stack_top), val);
}

int pop(struct stack *stack_head){
    if(stack_head == NULL || stack_head->stack_top == NULL){
		printf("\033[0;31m");
		printf("empty stack\n");
		printf("\033[0m");
		exit(EXIT_FAILURE);
    }
	int ret_val = stack_head->stack_top->val;
	remove_node(&(stack_head->stack_top));
	return ret_val;
}


void delete_stack(struct stack **stack_head){
	if(stack_head == NULL || *stack_head ==NULL){
		return;
	}
	
	while((*stack_head)->stack_top != NULL){
		pop(*stack_head);
	}
	
	free(*stack_head);
	stack_head = NULL;
}


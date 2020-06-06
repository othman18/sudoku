#include "linkedlist.h"



void init_node(struct node **head, int val, struct node *next, struct node *prev){
	if(*head == NULL){
		*head = (struct node*)malloc(sizeof(struct node));
	}
	(*head)->val = val;
	(*head)->next = next;
	(*head)->prev = prev;
	

}


void insert_node(struct node **head, int val){
	printf("18\n");	
	if(*head == NULL){
		return;
	}
	printf("21\n");
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	printf("23\n");
	init_node(&new_node, val,
			  NULL, // new node won't have a next;
		 	  *head); // set head as prev
	printf("27\n");
	(*head)->next = new_node;
	printf("29\n");
	*head = new_node;	
}


void remove_node(struct node **head){
	if(*head == NULL){
		return;
	}
	struct node *current_node = *head;	
	*head = (*head)->prev;
	free(current_node);
	current_node = NULL;
}


void print_list(struct node *head){
	while(head != NULL){
		printf("%d, ", head->val);
		head = head->prev;
	}
	printf("\n");
}


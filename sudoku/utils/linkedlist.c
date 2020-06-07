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
	if(head == NULL || *head == NULL){
		return;
	}
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	init_node(&new_node, val,
			  NULL, // new node won't have a next;
		 	  *head); // set head as prev
	(*head)->next = new_node;
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



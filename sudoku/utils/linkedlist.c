//linkedlist.c
#include "linkedlist.h"


void init_node(struct node **head, int val, int x, int y, struct node *next, struct node *prev){
	if(*head == NULL){
		*head = (struct node*)malloc(sizeof(struct node));
	}
	(*head)->val = val;
	(*head)->x = x;
	(*head)->y = y;
	(*head)->next = next;
	(*head)->prev = prev;
}


void init_linkedlist(struct linkedlist **lst, int val, int x, int y){
	if(*lst == NULL){
		*lst = (struct linkedlist*)malloc(sizeof(struct linkedlist));
	}
	(*lst)->head = NULL;
	init_node(&((*lst)->head), val, x, y, NULL, NULL);
}


void insert_node(struct linkedlist *lst, int val, int x, int y){
	if(lst == NULL || lst->head == NULL){
		return;
	}
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	init_node(&new_node, val, x, y,
		NULL, // new node won't have a next;
		lst->head); // set head as prev
	lst->head->next = new_node;
	lst->head = new_node;
}


void remove_node(struct linkedlist *lst){
	if(lst == NULL || lst->head == NULL){
		printf(RED "error, empty list!\n" DEFAULT);
		return;
	}
	struct node *current_node = lst->head;
	lst->head = lst->head->prev;
	free(current_node);
	current_node = NULL;
}


void delete_linkedlist(struct linkedlist **lst){
	if(lst == NULL || *lst == NULL){
		return;
	}

	while((*lst)->head != NULL){
		remove_node(*lst);
	}

	free(*lst);
	lst = NULL;
}


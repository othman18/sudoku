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


void remove_node(struct node **head){
    if(head == NULL || *head == NULL){
        return;
    }
    if((*head)->prev != NULL){
        (*head)->prev->next = (*head)->next;
    }
    free(*head);
    head = NULL;
}


void init_linkedlist(struct linkedlist **lst, int val, int x, int y){
	if(*lst == NULL){
		*lst = (struct linkedlist*)malloc(sizeof(struct linkedlist));
	}
	(*lst)->head = NULL;
	init_node(&((*lst)->head), val, x, y, NULL, NULL);
}


void insert_head_linkedlist(struct linkedlist *lst, int val, int x, int y){
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


void remove_head_linkedlist(struct linkedlist *lst){
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
		remove_head_linkedlist(*lst);
	}

	free(*lst);
	lst = NULL;
}


void print_linkedlist(struct linkedlist *lst){
    if(lst == NULL || lst->head == NULL){
        return;
    }

    struct node *current_node = lst->head;
    while(current_node->prev != NULL){
        current_node = current_node->prev;
    }
    while(current_node != NULL){
        printf("%d ", current_node->val);
        current_node = current_node->next;
    }
    printf("\n");

}

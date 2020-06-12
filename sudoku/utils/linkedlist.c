// linkedlist.c
#include "linkedlist.h"


void init_node(struct node **head, int val, int x, int y, struct node *next, struct node *prev){
	if(*head == NULL){
		*head = (struct node*)malloc(sizeof(struct node));
	}
    else{
        printf(RED "error, node already init\n" DEFAULT);
        return;
    }
	(*head)->val = val;
	(*head)->x = x;
	(*head)->y = y;
	(*head)->next = next;
	(*head)->prev = prev;
}


void linkedlist_init(struct linkedlist **lst, int val, int x, int y){
	if(*lst != NULL){
        linkedlist_free(lst);
    }
    *lst = (struct linkedlist*)malloc(sizeof(struct linkedlist));
	(*lst)->head = NULL;
	init_node(&((*lst)->head), val, x, y, NULL, NULL);
    (*lst)->tail = (*lst)->head;
}


/* add tail element and update it */
void linkedlist_insert(struct linkedlist *lst, int val, int x, int y){
	if(lst == NULL || lst->head == NULL){
		return;
	}
	struct node *new_node = NULL;
	init_node(&new_node, val, x, y,
		NULL, // new node won't have a next;
		lst->tail); // set tail as prev
	lst->tail->next = new_node; // set new tail
	lst->tail = new_node;
}


/* remove tail element and update it */
void linkedlist_remove(struct linkedlist *lst){
	if(lst == NULL || lst->tail == NULL){
		printf(RED "error, empty list!\n" DEFAULT);
		return;
	}
	struct node *current_node = lst->tail;
	lst->tail = lst->tail->prev;
	free(current_node);
	current_node = NULL;
}


/* free linkedlist from memory */
void linkedlist_free(struct linkedlist **lst){
	if(lst == NULL || *lst == NULL){
		return;
	}
	while((*lst)->tail != NULL){
		linkedlist_remove(*lst);
	}
	free(*lst);
	lst = NULL;
}


void linkedlist_print(struct linkedlist *lst){
    if(lst == NULL || lst->tail == NULL){
        return;
    }
    struct node *current_node = lst->head;
    while(current_node != NULL){
        printf("%d ", current_node->val);
        current_node = current_node->next;
    }
    printf("\n");
}


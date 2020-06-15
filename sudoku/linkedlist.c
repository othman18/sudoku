// linkedlist.c
#include "linkedlist.h"


///////////////////////////////////////NODE METHODS///////////////////////


void node_init(struct node **new_node, int val, int x, int y, struct node *next,
	struct node *prev){
	if(*new_node == NULL){
		*new_node = (struct node*)malloc(sizeof(struct node));
	}
    else{
        printf(RED "Error, node already init\n" DEFAULT);
        return;
    }
	(*new_node)->val = val;
	(*new_node)->x = x;
	(*new_node)->y = y;
	(*new_node)->next = next;
	(*new_node)->prev = prev;
}


/* free node from memory */
void node_free(struct node *delete_node){
	if(delete_node == NULL){
        printf(RED "Error, node not init\n" DEFAULT);
		return;
	}
	if(delete_node->next != NULL){
		delete_node->next->prev = delete_node->prev;
	}
	if(delete_node->prev != NULL){
		delete_node->prev->next = delete_node->next;
	}
	free(delete_node);
	delete_node = NULL;
}


///////////////////////////////////////LINKEDLIST METHODS///////////////////////


/* init a linkedlist with a given value
   set head, tail and current_move as the same first node
*/
void linkedlist_init(struct linkedlist **lst, int val, int x, int y){
	if(*lst != NULL){
        linkedlist_free(lst);
    }
    *lst = (struct linkedlist*)malloc(sizeof(struct linkedlist));
	(*lst)->head = NULL;
	node_init(&((*lst)->head), val, x, y, NULL, NULL);
    (*lst)->tail = (*lst)->head;
    (*lst)->current_move = (*lst)->tail;
}


/* create a new node which will act as the new tail
   remove all the nodes after current_move and set it to tail
 */
void linkedlist_insert(struct linkedlist *lst, int val, int x, int y){
	if(lst == NULL || lst->head == NULL){
		return;
	}
    linkedlist_remove_until_current(lst); // set current_move as tail
	struct node *new_node = NULL;
	node_init(&new_node, val, x, y,
		NULL, // new node won't have a next;
		lst->tail); // set tail as prev
	
	lst->tail->next = new_node; // set new tail
	lst->tail = new_node;
    lst->current_move = lst->tail;
}


/* remove tail element and update it */
void linkedlist_remove_last(struct linkedlist *lst){
	if(lst == NULL || lst->tail == NULL){
		printf(RED "Error, empty list!\n" DEFAULT);
		return;
	}
	struct node *current_node = lst->tail;
	lst->tail = lst->tail->prev; // make the prev node as tail
	// if current_move was the tail and the tail is about to get deleted
	// set current_move as the prev of tail
	if(lst->current_move == current_node){
		lst->current_move = lst->tail;
	}
	node_free(current_node);
	current_node = NULL;
}


/* remove all the nodes after the current pointer */
void linkedlist_remove_until_current(struct linkedlist *lst){
	if(lst == NULL || lst->current_move == NULL){
		printf(RED "Error, list or current_move not init!\n" DEFAULT);
		return;
	}
	
	// delete all nodes except then set the current_move as the new tail 
	while(lst->current_move->next != NULL){
		node_free(lst->current_move->next);
	}
	lst->tail = lst->current_move;
}


/* move the current pointer to its prev*/
bool linkedlist_forward_current(struct linkedlist *lst){
	if(lst == NULL || lst->current_move == NULL){
		printf(RED "Error, list or current_move not init!\n" DEFAULT);
		return false;
	}
	if(lst->current_move == lst->tail){
		return false;
	}
	lst->current_move = lst->current_move->next;
	return true;
}


/* move the current pointer to its next*/
bool linkedlist_rewind_current(struct linkedlist *lst){
	if(lst == NULL || lst->current_move == NULL){
		printf(RED "Error, list or current_move not init!\n" DEFAULT);
		return false;
	}
	if(lst->current_move == lst->head){
		return false;
	}
	lst->current_move = lst->current_move->prev;
	return true;
}


void linkedlist_print(struct linkedlist *lst){
    if(lst == NULL){
        return;
    }
    struct node *current_node = lst->head;
    while(current_node != NULL){
        printf("%d ", current_node->val);
        current_node = current_node->next;
    }
    printf("\n");
}


void linkedlist_print_until_current(struct linkedlist *lst){
    if(lst == NULL){
        return;
    }
    struct node *current_node = lst->head;
    while(current_node!= lst->current_move->next){
        printf("%d ", current_node->val);
        current_node = current_node->next;
    }
    printf("\n");
}


/* free linkedlist from memory */
void linkedlist_free(struct linkedlist **lst){
	if(lst == NULL || *lst == NULL){
		return;
	}
	while((*lst)->tail != NULL){
		linkedlist_remove_last(*lst);
	}
	free(*lst);
	*lst = NULL;
}



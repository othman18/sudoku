/* linkedlist.c */
#include "linkedlist.h"

/*//////////////////////////////////////NODE METHODS//////////////////////*/

void node_init(struct node **new_node, int val, int x, int y, int val_prev,
               int move_type, struct node *next, struct node *prev) {
	if (*new_node == NULL) {
		*new_node = (struct node *)malloc(sizeof(struct node));
	} else {
		ll_error_handler(ERROR_NODE_ALREADY_INIT);
		return;
	}
	(*new_node)->val = val;
	(*new_node)->val_prev = val_prev;
	(*new_node)->x = x;
	(*new_node)->y = y;
	(*new_node)->move_type = move_type;
	(*new_node)->next = next;
	(*new_node)->prev = prev;
}

/**
 * Free @param delete node from the linkedlist, by setting the @param
 * delete_node->prev
 * @param delete_node->next to point at each other thus deeming delete_node
 * obsolete
 */
void node_free(struct node *delete_node) {
	if (delete_node == NULL) {
		return;
	}
	if (delete_node->next != NULL) {
		delete_node->next->prev = delete_node->prev;
	}
	if (delete_node->prev != NULL) {
		delete_node->prev->next = delete_node->next;
	}
	free(delete_node);
	delete_node = NULL;
}

/*//////////////////////////////////////LINKEDLIST METHODS////////////////////*/

void linkedlist_init(struct linkedlist **lst, int val, int x, int y,
                     int val_prev, int move_type) {
	if (*lst == NULL) {
		*lst = (struct linkedlist *)malloc(sizeof(struct linkedlist));
	} else {
		ll_error_handler(ERROR_LL_ALREADY_INIT);
		return;
	}
	(*lst)->head = NULL;
	/* head node won't have any next nor prev pointers*/
	node_init(&((*lst)->head), val, x, y, val_prev, move_type, NULL, NULL);
	/* set head, tail and current_move as the head node */
	(*lst)->tail = (*lst)->head;
	(*lst)->current_move = (*lst)->tail;
}

void linkedlist_insert(struct linkedlist *lst, int val, int x, int y,
                       int val_prev, int move_type) {
	if (lst == NULL || lst->head == NULL) {
		return;
	}
	linkedlist_remove_until_current(lst); /* set current_move as tail */
	struct node *new_node = NULL;
	node_init(&new_node, val, x, y, val_prev, move_type,
	          NULL,             /* new node won't have a next */
	          lst->tail);       /* set tail as prev */
	lst->tail->next = new_node; /* set new tail */
	lst->tail = new_node;
	lst->current_move = lst->tail;
}

void linkedlist_remove_last(struct linkedlist *lst) {
	if (lst == NULL || lst->tail == NULL) {
		ll_error_handler(ERROR_LL_EMPTY);
		return;
	}
	struct node *current_node = lst->tail;
	/* make the prev node as tail */
	lst->tail = lst->tail->prev;
	/**
	 * if current_move was the tail and the tail is about to get deleted
	 * set current_move as the prev of tail
	 */
	if (lst->current_move == current_node) {
		lst->current_move = lst->tail;
	}
	node_free(current_node);
	current_node = NULL;
}

void linkedlist_remove_until_current(struct linkedlist *lst) {
	if (lst == NULL) {
		ll_error_handler(ERROR_LL_NOT_INIT);
		return;
	} else if (lst->current_move == NULL) {
		ll_error_handler(ERROR_LL_CURR_MOVE_NOT_INIT);
		return;
	}
	/* delete all nodes till current_move then set the current_move as the new
	 * tail */
	while (lst->current_move->next != NULL) {
		node_free(lst->current_move->next);
	}
	lst->tail = lst->current_move;
}

bool linkedlist_forward_current(struct linkedlist *lst) {
	if (lst == NULL) {
		ll_error_handler(ERROR_LL_NOT_INIT);
		return false;
	} else if (lst->current_move == NULL) {
		ll_error_handler(ERROR_LL_CURR_MOVE_NOT_INIT);
		return false;
	}
	/* can't move current_mode forward, since it is tail and won't have a next*/
	if (lst->current_move == lst->tail) {
		return false;
	}
	lst->current_move = lst->current_move->next;
	return true;
}

bool linkedlist_rewind_current(struct linkedlist *lst) {
	if (lst == NULL) {
		ll_error_handler(ERROR_LL_NOT_INIT);
		return false;
	} else if (lst->current_move == NULL) {
		ll_error_handler(ERROR_LL_CURR_MOVE_NOT_INIT);
		return false;
	}
	/* can't move current_mode forward, since it is head and won't have a prev*/
	if (lst->current_move == lst->head) {
		return false;
	}
	lst->current_move = lst->current_move->prev;
	return true;
}

void linkedlist_print(struct linkedlist *lst, struct node *until_node) {
	if (lst == NULL) {
		ll_error_handler(ERROR_LL_NOT_INIT);
		return;
	} else if (until_node == NULL) {
		ll_error_handler(ERROR_NODE_NOT_INIT);
	}
	struct node *current_node = lst->head;
	while (current_node != until_node->next) {
		switch (current_node->move_type) {
			case (MOVE_DUM): /* dummy node */
				printf("%d:DUM, ", current_node->val);
				break;
			case (MOVE_INS):
				printf("%d:INS, ", current_node->val);
				break;
			case (MOVE_REM):
				printf("%d:REM, ", current_node->val_prev);
				break;
			case (MOVE_EDI):
				printf("%d:EDI, ", current_node->val_prev);
				break;
			default:
				printf("TYPE ERROR, ");
		}
		current_node = current_node->next;
	}
	printf("\n");
}

void linkedlist_free(struct linkedlist **lst) {
	if (lst == NULL || *lst == NULL) {
		return;
	}
	/* delete the whole structure by removing the tail each time*/
	while ((*lst)->tail != NULL) {
		linkedlist_remove_last(*lst);
	}
	free(*lst);
	*lst = NULL;
}

void ll_error_handler(LL_ERROR err) {
	printf(RED);
	switch (err) {
		case (ERROR_NODE_ALREADY_INIT):
			printf("Error, node already init!\n");
			break;
		case (ERROR_NODE_NOT_INIT):
			printf("Error, node not init!\n");
			break;
		case (ERROR_LL_ALREADY_INIT):
			printf("Error, linkedlist already init!\n");
			break;
		case (ERROR_LL_EMPTY):
			printf("Error, empty linkedlist!\n");
			break;
		case (ERROR_LL_NOT_INIT):
			printf("Error, linkedlist not init!\n");
			break;
		case (ERROR_LL_CURR_MOVE_NOT_INIT):
			printf("Error, current_move not init!\n");
			break;
		default:
			break;
	}
	printf(DEFAULT);
}

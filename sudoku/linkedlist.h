// linkedlist.h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

#define MOVE_DUM -1
#define MOVE_INS 0
#define MOVE_REM 1
#define MOVE_MOD 2
struct node{
	int val; // move value
	int val_prev; // prevous move 
	int x,y; // move coordinats
	int move_type; // 0 = insert, 1 = remove, 2 = modify, -1 = dummy
	struct node *next, *prev;
};

struct linkedlist{
    struct node *head, *tail,
    	*current_move; // pointer to the current move in the move history
};

/* node methods*/
void node_init(struct node **new_node, int val, int x, int y, int val_prev,
	int move_type, struct node *next, struct node *prev);
void node_free(struct node *delete_node);

/* linkedlist methods */
void linkedlist_init(struct linkedlist **lst, int val, int x, int y, int val_prev,
	int move_type);
void linkedlist_insert(struct linkedlist *lst, int val, int x, int y, int val_prev,
	int move_type);
void linkedlist_remove_last(struct linkedlist *lst);
void linkedlist_remove_until_current(struct linkedlist *lst);
bool linkedlist_forward_current(struct linkedlist *lst);
bool linkedlist_rewind_current(struct linkedlist *lst);
void linkedlist_print(struct linkedlist *lst);
void linkedlist_print_until_current(struct linkedlist *lst);
void linkedlist_free(struct linkedlist **lst);

#endif /*LINKEDLIST_H_*/

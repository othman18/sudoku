/* linkedlist.h */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

#define MOVE_DUM -1 /* DUMMY */
#define MOVE_INS 0  /* INSERT */
#define MOVE_REM 1  /* REMOVE */
#define MOVE_EDI 2  /* EDIT */

/**
 * node definition and functions
 */
struct node {
	int val;       /* move value */
	int val_prev;  /* prevous move */
	int x, y;      /* move coordinats */
	int move_type; /* 0 = insert, 1 = remove, 2 = edit, -1 = dummy */
	struct node *next, *prev;
};

/**
 * On success, the given node pointer will be allocated and initialized. If
 * however it was already initialized then an error message will be displayed
 * and the function will exit without altering the pointer.
 * @param new_node - given node pointer to init
 * @param val - given value
 * @param x - given X coordinate
 * @param y - given Y coordinate
 * @param val_prev - given previous value
 * @param move_type - given move type insert/remove/edit/dummy
 * @param next - given pointer to the next node
 * @param prev - given pointer to the previous node
 */
void node_init(struct node **new_node, int val, int x, int y, int val_prev,
               int move_type, struct node *next, struct node *prev);

/**
 * On success, the given node pointer will be freed. If however it was already
 * freed or == NULL then the function will exit without altering the pointer.
 * @param delete_node - given node pointer to free
 */
void node_free(struct node *delete_node);

/**
 * linkedlist definition and functions
 */
struct linkedlist {
	struct node *head, *tail,
	    *current_move; /* pointer to the current move in the move history */
};

/**
 * On success, the given linkedlist pointer will be allocated and initialized,
 * then a new node will be promptly initialized and set as the linkedlist's head
 * and tail. If however it was already initialized then an error message will be
 * displayed and the function will exit without altering the pointer.
 * @param lst - given linkedlist pointer to init
 * @param val - given value for the linkedlist's head node
 * @param x - given X coordinate for the linkedlist's head node
 * @param y - given Y coordinate for the linkedlist's head node
 * @param val_prev - given previous value for the linkedlist's head node
 * @param move_type - given move type insert/remove/edit/dummy for the
 * linkedlist's head node
 * @param next - given pointer to the next node for the linkedlist's head node
 * @param prev - given pointer to the previous node for the linkedlist's head
 * node
 */
void linkedlist_init(struct linkedlist **lst, int val, int x, int y,
                     int val_prev, int move_type);

/**
 * On success, a new node will be initialized and appended to the tail of the
 * given linkedlist pointer. Each node after current_move will be removed. The
 * linkedlist's tail's next will point to the newly created node and the newly
 * created node will become the linkedlist's tail. If however the linkedlist
 * pointer was NULL or its head was NULL then the function will exit without
 * creating a new node.
 * @param lst - given linkedlist pointer to insert to
 * @param val - given value for the newly appended node to the linkedlist
 * @param x - given X coordinate for the newly appended node to the linkedlist
 * @param y - given Y coordinate for the newly appended node to the linkedlist
 * @param val_prev - given previous value for the newly appended node to the
 * linkedlist
 * @param move_type - given move type insert/remove/edit/dummy for the newly
 * appended node to the linkedlist
 */
void linkedlist_insert(struct linkedlist *lst, int val, int x, int y,
                       int val_prev, int move_type);

/**
 * On success, the linkedlist's tail will be deleted. its prev will be assigned
 * as the new linkedlist tail. If however the linkedlist pointer was NULL or its
 * tail was NULL then the function will exit without deleting any node.
 * @param lst - given linkedlist pointer to remove from
 */
void linkedlist_remove_last(struct linkedlist *lst);

/**
 * On success, all the nodes from the tail up untill the current_move will be
 * deleted (and freed). If however the linkedlist pointer was NULL or its
 * current_move was NULL then the function will exit without creating a new
 * node.
 * @param lst - given linkedlist pointer to remove from
 */
void linkedlist_remove_until_current(struct linkedlist *lst);

/**
 * On success, the current_move pointer will be set as its next. If the
 * current_move was the tail then the function will exit without changing
 * anything. If however the linkedlist pointer was NULL or its current_move was
 * NULL then the function will exit without creating a new node.
 * @param lst - given linkedlist pointer to forward current_move from
 * @return
 */
bool linkedlist_forward_current(struct linkedlist *lst);

/**
 * On success, the current_move pointer will be set as its prev. If the
 * current_move was the head then the function will exit without changing
 * anything. If however the linkedlist pointer was NULL or its current_move was
 * NULL then the function will exit without creating a new node.
 * @param lst - given linkedlist pointer to rewind current_move from
 * @return
 */
bool linkedlist_rewind_current(struct linkedlist *lst);

/**
 * On success, the function prints out the linkedlist HEAD ---> TAIL with the
 * fillowing format: VAL:DUM - value of the dummy node = -1 VAL:INS - value of
 * the inserted node VAL:REM - value of the removed node (before removing it)
 * VAL:EDI - value of the edited node (before editing it)
 * If however the linkedlist pointer was NULL then the function will exit
 * without creating a new node.
 * @param lst - given linkedlist pointer to print
 */
void linkedlist_print(struct linkedlist *lst);

/**
 * On success, the function prints out the linkedlist HEAD ---> CURRENT_MOVE
 * with the fillowing format: VAL:DUM - value of the dummy node = -1 VAL:INS -
 * value of the inserted node VAL:REM - value of the removed node (before
 * removing it) VAL:EDI - value of the edited node (before editing it) If
 * however the linkedlist pointer was NULL then the function will exit without
 * creating a new node.
 * @param lst - given linkedlist pointer ti print till current_move
 */
void linkedlist_print_until_current(struct linkedlist *lst);

/**
 * On success, the given linkedlist pointer will be freed as well as all the
 * nodes within the linkedlist itself. If however it was already freed or ==
 * NULL then the function will exit without altering the pointer.
 * @param lst - given linkedlist pointer to free
 */
void linkedlist_free(struct linkedlist **lst);
#endif /*LINKEDLIST_H_*/

/* linkedlist.h */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"
#define GREEN "\033[0;32m"

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

typedef enum LL_ERROR {
	ERROR_NODE_ALREADY_INIT,
	ERROR_NODE_NOT_INIT,
	ERROR_LL_ALREADY_INIT,
	ERROR_LL_EMPTY,
	ERROR_LL_NOT_INIT,
	ERROR_LL_CURR_MOVE_NOT_INIT,
	LL_SUCCESS,
} LL_ERROR;

/**
 * On success, the given node pointer will be allocated and initialized. If
 * @param new_node - given node pointer to init
 * @param val - given value
 * @param x - given X coordinate
 * @param y - given Y coordinate
 * @param val_prev - given previous value
 * @param move_type - given move type insert/remove/edit/dummy
 * @param next - given pointer to the next node
 * @param prev - given pointer to the previous node
 * @return
 * ERROR_NODE_ALREADY_INIT - node already init, function will exit without
 * altering the pointer. LL_SUCCESS - otherwise
 */
LL_ERROR node_init(struct node **new_node, const int val, const int x,
                   const int y, const int val_prev, const int move_type,
                   struct node *next, struct node *prev);

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
 * and tail.
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
 * @return
 * ERROR_LL_ALREADY_INIT - linkedlist not init, function will exit without
 * altering the pointer. LL_SUCESS - otherwise
 */
LL_ERROR linkedlist_init(struct linkedlist **lst, const int val, const int x,
                         const int y, const int val_prev, const int move_type);

/**
 * On success, the given linkedlist pointer will be freed as well as all the
 * nodes within the linkedlist itself. If however it was already freed or ==
 * NULL then the function will exit without altering the pointer.
 * @param lst - given linkedlist pointer to free
 */
void linkedlist_free(struct linkedlist **lst);

/**
 * On success, a new node will be initialized and appended to the tail of the
 * given linkedlist pointer. Each node after current_move will be removed. The
 * linkedlist's tail's next will point to the newly created node and the newly
 * created node will become the linkedlist's tail.
 * @param lst - given linkedlist pointer to insert to
 * @param val - given value for the newly appended node to the linkedlist
 * @param x - given X coordinate for the newly appended node to the linkedlist
 * @param y - given Y coordinate for the newly appended node to the linkedlist
 * @param val_prev - given previous value for the newly appended node to the
 * linkedlist
 * @param move_type - given move type insert/remove/edit/dummy for the newly
 * appended node to the linkedlist
 * @return
 * ERROR_LL_NOT_INIT - linkedlist not init, function will exit without craeting
 * new node. ERROR_LL_EMPTY - head not init, function will exit without craeting
 * new node. LL_SUCESS - otherwise
 */
LL_ERROR linkedlist_insert(struct linkedlist *lst, const int val, const int x,
                           const int y, const int val_prev,
                           const int move_type);

/**
 * On success, the linkedlist's tail will be deleted. its prev will be assigned
 * as the new linkedlist tail.
 * @param lst - given linkedlist pointer to remove last node
 * @return
 * ERROR_LL_NOT_INIT - linkedlist not init, function will exit without removing
 * node. ERROR_LL_EMPTY - tail not init, function will exit withoutwithout
 * removing node. LL_SUCESS - otherwise
 */
LL_ERROR linkedlist_remove_last(struct linkedlist *lst);

/**
 * On success, all the nodes from the tail up untill the current_move will be
 * deleted (and freed).
 * @param lst - given linkedlist pointer to remove from
 * @return
 * ERROR_LL_NOT_INIT - linkedlist not init, function will exit without removing
 * any node. ERROR_LL_CURR_MOVE_NOT_INIT - current_move not init, function will
 * exit without removing any node. LL_SUCESS - otherwise
 */
LL_ERROR linkedlist_remove_until_current(struct linkedlist *lst);

/**
 * On success, the current_move pointer will be set as its next. If the
 * current_move was the tail then the function will exit without changing
 * anything. If however the linkedlist pointer was NULL or its current_move was
 * NULL then the function will exit without creating a new node.
 * @param lst - given linkedlist pointer to forward current_move from
 * @return
 * true -
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
 * On success, the function prints out the linkedlist HEAD ---> CURRENT_MOVE
 * with the fillowing format: VAL:DUM - value of the dummy node = -1 VAL:INS -
 * value of the inserted node VAL:REM - value of the removed node (before
 * removing it) VAL:EDI - value of the edited node (before editing it) If
 * however the linkedlist pointer was NULL then the function will exit without
 * creating a new node.
 * @param lst - given linkedlist pointer
 * @param until_node - given node pointer. Print from head node untill this node
 * @return
 * ERROR_LL_NOT_INIT -  linkedlist not init, function will exit without
 * printing. ERROR_NODE_NOT_INIT - given param node not init, function will exit
 * without printing. LL_SUCESS - otherwise
 */
LL_ERROR linkedlist_print(struct linkedlist *lst, struct node *until_node);

void ll_error_handler(const LL_ERROR err);
#endif /*LINKEDLIST_H_*/

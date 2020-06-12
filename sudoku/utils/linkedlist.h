// linkedlist.h
#include <stdlib.h>
#include <stdio.h>


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define RED "\033[0;31m"
#define DEFAULT "\033[0m"

struct node{
	int val; // move value
	int x,y; // move coordinats
	struct node *next, *prev;
};

struct linkedlist{
    struct node *head;
    struct node *tail;
};

void init_node(struct node **head, int val, int x, int y, struct node *next, struct node *prev);

void linkedlist_init(struct linkedlist **lst, int val, int x, int y);
void linkedlist_insert(struct linkedlist *lst, int val, int x, int y);
void linkedlist_remove(struct linkedlist *lst);
void linkedlist_free(struct linkedlist **lst);
void linkedlist_print(struct linkedlist *lst);

#endif /*LINKEDLIST_H_*/

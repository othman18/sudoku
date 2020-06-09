//linkedlist.h
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
};

void init_node(struct node **head, int val, int x, int y, struct node *next, struct node *prev);
void init_linkedlist(struct linkedlist **lst, int val, int x, int y);
void insert_node(struct linkedlist *lst, int val, int x, int y);
void remove_node(struct linkedlist *lst);
void delete_linkedlist(struct linkedlist **lst);
#endif /*LINKEDLIST_H_*/


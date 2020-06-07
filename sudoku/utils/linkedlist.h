#include <stdlib.h>
#include <stdio.h>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct node{
	int val;
	struct node *next, *prev;
};

	
void init_node(struct node **head, int val, struct node *next, struct node *prev);
void insert_node(struct node **head, int val);
void remove_node(struct node **head);

#endif /*LINKEDLIST_H_*/

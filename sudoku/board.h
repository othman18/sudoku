//board.h
#include <stdlib.h>
#include <stdbool.h>
#include "utils/linkedlist.h"


#ifndef BOARD_H_
#define BOARD_H_

struct cell{
	int mode; // 0 = read/write, 1 = read, 2 = fixed 
	int val;
};


cell* init_cell();

/* modify board methods */
void init_board(int board_size);
void delete_board();
void print_board();

/* move methods */
bool valid_move(int x, int y);
void set_move(int val, int x, int y);
void edit_move(int val, int x, int y);
void remove_move(int x, int y);

/* modify history methods*/
void insert_history(int val, int x, int y);
void remove_history();
void undo_move();
void redo_move();

#endif


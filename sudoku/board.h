// board.h
#include <stdlib.h>
#include "utils/linkedlist.h"


#ifndef BOARD_H_
#define BOARD_H_

struct cell{
	int mode; // 0 = read/write, 1 = read, 2 = fixed 
	int val;
};


struct cell* init_cell();

/* modify board methods */
void board_init(int board_size);
void board_free();
void board_print();

/* move methods */
bool move_is_valid(int x, int y);
void move_set(int val, int x, int y);
void move_edit(int val, int x, int y);
void move_remove(int x, int y);
void move_undo();
void move_redo();

/* modify history methods*/
void history_insert(int val, int x, int y);
void history_print();
//void history_remove();

#endif

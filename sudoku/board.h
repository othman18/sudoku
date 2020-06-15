// board.h
#include "linkedlist.h"


#ifndef BOARD_H_
#define BOARD_H_

#define EMPTY_CELL 0
#define MODE_RW 0
#define MODE_R 1
#define MODE_F 2
struct cell{
	int mode; // 0 = read/write, 1 = read, 2 = fixed 
	int val;
};

struct cell* init_cell();

/* modify board methods */
void board_init(int board_size);
void board_free();
void board_print();
void board_reset();

/* move methods */
bool move_is_valid(int val, int x, int y);
void move_set(int val, int x, int y);
void move_edit(int val, int x, int y);
void move_remove(int x, int y);
void move_undo();
void move_redo();

/* modify history methods*/
//  found in linkedlist.h
// MOVE_INS 0
// MOVE_REM 1
// MOVE_MOD 2
void history_insert(int val, int x, int y, int val_prev, 
	int move_type); // 0 = insert, 1 = remove, 2 = modify
void history_print();

#endif

/* board.h */
#include "linkedlist.h"

#ifndef BOARD_H_
#define BOARD_H_

#define EMPTY_CELL 0
#define MODE_RW 0
#define MODE_R 1
#define MODE_F 2

#define BOARD_MAX_PRINT_SIZE 30
#define VALID_MOVE_VAL 1

struct cell {
	int mode; /* 0 = read/write, 1 = read, 2 = fixed */
	int val;
};

struct cell* cell_init();

/*
 * modify board methods
 */
void board_init(int size_m, int size_n);
void board_free();
void board_print();
void board_print_dashes();
void board_reset();
bool board_is_init();

/*
 * move methods
 */
bool move_is_valid(int value, int x, int y);
bool move_is_valid_coordinate(int x, int y);
bool move_is_valid_range(int val);
bool move_is_valid_horizontal(int val, int y);
bool move_is_valid_vertical(int val, int x);
bool move_is_valid_block(int val, int x, int y);

void move_set(int val, int x, int y);
void move_edit(int val, int x, int y);
void move_remove(int x, int y);
void move_undo();
void move_redo();

/*
 * modify history methods
 * found in linkedlist.h
 * MOVE_INS 0
 * MOVE_REM 1
 * MOVE_MOD 2
 */
void history_insert(int val, int x, int y, int val_prev,
                    int move_type); /* 0 = insert, 1 = remove, 2 = modify */
void history_print();

#endif

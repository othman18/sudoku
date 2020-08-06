/* board.h */
#include "linkedlist.h"

#ifndef BOARD_H_
#define BOARD_H_

#define EMPTY_CELL 0
#define MODE_RW 0
#define MODE_R 1
#define MODE_F 2
#define EMPTY_ARG -1
#define MIN_BOARD_SIZE 9
#define MAX_BOARD_SIZE 15

/**
 * cell definition and functions
 */
struct cell {
	int mode; /* 0 = read/write, 1 = read, 2 = fixed */
	int val;
};

/**
 * The function will initialize a cell with read/write mode and a default value
 * = 0
 */
struct cell* cell_init();

/**
 * board functions
 */

/**
 * On success, a mXn board will be allocated and initialized, then saved in the
 * global variable glob_board. If however the value m*n is greater than
 * MAX_BOARD_SIZE or smaller than MIN_BOARD_SIZE, then an error message will be
 * displayed and the function will exit.
 * @param size_m - given m dimension
 * @param size_n - given n dimension
 */
void board_init(int size_m, int size_n);

/**
 * On success, the global variable glob_board will be freed. If however the
 * variable was already freed (== NULL) then the function will exit without
 * changing anything. than MIN_BOARD_SIZE, then an error message will be
 * displayed and the function will exit.
 */
void board_free();

/**
 * On success, the function wil print the board. If the board was not
 * initialized, then an error message will be displayed and the function will
 * exit without printing the board.
 */
void board_print();

/**
 * Function will print a fixed number of dashes '-' depending on the size of the
 * board.
 */
void board_print_dashes();

/**
 * On success, the board will free the board and reinitialize it as a new board
 * with the same dimensions as before. If however the board was not initialized,
 * then an error message will be displayed and the function will exit without
 * altering the board.
 */
void board_reset();

/**
 * Check if the board was already reinitialized or not.
 * @return
 */
bool board_is_init();
/**
 * On success, the function will solve the board using a backtracking algorithm.
 * @param x - X coordinate
 * @param y - Y coordinate
 */
bool board_bt_solve(int x, int y); /* backtracking solve*/

/**
 * move functions
 */

/**
 * Check if the following functions return true
 * @function move_is_valid_coordinate
 * @function move_is_valid_range
 * @function move_is_valid_horizontal
 * @function move_is_valid_vertical
 * @function move_is_valid_block
 * @param val - value to be set at (x,y)
 * @param x - X coordinate
 * @param y - Y coordinate
 * @return
 */
bool move_is_valid(int val, int x, int y);

/**
 * Check if the coordinates are in bounds, i.e. >= 0 && < board size
 * @param x - X coordinate
 * @param y - Y coordinate
 * @return
 */
bool move_is_valid_coordinate(int x, int y);

/**
 * Check if the value is in bounds, i.e. > 0 && <= board size
 * @param val - value to be set
 * @return
 */
bool move_is_valid_range(int val);

/**
 * Check if value is present in any cell in the horizontal line of y
 * @param val - value to be set
 * @param y - Y coordinate
 * @return
 */
bool move_is_valid_horizontal(int val, int y);

/**
 * Check if value is present in any cell in the vertical line of x
 * @param val - value to be set
 * @param x - X coordinate
 * @return
 */
bool move_is_valid_vertical(int val, int x);

/**
 * Check if vlue is present in the current cell blocks of x and y
 * @param val - value to be set
 * @param x - X coordiante
 * @param y - Y coordinate
 * @return
 */
bool move_is_valid_block(int val, int x, int y);

/**
 * On success, val will be set at the coordinates (x, y). Cell will become in R
 * mode Insert set value to the history. If however the cell at (x, y) wasn't
 * empty, an error will be displayed and the function will exit.
 * @param val - value to be set
 * @param x - X coordiante
 * @param y - Y coordinate
 * @return
 */
void move_set(int val, int x, int y);

/**
 * On success, val will be set as the new val at the coordinates (x, y). Cell
 * will still be in R mode. Insert edited value to the history. If however the
 * cell at (x, y) was empty, an error will be displayed and the function will
 * exit.
 * @param val - value to be set
 * @param x - X coordiante
 * @param y - Y coordinate
 * @return
 */
void move_edit(int val, int x, int y);

/**
 * On success, the value at (x, y) will be removed and set as empty, the cell
 * will be in RW mode. Insert removed value to the history. If however the cell
 * at (x, y) was empty or it was in F mode, an error will be displayed and the
 * function will exit.
 * @param val - value to be set
 * @param x - X coordiante
 * @param y - Y coordinate
 * @return
 */
void move_remove(int x, int y);

/**
 * On success, reverse the last move.
 * An Insert move will be deleted
 * A remove move will be reinserted
 * An edit move will be unedited and set back to its previous value
 */
void move_undo();

/**
 * On success, restore previous move and set it. We don't need to check the
 * move, since this is a previously inserted move, which was already validated
 * An Insert move will be deleted
 * A remove move will be reinserted
 * An edit move will be unedited and set back to its previous value
 */
void move_redo();

/**
 * Insert moves to the linkedlist history. First node in the history is a dummy
 * node which will never be accesed.
 * @param val
 * @param x
 * @param y
 * @param val_prev
 * @param move_type
 */
void history_insert(int val, int x, int y, int val_prev,
                    int move_type); /* 0 = insert, 1 = remove, 2 = edit */

/**
 * Print move history.
 */
void history_print();

/**
 * flip global variable board_flip_error_msg_flag to true or false to allow or forbid printing messages.
 */
void board_flip_error_msg_flag();

typedef enum BOARD_ERROR {
	ERROR_BOARD_INVALID_DIM,
	ERROR_BOARD_NOT_INIT,
	ERROR_MOVE_INVALID_X_BOUNDS,
	ERROR_MOVE_INVALID_Y_BOUNDS,
	ERROR_MOVE_INVALID_VAL_RANGE,
	ERROR_MOVE_INVALID_VAL_HORIZONTAL,
	ERROR_MOVE_INVALID_VAL_VERTICAL,
	ERROR_MOVE_INVALID_VAL_BLOCK,
	ERROR_MOVE_INVALID_ALREADY_SET,
	ERROR_MOVE_INVALID_FIXED,
	ERROR_MOVE_INVALID_MODE,
	ERROR_MOVE_INVALID_EMPTY,
	ERROR_MOVE_INVALID_UNDO,
	ERROR_MOVE_INVALID_REDO,
} BOARD_ERROR;

void board_error_handler(BOARD_ERROR err, int arg0, int arg1, int arg2);

#endif

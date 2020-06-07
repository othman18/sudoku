#include <stdlib.h>
#include <stdbool.h>



#ifndef BOARD_H_
#define BOARD_H_
#define PRINT_RED printf("\033[0;31m");
#define PRINT_NORMAL printf("\033[0m");

struct cell{
	int mode; // 0 = read/write, 1 = read, 2 = fixed 
	int val;
}; 

extern int homo;

cell* init_cell();
void init_board(int board_size);
void delete_board();
void print_board();
bool valid_move(int x, int y);
void set_move(int val, int x, int y);
void edit_move(int val, int x, int y);
#endif


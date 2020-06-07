#include <stdbool.h>
#include <stdlib.h>


#ifndef BOARD_H_
#define BOARD_H_
#define PRINT_RED printf("\033[0;31m");
#define PRINT_NORMAL printf("\033[0m");

struct cell{
	bool fixed;
	int val;
}; 


cell* init_cell();
void init_board(int board_size);
void delete_board();
void print_board();
void set_move(int val, int x, int y);
#endif


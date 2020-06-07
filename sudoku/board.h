#include <stdbool.h>
#include <stdlib.h>


#ifndef BOARD_H_
#define BOARD_H_

struct cell{
	bool fixed;
	int val;
}; 


cell* init_cell();
void init_board(int board_size);
void delete_board();

#endif

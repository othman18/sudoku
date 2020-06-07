#include "board.h"
#include <stdio.h>


/* global variables */
cell ***glob_board = NULL;
int glob_board_size = 0;


cell* init_cell(){
	struct cell *new_cell = (struct cell*) malloc(sizeof(struct cell));
	new_cell->val = 0;
	new_cell->mode = 0;
	return new_cell;
}


void init_board(int board_size){
	if(board_size < 2){
		PRINT_RED;
		printf("board size can't be lower than 2\n");
		PRINT_NORMAL;
		return;
	}
	glob_board_size = board_size;
	glob_board = (struct cell***) malloc(board_size * board_size * sizeof(struct cell));	
	
	for(int i = 0; i < board_size; i++){
		glob_board[i] = (struct cell**) malloc(board_size * sizeof(struct cell));	
	}
	for(int i = 0; i < board_size; i++){
		for(int j = 0; j < board_size; j++){
			glob_board[i][j] = init_cell();
		}
	}
}


void delete_board(){
	if(glob_board == NULL){
		return;
	}
	
	for(int i = 0; i < glob_board_size; i++){
		for(int j = 0; j < glob_board_size; j++){
			free(glob_board[i][j]);
		}
		free(glob_board[i]);
	}
	
	free(glob_board);
}


void print_board(){
	if(glob_board == NULL){
		PRINT_RED;
		printf("board not init\n");
		PRINT_NORMAL;
		return;		
	}

	for(int i = 0; i < glob_board_size * 3 + 1; i++){
		printf("-");
	}
	
	for(int i = 0; i < glob_board_size; i++){
		printf("\n|");
		for(int j = 0; j < glob_board_size; j++){
			if(glob_board[i][j]->val == 0){
				printf("  |");
			}
			else{
				printf("%d |",glob_board[i][j]->val);			
			}
		}
	}
	
	printf("\n");
	for(int i = 0; i < glob_board_size * 3 + 1; i++){
		printf("-");
	}	
	printf("\n");
}


/* check if move is in bounds */
bool valid_move(int val, int x, int y){
	bool valid_b = true;
	PRINT_RED;
	if(glob_board == NULL){
		printf("board not init\n");
		valid_b = false;
	}
	else if(x < 0 ||x >= glob_board_size){
		printf("invalid move, x: %d out of board bounds (min: 0, max: %d)\n", x, glob_board_size);
		valid_b = false;
	}
	else if(y < 0 || y >= glob_board_size){
		printf("invalid move, y: %d out of board bounds (min: 0, max: %d)\n", y, glob_board_size);
		valid_b = false;
	}
	else if(val < 1 || val > glob_board_size){
		PRINT_RED;
		valid_b = false;
	}
	PRINT_NORMAL;
	return valid_b;
}


/* set move on board only if the cell is modifiable*/
void set_move(int val, int x, int y){
	if(!valid_move(val, x, y)){
		return;
	}
	
	switch(glob_board[x][y]->mode){
		case 0:
			glob_board[x][y]->val = val;
			glob_board[x][y]->mode = 1;
			break;
		case 1:
			PRINT_RED;
			printf("invalid move, cell[%d][%d] was already set, use edit to modify cell\n", x, y);
			PRINT_NORMAL;
			break;
		case 2:
			PRINT_RED;
			printf("invalid move, cell[%d][%d] has a fixed value\n", x, y);
			PRINT_NORMAL;
			break;
		default:
			PRINT_RED;
			printf("invalid cell mode\n");
			PRINT_NORMAL;
	}
}


/* set move on board if the cell was already set*/
void edit_move(int val, int x, int y){
	if(!valid_move(val, x, y)){
		return;
	}
	glob_board[x][y]->mode = 0;
	set_move(val, x, y);
}


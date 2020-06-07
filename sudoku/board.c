#include "board.h"
#include <stdio.h>

cell ***board = NULL;


cell* init_cell(){
	struct cell *new_cell = (struct cell*) malloc(sizeof(struct cell));
	new_cell->val = -1;
	new_cell->fixed = false;
	return new_cell;
}


void init_board(int board_size){
	
	board = (struct cell***) malloc(board_size * sizeof(struct cell));	
	
	printf("size board = %ld, size cell = %ld, num = %ld\n",sizeof((struct cell***)board), sizeof(struct cell), board_size * sizeof(struct cell));
	
	for(int i = 0; i < board_size; i++){
		board[i] = (struct cell**) malloc(board_size * sizeof(struct cell));	
	}
	
	for(int i = 0; i < board_size; i++){
		for(int j = 0; j < board_size; j++){
			board[i][j] = init_cell();
		}
	}
}


void delete_board(){
	if(board == NULL){
		return;
	}
	
	int board_size = sizeof(board) / sizeof(struct cell);
	printf("size = %d\n",board_size);
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			free(board[i][j]);
		}
		free(board[i]);
	}
	free(board);
}



// board.c
#include "board.h"
#include <stdio.h>


/* global variables */
cell ***glob_board = NULL;
int glob_board_size = 0;
linkedlist *glob_move_history = NULL;


/* init a cell with read/write mode and a default value = 0 */
cell* init_cell(){
	struct cell *new_cell = (struct cell*) malloc(sizeof(struct cell));
	new_cell->val = 0;
	new_cell->mode = 0;
	return new_cell;
}


///////////////////////////////////////BOARD METHODS////////////////////////////


void board_init(int board_size){
	if(board_size < 2){
		printf(RED "board size can't be lower than 2\n" DEFAULT);
		return;
	}
    if(glob_board != NULL){
        board_free();
    }
    
	glob_board_size = board_size;
	glob_board = (struct cell***) malloc(board_size * sizeof(struct cell));	
	
	for(int i = 0; i < board_size; i++){
		glob_board[i] = (struct cell**) malloc(board_size * sizeof(struct cell));	
	}
	for(int i = 0; i < board_size; i++){
		for(int j = 0; j < board_size; j++){
			glob_board[i][j] = init_cell();
		}
	}
}


void board_free(){
	if(glob_board == NULL){
		return;
	}
	
	for(int i = 0; i < glob_board_size; i++){
		for(int j = 0; j < glob_board_size; j++){
			free(glob_board[i][j]);
		}
		free(glob_board[i]);
	}
	linkedlist_free(&glob_move_history);
	free(glob_board);
    glob_board = NULL;
}


void board_print(){
    // TODO: fix this statement
	if(glob_board == NULL){
		printf(RED "board not init\n" DEFAULT);
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


///////////////////////////////////////MOVE METHODS/////////////////////////////


/* check if move is in bounds */
bool move_valid(int val, int x, int y){
	bool valid_b = true;
	printf(RED);
	
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
		valid_b = false;
	}
	printf(DEFAULT);
	return valid_b;
}


/* set move on board only if the cell is modifiable*/
void move_set(int val, int x, int y){
	if(!move_valid(val, x, y)){
		return;
	}
	
	switch(glob_board[x][y]->mode){
		case 0:
			glob_board[x][y]->val = val;
			glob_board[x][y]->mode = 1;
			history_insert(val, x, y);
			break;
		case 1:
			printf(RED "invalid move, cell[%d][%d] was already set, use edit to modify cell\n" DEFAULT, x, y);
			break;
		case 2:
			printf(RED "invalid move, cell[%d][%d] has a fixed value\n" DEFAULT, x, y);
			break;
		default:
			printf(RED "invalid cell mode\n" DEFAULT);
	}
}


/* set move on board if the cell was already set*/
void move_edit(int val, int x, int y){
	if(!move_valid(val, x, y)){
		return;
	}
	if(val == glob_board[x][y]->val){
		// same value, won't have to call move_set
		return;
	}
	glob_board[x][y]->mode = 0;
	move_set(val, x, y);
}


/* remove board[x][y], give it: read/write mode and a default value = 0 */
void move_remove(int x, int y){
	if(!move_valid(1, x, y)){
		return;
	}
	glob_board[x][y]->mode = 0;
	glob_board[x][y]->val = 0;
}


void move_undo(){
    
}


void move_redo(){

}


///////////////////////////////////////HISTORY METHODS//////////////////////////


void history_insert(int val, int x, int y){
	if(glob_move_history == NULL){
		linkedlist_init(&glob_move_history, val, x, y);
		return;
	}
	linkedlist_insert(glob_move_history, val, x, y);
}

void history_remove(){
	// create a current node inside the history structure and move the pointer as needed
    // when removing the history, simply pass the current node and delete all of its nexts
}


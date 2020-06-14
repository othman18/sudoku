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
		printf(RED "Board size can't be lower than 2\n" DEFAULT);
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
	if(glob_board == NULL){
		printf(RED "Board not init\n" DEFAULT);
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


void board_reset(){
	if(glob_board == NULL){
		printf(RED "Board not init\n" DEFAULT);
		return;
	}
	board_free();
	board_init(glob_board_size);
}


///////////////////////////////////////MOVE METHODS/////////////////////////////


/* check if move is in bounds */
bool move_is_valid(int val, int x, int y){
	bool valid_b = true;
	printf(RED);
	
	if(glob_board == NULL){
		printf(RED "Board not init\n" DEFAULT);
		valid_b = false;
	}
	else if(x < 0 ||x >= glob_board_size){
		printf(RED "Invalid move, x: %d out of board bounds (min: 0, max: %d)\n" DEFAULT, x, glob_board_size - 1);
		valid_b = false;
	}
	else if(y < 0 || y >= glob_board_size){
		printf(RED "Invalid move, y: %d out of board bounds (min: 0, max: %d)\n" DEFAULT, y, glob_board_size - 1);
		valid_b = false;
	}
	else if(val < 1 || val > glob_board_size){
		printf(RED "Invalid move, val: %d out of board bounds (min: 1, max: %d)\n" DEFAULT, val, glob_board_size);
		valid_b = false;
	}
	printf(DEFAULT);
	return valid_b;
}


/* set move on board only if the cell is modifiable*/
void move_set(int val, int x, int y){
	if(!move_is_valid(val, x, y)){
		return;
	}
	
	switch(glob_board[x][y]->mode){
		case 0:
			glob_board[x][y]->val = val;
			glob_board[x][y]->mode = 1;
			history_insert(val, x, y);
			break;
		case 1:
			printf(RED "Invalid move, cell[%d][%d] was already set, use edit to modify cell\n" DEFAULT, x, y);
			break;
		case 2:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT, x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}


/* set move on board if the cell was already set*/
void move_edit(int val, int x, int y){
	if(!move_is_valid(val, x, y)){
		return;
	}
	switch(glob_board[x][y]->mode){
		case 0:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x, y);
			break;
		case 1:
			glob_board[x][y]->mode = 0;
			move_set(val, x, y);
			break;
		case 2:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT, x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}


/* remove board[x][y], give it: read/write mode and a default value = 0 */
void move_remove(int x, int y){
	if(!move_is_valid(1, x, y)){
		return;
	}
	switch(glob_board[x][y]->mode){
		case 0:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x, y);
			break;
		case 1:
			glob_board[x][y]->mode = 0;
			glob_board[x][y]->val = 0;
			break;
		case 2:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT, x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}


void move_undo(){
	if(glob_board == NULL){
		printf(RED "Board not init\n" DEFAULT);
		return;
	}

    if(!linkedlist_rewind_current(glob_move_history)){
		printf(RED "No more moves to undo\n" DEFAULT);
		return;
	}
	struct node *prev_move = glob_move_history->current_move->next;
	move_remove(prev_move->x, prev_move->y);
}


/* restore prev move and set it. We don't need to check the move, since this is 
   a previously inserted move, which was already validated*/
void move_redo(){
	if(glob_board == NULL){
		printf(RED "Board not init\n" DEFAULT);
		return;
	}

	if(!linkedlist_forward_current(glob_move_history)){
		printf(RED "No more moves to redo\n" DEFAULT);
		return;
	}
	struct node *prev_move = glob_move_history->current_move;
	glob_board[prev_move->x][prev_move->y]->val = prev_move->val;
	glob_board[prev_move->x][prev_move->y]->mode = 1;
}


///////////////////////////////////////HISTORY METHODS//////////////////////////


void history_insert(int val, int x, int y){
	if(glob_move_history == NULL){
		linkedlist_init(&glob_move_history, val, x, y);
		return;
	}
	linkedlist_insert(glob_move_history, val, x, y);
}


void history_print(){
	printf("Move history: ");
	linkedlist_print_until_current(glob_move_history);
}



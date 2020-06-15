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
	new_cell->val = EMPTY_CELL;
	new_cell->mode = MODE_RW;
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
			if(glob_board[i][j]->val == EMPTY_CELL){
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
		case MODE_RW:
			glob_board[x][y]->val = val;
			glob_board[x][y]->mode = MODE_R;
			history_insert(val, x, y, MOVE_DUM, MOVE_INS);
			break;
		case MODE_R:
			printf(RED "Invalid move, cell[%d][%d] was already set, use edit to modify cell\n" DEFAULT, x, y);
			break;
		case MODE_F:
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
		case MODE_RW:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x, y);
			break;
		case MODE_R:
			history_insert(val, glob_board[x][y]->val, x, y, MOVE_MOD);
			glob_board[x][y]->val = val;
			break;
		case MODE_F:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT, x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}


/* remove board[x][y], give it: read/write mode and make it an empty cell
   insert old value into the history */
void move_remove(int x, int y){
	if(!move_is_valid(1, x, y)){
		return;
	}
	switch(glob_board[x][y]->mode){
		case MODE_RW:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x, y);
			break;
		case MODE_R:
			glob_board[x][y]->mode = MODE_RW;
			history_insert(EMPTY_CELL, glob_board[x][y]->val, x, y, MOVE_REM);
			glob_board[x][y]->val = EMPTY_CELL;
			break;
		case MODE_F:
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
	
	
	switch(prev_move->move_type){
		case(MOVE_INS):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = EMPTY_CELL;
			break;
		case(MOVE_REM):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val_prev;
			break;
		case(MOVE_MOD):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val_prev;
			break;
		default:
			printf("TYPE ERROR IN UNDO \n");
	}
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
	switch(prev_move->move_type){
		case(MOVE_INS):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val;
			break;
		case(MOVE_REM):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val_prev;
			break;
		case(MOVE_MOD):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val;
			break;
		default:
			printf("TYPE ERROR IN UNDO \n");
	}
}


///////////////////////////////////////HISTORY METHODS//////////////////////////


/* add move to history, first node in the history is a dummy node which will
   never be accesed.
   */
void history_insert(int val, int x, int y, int val_prev, int move_type){
	if(glob_move_history == NULL){
		linkedlist_init(&glob_move_history, MOVE_DUM, MOVE_DUM, MOVE_DUM, MOVE_DUM, MOVE_DUM);  // dummy node
	}
	linkedlist_insert(glob_move_history, val, x, y, val_prev, move_type);
}


void history_print(){
	printf("     Move history: ");
	linkedlist_print_until_current(glob_move_history);
	printf("\nFull Move history: ");
	linkedlist_print(glob_move_history);
}



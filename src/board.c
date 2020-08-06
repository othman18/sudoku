/* board.c */
#include "board.h"

#include <stdio.h>

/**
 * global variables
 */
struct cell ***glob_board = NULL;
int glob_board_size = 0;   /* X * Y */
int glob_board_size_n = 0; /* X dim*/
int glob_board_size_m = 0; /* Y dim*/
struct linkedlist *glob_move_history = NULL;
bool glob_erro_msg_flag = true; /* allow printing messages */

struct cell *cell_init() {
	struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));
	new_cell->val = EMPTY_CELL;
	new_cell->mode = MODE_RW;
	return new_cell;
}

/*//////////////////////////////////////BOARD
 * FUNCTIONS///////////////////////////*/

void board_init(int size_m, int size_n) {
	if (size_m * size_n < MIN_BOARD_SIZE) {
		board_error_handler(ERROR_BOARD_INVALID_DIM, EMPTY_ARG, EMPTY_ARG,
		                    EMPTY_ARG);
		return;
	}
	if (glob_board != NULL) {
		board_free();
	}
	glob_board_size_n = size_n;
	glob_board_size_m = size_m;
	glob_board_size = glob_board_size_m * glob_board_size_n;
	glob_board = (struct cell ***)malloc(glob_board_size * sizeof(struct cell));

	for (int i = 0; i < glob_board_size; i++) {
		glob_board[i] =
		    (struct cell **)malloc(glob_board_size * sizeof(struct cell));
	}
	for (int i = 0; i < glob_board_size; i++) {
		for (int j = 0; j < glob_board_size; j++) {
			glob_board[i][j] = cell_init();
		}
	}
}

void board_free() {
	if (glob_board == NULL) {
		return;
	}
	for (int i = 0; i < glob_board_size; i++) {
		for (int j = 0; j < glob_board_size; j++) {
			free(glob_board[i][j]);
		}
		free(glob_board[i]);
	}
	linkedlist_free(&glob_move_history);
	free(glob_board);
	glob_board = NULL;
}

void board_print() {
	if (!board_is_init()) {
		return;
	}

	/* print X values on top of board */
	for (int i = 0; i < glob_board_size; i++) {
		if (i % glob_board_size_m == 0) {
			/*empty space since the board starts with a '|' */
			printf(" ");
		}
		printf(" %2d ", i);
	}

	printf("\n");

	for (int i = 0; i < glob_board_size; i++) {
		if (i % glob_board_size_n == 0) {
			board_print_dashes();
		}
		for (int j = 0; j < glob_board_size; j++) {
			if (j % glob_board_size_m == 0) {
				printf("|");
			}
			/* i and j must be reversed to not flip the x and y axis */
			if (glob_board[j][i]->val == EMPTY_CELL) {
				printf("    ");
			} else if (glob_board[j][i]->mode == MODE_F) {
				printf("%2d.", glob_board[j][i]->val);
			} else {
				printf(" %2d ", glob_board[j][i]->val);
			}
		}
		/* print last border as well as the line number */
		printf("|%d\n", i);
	}
	board_print_dashes();

	printf("\n");
	// history_print();
}

void board_print_dashes() {
	for (int i = 0; i < glob_board_size * 4 + glob_board_size_n + 1; i++) {
		printf("-");
	}
	printf("\n");
}

void board_reset() {
	if (!board_is_init()) {
		return;
	}
	board_free();
	board_init(glob_board_size_m, glob_board_size_n);
}

bool board_is_init() {
	if (glob_board == NULL) {
		board_error_handler(ERROR_BOARD_NOT_INIT, EMPTY_ARG, EMPTY_ARG,
		                    EMPTY_ARG);
		return false;
	}
	return true;
}

int bt_solve_counter = 0;
bool board_bt_solve(int x, int y) {
	for (int i = 1; i <= glob_board_size; i++) {
		bt_solve_counter++;
		if (!move_is_valid(i, x, y)) {
			continue;
		}

		move_set(i, x, y);

		int new_x = 0, new_y = y;
		if (x == glob_board_size - 1) {
			new_x = 0;
			new_y = y + 1;
		} else {
			new_x = x + 1;
		}

		if (new_y == glob_board_size) {
			printf("finished with counter = %d\n", bt_solve_counter);
			bt_solve_counter = 0;
			return true;
		}

		if (board_bt_solve(new_x, new_y)) {
			return true;
		} else {
			move_remove(x, y);
		}
	}
	return false;
}

/*//////////////////////////////////////MOVE
 * FUNCTIONS////////////////////////////*/

bool move_is_valid(int val, int x, int y) {
	return move_is_valid_coordinate(x, y) && move_is_valid_range(val) &&
	       move_is_valid_horizontal(val, y) && move_is_valid_vertical(val, x) &&
	       move_is_valid_block(val, x, y);
}

bool move_is_valid_coordinate(int x, int y) {
	if (!board_is_init()) {
		return false;
	} else if (x < 0 || x >= glob_board_size) {
		board_error_handler(ERROR_MOVE_INVALID_X_BOUNDS, x, glob_board_size - 1,
		                    EMPTY_ARG);
		return false;
	} else if (y < 0 || y >= glob_board_size) {
		board_error_handler(ERROR_MOVE_INVALID_Y_BOUNDS, y, glob_board_size - 1,
		                    EMPTY_ARG);
		return false;
	}
	return true;
}

bool move_is_valid_range(int val) {
	if (val < 1 || val > glob_board_size) {
		board_error_handler(ERROR_MOVE_INVALID_VAL_RANGE, val, glob_board_size,
		                    EMPTY_ARG);
		return false;
	}
	return true;
}

bool move_is_valid_horizontal(int val, int y) {
	if (!board_is_init()) {
		return false;
	}
	/* iterate through board[...][y] */
	for (int i = 0; i < glob_board_size; i++) {
		if (glob_board[i][y]->val == val) {
			board_error_handler(ERROR_MOVE_INVALID_VAL_HORIZONTAL, val, y,
			                    EMPTY_ARG);
			return false;
		}
	}
	return true;
}

bool move_is_valid_vertical(int val, int x) {
	if (!board_is_init()) {
		return false;
	}
	/* iterate through board[x][...] */
	for (int i = 0; i < glob_board_size; i++) {
		if (glob_board[x][i]->val == val) {
			board_error_handler(ERROR_MOVE_INVALID_VAL_VERTICAL, val, x,
			                    EMPTY_ARG);
			return false;
		}
	}
	return true;
}

bool move_is_valid_block(int val, int x, int y) {
	if (!board_is_init()) {
		return false;
	}

	int x_block = x / glob_board_size_n;
	int y_block = y / glob_board_size_m;
	int x_new = x_block * glob_board_size_n;
	int y_new = y_block * glob_board_size_m;

	for (int i = 0; i < glob_board_size_n; i++) {
		for (int j = 0; j < glob_board_size_m; j++) {
			if (glob_board[x_new + i][y_new + j]->val == val) {
				board_error_handler(ERROR_MOVE_INVALID_VAL_BLOCK, val, x_block,
				                    y_block);
				return false;
			}
		}
	}
	return true;
}

void move_set(int val, int x, int y) {
	if (!move_is_valid(val, x, y)) {
		return;
	}

	switch (glob_board[x][y]->mode) {
		case MODE_RW:
			glob_board[x][y]->val = val;
			glob_board[x][y]->mode = MODE_R;
			history_insert(val, x, y, MOVE_DUM, MOVE_INS);
			break;
		case MODE_R:
			board_error_handler(ERROR_MOVE_INVALID_ALREADY_SET, x, y,
			                    EMPTY_ARG);
			break;
		case MODE_F:
			board_error_handler(ERROR_MOVE_INVALID_FIXED, x, y, EMPTY_ARG);
			break;
		default:
			board_error_handler(ERROR_MOVE_INVALID_MODE, EMPTY_ARG, EMPTY_ARG,
			                    EMPTY_ARG);
	}
}

void move_edit(int val, int x, int y) {
	if (!move_is_valid(val, x, y)) {
		return;
	}

	switch (glob_board[x][y]->mode) {
		case MODE_RW:
			board_error_handler(ERROR_MOVE_INVALID_EMPTY, x, y, EMPTY_ARG);
			break;
		case MODE_R:
			history_insert(val, glob_board[x][y]->val, x, y, MOVE_EDI);
			glob_board[x][y]->val = val;
			break;
		case MODE_F:
			board_error_handler(ERROR_MOVE_INVALID_FIXED, x, y, EMPTY_ARG);
			break;
		default:
			board_error_handler(ERROR_MOVE_INVALID_MODE, EMPTY_ARG, EMPTY_ARG,
			                    EMPTY_ARG);
	}
}

void move_remove(int x, int y) {
	if (!move_is_valid_coordinate(x, y)) {
		return;
	}
	switch (glob_board[x][y]->mode) {
		case MODE_RW:
			board_error_handler(ERROR_MOVE_INVALID_EMPTY, x, y, EMPTY_ARG);
			break;
		case MODE_R:
			glob_board[x][y]->mode = MODE_RW;
			history_insert(EMPTY_CELL, x, y, glob_board[x][y]->val, MOVE_REM);
			glob_board[x][y]->val = EMPTY_CELL;
			break;
		case MODE_F:
			board_error_handler(ERROR_MOVE_INVALID_FIXED, x, y, EMPTY_ARG);
			break;
		default:
			board_error_handler(ERROR_MOVE_INVALID_MODE, EMPTY_ARG, EMPTY_ARG,
			                    EMPTY_ARG);
	}
}

void move_undo() {
	if (!board_is_init()) {
		return;
	}

	if (!linkedlist_rewind_current(glob_move_history)) {
		board_error_handler(ERROR_MOVE_INVALID_UNDO, EMPTY_ARG, EMPTY_ARG,
		                    EMPTY_ARG);
		return;
	}
	struct node *prev_move = glob_move_history->current_move->next;

	switch (prev_move->move_type) {
		case (MOVE_INS):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = EMPTY_CELL;
			break;
		case (MOVE_REM):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val_prev;
			break;
		case (MOVE_EDI):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val_prev;
			break;
		default:
			printf("TYPE ERROR IN UNDO\n");
	}
}

void move_redo() {
	if (!board_is_init()) {
		return;
	}

	if (!linkedlist_forward_current(glob_move_history)) {
		board_error_handler(ERROR_MOVE_INVALID_REDO, EMPTY_ARG, EMPTY_ARG,
		                    EMPTY_ARG);
		return;
	}
	struct node *prev_move = glob_move_history->current_move;
	switch (prev_move->move_type) {
		case (MOVE_INS):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_R;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val;
			break;
		case (MOVE_REM):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = EMPTY_CELL;
			break;
		case (MOVE_EDI):
			glob_board[prev_move->x][prev_move->y]->mode = MODE_RW;
			glob_board[prev_move->x][prev_move->y]->val = prev_move->val;
			break;
		default:
			printf("TYPE ERROR IN UNDO\n");
	}
}

/*//////////////////////////////////////HISTORY
 * FUNCTIONS/////////////////////////*/

void history_insert(int val, int x, int y, int val_prev, int move_type) {
	if (glob_move_history == NULL) {
		/* dummy node */
		linkedlist_init(&glob_move_history, MOVE_DUM, MOVE_DUM, MOVE_DUM,
		                MOVE_DUM, MOVE_DUM);
	}
	linkedlist_insert(glob_move_history, val, x, y, val_prev, move_type);
}

void history_print() {
	if (glob_move_history == NULL) {
		return;
	}
	printf("     Move history: ");
	linkedlist_print(glob_move_history, glob_move_history->current_move);
	printf("Full Move history: ");
	linkedlist_print(glob_move_history, glob_move_history->tail);
	printf("\n");
}

void board_flip_error_msg_flag(){
    glob_erro_msg_flag = !glob_erro_msg_flag;
}

void board_error_handler(BOARD_ERROR err, int arg0, int arg1, int arg2) {
    if(!glob_erro_msg_flag){
        return;
    }
    printf(RED);
	switch (err) {
		case (ERROR_BOARD_INVALID_DIM):
			printf("Error, board size can't be lower than %d!\n",
			       MIN_BOARD_SIZE);
			break;
		case (ERROR_BOARD_NOT_INIT):
			printf("Error, board not init!\n");
			break;
		case (ERROR_MOVE_INVALID_X_BOUNDS):
			printf(
			    "Invalid move, x: %d out of board bounds (min: 0, max: %d)!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_Y_BOUNDS):
			printf(
			    "Invalid move, y: %d out of board bounds (min: 0, max: "
			    "%d)!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_VAL_RANGE):
			printf(
			    "Invalid move, val: %d out of move range (min: 1, max: "
			    "%d)!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_VAL_HORIZONTAL):
			printf(
			    "Invalid move, val: %d already present in row "
			    "%d!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_VAL_VERTICAL):
			printf(
			    "Invalid move, val: %d already present in column "
			    "%d!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_VAL_BLOCK):
			printf(
			    "Invalid move, val: %d already present in "
			    "block[%d][%d]!\n",
			    arg0, arg1, arg2);
			break;
		case (ERROR_MOVE_INVALID_ALREADY_SET):
			printf(
			    "Invalid move, cell[%d][%d] was already set, use edit to "
			    "modify cell!\n",
			    arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_FIXED):
			printf("Invalid move, cell[%d][%d] has a fixed value!\n", arg0,
			       arg1);
			break;
		case (ERROR_MOVE_INVALID_MODE):
			printf("Invalid cell mode!\n");
			break;
		case (ERROR_MOVE_INVALID_EMPTY):
			printf("Invalid move, cell[%d][%d] has no value!\n", arg0, arg1);
			break;
		case (ERROR_MOVE_INVALID_UNDO):
			printf("No more moves to undo!\n");
			break;
		case (ERROR_MOVE_INVALID_REDO):
			printf("No more moves to redo!\n");
			break;
		default:
			break;
	}
	printf(DEFAULT);
}

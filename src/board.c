/* board.c */
#include "board.h"

#include <stdio.h>

/*
 * global variables
 */
struct cell ***glob_board = NULL;
int glob_board_size = 0;   /* X * Y */
int glob_board_size_n = 0; /* X dim*/
int glob_board_size_m = 0; /* Y dim*/
struct linkedlist *glob_move_history = NULL;

/*
 * init a cell with read/write mode and a default value = 0
 */
struct cell *cell_init() {
	struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));
	new_cell->val = EMPTY_CELL;
	new_cell->mode = MODE_RW;
	return new_cell;
}

/*//////////////////////////////////////BOARD
 * FUNCTIONS///////////////////////////*/

/*
 * init board struct with dimensions n and m
 */
void board_init(int size_m, int size_n) {
	if (size_m * size_n < 2) {
		printf(RED "Board size can't be lower than 2\n" DEFAULT);
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

/*
 * free board from memory
 */
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

/*
 * print board to console
 */
void board_print() {
	if (!board_is_init()) {
		return;
	}
	if (glob_board_size > BOARD_MAX_PRINT_SIZE) {
		printf("board too big to print\n");
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

			if (glob_board[i][j]->val == EMPTY_CELL) {
				printf("    ");
			} else if (glob_board[i][j]->mode == MODE_F) {
				printf("%2d.", glob_board[i][j]->val);
			} else {
				printf(" %2d ", glob_board[i][j]->val);
			}
		}
		/* print last border as well as the line number */
		printf("|%d\n", i);
	}
	board_print_dashes();

	printf("\n");
	// history_print();
}

/*
 * print board to console
 */
void board_print_dashes() {
	for (int i = 0; i < glob_board_size * 4 + glob_board_size_n + 1; i++) {
		printf("-");
	}
	printf("\n");
}

/*
 * reset board
 */
void board_reset() {
	if (!board_is_init()) {
		return;
	}
	board_free();
	board_init(glob_board_size_m, glob_board_size_n);
}

/*
 * return true if board is already init, otherwise print an error message and
 * return false
 */
bool board_is_init() {
	if (glob_board == NULL) {
		printf(RED "Board not init\n" DEFAULT);
		return false;
	}
	return true;
}

int counter = 0;
bool board_bt_solve(int x, int y) {
	for (int i = 1; i <= glob_board_size; i++) {
		counter++;
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
			printf("finished with counter = %d\n", counter);
			counter = 0;
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

/*
 * check if move is in bounds
 */
bool move_is_valid_coordinate(int x, int y) {
	if (!board_is_init()) {
	} else if (x < 0 || x >= glob_board_size) {
		printf(RED
		       "Invalid move, x: %d out of board bounds (min: 0, max: "
		       "%d)\n" DEFAULT,
		       x, glob_board_size - 1);
		return false;
	} else if (y < 0 || y >= glob_board_size) {
		printf(RED
		       "Invalid move, y: %d out of board bounds (min: 0, max: "
		       "%d)\n" DEFAULT,
		       y, glob_board_size - 1);
		return false;
	}
	return true;
}

/*
 * check if move val is in the right range
 */
bool move_is_valid_range(int val) {
	if (val < 1 || val > glob_board_size) {
		printf(RED
		       "Invalid move, val: %d out of move range (min: 1, max: "
		       "%d)\n" DEFAULT,
		       val, glob_board_size);
		return false;
	}
	return true;
}

/*
 * iterate through board[...][y] and return false if val is present in any other
 * cell
 */
bool move_is_valid_horizontal(int val, int y) {
	if (!board_is_init()) {
		return false;
	}

	for (int i = 0; i < glob_board_size; i++) {
		if (glob_board[i][y]->val == val) {
			printf(RED
			       "Invalid move, val: %d already present in horizontal line "
			       "%d\n" DEFAULT,
			       val, y);
			return false;
		}
	}
	return true;
}

/*
 * iterate through board[x][...] and return false if val is present in any other
 * cell
 */
bool move_is_valid_vertical(int val, int x) {
	if (!board_is_init()) {
		return false;
	}

	for (int i = 0; i < glob_board_size; i++) {
		if (glob_board[x][i]->val == val) {
			printf(RED
			       "Invalid move, val: %d already present in vertical line "
			       "%d\n" DEFAULT,
			       val, x);
			return false;
		}
	}
	return true;
}

/*
 * iterate through the current block and return false if val is already present
 */
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
				printf(RED
				       "Invalid move, val: %d already present in "
				       "block[%d][%d]\n" DEFAULT,
				       val, x_block, y_block);
				return false;
			}
		}
	}
	return true;
}

/*
 * set move on board only if the cell is modifiable
 */
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
			printf(RED
			       "Invalid move, cell[%d][%d] was already set, use edit to "
			       "modify cell\n" DEFAULT,
			       x, y);
			break;
		case MODE_F:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT,
			       x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}

/*
 * set move on board if the cell was already set
 */
void move_edit(int val, int x, int y) {
	if (!move_is_valid(val, x, y)) {
		return;
	}

	switch (glob_board[x][y]->mode) {
		case MODE_RW:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x,
			       y);
			break;
		case MODE_R:
			history_insert(val, glob_board[x][y]->val, x, y, MOVE_EDI);
			glob_board[x][y]->val = val;
			break;
		case MODE_F:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT,
			       x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}

/*
 * remove board[x][y], give it:
 * read/write mode and make it an empty cell
 * insert old value into the history
 */
void move_remove(int x, int y) {
	if (!move_is_valid_coordinate(x, y)) {
		return;
	}
	switch (glob_board[x][y]->mode) {
		case MODE_RW:
			printf(RED "Invalid move, cell[%d][%d] has no value\n" DEFAULT, x,
			       y);
			break;
		case MODE_R:
			glob_board[x][y]->mode = MODE_RW;
			history_insert(EMPTY_CELL, x, y, glob_board[x][y]->val, MOVE_REM);
			glob_board[x][y]->val = EMPTY_CELL;
			break;
		case MODE_F:
			printf(RED "Invalid move, cell[%d][%d] has a fixed value\n" DEFAULT,
			       x, y);
			break;
		default:
			printf(RED "Invalid cell mode\n" DEFAULT);
	}
}

/*
 * remove prev move and clear the board where it was set.
 */
void move_undo() {
	if (!board_is_init()) {
		return;
	}

	if (!linkedlist_rewind_current(glob_move_history)) {
		printf(RED "No more moves to undo\n" DEFAULT);
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
			printf("TYPE ERROR IN UNDO \n");
	}
}

/*
 * restore prev move and set it. We don't need to check the move,
 * since this is a previously inserted move, which was already validated
 */
void move_redo() {
	if (!board_is_init()) {
		return;
	}

	if (!linkedlist_forward_current(glob_move_history)) {
		printf(RED "No more moves to redo\n" DEFAULT);
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
			printf("TYPE ERROR IN UNDO \n");
	}
}

/*//////////////////////////////////////HISTORY
 * FUNCTIONS/////////////////////////*/

/*
 * add move to history, first node in the history is a dummy node which will
 * never be accesed.
 */
void history_insert(int val, int x, int y, int val_prev, int move_type) {
	if (glob_move_history == NULL) {
		/* dummy node */
		linkedlist_init(&glob_move_history, MOVE_DUM, MOVE_DUM, MOVE_DUM,
		                MOVE_DUM, MOVE_DUM);
	}
	linkedlist_insert(glob_move_history, val, x, y, val_prev, move_type);
}

/*
 * internal function used for debugging
 */
void history_print() {
	printf("     Move history: ");
	linkedlist_print_until_current(glob_move_history);
	printf("Full Move history: ");
	linkedlist_print(glob_move_history);
	printf("\n");
}

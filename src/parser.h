/* parser.h */
#include <ctype.h>  /* using isdigit */
#include <string.h> /* using strcmp */

#include "board.h"

#ifndef PARSER_H_
#define PARSER_H_

#define RESET "reset"
#define SET "set"
#define EDIT "edit"
#define REMOVE "remove"
#define UNDO "undo"
#define REDO "redo"
#define EXIT "exit"
#define CLEAR "clear"
#define HELP "help"
#define SOLVE "solve"
#define STARS "\t>>  "

/**
 * On success, the game will start and the user can interact with the console
 */
void start_game();

/**
 * On success, get the user's input and set it the dimension m and n. If the
 * user only gives one dimension then assume m = n. If the user gives a non
 * valid input such as: A non integer input m * n < MIN_BOARD_SIZE or m*n >
 * MAX_BOARD_SIZE Empty input more than 2 arguments then an error will be
 * displayed and the function will ask the user for a different input.
 */
void get_mn_dim(int* size_m, int* size_n);
/**
 * On success, get the usere's input and check if it's a valid (case sensative)
 * command. If however the command was not valid, an error message will be
 * displayed and the function will ask the user for a different input.
 */
void get_command();

/**
 * Check if the tokenized command  = RESET.
 * On success reset the board to the original game.
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_reset(char* token_command);

/**
 * Check if the tokenized command  = SET VAL X Y.
 * On success, board[x][y] = val.
 * If the user enters more than three arguments, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_set(char* token_command);

/**
 * Check if the tokenized command  = EDIT NEW_VAL X Y.
 * On success, board[x][y] = new_val.
 * If the user enters more than three arguments, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_edit(char* token_command);

/**
 * Check if the tokenized command  = REMOVE X Y.
 * On success, board[x][y] = EMPTY.
 * If the user enters more than two arguments, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_remove(char* token_command);

/**
 * Check if the tokenized command  = UNDO.
 * On success, the game will reverse the last move.
 * An Insert move will be deleted
 * A remove move will be reinserted
 * An edit move will be unedited and set back to its previous value
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 * */
bool is_valid_undo(char* token_command);

/**
 * Check if the tokenized command  = REDO.
 * On success, the game will unreverse the last move.
 * An Insert move will be deleted
 * A remove move will be reinserted
 * An edit move will be unedited and set back to its previous value
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_redo(char* token_command);

/**
 * Check if the tokenized command = EXIT.
 * On success, the game will free every allocated memory and terminate.
 * The function will ignore any additional arguments after validating the
 * command EXIT
 * @param token_command - user intered command
 * @return
 */
bool is_valid_exit(char* token_command);

/**
 * Check if the tokenized command  = CLEAR.
 * On success, the game will clear the console.
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_clear(char* token_command);

/**
 * Check if the tokenized command  = HELP.
 * On success, the game will display all the commands the user may enter.
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_help(char* token_command);

/**
 * Check if the tokenized command  = SOLVE.
 * On success, the game will solve the board.
 * If the user enters more than one argument, an error message will be
 * displayed.
 * @param token_command - user intered command
 * @return
 */
bool is_valid_solve(char* token_command);

/**
 * Check if the given string is a number. return
 * @param token
 * @return - true if number, false otherwise
 */
bool is_number(char* token);

/**
 * Function is called at the end of each is_valid_... function to check if there
 * are any more arguments passed. If that is not the case then an error message
 * will be displayed.
 * @return - true if empty, false otherwise
 */
bool is_command_end();

typedef enum PARSER_ERROR {
	ERROR_ARGUMENT_FEW,
	ERROR_ARGUMENT_MANY,
	ERROR_ARGUMENT_MAX_MIN_DIM,
	ERROR_INVALID_DIM,
	ERROR_INVALID_COMMAND,
	ERROR_INVALID_VAL,
	ERROR_INVALID_X,
	ERROR_INVALID_Y,
	SUCCESS,
} PARSER_ERROR;

void parser_error_handler(PARSER_ERROR err);
#endif

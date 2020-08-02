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
#define STARS "\t>>  "

void start_game();
void get_mn_dim(int* size_m, int* size_n);
void get_command();

/*
 * user methods
 */
bool is_valid_reset(char* token_command);
bool is_valid_set(char* token_command);
bool is_valid_edit(char* token_command);
bool is_valid_remove(char* token_command);
bool is_valid_undo(char* token_command);
bool is_valid_redo(char* token_command);
bool is_valid_exit(char* token_command);
bool is_valid_clear(char* token_command);
bool is_valid_help(char* token_command);

/*
 * internal methods
 */
bool is_number(char* token);
bool is_command_end();
#endif

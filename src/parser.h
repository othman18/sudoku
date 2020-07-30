/* parser.h */
#include "board.h"
#include <string.h> /* using strcmp */
#include <ctype.h> /* using isdigit */

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
void get_mn_dim(int *size_m, int *size_n);
void get_command();

/*
 * user methods
 */
bool is_valid_reset(char* command);
bool is_valid_set(char* command);
bool is_valid_edit(char* command);
bool is_valid_remove(char* command);
bool is_valid_undo(char* command);
bool is_valid_redo(char* command);
bool is_valid_exit(char* command);
bool is_valid_clear(char* command);
bool is_valid_help(char* command);

/*
 * internal methods
 */
bool is_number(char* token);
#endif

// parser.h
#include "../board.h"


#ifndef PARSER_H_
#define PARSER_H_

void get_command();
bool is_number(char* token);
bool is_valid_print(char* command);
bool is_valid_reset(char* command);
bool is_valid_set(char* command);
bool is_valid_edit(char* command);
bool is_valid_remove(char* command);
bool is_valid_undo(char* command);
bool is_valid_redo(char* command);
bool is_valid_exit(char* command);

#endif

/* parser.c */
#include "parser.h"
#define M 256 /* max size of each command */


/*
 * global variables
 */
const char glob_delemeter[8] = " \t\r\n\v\f";

void start_game(){
	setbuf(stdout, NULL); /* clear stdout */
    int size_m = -1, size_n = 0;
    get_mn_dim(&size_m, &size_n);
    system("clear");
    board_init(size_m, size_n);
    board_print();
    get_command();
    board_free();
    
}

/*
 * get the user's input and set it the dimension m and n
 * if the user only gives one dimension then assume m = n
 */
void get_mn_dim(int *size_m, int *size_n){
    printf("Enter board dimensions m X n: ");
    char *command = (char*)malloc(M);
    if(fgets(command, M, stdin) != NULL){}

    char *token_m = strtok(command, glob_delemeter); /* tokinize command */
    char *token_n = strtok(NULL, glob_delemeter);
    
    bool ok_m = false, ok_n = false;

    if(token_m == NULL){
        printf(RED "Error, entered too few parameters.\n" DEFAULT);
    }
    else if(!is_number(token_m)){
        printf(RED "Error, dimension m must be an int.\n" DEFAULT);
    }
    else{
        *size_m = atoi(token_m);
        ok_m = true;
        /* If the user only game one dim then assume n=m*/
        if(token_n == NULL){
            *size_n = atoi(token_m);
            ok_n = true;
        }
        else if(!is_number(token_n)){
            printf(RED "Error, dimension n must be an int.\n" DEFAULT);
        }
        else{
            *size_n = atoi(token_n);
            ok_n = true;
        }
    }
    
    free(command);
    
    if(!ok_n || !ok_m || (*size_n) * (*size_m) < 9){
        printf(RED "Error, dimension mXn can't be lower than 9\n" DEFAULT);
        get_mn_dim(size_m, size_n);
    }
}


/*
 * get the command entered by the user and check if it's a valid command
 * print error otherwise and wait for the next command
 */
void get_command(){
    printf("To list game commands, type \"help\"\n");
	printf("Enter command: ");
	char *command = (char*)malloc(M);
	if(fgets(command, M, stdin) != NULL){}
	bool print_board = true;
	if(is_valid_exit(command)){
		free(command);
		return;
	}
	else if(is_valid_set(command)){}
	else if(is_valid_reset(command)){}
	else if(is_valid_edit(command)){}
	else if(is_valid_remove(command)){}
	else if(is_valid_undo(command)){}
	else if(is_valid_redo(command)){}
	else if(is_valid_clear(command)){}
	else if(is_valid_help(command)){}
	else{
		printf(RED "Error, no such command exists\n" DEFAULT);
		print_board = false;
	}

	if(print_board){
		board_print();
	}
	free(command);
	get_command();
}


/*
 * check if command == "reset" and reset the board
 */
bool is_valid_reset(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */

	if(token_command == NULL ||
        strcmp(token_command, RESET)) {
		return false;
	}
    /* using NULL will continue to tokinize command */
	char *token_end = strtok(NULL, glob_delemeter);
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	board_reset();
	return true;
}


/*
 * check if command == "set val x y" board[x][y] = val, unless
 * val/x/y is out of bounds
 */
bool is_valid_set(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */

	if(token_command == NULL ||
        strcmp(token_command, SET)) {
		return false;
	}
	char *token_val = strtok(NULL, glob_delemeter);
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);
	char *token_end = strtok(NULL, glob_delemeter);

	if(token_val == NULL ||
		token_x == NULL ||
		token_y == NULL){
		printf(RED "Error, entered too few parameters.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_val)){
		printf(RED "Error, val must be an int.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_x)){
		printf(RED "Error, X must be an int.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_y)){
		printf(RED "Error, Y must be an int.\n" DEFAULT);
		return true;
	}
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	move_set(atoi(token_val), atoi(token_x), atoi(token_y));
	return true;
}


/*
 * check if command == "edit val x y" board[x][y] = val, unless
 * board[x][y] is empty
 * val/x/y is out of bounds
 */
bool is_valid_edit(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */

	if(token_command == NULL ||
        strcmp(token_command, EDIT)) {
		return false;
	}
	char *token_val = strtok(NULL, glob_delemeter);
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);
	char *token_end = strtok(NULL, glob_delemeter);

	if(token_val == NULL ||
		token_x == NULL ||
		token_y == NULL){
		printf(RED "Error, entered too few parameters.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_val)){
		printf(RED "Error, val must be an int.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_x)){
		printf(RED "Error, X must be an int.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_y)){
		printf(RED "Error, Y must be an int.\n" DEFAULT);
		return true;
	}
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	move_edit(atoi(token_val), atoi(token_x), atoi(token_y));
	return true;
}


/*
 * check if command == "remove x y" board[x][y] = empty, unless
 * board[x][y] is empty
 * x/y is out of bounds
 */
bool is_valid_remove(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */

	if (token_command == NULL ||
        strcmp(token_command, REMOVE)) {
		return false;
	}
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);
	char *token_end = strtok(NULL, glob_delemeter);

	if(token_x == NULL ||
	   token_y == NULL){
		printf(RED "Error, entered too few parameters.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_x)){
		printf(RED "Error, X must be an int.\n" DEFAULT);
		return true;
	}
	if(!is_number(token_y)){
		printf(RED "Error, Y must be an int.\n" DEFAULT);
		return true;
	}
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	move_remove(atoi(token_x), atoi(token_y));
	return true;
}


/*
 * check if command == "undo" then reverse the last move, unless
 * there are no more moves do undo
 */
bool is_valid_undo(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */

	if (token_command == NULL ||
        strcmp(token_command, UNDO)) {
		return false;
	}
	char *token_end = strtok(NULL, glob_delemeter);

	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	move_undo();
	return true;
}


/*
 * check if command == "redo" then redo the last move, unless
 * there are no more moves do redo
 */
bool is_valid_redo(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */
    if (token_command == NULL ||
        strcmp(token_command, REDO)) {
		return false;
	}
	char *token_end = strtok(NULL, glob_delemeter);

	if(token_command == NULL ||
       token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	move_redo();
	return true;
}


/*
 * check if command == "exit" then free memory and terminate
 */
bool is_valid_exit(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */
    if (token_command == NULL ||
        strcmp(token_command, EXIT)) {
		return false;
	}
    /* using NULL will continue to tokinize command */
	char *token_end = strtok(NULL, glob_delemeter);
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
	return true;
}


/*
 * check if command == "clear" then clear the screen
 */
bool is_valid_clear(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */
	if (token_command == NULL ||
        strcmp(token_command, CLEAR)) {
		return false;
	}
    /* using NULL will continue to tokinize command */
	char *token_end = strtok(NULL, glob_delemeter);
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
    system("clear");
	return true;
}


/*
 * check if command == "help" then display all the command options
 */
bool is_valid_help(char* command){
	char command_tmp[M];
	strcpy(command_tmp, command);
	char *token_command = strtok(command_tmp, glob_delemeter); /* tokinize command */
	if (token_command == NULL ||
        strcmp(token_command, HELP)) {
		return false;
	}
    /* using NULL will continue to tokinize command */
	char *token_end = strtok(NULL, glob_delemeter);
	if(token_end != NULL){
		printf(RED "Error, entered too many parameters.\n" DEFAULT);
		return true;
	}
    system("clear");
	printf("Available commands:\n" STARS "set VAL:int X:int Y:int => [X][Y] = Val\n"
		STARS "remove X:int Y:int => [X][Y] = EMPTY\n"
		STARS "undo => undo last move\n"
		STARS "redo => redo last move\n"
		STARS "clear => clear terminal\n"
		STARS "reset => reset board\n"
		STARS "exit => end program\n");
	return true;
}


/*
 * check if the string token is a number
 */
bool is_number(char* token){
	if(token == NULL){
		return false;
	}
	for (int i = 0; token[i] != '\0'; i++){
		if(!isdigit(token[i])){
			return false;
		}
	}
	return true;
}

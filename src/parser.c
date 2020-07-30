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
    
    char *token_command = strtok(command, glob_delemeter); /* tokinize command */
    
	if(is_valid_exit(token_command)){
		free(command);
		return;
	}
	else if(is_valid_set(token_command)){}
	else if(is_valid_reset(token_command)){}
	else if(is_valid_edit(token_command)){}
	else if(is_valid_remove(token_command)){}
	else if(is_valid_undo(token_command)){}
	else if(is_valid_redo(token_command)){}
	else if(is_valid_clear(token_command)){}
	else if(is_valid_help(token_command)){
        print_board = false;
    }
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
 * check if tokenized command == "reset" and reset the board
 */
bool is_valid_reset(char* token_command){
	if(token_command == NULL ||
        strcmp(token_command, RESET)) {
		return false;
	}
    
    if(is_command_end()){
        board_reset();
    }
	return true;
}


/*
 * check if tokenized command == "set val x y" board[x][y] = val, unless
 * val/x/y is out of bounds
 */
bool is_valid_set(char* token_command){
	if(token_command == NULL ||
        strcmp(token_command, SET)) {
		return false;
	}
	char *token_val = strtok(NULL, glob_delemeter);
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);

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
    
    if(is_command_end()){
        move_set(atoi(token_val), atoi(token_x), atoi(token_y));
    }
    return true;
}


/*
 * check if tokenized command == "edit val x y" board[x][y] = val, unless
 * board[x][y] is empty
 * val/x/y is out of bounds
 */
bool is_valid_edit(char* token_command){
	if(token_command == NULL ||
        strcmp(token_command, EDIT)) {
		return false;
	}
	char *token_val = strtok(NULL, glob_delemeter);
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);

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

    if(is_command_end()){
        move_edit(atoi(token_val), atoi(token_x), atoi(token_y));
    }
	return true;
}


/*
 * check if tokenized command == "remove x y" board[x][y] = empty, unless
 * board[x][y] is empty
 * x/y is out of bounds
 */
bool is_valid_remove(char* token_command){
	if (token_command == NULL ||
        strcmp(token_command, REMOVE)) {
		return false;
	}
	char *token_x = strtok(NULL, glob_delemeter);
	char *token_y = strtok(NULL, glob_delemeter);

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
    
    if(is_command_end()){
        move_remove(atoi(token_x), atoi(token_y));
    }
	return true;
}


/*
 * check if tokenized command == "undo" then reverse the last move, unless
 * there are no more moves do undo
 */
bool is_valid_undo(char* token_command){
	if (token_command == NULL ||
        strcmp(token_command, UNDO)) {
		return false;
	}

    if(is_command_end()){
        move_undo();
    }
	return true;
}


/*
 * check if tokenized command == "redo" then redo the last move, unless
 * there are no more moves do redo
 */
bool is_valid_redo(char* token_command){
    if (token_command == NULL ||
        strcmp(token_command, REDO)) {
		return false;
	}
    if(is_command_end()){
        move_redo();
    }
	return true;
}


/*
 * check if tokenized command == "exit" then free memory and terminate
 */
bool is_valid_exit(char* token_command){
    if (token_command == NULL ||
        strcmp(token_command, EXIT)) {
		return false;
	}
	return true;
}


/*
 * check if tokenized command == "clear" then clear the screen
 */
bool is_valid_clear(char* token_command){
	if (token_command == NULL ||
        strcmp(token_command, CLEAR)) {
		return false;
	}
    
    if(is_command_end()){
        system("clear");
    }
	return true;
}


/*
 * check if tokenized command == "help" then display all the command options
 */
bool is_valid_help(char* token_command){
	if (token_command == NULL ||
        strcmp(token_command, HELP)) {
		return false;
	}

    if(is_command_end()){
        system("clear");
        printf("Available commands:\n" STARS "set VAL:int X:int Y:int => [X][Y] = Val\n"
            STARS "remove X:int Y:int => [X][Y] = EMPTY\n"
            STARS "edit NEW_VAL:int X:int Y:int => [X][Y] = NEW_VAL\n"
            STARS "undo => undo last move\n"
            STARS "redo => redo last move\n"
            STARS "clear => clear terminal\n"
            STARS "reset => reset board\n"
            STARS "exit => end program\n");
    }
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


/*
 * method called at the end of a is_valid_... method to check if there are any
 * more arguments passed. If that is the case then an error is printed out
 */
bool is_command_end(){
    char *token_end = strtok(NULL, glob_delemeter);
    /* using NULL will continue to tokinize command */
    if(token_end != NULL){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return false;
    }
    return true;
}


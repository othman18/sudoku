//parser.c
#include "parser.h"
#define M 256 // max size of each command


/* global variables*/
char *glob_null_char = '\0';
const char glob_delemeter[8] = " \t\r\n\v\f";


void start_game(){
    setbuf(stdout, NULL); // clear stdout
	if(system("clear"));

    printf("Enter board dimensions N X N: ");
    char *command = (char*)malloc(M);
    if(fgets(command, M, stdin) != NULL){}
    char *token_dim = strtok(command, glob_delemeter); // tokinize command
    if(!is_number(token_dim)){
        printf(RED "Error, dimension must be an int\n" DEFAULT);
        free(command);
        start_game();
    }
    else{
        int dim = atoi(token_dim);
        if(dim < 2){
            printf(RED "Error, dimension can't be lower than 2\n" DEFAULT);
        	free(command);
            start_game();
        }
        if(dim > 9){
            printf(RED "Error, dimension can't exceed 9 (for now...)\n" DEFAULT);
	        free(command);
            start_game();
        }
        else{
            board_init(dim);
    //      board_generate(dim);
            board_print();
            get_command();
	        free(command);
            board_free();
        }
    }
}


void get_command(){
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


bool is_valid_reset(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, RESET)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter); // using NULL will continue to tokinize command
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    board_reset();
	return true;
}


bool is_valid_set(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, SET)) {
        return false;
    }
    char *token_val = strtok(NULL, glob_delemeter);
    char *token_x = strtok(NULL, glob_delemeter);
    char *token_y = strtok(NULL, glob_delemeter);
    char *token_end = strtok(NULL, glob_delemeter);

    if(token_val == glob_null_char ||
       	token_x == glob_null_char ||
       	token_y == glob_null_char){
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
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    move_set(atoi(token_val), atoi(token_x), atoi(token_y));
    return true;
}


bool is_valid_edit(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, EDIT)) {
        return false;
    }
    char *token_val = strtok(NULL, glob_delemeter);
    char *token_x = strtok(NULL, glob_delemeter);
    char *token_y = strtok(NULL, glob_delemeter);
    char *token_end = strtok(NULL, glob_delemeter);

    if(token_val == glob_null_char ||
		token_x == glob_null_char ||
       	token_y == glob_null_char){
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
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    move_edit(atoi(token_val), atoi(token_x), atoi(token_y));
    return true;
}


bool is_valid_remove(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, REMOVE)) {
        return false;
    }
    char *token_x = strtok(NULL, glob_delemeter);
    char *token_y = strtok(NULL, glob_delemeter);
    char *token_end = strtok(NULL, glob_delemeter);

    if(token_x == glob_null_char ||
       token_y == glob_null_char){
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
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    move_remove(atoi(token_x), atoi(token_y));
    return true;
}


bool is_valid_undo(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, UNDO)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter);

    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    move_undo();
    return true;
}


bool is_valid_redo(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command

    if (strcmp(token_command, REDO)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter);

    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    move_redo();
    return true;
}


bool is_valid_exit(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command
    if (strcmp(token_command, EXIT)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter); // using NULL will continue to tokinize command
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    return true;
}


bool is_valid_clear(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command
    if (strcmp(token_command, CLEAR)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter); // using NULL will continue to tokinize command
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
	if(system("clear"));
    return true;
}


bool is_valid_help(char* command){
    char command_tmp[M];
    strcpy(command_tmp, command);
    char *token_command = strtok(command_tmp, glob_delemeter); // tokinize command
    if (strcmp(token_command, HELP)) {
        return false;
    }
    char *token_end = strtok(NULL, glob_delemeter); // using NULL will continue to tokinize command
    if(token_end != glob_null_char){
        printf(RED "Error, entered too many parameters.\n" DEFAULT);
        return true;
    }
    
    printf("Available commands:\n" STARS "set VAL:int X:int Y:int => [X][Y] = Val\n"
    	STARS "remove X:int Y:int => [X][Y] = EMPTY\n"
    	STARS "undo => undo last move\n"
    	STARS "redo => redo last move\n"
    	STARS "clear => clear terminal\n"
    	STARS "reset => reset board\n"
    	STARS "exit => end program\n");
    return true;
}


bool is_number(char* token){
    if(token == NULL){
        return false;
    }
    for (int i = 0; token[i] != '\0'; i++){
        if(!isdigit(token[i]) != 0){
            return false;
        }
    }
	return true;
}




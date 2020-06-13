//parser.c
#include "parser.h"
#define M 256 // max size of each command


void get_command(){
	char *command = (char*)malloc(M);
	printf("Enter command\n");
	
	if(fgets(command, M, stdin) != NULL){
	
	}
	printf("%s\n",command);
	
	if(is_valid_print(command)){}
	else if(is_valid_reset(command)){}
	else if(is_valid_set(command)){}
	else if(is_valid_edit(command)){}
	else if(is_valid_undo(command)){}
	else if(is_valid_redo(command)){}
	else if(is_valid_print(command)){}
	else if(is_valid_exit(command)){}
	else if(is_valid_print(command)){}
	else{
		printf("Invalid command\n");
	}

	free(command);
	get_command();
}


bool is_valid_print(char* command){
	return true;
}


bool is_valid_reset(char* command){
	return true;
}


bool is_valid_set(char* command){
	return true;
}


bool is_valid_edit(char* command){
	return true;
}


bool is_valid_remove(char* command){
	return true;
}


bool is_valid_undo(char* command){
	return true;
}


bool is_valid_redo(char* command){
	return true;
}


bool is_valid_exit(char* command){
	return true;
}


bool is_number(char* token){
	return true;
}



#include "board.h"
#include "utils/stack.h"



int main(){
	
	init_board(3);
	
	set_move(1, 0, 0);	
	set_move(2, 1, 0);	
	set_move(3, 2, 0);	

	print_board();
	
	set_move(3, 0, 0);	
		
	edit_move(3, 0, 0);	

	print_board();
	
	delete_board();
	printf("end\n");
	return EXIT_SUCCESS;
}

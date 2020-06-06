#include "stack.h"


int main(){

	struct stack *a = NULL;
	
	init_stack(&a, 1);
		
	for(int i = 2; i < 6; i++){
		push(a, i);
	}

	for(int i = 0; i < 6; i++){	
//		printf("%d, ", pop(a));
	}
	printf("\n");
		

	printf("end\n");

}

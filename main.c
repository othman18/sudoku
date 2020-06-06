#include "stack.h"



int main(){

	struct stack *a = NULL;
	
	init_stack(a, 1);
	
	push(a, 2);
	
	for(int i = 2; i < 5; i++){
//		push(a, i);
	}

	for(int i = 2; i < 5; i++){	
//		printf("%d, ", pop(a));
	}
	printf("\n");
		

	printf("end\n");

}

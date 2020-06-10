#include "board.h"


int main(){
    //TODO: add a tail to the linkedlist
    //TODO: add a tail to the linkedlist
    //TODO: add a tail to the linkedlist
    //TODO: add a tail to the linkedlist
    //TODO: add a tail to the linkedlist

//    init_board(3);
	
//    delete_board();
    
    struct linkedlist *lst = NULL;
    
    init_linkedlist(&lst, 1, 0 ,0);
    
    insert_head_linkedlist(lst, 2, 0, 0);
    insert_head_linkedlist(lst, 3, 0, 0);
    insert_head_linkedlist(lst, 4, 0, 0);
    
    
    print_linkedlist(lst);
    
//    remove_node(&lst->head->prev->prev);


    return EXIT_SUCCESS;
}

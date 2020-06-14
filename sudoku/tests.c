// tests.c
#include "tests.h"


void run_tests(){
    // tests for valgrind
/*
    test1();
    test2();
	test3();
 	test4();
 	test5();
    test6();
//*/
    test7();
}


void test1(){
    printf("\ntest1\n");
    struct linkedlist *lst = NULL;
    
    linkedlist_init(&lst, 1, 0 ,0);
    linkedlist_insert(lst, 2, 0, 0);
    linkedlist_insert(lst, 3, 0, 0);
    linkedlist_insert(lst, 4, 0, 0);
    linkedlist_print(lst);
    
    linkedlist_init(&lst, 10, 0 ,0);
    linkedlist_insert(lst, 20, 0, 0);
    linkedlist_print(lst);

    linkedlist_free(&lst);
}


void test2(){
    printf("\ntest2\n");
    board_init(5);
    board_print();
    board_free();
    board_print();
	board_free();
}


void test3(){
    printf("\ntest3\n");
    board_init(5);
    board_print();
    board_init(3);
    board_print();
    board_free();
}


void test4(){
	// undo and redo moves
    printf("\ntest4\n");
    board_init(5);
	move_set(1 ,0, 0);
	move_set(2 ,1, 1);
	move_set(3 ,2, 2);
	move_set(4 ,3, 3);
	move_set(5 ,4, 4);
	board_print();
	history_print();

	move_undo();
	move_undo();
	move_undo();
	move_undo();

	board_print();
	history_print();

	move_redo();
	move_redo();
	move_redo();
	board_print();
	history_print();

	move_set(1, 0, 4);	
	board_print();
	history_print();
    board_free();
}


void test5(){
	//moves before init
	printf("\ntest5\n");
	move_set(1 ,0, 0);
	move_is_valid(0, 0, 0);
	move_set(0, 0, 0);
	move_edit(0, 0, 0);
	move_remove(0, 0);
	move_undo();
	move_redo();
}


void test6(){
	printf("\ntest6\n");
	board_init(5);
	move_set(1, 0, 0);
	move_edit(1, 1, 0);
	move_remove(0, 0);
	move_remove(0, 0);
	move_remove(0, 0);
	board_free();
}


void test7(){
	printf("\ntest7\n");
	board_init(9);
	move_set(1, 0, 4);
	move_set(6, 0, 5);
	move_set(8, 3, 1);
	board_print();
	board_reset();
	board_print();
	board_free();
}











// tests.c
#include "tests.h"


void run_tests(){
    // tests for valgrind
    test1();
    test2();
    test3();
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
}


void test3(){
    printf("\ntest3\n");
    board_init(5);
    board_print();
    board_init(3);
    board_print();
    board_free();
}

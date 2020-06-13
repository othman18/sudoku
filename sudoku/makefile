CC = g++-9#gcc

OBJS = main.o linkedlist.o board.o parser.o tests.o #stack.o 
EXEC = exe

COMP_FLAGS = -ansi -O3 -Wall -pedantic-errors
#GUROBI_COMP = -I/usr/local/lib/gurobi563/include
#GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

linkedlist.o: utils/linkedlist.h
	$(CC) $(COMP_FLAGS) -c utils/linkedlist.c

#stack.o: utils/stack.h 
#	$(CC) $(COMP_FLAGS) -c utils/stack.c

board.o: board.h
	$(CC) $(COMP_FLAGS) -c $*.c

main.o: tests.h
	$(CC) $(COMP_FLAGS) -c $*.c

parser.o: utils/parser.h
	$(CC) $(COMP_FLAGS) -c utils/parser.c

tests.o: tests.h
	$(CC) $(COMP_FLAGS) -c $*.c
clean:
	rm -f *.o $(EXEC)

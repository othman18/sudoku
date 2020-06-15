CC = g++-9

OBJS = main.o linkedlist.o board.o parser.o tests.o
EXEC = sudoku

COMP_FLAGS = -ansi -O3 -Wall -pedantic-errors
#GUROBI_COMP = -I/usr/local/lib/gurobi563/include
#GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

linkedlist.o: linkedlist.h
	$(CC) $(COMP_FLAGS) -c $*.c

board.o: board.h
	$(CC) $(COMP_FLAGS) -c $*.c

main.o: tests.h
	$(CC) $(COMP_FLAGS) -c $*.c

parser.o: parser.h
	$(CC) $(COMP_FLAGS) -c $*.c

tests.o: tests.h
	$(CC) $(COMP_FLAGS) -c $*.c
clean:
	rm -f *.o $(EXEC)

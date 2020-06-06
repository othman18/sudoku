CC = g++-9#gcc

OBJS = main.o linkedlist.o stack.o
EXEC = exe

COMP_FLAGS = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors
#GUROBI_COMP = -I/usr/local/lib/gurobi563/include
#GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm

main.o: stack.o
	$(CC) $(COMP_FLAGS) -c $*.c

linkedlist.o: linkedlist.h
	$(CC) $(COMP_FLAGS) -c $*.c

stack.o: linkedlist.h
	$(CC) $(COMP_FLAGS) -c $*.c

clean:
	rm -f *.o $(EXEC)

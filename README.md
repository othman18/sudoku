# Sudoku Game & Solver

#### requirements

* g++-9 compiler (or change the makefile to any other version)


#### run game:

* make
* ./sudoku


#### game commands

* set VAL:int X:int Y:int => sets the board(x, y) = val
* remove X:int Y:int => sets the board(x, y) = emtpy
* undo => reverses last move:
	* if last move was set then it will get removed
	* if last move was remove then it will get set again
	* if last move was edit then it will get unedited
* redo => redoes last move that was reversed by undo
* clear => clears terminal
* reset => resets board
* exit => ends program
* help => displays all possible moves


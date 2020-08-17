# Sudoku Game

#### requirements

* gcc compiler


#### run game

```bash
* sh run.sh
```


#### game commands

* set VAL:int X:int Y:int => sets the board(x, y) = val
* remove X:int Y:int => sets the board(x, y) = emtpy
* edit VAL:int X:int Y:int => modify the board(x, y) = new val
* undo => reverses last move:
	* if last move was set then it will get removed
	* if last move was remove then it will get set again
	* if last move was edit then it will get unedited
* redo => redoes last move that was reversed by undo
* print => print board + move history
* clear => clears terminal
* reset => resets board and moves set
* restart => restart game with new board
* exit => ends program
* help => displays all user commands

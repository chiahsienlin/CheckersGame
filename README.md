# CheckersGame
The game is played on a reduced game board size of 6x6 squares and the rules have been modified from the original checkers game. The details about the user flow, the utility function and the cut-off evaluation function could be found in the report.(https://github.com/chiahsienlin/CheckersGame/blob/master/report.pdf)

## Evironment Setup
1.  Language: C++
2.  Operating System: macOS High Sierra version 10.13.1
3.  IDE: Qt Creator 5.11.0
4.  Qt/5.11.0/clang_64/bin/qmake

## How to Build
1.  Install qt5-qmake
2.  In the project directory, execute command `/.../Qt/5.11.0/clang_64/bin/qmake .`
3.  qmake will automatically generate a Makefile, and execute command `make`
4.  The executable application will be generated
5.  Now, you can run the game

## Executalbe (Only for MacOS)
1.  You can download the compressed executable file from 
    https://github.com/chiahsienlin/CheckersGame/blob/master/Checkers.zip
2.  `tar -xf Checkers.zip ` and you will get the 'Checkers' application
3.  Set the security authority: Go to the System Preferences → Security & Privacy → Open anyway

## Rule Description
* The checker board consists of 6 x 6 alternating light and dark squares. The board is placed so that the left corner square     on each player’s side is a dark square.
* There are two types of moves:
  * Regular move: a piece can move forward diagonally to an adjacent square that is empty.
  * Capture move: a piece can jump over and capture an opponent’s piece and land on an empty square (landing on a square that is not empty is not allowed.) The jump must be in the forward diagonal direction and no consecutive jumps are allowed. In addition, every opportunity to jump must be taken. In the case where there are two or more possible jump moves, the player can choose which one to take.
  * No vertical, horizontal or backward moves areallowedforbothregularand capture moves.
* If a player has no legal move to take, his/her turn will be forfeited and the other player will make the next move.
* A player wins when he/she captures all of the other player’s pieces. If both players do not have any legal move to take, the game will end and the player with the most number of pieces left wins; if the two players have the same number of pieces       left, the game is a draw.

## User Interface
![alt text](https://github.com/chiahsienlin/CheckersGame/blob/master/Images/interface.png)
* Before getting into the interface above, you have to choose the difficulty from 1 to 3 and who will move the first step.
* The timer on the left-hand side is for timing the AI player making a move. (no more than 15 sec)
* If you want to move one of the checkers pieces, click the one you choose once and you will see the valid tiles turning into yellow. Click one of the valid tiles to make a move or unclick the original checkers piece you choose.
* The whiteboard on the right-hand side is for the purpose of displaying the status of the game and the judgement given by the judge.

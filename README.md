# CheckersGame
The game is played on a reduced game board size of 6x6 squares and the rules have been modified from the original checkers game.

## Evironment Setup
• Language: C++
• Operating System: macOS High Sierra version 10.13.1
• IDE: Qt Creator 5.11.0
• Qt/5.11.0/clang_64/bin/qmake

## How to Build
• Install qt5-qmake
• In the project directory, execute command /.../Qt/5.11.0/clang_64/bin/qmake .
• You will see a Makefile, and execute command make
• You will see an application be generated

• Now, you can run the game

## Executalbe (Only for MacOS)
• You can download the compressed executable file from 
  https://github.com/chiahsienlin/CheckersGame/blob/master/Checkers.zip
• Decompressed the file
• Set the security authority: Go to the System Preferences → Security & Privacy → Open anyway

## Rule Description
• The checker board consists of 6 x 6 alternating light and dark squares. The board is placed so that the left corner square     on each player’s side is a dark square.
• There are two types of moves:
  - regular move: a piece can move forward diagonally to an adjacent square that is
    empty.
  - capture move: a piece can jump over and capture an opponent’s piece and land
    on an empty square (landing on a square that is not empty is not allowed.) The jump must be in the forward diagonal           direction and no consecutive jumps are allowed. In addition, every opportunity to jump must be taken. In the case where       there are two or more possible jump moves, the player can choose which one to take.
  - No vertical, horizontal or backward moves areallowedforbothregularand capture moves.
• If a player has no legal move to take, his/her turn will be forfeited and the other player will make the next move.
• A player wins when he/she captures all of the other player’s pieces. If both players do not have any legal move to take, the   game will end and the player with the most number of pieces left wins; if the two players have the same number of pieces       left, the game is a draw.

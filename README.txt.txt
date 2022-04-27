EX04: Circle The Cat

Student's info:
name: Michael Basov	ID: 315223156

Task description:
In this task we built a game called circle the cat.
the goal is to prevent a cat from running grom the board by blocking its pasage
by cliking tiles. the game is turn based, after each block the cat will make its move,
if the cat manages to run away, the same level will start over again, if the player 
blocks the cat by blocking it completly the game goes to next level, there are 3 levels
generated randomly with increasing difficulty between each level.
there are two buttons:
undo - reverts the game one move (unblocks the last circle and moves the cat back)
restart - resets the currnet level


List of files:
Board.cpp - draws and manages the objects on the board
Button.cpp - represents a button that can be drawn and clicked
Controller.cpp - controls and runs the game
Cat.cpp - represents the cat and its logic
Graph.cpp - represents a graph, built from the circle objects on the board
// every .cpp file has a .h file with the same name //
CircleData.h - Contains a struct that holds data about a circle
LastMove.h - contains a struct that uses to store info about last move made by player and cat

Main databases:
A vector of circles that contains the board
A graph that used to calcultae shortest path using BFS algorithm

Special Algorithems:

Known bugs:

Other:
I used a graph class i found on the interner, changed it a bit
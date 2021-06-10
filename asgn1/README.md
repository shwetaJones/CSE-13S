#Assignment 1
Program Description: This programs creates a game called "Left, Right, Center". The game uses a random seed and number of players from the user in order to create this game. The game then checks the validity of these inputted values and then playes the game. Each player is initially given $3. If the player has 3 or more dollar's they get 3 dice rolls, if they have $2 they get 2 dice rolls, and finally if they only have $1 they have one dice roll. The dice used in this game has 6 sides, 3 faces, 1 left, 1 right, and 1 center. If a left is rolled, $1 is given to the player on the left, likewise, if a right is rolled a $1 is given to the player on the right. And if a Center is rolled, $1 is placed into the center. The game comes to a close when one player remains, and the money in the center then goes to this winning player. The program can be run through terminal with the Makefile. If "make all" and the "./lrc" is typed into the terminal, the program will run. The program was constructed using C programming.   

## Build 
	$ clang -Wall -Wextra -Wpedantic -o lrc lrc.c

## Clean
	$ rm -f lrc lrc.o

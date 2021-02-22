# Knights Tour With Arbitrary Pieces Added to the board

## Introduction
This program accepts a board layout from stdin and finds a path the knight given can take which goes to each square exactly once.
The knight cannot go to a square where it will be attacked by the additional pieces added to the board unless it has already taken them.

## Format
First specify the size of the board with an integer,  
Then a space character and specify add pieces to the board:
### Adding pieces
- Pieces can be added in standard chess notation with a newline character between each, pawns must have a leading P which cannot be omitted.  
- The first piece must be the touring knight  
- Stop adding pieces with a line of only q
### Example Input
Unformatted:  
8 Nd3  
Qf4  
q

## Things to add
-Accept commandline args for board arrangements.

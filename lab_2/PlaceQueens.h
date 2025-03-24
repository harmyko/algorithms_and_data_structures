#ifndef FIVE_QUEENS
#define FIVE_QUEENS

typedef struct Tile
{
    int row;
    int col;
    int isQueen;
    int isSafe;
} Tile;

typedef struct Board
{
    Tile **tile;
    int n;
} Board;

Board *createEmptyBoard(int n);
void printBoardLegend();
void printBoard(Board *board);
int placeQueens(Board *board, int queensPlaced, int row, int col);
void updateSafety(Board *board, int row, int col, int value);
int solveQueens(Board *board, int numQueens);
void destroyBoard(Board *board);


#endif 

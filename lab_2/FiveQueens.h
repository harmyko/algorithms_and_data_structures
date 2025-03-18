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
} Board;

Board *createEmptyBoard();
void printBoardLegend();
void printBoard(Board *board);
void placeQueen(Board *board, int row, int col);
int solveFiveQueensCoverage(Board *board);
int solveFiveQueensCoverageAndPrintState(Board *board);
void destroyBoard(Board *board);


#endif 

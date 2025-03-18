#include <stdio.h>
#include <stdlib.h>
#include "FiveQueens.h"

int main()
{
    Board *board = createEmptyBoard();

    if (board == NULL)
    {
        printf("Failed to create the board.\n");
        return 1;
    }

    printBoardLegend();

    if (solveFiveQueensCoverageAndPrintState(board))
    {
        printf("Successfully placed 5 queens.\n");
    }
    else
    {
        printf("Failed to place 5 queens.\n");
    }

    destroyBoard(board);

    return 0;
}

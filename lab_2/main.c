#include <stdio.h>
#include <stdlib.h>
#include "PlaceQueens.h"

int main()
{
    int n = 8;
    Board *board = createEmptyBoard(n);

    if (board == NULL)
    {
        printf("Failed to create the board.\n");
        return 1;
    }

    printf("Three tests were performed to confirm the algorithm is working as expected\n\n");

    printf("Chess board's legend:\n");

    printBoardLegend();

    printf("=============================================\n");
    printf("TEST 1: Placing 5 queens on a 8x8 chess board.\n");
    printf("=============================================\n\n");

    if (solveQueens(board, 5))
    {
        printf("Successfully placed 5 queens that protect every tile.\n");
    }
    else
    {
        printf("Failed to place 5 queens that protect every tile.\n");
    }

    printBoard(board);

    destroyBoard(board);

    printf("\n");

    n = 7;
    board = createEmptyBoard(n);

    if (board == NULL)
    {
        printf("Failed to create the board.\n");
        return 1;
    }

    printf("=============================================\n");
    printf("TEST 2: Placing 5 queens on a 7x7 chess board.\n");
    printf("=============================================\n\n");

    if (solveQueens(board, 5))
    {
        printf("Successfully placed 5 queens that protect every tile.\n");
    }
    else
    {
        printf("Failed to place 5 queens that protect every tile.\n");
    }

    printBoard(board);

    destroyBoard(board);

    printf("\n");

    n = 9;
    board = createEmptyBoard(n);

    if (board == NULL)
    {
        printf("Failed to create the board.\n");
        return 1;
    }

    printf("=============================================\n");
    printf("TEST 3: Placing 5 queens on a 9x9 chess board.\n");
    printf("=============================================\n\n");

    if (solveQueens(board, 5))
    {
        printf("Successfully placed 5 queens that protect every tile.\n");
    }
    else
    {
        printf("Failed to place 5 queens that protect every tile.\n");
    }

    printBoard(board);

    destroyBoard(board);

    return 0;
}

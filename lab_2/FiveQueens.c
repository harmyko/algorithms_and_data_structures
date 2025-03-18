#include <stdio.h>
#include <stdlib.h>
#include "FiveQueens.h"

Board *createEmptyBoard()
{
    Board *board = (Board *)malloc(sizeof(Board));

    if (board == NULL)
    {
        return NULL;
    }

    board->tile = (Tile **)malloc(8 * sizeof(Tile *));

    if (board->tile == NULL)
    {
        free(board);
        return NULL;
    }

    for (int i = 0; i < 8; i++)
    {
        board->tile[i] = (Tile *)malloc(8 * sizeof(Tile));

        if (board->tile[i] == NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(board->tile[j]);
            }

            free(board->tile);
            free(board);
            return NULL;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board->tile[i][j].row = i;
            board->tile[i][j].col = j;
            board->tile[i][j].isQueen = 0;
            board->tile[i][j].isSafe = 1;
        }
    }

    return board;
}

void printBoardLegend()
{
    printf( "Q - a queen has been placed on this tile.\n"
        "O - this tile is not being protected by a queen.\n"
        "X - this tile is being protected by a queen.\n\n");
}

void printBoard(Board *board)
{
    printf( "\n");

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board->tile[i][j].isSafe)
            {
                printf(" O ");
            }
            else if (board->tile[i][j].isQueen)
            {
                printf(" Q ");
            }
            else
            {
                printf(" X ");
            }
        }

        printf("\n");
    }

    printf("\n");
}

// Places a queen on the board and marks all protected tile.
void placeQueen(Board *board, int row, int col)
{
    board->tile[row][col].isQueen = 1;

    for (int i = 0; i < 8; i++)
    {
        board->tile[row][i].isSafe = 0;
        board->tile[i][col].isSafe = 0;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
    {
        board->tile[i][j].isSafe = 0;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < 8; --i, ++j)
    {
        board->tile[i][j].isSafe = 0;
    }

    for (int i = row + 1, j = col - 1; i < 8 && j >= 0; ++i, --j)
    {
        board->tile[i][j].isSafe = 0;
    }

    for (int i = row + 1, j = col + 1; i < 8 && j < 8; ++i, ++j)
    {
        board->tile[i][j].isSafe = 0;
    }
}


// Returns 1 if successful, 0 otherwise
int solveFiveQueensCoverage(Board *board)
{
    int queenCount = 0;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board->tile[i][j].isSafe)
            {
                placeQueen(board, i, j);
                ++queenCount;
            }
        }
    }

    return queenCount == 5;
}

// Same as solveFiveQueensCoverage, but in addition prints state of board after each queen placement
int solveFiveQueensCoverageAndPrintState(Board *board)
{
    int queenCount = 0;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board->tile[i][j].isSafe)
            {
                placeQueen(board, i, j);
                ++queenCount;
                printf("A queen has been placed on square i=%d, j=%d", i, j);
                printBoard(board);
            }
        }
    }

    return queenCount == 5;
}

void destroyBoard(Board *board)
{
    if (board == NULL)
    {
        return;
    }

    for (int i = 0; i < 8; ++i)
    {
        free(board->tile[i]);
    }

    free(board->tile);
    free(board);
}
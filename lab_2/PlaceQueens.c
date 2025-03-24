#include <stdio.h>
#include <stdlib.h>
#include "PlaceQueens.h"

Board *createEmptyBoard(int n)
{
    Board *board = (Board *)malloc(sizeof(Board));

    if (board == NULL)
    {
        return NULL;
    }

    board->n = n;
    board->tile = (Tile **)malloc(n * sizeof(Tile *));

    if (board->tile == NULL)
    {
        free(board);
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        board->tile[i] = (Tile *)malloc(n * sizeof(Tile));

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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
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
    printf("X - a queen has been placed on this tile.\n"
           "O - this tile is being protected by a queen.\n\n");
}

void printBoard(Board *board)
{
    printf("\n");
    for (int i = 0; i < board->n; ++i)
    {
        for (int j = 0; j < board->n; ++j)
        {
            if (board->tile[i][j].isQueen)
            {
                printf(" X ");
            }
            else
            {
                printf(" O ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void updateSafety(Board *board, int row, int col, int value)
{
    for (int i = 0; i < board->n; i++)
    {
        board->tile[row][i].isSafe += value;
        board->tile[i][col].isSafe += value;
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
    {
        board->tile[i][j].isSafe += value;
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < board->n; --i, ++j)
    {
        board->tile[i][j].isSafe += value;
    }

    for (int i = row + 1, j = col - 1; i < board->n && j >= 0; ++i, --j)
    {
        board->tile[i][j].isSafe += value;
    }

    for (int i = row + 1, j = col + 1; i < board->n && j < board->n; ++i, ++j)
    {
        board->tile[i][j].isSafe += value;
    }
}

int placeQueens(Board *board, int queensPlaced, int numQueens, int row)
{
    if (queensPlaced == numQueens)
    {
        return 1;
    }

    if (row >= board->n)
    {
        return 0;
    }

    for (int col = 0; col < board->n; col++)
    {
        if (board->tile[row][col].isSafe == 1)
        {
            board->tile[row][col].isQueen = 1;
            updateSafety(board, row, col, -1);

            if (placeQueens(board, queensPlaced + 1, numQueens, row + 1))
            {
                return 1;
            }

            board->tile[row][col].isQueen = 0;
            updateSafety(board, row, col, 1);
        }
    }

    return 0;
}

int solveQueens(Board *board, int numQueens)
{
    return placeQueens(board, 0, numQueens, 0);
}

void destroyBoard(Board *board)
{
    if (board == NULL)
    {
        return;
    }

    for (int i = 0; i < board->n; ++i)
    {
        free(board->tile[i]);
    }

    free(board->tile);
    free(board);
}

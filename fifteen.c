/**
 * fifteen.c
 *
 * CS50 AP
 * Name: Margaret Tanzosh
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

// necessary for usleep
#define _XOPEN_SOURCE 500

// libraries to include
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// globally declared board
int board[DIM_MAX][DIM_MAX];

// globally declared board dimension
int d;

// globally declared variable for blank tile
int empty_row, empty_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);


int main(int argc, string argv[])
{
    // TODO 00: Check for the correct number of arguments
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // TODO 01: Make sure size of board is between 3 x 3 and 9 x 9
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log file to record moves
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // TODO 02: Welcomes the player to the game of fifteen
    greet();

    // TODO 03: Initialize the game board with tiles numbered 1 through n*n-1
    init();

    // Initialize empty tile at botton right
    empty_row = d-1;
    empty_col = d-1;

    // accept moves until game is won
    while (true)
    {
        // TODO 04: Clear the screen
        clear();

        // TODO 05: Prints the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // TODO 06: Check if game is won
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // TODO 07: User inputs which tile to move
        // printf("Tile to move: ");
        int tile = get_int("Tile to move: ");

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // TODO 08: Let user know move is illegal
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // TODO 09: Pause for a moment
        usleep(500000);
    }

    // close log
    fclose(file);

    // TODO 10: All done!
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // Fill up array

    int value = d * d - 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = value;
            value--;
        }
    }
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
                printf("     ");
            else
                printf("%2d   ", board[i][j]);
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // TODO: First search for tile's position
    int tile_row, tile_col;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                tile_row = i;
                tile_col = j;
                break;
            }

        }
    }

    // now switch tile with empty tile if legal move

        if ((tile_row == empty_row) && ((tile_col + 1) == empty_col))
        {
            board[tile_row][tile_col + 1] = tile;
            board[tile_row][tile_col] = 0;
            empty_col = tile_col;
            return true;
        }


        if ((tile_row == empty_row) && ((tile_col - 1) == empty_col))
        {
            board[tile_row][tile_col - 1] = tile;
            board[tile_row][tile_col] = 0;
            empty_col = tile_col;
            return true;
        }

        if ((tile_col == empty_col) && ((tile_row - 1) == empty_row))
        {
            board[tile_row - 1][tile_col] = tile;
            board[tile_row][tile_col] = 0;
            empty_row = tile_row;
            return true;
        }

        if ((tile_col == empty_col) && ((tile_row + 1) == empty_row))
        {
            board[tile_row + 1][tile_col] = tile;
            board[tile_row][tile_col] = 0;
            empty_row = tile_row;
            return true;
        }



        return false;


}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // Check that array in order
    for (int i = 0, check_tile = 0; i < d; i++)
        for (int j = 0; j < d; j++)
        {
            check_tile++;
            if (check_tile == d*d)
                return true;

            if (board[i][j] != check_tile)
                return false;
        }
    return false;
}

#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "display.h"

#define BOARD_LINE_WIDTH 6 //Width of board limits
#define BLOCK_SIZE 16 //Width and Height of each block
#define BOARD_POSITION 320 //Center position of the board
#define BOARD_WIDTH 10 //Board width in blocks
#define BOARD_HEIGHT 20 //Board height in blocks
#define MIN_MARGIN 20 //Minimum margins

class Board
{
    public:

    int get_x_pix_pos (int xPos);
    int get_y_pix_pos (int yPos);
    bool is_space_free (int xPos, int yPos);
    bool movement_possible (int xPos, int yPos, int piece, int rotation);
    void update_board (int xPos, int yPos, int piece, int rotation);
    void delete_lines();
    bool game_over();

    Board(Pieces *livePieces, int inScreenHeight)
    : screenHeight(inScreenHeight), gamePieces(livePieces)
    {
        initialize_board();
    }

    private:
    enum {FREE, FILLED}; //States of board squares (FREE == 0, FILLED == 1)
    int gameBoard[BOARD_WIDTH][BOARD_HEIGHT]; //Actual game board, [x][y] where y=0 is the top of the board
    int screenHeight;
    Pieces *gamePieces;

    void initialize_board();
    void delete_line(int row);
};

/*
Returns an integer value of a given block's x coordinate in pixels.
Parameters:
    - int xPos: The x coordinate (in blocks) of a given block
Output:
    - An integer of the x coordinate converted to pixels
*/
int Board::get_x_pix_pos (int xPos)
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (xPos * BLOCK_SIZE));
}
/*
Returns an integer value of a given block's y coordinate in pixels.
Parameters:
    - int yPos: The y coordinate (in blocks) of a given block
Output:
    - An integer of the y coordinate converted to pixels
*/
int Board::get_y_pix_pos (int yPos)
{
    return ((screenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (yPos * BLOCK_SIZE));
}

/*
Checks a space on the gameboard is unnoccupied;
Parameters:
 - int xPos: The x coordinate of the block to be checked
    - int yPos: The y coordinate of the block to be checked
Output:
    - bool: True if the space is empty, false if the space is occupied.
*/
bool Board::is_space_free (int xPos, int yPos)
{
    if (gameBoard[xPos][yPos] == 0)
    {
        return true;
    }
    else return false;
}

/*
Checks if the movement of a piece is possible by comparing the piece's current location to borders and occupied blocks.
Returns a boolean value to indicate if movement is possible.
Parameters:
    - int xPos:
    - int yPos:
    - int piece:
    - int rotation:
Output:
    - A boolean value, true if movement is possible and there are no conflictions, false if there are conflicts
*/
bool Board::movement_possible(int xPos, int yPos, int piece, int rotation)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int blockType = gamePieces->get_block_type(piece, rotation, i, j);
            if (blockType == 0)
                continue;

            int boardX = xPos + (j - 2); //Really gotta make a variable for the dimensions of each piece array
            int boardY = yPos + (i - 2);

            //Left/right edge
            if (boardX < 0 || boardX >= BOARD_WIDTH)
                return false;

            //Bottom edge
            if (boardY >= BOARD_HEIGHT)
                return false;

            //Above board (ignore, new piece)
            if (boardY < 0)
                continue;

            //Collides with a block already stored on the board
            if (!is_space_free(boardX, boardY))
                return false;
        }
    }
    //No collisions
    return true;
}

//Initialize the board state to all empty squares before the game begins
void Board::initialize_board()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            gameBoard[i][j] = FREE;
        }
    }
}

//Once a piece has been placed, updates the board to reflect the newly filled squares
void Board::update_board(int xPos, int yPos, int piece, int rotation)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int blockType = gamePieces->get_block_type(piece, rotation, i, j);
            if (blockType == 0)
                continue;

            int boardX = xPos + (j - 2);
            int boardY = yPos + (i - 2);

            if (boardX >= 0 && boardX < BOARD_WIDTH && boardY >= 0 && boardY < BOARD_HEIGHT)
                gameBoard[boardX][boardY] = FILLED;
        }
    }
}

//If there is a piece inside the top row, ends the game
//Checks the top row for any not empty spaces
bool Board::game_over()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (gameBoard[i][0] == FILLED) return true;
    }
    return false;
}

//Check the gameboard for full lines - Calls delete_line to remove it if one is found.
void Board::delete_lines()
{
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        bool full = true;
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (gameBoard[j][i] == FREE) { full = false; break; }
        }
        if (full) delete_line(i);
    }
}

//Removes a full row consumed by pieces, then updates the gameboard to move all pieces above the removed row down.
// Parameters:
//  - int row: The row to be removed, determined by delete_lines()

void Board::delete_line(int row)
{
    for (int x = 0; x < BOARD_WIDTH; x++)
        gameBoard[x][row] = FREE;

    for (int y = row; y > 0; y--)
        for (int x = 0; x < BOARD_WIDTH; x++)
            gameBoard[x][y] = gameBoard[x][y - 1];

    for (int x = 0; x < BOARD_WIDTH; x++)
        gameBoard[x][0] = FREE;
}

#endif // BOARD_H
#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"

#define BOARD_LINE_WIDTH 6 //Width of board limits
#define BLOCK_SIZE 16 //Width and Height of each block
#define BOARD_POSITION 320 //Center position of the board
#define BOARD_WIDTH 10 //Board width in blocks
#define BOARD_HEIGHT 20 //Board height in blocks
#define PIECE_BLOCKS 5 //Number of horizontal and vertical blocks of a piece
#define MIN_MARGIN 20 //Minimum margins

class Board
{
    public:
    Board(Pieces *livePieces, int screenHeight);

    int get_x_pos (int pPos);
    int get_y_pos (int pPos);
    bool is_block_free (int xPos, int yPos);
    bool movement_possible (int xPos, int yPos, int piece, int rotation);
    void update_board (int xPos, int yPos, int piece, int rotation);
    void delete_lines();
    bool game_over();

    private:
    enum {FREE, FILLED}; //States of board squares
    int gameBoard[BOARD_WIDTH][BOARD_HEIGHT]; //Actual game board
    Pieces *gamePieces;

    void initialize_board();
    void delete_line();
};

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

void Board::update_board(int xPos, int yPos, int piece, int rotation)
{
    for (int i = 0, xP = 0; i < 5; i++, xP++)
    {
        for (int j = 0, yP = 0; j < 5; j++, yP++)
        {
            if (get_block_type(piece, rotation, xPos, yPos) == 1)
            {
                gameBoard[i][j] == FILLED;
            }
        }
    }
}

void Board::game_over()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (gameBoard[0][i] == FILLED) return true;
    }
    return false;
}

#endif // BOARD_H
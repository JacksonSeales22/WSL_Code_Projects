#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "board.h"
#include "pieces.h"
#include "display.h"
#include <time.h>

#define WAIT_TIME 700 //Time between blocks moving

class Game
{
    public:
        Game (Board *inBoard, Pieces *inPieces, Display *inDisplay, int inScreenHeight)
        {
            gameBoard = inBoard;
            pieces = inPieces;
            display = inDisplay;
            screenHeight = inScreenHeight;
        }

        void start_game();
        void draw_game();
        void create_new_piece();

        //Information about falling piece
        int xPos, yPos;
        int piece, rotation;


    private:
        int screenHeight;
        int nextXPos, nextYPos;
        int nextPiece, nextRotation;
        color blockColor;
        color nextBlockColor;

        Board *gameBoard;
        Pieces *pieces;
        Display *display;

        void draw_piece(int xPos, int yPos, int piece, int rotation);
        void draw_board();
};

void Game::draw_board()
{
    int pX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int pX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int pY  = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    //Left and right "goalposts"
    display->draw_block(pX1 - BOARD_LINE_WIDTH, pY, BOARD_LINE_WIDTH, screenHeight - pY, BLUE);
    display->draw_block(pX2, pY, BOARD_LINE_WIDTH, screenHeight - pY, BLUE);

    pX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (!gameBoard->is_space_free(i, j))
                display->draw_block(pX1 + i * BLOCK_SIZE, pY + j * BLOCK_SIZE,
                                     BLOCK_SIZE - 1, BLOCK_SIZE - 1, RED);
        }
    }
}

void Game::create_new_piece()
{
    //Creating a new piece
    piece = nextPiece;
    rotation = nextRotation;
    xPos = pieces->get_x_initial_pos(piece, rotation);
    yPos = pieces->get_y_initial_pos(piece, rotation);

    //Random next piece
    nextPiece = rand () % (6 - 0 + 1) + 0;
    nextRotation = rand () % (3 - 0 + 1) + 0;
}

void Game::start_game()
{
    //Seeding rand function
    srand ((unsigned int) time(NULL));

    //Creating first piece
    piece = rand () % (6 - 0 + 1) + 0;
    rotation = rand () % (3 - 0 + 1) + 0;
    xPos = pieces->get_x_initial_pos (piece, rotation);
    yPos = pieces->get_y_initial_pos (piece, rotation);

    // Next piece
    nextPiece = rand () % (6 - 0 + 1) + 0;
    nextRotation = rand () % (3 - 0 + 1) + 0;
    nextXPos = BOARD_WIDTH + 5;
    nextYPos = 5;
}

void Game::draw_piece(int xPos, int yPos, int piece, int rotation)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int blockType = pieces->get_block_type(piece, rotation, i, j);
            if (blockType == 0)
                continue;

            //blockColor = (blockType == 2) ? BLUE : GREEN;

            int cellBoardX = xPos + (j - 2);
            int cellBoardY = yPos + (i - 2);

            display->draw_block(gameBoard->get_x_pix_pos(cellBoardX),
                                 gameBoard->get_y_pix_pos(cellBoardY),
                                 BLOCK_SIZE - 1, BLOCK_SIZE - 1, blockColor);
        }
    }
}

void Game::draw_game ()
{
    draw_board (); // Draw the delimitation lines and blocks stored in the board
    draw_piece (xPos, yPos, piece, rotation); // Draw the playing piece
    draw_piece (nextXPos, nextYPos, nextPiece, nextRotation); // Draw the next piece
}

#endif // GAMEPLAY_H
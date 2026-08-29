#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "board.h"
#include "pieces.h"
#include "display.h"
#include <time.h>
#include <cmath>

#define WAIT_TIME 700 //Time between blocks moving
#define MOVE_REPEAT_TIME 125 //ms between repeated moves while a key is held
#define POINTS_PER_ROW 100 //Default score for the number of points awarded per row removed
#define SCORE_MULTIPLIER 1.5 //Multiplier to score for each row removed in a single turn.

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
        color get_color();
        int get_score();
        void add_score(int linesCleared);

        //Information about falling piece
        int xPos, yPos;
        int piece, rotation;


    private:
        int screenHeight;
        int nextXPos, nextYPos;
        int nextPiece, nextRotation;
        int score = 0;
        color blockColor;
        color nextBlockColor;

        Board *gameBoard;
        Pieces *pieces;
        Display *display;

        void draw_piece(int xPos, int yPos, int piece, int rotation);
        void draw_grid();
        void draw_board();
        void draw_score();
};

//Returns the current score of the game
int Game::get_score(){return score;}

//Displays the current game score on the screen
void Game::draw_score()
{
    display->draw_text(BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2)) + 20, 20,
                        "Score: " + std::to_string(score), {255, 255, 255, 255});
}

//Adds the score acquired from the current turn to the previous combined score
//Parameters:
//    - int linesCleared: From delete_lines(), the number of lines removed from the board at the end of a turn
void Game::add_score(int linesCleared)
{
    if (linesCleared > 0)
    {
        if (linesCleared == 1)
        {
            score += POINTS_PER_ROW;
        }
        else if (linesCleared > 1)
        {
            score += POINTS_PER_ROW * (pow(SCORE_MULTIPLIER, linesCleared));
        }
    }
}

//Returns the block color of the current piece
color Game::get_color(){return blockColor;}

//Draws a simple grid around each block on the board to highlight pathing for the pieces
void Game::draw_grid()
{
    int pX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int pY  = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    //Drawing vertical grid lines, one per column
    for (int i = 0; i <= BOARD_WIDTH; i++)
        display->draw_block(pX1 + i * BLOCK_SIZE, pY, 1, BLOCK_SIZE * BOARD_HEIGHT, GRAY);

    //Drawing horizontal grid lines, one per row
    for (int j = 0; j <= BOARD_HEIGHT; j++)
        display->draw_block(pX1, pY + j * BLOCK_SIZE, BLOCK_SIZE * BOARD_WIDTH, 1, GRAY);
}

//Iterates through the given dimensions of a gameboard, (BOARD_WIDTH and BOARD_HEIGHT from board.h)
//Steps:
    // - Determines variables for board positioning
    // - Draws the left and right 'goalposts' that contain the gameboard
    // - Checks each space on the board, if the space is not free draws a block.
void Game::draw_board()
{
    draw_grid();

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
                                     BLOCK_SIZE - 1, BLOCK_SIZE - 1, static_cast<color>(gameBoard->get_content(i, j)));
        }
    }
}

//Generates a new piece to be played as well as the next piece to be played.
void Game::create_new_piece()
{
    //Creating a new piece
    piece = nextPiece;
    rotation = nextRotation;
    xPos = pieces->get_x_initial_pos(piece, rotation);
    yPos = pieces->get_y_initial_pos(piece, rotation);
    blockColor = nextBlockColor;

    //Random next piece
    nextPiece = rand () % (6 - 0 + 1) + 0;
    nextRotation = rand () % (3 - 0 + 1) + 0;
    nextBlockColor = static_cast<color>(rand() % (COLOR_MAX - 4) + 2);
}

//Similar to create_new_piece(), generates the first and second piece, seeding the random function first.
void Game::start_game()
{
    //Seeding rand function
    srand ((unsigned int) time(NULL));

    //Creating first piece
    piece = rand () % (6 - 0 + 1) + 0;
    rotation = rand () % (3 - 0 + 1) + 0;
    xPos = pieces->get_x_initial_pos (piece, rotation);
    yPos = pieces->get_y_initial_pos (piece, rotation);
    blockColor = static_cast<color>(rand() % (COLOR_MAX - 4) + 2);

    // Next piece
    nextPiece = rand () % (6 - 0 + 1) + 0;
    nextRotation = rand () % (3 - 0 + 1) + 0;
    nextXPos = BOARD_WIDTH + 5;
    nextYPos = 5;
    nextBlockColor = static_cast<color>(rand() % (COLOR_MAX - 4) + 2);
}

//Draws the current piece being played by sending all indexes of blocks that the piece is occupying to draw_block
//Parameters:
//    - int xPos: Current x coordinate on the game board of the pivot of the current piece
//    - int yPos: Current y coordinate on the game board of the pivot of the current piece
//    - int piece: Current piece shape (0-6)
//    - int rotation: Current piece rotation (0-3)
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

//Calls all functions required to present the game state to the player
//draw_board - The game boundaries and stored blocks
//draw_piece - For drawing the current piece and the preview of the next piece
//draw_score - For drawing the current score
void Game::draw_game()
{
    draw_board (); //Draw the goalposts and blocks stored in the board
    draw_piece (xPos, yPos, piece, rotation); //Draw the playing piece
    draw_piece (nextXPos, nextYPos, nextPiece, nextRotation); //Draw the next piece
    draw_score(); //Draw the score
}

#endif // GAMEPLAY_H
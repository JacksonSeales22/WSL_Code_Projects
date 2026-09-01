/*

Variable name and commenting conventions:
    - All gameboard squares/blocks will be referred to as 'spaces'
    - All sections of the game pieces will be referred to as 'blocks' before being placed
*/

#include <iostream>
#include <vector>

#include "pieces.h"
#include "board.h"
#include "display.h"
#include "gameplay.h"


int main()
{
    FILE *fptr;

    char fileName[11] = "scores.txt";
    fptr = fopen(fileName, "w");
    //char highScore[12] = "Unavailable"; //Scores are stored as integers, since max int value is 2,147,483,647 size is at least 11.
    int highScore = 0;

    if (fptr == NULL)
    {
        fclose(fptr);
    }
    else
    {
        fscanf(fptr, "%d", &highScore);
    }

    int pieceData[7][4][5][5] ={{
        {//O-piece
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,2,1,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,2,1,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,2,1,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,2,1,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        }},
        {{//I-piece
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,2,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,2,1,1},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,2,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,2,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        }},
        {{//T-piece
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,2,1,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,2,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,2,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,2,1,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        }},
        {{//S-piece
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,2,1,0},
            {0,1,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,0,0,0},
            {0,1,2,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,1,0},
            {0,1,2,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,2,1,0},
            {0,0,0,1,0},
            {0,0,0,0,0}
        }},
        {{//Z-piece
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,2,0,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,1,2,0,0},
            {0,1,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,0,2,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,1,0},
            {0,0,2,1,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        }},
        {{//L-piece
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,2,0,0},
            {0,0,1,1,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,2,1,0},
            {0,1,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,1,0,0},
            {0,0,2,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,1,0},
            {0,1,2,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        }},
        {{//J-piece
            {0,0,0,0,0},
            {0,0,1,0,0},
            {0,0,2,0,0},
            {0,1,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,1,0,0,0},
            {0,1,2,1,0},
            {0,0,0,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,1,1,0},
            {0,0,2,0,0},
            {0,0,1,0,0},
            {0,0,0,0,0}
        },
        {
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,1,2,1,0},
            {0,0,0,1,0},
            {0,0,0,0,0}
        }}};
        int startPositions[7][4][2] = {
        { //o-piece
            {5, -1},
            {5, -1},
            {5, -1},
            {5, -1}
        },
        { //i-piece
            {5, -1},
            {5, 0},
            {5, -2},
            {5, 0}
        }, 
        { //t-piece
            {5, -1},
            {5, -1},
            {5, 0},
            {5, -1}
        }, 
        { //s-piece
            {5, -1},
            {5, -1},
            {5, -1},
            {5, -1}
        }, 
        { //z-piece
            {5, -1},
            {5, -1},
            {5, -1},
            {5, -1}
        }, 
        { //L-piece
            {5, -1},
            {5, -1},
            {5, -1},
            {5, 0}
        }, 
        { //j-piece
            {5, -1},
            {5, 0},
            {5, -1},
            {5, -1}
        }
    };

    Pieces pieces(pieceData, startPositions);

    Display display;
    int screenHeight = display.get_screen_height();

    Board gameBoard(&pieces, screenHeight);

    Game game(&gameBoard, &pieces, &display, screenHeight);

    unsigned long gameTime1 = SDL_GetTicks();
    unsigned long moveTime1 = SDL_GetTicks();
    int piecesSinceSpeedup = 0;

    display.init_window();

    game.start_game();
        
    while (!display.key_press(SDLK_ESCAPE))
    {
        int linesCleared = 0;
        display.clear_screen(); // Clear screen
        game.draw_game(); // Draw staff
        display.update_screen (); // Put the graphic context in the screen

        int key = display.poll_key();

        switch (key)
        {        
        case (SDLK_x):
        {
            // Check collision from up to down
            while (gameBoard.movement_possible(game.xPos, game.yPos, game.piece, game.rotation)) 
            {
                game.yPos++;
            }

            gameBoard.update_board(game.xPos, game.yPos - 1, game.piece, game.rotation, game.get_color());

            linesCleared = gameBoard.delete_lines();
            game.add_score(linesCleared);

            if (gameBoard.game_over())
            {
                display.get_key();
                exit(0);
            }

            game.create_new_piece();
            piecesSinceSpeedup++;

            break;
        }

        case (SDLK_z):
        {
            if (gameBoard.movement_possible (game.xPos, game.yPos, game.piece, (game.rotation + 1) % 4))
            game.rotation = (game.rotation + 1) % 4 ;

            break;
        }
        }

        unsigned long moveTime2 = SDL_GetTicks();
        if ((moveTime2 - moveTime1) > MOVE_REPEAT_TIME)
        {
            if (display.key_press(SDLK_LEFT) &&
                gameBoard.movement_possible(game.xPos - 1, game.yPos, game.piece, game.rotation))
                game.xPos--;

            if (display.key_press(SDLK_RIGHT) &&
                gameBoard.movement_possible(game.xPos + 1, game.yPos, game.piece, game.rotation))
                game.xPos++;

            if (display.key_press(SDLK_DOWN) &&
                gameBoard.movement_possible(game.xPos, game.yPos + 1, game.piece, game.rotation))
                game.yPos++;

            moveTime1 = SDL_GetTicks();
        }

        unsigned long gameTime2 = SDL_GetTicks();

        if (game.currentSpeedup < MAX_SPEEDUP && piecesSinceSpeedup >= TT_SPEEDUP)
        {
            if (game.piecesPlaced % (TT_SPEEDUP * MAX_SPEEDUP) == 0)
            {
                game.currentSpeedup = MAX_SPEEDUP;
            }
            else
            {
                game.currentSpeedup += SPEEDUP;
                //std::cout << "Current Speedup: " << game.currentSpeedup;
            }
        }

        if ((gameTime2 - gameTime1) > (INITIAL_WAIT_TIME - game.currentSpeedup))
        {
            //std::cout << "Current Wait: " << (INITIAL_WAIT_TIME - game.currentSpeedup);
            if (gameBoard.movement_possible (game.xPos, game.yPos + 1, game.piece, game.rotation))
            {
                game.yPos++;
            }
            else
            {
                gameBoard.update_board(game.xPos, game.yPos, game.piece, game.rotation, game.get_color());

                linesCleared = gameBoard.delete_lines();
                game.add_score(linesCleared);

                if (gameBoard.game_over())
                {
                    display.get_key();
                    exit(0);
                }

                game.create_new_piece();
                piecesSinceSpeedup++;
            }

            gameTime1 = SDL_GetTicks();
        }
    }

    if (fptr != NULL)
    {
        if (game.get_score() > highScore)
        {
            //Write to file with new high score
        }
        fclose(fptr);
    }

    return 0;
}
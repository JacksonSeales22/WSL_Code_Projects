/*
File defining the Pieces class, which consists of 4 arrays of 5x5 integers. Each of the 4 arrays is a rotation of the initial piece
The arrays can contain a 0 (no part of the piece is present) a 1 (a non-center piece is present) and 2 (the center of the piece)
The arrays are in the following order: 
    0: Default position
    1: Rotated 90 degrees CW
    2: Rotated 180 degrees CW
    3: Rotated 270 degrees CW
*/

#ifndef PIECES_H
#define PIECES_H

#include <cstring>
#include "display.h"

#define PIECE_WIDTH 5 //Dimensions of the piece array containing block information

class Pieces
{
    public: 
    //Integer array of all piece shapes, rotations, and block types. [Shape][Rotation][Rows][Columns]
    //When referring to indices in a piece array, [y,x] is used to match [Rows][Columns]
    int pieces[7][4][5][5];
    //Integer array of all piece shapes and their starting positions for each rotation. [Shape][Rotation][Indices]
    int startingPositions[7][4][2];

    int get_block_type(int piece, int rotation, int row, int col);
    int get_x_initial_pos(int piece, int rotation);
    int get_y_initial_pos(int piece, int rotation);

    //Constructor
    Pieces(int details[7][4][5][5], int rotations[7][4][2])
    {
        memcpy(pieces, details, sizeof(pieces));
        memcpy(startingPositions, rotations, sizeof(startingPositions));
    }
};

/*
Returns the int value stored in a piece at a certain location.
Parameters:
    - int piece: A value 0-6 that represents the shape of the piece
    - int rotation: A value 0-3 that represents the current rotation of the piece
    - int row: The row chosen from the pieces 4d array, which contains PIECE_WIDTH of columns
    - int col: The column chosen from the pieces 4d array, finalizing the block coordinates

Outputs:
    - An integer 0-2
        - 0: Empty block
        - 1: Piece present
        - 2: Pivot of piece present
*/
int Pieces::get_block_type(int piece, int rotation, int row, int col)
{
    return pieces[piece][rotation][row][col];
}

//Returns the int value of the x coordinate that a piece spawns at
int Pieces::get_x_initial_pos (int piece, int rotation)
{
    return startingPositions[piece][rotation][0];
}

//Returns the int value of the y coordinate that a piece spawns at
int Pieces::get_y_initial_pos (int piece, int rotation)
{
    return startingPositions[piece][rotation][1];
}

#endif // PIECES_H
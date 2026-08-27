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

class Pieces
{
    //Attributes
    std::int piece[4][5][5];
    std::int direction;
    std::int piece_type;

    public: 
    //Methods
    int get_block_type(int xPos, int yPos);

    //Constructor
    Pieces(std::int details[4][5][5], int rotation, int shape)
    {
        piece = details;
        direction = rotation;
        piece_type = shape;
    }

};

int Pieces::get_block_type(int piece, int direction, int x, int y)
{
    return 
}

#endif // PIECES_H
#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>
#include "vec2i.h"

// a pentomino piece is composed of size() cells;

// each cell coordinate is immutable and stored in vector coords_;

// all possible (8) orientations can be represented by three integers cos_, sin_, flip_
// given (immutable) cell with coordinates (x, y) its current coordinates can be calculated as (function Vec2i rotate_wo_offset(Vec2i c))
// (flip_  0) x (cos_  -sin_) x (x)
// (    0  1)   (sin_   cos_)   (y)
// attention, multiplying vector (x, y) by the transformation matrix possibly produces negative coordinates;
// hence we need to compute correct offset vector to make the coordinates non-negative (see Vec2i cell(int i))

class Piece {
private:
    int width_;   // immutable width
    int height_;  // immutable height
    int sin_;     // following three variables encode the transformation of a piece
    int cos_;
    int flip_;
    std::vector<Vec2i> coords_;      // immutable coordinates withing bounds ([0,width_-1], [0,height_-1])

    Vec2i rotate_wo_offset(Vec2i c); // perform the multiplication of the transformation matrix (see the file header) by the vector (c.x, c.y), the outcome possibly contains negative coordinates
public:
    Piece(std::ifstream &in);
    ~Piece();
    int w();           // actual width (taking into account rotations and flip)
    int h();           // actual height
    int size();        // number of cells in the piece
    Vec2i cell(int i); // gives actual coordinates (rotated and flipped) of the cell number i, lies within bounds ([0,w()-1], [0,h()-1])
    void rotate();
    void flip();
};

#endif //__PIECE_H__

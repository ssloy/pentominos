#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>
#include "vec2i.h"

class Piece {
private:
    int width_;
    int height_;
    int sin_;
    int cos_;
    int flip_;
    std::vector<Vec2i> coords;

    Vec2i rotate_wo_offset(Vec2i c);
    Vec2i rotate(Vec2i c);
public:
    Piece(std::ifstream &in);
    ~Piece();
    int w();
    int h();
    void rotate();
    void flip();
    void print();
};

#endif //__PIECE_H__

#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>

struct Couple {
    Couple(int X, int Y) : x(X), y(Y) {}
    int x, y;
};


class Piece {
    private:
        int width_;
        int height_;
        int sin_;
        int cos_;
        int flip_;
        std::vector<Couple> coords;

        Couple rotate_wo_offset(Couple c);
        Couple rotate(Couple c);
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

#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>

struct Couple {
    int x, y;
    Couple(int X, int Y) : x(X), y(Y) {}
    inline Couple operator +(const Couple &v) const { return Couple(x+v.x, y+v.y); }
    inline Couple operator -(const Couple &v) const { return Couple(x-v.x, y-v.y); }
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

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "piece.h"

using namespace std;

Piece::Piece(ifstream &in) : width_(0), height_(0), sin_(0), cos_(1), flip_(1) {
    string line;
    while (!in.eof()) {
        getline(in, line);
        size_t occ = line.find_last_of('#');
        if (!line.length() || string::npos==occ) break;
        width_ = max(width_, (int)occ+1);
        for (int i=0; i<(int)line.length(); i++) {
            if (line[i]=='#') coords.push_back(Vec2i(i, height_));
        }
        height_++;
    }
}

Piece::~Piece() {
}

int Piece::size() {
    return (int)coords.size();
}

Vec2i Piece::cell(int i) {
    return rotate(coords[i]);
}

int Piece::w() {
    Vec2i tmp = rotate_wo_offset(Vec2i(width_, height_));
    return abs(tmp.x);
}

int Piece::h() {
    Vec2i tmp = rotate_wo_offset(Vec2i(width_, height_));
    return abs(tmp.y);
}

void Piece::rotate() {
    int tmp = cos_;
    cos_ = -sin_;
    sin_ = tmp;
}

void Piece::flip() {
    flip_ = -flip_;
}

Vec2i Piece::rotate_wo_offset(Vec2i c) {
// cout << "(" << flip_ << " " << 0 << ") x ( " << cos_ << "  " << -sin_ << ")" << endl;
// cout << "(" <<     0 << " " << 1 << ")   ( " << sin_ << "  " <<  cos_ << ")" << endl;
   return Vec2i(flip_*cos_*c.x - flip_*sin_*c.y, sin_*c.x + cos_*c.y);
}

Vec2i Piece::rotate(Vec2i c) {
    Vec2i offset = rotate_wo_offset(Vec2i(width_-1, height_-1));
    offset = Vec2i(max(0, -offset.x), max(0, -offset.y));
    Vec2i pt = rotate_wo_offset(c);
    return pt+offset;
}


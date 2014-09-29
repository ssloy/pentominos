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
            if (line[i]=='#') coords_.push_back(Vec2i(i, height_));
        }
        height_++;
    }
}

Piece::~Piece() {
}

int Piece::size() {
    return (int)coords_.size();
}

Vec2i Piece::cell(int i) {
    Vec2i offset = rotate_wo_offset(Vec2i(width_-1, height_-1));
    offset = Vec2i(max(0, -offset.x), max(0, -offset.y));
    return rotate_wo_offset(coords_[i]) + offset;
}

int Piece::w() {
    return abs(rotate_wo_offset(Vec2i(width_, height_)).x);
}

int Piece::h() {
    return abs(rotate_wo_offset(Vec2i(width_, height_)).y);
}

// TODO: need to fix the rotation direction that depends on the flip_
void Piece::rotate() {
    int tmp =  cos_;
    cos_    = -sin_;
    sin_    =  tmp;
}

void Piece::flip() {
    flip_ = -flip_;
}

Vec2i Piece::rotate_wo_offset(Vec2i c) {
  return Vec2i(flip_*cos_*c.x - flip_*sin_*c.y, sin_*c.x + cos_*c.y);
}


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
            if (line[i]=='#') coords.push_back(Couple(i, height_));
        }
        height_++;
    }
}

Piece::~Piece() {
}

int Piece::w() {
    Couple tmp = rotate_wo_offset(Couple(width_, height_));
    return abs(tmp.x);
}

int Piece::h() {
    Couple tmp = rotate_wo_offset(Couple(width_, height_));
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

Couple Piece::rotate_wo_offset(Couple c) {
// cout << "(" << flip_ << " " << 0 << ") x ( " << cos_ << "  " << -sin_ << ")" << endl;
// cout << "(" <<     0 << " " << 1 << ")   ( " << sin_ << "  " <<  cos_ << ")" << endl;
   return Couple(flip_*cos_*c.x - flip_*sin_*c.y, sin_*c.x + cos_*c.y);
}

Couple Piece::rotate(Couple c) {
    Couple tmp = rotate_wo_offset(Couple(width_-1, height_-1));
    tmp.x = max(0, -tmp.x);
    tmp.y = max(0, -tmp.y);
    Couple pt = rotate_wo_offset(c);
    return Couple(pt.x+tmp.x, pt.y+tmp.y);
}

void Piece::print() {
    char *p = new char[width_*height_];
    for (int i=0; i<width_*height_; i++) {
        p[i] = ' ';
    }

    for (int i=0; i<(int)coords.size(); i++) {
        Couple pt = rotate(coords[i]);
        p[pt.x + pt.y*w()] = '#';
    }
    for (int j=0; j<h(); j++) {
        for (int i=0; i<w(); i++) {
            cout << p[i+j*w()];
        }
        cout << endl;
    }

    delete [] p;
}


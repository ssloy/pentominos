#include <SDL/SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "piece.h"
#include "collection.h"

using namespace std;

Collection::Collection(string filename) : pieces_(vector<SDLPiece>()), maxz_(-1) {
    srand(1);
    ifstream in;
    in.open(filename.c_str(), ifstream::in);
    if (in.fail()) {
        cerr << "can't open file " << filename << endl;
        return;
    }
    while (!in.eof()) {
        SDLPiece p = SDLPiece(++maxz_, Vec2i(rand()%100, rand()%100), in);
        if (p.w() && p.h()) {
            pieces_.push_back(p);
        }
    }
    in.close();
}

void Collection::sort() {
    for (int i=0; i<int(pieces_.size()); i++) {
        for (int j=0; j<int(pieces_.size())-1; j++) {
            if (pieces_[j].z<=pieces_[j+1].z) continue;
            swap(pieces_[j], pieces_[j+1]);
        }
    }
}

void Collection::render(SDL_Surface *screen) {
    for (int i=0; i<(int)pieces_.size(); i++) {
        for (int j=0; j<(int)pieces_[i].size(); j++) {
            Vec2i pt = pieces_[i].pos + pieces_[i].cell(j)*square_size;
            SDL_Rect tmp;
            tmp.w = tmp.h = square_size-1;
            tmp.x = pt.x;
            tmp.y = pt.y;
            SDL_FillRect(screen, &tmp, SDL_MapRGB(screen->format, pieces_[i].rgb[0], pieces_[i].rgb[1], pieces_[i].rgb[2]));
        }
    }
}

bool Collection::popup(Vec2i p) {
    int idx = -1;
    for (int i=int(pieces_.size())-1; -1==idx && i>0; i--) { // >0 forbids popping up the board
        for (int c=0; -1==idx && c<(int)pieces_[i].size(); c++) {
            Vec2i cell = pieces_[i].pos + pieces_[i].cell(c)*square_size;
            if (p>=cell && p<cell+Vec2i(square_size, square_size)) {
                idx = i;
            }
        }
    }
    if (idx>=0) {
        pieces_[idx].z = ++maxz_;
        sort();
    }
    return idx!=-1;
}

SDLPiece &Collection::topmost() {
    return pieces_.back();
}


#include <SDL/SDL.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include "piece.h"
#include "collection.h"

using namespace std;

Collection::Collection(string filename) : pieces(vector<Piece>()), z(vector<int>()), pos(vector<Vec2i>()), maxz(-1) {
    ifstream in;
    in.open(filename.c_str(), ifstream::in);
    if (in.fail()) {
        cerr << "can't open file " << filename << endl;
        return;
    }
    while (!in.eof()) {
        Piece p = Piece(in);
        if (p.w() && p.h()) {
            pieces.push_back(p);
            z.push_back(++maxz);
            pos.push_back(Vec2i(rand()%100, rand()%100));
        }
    }
    in.close();
}

void Collection::sort() {
    for (int i=0; i<int(z.size()); i++) {
        for (int j=0; j<int(z.size())-1; j++) {
            if (z[j]<=z[j+1]) continue;
            swap(z[j], z[j+1]);
            swap(pieces[j], pieces[j+1]);
            swap(pos[j], pos[j+1]);
        }
    }
}

void Collection::render(SDL_Surface *screen) {
    srand(3);
    for (int i=0; i<(int)z.size(); i++) {
        int r = rand()%255;
        int g = rand()%255;
        int b = rand()%255;
        for (int j=0; j<(int)pieces[i].size(); j++) {
            Vec2i pt = pos[i] + pieces[i].cell(j)*square_size;
            SDL_Rect tmp;
            tmp.w = tmp.h = square_size-1;
            tmp.x = pt.x;
            tmp.y = pt.y;
            SDL_FillRect(screen, &tmp, SDL_MapRGB(screen->format, r, g, b));
        }
    }
}

bool Collection::popup(Vec2i p) {
    int idx = -1;
    for (int i=int(z.size())-1; -1==idx && i>0; i--) { // >0 not to click the board
        for (int c=0; -1==idx && c<(int)pieces[i].size(); c++) {
            Vec2i cell = pos[i] + pieces[i].cell(c)*square_size;
            if (p>=cell && p<cell+Vec2i(square_size, square_size)) {
                idx = i;
            }
        }
    }
    if (idx>=0) {
        z[idx] = ++maxz;
        sort();
    }
    return idx!=-1;
}



#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <vector>
#include <string>
#include "piece.h"
#include "vec2i.h"

const int square_size = 32;

struct Collection {
    Collection(std::string filename);
    void render(SDL_Surface *screen);
    void sort();
    bool popup(Vec2i p);  // floats the piece to the top
    void topmost_move(Vec2i dxdy);

    std::vector<Piece> pieces;
    std::vector<int> z;
    std::vector<Vec2i> pos;
    int maxz;
};

#endif //__COLLECTION_H__

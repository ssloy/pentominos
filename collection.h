#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include <vector>
#include <string>
#include "piece.h"
#include "vec2i.h"
#include <cstdlib>

const int square_size = 32;
const int colors[] = {127, 127, 127, 255,127,80, 127,255,0, 153,0,255, 218,165,32, 139,69,19, 19,89,139, 173,216,230, 255,99,71, 204,31,0, 30,255,254, 143,188,143, 188,143,188, 153,204,153, 30,144,255};

// standard piece augmented with color, z index in the sdl window, position
struct SDLPiece : Piece {
    SDLPiece(int Z, Vec2i P, std::ifstream &in) : Piece(in), z(Z), pos(P) {
        int ncolors = sizeof(colors)/(sizeof(int)*3);
        int offset = Z%ncolors*3;
        for (int i=0; i<3; i++) rgb[i] = colors[i+offset];
    }
    int z;
    Vec2i pos;
    int rgb[3];
};


// collection of sdl pieces:
//   a) grants access to the topmost piece
//   b) capable of popping a piece we click on to the top
// it is ugly, TODO : get rid of sort() and stuff

class Collection {
public:
    Collection(std::string filename);
    SDLPiece &topmost();
    void render(SDL_Surface *screen);
    bool popup(Vec2i p);  // floats the piece to the top

private:
    void sort();

    std::vector<SDLPiece> pieces_;
    int maxz_;
};

#endif //__COLLECTION_H__

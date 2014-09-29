#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>
#include <string>

#include "collection.h"
#include "vec2i.h"

class Game {
public:
    Game(std::string filename);
    bool init_sdl(const char* title, int width, int height, int bpp);
    void handle_events();
    void draw();
    void clean();
    bool running();
private:
    SDL_Surface* sdl_screen_;
    bool running_;
    int width_;
    int height_;
    int bpp_;

    Collection collection_;
    Vec2i grab_pt_;
    int grab_;
};

#endif


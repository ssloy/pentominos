#ifndef _GAME_H_
#define _GAME_H_

#include <SDL/SDL.h>

class Game {
public:
    Game();
    bool init(const char* title, int width, int height, int bpp);
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

    int x_;
    int y_;
    int grab_x_;
    int grab_y_;
    int grab_;
};

#endif


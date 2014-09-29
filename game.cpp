#include <SDL/SDL.h>
#include <iostream>
#include <string>
#include "game.h"
#include "vec2i.h"

Game::Game(std::string filename) : running_(false), collection_(filename) {
}

bool Game::init_sdl(const char* title, int width, int height, int bpp) {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        std::cerr << "SDL_Init failed, SDL_GetError()=" << SDL_GetError() << std::endl;
        return false;
    }
    SDL_WM_SetCaption(title, NULL);
    sdl_screen_ = SDL_SetVideoMode(width, height, bpp, 0);
    if (!sdl_screen_) {
        std::cerr << "SDL_SetVideoMode failed, SDL_GetError()=" << SDL_GetError() << std::endl;
        return false;
    }
    running_ = true;
    width_ = width;
    height_ = height;
    bpp_ = bpp;

    grab_ = -1;
    grab_pt_ = Vec2i(0,0);
    return true;
}

bool Game::running() {
    return running_;
}

void Game::handle_events() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        running_ = !(SDL_QUIT==event.type || (SDL_KEYDOWN==event.type && SDLK_ESCAPE==event.key.keysym.sym));
         if (SDL_MOUSEBUTTONDOWN==event.type && SDL_BUTTON_LEFT==event.button.button) {
            Vec2i p = Vec2i(event.button.x, event.button.y);
            if (collection_.popup(p)) {
                grab_ = 1;
                grab_pt_ = p;
            }
         }
         if (SDL_MOUSEBUTTONUP==event.type && SDL_BUTTON_LEFT==event.button.button) {
            grab_ = -1;
         }
         if (event.type == SDL_MOUSEMOTION && grab_>=0) {
            Vec2i p = Vec2i(event.motion.x, event.motion.y);
            collection_.topmost_move(p-grab_pt_);
            grab_pt_ = p;
         }
    }
}

void Game::draw() {
    SDL_FillRect(sdl_screen_, NULL, SDL_MapRGB(sdl_screen_->format, 255, 255, 255));
    collection_.render(sdl_screen_);
    SDL_Flip(sdl_screen_);
}

void Game::clean() {
    if (sdl_screen_) SDL_FreeSurface(sdl_screen_);
    SDL_Quit();
}


#include <iostream>
#include "game.h"

Game::Game() : running_(false) {
}

bool Game::init(const char* title, int width, int height, int bpp) {
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
    x_ = 128;
    y_ = 128;
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
            int x = event.button.x;
            int y = event.button.y;
            if (x>=x_ && x<x_+64 && y>=y_ && y<y_+64) {
                grab_ = 1;
                grab_x_ = x;
                grab_y_ = y;
            }
         }
         if (SDL_MOUSEBUTTONUP==event.type && SDL_BUTTON_LEFT==event.button.button) {
            grab_ = -1;
         }
         if ( event.type == SDL_MOUSEMOTION && grab_>=0) {
            x_ += event.motion.x-grab_x_;
            y_ += event.motion.y-grab_y_;
            grab_x_ = event.motion.x;
            grab_y_ = event.motion.y;
         }
    }
}

void Game::draw() {
    SDL_FillRect(sdl_screen_, NULL, SDL_MapRGB(sdl_screen_->format, 255, 255, 255));
    SDL_Rect tmp;
    tmp.w = 64;
    tmp.h = 64;
    tmp.x = x_;
    tmp.y = y_;
    SDL_FillRect(sdl_screen_, &tmp, SDL_MapRGB(sdl_screen_->format, 255, 0, 0));

    SDL_Flip(sdl_screen_);
}

void Game::clean() {
    if (sdl_screen_) SDL_FreeSurface(sdl_screen_);
    SDL_Quit();
}


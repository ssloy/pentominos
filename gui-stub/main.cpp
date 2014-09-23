#include "game.h"

int main(int argc, char* args[]) {
    Game game;
    game.init("Pentominos stub", 640, 480, 32);
    while (game.running()) {
        game.handle_events();
        game.draw();
    }
    game.clean();
    return 0;
}


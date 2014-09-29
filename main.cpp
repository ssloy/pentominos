#include <string>
#include "game.h"

int main(int argc, char* args[]) {
    std::string filename = std::string(2==argc ? args[1] : "pentomino.txt");
    Game game(filename);
    game.init_sdl("Pentominos stub", 640, 480, 32);
    while (game.running()) {
        game.handle_events();
        game.draw();
    }
    game.clean();
    return 0;
}


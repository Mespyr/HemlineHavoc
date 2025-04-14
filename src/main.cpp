#include <ostream>

#include "util.hpp"
#include "window/window.hpp"

int main() {
    std::ostream& log = std::cerr;

    if (!init_lib(log)) exit(1);

    Window window(log, "Hemline Havoc", 1280, 720);
    if (!window) exit(1);

    std::shared_ptr<SDL_Texture> tree = window.load_texture("tree.png");

    do {
        window.handle_events();
        window.begin_drawing();

        window.draw_texture(tree, 10, 10);

        window.end_drawing();
        window.render();
    } while (window);

    SDL_Quit();
    return 0;
}

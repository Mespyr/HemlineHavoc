#include <algorithm>
#include <ostream>

#include "util.hpp"
#include "window/window.hpp"

int main() {
    std::ostream& log = std::cerr;

    if (!init_lib(log)) exit(1);

    Window window("Hemline Havoc", log, 1280, 720);
    if (!window) exit(1);

    // texture from a file
    Texture tree = window.create_texture("tree.png");
    // create texture
    uint32_t* pixels =
        static_cast<uint32_t*>(malloc(20 * 20 * sizeof(uint32_t)));
    std::fill(pixels, pixels + (20 * 20), 0x320ac8FF);
    Texture block = window.create_texture(pixels, 20, 20);
    free(pixels);

    do {
        window.handle_events();
        window.begin_render();
        window.draw_texture(tree, {160, 90}, 100, 100,
                            {0, 0, tree.get_width(), tree.get_height()});
        window.draw_texture(block, {-10, 20}, 20, 20,
                            {0, 0, block.get_width(), block.get_height()});

        window.end_render();
    } while (window);

    SDL_Quit();
    return 0;
}

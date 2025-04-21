#include "window.hpp"

Window::Window(const std::string& name, std::ostream& log, uint32_t width,
               uint32_t height)
    : name(name), log(log), WINDOW_WIDTH(width), WINDOW_HEIGHT(height) {
    create_window_and_renderer();
    create_scanline_texture();
}

void Window::update_events() {
    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_EVENT_QUIT) quit = true;
}

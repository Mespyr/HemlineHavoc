#include "window.hpp"

void Window::clear() {
    SDL_SetRenderDrawColor(renderer.get(), 20, 20, 20, 255);
    SDL_RenderClear(renderer.get());
}

void Window::render() {
    SDL_RenderTexture(renderer.get(), scanline_texture.get(), nullptr, nullptr);
    SDL_RenderPresent(renderer.get());
}

void Window::draw_texture(Texture &texture, SDL_FPoint position, float width,
                          float height, SDL_FRect src_rect) {
    SDL_FRect dest_rect = {position.x, position.y, width, height};
    SDL_RenderTexture(renderer.get(), texture.get_ptr(), &src_rect, &dest_rect);
}

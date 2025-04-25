#include "window.hpp"

void Window::clear() {
    SDL_SetRenderDrawColor(renderer.get(), 20, 20, 20, 255);
    SDL_RenderClear(renderer.get());
}

void Window::render() {
    SDL_RenderTexture(renderer.get(), scanline_texture.get(), nullptr, nullptr);
    SDL_RenderPresent(renderer.get());
}

void Window::draw_texture(Texture &texture, SDL_FRect dest_rect,
                          SDL_FRect src_rect, SDL_FlipMode flip) {
    SDL_RenderTextureRotated(renderer.get(), texture.get_ptr(), &src_rect, &dest_rect, 0, nullptr, flip);
}

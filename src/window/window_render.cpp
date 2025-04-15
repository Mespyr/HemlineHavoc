#include "window.hpp"

void Window::begin_render() {
    // set the target to the game_texture so
    // that everything drawn is put on it
    SDL_SetRenderTarget(renderer.get(), game_texture.get());
    SDL_SetRenderDrawColor(renderer.get(), 14, 14, 14, 255);
    SDL_RenderClear(renderer.get());
}

void Window::end_render() {
    // go back to rendering directly to the window
    SDL_SetRenderTarget(renderer.get(), nullptr);
    SDL_RenderClear(renderer.get());
    SDL_RenderTexture(renderer.get(), game_texture.get(), nullptr, nullptr);
    SDL_RenderTexture(renderer.get(), scanline_texture.get(), nullptr, nullptr);
    SDL_RenderPresent(renderer.get());
}

void Window::draw_texture(Texture &texture, SDL_FPoint position, float width,
                          float height, SDL_FRect src_rect) {
    SDL_FRect dest_rect = {position.x, position.y, width, height};
    SDL_RenderTexture(renderer.get(), texture.get_ptr(), &src_rect, &dest_rect);
}

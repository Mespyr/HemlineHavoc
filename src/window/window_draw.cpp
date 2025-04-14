#include "window.hpp"

std::shared_ptr<SDL_Texture> Window::load_texture(
    const std::string& file_path) {
    SDL_Texture* texture_ptr =
        IMG_LoadTexture(renderer.get(), file_path.c_str());
    if (texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        quit = true;
    }
    std::shared_ptr<SDL_Texture> texture(texture_ptr, SDL_Deleter());
    SDL_SetTextureScaleMode(game_texture.get(), SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(game_texture.get(), SDL_BLENDMODE_BLEND);
    return texture;
}

void Window::draw_texture(std::shared_ptr<SDL_Texture> texture, uint32_t x,
                          uint32_t y) {
    SDL_FRect destRect{static_cast<float>(x), static_cast<float>(y), 100, 100};
    SDL_RenderTexture(renderer.get(), texture.get(), NULL, &destRect);
}

void Window::begin_drawing() {
    SDL_SetRenderTarget(renderer.get(), game_texture.get());
    SDL_SetRenderDrawColor(renderer.get(), 14, 14, 14, 255);
    SDL_RenderClear(renderer.get());
}

void Window::end_drawing() { SDL_SetRenderTarget(renderer.get(), NULL); }

void Window::render() {
    SDL_RenderClear(renderer.get());
    SDL_RenderTexture(renderer.get(), game_texture.get(), NULL, NULL);
    SDL_RenderTexture(renderer.get(), scanline_texture.get(), NULL, NULL);
    SDL_RenderPresent(renderer.get());
}

#include "texture.hpp"

Texture::Texture(SDL_Texture* tex, float width, float height)
    : width(width), height(height) {
    texture = std::unique_ptr<SDL_Texture, SDL_Deleter>(tex);
}

SDL_Texture* Texture::get_ptr() { return texture.get(); }
float        Texture::get_width() { return width; }
float        Texture::get_height() { return height; }

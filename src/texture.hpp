#pragma once

#include <SDL3/SDL.h>

#include <memory>
#include <string>

#include "util.hpp"

class Texture {
  public:
    Texture(SDL_Texture* tex, float width, float height)
        : texture(tex), width(width), height(height) {}

    SDL_Texture* get_ptr() { return texture.get(); }
    float        get_width() { return width; }
    float        get_height() { return height; }

  private:
    std::unique_ptr<SDL_Texture, SDL_Deleter> texture;
    const float                               width, height;
};

#pragma once

#include <SDL3/SDL.h>

#include <memory>
#include <string>

#include "util.hpp"

class Texture {
  public:
    Texture(SDL_Texture* tex, float width, float height);

    SDL_Texture* get_ptr();
    float        get_width();
    float        get_height();

  private:
    std::unique_ptr<SDL_Texture, SDL_Deleter> texture;
    const float                               width, height;
};

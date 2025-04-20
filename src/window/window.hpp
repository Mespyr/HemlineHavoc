#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>

#include "../texture.hpp"
#include "../util.hpp"

class Window {
  public:
    Window(const std::string& name, std::ostream& log, uint32_t width,
           uint32_t height);

    explicit operator bool() const { return !quit; }

    void handle_events();

    Texture create_texture(const std::string& file_path);
    Texture create_texture(const uint32_t* pixels, float width, float height);

    void clear();
    void render();

    void draw_texture(Texture& texture, SDL_FRect dest_rect,
                      SDL_FRect src_rect);

  private:
    bool               quit = false;  // whether to close window or not
    const std::string& name;          // window name
    std::ostream&      log;           // where to write errors to

    // window resolution
    const uint32_t WINDOW_WIDTH, WINDOW_HEIGHT;
    // native game resolution (for upscaling)
    static const uint32_t GAME_WIDTH = 640, GAME_HEIGHT = 360;

    // SDL behind the scenes
    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  scanline_texture;

    void create_window_and_renderer();
    void create_scanline_texture();
};

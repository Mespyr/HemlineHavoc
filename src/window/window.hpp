#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <string>

#include "../util.hpp"

class Window {
  public:
    Window(std::ostream& log, const std::string& name, uint32_t width,
           uint32_t height);

    explicit operator bool() const { return !quit; }

    // textures
    std::shared_ptr<SDL_Texture> load_texture(const std::string& file_path);
    void draw_texture(std::shared_ptr<SDL_Texture> texture, uint32_t x,
                      uint32_t y);

    void handle_events();
    void begin_drawing();
    void end_drawing();
    void render();

  private:
    bool               quit = false;
    const std::string& name;
    const uint32_t     WINDOW_WIDTH, WINDOW_HEIGHT;
    std::ostream&      log;

    // native game resolution
    static const uint32_t GAME_WIDTH = 320, GAME_HEIGHT = 180;

    // SDL behind the scenes
    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  game_texture;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  scanline_texture;

    bool create_window();
    bool create_renderer();
    bool create_game_texture();
    bool create_scanline_texture();
};

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

    void begin_render();
    void end_render();

    void draw_texture(Texture& texture, SDL_FPoint position, float width,
                      float height, SDL_FRect source);

  private:
    bool               quit = false;  // whether to close window or not
    const std::string& name;          // window name
    std::ostream&      log;           // where to write errors to

    // window resolution
    const uint32_t WINDOW_WIDTH, WINDOW_HEIGHT;
    // native game resolution
    static const uint32_t GAME_WIDTH = 320, GAME_HEIGHT = 180;

    // SDL behind the scenes
    std::unique_ptr<SDL_Window, SDL_Deleter>   window;
    std::unique_ptr<SDL_Renderer, SDL_Deleter> renderer;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  game_texture;
    std::unique_ptr<SDL_Texture, SDL_Deleter>  scanline_texture;

    void create_window();
    void create_renderer();
    void create_game_texture();
    void create_scanline_texture();
};

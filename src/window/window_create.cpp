#include "window.hpp"

void Window::create_window() {
    window = std::unique_ptr<SDL_Window, SDL_Deleter>(
        SDL_CreateWindow(name.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT, 0),
        SDL_Deleter());
    if (window == nullptr) {
        log_sdl_error(log, "SDL_CreateWindow");
        quit = true;
    }
}

void Window::create_renderer() {
    renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>(
        SDL_CreateRenderer(window.get(), nullptr), SDL_Deleter());
    if (renderer == nullptr) {
        log_sdl_error(log, "SDL_CreateRenderer");
        quit = true;
        return;
    }
    // turn on vsync
    SDL_SetRenderVSync(renderer.get(), SDL_RENDERER_VSYNC_ADAPTIVE);
    // renderer settings
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
}

void Window::create_game_texture() {
    // create the games's texture at native resolution
    // using TEXTUREACCESS_TARGET to use renderer to draw
    SDL_Texture* game_texture_ptr =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);
    if (game_texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        quit = true;
        return;
    }
    game_texture = std::unique_ptr<SDL_Texture, SDL_Deleter>(game_texture_ptr,
                                                             SDL_Deleter());
    // game texture settings
    SDL_SetTextureScaleMode(game_texture.get(), SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(game_texture.get(), SDL_BLENDMODE_BLEND);
}

void Window::create_scanline_texture() {
    // create the scanline effect in a texture
    // using TEXTUREACCESS_TARGET to draw using the renderer
    SDL_Texture* scanline_texture_ptr =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_TARGET, GAME_WIDTH, GAME_HEIGHT);
    if (scanline_texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        quit = true;
        return;
    }
    scanline_texture = std::unique_ptr<SDL_Texture, SDL_Deleter>(
        scanline_texture_ptr, SDL_Deleter());

    // scanline texture settings
    SDL_SetTextureScaleMode(scanline_texture.get(), SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(scanline_texture.get(), SDL_BLENDMODE_BLEND);

    // draw scanlines onto the texture using the renderer
    SDL_SetRenderTarget(renderer.get(), scanline_texture.get());
    SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderFillRect(renderer.get(), nullptr);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0x33);
    for (uint32_t i = 0; i < GAME_HEIGHT; i += 2)
        SDL_RenderLine(renderer.get(), 0, i, GAME_WIDTH, i);
    // reset renderer target, now ready to draw frames
    SDL_SetRenderTarget(renderer.get(), nullptr);
}

Texture Window::create_texture(const std::string& file_path) {
    SDL_Texture* texture_ptr =
        IMG_LoadTexture(renderer.get(), file_path.c_str());
    if (texture_ptr == nullptr) {
        log_sdl_error(log, "SDL_CreateTexture");
        quit = true;
    }
    // necessary modes
    SDL_SetTextureScaleMode(texture_ptr, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(texture_ptr, SDL_BLENDMODE_BLEND);
    // get width and height
    float width, height;
    SDL_GetTextureSize(texture_ptr, &width, &height);
    return Texture(texture_ptr, width, height);
}

Texture Window::create_texture(const uint32_t* pixels, float width,
                               float height) {
    SDL_Texture* texture_ptr =
        SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_UpdateTexture(texture_ptr, nullptr, pixels, sizeof(uint32_t));
    // necessary modes
    SDL_SetTextureScaleMode(texture_ptr, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(texture_ptr, SDL_BLENDMODE_BLEND);
    return Texture(texture_ptr, width, height);
}

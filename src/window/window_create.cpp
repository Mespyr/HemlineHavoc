#include "window.hpp"

void Window::create_window_and_renderer() {
    SDL_Window*   window_ptr = nullptr;
    SDL_Renderer* renderer_ptr = nullptr;
    if (!SDL_CreateWindowAndRenderer(name.c_str(), WINDOW_WIDTH, WINDOW_HEIGHT,
                                     0, &window_ptr, &renderer_ptr)) {
        log_sdl_error(log, "SDL_CreateWindowAndRenderer");
        quit = true;
        return;
    }
    // renderer settings
    SDL_SetRenderVSync(renderer_ptr, SDL_RENDERER_VSYNC_ADAPTIVE);
    SDL_SetRenderDrawBlendMode(renderer_ptr, SDL_BLENDMODE_BLEND);
    SDL_SetRenderLogicalPresentation(renderer_ptr, GAME_WIDTH, GAME_HEIGHT,
                                     SDL_LOGICAL_PRESENTATION_LETTERBOX);
    // save to class
    window =
        std::unique_ptr<SDL_Window, SDL_Deleter>(window_ptr, SDL_Deleter());
    renderer =
        std::unique_ptr<SDL_Renderer, SDL_Deleter>(renderer_ptr, SDL_Deleter());
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

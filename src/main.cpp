#include <ostream>

#include "util.hpp"
#include "window/window.hpp"

int main() {
    std::ostream& log = std::cerr;

    if (!init_lib(log)) exit(1);

    Window window("Hemline Havoc", log, 1920, 1080);
    if (!window) exit(1);

    // texture from a file
    Texture logo = window.create_texture("assets/logo.png");
	Texture pants = window.create_texture("assets/pants.png");

    // create texture
    // uint32_t* pixels =
    //     static_cast<uint32_t*>(malloc(20 * 20 * sizeof(uint32_t)));
    // std::fill(pixels, pixels + (20 * 20), 0x320ac8FF);
    // Texture block = window.create_texture(pixels, 20, 20);
    // free(pixels);

    SDL_FRect pos = {320-16, 180-16, 32, 32};
    SDL_FRect src = {0, 0, 32, 32};
	double animation_diff = 0.0;

    uint64_t NOW = SDL_GetPerformanceCounter();
    uint64_t LAST = 0;
    double   delta_time = 0;

    const bool *kbd_state = SDL_GetKeyboardState(NULL);

    do {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        delta_time = static_cast<double>(
            ((NOW - LAST) * 1000) /
            static_cast<double>(SDL_GetPerformanceFrequency()));

        window.update_events();

		if (kbd_state[SDL_SCANCODE_W])
			pos.y -= 0.05 * delta_time;
		if (kbd_state[SDL_SCANCODE_S])
			pos.y += 0.05 * delta_time;
		if (kbd_state[SDL_SCANCODE_A])
			pos.x -= 0.05 * delta_time;
		if (kbd_state[SDL_SCANCODE_D])
			pos.x += 0.05 * delta_time;

        window.clear();
        window.draw_texture(logo, {10.0, 10.0, 240.0, 135.0},
                            {0, 0, logo.get_width(), logo.get_height()});

		// animate
        window.draw_texture(pants, pos, src, SDL_FLIP_NONE);
		animation_diff += delta_time;
		if (animation_diff > 200.0) {
			animation_diff = 0.0;
			if (src.x != 288) src.x += 32;
			else src.x = 0;
		}

        window.render();
    } while (window);

    SDL_Quit();
    return 0;
}

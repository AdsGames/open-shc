#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "core/asset_manager.h"
#include "core/core.h"

int main(int argc, char **argv)
{
    oshc::core::init();
    oshc::core::asset_manager.init("assets/config/assets.json");

    std::cout << "Hello World!" << std::endl;

    oshc::core::asset_manager.get_music("a_pane_in_the_glass").play();

    for (int i = 0; i < 100; i++)
    {
        SDL_RenderClear(oshc::core::renderer);
        SDL_RenderCopy(oshc::core::renderer, oshc::core::asset_manager.get_texture("frontend_loading").get().get(),
                       nullptr, nullptr);
        SDL_RenderPresent(oshc::core::renderer);
        SDL_Delay(100);
    }

    return 0;
}
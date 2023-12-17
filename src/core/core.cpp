#include "core.h"

#include <SDL2/SDL_mixer.h>

namespace oshc::core
{
SDL_Renderer *renderer = nullptr;

SDL_Window *window = nullptr;

oshc::core::asset::AssetManager asset_manager = oshc::core::asset::AssetManager();

oshc::core::state::StateEngine state_engine = oshc::core::state::StateEngine();

void init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL2: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cout << "Failed to init SDL2_image: " << IMG_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow("OpenSHC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr)
    {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Failed to init SDL2_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }

    Mix_AllocateChannels(32);
    Mix_Volume(-1, 32);
    Mix_VolumeMusic(32);
}

} // namespace oshc::core
#include "core.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace oshc::core
{
SDL_Renderer *renderer = nullptr;

SDL_Window *window = nullptr;

oshc::core::asset::AssetManager asset_manager = oshc::core::asset::AssetManager();

oshc::core::state::StateEngine state_engine = oshc::core::state::StateEngine();

void init()
{
    // SDL2
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "Failed to init SDL2: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // SDL2_image
    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        std::cout << "Failed to init SDL2_image: " << IMG_GetError() << std::endl;
        exit(1);
    }

    // SDL2_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "Failed to init SDL2_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }

    Mix_AllocateChannels(32);
    Mix_Volume(-1, 32);
    Mix_VolumeMusic(32);

    // SDL2_ttf
    if (TTF_Init() < 0)
    {
        std::cout << "Failed to init SDL2_ttf: " << TTF_GetError() << std::endl;
        exit(1);
    }

    // Create window
    window =
        SDL_CreateWindow("OpenSHC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);

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
}

} // namespace oshc::core
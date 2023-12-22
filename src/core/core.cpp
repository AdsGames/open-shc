#include "core.h"

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace oshc::core
{
std::shared_ptr<SDL_Renderer> renderer = nullptr;

std::shared_ptr<SDL_Window> window = nullptr;

oshc::asset::AssetManager asset_manager = oshc::asset::AssetManager();

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
    window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("OpenSHC", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 960, SDL_WINDOW_SHOWN),
        SDL_DestroyWindow);

    if (window == nullptr)
    {
        std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
        exit(1);
    }

    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
        SDL_DestroyRenderer);

    if (renderer == nullptr)
    {
        std::cout << "Failed to create renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }
}

void destroy()
{
    std::cout << "Stopping music..." << std::endl;
    Mix_CloseAudio();

    std::cout << "Destroying asset manager..." << std::endl;
    asset_manager.destroy();

    std::cout << "Destroying SDL2..." << std::endl;
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

} // namespace oshc::core
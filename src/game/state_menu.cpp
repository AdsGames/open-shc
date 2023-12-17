#include "state_menu.h"

#include "../core/core.h"
#include <SDL2/SDL.h>

namespace oshc::state
{
void StateMenu::render()
{
    SDL_RenderCopy(oshc::core::renderer, oshc::core::asset_manager.get_texture("frontend_main").get().get(), nullptr,
                   nullptr);
}

} // namespace oshc::state
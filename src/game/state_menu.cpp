#include "state_menu.h"

#include "../core/core.h"
#include "asset_viewer.h"
#include <SDL2/SDL.h>

namespace oshc::state
{

void StateMenu::init()
{
    oshc::core::asset_manager.get_music("a_strong_spice").play();
    oshc::core::asset_manager.get_sound("greetings_fatal_exception").play();
}

void StateMenu::update()
{
    m_asset_viewer.update();
}

void StateMenu::render()
{
    SDL_RenderCopy(oshc::core::renderer, oshc::core::asset_manager.get_texture("frontend_main").get().get(), nullptr,
                   nullptr);

    m_asset_viewer.render();
}

} // namespace oshc::state
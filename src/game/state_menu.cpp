#include "state_menu.h"

#include "../core/core.h"
#include "../core/music_player.h"
#include "../core/render.h"

#include "asset_viewer.h"
#include <SDL2/SDL.h>

namespace oshc::state
{

void StateMenu::init()
{
    oshc::music::play("a_strong_spice");
    oshc::core::asset_manager.get_sound("greetings_fatal_exception")->play();
}

void StateMenu::update()
{
    m_asset_viewer.update();
}

void StateMenu::render()
{
    oshc::render::draw_texture("frontend_main", SDL_Rect{0, 0, 1280, 960});
    oshc::render::draw_texture("ads_logo", SDL_Rect{0, 0, 123, 123});
    oshc::render::draw_animation("interface_buttons", SDL_Rect{0, 0, 123, 123}, 7);

    // m_asset_viewer.render();
}

} // namespace oshc::state
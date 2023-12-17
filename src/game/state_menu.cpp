#include "state_menu.h"

#include "../core/core.h"
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
    m_anim_frame++;
    if (m_anim_frame > oshc::core::asset_manager.get_animation("anim_armourer").get_frame_count() - 1)
    {
        m_anim_frame = 0;
    }
}

void StateMenu::render()
{
    SDL_RenderCopy(oshc::core::renderer, oshc::core::asset_manager.get_texture("frontend_main").get().get(), nullptr,
                   nullptr);

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = 100;
    rect.h = 100;
    SDL_RenderCopy(oshc::core::renderer,
                   oshc::core::asset_manager.get_animation("anim_armourer").get().at(m_anim_frame).get(), nullptr,
                   &rect);
}

} // namespace oshc::state
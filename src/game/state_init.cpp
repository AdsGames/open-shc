#include "state_init.h"

#include "../core/core.h"
#include "../core/music_player.h"
#include "../core/render.h"

namespace oshc::state
{

void StateInit::init()
{
    oshc::core::init();
    oshc::core::asset_manager.init("assets/config/assets.json");
    oshc::music::play("a_pane_in_the_glass");
}

void StateInit::update()
{
    oshc::core::asset_manager.eager_load_asset();

    m_loading_percent = static_cast<float>(oshc::core::asset_manager.get_loaded_asset_count()) /
                        static_cast<float>(oshc::core::asset_manager.get_asset_count());

    if (oshc::core::asset_manager.get_loaded_asset_count() == oshc::core::asset_manager.get_asset_count())
    {
        oshc::core::state_engine.set_next_state(oshc::core::state::ProgramState::STATE_MENU);
    }
}

void StateInit::render()
{
    oshc::render::draw_texture("frontend_loading", SDL_Rect{0, 0, 1280, 960});
    oshc::render::draw_animation("anim_brewer", SDL_Rect{0, 0, 200, 200}, m_frame++);

    // Draw loading bar
    auto loading_bar_width = 500;
    auto loading_bar_height = 20;
    auto loading_bar_x = (1280 - loading_bar_width) / 2;
    auto loading_bar_y = 960 - 100;

    SDL_Rect loading_bar_rect{loading_bar_x, loading_bar_y, loading_bar_width, loading_bar_height};
    SDL_Rect loading_bar_fill_rect{loading_bar_x, loading_bar_y,
                                   static_cast<int>(loading_bar_width * m_loading_percent), loading_bar_height};

    SDL_SetRenderDrawBlendMode(oshc::core::renderer.get(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(oshc::core::renderer.get(), 0, 0, 0, 128);
    SDL_RenderFillRect(oshc::core::renderer.get(), &loading_bar_rect);
    SDL_SetRenderDrawColor(oshc::core::renderer.get(), 0, 0, 0, 128);
    SDL_RenderDrawRect(oshc::core::renderer.get(), &loading_bar_rect);
    SDL_SetRenderDrawColor(oshc::core::renderer.get(), 255, 128, 128, 128);
    SDL_RenderFillRect(oshc::core::renderer.get(), &loading_bar_fill_rect);
    SDL_SetRenderDrawBlendMode(oshc::core::renderer.get(), SDL_BLENDMODE_NONE);
}

void StateInit::destroy()
{
    oshc::music::stop();
}

} // namespace oshc::state
#include "state_init.h"

#include "../core/core.h"

namespace oshc::state
{

void StateInit::init()
{
    oshc::core::init();
    oshc::core::asset_manager.init("assets/config/assets.json");
    oshc::core::asset_manager.get_music("a_pane_in_the_glass").play();

    m_fake_loader = SDL_GetTicks();
}

void StateInit::update()
{
    if (SDL_GetTicks() - m_fake_loader > 3000)
    {
        oshc::core::state_engine.set_next_state(oshc::core::state::ProgramState::STATE_MENU);
    }
}

void StateInit::render()
{
    SDL_RenderCopy(oshc::core::renderer, oshc::core::asset_manager.get_texture("frontend_loading").get().get(), nullptr,
                   nullptr);
}

void StateInit::destroy()
{
    oshc::core::asset_manager.get_music("a_pane_in_the_glass").stop();
}

} // namespace oshc::state
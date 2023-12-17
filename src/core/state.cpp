#include "state.h"

#include <SDL2/SDL.h>
#include <iostream>

#include "core.h"

#include "../game/state_game.h"
#include "../game/state_init.h"
#include "../game/state_intro.h"
#include "../game/state_menu.h"

namespace oshc::core::state
{

void StateEngine::render() const
{
    if (!m_state)
    {
        return;
    }

    SDL_RenderClear(oshc::core::renderer);
    m_state->render();
    SDL_RenderPresent(oshc::core::renderer);
}

void StateEngine::update()
{
    if (m_state)
    {
        m_state->update();
    }

    change_state();
}

void StateEngine::set_next_state(const ProgramState state)
{
    m_next_state = state;
}

ProgramState StateEngine::get_active_state_id() const
{
    return m_active_state;
}

void StateEngine::change_state()
{
    // If the state needs to be changed
    if (m_next_state == ProgramState::STATE_NULL)
    {
        return;
    }

    // Delete the current state
    if (m_state)
    {
        m_state->destroy();
        m_state = nullptr;
    }

    // Change the state
    switch (m_next_state)
    {
    case ProgramState::STATE_GAME:
        m_state = std::make_unique<oshc::state::StateGame>(*this);
        std::cout << "Switched state to game." << std::endl;
        break;

    case ProgramState::STATE_MENU:
        m_state = std::make_unique<oshc::state::StateMenu>(*this);
        std::cout << "Switched state to main menu." << std::endl;
        break;

    case ProgramState::STATE_INIT:
        m_state = std::make_unique<oshc::state::StateInit>(*this);
        std::cout << "Switched state to init." << std::endl;
        break;

    case ProgramState::STATE_INTRO:
        m_state = std::make_unique<oshc::state::StateIntro>(*this);
        std::cout << "Switched state to intro." << std::endl;
        break;

    default:
        std::cout << "Exiting program." << std::endl;
        break;
    }

    m_state->init();

    // Change the current state ID
    m_active_state = m_next_state;

    // NULL the next state ID
    m_next_state = ProgramState::STATE_NULL;
}

} // namespace oshc::core::state
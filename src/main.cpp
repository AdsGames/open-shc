#include <SDL2/SDL.h>

#include <iostream>
#include <vector>

#include "core/core.h"

/**
 * @brief Entry point for the program
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @return int Exit code
 */
int main(int argc, char **argv)
{
    oshc::core::state_engine.set_next_state(oshc::core::state::ProgramState::STATE_INIT);

    while (oshc::core::state_engine.get_active_state_id() != oshc::core::state::ProgramState::STATE_EXIT)
    {
        oshc::core::state_engine.update();
        oshc::core::state_engine.render();

        // Check if esc pressed
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                oshc::core::state_engine.set_next_state(oshc::core::state::ProgramState::STATE_EXIT);
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    oshc::core::state_engine.set_next_state(oshc::core::state::ProgramState::STATE_EXIT);
                }
            }
        }
    }

    return 0;
}
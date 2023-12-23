#include <SDL2/SDL.h>

#include <chrono>
#include <iostream>
#include <tracy/Tracy.hpp>
#include <vector>

#include "core/core.h"

using namespace std::chrono_literals;
using namespace std::chrono;
constexpr nanoseconds timestep(16ms);

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

    nanoseconds lag(0ns);
    auto time_start = high_resolution_clock::now();

    while (oshc::core::state_engine.get_active_state_id() != oshc::core::state::ProgramState::STATE_EXIT)
    {
        FrameMarkStart("Main Loop");

        auto delta_time = high_resolution_clock::now() - time_start;
        time_start = high_resolution_clock::now();
        lag += duration_cast<nanoseconds>(delta_time);

        while (lag >= timestep)
        {
            lag -= timestep;
            FrameMarkStart("Main Loop - Update");
            oshc::core::state_engine.update();
            FrameMarkEnd("Main Loop - Update");
        }

        FrameMarkStart("Main Loop - Render");
        oshc::core::state_engine.render();
        FrameMarkEnd("Main Loop - Render");

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
        FrameMarkEnd("Main Loop");
    }

    oshc::core::destroy();

    return 0;
}
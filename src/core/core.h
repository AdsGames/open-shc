/**
 * @file core.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Core engine utilities
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "asset_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace oshc::core
{

// Accept global renderer

/// @brief Global renderer
extern SDL_Renderer *renderer;

/// @brief Global window
extern SDL_Window *window;

/// @brief Global asset manager
extern oshc::asset::AssetManager asset_manager;

/**
 * @brief Initialize SDL2 and create window
 *
 */
void init();

} // namespace oshc::core
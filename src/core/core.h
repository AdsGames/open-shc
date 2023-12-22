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
#include "state.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>

namespace oshc::core
{

// Accept global renderer

/// @brief Global renderer
extern std::shared_ptr<SDL_Renderer> renderer;

/// @brief Global window
extern std::shared_ptr<SDL_Window> window;

/// @brief Global asset manager
extern oshc::asset::AssetManager asset_manager;

// @breif Global state engine
extern oshc::core::state::StateEngine state_engine;

// @breif Global dev font
extern TTF_Font *dev_font;

/**
 * @brief Initialize SDL2 and create window
 *
 */
void init();

/**
 * @brief Destroy SDL2 and window
 *
 */
void destroy();

} // namespace oshc::core
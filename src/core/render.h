/**
 * @file render.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Rendering routines
 * @version 0.1
 * @date 2023-12-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "asset.h"

namespace oshc::render
{

/**
 * @brief Draw a texture to the screen
 *
 */
void draw_texture(const std::string &texture_id, const SDL_Rect &rect);

/**
 * @brief Draw text to the screen
 *
 */
void draw_text(const std::string &font_id, const std::string &text, const int x, const int y, const SDL_Color &color);

/**
 * @brief Draw an animation to the screen
 *
 */
void draw_animation(const std::string &animation_id, const SDL_Rect &rect, const unsigned int frame = 0);

} // namespace oshc::render
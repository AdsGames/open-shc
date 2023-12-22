/**
 * @file music_player.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Manage music playback
 * @version 0.1
 * @date 2023-12-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>

namespace oshc::music
{
/**
 * @brief Play music
 *
 * @param music_id
 */
void play(const std::string &music_id);

/**
 * @brief Stop all music
 *
 */
void stop();

/**
 * @brief Set music volume
 *
 * @param volume Volume between 0 and 1
 */
void set_volume(float volume);

/**
 * @brief Get music volume
 *
 * @return float
 */
float get_volume();

} // namespace oshc::music
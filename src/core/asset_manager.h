/**
 * @file asset_manager.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Centralized asset manager for loading and storing assets
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <vector>

#include "asset.h"

namespace oshc::core::asset
{

class AssetManager
{
  public:
    /**
     * @brief Initialize assets from config file
     *
     * @param asset_config_path Path to asset config file
     */
    void init(const std::string &asset_config_path);

    /**
     * @brief Get a texture
     *
     * @param id Texture id
     * @return Texture
     */
    Texture get_texture(const std::string &id);

    /**
     * @brief Get a animation
     *
     * @param id Animation id
     * @return Animation
     */
    Animation get_animation(const std::string &id);

    /**
     * @brief Get music
     *
     * @param id Music id
     * @return Music
     */
    Music get_music(const std::string &id);

  private:
    /// @brief Map of textures
    std::map<std::string, Texture, std::less<>> textures;

    /// @brief Map of animations
    std::map<std::string, Animation, std::less<>> animations;

    /// @brief Map of music
    std::map<std::string, Music, std::less<>> music;
};

} // namespace oshc::core::asset
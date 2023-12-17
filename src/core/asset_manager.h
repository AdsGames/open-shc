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

using TextureMap = std::map<std::string, Texture, std::less<>>;
using AnimationMap = std::map<std::string, Animation, std::less<>>;
using SoundMap = std::map<std::string, Sound, std::less<>>;
using MusicMap = std::map<std::string, Music, std::less<>>;
using FontMap = std::map<std::string, Font, std::less<>>;

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
     * @brief Get a sound
     *
     * @param id Sound id
     * @return Sound
     */
    Sound get_sound(const std::string &id);

    /**
     * @brief Get music
     *
     * @param id Music id
     * @return Music
     */
    Music get_music(const std::string &id);

    /**
     * @brief Get font
     *
     * @param id Font id
     * @return Font
     */
    Font get_font(const std::string &id);

    /**
     * @brief Get all textures as ref
     *
     */
    TextureMap &get_textures();

    /**
     * @brief Get all animations as ref
     *
     */
    AnimationMap &get_animations();

  private:
    /// @brief Map of textures
    TextureMap m_textures;

    /// @brief Map of animations
    AnimationMap m_animations;

    /// @brief Map of sounds
    SoundMap m_sounds;

    /// @brief Map of music
    MusicMap m_music;

    /// @brief Map of fonts
    FontMap m_fonts;
};

} // namespace oshc::core::asset
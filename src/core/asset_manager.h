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
#include <memory>
#include <string>

#include "asset.h"

namespace oshc::asset
{

using AssetMap = std::map<std::string, std::shared_ptr<Asset>, std::less<>>;

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
     * @brief Destroy all assets
     *
     */
    void destroy();

    /**
     * @brief Eager load all assets
     *
     */
    void eager_load_asset() const;

    /**
     * @brief Get a texture
     *
     * @param id Texture id
     * @return Texture
     */
    std::shared_ptr<Texture> get_texture(const std::string &id);

    /**
     * @brief Get a animation
     *
     * @param id Animation id
     * @return Animation
     */
    std::shared_ptr<Animation> get_animation(const std::string &id);

    /**
     * @brief Get a sound
     *
     * @param id Sound id
     * @return Sound
     */
    std::shared_ptr<Sound> get_sound(const std::string &id);

    /**
     * @brief Get music
     *
     * @param id Music id
     * @return Music
     */
    std::shared_ptr<Music> get_music(const std::string &id);

    /**
     * @brief Get font
     *
     * @param id Font id
     * @return Font
     */
    std::shared_ptr<Font> get_font(const std::string &id);

    /**
     * @brief Get all assets
     *
     */
    AssetMap &get_assets();

    /**
     * @brief Get asset count
     *
     */
    unsigned long get_asset_count() const;

    /**
     * @brief Get loaded asset count
     *
     */
    unsigned long get_loaded_asset_count() const;

  private:
    /**
     * @brief Get variant from asset map
     *
     */
    std::shared_ptr<Asset> get_asset(const std::string &id);

    /// @brief Map of all assets
    AssetMap m_assets;
};

} // namespace oshc::asset
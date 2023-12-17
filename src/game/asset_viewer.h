/**
 * @file asset_viewer.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Asset viewer for debugging
 * @version 0.1
 * @date 2023-12-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <string>
#include <vector>

namespace oshc::state
{

class AssetViewer
{
  public:
    /**
     * @brief Construct a new Asset Viewer object
     *
     */
    AssetViewer();

    /**
     * @brief Update asset viewer
     *
     */
    void update();

    /**
     * @brief Render asset viewer
     *
     */
    void render();

  private:
    std::vector<std::string> m_textures;
    std::vector<std::string> m_animations;

    std::string m_current_texture;
    std::string m_current_animation;
};

} // namespace oshc::state
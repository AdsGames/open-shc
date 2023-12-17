#include "asset_manager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace oshc::core::asset
{

// Load assets from json
void AssetManager::init(const std::string &config_file_path)
{
    // Load json
    std::ifstream file(config_file_path);

    if (!file.is_open())
    {
        std::cout << "Failed to open config file: " << config_file_path << std::endl;
        return;
    }

    nlohmann::json j;
    file >> j;

    // Load textures
    for (auto &curr : j["textures"])
    {
        std::cout << "Loading texture: " << curr["id"] << std::endl;
        Texture t;
        t.load(curr["path"]);
        this->m_textures[curr["id"]] = t;
    }

    // Load animations
    for (auto &curr : j["animations"])
    {
        std::cout << "Loading animation: " << curr["id"] << std::endl;
        Animation a;
        a.load(curr["path"]);
        this->m_animations[curr["id"]] = a;
    }

    // Load music
    for (auto &curr : j["music"])
    {
        std::cout << "Loading music: " << curr["id"] << std::endl;
        Music m;
        m.load(curr["path"]);
        this->m_music[curr["id"]] = m;
    }

    // Load sounds
    for (auto &curr : j["sounds"])
    {
        std::cout << "Loading sound: " << curr["id"] << std::endl;
        Sound s;
        s.load(curr["path"]);
        this->m_sounds[curr["id"]] = s;
    }

    // Load fonts
    for (auto &curr : j["fonts"])
    {
        std::cout << "Loading font: " << curr["id"] << std::endl;
        Font f;
        f.load(curr["path"], curr["size"]);
        this->m_fonts[curr["id"]] = f;
    }
}

// Get texture
Texture AssetManager::get_texture(const std::string &id)
{
    return this->m_textures[id];
}

// Get animation
Animation AssetManager::get_animation(const std::string &id)
{
    return this->m_animations[id];
}

// Get sound
Sound AssetManager::get_sound(const std::string &id)
{
    return this->m_sounds[id];
}

// Get music
Music AssetManager::get_music(const std::string &id)
{
    return this->m_music[id];
}

// Get font
Font AssetManager::get_font(const std::string &id)
{
    return this->m_fonts[id];
}

// Get all textures as ref
TextureMap &AssetManager::get_textures()
{
    return this->m_textures;
}

// Get all animations as ref
AnimationMap &AssetManager::get_animations()
{
    return this->m_animations;
}

} // namespace oshc::core::asset
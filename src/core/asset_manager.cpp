#include "asset_manager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace oshc::asset
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
        textures[curr["id"]] = t;
    }

    // Load animations
    for (auto &curr : j["animations"])
    {
        std::cout << "Loading animation: " << curr["id"] << std::endl;
        Animation a;
        a.load(curr["path"]);
        animations[curr["id"]] = a;
    }

    // Load music
    for (auto &curr : j["music"])
    {
        std::cout << "Loading music: " << curr["id"] << std::endl;
        Music m;
        m.load(curr["path"]);
        this->music[curr["id"]] = m;
    }
}

// Get texture
Texture AssetManager::get_texture(const std::string &id)
{
    return textures[id];
}

// Get animation
Animation AssetManager::get_animation(const std::string &id)
{
    return animations[id];
}

// Get music
Music AssetManager::get_music(const std::string &id)
{
    return music[id];
}

} // namespace oshc::asset
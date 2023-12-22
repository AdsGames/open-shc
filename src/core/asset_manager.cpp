#include "asset_manager.h"

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <tracy/Tracy.hpp>

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
        auto t = std::make_shared<Texture>();
        std::string path = curr["path"];
        t->set_path(path);
        this->m_assets[curr["id"]] = t;
    }

    // Load animations
    for (auto &curr : j["animations"])
    {
        auto a = std::make_shared<Animation>();
        std::string path = curr["path"];
        a->set_path(path);
        this->m_assets[curr["id"]] = a;
    }

    // Load music
    for (auto &curr : j["music"])
    {
        auto m = std::make_shared<Music>();
        std::string path = curr["path"];
        m->set_path(path);
        this->m_assets[curr["id"]] = m;
    }

    // Load sounds
    for (auto &curr : j["sounds"])
    {
        auto s = std::make_shared<Sound>();
        std::string path = curr["path"];
        s->set_path(path);
        this->m_assets[curr["id"]] = s;
    }

    // Load fonts
    for (auto &curr : j["fonts"])
    {
        auto f = std::make_shared<Font>();
        std::string path = curr["path"];
        f->set_path(path);
        f->set_size(curr["size"]);
        this->m_assets[curr["id"]] = f;
    }
}

// Destroy all assets
void AssetManager::destroy()
{
    m_assets.clear();
}

// Eager load one asset
void AssetManager::eager_load_asset() const
{

    for (auto &[_, curr] : this->m_assets)
    {
        if (!curr->is_loaded())
        {
            FrameMarkStart("Load Asset");
            curr->load();
            FrameMarkEnd("Load Asset");
            return;
        }
    }
}

// Get asset
std::shared_ptr<Asset> AssetManager::get_asset(const std::string &id)
{
    const auto asset = this->m_assets.at(id);

    if (asset == nullptr)
    {
        std::cout << "Failed to get asset: " << id << std::endl;
        return nullptr;
    }

    if (!asset->is_loaded())
    {
        std::cout << "Loading asset: " << asset->get_path() << std::endl;
        asset->load();
    }

    return asset;
}

// Get texture
std::shared_ptr<Texture> AssetManager::get_texture(const std::string &id)
{
    const auto texture = get_asset(id);
    return std::dynamic_pointer_cast<Texture>(texture);
}

// Get animation
std::shared_ptr<Animation> AssetManager::get_animation(const std::string &id)
{
    const auto animation = get_asset(id);
    return std::dynamic_pointer_cast<Animation>(animation);
}

// Get sound
std::shared_ptr<Sound> AssetManager::get_sound(const std::string &id)
{
    const auto sound = get_asset(id);
    return std::dynamic_pointer_cast<Sound>(sound);
}

// Get music
std::shared_ptr<Music> AssetManager::get_music(const std::string &id)
{
    const auto music = get_asset(id);
    return std::dynamic_pointer_cast<Music>(music);
}

// Get font
std::shared_ptr<Font> AssetManager::get_font(const std::string &id)
{
    auto font = get_asset(id);
    return std::dynamic_pointer_cast<Font>(font);
}

// Get all assets
AssetMap &AssetManager::get_assets()
{
    return this->m_assets;
}

// Get asset count
unsigned long AssetManager::get_asset_count() const
{
    return this->m_assets.size();
}

// Get loaded asset count
unsigned long AssetManager::get_loaded_asset_count() const
{
    unsigned long count = 0;

    for (auto &[_, curr] : this->m_assets)
    {
        if (curr->is_loaded())
        {
            count++;
        }
    }

    return count;
}

} // namespace oshc::asset
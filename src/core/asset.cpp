#include "asset.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../lib/parsers/gm1_parser.h"
#include "../lib/parsers/tgx_parser.h"
#include "core.h"

namespace oshc::asset
{

// Base asset
bool Asset::is_loaded() const
{
    return this->m_is_loaded;
}

void Asset::set_path(const std::string_view &path)
{
    this->m_path = path;
}

std::string Asset::get_path() const
{
    return this->m_path;
}

// Texture
bool Texture::load()
{
    if (m_path.ends_with(".tgx"))
    {
        m_data = load_tgx(m_path);
    }
    else if (m_path.ends_with(".png"))
    {
        m_data = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(oshc::core::renderer.get(), m_path.c_str()),
                                              SDL_DestroyTexture);
    }
    else
    {
        std::cout << "Unknown texture type: " << m_path << std::endl;
        return false;
    }

    if (m_data == nullptr)
    {
        std::cout << "Failed to load texture: " << m_path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    auto width = 0;
    auto height = 0;

    SDL_QueryTexture(m_data.get(), nullptr, nullptr, &width, &height);

    m_width = width;
    m_height = height;
    m_is_loaded = true;

    return true;
}

std::shared_ptr<SDL_Texture> Texture::get_data() const
{
    return this->m_data;
}

unsigned int Texture::get_width() const
{
    return this->m_width;
}

unsigned int Texture::get_height() const
{
    return this->m_height;
}

AssetId Texture::get_type() const
{
    return AssetId::TEXTURE;
}

// Animation
bool Animation::load()
{
    if (!m_path.ends_with(".gm1"))
    {
        std::cout << "Unknown animation type: " << m_path << std::endl;
        return false;
    }

    for (const auto &texture : load_gm1(m_path))
    {
        if (texture == nullptr)
        {
            std::cout << "Failed to load texture: " << m_path << std::endl;
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        auto width = 0;
        auto height = 0;

        SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

        this->m_width = width;
        this->m_height = height;

        m_data.push_back(texture);
    }

    this->m_is_loaded = true;
    return true;
}

std::vector<std::shared_ptr<SDL_Texture>> &Animation::get_data()
{
    return this->m_data;
}

unsigned int Animation::get_width() const
{
    return this->m_width;
}

unsigned int Animation::get_height() const
{
    return this->m_height;
}

unsigned int Animation::get_frame_count() const
{
    return static_cast<unsigned int>(this->m_data.size());
}

AssetId Animation::get_type() const
{
    return AssetId::ANIMATION;
}

// Sound
bool Sound::load()
{
    m_data = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(m_path.c_str()), Mix_FreeChunk);

    if (m_data == nullptr)
    {
        std::cout << "Failed to load sound: " << m_path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    Mix_VolumeChunk(m_data.get(), 32);
    m_is_loaded = true;
    return true;
}

void Sound::play() const
{
    Mix_PlayChannel(-1, m_data.get(), 0);
}

AssetId Sound::get_type() const
{
    return AssetId::SOUND;
}

// Music
bool Music::load()
{
    m_data = std::shared_ptr<Mix_Music>(Mix_LoadMUS(m_path.c_str()), Mix_FreeMusic);

    if (m_data == nullptr)
    {
        std::cout << "Failed to load music: " << m_path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    Mix_VolumeMusic(32);

    m_is_loaded = true;

    return true;
}

std::shared_ptr<Mix_Music> Music::get_data() const
{
    return m_data;
}

AssetId Music::get_type() const
{
    return AssetId::MUSIC;
}

// Font
bool Font::load()
{
    m_data = std::shared_ptr<TTF_Font>(TTF_OpenFont(m_path.c_str(), m_size), TTF_CloseFont);

    if (m_data == nullptr)
    {
        std::cout << "Failed to load font: " << m_path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_is_loaded = true;

    return true;
}

void Font::set_size(unsigned int size)
{
    m_size = size;
}

std::shared_ptr<TTF_Font> Font::get_data() const
{
    return m_data;
}

AssetId Font::get_type() const
{
    return AssetId::FONT;
}

} // namespace oshc::asset
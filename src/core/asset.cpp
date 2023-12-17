#include "asset.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "../lib/parsers/gm1_parser.h"
#include "../lib/parsers/tgx_parser.h"
#include "core.h"

namespace oshc::core::asset
{

// Texture
bool Texture::load(const std::string &path)
{
    if (path.ends_with(".tgx"))
    {
        this->load_tgx(path);
    }
    else if (path.ends_with(".png"))
    {
        this->load_png(path);
    }
    else
    {
        std::cout << "Unknown texture type: " << path << std::endl;
        return false;
    }

    if (m_data == nullptr)
    {
        std::cout << "Failed to load texture: " << path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    auto width = 0;
    auto height = 0;

    SDL_QueryTexture(m_data.get(), nullptr, nullptr, &width, &height);

    this->m_width = width;
    this->m_height = height;

    return true;
}

void Texture::load_png(const std::string &path)
{
    m_data = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(oshc::core::renderer, path.c_str()), SDL_DestroyTexture);
}

void Texture::load_tgx(const std::string &path)
{
    m_data = std::shared_ptr<SDL_Texture>(TGXParser::load_tgx(path), SDL_DestroyTexture);
}

std::shared_ptr<SDL_Texture> Texture::get() const
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

// Animation
void Animation::load(const std::string &path)
{
    if (!path.ends_with(".gm1"))
    {
        std::cout << "Unknown animation type: " << path << std::endl;
        return;
    }

    auto gm1 = GM1Parser::load_gm1(path);

    for (auto &frame : *gm1)
    {
        auto texture = std::shared_ptr<SDL_Texture>(frame, SDL_DestroyTexture);

        if (texture == nullptr)
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            std::cout << "SDL Error: " << SDL_GetError() << std::endl;
            return;
        }

        auto width = 0;
        auto height = 0;

        SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);

        this->m_width = width;
        this->m_height = height;

        m_data.push_back(texture);
    }
}

std::vector<std::shared_ptr<SDL_Texture>> Animation::get() const
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

// Sound
void Sound::load(const std::string &path)
{
    m_data = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(path.c_str()), Mix_FreeChunk);

    if (m_data == nullptr)
    {
        std::cout << "Failed to load sound: " << path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    Mix_VolumeChunk(m_data.get(), 32);
}

void Sound::play() const
{
    Mix_PlayChannel(-1, m_data.get(), 0);
}

// Music
void Music::load(const std::string &path)
{
    m_data = std::shared_ptr<Mix_Music>(Mix_LoadMUS(path.c_str()), Mix_FreeMusic);

    if (m_data == nullptr)
    {
        std::cout << "Failed to load music: " << path << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    Mix_VolumeMusic(32);
}

void Music::play() const
{
    Mix_PlayMusic(m_data.get(), -1);
}

void Music::stop() const
{
    Mix_HaltMusic();
}

void Music::pause() const
{
    if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
    else
    {
        Mix_PauseMusic();
    }
}

void Music::set_volume(int volume) const
{
    Mix_VolumeMusic(volume);
}

bool Music::is_playing() const
{
    return Mix_PlayingMusic() == 1;
}

} // namespace oshc::core::asset
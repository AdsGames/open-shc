#include "music_player.h"

#include <SDL2/SDL_mixer.h>

#include "core.h"

namespace oshc::music
{

void play(const std::string &id)
{
    auto music = oshc::core::asset_manager.get_music(id);

    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }

    Mix_PlayMusic(music->get_data().get(), -1);
}

void stop()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
}

void set_volume(float volume)
{
    auto _volume = static_cast<int>(volume * static_cast<float>(MIX_MAX_VOLUME));
    Mix_VolumeMusic(_volume);
}

float get_volume()
{
    auto volume = Mix_VolumeMusic(-1);
    return static_cast<float>(volume) / static_cast<float>(MIX_MAX_VOLUME);
}

} // namespace oshc::music
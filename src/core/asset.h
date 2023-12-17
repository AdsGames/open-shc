/**
 * @file asset.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Asset types
 * @version 0.1
 * @date 2023-12-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <memory>
#include <vector>

namespace oshc::core::asset
{

/**
 * @brief Base asset class
 *
 */
class Asset
{
  public:
    virtual ~Asset() = default;
};

/**
 * @brief Texture asset
 *
 */
class Texture : public Asset
{
  public:
    ~Texture() override = default;

    /**
     * @brief Load a generic texture from file
     *
     * @param path Path to texture
     * @return true Asset loaded successfully
     * @return false Asset failed to load
     */
    bool load(const std::string &path);

    /**
     * @brief Get a shared pointer to the texture
     *
     * @return std::shared_ptr<SDL_Texture>
     */
    std::shared_ptr<SDL_Texture> get() const;

    /**
     * @brief Get width of texture
     *
     * @return unsigned int
     */
    unsigned int get_width() const;

    /**
     * @brief Get height of texture
     *
     * @return unsigned int
     */
    unsigned int get_height() const;

  private:
    /**
     * @brief Load a png texture from file
     *
     * @param path Path to texture
     */
    void load_png(const std::string &path);

    /**
     * @brief Load a tgx texture from file
     *
     * @param path Path to texture
     */
    void load_tgx(const std::string &path);

    /// @brief Shared pointer to underlying texture
    std::shared_ptr<SDL_Texture> m_data;

    /// @brief Width of texture
    unsigned int m_width;

    /// @brief Height of texture
    unsigned int m_height;
};

/**
 * @brief Animation asset
 *
 */
class Animation : public Asset
{
  public:
    ~Animation() override = default;

    /**
     * @brief Load an animation from file
     *
     * @param path
     */
    void load(const std::string &path);

    /**
     * @brief Get a vector of shared pointers to the textures
     *
     * @return std::vector<std::shared_ptr<SDL_Texture>>
     */
    std::vector<std::shared_ptr<SDL_Texture>> get() const;

    /**
     * @brief Get the width of the animation
     *
     * @return unsigned int
     */
    unsigned int get_width() const;

    /**
     * @brief Get the height of the animation
     *
     * @return unsigned int
     */
    unsigned int get_height() const;

    /**
     * @brief Get the frame count of the animation
     *
     * @return unsigned int
     */
    unsigned int get_frame_count() const;

  private:
    /// @brief Vector of shared pointers to underlying textures
    std::vector<std::shared_ptr<SDL_Texture>> m_data;

    /// @brief Width of animation
    unsigned int m_width;

    /// @brief Height of animation
    unsigned int m_height;

    /// @brief Frame count of animation
    unsigned int m_frame_count;
};

/**
 * @brief Sound asset
 *
 */
class Sound : public Asset
{
  public:
    ~Sound() override = default;

    /**
     * @brief Load sound from file
     *
     * @param path Path to sound file
     */
    void load(const std::string &path);

    /**
     * @brief Play sound
     *
     */
    void play() const;

  private:
    /// @brief Shared pointer to underlying sound
    std::shared_ptr<Mix_Chunk> m_data;
};

/**
 * @brief Music asset
 *
 */
class Music : public Asset
{
  public:
    ~Music() override = default;

    /**
     * @brief Load music from file
     *
     * @param path Path to music file
     */
    void load(const std::string &path);

    /**
     * @brief Play music
     *
     */
    void play() const;

    /**
     * @brief Pause music
     *
     */
    void pause() const;

    /**
     * @brief Stop music
     *
     */
    void stop() const;

    /**
     * @brief Set the global music volume
     *
     * @param volume
     */
    void set_volume(int volume) const;

    /**
     * @brief Check if music is playing
     *
     * @return true Music is playing
     * @return false Music is not playing
     */
    bool is_playing() const;

  private:
    /// @brief Shared pointer to underlying music
    std::shared_ptr<Mix_Music> m_data;
};
} // namespace oshc::core::asset
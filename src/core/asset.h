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
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <thread>
#include <vector>

namespace oshc::asset
{

/**
 * @brief Asset type enum
 *
 */
enum class AssetId
{
    TEXTURE,
    ANIMATION,
    SOUND,
    MUSIC,
    FONT
};

/**
 * @brief Base asset class
 *
 */
class Asset
{
  public:
    virtual ~Asset() = default;

    /**
     * @brief Get is loaded
     *
     */
    bool is_loaded() const;

    /**
     * @brief Set path
     *
     */
    void set_path(const std::string_view &path);

    /**
     * @brief Get path
     *
     */
    std::string get_path() const;

    /**
     * @brief Load asset
     *
     */
    virtual bool load() = 0;

    /**
     * @brief Get type
     *
     */
    virtual AssetId get_type() const = 0;

  protected:
    /// @breif Is asset loaded
    bool m_is_loaded{false};

    /// @brief Path to asset
    std::string m_path{""};
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
    bool load() override;

    /**
     * @brief Get a shared pointer to the texture
     *
     * @return std::shared_ptr<SDL_Texture>
     */
    std::shared_ptr<SDL_Texture> get_data() const;

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

    /**
     * @brief Get type of asset
     *
     * @return AssetId
     */
    AssetId get_type() const override;

  private:
    /// @brief Shared pointer to underlying texture
    std::shared_ptr<SDL_Texture> m_data{nullptr};

    /// @brief Width of texture
    unsigned int m_width{0};

    /// @brief Height of texture
    unsigned int m_height{0};
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
    bool load() override;

    /**
     * @brief Get a vector of shared pointers to the textures
     *
     * @return std::vector<std::shared_ptr<SDL_Texture>>
     */
    std::vector<std::shared_ptr<SDL_Texture>> &get_data();

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

    /**
     * @brief Get type of asset
     *
     * @return AssetId
     */
    AssetId get_type() const override;

  private:
    /// @brief Vector of shared pointers to underlying textures
    std::vector<std::shared_ptr<SDL_Texture>> m_data{nullptr};

    /// @brief Width of animation
    unsigned int m_width{0};

    /// @brief Height of animation
    unsigned int m_height{0};

    /// @brief Frame count of animation
    unsigned int m_frame_count{0};
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
    bool load() override;

    /**
     * @brief Play sound
     *
     */
    void play() const;

    /**
     * @brief Get type of asset
     *
     * @return AssetId
     */
    AssetId get_type() const override;

  private:
    /// @brief Shared pointer to underlying sound
    std::shared_ptr<Mix_Chunk> m_data{nullptr};
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
    bool load() override;

    /**
     * @brief Get a vector of shared pointers to the textures
     *
     * @return Mix_Music
     */
    std::shared_ptr<Mix_Music> get_data() const;

    /**
     * @brief Get type of asset
     *
     * @return AssetId
     */
    AssetId get_type() const override;

  private:
    /// @brief Shared pointer to underlying music
    std::shared_ptr<Mix_Music> m_data;
};

/**
 * @brief Font asset
 *
 */
class Font : public Asset
{
  public:
    ~Font() override = default;

    /**
     * @brief Load font from file
     *
     * @param path Path to font file
     */
    bool load() override;

    /**
     * @brief Get the font
     *
     * @return std::shared_ptr<TTF_Font>
     */
    std::shared_ptr<TTF_Font> get_data() const;

    /**
     * @brief Set size
     *
     */
    void set_size(unsigned int size);

    /**
     * @brief Get type of asset
     *
     * @return AssetId
     */
    AssetId get_type() const override;

  private:
    /// @brief Shared pointer to underlying font
    std::shared_ptr<TTF_Font> m_data{nullptr};

    /// @brief Size of font
    unsigned int m_size{0};
};

} // namespace oshc::asset
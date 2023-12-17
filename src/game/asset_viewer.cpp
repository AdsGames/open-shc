#include "asset_viewer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../core/core.h"

namespace oshc::state
{

AssetViewer::AssetViewer()
{
    for (const auto &[key, texture] : oshc::core::asset_manager.get_textures())
    {
        m_textures.push_back(key);
    }

    for (const auto &[key, animation] : oshc::core::asset_manager.get_animations())
    {
        m_animations.push_back(key);
    }

    m_current_texture = m_textures[0];
    m_current_animation = m_animations[0];
}

void AssetViewer::update()
{
}

void AssetViewer::render()
{
    const auto &font = oshc::core::asset_manager.get_font("default");

    // Draw background
    const auto &texture = oshc::core::asset_manager.get_texture(m_current_texture);

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = texture.get_width();
    rect.h = texture.get_height();

    SDL_RenderCopy(oshc::core::renderer, texture.get().get(), nullptr, &rect);

    int y = 0;
    for (const auto &texture_name : m_textures)
    {
        // Draw name
        SDL_Color color = {255, 0, 0, 255};
        const auto &text_surface = TTF_RenderText_Solid(font.get().get(), texture_name.c_str(), color);
        const auto &text_texture = SDL_CreateTextureFromSurface(oshc::core::renderer, text_surface);

        SDL_Rect text_rect;
        text_rect.x = 100;
        text_rect.y = y;
        text_rect.w = text_surface->w;
        text_rect.h = text_surface->h;

        SDL_RenderCopy(oshc::core::renderer, text_texture, nullptr, &text_rect);

        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);

        y += text_surface->h;
    }
}

} // namespace oshc::state
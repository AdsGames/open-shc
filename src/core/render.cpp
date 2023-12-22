#include "render.h"

#include "core.h"

namespace oshc::render
{

void draw_texture(const std::string &texture_id, const SDL_Rect &rect)
{
    const auto texture = oshc::core::asset_manager.get_texture(texture_id);

    if (texture == nullptr)
    {
        std::cout << "Failed to draw texture: " << texture_id << std::endl;
        return;
    }

    SDL_RenderCopy(oshc::core::renderer.get(), texture->get_data().get(), nullptr, &rect);
}

void draw_animation(const std::string &animation_id, const SDL_Rect &rect, const unsigned int frame)
{
    const auto animation = oshc::core::asset_manager.get_animation(animation_id);
    const auto draw_frame = frame % animation->get_frame_count();

    if (animation == nullptr)
    {
        std::cout << "Failed to draw texture: " << animation_id << std::endl;
        return;
    }

    SDL_RenderCopy(oshc::core::renderer.get(), animation->get_data().at(draw_frame).get(), nullptr, &rect);
}

void draw_text(const std::string &font_id, const std::string &text, const int x, const int y, const SDL_Color &color)
{
    const auto font = oshc::core::asset_manager.get_font(font_id);

    if (font == nullptr)
    {
        std::cout << "Failed to draw text: " << text << std::endl;
        return;
    }

    const auto &text_surface = TTF_RenderText_Solid(font->get_data().get(), text.c_str(), color);
    const auto &text_texture = SDL_CreateTextureFromSurface(oshc::core::renderer.get(), text_surface);

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = text_surface->w;
    rect.h = text_surface->h;

    SDL_RenderCopy(oshc::core::renderer.get(), text_texture, nullptr, &rect);

    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
}

} // namespace oshc::render
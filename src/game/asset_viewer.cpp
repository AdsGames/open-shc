#include "asset_viewer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "../core/core.h"
#include "../core/render.h"

namespace oshc::state
{

void AssetViewer::update()
{
}

void AssetViewer::render()
{
    const auto &font = oshc::core::asset_manager.get_font("default");

    int y = 0;
    for (const auto &[name, asset] : oshc::core::asset_manager.get_assets())
    {
        // Draw name
        oshc::render::draw_text("default", name, 100, y, {255, 0, 0, 255});
        y += 16;
    }
}

} // namespace oshc::state
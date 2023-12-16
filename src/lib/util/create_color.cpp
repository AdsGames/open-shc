#include "create_color.h"

namespace oshc::util
{

SDL_Color create_color(unsigned char r, unsigned char g, unsigned char b)
{
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

} // namespace oshc::util
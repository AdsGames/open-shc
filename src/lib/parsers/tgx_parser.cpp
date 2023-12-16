#include "tgx_parser.h"

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

#include "../../core/core.h"

// Convert 15 bit colour to 24 bit
Uint32 TGXParser::convert_color(SDL_PixelFormat *pixel_format, unsigned char byte1, unsigned char byte2)
{
    // Extract values
    unsigned char r = byte2 >> 2;
    unsigned char g = ((byte1 >> 5) & 0b00000111) | ((byte2 << 3) & 0b00011000);
    unsigned char b = byte1 & 0b00011111;

    // Convert from 15 bit to 24
    // Technically this will truncate the whites
    //   but I can't think of a better solition
    //   without involving float rounding.
    r = r * 8;
    g = g * 8;
    b = b * 8;

    // Return new colour
    return SDL_MapRGB(pixel_format, r, g, b);
}

// Look up address from pallette
Uint32 TGXParser::pallete_lookup(SDL_PixelFormat *pixel_format, unsigned char addr, std::vector<unsigned int> *pall)
{
    if (addr < pall->size())
    {
        return pall->at(addr);
    }

    return SDL_MapRGB(pixel_format, 255, 0, 0);
}

// Tgx helper used by file and memory
SDL_Texture *TGXParser::load_tgx_helper(std::vector<unsigned char> *bytes, unsigned int *iter, unsigned int width,
                                        unsigned int height, std::vector<unsigned int> *pall)
{
    // Make bitmap
    SDL_PixelFormat *pixel_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_Texture *texture =
        SDL_CreateTexture(oshc::core::renderer, pixel_format->format, SDL_TEXTUREACCESS_STREAMING, width, height);

    if (texture == nullptr)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Lock and dump pixels
    Uint32 *pixels = nullptr;
    int pitch = 0;
    if (SDL_LockTexture(texture, nullptr, (void **)&pixels, &pitch))
    {
        std::cout << "Failed to lock texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // File iterator and image x and y
    unsigned int x = 0;
    unsigned int y = 0;

    // Parse file
    while (*iter < bytes->size())
    {
        // Close
        if (y >= height)
            break;

        // Extract token and length
        int token = bytes->at(*iter) >> 5;
        int length = (bytes->at(*iter) & 0b00011111) + 1;

        // Increment iter (consume token)
        *iter += 1;

        // Deal with tokens accordingly
        switch (token)
        {
        // Pixel stream
        case 0:

            // 15 bit colour
            if (pall == nullptr)
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    // Get pixel position
                    Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                    auto color1 = bytes->at(*iter);
                    auto color2 = bytes->at(*iter + 1);
                    pixels[pixel_pos] = convert_color(pixel_format, color1, color2);

                    *iter += 2;
                }
            }
            // Palette lookup
            else
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    // Get pixel position
                    Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                    auto color = bytes->at(*iter);
                    pixels[pixel_pos] = pallete_lookup(pixel_format, color, pall);

                    *iter += 1;
                }
            }

            break;

        // Transparent pixels
        case 1:

            for (unsigned int t = x + length; x < t; x++)
            {
                Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                pixels[pixel_pos] = SDL_MapRGBA(pixel_format, 0, 0, 0, 255);
            }

            break;

        // Repeating pixels
        case 2:

            // 15 bit colour
            if (pall == nullptr)
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                    pixels[pixel_pos] = convert_color(pixel_format, (unsigned char)bytes->at(*iter),
                                                      (unsigned char)bytes->at(*iter + 1));
                }

                *iter += 2;
            }
            // Pallette lookup
            else
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                    pixels[pixel_pos] = pallete_lookup(pixel_format, (unsigned char)bytes->at(*iter), pall);
                }

                *iter += 1;
            }

            break;

        // New line
        case 4:
            // Fill rest of line
            for (; x < width; x++)
            {
                Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
                pixels[pixel_pos] = SDL_MapRGBA(pixel_format, 0, 0, 0, 255);
            }

            // New line
            y += 1;
            x = 0;

            break;

        // Should never get here
        default:
            std::cout << "Invalid token (" << token << ") at " << *iter << " length " << length << std::endl;
            return nullptr;
        }
    }

    SDL_UnlockTexture(texture);

    // Return bmp
    return texture;
}

// Load tgx from file
SDL_Texture *TGXParser::load_tgx(const std::string &filename)
{
    // Create file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        return nullptr;
    }

    std::ifstream::pos_type length = file.tellg();

    // Vector to dump file into
    std::vector<unsigned char> bytes(length);

    // Read the file
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(bytes.data()), length);

    // Header
    unsigned int width = bytes.at(0) + 256 * bytes.at(1);
    unsigned int height = bytes.at(4) + 256 * bytes.at(5);

    // Iterator start position
    unsigned int iter = 8;

    // Return new image
    return load_tgx_helper(&bytes, &iter, width, height);
}
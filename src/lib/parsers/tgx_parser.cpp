#include "tgx_parser.h"

#include <SDL2/SDL.h>
#include <fstream>
#include <iostream>

#include "../../core/core.h"

// Convert 15 bit colour to 24 bit
Uint32 convert_color(unsigned char byte1, unsigned char byte2)
{
    // Extract values
    unsigned char r = byte2 >> 2;
    unsigned char g = ((byte1 >> 5) & 0b00000111) | ((byte2 << 3) & 0b00011000);
    unsigned char b = byte1 & 0b00011111;

    // Return new colour
    return 255 | (r << 27) | (g << 19) | (b << 11);
}

// Look up address from pallette
Uint32 pallete_lookup(unsigned char addr, std::vector<unsigned int> *pall)
{
    if (addr < pall->size())
    {
        return (*pall)[addr];
    }

    return 255;
}

// Tgx helper used by file and memory
std::shared_ptr<SDL_Texture> load_tgx_helper(std::vector<unsigned char> *bytes, unsigned int *iter, unsigned int width,
                                             unsigned int height, std::vector<unsigned int> *pall)
{
    // Make bitmap
    auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTexture(oshc::core::renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                                                                  SDL_TEXTUREACCESS_STREAMING, width, height),
                                                SDL_DestroyTexture);

    if (texture == nullptr)
    {
        std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Lock and dump pixels
    Uint32 *pixels = nullptr;
    int pitch = 0;
    if (SDL_LockTexture(texture.get(), nullptr, (void **)&pixels, &pitch))
    {
        std::cout << "Failed to lock texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // File iterator and image x and y
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int y_offset = 0;

    // Parse file
    while (*iter < bytes->size())
    {
        // Close
        if (y >= height)
            break;

        // Extract token and length
        int token = (*bytes)[*iter] >> 5;
        int length = ((*bytes)[*iter] & 0b00011111) + 1;

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
                    Uint32 pixel_pos = y_offset + x;
                    auto color1 = (*bytes)[*iter];
                    auto color2 = (*bytes)[*iter + 1];
                    pixels[pixel_pos] = convert_color(color1, color2);

                    *iter += 2;
                }
            }
            // Palette lookup
            else
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    // Get pixel position
                    Uint32 pixel_pos = y_offset + x;
                    auto color = (*bytes)[*iter];
                    pixels[pixel_pos] = pallete_lookup(color, pall);

                    *iter += 1;
                }
            }

            break;

        // Transparent pixels
        case 1:

            for (unsigned int t = x + length; x < t; x++)
            {
                Uint32 pixel_pos = y_offset + x;
                pixels[pixel_pos] = 255;
            }

            break;

        // Repeating pixels
        case 2:

            // 15 bit colour
            if (pall == nullptr)
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    Uint32 pixel_pos = y_offset + x;
                    pixels[pixel_pos] = convert_color((*bytes)[*iter], (*bytes)[*iter + 1]);
                }

                *iter += 2;
            }
            // Pallette lookup
            else
            {
                for (unsigned int t = x + length; x < t; x++)
                {
                    Uint32 pixel_pos = y_offset + x;
                    pixels[pixel_pos] = pallete_lookup((*bytes)[*iter], pall);
                }

                *iter += 1;
            }

            break;

        // New line
        case 4:
            // Fill rest of line
            for (; x < width; x++)
            {
                Uint32 pixel_pos = y_offset + x;
                pixels[pixel_pos] = 255;
            }

            // New line
            y += 1;
            y_offset = y * (pitch / sizeof(unsigned int));
            x = 0;

            break;

        // Should never get here
        default:
            std::cout << "Invalid token (" << token << ") at " << *iter << " length " << length << std::endl;
            return nullptr;
        }
    }

    SDL_UnlockTexture(texture.get());

    // Return bmp
    return texture;
}

// Load tgx from file
std::shared_ptr<SDL_Texture> load_tgx(const std::string &filename)
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
    unsigned int width = bytes[0] + 256 * bytes[1];
    unsigned int height = bytes[4] + 256 * bytes[5];

    // Iterator start position
    unsigned int iter = 8;

    // Return new image
    auto res = load_tgx_helper(&bytes, &iter, width, height);

    return res;
}
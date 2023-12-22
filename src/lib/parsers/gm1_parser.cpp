#include "gm1_parser.h"

#include <fstream>
#include <iostream>
#include <string>
#include <tracy/Tracy.hpp>
#include <vector>

#include "../../core/core.h"
#include "tgx_parser.h"

constexpr unsigned int GM1_HEADER_SIZE = 88;
constexpr unsigned int GM1_PALLETE_SIZE = 5120;

// Convert 4 chars to int32
unsigned int chars_to_int(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    return a | (b << 8) | (c << 16) | (d << 24);
}

// Load animation
std::shared_ptr<SDL_Texture> load_gm1_animation(std::vector<unsigned char> *bytes, unsigned int *iter,
                                                GM1Data *image_data, std::vector<unsigned int> *pall)
{
    return load_tgx_helper(bytes, iter, image_data->width, image_data->height, pall);
}

// Load tile
std::shared_ptr<SDL_Texture> load_gm1_tile(std::vector<unsigned char> *bytes, unsigned int *iter, GM1Data *image_data)
{
    // File iterator and image x and y
    unsigned int pixels_per_line = 2;
    unsigned int img_size = 256;
    unsigned int x = 14;
    unsigned int y = 0;

    // Make bitmap
    auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTexture(oshc::core::renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                                                                  SDL_TEXTUREACCESS_STREAMING, image_data->width,
                                                                  image_data->height),
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

    // Parse file
    for (unsigned int t = 0; t < img_size; ++t)
    {
        // Break if we go too far
        if (*iter + 1 > bytes->size())
        {
            break;
        }

        // Get pixel position
        Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
        pixels[pixel_pos] = convert_color((*bytes)[*iter], (*bytes)[*iter + 1]);
        ++x;
        *iter += 2;

        if (x > 14 + pixels_per_line / 2)
        {
            if (y < 7)
            {
                pixels_per_line += 4;
            }
            else if (y > 7)
            {
                pixels_per_line -= 4;
            }

            y += 1;
            x = 15 - pixels_per_line / 2;
        }
    }

    SDL_UnlockTexture(texture.get());

    // Return bmp
    return texture;
}

// Load tgx
std::shared_ptr<SDL_Texture> load_gm1_tgx(std::vector<unsigned char> *bytes, unsigned int *iter, GM1Data *image_data)
{
    return load_tgx_helper(bytes, iter, image_data->width, image_data->height);
}

// Load uncompressed
std::shared_ptr<SDL_Texture> load_gm1_uncompressed(std::vector<unsigned char> *bytes, unsigned int *iter,
                                                   GM1Data *image_data)
{
    // File iterator and image x and y
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int img_size = image_data->width * image_data->height;

    // Make bitmap
    auto texture = std::shared_ptr<SDL_Texture>(SDL_CreateTexture(oshc::core::renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                                                                  SDL_TEXTUREACCESS_STREAMING, image_data->width,
                                                                  image_data->height),
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

    // Parse file
    for (unsigned int t = 0; t < img_size; t++)
    {
        // Break if we go too far
        if (*iter + 1 > bytes->size())
            break;

        // Get pixel position
        Uint32 pixel_pos = y * (pitch / sizeof(unsigned int)) + x;
        pixels[pixel_pos] = convert_color((*bytes)[*iter], (*bytes)[*iter + 1]);
        x++;

        if (x == image_data->width)
        {
            y += 1;
            x = 0;
        }

        *iter += 2;
    }

    SDL_UnlockTexture(texture.get());

    // Return bmp
    return texture;
}

// Load gm1 from file
std::vector<std::shared_ptr<SDL_Texture>> load_gm1(const std::string &filename)
{

    // Create file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (!file.is_open())
    {
        return std::vector<std::shared_ptr<SDL_Texture>>();
    }

    FrameMarkStart("Load GM1");

    FrameMarkStart("Load GM1 File");

    std::ifstream::pos_type length = file.tellg();

    // Vector to dump file into
    std::vector<unsigned char> bytes(length);

    // Read the file
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char *>(bytes.data()), length);

    FrameMarkEnd("Load GM1 File");

    // Header
    unsigned int num_pictures = (bytes[13] << 8) | bytes[12];
    unsigned int data_type = bytes[20];

    // Vector to store offsets
    std::vector<GM1Data> image_data;
    image_data.reserve(num_pictures);

    // Return bitmaps
    std::vector<std::shared_ptr<SDL_Texture>> return_bitmaps;
    return_bitmaps.reserve(num_pictures);

    // Create pallette
    std::vector<unsigned int> pall;

    // std::cout << "GM1 Header: " << std::endl;
    // std::cout << "Number of pictures: " << num_pictures << std::endl;
    // std::cout << "Data type: " << data_type << std::endl;

    // Iterator, skip header
    unsigned int i = GM1_HEADER_SIZE;

    // Only animations use pallette
    if (data_type == 2)
    {
        pall.reserve(GM1_PALLETE_SIZE / 2);

        // Load pallete (constant size)
        for (unsigned int t = i; i < t + GM1_PALLETE_SIZE; i += 2)
        {
            pall.push_back(convert_color(bytes[i], bytes[i + 1]));
        }
    }

    // Iterator, skip pallete
    i = GM1_PALLETE_SIZE + GM1_HEADER_SIZE;

    // Create empty image data
    for (unsigned int t = 0; t < num_pictures; t++)
    {
        GM1Data newData;
        newData.index = t;
        image_data.push_back(newData);
    }

    // Get image offset list
    for (unsigned int t = i; i < t + (num_pictures * 4); i += 4)
    {
        image_data.at((i - t) / 4).offset =
            chars_to_int(bytes.at(i), bytes.at(i + 1), bytes.at(i + 2), bytes.at(i + 3));
        // std::cout << "Image " << (i - t) / 4 << " offset: " << image_data.at((i - t) / 4).offset << std::endl;
    }

    // Get image size list
    for (unsigned int t = i; i < t + (num_pictures * 4); i += 4)
    {
        image_data.at((i - t) / 4).size = chars_to_int(bytes.at(i), bytes.at(i + 1), bytes.at(i + 2), bytes.at(i + 3));
        // std::cout << "Image " << (i - t) / 4 << " size: " << image_data.at((i - t) / 4).size << std::endl;
    }

    // Image header
    for (unsigned int t = i; i < t + (num_pictures * 16); i += 16)
    {
        image_data.at((i - t) / 16).width = bytes.at(i) + bytes.at(i + 1) * 256;
        image_data.at((i - t) / 16).height = bytes.at(i + 2) + bytes.at(i + 3) * 256;
        // std::cout << "Image " << (i - t) / 16 << " width: " << image_data.at((i - t) / 16).width
        //           << " height: " << image_data.at((i - t) / 16).height << std::endl;
    }

    // Go through each image
    for (unsigned int t = 0; t < image_data.size(); t++)
    {
        FrameMarkStart("Load GM1 Frame");

        // Image data offset
        unsigned int new_iter = i + image_data[t].offset;
        // std::cout << "Loading image " << image_data.at(t).index << " at " << new_iter << std::endl;

        // Split between many gm1 types
        switch (data_type)
        {
        case 1:
        case 4:
        case 6:
            image_data[t].image = load_gm1_tgx(&bytes, &new_iter, &image_data[t]);
            break;

        case 2:
            image_data[t].image = load_gm1_animation(&bytes, &new_iter, &image_data[t], &pall);
            break;

        case 3:
            image_data[t].image = load_gm1_tile(&bytes, &new_iter, &image_data[t]);
            break;

        case 5:
        case 7:
            image_data[t].image = load_gm1_uncompressed(&bytes, &new_iter, &image_data[t]);
            break;

        default:
            std::cout << "Invalid data type (" << data_type << ")" << std::endl;
            image_data[t].image = nullptr;
        }

        // Add bitmap to return vector
        if (image_data[t].image)
        {
            return_bitmaps.push_back(image_data[t].image);
        }

        FrameMarkEnd("Load GM1 Frame");
    }

    FrameMarkEnd("Load GM1");

    return return_bitmaps;
}
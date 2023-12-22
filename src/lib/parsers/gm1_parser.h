/*
 * GM1Parser
 * Loads gm1 animation from file
 * Allan Legemaate
 * 12/12/2018
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

struct GM1Data
{
    unsigned int index = -1;
    unsigned int size = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int offset = 0;
    std::shared_ptr<SDL_Texture> image = nullptr;
};

// Load tgx from file
std::vector<std::shared_ptr<SDL_Texture>> load_gm1(const std::string &filename);

// Convert 4 chars to int32
unsigned int chars_to_int(unsigned char a, unsigned char b, unsigned char c, unsigned char d);

// Load animation
std::shared_ptr<SDL_Texture> load_gm1_animation(std::vector<unsigned char> *bytes, unsigned int *iter,
                                                GM1Data *image_data, std::vector<unsigned int> *pall);

// Load tile
std::shared_ptr<SDL_Texture> load_gm1_tile(std::vector<unsigned char> *bytes, unsigned int *iter, GM1Data *image_data);

// Load font
std::shared_ptr<SDL_Texture> load_gm1_tgx(std::vector<unsigned char> *bytes, unsigned int *iter, GM1Data *image_data);

// Load uncompressed
std::shared_ptr<SDL_Texture> load_gm1_uncompressed(std::vector<unsigned char> *bytes, unsigned int *iter,
                                                   GM1Data *image_data);

/*
 * GM1Parser
 * Loads tgx image from file
 * Allan Legemaate
 * 12/12/2018
 */

#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include <vector>

// Load tgx from file
std::shared_ptr<SDL_Texture> load_tgx(const std::string &filename);

// Tgx helper used by file and memory
std::shared_ptr<SDL_Texture> load_tgx_helper(std::vector<unsigned char> *bytes, unsigned int *iter, unsigned int width,
                                             unsigned int height, std::vector<unsigned int> *pall = nullptr);

// Convert 15 bit to 24 colour
Uint32 convert_color(unsigned char byte1, unsigned char byte2);

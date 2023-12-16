/*
 * GM1Parser
 * Loads tgx image from file
 * Allan Legemaate
 * 12/12/2018
 */

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

class GM1Parser;

class TGXParser
{
  public:
    // Load tgx from file
    static SDL_Texture *load_tgx(const std::string &filename);

  protected:
    // Tgx helper used by file and memory
    static SDL_Texture *load_tgx_helper(std::vector<unsigned char> *bytes, unsigned int *iter, unsigned int width,
                                        unsigned int height, std::vector<unsigned int> *pall = nullptr);

    // Convert 15 bit to 24 colour
    static Uint32 convert_color(SDL_PixelFormat *pixel_format, unsigned char byte1, unsigned char byte2);

  private:
    // Look up colour from pallete
    static Uint32 pallete_lookup(SDL_PixelFormat *pixel_format, unsigned char addr, std::vector<unsigned int> *pall);

    friend class GM1Parser;
};

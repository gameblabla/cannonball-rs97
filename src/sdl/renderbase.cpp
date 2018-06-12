#include "renderbase.hpp"
#include <iostream>

RenderBase::RenderBase()
{
    surface       = NULL;
    screen_pixels = NULL;

    orig_width  = 320;
    orig_height = 240;
}

// Setup screen size
bool RenderBase::sdl_screen_size()
{
    scn_width  = 320;
    scn_height = 240;

    return true;
}

void RenderBase::convert_palette(uint32_t adr, uint32_t r, uint32_t g, uint32_t b)
{
    adr >>= 1;

    r = (r) * (255 / 31);
    g = (g) * (255 / 31);
    b = (b) * (255 / 31);

	rgb[adr] = ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3);
      
    // Create shadow / highlight colours at end of RGB array
    // The resultant values are the same as MAME
    // 79105
    r = (r * 202) / 256;
    g = (g * 202) / 256;
    b = (b * 202) / 256;
    
    rgb[adr + S16_PALETTE_ENTRIES] = rgb[adr + (S16_PALETTE_ENTRIES * 2)] = ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3);
}

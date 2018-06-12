/***************************************************************************
    SDL Software Video Rendering.  
    
    Known Bugs:
    - Scanlines don't work when Endian changed?

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#include <iostream>

#include "rendersw.hpp"
#include "frontend/config.hpp"

RenderSW::RenderSW()
{
    scan_pixels = NULL;
    pix         = NULL;
}

RenderSW::~RenderSW()
{
    if (scan_pixels) 
        delete[] scan_pixels;

    if (pix)
        delete[] pix;
}

bool RenderSW::init(int src_width, int src_height, 
                    int scale,
                    int video_mode,
                    int scanlines)
{
    this->src_width  = src_width;
    this->src_height = src_height;
    this->video_mode = video_mode;
    this->scanlines  = scanlines;

    // Setup SDL Screen size
    /*if (!RenderBase::sdl_screen_size())
        return false;*/
        
    // --------------------------------------------------------------------------------------------
    // Full Screen Mode
    // When using full-screen mode, we attempt to keep the current resolution.
    // This is because for LCD monitors, I suspect it's what we want to remain in
    // and we don't want to risk upsetting the aspect ratio.
    // --------------------------------------------------------------------------------------------
    this->video_mode = video_settings_t::MODE_WINDOW;
	scale_factor  = 1;

	scn_width  = 320;
	scn_height = 224;

	// As we're windowed this is just the same
	dst_width  = scn_width;
	dst_height = scn_height;
        
	SDL_ShowCursor(false);

    // Frees (Deletes) existing surface
    if (surface)
        SDL_FreeSurface(surface);

    // Set the video mode
    surface = SDL_SetVideoMode(scn_width, scn_height, 16, SDL_HWSURFACE);

    if (!surface)
    {
        std::cerr << "Video mode set failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // This is potentially a larger surface area than the internal pixel array.
    screen_pixels = (uint16_t*)surface->pixels;
    
    // SDL Pixel Format Information
    Rshift = surface->format->Rshift;
    Gshift = surface->format->Gshift;
    Bshift = surface->format->Bshift;
    Rmask  = surface->format->Rmask;
    Gmask  = surface->format->Gmask;
    Bmask  = surface->format->Bmask;

    if (pix)
        delete[] pix;
    pix = new uint16_t[src_width * src_height];

    return true;
}

void RenderSW::disable()
{

}

bool RenderSW::start_frame()
{
    return !(SDL_MUSTLOCK(surface) && SDL_LockSurface(surface) < 0);
}

bool RenderSW::finalize_frame()
{
    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    SDL_Flip(surface);

    return true;
}


void RenderSW::draw_frame(uint16_t* pixels)
{
    uint16_t* spix = screen_pixels;
    for (int i = 0; i < (src_width * src_height); i++)
    {
		*(spix++) = rgb[*(pixels++) & ((S16_PALETTE_ENTRIES * 3) - 1)]; 
	}   
}

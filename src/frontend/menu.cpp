/***************************************************************************
    Front End Menu System.

    This file is part of Cannonball. 
    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

// Boost string prediction

#include "main.hpp"
#include "menu.hpp"
#include "setup.hpp"
#include "../utils.hpp"


#include "engine/ohud.hpp"
#include "engine/oinputs.hpp"
#include "engine/osprites.hpp"
#include "engine/ologo.hpp"
#include "engine/opalette.hpp"
#include "engine/otiles.hpp"

#include "frontend/ttrial.hpp"

// Logo Y Position
const static int16_t LOGO_Y = -60;

// Columns and rows available
const static uint16_t COLS = 40;
const static uint16_t ROWS = 28;

// Horizon Destination Position
const static uint16_t HORIZON_DEST = 0x3A0;

void start_game(int mode, int settings);


Menu::Menu(Interface* cannonboard)
{
    ttrial  = new TTrial(config.ttrial.best_times);
}


Menu::~Menu(void)
{
    delete cabdiag;
    delete ttrial;
}

void Menu::populate()
{
}

void Menu::init()
{   
    state = STATE_MENU;
    start_game(Outrun::MODE_ORIGINAL,0);
}


bool check_jap_roms()
{
    if (config.engine.jap && !roms.load_japanese_roms())
    {
        printf("JAPANESE ROMSET NOT FOUND\n");
        return false;
    }
    return true;
}

// Reinitalize Video, and stop audio to avoid crackles
void restart_video()
{
    #ifdef COMPILE_SOUND_CODE
    if (config.sound.enabled)
        cannonball::audio.stop_audio();
    #endif
    video.disable();
    video.init(&roms, &config.video);
    #ifdef COMPILE_SOUND_CODE
    osoundint.init();
    if (config.sound.enabled)
        cannonball::audio.start_audio();
    #endif
}

void start_game(int mode, int settings)
{
    // Enhanced Settings
    if (settings == 1)
    {
        if (!config.video.hires)
        {
            if (config.video.scale > 1)
                config.video.scale >>= 1;
        }

        if (!config.sound.fix_samples)
        {
            if (roms.load_pcm_rom(true))
                config.sound.fix_samples = 1;
        }

        config.set_fps(config.video.fps = 2);
        config.video.widescreen     = 1;
        config.video.hires          = 1;
        config.engine.level_objects = 1;
        config.engine.new_attract   = 1;
        config.engine.fix_bugs      = 1;
        config.sound.preview        = 1;

        restart_video();
    }
    // Original Settings
    else if (settings == 2)
    {
        if (config.video.hires)
        {
            config.video.scale <<= 1;
        }

        if (config.sound.fix_samples)
        {
            if (roms.load_pcm_rom(false))
                config.sound.fix_samples = 0;
        }

        config.set_fps(config.video.fps = 1);
        config.video.widescreen     = 0;
        config.video.hires          = 0;
        config.engine.level_objects = 0;
        config.engine.new_attract   = 0;
        config.engine.fix_bugs      = 0;
        config.sound.preview        = 0;

        restart_video();
    }
    // Otherwise, use whatever is already setup...
    else
    {
        config.engine.fix_bugs = config.engine.fix_bugs_backup;
    }

    if (check_jap_roms())
    {
        outrun.cannonball_mode = mode;
        cannonball::state = cannonball::STATE_INIT_GAME;
        osoundint.queue_clear();
    }
}

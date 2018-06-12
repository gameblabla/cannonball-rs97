/***************************************************************************
    XML Configuration File Handling.

    Load Settings.
    Load & Save Hi-Scores.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#include <iostream>

#include "main.hpp"
#include "config.hpp"
#include "globals.hpp"
#include "setup.hpp"
#include "../utils.hpp"

#include "engine/ohiscore.hpp"
#include "engine/audio/osoundint.hpp"

Config config;

Config::Config(void)
{

}


Config::~Config(void)
{
}

void Config::init()
{

}

/*
 * UP : 273
 * DOWN : 274
 * LEFT : 276
 * RIGHT : 275
 * ALT : 308
 * SPACE : 32
 * LCTRL : 306
 * SPACE : 32
 * TAB : 9
 * BACKSPACE : 8
 * LEFT SHIFT : 304
 * RETURN : 13
 * */

void Config::load(const std::string &filename)
{
	set_fps(0);
	config.sound.enabled = 1;
	config.controls.keyconfig[0] = 273;
	config.controls.keyconfig[1] = 274;
	config.controls.keyconfig[2] = 276;
	config.controls.keyconfig[3] = 275;
	
	config.controls.keyconfig[4] = 306;
	config.controls.keyconfig[5] = 308;
	config.controls.keyconfig[6] = 9;
	config.controls.keyconfig[7] = 8;
	
	config.controls.keyconfig[8] = 13;
	config.controls.keyconfig[9] = 32;
	config.controls.keyconfig[10] = 27;
    controls.pad_id        = 0;
    controls.axis[0]       = 0;
    controls.axis[1]       = 2;
    controls.axis[2]       = 3;
    controls.asettings[0]  = 75;
    controls.asettings[1]  = 0;
    controls.asettings[2]  = 0;
    
    engine.level_objects   = 1;
    engine.randomgen       = 1;
    engine.fix_bugs_backup = 0;
    engine.fix_bugs        = 1;
    engine.fix_timer       = 1;
    engine.layout_debug    = 0;
    engine.new_attract     = 0;
    
    ttrial.laps    = 5;
    ttrial.traffic = 3;
    cont_traffic   = 3;
    
    controls.gear          = 0;
    controls.steer_speed   = 3;
    controls.pedal_speed   = 4;
	
	config.controls.analog = 0;
}

bool Config::save(const std::string &filename)
{

    return true;
}

void Config::load_scores(const std::string &filename)
{
 
}

void Config::save_scores(const std::string &filename)
{
  
}

void Config::load_tiletrial_scores()
{
}

void Config::save_tiletrial_scores()
{
}

bool Config::clear_scores()
{
    return 0;
}

void Config::set_fps(int fps)
{
    video.fps = fps;
    // Set core FPS to 30fps or 60fps
    this->fps = video.fps == 0 ? 30 : 60;
    
    // Original game ticks sprites at 30fps but background scroll at 60fps
    tick_fps  = video.fps < 2 ? 30 : 60;

    cannonball::frame_ms = 1000.0 / this->fps;

    #ifdef COMPILE_SOUND_CODE
    if (config.sound.enabled)
        cannonball::audio.stop_audio();
    osoundint.init();
    if (config.sound.enabled)
        cannonball::audio.start_audio();
    #endif
}

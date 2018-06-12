/***************************************************************************
    SDL Based Input Handling.

    Populates keys array with user input.
    If porting to a non-SDL platform, you would need to replace this class.

    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#include <iostream>
#include <cstdlib> // abs
#include "sdl/input.hpp"

int CENTRE = 0x80;
// Digital Dead Zone
int DIGITAL_DEAD = 3200;

Input input;

Input::Input(void)
{
}

Input::~Input(void)
{
}

void Input::init(int pad_id, int* key_config, int* pad_config, int analog, int* axis, int* analog_settings)
{
    this->key_config  = key_config;
    this->pad_config  = pad_config;
    this->analog      = analog;
    this->axis        = axis;
    this->wheel_zone  = analog_settings[0];
    this->wheel_dead  = analog_settings[1];
    this->pedals_dead = analog_settings[2];

    gamepad = 1;

    a_wheel = CENTRE;
}

void Input::close()
{
}

// Detect whether a key press change has occurred
bool Input::has_pressed(presses p)
{
    return keys[p] && !keys_old[p];
}

// Detect whether key is still pressed
bool Input::is_pressed(presses p)
{
    return keys[p];
}

// Detect whether pressed and clear the press
bool Input::is_pressed_clear(presses p)
{
    bool pressed = keys[p];
    keys[p] = false;
    return pressed;
}

// Denote that a frame has been done by copying key presses into previous array
void Input::frame_done()
{
    memcpy(&keys_old, &keys, sizeof(keys));
}

void Input::handle_key_down(SDL_keysym* keysym)
{
    key_press = keysym->sym;
    handle_key(key_press, true);
}

void Input::handle_key_up(SDL_keysym* keysym)
{
    handle_key(keysym->sym, false);
}
void Input::handle_key(const int key, const bool is_pressed)
{
    // Redefinable Key Input
    if (key == key_config[0])
        keys[UP] = is_pressed;

    else if (key == key_config[1])
        keys[DOWN] = is_pressed;

    else if (key == key_config[2])
        keys[LEFT] = is_pressed;

    else if (key == key_config[3])
        keys[RIGHT] = is_pressed;

    if (key == key_config[4])
        keys[ACCEL] = is_pressed;

    if (key == key_config[5])
        keys[BRAKE] = is_pressed;

    if (key == key_config[6])
        keys[GEAR1] = is_pressed;

    if (key == key_config[7])
        keys[GEAR2] = is_pressed;

    if (key == key_config[8])
        keys[START] = is_pressed;

    if (key == key_config[9])
        keys[COIN] = is_pressed;

    if (key == key_config[10])
        keys[MENU] = is_pressed;

    if (key == key_config[11])
        keys[VIEWPOINT] = is_pressed;

    // Function keys are not redefinable
    switch (key)
    {
        case SDLK_F1:
            keys[PAUSE] = is_pressed;
            break;

        case SDLK_F2:
            keys[STEP] = is_pressed;
            break;

        case SDLK_F3:
            keys[TIMER] = is_pressed;
            break;

        case SDLK_F5:
            keys[MENU] = is_pressed;
            break;
    }
}

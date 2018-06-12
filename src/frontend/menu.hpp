/***************************************************************************
    Front End Menu System.

    This file is part of Cannonball. 
    Copyright Chris White.
    See license.txt for more details.
***************************************************************************/

#pragma once

#include <vector>
#include "stdint.hpp"

class Interface;
class CabDiag;
class TTrial;
struct Packet;

class Menu
{
public:
    Menu(Interface* cannonboard);
    ~Menu(void);

    void populate();
    void init();
    void tick(Packet* packet);

private:
    Interface* cannonboard;
    CabDiag* cabdiag;

    // Menu state
    uint8_t state;

    enum
    {
        STATE_MENU,
        STATE_REDEFINE_KEYS,
        STATE_REDEFINE_JOY,
        STATE_TTRIAL,
        STATE_DIAGNOSTICS,
    };

    TTrial* ttrial;

    // Redefine keys/joystick substate
    uint8_t redef_state;

    uint32_t frame;

    // Counter for showing messages
    int32_t message_counter;

    // Number of seconds to show message for
    const static int32_t MESSAGE_TIME = 5;
    
    
    // Cursor
    int16_t cursor;

    // Stores whether this is a textual menu (i.e. no options that can be chosen)
    bool is_text_menu;

    // Used to control the horizon pan effect
    uint16_t horizon_pos;
    
    void tick_ui();
    void draw_menu_options();
    void tick_menu();
};

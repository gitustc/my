/*
 * =====================================================================================
 *
 *       Filename: ./sdlib/event.cpp
 *        Created: 06/04/2014 05:09:17 PM
 *  Last Modified: 06/05/2014 06:06:03 PM
 *
 *    Description: event
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#include "./event.hpp"
#include <cstdint>
#include <SDL2/SDL.h>

int sdlib::poll_event(sdlib::event *event)
{
    return SDL_PollEvent(&(event->m_event));
}

sdlib::event::event()
{
    memset(&m_event, 0, sizeof(SDL_Event));
}

sdlib::event::~event()
{
    memset(&m_event, 0, sizeof(SDL_Event));
}

uint32_t sdlib::event::type()
{
    return m_event.type;
}

int32_t sdlib::event::key_name()
{
    return m_event.key.keysym.sym;
}

uint8_t sdlib::event::key_state()
{
    return m_event.key.state;
}

bool sdlib::event::key_repeat()
{
    return (bool)m_event.key.repeat;
}

bool sdlib::event::mouse_motion_state(uint8_t btn)
{
    return (bool)(m_event.motion.state & SDL_BUTTON(btn));
}

int32_t sdlib::event::mouse_motion_x()
{
    return m_event.motion.x;
}

int32_t sdlib::event::mouse_motion_y()
{
    return m_event.motion.y;
}

uint8_t sdlib::event::mouse_button_name()
{
    return m_event.button.button;
}

bool sdlib::event::mouse_button_state(uint8_t)
{
    return m_event.button.state;
}

int32_t sdlib::event::mouse_button_x()
{
    return m_event.button.x;
}

int32_t sdlib::event::mouse_button_y()
{
    return m_event.button.y;
}

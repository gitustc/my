/*
 * =====================================================================================
 *
 *       Filename: sdlib/event.hpp
 *        Created: 06/04/2014 05:09:17 PM
 *  Last Modified: 06/06/2014 08:41:54 PM
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

#ifndef  _included_event_inc__
#define  _included_event_inc__

#include <cstdint>
#include <SDL2/SDL.h>

namespace sdlib{

    class event;

    int poll_event(event *);

    class event{
        friend int poll_event(event *);
        public:
        enum{
            KEYUP           = SDL_KEYUP,
            KEYDOWN         = SDL_KEYDOWN,
            MOUSEMOTION     = SDL_MOUSEMOTION,
            MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN,
            MOUSEBUTTONUP   = SDL_MOUSEBUTTONUP,
        };
        enum{

            KEY_0       =   SDLK_0,
            KEY_9       =   SDLK_9,

            KEY_A       =   SDLK_a,
            KEY_Q       =   SDLK_q,
            KEY_Z       =   SDLK_z,

            KEY_UP      =   SDLK_UP,
            KEY_DOWN    =   SDLK_DOWN,
            KEY_LEFT    =   SDLK_LEFT,
            KEY_RIGHT   =   SDLK_RIGHT,
        };
        enum{
            BUTTON_LEFT    = SDL_BUTTON_LEFT,
            BUTTON_L       = SDL_BUTTON_LEFT,
            BUTTON_MIDDLE  = SDL_BUTTON_MIDDLE,
            BUTTON_M       = SDL_BUTTON_MIDDLE,
            BUTTON_RIGHT   = SDL_BUTTON_RIGHT,
            BUTTON_R       = SDL_BUTTON_RIGHT,
        };

        enum{
            PRESSED     = SDL_PRESSED,
            RELEASED    = SDL_RELEASED,
        };

        public:
        event();
        ~event();

        public:
        uint32_t type();

        public:
        int32_t  key_name();
        uint8_t  key_state();
        bool     key_repeat();

        public:
        bool        mouse_motion_state(uint8_t);
        int32_t     mouse_motion_x();
        int32_t     mouse_motion_y();

        public:
        uint8_t     mouse_button_name();
        bool        mouse_button_state(uint8_t);
        bool        mouse_button_double_click();
        int32_t     mouse_button_x();
        int32_t     mouse_button_y();

        private:
        SDL_Event   m_event;

    };
};

#endif

/*
 * =====================================================================================
 *
 *       Filename: sdlib.cpp
 *        Created: 06/01/2014 06:48:28 PM
 *  Last Modified: 06/04/2014 05:01:37 PM
 *
 *    Description: 
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

#include "sdlib.hpp"

int sdlib::init()
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS);
    sdlib::graphics::init();
    sdlib::font::init();
    return 0;
}


int sdlib::delay(int ms)
{
    SDL_Delay(ms);
    return 0;
}

uint32_t sdlib::time()
{
    return SDL_GetTicks();
}

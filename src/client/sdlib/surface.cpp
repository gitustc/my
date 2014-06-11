/*
 * =====================================================================================
 *
 *       Filename: surface.cpp
 *        Created: 06/01/2014 06:53:47 PM
 *  Last Modified: 06/02/2014 07:41:48 PM
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

#include <cstdint>
#include "surface.hpp"

sdlib::surface::surface(SDL_Surface *surf)
{
    m_surf = surf;
}

sdlib::surface::~surface()
{
    if(m_surf){
        SDL_FreeSurface(m_surf);
    }
}

int sdlib::surface::width()
{
    return m_surf->w;
}

int sdlib::surface::height()
{
    return m_surf->h;
}

SDL_Surface *sdlib::surface::surptr()
{
    return m_surf;
}

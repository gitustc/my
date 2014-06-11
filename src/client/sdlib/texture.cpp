/*
 * =====================================================================================
 *
 *       Filename: sdlib/texture.cpp
 *        Created: 06/01/2014 07:57:42 PM
 *  Last Modified: 06/05/2014 08:36:02 PM
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
#include "./texture.hpp"

sdlib::texture::texture(SDL_Texture *p)
{
    m_tex = p;
    SDL_SetTextureBlendMode(m_tex, SDL_BLENDMODE_BLEND);
}
sdlib::texture::~texture()
{
    SDL_DestroyTexture(m_tex);
}

SDL_Texture *sdlib::texture::texptr()
{
    return m_tex;
}

int sdlib::texture::width()
{
    int w;
    SDL_QueryTexture(m_tex, nullptr, nullptr, &w, nullptr);
    return w;
}

int sdlib::texture::height()
{
    int h;
    SDL_QueryTexture(m_tex, nullptr, nullptr, nullptr, &h);
    return h;
}

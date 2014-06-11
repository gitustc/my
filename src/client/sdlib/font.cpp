/*
 * =====================================================================================
 *
 *       Filename: sdlib/font.cpp
 *        Created: 06/02/2014 04:55:16 PM
 *  Last Modified: 06/06/2014 08:13:48 PM
 *
 *    Description: ttf
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

#include "./font.hpp"
#include "./surface.hpp"
#include <SDL2/SDL_ttf.h>

static sdlib::font *g_font;
sdlib::font::font()
{
    m_font       = nullptr;
    m_initialize = false;
}

sdlib::font::~font()
{
    TTF_CloseFont(m_font);
    TTF_Quit();
}

int sdlib::font::init()
{
    static sdlib::font s_font;
    g_font = &s_font;
    if(!g_font->m_initialize){
        if(TTF_Init() == -1){
            printf("init font library failed...\n");
            return 1;
        }
        g_font->m_font = TTF_OpenFont("./res/test.ttf", 14);
        if(!g_font->m_font){
            printf("open font file failed...\n");
            return 1;
        }
        g_font->m_initialize = true;
    }
    return 0;
}

sdlib::surface *sdlib::font::write(const char * info, sdlib::color fc)
{
    return (new sdlib::surface(TTF_RenderUTF8_Blended(g_font->m_font, info, fc)));
}


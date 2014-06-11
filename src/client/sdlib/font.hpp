/*
 * =====================================================================================
 *
 *       Filename: font.hpp
 *        Created: 06/02/2014 04:55:16 PM
 *  Last Modified: 06/02/2014 07:19:58 PM
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



#ifndef  _included_font_inc__
#define  _included_font_inc__

#include "./color.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


namespace sdlib{
    class surface;
    class font{
        private:
            font();
            virtual ~font();
        public:
            static int init();
            static int free();
        public:
            static sdlib::surface *write(const char *, sdlib::color);
        private:
            TTF_Font    *m_font;
            bool        m_initialize;
    };
};

#endif

/*
 * =====================================================================================
 *
 *       Filename: texture.hpp
 *        Created: 06/01/2014 07:02:35 PM
 *  Last Modified: 06/02/2014 07:10:08 PM
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

#ifndef  _included_texture_inc__
#define  _included_texture_inc__

#include <SDL2/SDL.h>
#include "./bitmap.hpp"
#include "graphics.hpp"

namespace sdlib{
    class texture{
        friend class graphics;
        private:
            texture(SDL_Texture *);
            texture(sdlib::bitmap *);
        public:
            int         width();
            int         height();
        public:
            SDL_Texture *texptr();
        private:
            SDL_Texture *m_tex;
        public:
            virtual ~texture();
    };
};

#endif

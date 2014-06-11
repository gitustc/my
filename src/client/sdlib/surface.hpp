/*
 * =====================================================================================
 *
 *       Filename: surface.hpp
 *        Created: 06/01/2014 06:53:43 PM
 *  Last Modified: 06/02/2014 07:40:34 PM
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


#ifndef  _included_surface_inc__
#define  _included_surface_inc__

#include <SDL2/SDL.h>
#include "./font.hpp"

namespace sdlib{
    class surface{

        friend class font;
        private:
            surface(SDL_Surface *);
        public:
            virtual ~surface();
        public:
            int  width();
            int  height();

            SDL_Surface *surptr();

        private:
            SDL_Surface *m_surf;
    };
};


#endif

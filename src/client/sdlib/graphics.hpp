/*
 * =====================================================================================
 *
 *       Filename: sdlib/graphics.hpp
 *        Created: 05/31/2014 05:41:03 PM
 *  Last Modified: 06/06/2014 06:36:11 PM
 *
 *    Description: singleton for graphics
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


#ifndef  _included_graphics_inc__
#define  _included_graphics_inc__

#include <stack>
#include <cstdint>
#include <SDL2/SDL.h>
#include "./bitmap.hpp"
#include "./surface.hpp"


namespace sdlib{

    class texture;

    class graphics{
        public:
            static int init();
            static int free();
        public:
            static sdlib::texture *create(sdlib::bitmap *);
            static sdlib::texture *create(sdlib::surface *);

            static int update(sdlib::texture *, sdlib::bitmap *);
            static int update(sdlib::texture *, sdlib::surface *);
        public:
            static int clear();
            static int present();
        public:
            static int set_color(uint8_t, uint8_t, uint8_t, uint8_t);
            static int unset_color();
        public:
            // blit at (x, y) with the size of texture
            static int blit(sdlib::texture *, int, int);
            // blit at (x, y) with given size
            // when scale is true, scale it to occupy the full region
            // otherwise locate at the center
            static int blit(sdlib::texture *, int, int, int, int, bool);
        public:
            static int draw_rect(int, int, int, int);
        public:
            static int window_width();
            static int window_height();
        private:
            graphics();
            virtual ~graphics();

        private:
            int     m_window_width;
            int     m_window_height;
            bool    m_initialize;
            bool    m_fullscreen;
        private:
            std::stack<SDL_Color>   m_color_stack;
        private:
            SDL_Renderer    *m_renderer;
            SDL_Window      *m_window;
    };

};

#endif

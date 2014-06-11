/*
 * =====================================================================================
 *
 *       Filename: sdlib/graphics.cpp
 *        Created: 05/31/2014 05:41:03 PM
 *  Last Modified: 06/06/2014 06:36:52 PM
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

#include <SDL2/SDL.h>
#include "./graphics.hpp"
#include "./texture.hpp"

static sdlib::graphics *g_graphics;

sdlib::graphics::graphics()
{
    m_window_width      = 800;
    m_window_height     = 600;
    // m_window_width      = 640;
    // m_window_height     = 480;
    m_fullscreen = false;
    m_initialize = false;
}

sdlib::graphics::~graphics()
{
    if(m_initialize){
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
    }
}

int sdlib::graphics::init()
{
    static sdlib::graphics s_graphics;

    g_graphics = &s_graphics;
    if(!g_graphics->m_initialize){
        g_graphics->m_window   = SDL_CreateWindow("Mir2EI", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, g_graphics->m_window_width, g_graphics->m_window_height, 0);
        g_graphics->m_renderer = SDL_CreateRenderer(g_graphics->m_window, -1, 0);
        
        g_graphics->set_color(0, 0, 0, 0);

        if(g_graphics->m_fullscreen){
            SDL_SetWindowFullscreen(g_graphics->m_window, SDL_WINDOW_FULLSCREEN|SDL_WINDOW_OPENGL);
        }else{
            SDL_SetWindowFullscreen(g_graphics->m_window, SDL_WINDOW_OPENGL);
        }
        g_graphics->m_initialize = true;
    }
    return 0;
}



sdlib::texture *sdlib::graphics::create(sdlib::bitmap *bitmap)
    // sdlib::texture *sdlib::graphics::create(const sdlib::bitmap *bitmap)
{
    if(bitmap){
        SDL_Texture *tex = SDL_CreateTexture(g_graphics->m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, bitmap->width(), bitmap->height());
        SDL_UpdateTexture(tex, NULL, (uint32_t *)bitmap->buffer(), bitmap->width()*sizeof(uint32_t));
        return (new sdlib::texture(tex));
    }else{
        return nullptr;
    }
}


sdlib::texture *sdlib::graphics::create(sdlib::surface *surface)
    // sdlib::texture *sdlib::graphics::create(const sdlib::surface *surface)
{
    if(surface){
        return (new sdlib::texture(SDL_CreateTextureFromSurface(g_graphics->m_renderer, surface->surptr())));
    }else{
        return nullptr;
    }
}

int sdlib::graphics::update(sdlib::texture *tex, sdlib::bitmap *bitmap)
{
    // TODO check the size for matching
    SDL_UpdateTexture(tex->texptr(), NULL, (uint32_t *)bitmap->buffer(), bitmap->width()*sizeof(uint32_t));
    return 0;
}

int sdlib::graphics::update(sdlib::texture *tex, sdlib::surface *surface)
{
    // TODO check the size for matching
    SDL_Surface *surf = surface->surptr();
    int w = surface->width();
    int needlock = SDL_MUSTLOCK(surf);

    if(needlock){
        SDL_LockSurface(surf);
    }
    SDL_UpdateTexture(tex->texptr(), NULL, surf->pixels, w*sizeof(uint32_t));
    if(needlock){
        SDL_UnlockSurface(surf);
    }
    return 0;
}

int sdlib::graphics::clear()
{
    SDL_RenderClear(g_graphics->m_renderer);
    return 0;
}

int sdlib::graphics::present()
{
    SDL_RenderPresent(g_graphics->m_renderer);
    return 0;
}

int sdlib::graphics::blit(sdlib::texture *tex, int dx, int dy)
{
    return blit(tex, dx, dy, tex->width(), tex->height(), true);
}

int sdlib::graphics::blit(sdlib::texture *tex, int dx, int dy, int dwidth, int dheight, bool scale)
{
    SDL_Rect    src_rect;
    SDL_Rect    dst_rect;

    if(scale){
        src_rect.x = 0;
        src_rect.y = 0;
        src_rect.w = tex->width();
        src_rect.h = tex->height();

        dst_rect.x = dx;
        dst_rect.y = dy;
        dst_rect.w = dwidth;
        dst_rect.h = dheight;
    }else{
        if(dwidth >= tex->width()){
            src_rect.x = 0;
            src_rect.w = tex->width();
            dst_rect.x = dx + (dwidth - tex->width())/2;
            dst_rect.w = tex->width();
        }else{
            src_rect.x = (tex->width() - dwidth)/2;
            src_rect.w = dwidth;
            dst_rect.x = dx;
            dst_rect.w = dwidth;
        }
        if(dheight >= tex->height()){
            src_rect.y = 0;
            src_rect.h = tex->height();
            dst_rect.y = dy + (dheight - tex->height())/2;
            dst_rect.h = tex->height();
        }else{
            src_rect.y = (tex->height() - dheight)/2;
            src_rect.h = dheight;
            dst_rect.y = dy;
            dst_rect.h = dheight;
        }
    }

    SDL_RenderCopy(g_graphics->m_renderer, tex->texptr(), &src_rect, &dst_rect);
    return 0;
}

int sdlib::graphics::window_width()
{
    return g_graphics->m_window_width;
}

int sdlib::graphics::window_height()
{
    return g_graphics->m_window_height;
}

int sdlib::graphics::draw_rect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return SDL_RenderDrawRect(g_graphics->m_renderer, &rect);
}

int sdlib::graphics::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_Color color = {r, g, b, a};
    g_graphics->m_color_stack.push(color);
    return SDL_SetRenderDrawColor(g_graphics->m_renderer, color.r, color.g, color.b, color.a);
}

int sdlib::graphics::unset_color()
{
    g_graphics->m_color_stack.pop();
    return SDL_SetRenderDrawColor(g_graphics->m_renderer,
            g_graphics->m_color_stack.top().r,
            g_graphics->m_color_stack.top().g,
            g_graphics->m_color_stack.top().b,
            g_graphics->m_color_stack.top().a);
}


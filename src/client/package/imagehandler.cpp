/*
 * =====================================================================================
 *
 *       Filename: package/imagehandler.cpp
 *        Created: 05/31/2014 05:41:03 PM
 *  Last Modified: 06/08/2014 05:29:00 PM
 *
 *    Description: singleton for imagehandler
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

#include <iostream>
#include <cstdio>
#include <SDL2/SDL.h>
#include "./imagepackage.hpp"
#include "./imagehandler.hpp"

static package::image  *g_imagehandler;

package::image::image()
{
    m_initialize = false;
}

package::image::~image()
{
}


int package::image::init()
{
    static package::image s_imagehandler;
    g_imagehandler = &s_imagehandler;
    if(!(g_imagehandler->m_initialize)){
        const char *file_list[] = {
            "../../../mir2ei_data/tilesc.wil",           //0
            "../../../mir2ei_data/tiles30c.wil",         //1
            "../../../mir2ei_data/tiles5c.wil",          //2
            "../../../mir2ei_data/smtilesc.wil",         //3
            "../../../mir2ei_data/housesc.wil",          //4
            "../../../mir2ei_data/cliffsc.wil",          //5
            "../../../mir2ei_data/dungeonsc.wil",        //6
            "../../../mir2ei_data/innersc.wil",          //7
            "../../../mir2ei_data/furnituresc.wil",      //8
            "../../../mir2ei_data/wallsc.wil",           //9
            "../../../mir2ei_data/smobjectsc.wil",       //10
            "../../../mir2ei_data/animationsc.wil",      //11
            "../../../mir2ei_data/object1c.wil",         //12
            "../../../mir2ei_data/object2c.wil",         //13
            "../../../mir2ei_data/interface1c.wil",      //14
            nullptr
        };
        int current_file_index = 0;
        while(file_list[current_file_index] != nullptr){
            // (g_imagehandler->m_images).push_back(package::imagepackage());
            (g_imagehandler->m_images).emplace_back(
                    std::shared_ptr<package::imagepackage>(new package::imagepackage));
            printf("vector size = %d\n", g_imagehandler->m_images.size());
            (g_imagehandler->m_images[current_file_index])->load(file_list[current_file_index]);
            current_file_index++;
        }
        g_imagehandler->m_initialize = true;
    }
    return 0;
}


sdlib::bitmap *package::image::retrieve(uint8_t pre, uint8_t fid, uint16_t index, uint8_t alpha)
{
    int fvid = pre+fid;
    g_imagehandler->m_images[fvid]->set_index(index);
    int w = (g_imagehandler->m_images[fvid])->width();
    int h = (g_imagehandler->m_images[fvid])->height();

    sdlib::bitmap *tmp = new sdlib::bitmap(w, h);
    blit(pre, fid, index, tmp->buffer(), 0, 0, w, h, 4, 0, 0, alpha);
    return tmp;
}


int package::image::blit(
        uint8_t pre, uint8_t fid, uint16_t index,       // index for image
        void *dstptr,                                   // buffer
        int dx, int dy,                                 // corresponding point
        int dwidth, int dheight,                        // buffer size
        int dpixsize,                                   // 4 for uint32_t
        uint32_t mask1, uint32_t mask2, uint8_t alpha)  // masks
{
    int fid1d = pre + fid;
    return g_imagehandler->m_images[fid1d]->decompress(index, dstptr, dx, dy, dwidth, dheight, dpixsize, mask1, mask2, alpha);
}

/*
 * =====================================================================================
 *
 *       Filename: sdlib/bitmap.cpp
 *        Created: 06/01/2014 06:53:47 PM
 *  Last Modified: 06/05/2014 08:29:52 PM
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

#include <cstdlib>
#include <cstdint>
#include "./bitmap.hpp"
#include <cstring>

sdlib::bitmap::bitmap()
{
    m_length = 0;
    m_width  = 0;
    m_height = 0;
    m_buffer = nullptr;
}

sdlib::bitmap::bitmap(int width, int height)
{
    m_width  = width;
    m_height = height;
    m_length = width * height;
    m_buffer = malloc(width * height * sizeof(uint32_t));
    memset(m_buffer, 0, m_width*m_height*sizeof(uint32_t));
}

sdlib::bitmap::~bitmap()
{
    if(m_buffer){
        free(m_buffer);
    }
}

int sdlib::bitmap::resize(int w, int h)
{
    if(m_buffer){
        if(m_length < w * h){
            free(m_buffer);
            m_buffer = malloc(w * h * sizeof(uint32_t));
            m_length = w * h;
        }
    }else{
        m_buffer = malloc(w * h * sizeof(uint32_t));
        m_length = w * h;
    }
    m_width  = w;
    m_height = h;
    memset(m_buffer, 0, m_width*m_height*sizeof(uint32_t));

    return 0;
}

int sdlib::bitmap::width()
{
    return m_width;
}

int sdlib::bitmap::height()
{
    return m_height;
}

void *sdlib::bitmap::buffer()
{
    return m_buffer;
}

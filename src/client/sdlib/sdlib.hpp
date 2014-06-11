/*
 * =====================================================================================
 *
 *       Filename: ../sdlib/sdlib.hpp
 *        Created: 06/01/2014 06:48:23 PM
 *  Last Modified: 06/04/2014 05:09:03 PM
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


#ifndef  _included_sdlib_inc__
#define  _included_sdlib_inc__


#include "./bitmap.hpp"
#include "./font.hpp"
#include "./graphics.hpp"
#include "./sdlib.hpp"
#include "./surface.hpp"
#include "./texture.hpp"
#include "./event.hpp"

namespace sdlib{
    int init();
    int free();

    int      delay(int);
    uint32_t time();
};


#endif

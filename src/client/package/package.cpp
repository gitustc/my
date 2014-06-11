/*
 * =====================================================================================
 *
 *       Filename: package.cpp
 *        Created: 06/01/2014 06:46:53 PM
 *  Last Modified: 06/02/2014 08:42:46 PM
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

#include "package.hpp"

int package::init()
{
    package::image::init();
    return 0;
}

int package::free()
{
    return 0;
}


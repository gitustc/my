/*
 * =====================================================================================
 *
 *       Filename: process/process.cpp
 *        Created: 06/04/2014 07:57:15 PM
 *  Last Modified: 06/05/2014 11:32:24 AM
 *
 *    Description: process
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

#include "./process.hpp"

my::process::base::base()
{
    m_state = my::process::QUIT;
}

my::process::base::~base()
{
}

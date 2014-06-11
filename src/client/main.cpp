/*
 * =====================================================================================
 *
 *       Filename: main.cpp
 *        Created: 06/01/2014 03:34:59 PM
 *  Last Modified: 06/10/2014 06:56:41 PM
 *
 *    Description: entry
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
#include <memory>
#include "./package/package.hpp"
#include "./sdlib/sdlib.hpp"
#include "client.hpp"

int main()
{

    my::client  client;

    client.start();

    return 0;
}

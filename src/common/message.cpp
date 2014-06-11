/*
 * =====================================================================================
 *
 *       Filename: ../../common/message.cpp
 *        Created: 06/07/2014 10:31:59 AM
 *  Last Modified: 06/07/2014 10:23:27 PM
 *
 *    Description: message
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
#include <algorithm>
#include <cstring>
#include "./message.hpp"

my::message::message()
{
    set(my::message::NONE);
}

my::message::message(uint16_t type)
{
    set(type);
}

my::message::message(uint16_t type, const void * info)
{
    set(type, info);
}

my::message::message(uint16_t type, uint16_t len, const void * info)
{
    set(type, len, info);
}

uint16_t my::message::type()
{
    return *((uint16_t *)(m_info+0));
}

uint16_t my::message::length()
{
    return *((uint16_t *)(m_info+2));
}
uint8_t *my::message::data()
{
    return m_info;
}
uint8_t *my::message::body()
{
    return m_info+4;
}

int my::message::set(my::message *msg)
{
    memcpy(m_info, msg->data(), msg->length() + 4);
    return 0;
}

int my::message::set(uint16_t type)
{
    *((uint16_t *)(m_info+0)) = type;
    *((uint16_t *)(m_info+2)) = 0;
    memset(m_info+4, 0, my::message::MAX_LENGTH);
    return 0;
}

int my::message::set(uint16_t type, const void * info)
{
    *((uint16_t *)(m_info+0)) = type;
    *((uint16_t *)(m_info+2)) = std::min(
            (uint16_t)(strlen((const char *)info)), (uint16_t)(my::message::MAX_LENGTH));
    memcpy(m_info+4, info, *((uint16_t *)(m_info+2)));
    return 0;
}

int my::message::set(uint16_t type, uint16_t len, const void * info)
{
    *((uint16_t *)(m_info+0)) = type;
    *((uint16_t *)(m_info+2)) = std::min(len, (uint16_t)(my::message::MAX_LENGTH));
    memcpy(m_info+4, info, *((uint16_t *)(m_info+2)));
    return 0;
}

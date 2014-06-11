/*
 * =====================================================================================
 *
 *       Filename: gui/widget.cpp
 *        Created: 06/04/2014 06:42:29 PM
 *  Last Modified: 06/07/2014 11:32:59 AM
 *
 *    Description: widget
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

#include "./widget.hpp"

my::gui::widget::widget()
{
    m_x      = 0;
    m_y      = 0;
    m_id     = -1;
    m_width  = 0;
    m_height = 0;
    m_parent = nullptr;
}

my::gui::widget::~widget()
{
}


int my::gui::widget::set_id(int id)
{
    m_id = id;
    return 0;
}

int my::gui::widget::set_xy(int x, int y)
{
    m_x = x;
    m_y = y;
    return 0;
}

const int my::gui::widget::x()
{
    if(m_parent){
        return m_x + m_parent->x();
    }else{
        return m_x;
    }
}


const int my::gui::widget::y()
{
    if(m_parent){
        return m_y + m_parent->y();
    }else{
        return m_y;
    }
}

bool my::gui::widget::in(int newx, int newy)
{
    return (newx > x()) && (newx < (x() + m_width)) && (newy > y()) && (newy < y() + m_height);
}

const int my::gui::widget::width()
{
    return m_width;
}

const int my::gui::widget::height()
{
    return m_height;
}

const int my::gui::widget::id()
{
    return m_id;
}

const my::gui::widget *my::gui::widget::parent()
{
    return m_parent;
}

int my::gui::widget::update(int ms)
{
    return 0;
}

int my::gui::widget::set_focus(int id)
{
    return 0;
}

int my::gui::widget::set_parent(my::gui::widget *parent)
{
    m_parent = parent;
    return 0;
}

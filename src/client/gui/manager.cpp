/*
 * =====================================================================================
 *
 *       Filename: gui/manager.cpp
 *        Created: 06/04/2014 06:42:29 PM
 *  Last Modified: 06/07/2014 11:46:23 AM
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

#include <vector>
#include <memory>
#include "./widget.hpp"
#include "./manager.hpp"
#include "../sdlib/sdlib.hpp"

int my::gui::manager::process(sdlib::event *event)
{
    int res = 1;
    for(auto p: m_widgets){
        res = res * p->process(event);
    }

    return res;
}

int my::gui::manager::blit()
{
    // printf("%d\n", m_widgets.size());
    for(auto p = m_widgets.rbegin(); p != m_widgets.rend(); p++){
        (*p)->blit();
    }
    return 0;
}

int my::gui::manager::add(std::shared_ptr<my::gui::widget> widget, int x, int y)
{
    widget->set_xy(x, y);
    widget->set_parent(this);
    m_widgets.emplace_back(widget);
    return 0;
}

int my::gui::manager::update(int ms)
{
    for(auto p: m_widgets){
        p->update(ms);
    }
    return 0;
}

int my::gui::manager::set_focus(int id)
{
    for( auto &p: m_widgets ){
        if(id == p->id()){
            printf("focus changed\n");
            std::swap(p, m_widgets[0]);
            break;
        }
    }
    printf("out of focus changed\n");
    return 0;
}

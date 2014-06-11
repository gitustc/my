/*
 * =====================================================================================
 *
 *       Filename: gui/button.cpp
 *        Created: 06/04/2014 06:04:16 PM
 *  Last Modified: 06/07/2014 12:43:26 PM
 *
 *    Description: button
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

#include <cstdint>
#include <cstdlib>
#include <memory>
#include "./button.hpp"
#include "./widget.hpp"
#include "../package/package.hpp"

my::gui::button::button(uint8_t pre, uint8_t fid, uint16_t idx)
{
    m_on_pressed   = nullptr;
    m_on_released  = nullptr;
    m_pressed      = false;
    m_over         = false;
    
    std::shared_ptr<sdlib::bitmap>   pb1(package::image::retrieve(pre, fid, idx + 0, 0xff));
    std::shared_ptr<sdlib::bitmap>   pb2(package::image::retrieve(pre, fid, idx + 1, 0xff));
    m_tex1 = std::shared_ptr<sdlib::texture>(sdlib::graphics::create(pb1.get()));
    m_tex2 = std::shared_ptr<sdlib::texture>(sdlib::graphics::create(pb2.get()));

    m_width  = std::max(m_tex1->width(), m_tex2->width());
    m_height = std::max(m_tex1->height(), m_tex2->height());

}

my::gui::button::~button()
{
}

int my::gui::button::blit()
{
    if(m_over && m_pressed){
        sdlib::graphics::blit(m_tex2.get(), x()+2, y()+2, m_width, m_height, true);
    }else if(m_over){
        sdlib::graphics::blit(m_tex2.get(), x()+1, y()+1, m_width, m_height, true);
    }else{
        sdlib::graphics::blit(m_tex1.get(), x(), y(), m_width, m_height, true);
    }
    return 0;
}

int my::gui::button::process(sdlib::event *event)
{
    // printf("event\n");
    switch(event->type()){
        // case sdlib::event::MOUSEMOTION:
        case sdlib::event::MOUSEBUTTONDOWN:
            if(in(event->mouse_button_x(), event->mouse_button_y())){
                m_over    = true;
                m_pressed = true;
                if(m_on_pressed){
                    m_on_pressed();
                }
                if(m_parent){
                    m_parent->set_focus(m_id);
                }
                return 0;
            }else{
                m_over    = false;
                m_pressed = false;
                return 1;
            }
        case sdlib::event::MOUSEBUTTONUP:
            if(in(event->mouse_button_x(), event->mouse_button_y())){
                m_over    = true;
                m_pressed = false;
                if(m_on_released){
                    m_on_released();
                }
                if(m_parent){
                    m_parent->set_focus(m_id);
                }
                return 0;
            }else{
                m_over    = false;
                m_pressed = false;
                return 1;
            }
        case sdlib::event::MOUSEMOTION:
            if(in(event->mouse_motion_x(), event->mouse_motion_y())){
                m_over    = true;
                m_pressed = (bool)event->mouse_motion_state(sdlib::event::BUTTON_LEFT);
                return 0;
            }else{
                m_over    = false;
                m_pressed = false;
                return 1;
            }
        default:
            return 1;
    }
}

int my::gui::button::on_pressed(std::function<void()> hdr)
{
    m_on_pressed = hdr;
    return 0;
}

int my::gui::button::on_released(std::function<void()> hdr)
{
    m_on_released = hdr;
    return 0;
}

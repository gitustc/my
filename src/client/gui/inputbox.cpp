/*
 * =====================================================================================
 *
 *       Filename: gui/inputbox.cpp
 *        Created: 06/04/2014 06:10:53 PM
 *  Last Modified: 06/07/2014 11:56:50 AM
 *
 *    Description: input box
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
#include "./inputbox.hpp"

my::gui::inputbox::inputbox(int w, int h)
{
    m_focused = false;
    m_vbar    = false;
    m_ms      = 0;
    m_content = "";
    m_changed = true;
    m_width   = w;
    m_height  = h;
}

my::gui::inputbox::~inputbox()
{
}

int my::gui::inputbox::blit()
{
    if(m_content.size()>0){
        if(m_focused){
            if(m_changed){
                if(m_ms < 500){
                    m_content.push_back('<');
                    m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                    m_content.pop_back();
                    m_vbar = true;
                }else{
                    m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                    m_vbar = false;
                }
                m_changed = false;
            }else{
                if(m_ms < 500){
                    if(!m_vbar){
                        m_content.push_back('<');
                        m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                        m_content.pop_back();
                        m_vbar = true;
                    }
                }else{
                    if(m_vbar){
                        m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                        m_vbar = false;
                    }
                }
            }
        }else{
            if(m_changed){
                m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                m_changed = false;
            }else{
                if(m_vbar){
                    m_tex.reset(sdlib::graphics::create(sdlib::font::write(m_content.c_str(), {170, 170, 170, 0})));
                    m_vbar = false;
                }
            }
        }
        sdlib::graphics::blit(m_tex.get(), x(), y());
        return 0;
    }else{
        if(m_focused){
            if(m_ms < 500){
                if(!m_vbar){
                    m_tex.reset(sdlib::graphics::create(sdlib::font::write("<", {170, 170, 170, 0})));
                    m_vbar = true;
                }
                sdlib::graphics::blit(m_tex.get(), x(), y());
                return 0;
            }else{
                m_vbar = false;
                return 0;
            }
        }else{
            return 0;
        }
    }
}

int my::gui::inputbox::process(sdlib::event *event)
{
    switch(event->type()){
        case sdlib::event::KEYDOWN:
            if(m_focused){

                int32_t ret = event->key_name();
                int32_t ch  = ret - sdlib::event::KEY_A + 'a';

                if(ch >= 'a' && ch <= 'z' && m_content.size() < 12){
                    m_content.push_back(ch);
                    m_changed = true;
                }
                return 0;
            }else{
                return 1;
            }
        case sdlib::event::MOUSEBUTTONDOWN:
            if(in(event->mouse_button_x(), event->mouse_button_y())){
                if(m_parent){
                    m_parent->set_focus(m_id);
                }
                m_focused = true;
                return 0;
            }else{
                m_focused = false;
                return 1;
            }
        default:
            return 1;
    }
}

const char *my::gui::inputbox::content()
{
    return m_content.c_str();
}

int my::gui::inputbox::update(int ms)
{
    m_ms += ms;
    m_ms %= 1000;
    return 0;
}

/*
 * =====================================================================================
 *
 *       Filename: pwdbox.cpp
 *        Created: 06/04/2014 07:11:03 PM
 *  Last Modified: 06/10/2014 07:58:46 PM
 *
 *    Description: pwd
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

#include "./pwdbox.hpp"

my::gui::pwdbox::pwdbox(int w, int h):
    my::gui::inputbox(w, h)
{
    m_stars = "";
}

int my::gui::pwdbox::blit()
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

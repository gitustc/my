/*
 * =====================================================================================
 *
 *       Filename: gui/button.hpp
 *        Created: 06/04/2014 03:45:00 PM
 *  Last Modified: 06/07/2014 12:43:47 PM
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


#ifndef  _included_button_inc__
#define  _included_button_inc__

#include <memory>
#include <functional>
#include "./widget.hpp"

namespace my{
    namespace gui{
        class button: public widget{
            public:
                button(uint8_t, uint8_t, uint16_t);
                // button(uint8_t, uint8_t, uint16_t, std::function<void()>);
                ~button();
            public:
                int blit();
            public:
                int process(sdlib::event *);
            public:
                int on_pressed(std::function<void()>);
                int on_released(std::function<void()>);
            private:
                std::function<void()>  m_on_pressed;
                std::function<void()>  m_on_released;
            private:
                bool    m_pressed;
                bool    m_over;
            private:
                std::shared_ptr<sdlib::texture>     m_tex1;
                std::shared_ptr<sdlib::texture>     m_tex2;
        };
    };
};

#endif

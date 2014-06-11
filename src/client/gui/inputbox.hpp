/*
 * =====================================================================================
 *
 *       Filename: gui/inputbox.hpp
 *        Created: 06/04/2014 06:13:11 PM
 *  Last Modified: 06/07/2014 11:54:07 AM
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


#ifndef  _included_inputbox_inc__
#define  _included_inputbox_inc__


#include <string>
#include <memory>
#include "../sdlib/sdlib.hpp"
#include "./widget.hpp"

namespace my{
    namespace gui{
        class inputbox: public widget{
            public:
                inputbox(int, int);
                ~inputbox();
            public:
                const char * content();
            public:
                int blit();
                int update(int);
                int process(sdlib::event *);
            protected:
                std::shared_ptr<sdlib::texture> m_tex;
            protected:
                std::string m_content;
                bool        m_changed;
                int         m_ms;
                bool        m_vbar;
                bool        m_focused;
        };
    };
};



#endif

/*
 * =====================================================================================
 *
 *       Filename: manager.hpp
 *        Created: 06/04/2014 06:42:29 PM
 *  Last Modified: 06/07/2014 11:28:11 AM
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

#ifndef  _included_manger_inc__
#define  _included_manger_inc__



#include <vector>
#include <memory>
#include "./widget.hpp"
#include "../sdlib/sdlib.hpp"


namespace my{
    namespace gui{
        class manager: public widget{
            public:
                int process(sdlib::event *);
                int blit();
                int update(int);
            public:
                int set_focus(int);
            public:
                int add(std::shared_ptr<my::gui::widget>, int, int);
            private:
                std::vector<std::shared_ptr<my::gui::widget>> m_widgets;
        };
    };
};


#endif

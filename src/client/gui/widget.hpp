/*
 * =====================================================================================
 *
 *       Filename: widget.hpp
 *        Created: 06/04/2014 06:42:29 PM
 *  Last Modified: 06/07/2014 11:27:38 AM
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



#ifndef  _included_widget_inc__
#define  _included_widget_inc__

#include "../sdlib/sdlib.hpp"

namespace my{
    namespace gui{

        class widget{

            public:
                widget();
                virtual ~widget();

            public:
                virtual int process(sdlib::event *) = 0;
                virtual int blit() = 0;
            public:
                virtual int update(int);
                virtual int set_focus(int);
            public:
                bool in(int, int);
            public:
                int set_id(int);
                int set_xy(int, int);
                int set_parent(widget *);
            public:

            public:
                const int x();
                const int y();
                const int id();
            public:
                const int width();
                const int height();
            public:
                const widget *parent();
            protected:
                int m_width;
                int m_height;
                int m_x;
                int m_y;
                int m_id;
            protected:
                widget  *m_parent;
        };
    };
};


#endif

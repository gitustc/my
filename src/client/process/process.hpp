/*
 * =====================================================================================
 *
 *       Filename: process.hpp
 *        Created: 06/04/2014 03:58:00 PM
 *  Last Modified: 06/10/2014 08:29:54 PM
 *
 *    Description: 
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

#ifndef  _included_process_inc__
#define  _included_process_inc__

#include "../sdlib/sdlib.hpp"
#include "../../common/message.hpp"



namespace my{
    namespace process{
        enum{
            QUIT    = -1,
            LOGIN   = 0,
            MAIN    = 1,
            ALL
        };
        class base{
            public:
            public:
                base();
                virtual ~base();

            public:
                virtual int update(uint32_t) = 0;
                virtual int render()         = 0;
            public:
                virtual int on_recv(my::message *)        = 0;
                virtual int on_send(my::message *)        = 0;
                virtual int process_event(sdlib::event *) = 0;
            protected:
                int     m_state;

        };

    };
};
#endif

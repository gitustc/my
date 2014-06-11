/*
 * =====================================================================================
 *
 *       Filename: login.hpp
 *        Created: 06/04/2014 04:00:57 PM
 *  Last Modified: 06/10/2014 08:30:11 PM
 *
 *    Description: login process
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



#ifndef  _included_login_inc__
#define  _included_login_inc__




#include <thread>
#include <mutex>
#include <cstdint>
#include "../../gui/gui.hpp"
#include "../process.hpp"
namespace my{
    namespace process{
        class login: public base{
            public:
                login();
                ~login();
            public:
                int update(uint32_t);
                int render();
            public:
                int process_event(sdlib::event *);
                int on_recv(my::message *);
                int on_send(my::message *);
            private:
                my::gui::manager    m_manager;
            private:
                std::shared_ptr<sdlib::texture> m_background;
                std::shared_ptr<sdlib::texture> m_bar;
                std::shared_ptr<sdlib::texture> m_idpwd;
                std::shared_ptr<sdlib::texture> m_info;
            private:
                std::mutex          m_login_lock;
            private:
                int do_login(const char*, const char*);
        };
    };

};


#endif


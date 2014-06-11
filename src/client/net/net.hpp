/*
 * =====================================================================================
 *
 *       Filename: net.hpp
 *        Created: 06/07/2014 08:20:41 AM
 *  Last Modified: 06/10/2014 08:34:26 PM
 *
 *    Description: network
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


#ifndef  _included_net_inc__
#define  _included_net_inc__

#include <deque>
#include <thread>
#include <asio.hpp>
#include <functional>
#include "../../common/message.hpp"

namespace my{

    class net{
        public:
            static int init();
            static int stop();
            static int on_recv(std::function<void(my::message*)>);
            static int on_send(std::function<void(my::message*)>);
            static int send(const my::message*);
        private:
            net();
            ~net();
        private:
            int receive();
            int do_send();
        private:
            bool                    m_initialize;
            asio::io_service        m_io_service;
            asio::ip::tcp::resolver m_resolver;
            asio::ip::tcp::socket   m_socket;
            std::deque<my::message> m_messages;
            my::message             m_read_message;
        private:
            std::function<void(my::message*)>   m_on_recv_msg;
            std::function<void(my::message*)>   m_on_send_msg;
            std::shared_ptr<std::thread>        m_thread;

    };
};

#endif

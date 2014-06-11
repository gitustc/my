#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <asio.hpp>
#include <deque>
#include "../../common/message.hpp"

namespace my{

    class server;

    class session{
        public:
            session(asio::ip::tcp::socket, my::server *);

        public:
            int  id();
            void start();
            int  set_id(int);
            void deliver(const my::message *);
        private:
            void do_read_header();
            void do_read_body();
            void do_write();

        private:
            asio::ip::tcp::socket       m_socket;
            my::message                 m_read_message;
            my::server                 *m_server;
            std::deque<my::message>     m_write_messages;
            int                         m_id;
    };
};

#endif

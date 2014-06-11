#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <list>
#include <deque>
#include "session.hpp"
#include "../common/db.hpp"
#include "../../common/message.hpp"


namespace my{

    class server{

        public:
            server(asio::io_service&, const asio::ip::tcp::endpoint&);
        public:
            void    on_recv(my::message *, my::session *);
            void    stop(int);
            void    dispatch(my::message *);

        private:
            void    do_accept();
        private:
            my::db::connection      m_connection;
            asio::ip::tcp::acceptor m_acceptor;
            asio::ip::tcp::socket   m_socket;
        private:
            std::list<std::shared_ptr<my::session>> m_sessions;
        private:
            int     m_count;


        private:
            void on_recv_login_request(my::message *, my::session *);
            void on_recv_logoff_request(my::message *, my::session *);
    };
};
#endif

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include "asio.hpp"
#include "session.hpp"
#include "server.hpp"
#include "../../common/message.hpp"


my::session::session(asio::ip::tcp::socket socket,
        my::server *server):
    m_socket(std::move(socket)),
    m_server(server)
{
}

void my::session::start()
{
    do_read_header();
}

void my::session::deliver(const my::message *msg)
{
    bool tmp = m_write_messages.empty();
    m_write_messages.push_back(*msg);

    if(tmp){
        do_write();
    }
}

void my::session::do_read_header()
{
    auto tmp = [this](std::error_code ec, std::size_t){
        if(!ec){
            if(0 != m_read_message.length()){
                do_read_body();
            }else{
                m_server->on_recv(&m_read_message, this);
                // std::cout<<"new message: type = "<<m_read_message.type()<<", length = 0"<<std::endl;
                // m_server->dispatch(&m_read_message);
                do_read_header();
            }
        }else{
            m_server->stop(m_id);
        }
    };

    asio::async_read(m_socket,
            asio::buffer(m_read_message.data(), 4), tmp);
}

void my::session::do_read_body()
{
    auto tmp = [this](std::error_code ec, std::size_t){
        if(!ec){
            m_server->on_recv(&m_read_message, this);
            // std::cout<<"new message: type = "<<m_read_message.type()<<", length = "<<m_read_message.length()<<std::endl;
            // m_server->dispatch(&m_read_message);
            do_read_header();
        }else{
            m_server->stop(m_id);
        }
    };

    asio::async_read(m_socket,
            asio::buffer(m_read_message.body(), m_read_message.length()), tmp);
}


void my::session::do_write()
{
    auto tmp = [this](std::error_code ec, std::size_t){
        if(!ec){
            m_write_messages.pop_front();
            if(!m_write_messages.empty()){
                do_write();
            }
        }else{
            m_server->stop(m_id);
        }
    };

    asio::async_write(m_socket,
            asio::buffer(m_write_messages.front().data(), m_write_messages.front().length()+4), tmp);
}

int my::session::id()
{
    return m_id;
}

int my::session::set_id(int id)
{
    m_id = id;
    return 0;
}

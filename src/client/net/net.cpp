/*
 * =====================================================================================
 *
 *       Filename: net.cpp
 *        Created: 06/07/2014 09:20:50 AM
 *  Last Modified: 06/10/2014 09:05:24 PM
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
#include <deque>
#include <iostream>
#include "./net.hpp"

my::net::net():
    m_io_service(),
    m_resolver(m_io_service),
    m_socket(m_io_service),
    m_thread()
    // m_endp()
{
    m_initialize = false;

    m_on_recv_msg = [](my::message* msg){
        std::cout<<"receive message, type = "<<msg->type()<<" length = "<<msg->length()<<std::endl;
    };
    m_on_send_msg = [](my::message* msg){
        std::cout<<"send message, type = "<<msg->type()<<" length = "<<msg->length()<<std::endl;
    };
}

my::net::~net()
{
    m_io_service.stop();
    m_thread->join();
}

static my::net *g_net;
int my::net::init()
{
    static my::net s_net;
    g_net = &s_net;
    if(!(g_net->m_initialize)){
        auto tmp = [](std::error_code ec, asio::ip::tcp::resolver::iterator){
            if(!ec){
                printf("connect successed...\n");
                g_net->receive();
            }else{
                printf("connect failed...\n");
            }
        };
        asio::async_connect(g_net->m_socket, (g_net->m_resolver).resolve({"127.0.0.1", "3000"}), tmp);
        g_net->m_thread = std::make_shared<std::thread>([](){(g_net->m_io_service).run();});
        g_net->m_initialize = true;
    }
    return 0;
}

int my::net::receive()
{
    auto on_recv_body = [this](std::error_code ec, std::size_t){
        if(!ec){
            if(m_on_recv_msg){
                m_on_recv_msg(&m_read_message);
            receive();
            }
        }else{
            m_socket.close();
            m_io_service.stop();
        }

    };

    auto on_recv_header = [this, on_recv_body](std::error_code ec, std::size_t){
        if(!ec){
            if(0 != m_read_message.length()){
                asio::async_read(m_socket, 
                        asio::buffer(m_read_message.body(), m_read_message.length()), on_recv_body);
            }else{
                if(m_on_recv_msg){
                    m_on_recv_msg(&m_read_message);
                }
                receive();
            }
        }else{
            m_socket.close();
            m_io_service.stop();
        }
    };

    asio::async_read(m_socket,
            asio::buffer((g_net->m_read_message.data()), 4), on_recv_header);
    return 0;
}

int my::net::send(const my::message *msg)
{

    auto tmp = [msg](){
        bool flag = (g_net->m_messages).empty();
        (g_net->m_messages).push_back(*msg);
        if(flag){
            g_net->do_send();
        }

    };
    (g_net->m_io_service).post(tmp);

    return 0;
}

int my::net::do_send()
{
    auto tmp = [this](std::error_code ec, std::size_t){
        if(!ec){
            if(m_on_send_msg){
                m_on_send_msg(&(m_messages.front()));
            }
            m_messages.pop_front();
            if(!m_messages.empty()){
                do_send();
            }
        }else{
            m_socket.close();
            m_io_service.stop();
        }
    };
    asio::async_write(m_socket,
            asio::buffer(m_messages.front().data(), m_messages.front().length()+4), tmp);
    return 0;
}

int my::net::on_recv(std::function<void(my::message*)> hdr)
{
    g_net->m_on_recv_msg = hdr;
    return 0;
}

int my::net::on_send(std::function<void(my::message*)> hdr)
{
    g_net->m_on_send_msg = hdr;
    return 0;
}


int my::net::stop()
{
    g_net->m_io_service.stop();
    return 0;
}

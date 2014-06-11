/*
 * =====================================================================================
 *
 *       Filename: client.cpp
 *        Created: 06/04/2014 03:53:14 PM
 *  Last Modified: 06/10/2014 08:29:38 PM
 *
 *    Description: main
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
#include <memory>
#include "client.hpp"
#include "./net/net.hpp"
#include "./sdlib/sdlib.hpp"
#include "./package/package.hpp"
#include "./process/login/login.hpp"

my::client::client()
{
    sdlib::init();
    package::init();

    my::net::init();

    my::net::on_recv([this](my::message* msg){on_recv(msg);});
    my::net::on_send([this](my::message* msg){on_send(msg);});

    m_state = my::process::LOGIN;
    m_process.resize(my::process::ALL);

    m_process[my::process::LOGIN] = std::shared_ptr<my::process::login>(new my::process::login());
}

my::client::~client()
{
}

int my::client::start()
{
    uint32_t last_time;
    uint32_t current_time;

    current_time = sdlib::time();

    while(m_state != my::process::QUIT){

        if(m_state == my::process::MAIN){
            printf("OK, LOGIN SUCCEED, NOW IN MAIN PROCESS\n");
            break;
        }
        m_process[m_state]->render();

        sdlib::event event;
        while(sdlib::poll_event(&event)){
            m_process[m_state]->process_event(&event);
        }
        last_time    = current_time;
        current_time = sdlib::time();
        set_state(m_process[m_state]->update(current_time - last_time));

        sdlib::delay(50);
    }

    return 0;
}

int my::client::set_state(int newstate)
{
    if(m_state != newstate){
        m_state = newstate;
    }
    return 0;
}

int my::client::on_recv(my::message *msg)
{
    printf("on_recv: type = %u, length = %u\n", msg->type(), msg->length());
    return m_process[my::process::LOGIN]->on_recv(msg);
}

int my::client::on_send(my::message *msg)
{
    printf("on_send: type = %u, length = %u\n", msg->type(), msg->length());
    return m_process[my::process::LOGIN]->on_send(msg);
}

#include "server.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "../common/db.hpp"
#include "../../common/message.hpp"

my::server::server(asio::io_service &io_service,
        const asio::ip::tcp::endpoint &endpoint):
    m_acceptor(io_service, endpoint),
    m_socket(io_service)
{
    m_connection.connect();
    m_connection.query("use account");
    m_count = 0;
    do_accept();
}

void my::server::do_accept()
{
    auto tmp = [this](std::error_code ec){
        if(!ec){
            m_count++;

            my::message msg(my::message::NEWPLAYERADDED);
            dispatch(&msg);

            auto p = std::make_shared<my::session>(std::move(m_socket), this);
            p->start();
            m_sessions.emplace_back(p);
        }
        do_accept();
    };
    m_acceptor.async_accept(m_socket, tmp);
}

void my::server::stop(int id)
{
    for(auto p=m_sessions.begin(); p!=m_sessions.end(); ++p){
        if((*p)->id() == id){
            m_sessions.erase(p);
            break;
        }
    }
}

void my::server::dispatch(my::message *msg)
{
    for(auto p: m_sessions){
        p->deliver(msg);
    }
}

void my::server::on_recv_login_request(my::message *msg, my::session *p)
{
    char statement[1024];
    int  len = msg->length();

    char *p1, *p2;

    p1      = (char *) msg->body();
    p1[len] = '\0';
    p2      = strchr(p1, ':');
    *p2     = '\0';
    p2++;

    sprintf(statement, "select uid, pwd from account where id = \"%s\"", p1);
    fprintf(stdout, "select uid, pwd from account where id = \"%s\" || pwd = %s\n", p1, p2);
    m_connection.query(statement);

    for(int i=1;i<m_connection.rows();i++){
        printf("\n");
        for(int j=1;j<m_connection.columns();j++){
            printf("%s ", m_connection.get(i,j));
        }
    }
    printf("\n");

    if(!strcmp(m_connection.get(0, 1), p2)){
        printf("matched id and pwd, login succeed...\n");
        p->set_id(atoi(m_connection.get(0, 0)));
        my::message message(my::message::LOGINOK);
        p->deliver(&message);
    }else{
        printf("unmatched id and pwd...\n");
    }

}




void my::server::on_recv_logoff_request(my::message *msg, my::session *p)
{
    fprintf(stdout, "logoff requested\n");
    m_sessions.erase(remove_if(m_sessions.begin(), m_sessions.end(), 
            [p](std::shared_ptr<my::session> iter){return iter->id() == p->id();}), m_sessions.end());

}


void my::server::on_recv(my::message *msg, my::session *p)
{
    switch(msg->type()){
        case my::message::LOGIN:
            on_recv_login_request(msg, p);
            break;
        case my::message::LOGOFF:
            on_recv_logoff_request(msg, p);
            break;
        default:
            break;
    }
}

/*
 * =====================================================================================
 *
 *       Filename: login.cpp
 *        Created: 06/04/2014 04:00:57 PM
 *  Last Modified: 06/10/2014 08:37:42 PM
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

#include <cstdint>
#include <memory>
#include "./login.hpp"
#include "../../net/net.hpp"
#include "../../gui/gui.hpp"
#include "../../package/package.hpp"
#include "../../../common/message.hpp"


my::process::login::login()
{

    m_login_lock.lock();
    m_state = my::process::LOGIN;
    m_login_lock.unlock();

    m_background = std::shared_ptr<sdlib::texture>(
            sdlib::graphics::create(package::image::retrieve(0, 14, 1, 0xff)));
    m_bar  = std::shared_ptr<sdlib::texture>(
            sdlib::graphics::create(package::image::retrieve(0, 14, 2, 0x9f)));
    m_idpwd= std::shared_ptr<sdlib::texture>(
            sdlib::graphics::create(package::image::retrieve(0, 14, 3, 0x9f)));
    // m_info = std::shared_ptr<sdlib::texture>(
    //         sdlib::graphics::create(sdlib::font::write("hello", {0x00, 0xff, 0x00, 0xff})));

    auto hbtn1 = [](){
        printf("button cliked\n");
    };




    auto hbtn2 = [this](){
        printf("button cliked\n");
        my::message msg(my::message::LOGOFF);
        my::net::send(&msg);
    };

    // auto hbtn2 = [&idb, &pwdb](){
    //     printf("id  = %s\n",  idb->content());
    //     printf("pwd = %s\n", pwdb->content());
    // };
    // auto hbtn2 = [](){
    //     printf("pwdb here\n");
    // };
    std::shared_ptr<my::gui::button> btn1(new my::gui::button(0, 14, 13));
    std::shared_ptr<my::gui::button> btn2(new my::gui::button(0, 14, 15));
    std::shared_ptr<my::gui::button> btn3(new my::gui::button(0, 14, 11));

    std::shared_ptr<my::gui::button> btn4(new my::gui::button(0, 14, 17));

    std::shared_ptr<my::gui::inputbox> idb(new my::gui::inputbox(101, 20));
    std::shared_ptr<my::gui::pwdbox>   pwdb(new my::gui::pwdbox(101, 20));

    auto hbtn_login = [idb, pwdb, this](){
        // do not use reference here!!!
        do_login(idb->content(), pwdb->content());
    };

    btn1->on_released(hbtn1);
    btn2->on_released(hbtn1);
    btn3->on_released(hbtn_login);

    btn4->on_released(hbtn2);

    btn1->set_id(1);
    btn2->set_id(2);
    btn3->set_id(3);
    btn4->set_id(4);

    idb->set_id(5);
    pwdb->set_id(6);
    // btn2->set_id(1);
    // idb->set_id(2);

    m_manager.add(btn1, 200-45, 480);
    m_manager.add(btn2, 400-45, 480);
    m_manager.add(btn3, 600-45, 480);

    m_manager.add(btn4, 565, 538);

    m_manager.add(idb, 209, 547);
    m_manager.add(pwdb, 209+198, 548);
    // m_manager.add(btn2, 100, 100);
    // m_manager.add(idb, 200, 200);
    // m_manager.add(pwdb, 300, 300);
}


my::process::login::~login()
{
}


int my::process::login::update(uint32_t ms)
{
    m_manager.update(ms);

    m_login_lock.lock();
    int old_state = m_state;
    m_login_lock.unlock();

    return old_state;
}

int my::process::login::render()
{
    sdlib::graphics::clear();
    // blit background

    float ratio     = 1.0*sdlib::graphics::window_width()/m_background->width();
    int   newheight = m_background->height()*ratio;
    sdlib::graphics::blit( m_background.get(), 0, (sdlib::graphics::window_height()-newheight)/2, 
            sdlib::graphics::window_width(), newheight, true);

    ratio     = 1.0*sdlib::graphics::window_width()/m_bar->width();
    newheight = m_bar->height()*ratio;
    sdlib::graphics::blit( m_bar.get(), 0, 465, 
            sdlib::graphics::window_width(), newheight, true);

    sdlib::graphics::blit(m_idpwd.get(), 180, 543);

    m_manager.blit();

    sdlib::graphics::set_color(100, 100, 100, 0);
    sdlib::graphics::draw_rect(207, 545, 102, 20);
    sdlib::graphics::draw_rect(405, 545, 102, 20);
    sdlib::graphics::unset_color();

    /* sdlib::graphics::blit(m_info.get(), 300, 300); */
    sdlib::graphics::present();
    return 0;
}


int my::process::login::process_event(sdlib::event *event)
{
    m_manager.process(event);
    return 0;
}


int my::process::login::do_login(const char *id, const char *pwd)
{
    printf("try to login, id = %s pwd = %s\n", id, pwd);

    char body[256];
    sprintf(body, "%s:%s", id, pwd);
    my::message msg(my::message::LOGIN, body);
    my::net::send(&msg);
    return 0;
}


int my::process::login::on_recv(my::message *msg)
{
    switch(msg->type()){
        case my::message::LOGINOK:
            m_login_lock.lock();
            printf("login successsed...\n");
            m_state = my::process::MAIN;
            m_login_lock.unlock();
            break;
        case my::message::LOGINERROR:
            printf("login failed...\n");
            break;
        default:
            break;
    }
    return 0;
}

int my::process::login::on_send(my::message *msg)
{
    switch(msg->type()){
        case my::message::LOGOFF:
            printf("logoff message sent...\n");
            my::net::stop();
            m_login_lock.lock();
            m_state = my::process::QUIT;
            m_login_lock.unlock();
            break;
        default:
            break;
    }
    return 0;
}

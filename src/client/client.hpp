/*
 * =====================================================================================
 *
 *       Filename: client.hpp
 *        Created: 06/04/2014 03:52:02 PM
 *  Last Modified: 06/10/2014 08:33:43 PM
 *
 *    Description: main body
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


#include <vector>
#include <memory>
#include "./process/process.hpp"
#include "../common/message.hpp"

namespace my{
    class client{

        public:
            client();
            virtual ~client();
        public:
            int start();
        private:

            int set_state(int);
            int on_send(my::message *);
            int on_recv(my::message *);

        private:
            int m_state;
        // private:
        //     int m_last_recv;
        //     int m_last_send;
        private:
            std::vector<std::shared_ptr<my::process::base>>   m_process;
    };
};

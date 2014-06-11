/*
 * =====================================================================================
 *
 *       Filename: message.hpp
 *        Created: 06/07/2014 10:31:59 AM
 *  Last Modified: 06/10/2014 08:33:12 PM
 *
 *    Description: message
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



#ifndef  _included_message_inc__
#define  _included_message_inc__

#include <cstdint>


namespace my{
    class message{

        public:
            enum{
                MAX_LENGTH                  = 1024,
            };
            enum{
                NONE                        = 0,
                LOGIN,
                LOGINOK,
                LOGINERROR,
                LOGOFF,

                NEWPLAYERADDED,
            };

        public:
            message();
            message(uint16_t);
            message(uint16_t, const void *);
            message(uint16_t, uint16_t, const void *);

        public:
            uint16_t  type();
            uint16_t  length();
        public:
            uint8_t *data();
            uint8_t *body();
        public:
            int set(message*);
            int set(uint16_t);
            int set(uint16_t, const void *);
            int set(uint16_t, uint16_t, const void *);
        private:
            uint8_t m_info[MAX_LENGTH + 2 * sizeof(uint16_t)];
    };
};



#endif


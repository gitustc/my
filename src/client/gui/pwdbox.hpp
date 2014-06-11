/*
 * =====================================================================================
 *
 *       Filename: gui/pwdbox.hpp
 *        Created: 06/04/2014 07:09:31 PM
 *  Last Modified: 06/06/2014 08:29:20 PM
 *
 *    Description: pwd
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



#ifndef  _included_pwdbox_inc__
#define  _included_pwdbox_inc__

#include <string>
#include "./inputbox.hpp"
namespace my{
    namespace gui{
        class pwdbox: public inputbox{
            public:
                pwdbox(int, int);
            public:
                int blit();
            private:
                std::string m_stars;
        };
    };
};






#endif


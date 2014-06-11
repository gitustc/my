/*
 * =====================================================================================
 *
 *       Filename: db.hpp
 *        Created: 06/08/2014 09:02:31 PM
 *  Last Modified: 06/10/2014 05:25:57 PM
 *
 *    Description: connection to sql database
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


#ifndef  _included_db_inc__
#define  _included_db_inc__


#include <mysql.h>

namespace my{
    namespace db{
        class connection{
            public:
                connection();
                ~connection();
            public:
                int connect();
                int query(const char *);
                int rows();
                int columns();
            public:
                const char *get(int, int);
            private:
                MYSQL       *m_connection;
                MYSQL_RES   *m_res;
        };
    };
};

#endif


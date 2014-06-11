/*
 * =====================================================================================
 *
 *       Filename: db.cpp
 *        Created: 06/08/2014 09:11:51 PM
 *  Last Modified: 06/10/2014 05:27:46 PM
 *
 *    Description: db
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

#include "./db.hpp"

my::db::connection::connection()
{
    m_connection = mysql_init(nullptr);
    m_res        = nullptr;
}

my::db::connection::~connection()
{
    if(m_connection){
        mysql_close(m_connection);
    }
    if(m_res){
        mysql_free_result(m_res);
    }
}

int my::db::connection::connect()
{
    if(m_connection){
        return !(m_connection == mysql_real_connect( m_connection, 
                    "127.0.0.1", "root", "hah86918", "helloworld", 0, nullptr, 0));
    }else{
        return 1;
    }
}

int my::db::connection::rows()
{
    if(m_connection && m_res){
        return mysql_num_rows(m_res);
    }else{
        return 0;
    }
}

int my::db::connection::columns()
{
    if(m_connection && m_res){
        return mysql_num_fields(m_res);          
    }else{
        return 0;
    }
}

int my::db::connection::query(const char *cmd)
{
    if(m_res){
        mysql_free_result(m_res);
        m_res = nullptr;
    }
    if(m_connection && (!mysql_query(m_connection, cmd)) && (m_res = mysql_store_result(m_connection))){
        return 0;
    }else{
        return 1;
    }
}

const char *my::db::connection::get(int i, int j)
{
    if(m_connection && m_res && i >= 0 && i < rows() && j>=0 && j < columns()){
        mysql_data_seek(m_res, i);
        MYSQL_ROW sqlrow = mysql_fetch_row(m_res);
        return sqlrow[j];
    }else{
        return nullptr;
    }
}

/*
 * =====================================================================================
 *
 *       Filename: bitmap.hpp
 *        Created: 06/01/2014 06:53:43 PM
 *  Last Modified: 06/02/2014 06:32:47 PM
 *
 *    Description: 
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


#ifndef  _included_bitmap_inc__
#define  _included_bitmap_inc__


namespace sdlib{
    class bitmap{

        public:
            bitmap();
            bitmap(int, int);
        public:
            virtual ~bitmap();
        public:
            void *buffer();
            int  resize(int, int);
            int  width();
            int  height();

        private:
            int     m_width;
            int     m_height;
            int     m_length;
            void    *m_buffer;
    };
};


#endif

/*
 * =====================================================================================
 *
 *       Filename: ./package/./imagehandler.hpp
 *        Created: 05/31/2014 05:36:37 PM
 *  Last Modified: 06/05/2014 08:53:40 PM
 *
 *    Description: singleton for image
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


#ifndef  _included_imagehandler_inc__
#define  _included_imagehandler_inc__





#include <memory>
#include <cstdint>
#include <vector>
#include <SDL2/SDL.h>
#include "../sdlib/sdlib.hpp"
#include "./imagepackage.hpp"
#include "../sdlib/bitmap.hpp"

namespace package{
    class image{
        private:
            image();
            virtual ~image();

        public:
            static int  init();
            static int  free();
        public:
            static sdlib::bitmap *retrieve(uint8_t, uint8_t, uint16_t, uint8_t);
            static int  blit(
                    uint8_t, uint8_t, uint16_t,     // index for image
                    void *,                         // buffer
                    int, int,                       // corresponding point
                    int, int,                       // buffer size
                    int,                            // 4 for uint32_t
                    uint32_t, uint32_t, uint8_t);   // masks
        private:
            std::vector<std::shared_ptr<package::imagepackage>>     m_images; 
        private:
            bool    m_initialize;

    };

};






#endif

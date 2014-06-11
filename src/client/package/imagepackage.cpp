#include "./imagepackage.hpp"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "msdndef.hpp"

static void memcpy16to32(uint32_t *dst, uint16_t *src, int n, uint8_t alpha)
{
    for (int ptr = 0; ptr < n; ptr++){

        uint16_t p;
        uint8_t  r, g, b;

        p = src[ptr];

        r = (uint8_t)((p & 0XF800) >> 8);
        g = (uint8_t)((p & 0X07E0) >> 3);
        b = (uint8_t)((p & 0X001F) << 3);

        dst[ptr] = ((uint32_t)alpha << 24) + ((uint32_t)r << 16) + ((uint32_t)g << 8) +(uint32_t)b;
    }
}

package::imagepackage::imagepackage()
{
    m_fp                            = nullptr;
    m_current_buffer                = nullptr;
    m_wix_image_info.position       = nullptr;
    m_current_wil_image_info.length = 0;
}

// package::imagepackage::imagepackage(package::imagepackage&& other)
// {
//     m_fp                                  = other.m_fp;
//     m_current_buffer                      = other.m_current_buffer;
//     m_current_image_index                 = other.m_current_image_index;
//
//     memcpy(&m_wix_image_info, &(other.m_wix_image_info), sizeof(WIXIMAGEINFO));
//     memcpy(&m_current_wil_image_info, &(other.m_current_wil_image_info), sizeof(WILIMAGEINFO));
//
//     other.m_fp                            = nullptr;
//     other.m_current_buffer                = nullptr;
//     other.m_current_image_index           = 0;
//
//     memset(&(other.m_wix_image_info), 0, sizeof(WIXIMAGEINFO));
//     memset(&(other.m_current_wil_image_info), 0, sizeof(WILIMAGEINFO));
// }

package::imagepackage::~imagepackage()
{
    if(m_fp){
        fclose(m_fp);
    }
    if(m_current_buffer){
        free(m_current_buffer);
    }
    if(m_wix_image_info.position){
        free(m_wix_image_info.position);
    }
}

int package::imagepackage::width()
{
    return m_current_wil_image_info.width;
}

int package::imagepackage::height()
{
    return m_current_wil_image_info.height;
}
int package::imagepackage::load(const char *wil_file)
{
    if(strlen(wil_file) < 128){

        FILE    *fp_wix = nullptr;
        char    wix_file[128];

        printf("enter...\n");
        strcpy(wix_file, wil_file);
        strcpy(wix_file+strlen(wix_file)-3, "wix");
        printf("%s\n", wix_file);

        fp_wix = fopen(wix_file, "rb");
        if(!fp_wix){
            printf("fail to open: %s\n", wix_file);
            return 1;
        }
        fread(&m_wix_image_info, sizeof(WIXIMAGEINFO)-sizeof(int32_t*), 1, fp_wix);

        m_current_image_index = m_wix_image_info.count;
        printf("image number: %u\n", m_wix_image_info.count);

        m_wix_image_info.position = (int32_t *)malloc(m_wix_image_info.count * sizeof(int32_t));
        if(!m_wix_image_info.position){
            printf("fail to malloc position\n");
            return 1;
        }
        fread(m_wix_image_info.position, sizeof(int32_t) * m_wix_image_info.count, 1, fp_wix);

        printf("before close\n");
        fclose(fp_wix);
        printf("after close\n");

        m_fp = fopen(wil_file, "rb");
        if(!m_fp){
            printf("fail to open %s:\n", wil_file);
            return 1;
        }

        printf("out...\n");
        return 0;
    }
    return 1;
}

int package::imagepackage::set_index(uint32_t index)
{
    if(m_current_image_index != index){
        if(m_wix_image_info.position[index] > 0 && index < m_wix_image_info.count){

            uint32_t old_length = m_current_wil_image_info.length;
            fseek(m_fp, m_wix_image_info.position[index], SEEK_SET);
            fread(&m_current_wil_image_info, sizeof(WILIMAGEINFO), 1, m_fp);

            if(m_current_buffer){
                if(old_length < m_current_wil_image_info.length){
                    free(m_current_buffer);
                    m_current_buffer = malloc(m_current_wil_image_info.length * sizeof(uint16_t));
                }
            }else{
                m_current_buffer = malloc(m_current_wil_image_info.length * sizeof(uint16_t));
            }
            fread(m_current_buffer, m_current_wil_image_info.length * sizeof(uint16_t), 1, m_fp);
            m_current_image_index = index;
        }
    }
    return 0;
}


int package::imagepackage::decompress(
        uint16_t index,                                     // image index
        void *dstptr,                                       // buffer for drawing
        int dx, int dy,                                     // coordinate for drawing on *dst*
        int dwidth, int dheight,                            // buffer size
        int dpixsize,                                       // 4 for uint32_t
        uint32_t mask1, uint32_t mask2,                     // masks
        uint8_t alpha)                                      // alpha
{
    set_index(index);

    uint16_t    *psrc   = (uint16_t *)m_current_buffer;
    uint32_t    *pdst   = (uint32_t *)dstptr;

    // (dx, dy) on buffer <-> (0, 0) on image
    // here both dx and dy may be negative because of stuff when drawing object
    // this is the simplest way for blit
    // do think it as too complicated

    int swidth    = m_current_wil_image_info.width;
    int sheight   = m_current_wil_image_info.height;

    int rc_left   = (dx < 0) ? (-1*dx) : 0;
    int rc_top    = (dy < 0) ? (-1*dy) : 0;

    int rc_right  = (dx+swidth-dwidth   > 0) ? (dwidth-dx)  : swidth;
    int rc_bottom = (dy+sheight-dheight > 0) ? (dheight-dy) : sheight;

    if(rc_left >= 0 && rc_top >= 0 && 
            rc_right >= 0  && rc_bottom >= 0 && 
            rc_right > rc_left && rc_bottom > rc_top){

        int width_start   = 0;
        int width_end     = 0;
        int current_width = 0;
        int copied_word   = 0;
        int currenty      = 0;
        int last_width    = 0;

        for(currenty = 0; currenty < rc_top; currenty++){
            width_end += psrc[width_start];
            width_end++;
            width_start = width_end;
        }

        for(currenty = rc_top ;currenty < rc_bottom ;currenty++){
            width_end += psrc[width_start];
            width_start++;

            for(int x = width_start; x < width_end;){
                if(psrc[x] == 0xC0){
                    // jump code
                    x++;
                    copied_word = psrc[x];
                    x++;
                    current_width += copied_word;
                }else if(psrc[x] == 0xC1 || psrc[x] == 0xC2 || psrc[x] == 0xC3){
                    x++;
                    copied_word = psrc[x];
                    x++;

                    last_width = current_width;
                    current_width += copied_word;

                    if(rc_left > current_width || rc_right < last_width){
                        // data is out of the rectangle
                        // skip it just
                        x += copied_word;
                    }else{
                        // data is in the rectangle
                        // three cases and handle it one by one
                        if(last_width < rc_left && rc_left <= current_width){
                            x += (rc_left-last_width);
                            memcpy16to32(&pdst[((currenty+dy) * dwidth) + (rc_left+dx)], &psrc[x], (current_width-rc_left), alpha);
                            x += (current_width-rc_left);
                        }else if(last_width <= rc_right && rc_right < current_width){
                            memcpy16to32(&pdst[((currenty+dy) * dwidth) + (last_width+dx)], &psrc[x], (rc_right-last_width), alpha);
                            x += copied_word;
                        }else{
                            memcpy16to32(&pdst[((currenty+dy) * dwidth) + (last_width+dx)], &psrc[x], copied_word, alpha);
                            x += copied_word;
                        }
                    }
                }
            }
            width_end++;

            width_start   = width_end;
            current_width = 0;
        }
    }
    return 0;
}

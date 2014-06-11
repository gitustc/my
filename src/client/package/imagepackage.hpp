#ifndef  _included_imagepackage_inc__
#define  _included_imagepackage_inc__

#include <cstdint>
#include <cstdlib>
#include <cstdio>

#pragma pack(push, 1)

typedef struct{
    uint8_t	    title[20];
    uint32_t    count;
    int32_t     *position;      // I am not sure here for uint32_t or int32_t
}WIXIMAGEINFO;

typedef struct{
    int16_t	    width;
    int16_t	    height;
    int16_t	    px;
    int16_t	    py;
    uint8_t	    shadow;					
    int16_t	    shadowpx;
    int16_t	    shadowpy;
    uint32_t	length;
}WILIMAGEINFO;

#pragma pack(pop)


namespace package{

    class imagepackage{

        public:
            imagepackage();
            // imagepackage(package::imagepackage&&);
            // imagepackage(imagepackage&&);
            ~imagepackage();

        public:
            int width();
            int height();
            int load(const char *);
            int set_index(uint32_t);

            int decompress(
                    uint16_t,                            // image index
                    void *,                              // buffer for drawing
                    int, int,                            // coordinate for drawing on *dst*
                    int, int,                            // buffer size
                    int,                                 // 4 for uint32_t
                    uint32_t, uint32_t, uint8_t);        // masks
        private:
            FILE                *m_fp;
            void                *m_current_buffer;

            uint32_t            m_current_image_index;
            WIXIMAGEINFO		m_wix_image_info;
            WILIMAGEINFO        m_current_wil_image_info;

    };
};

#endif

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <stdint.h>
#include "fblib_util.hpp"

namespace fblib{
        class device{
    private:
        int fbfd;
        int dev_fb_size;
        char* dev_fb;

        struct fb_var_screeninfo vinfo;
        struct fb_fix_screeninfo finfo;
    public:
        device();
        ~device();
        
        int get_fbfd();
        int get_x_res();
        int get_y_res();
        int get_x_offset();
        int get_y_offset();
        int get_linelength();
        int get_bpp();
        char* get_device_fb();
        int get_device_fb_size();

        void set_pixel(uint32_t,uint32_t,Color);

        // DEBUG to stdout
        void print_device_info();
    };
}

#endif

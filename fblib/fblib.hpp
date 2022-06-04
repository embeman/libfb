#ifndef _FBLIB_HPP_
#define _FBLIB_HPP_

#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>

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

    class display
    {
    private:
        device* fb_dev;
        int xres;
        int yres;
        int bpp;
        int buffer_size;
        char* screen_buffer;
        int margin;
    public:

        display();
        // delete copy constructor only one instane of display should be created
        display(const display&) = delete;
       ~display();

        void draw_line(uint32_t,uint32_t,uint32_t,uint32_t,Color);
        void clear_screen();
        void draw_obj(const char*,Color);
        // DEBUG ONLY
        void print();

    };
};



#endif
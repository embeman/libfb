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
        // DEBUG ONLY
        void print();

    };
};



#endif
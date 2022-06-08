#ifndef _FBLIB_HPP_
#define _FBLIB_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>

#include "fblib_util.hpp"
#include "interface.hpp"

namespace fblib{

    class display
    {
    private:
        device* fb_dev;
        int xres;
        int yres;
        int bpp;
    public:

        display();
        // delete copy constructor only one instane of display should be created
        display(const display&) = delete;
       ~display();

        void draw_line(uint32_t,uint32_t,uint32_t,uint32_t,Color);
        void draw_line(Vec2 , Vec2,Color);
        void clear_screen();
        
    };
};



#endif
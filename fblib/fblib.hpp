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
        int max_x;
        int max_y;
    public:

        display();
        // delete copy constructor only one instane of display should be created
        display(const display&) = delete;
       ~display();

        int get_max_x(){return max_x;}
        int get_max_y(){return max_y;}

        void draw_line(uint32_t,uint32_t,uint32_t,uint32_t,Color);
        void draw_line(Vec2 , Vec2,Color);
        void clear_screen();
        
    };
};



#endif
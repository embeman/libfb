#ifndef _FBLIB_HPP_
#define _FBLIB_HPP_

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>
#include <vector>

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

        void draw_line(int,int,int,int,Color);
        void draw_line(Vec2 , Vec2,Color);
        void draw_line_new(int,int,int,int,Color);

        void draw_wirefram_triangle(Vec2,Vec2,Vec2,Color);
        void draw_filled_triangle(Vec2,Vec2,Vec2,Color);

        void clear_screen();
        void set_pixel(uint32_t,uint32_t,Color);

        std::vector<int> Interpolate(int i0,int d0, int i1, int d1){
        std::vector<int> values;
        if (i0 == i1)
        {
            values.push_back(d0);
            return values;
        }
        
        int a = (d0-d1) / (i0-i1);
        int d = d0;
        for (int i = i0; i < i1; i++){
            values.push_back(d);
            d = d + a;
        }
        return values;
    }
    
        
    };


    
};



#endif
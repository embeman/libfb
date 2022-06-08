#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string>

#include "fblib.hpp"
#include "fblib_util.hpp"

fblib::display::display(){
    fb_dev = new device();
    
    // read information from device memory 
    xres = fb_dev->get_x_res();
    yres = fb_dev->get_y_res();
    bpp = fb_dev->get_bpp();
}

fblib::display::~display(){
    delete this->fb_dev;
}

void fblib::display::draw_line(uint32_t x0,uint32_t y0,uint32_t x1 ,uint32_t y1, Color color){
    int a = (int)(y1-y0)/(int)(x1-x0);
    int b = y0 - (a * x0);
    int y = y0;
    for (int x = x0; x < x1; x++)
    {
        fb_dev->set_pixel(x,y,color);
        y = y + a;
    }
    
}

void fblib::display::draw_line(Vec2 P0,Vec2 P1 ,Color color){
    int a = (P1.y() - P0.y()) /(P1.x() - P0.x());
    int b = P0.y() - (a * P0.x());
    int y = P0.y();
    for (int x = P0.x(); x < P1.x(); x++)
    {
        fb_dev->set_pixel(x , y , color);
        y += a;
    }
          
}


void fblib::display::clear_screen(){
    Color color(0xFF , 0xFF , 0xFF , 0xFF);
    for(int y = 0; y < yres; y++){
        for (int x = 0; x < xres; x++)
        {
            fb_dev->set_pixel(x,y,color);
        }
    }
}

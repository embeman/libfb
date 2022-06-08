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
    max_x = fb_dev->get_max_x();
    max_y = fb_dev->get_max_y();
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
    this->draw_line(P0.x() , P0.y() , P1.x() , P1.y() , color);    
}


void fblib::display::clear_screen(){
    Color color(0xFF , 0xFF , 0xFF , 0xFF);
    for(int y = max_y * -1 ; y < max_y; y++){
        for (int x = max_x * -1; x < max_x; x++)
        {
            fb_dev->set_pixel(x,y,color);
        }
    }
}

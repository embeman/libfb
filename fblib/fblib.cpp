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
    buffer_size = fb_dev->get_device_fb_size();
    // Get Device FrameBuffer
    screen_buffer = fb_dev->get_device_fb();
    /*
    MUST LEAVE MARGIN IN ALL SIDES
    could be calculated by finding the time of each pixle 
    struct 
        __u32 left_margin;      
        __u32 right_margin;     
        __u32 upper_margin;     
        __u32 lower_margin;
     */
    margin = 20;
}

fblib::display::~display(){
    delete this->fb_dev;
}

void fblib::display::draw_line(uint32_t x0,uint32_t y0,uint32_t x1 ,uint32_t y1, 
                                        Color color){
    bool steep = false; 
    if (std::abs((float)(x0-x1))<std::abs((float)(y0-y1))) { // if the line is steep, we transpose the image 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { // make it left−to−right 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            fb_dev->set_pixel(y, x, color); 
        } else { 
            fb_dev->set_pixel(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    }
}

void fblib::display::clear_screen(){
    Color color(0x00 , 0x22 , 0x33 , 0xFF);
    for(int y = margin; y < yres - margin; y++){
        for (int x = margin; x < xres - margin; x++)
        {
            fb_dev->set_pixel(x,y,color);
        }
    }
}

// DEBUG ONLY
void fblib::display::print(){
    std::cout << "xres : " << xres << std::endl << "yres : " << yres << std::endl << "bpp : " << bpp << std::endl
        << "FramBuffer Size : " << buffer_size << std::endl;
}

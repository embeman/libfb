#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>

#include "fblib.hpp"
#include "fblib_util.hpp"
#include "../model.h"
#include "../geometry.h"
fblib::device::device(){
    // Open framebuffer driver
    fbfd = open("/dev/fb0" , O_RDWR);
    if (fbfd < 0)
    {
        std::cout << "Error Opening \"/dev/fb0\" Are You Root ?!!\n";
        exit(EXIT_FAILURE);             // terminate the program
    }else{
        std::cout << "<<FrameBuffer Read Done Succefully>>\n";
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        std::cout << "Error reading fixed information.\n";
        exit(EXIT_FAILURE);
    }else{
        std::cout << "<<Fixed Info Read Done Succefully>>\n";
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        std::cout << "Error reading variable information.\n";
        exit(EXIT_FAILURE);
    }else{
        std::cout << "<<Varriable Info Read Done Succefully>>\n";
    }

    /* 
        Mappnig device Memory to dev_fb
    */

    // calculate screen size in bytes
    dev_fb_size = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device memory to dev_fb
    dev_fb = (char *)mmap(0, dev_fb_size, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd , 0);
    if (dev_fb == (char*)-1) {
        std::cout << "Error: failed to map framebuffer device to memory.\n";
        exit(EXIT_FAILURE);
    }else{
        std::cout << "<<FrameBuffer Mapped Succefully>>\n";
    }
}

fblib::device::~device(){
    munmap(dev_fb, dev_fb_size);
    close(fbfd);
}

void fblib::device::set_pixel(uint32_t x ,uint32_t y,fblib::Color color){
    int location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;

    *(dev_fb + location) = color.red();
    *(dev_fb + location + 1) = color.green();
    *(dev_fb + location + 2) = color.blue();
    *(dev_fb + location + 3) = color.alpha();
}

int fblib::device::get_fbfd(){  return fbfd;    }
char* fblib::device::get_device_fb(){ return dev_fb; }
int fblib::device::get_device_fb_size(){ return dev_fb_size; }
int fblib::device::get_bpp(){  return vinfo.bits_per_pixel;  }
int fblib::device::get_x_res(){  return vinfo.xres;  }
int fblib::device::get_y_res(){  return vinfo.yres;  }
int fblib::device::get_x_offset(){ return vinfo.xoffset;}
int fblib::device::get_y_offset(){ return vinfo.yoffset;}
int fblib::device::get_linelength(){ return finfo.line_length;}


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
    Color color(0xFF , 0xFF , 0xFF , 0xFF);
    for(int y = margin; y < yres - margin; y++){
        for (int x = margin; x < xres - margin; x++)
        {
            fb_dev->set_pixel(x,y,color);
        }
    }
}

void fblib::display::draw_obj(const char* path,Color c){
    Model m(path);
    
    std::cout << m.nfaces() << std::endl << m.nverts() << std::endl;

    for (int i=0; i<m.nfaces(); i++) { 
    std::vector<int> face = m.face(i); 
        for (int j=0; j<3; j++) { 
            Vec3f v0 = m.vert(face[j]); 
            Vec3f v1 = m.vert(face[(j+1)%3]); 
            int x0 = (v0.x+1.)*1300/2.; 
            int y0 = (v0.y+1.)*700/2.; 
            int x1 = (v1.x+1.)*1300/2.;
            int y1 = (v1.y+1.)*700/2.; 
            draw_line(x0,y0,x1,y1,c);
        } 
    }
}

// DEBUG ONLY
void fblib::display::print(){
    std::cout << "xres : " << xres << std::endl << "yres : " << yres << std::endl << "bpp : " << bpp << std::endl
        << "FramBuffer Size : " << buffer_size << std::endl;
}

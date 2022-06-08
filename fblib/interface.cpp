#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>

#include "interface.hpp"
#include "fblib_util.hpp"


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

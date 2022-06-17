#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <string>
#include <bits/stdc++.h>

#include "fblib.hpp"

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

void fblib::display::set_pixel(uint32_t x,uint32_t y, Color color){
    fb_dev->set_pixel(x,y,color.red() , color.green() , color.blue() , color.alpha());
}

void fblib::display::draw_line(int x0,int y0,int x1 ,int y1, Color color){
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
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
            set_pixel(y, x, color); 
        } else { 
            set_pixel(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    }    
}

void fblib::display::draw_line(Vec2 P0,Vec2 P1 ,Color color){
    this->draw_line(P0.x() , P0.y() , P1.x() , P1.y() , color);    
}


void fblib::display::draw_wirefram_triangle(Vec2 P0,Vec2 P1,Vec2 P2,Color color){
    draw_line(P0 , P1 , color);
    draw_line(P1 , P2 , color);
    draw_line(P0 , P2 , color);
}

void fblib::display::draw_filled_triangle(Vec2 P0,Vec2 P1,Vec2 P2,Color color){
    // sort the points so that y0 < y1 < y2
    if (P0.y() > P1.y()){
        // swap P0 and P1
        P0.swap(&P1);
    }

    if (P0.y() > P2.y())
    {
        // swap P0 and P2
        P0.swap(&P2);
    }
    
    if (P1.y() > P2.y())
    {
        // swap P1 and P2
        P1.swap(&P2);
    }


    // Calculate X values for each side
    std::vector<int> x01 = Interpolate(P0.y() , P0.x() , P1.y() , P1.x());
    std::vector<int> x12 = Interpolate(P1.y() , P1.x() , P2.y() , P2.x());        
    std::vector<int> x02 = Interpolate(P0.y() , P0.x() , P2.y() , P2.x());

    // remove last element in x01
    x01.pop_back();
    // concatinate x01 , x12
    std::vector<int> x012;
    x012.insert(x012.end() , x01.begin() , x01.end());
    x012.insert(x012.end() , x12.begin() , x12.end());

    std::vector<int>* x_left;
    std::vector<int>* x_right;

    int m = floor(x012.size() / 2);
    if (x02[m] < x012[m]) {
        x_left = &x02;
        x_right = &x012;
    } else {
        x_left = &x012;
        x_right = &x02;
    }

    for (int y = P0.y(); y < P2.y(); y++)
    {
        for (int x = (*x_left)[y - P0.y()] ; x < (*x_right)[y - P0.y()]; x++)
        {
            set_pixel(x,y,color);
        }   
    }
}

void fblib::display::clear_screen(){
    Color white(0xFF , 0xFF , 0xFF , 0xFF);
    for(int y = max_y * -1 ; y < max_y; y++){
        for (int x = max_x * -1; x < max_x; x++)
        {
            fb_dev->set_pixel(x,y,white.red(),white.green(),white.blue(),white.alpha());
        }
    }
}

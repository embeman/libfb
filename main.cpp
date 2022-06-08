#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>
#include <thread>
#include <chrono>
#include "fblib/fblib.hpp"
using namespace fblib;

int main(){
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    // Testing set pixel
    Color black(0x00,0x00,0x00,0x00);
    Color white(0xFF,0xFF,0xFF,0xFF);
    Color red(0xFF,0x00,0x00,0x00);
    Color green(0x00,0xFF,0x00,0x00);
    Color blue(0x00,0x00,0xff,0x00);

    // Test Switch to cartisean
    device d;
    int max_x = d.get_max_x();
    int max_y = d.get_max_y();

    // upper-right quorter
    for (int x = 0; x < max_x; x++)
    {
        for (int y = 0; y < max_y; y++)
        {
            d.set_pixel(x,y , white);
        }
        
    }
    // down-right quorter
    for (int x = 0; x < max_x; x++)
    {
        for (int y = max_y * -1 ; y < 0; y++)
        {
            d.set_pixel(x,y , red);
        }
    }
    
    // upper-left quorter
    for (int x = max_x * -1; x < 0; x++)
    {
        for (int y = 0 ; y < max_y; y++)
        {
            d.set_pixel(x,y , green);
        }
    }
    // down-left quorter
    for (int x = max_x * -1; x < 0; x++)
    {
        for (int y = max_y * -1 ; y < 0; y++)
        {
            d.set_pixel(x,y , blue);
        }
    }
    
    
    
    while(1);
    

    return 0;

}

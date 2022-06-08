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

    display d;
    int max_x = d.get_max_x();
    int max_y = d.get_max_y();

    d.clear_screen();
    d.draw_line(0,0,max_x,max_y,red);
    d.draw_line(0,0,0, 90,red);
    d.draw_line(0,0,200,500,red);
    d.draw_line(0,0,100,200,red);

    while(1);
    

    return 0;

}

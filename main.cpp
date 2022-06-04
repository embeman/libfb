#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <string>

#include "fblib/fblib.hpp"
#include "fblib/fblib_util.hpp"
#include "model.h"
#include "geometry.h"

int main(){
    fblib::display testDisplay;
    testDisplay.print();
    testDisplay.clear_screen();
    fblib::Color c(0x00,0x00,0xff,0xff);
    testDisplay.draw_obj("body.obj",c);
    while (1);

    
    return 0;

}

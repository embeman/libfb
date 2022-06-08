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

int main(){
    fblib::display testDisplay;
    testDisplay.print();
    testDisplay.clear_screen();
    while (1);

    
    return 0;

}

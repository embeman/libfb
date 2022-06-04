#ifndef _FBLIB_UTILL_
#define _FBLIB_UTILL_

#include <stdint.h>


namespace fblib{
    class Color {
    private:
        uint8_t _r;
        uint8_t _g;
        uint8_t _b;
        uint8_t _a;
        uint32_t _c;
    public:
        Color(uint8_t red,uint8_t green,uint8_t blue,uint8_t alpha) : _r(red) , _g(green),_b(blue) , _a(alpha){};
        Color(uint32_t color) : _c(color){};
        uint32_t color(){return _c;}
        uint8_t red(){return _r;}
        uint8_t green(){return _g;}
        uint8_t blue(){return _b;}
        uint8_t alpha(){return _a;}
    };

    class Vec2{
        private:
            int _x;
            int _y;

        public:
        Vec2() = delete;
        Vec2(uint32_t X,uint32_t Y) : _x(X) , _y(Y){}
    };

}

#endif
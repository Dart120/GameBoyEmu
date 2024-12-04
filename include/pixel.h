
#ifndef PIXEL_H
#define PIXEL_H
#include<iostream>

struct Pixel {
    uint8_t color;
    bool palette;
    bool bg_priority;

    Pixel(uint8_t color, bool palette, bool bg_priority): color(color), palette(palette), bg_priority(bg_priority) {}
};


#endif
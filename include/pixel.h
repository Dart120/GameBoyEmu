
#ifndef PIXEL_H
#define PIXEL_H
#include<iostream>

struct Pixel {
    uint8_t color;
    uint8_t color_idx;
    Pixel(uint8_t color, uint8_t color_idx): color(color), color_idx(color_idx) {}
};


#endif

#ifndef SpritePixel_H
#define SpritePixel_H
#include<iostream>

struct SpritePixel {
    uint8_t color;
    uint8_t oam_idx;


    SpritePixel(uint8_t color, uint8_t oam_idx): color(color), oam_idx(oam_idx) {}
};


#endif
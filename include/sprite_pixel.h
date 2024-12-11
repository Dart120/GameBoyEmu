
#ifndef SpritePixel_H
#define SpritePixel_H
#include<iostream>

struct SpritePixel {
    uint8_t color;
    
    uint8_t oam_idx;
    uint8_t color_idx;
    bool bg_priority;


    SpritePixel(uint8_t color, uint8_t oam_idx,uint8_t color_idx, bool bg_priority): 
    color(color), oam_idx(oam_idx), color_idx(color_idx), bg_priority(bg_priority) {}
};


#endif
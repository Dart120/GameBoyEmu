
#ifndef SPRITE_H
#define SPRITE_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "modes.h"
#include "tiledata.h"
#include "background.h"
#include "window.h"
#include "objects.h"
#include "display_ctl.h"
#include "pixel_fetcher.h"
#include "pixel.h"
#include <vector>
#include <queue>
#include <map>
#include <array>





struct Sprite {
    uint8_t y_pos;
    uint8_t x_pos;
    uint8_t tile_number;
    uint8_t sprite_flags;
    uint8_t oam_idx;
    bool palette(){
        return (bool) ((sprite_flags >> 4) & 1);
    }
    bool x_filp(){
        return (bool) ((sprite_flags >> 5) & 1);
    }
    bool y_filp(){
        return (bool) ((sprite_flags >> 6) & 1);
    }
    bool obj_bg_priority(){
        return (bool) ((sprite_flags >> 7) & 1);
    }
};

#endif


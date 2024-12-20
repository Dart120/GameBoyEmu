
#ifndef PF_H
#define PF_H
// #include<iostream>
// #define FMT_HEADER_ONLY
#include "memory.h"
#include "modes.h"
#include "tiledata.h"
#include "background.h"
#include "window.h"
#include "objects.h"
#include "display_ctl.h"
#include "pixel.h"
#include "sprite_pixel.h"
#include "sprite.h"
#include <vector>
#include <queue>
#include <map>
#include <array>




class PixelFetcher
{
    
    public:
    PixelFetcher(Memory& memory, std::queue<Sprite>& to_display, bool& fetching_sprites, bool& tall_mode);

    Memory& memory;
    std::queue<Sprite>& to_display;
    bool& tall_mode;
    bool& fetching_sprites;
    
    PF_MODES mode = PF_MODES::GET_TILE;
    PF_MODES sprite_mode = PF_MODES::GET_TILE;
    uint8_t X_POS;
    bool rendering_window;
    void switch_to_window();
    std::queue<Pixel> BG_FIFO;
    std::queue<SpritePixel> S_FIFO;
    void process_2_cycles(uint8_t LY, bool should_push);
    void get_tile(uint8_t LY);
    void reset(bool stall, bool switching_to_sprite);
    void populate_sprite_fifo(uint8_t LY, bool should_push);
    uint8_t idx_to_color(uint8_t LY);
    uint8_t sprite_idx_to_color(uint8_t LY, bool use_OBP1);
    uint8_t pixel_mixing();
    
    uint8_t tile_number;
    uint8_t sprite_tile_number;
    uint8_t WLC;
    uint16_t tile_addr_lower;
    uint16_t tile_addr_upper;
    uint16_t tile_data_upper;
    uint16_t tile_data_lower;
    uint16_t sprite_tile_addr_lower;
    uint16_t sprite_tile_addr_upper;
    uint16_t sprite_tile_data_upper;
    uint16_t sprite_tile_data_lower;
    bool first_time_on_line = true;
    

   
};

#endif
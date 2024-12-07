
#ifndef GPU_H
#define GPU_H
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



class GPU
{
    
    public:
    GPU(Memory& memory, MODES& GPU_modes, int scale);

    Memory& memory;
    
    TileData tiledata;
    Background background;
    Window window;
    Objects object;
    MODES GPU_modes;
    PixelFetcher pixel_fetcher;
    std::vector<Sprite> sprite_buffer;
    long clock = 0;
    uint8_t line = 0;

    std::queue<Pixel> Sprite_FIFO;
    std::array<std::array<u_int8_t,160>,144> buffer;
    Display_Ctl display_ctl;
    uint8_t X_POS = 0;
    uint8_t dump_counter = 0;
    bool WYeqLY = false; 
  
    const int t_cycles_in_OAM_scan = 80;
    const int t_cycles_in_V_blank = 4560;
    int cycles_left = 80;
    int mode_2_limit = 456 - 80;
    int mode_3_limit = mode_2_limit - 172;
    uint8_t H_BLANK_cycles;
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    
   
    void do_4_dots();
    void update_LY();
    void OAM_scan();
    void drawScanLine();
    void drawBackground();
    std::vector<uint8_t> readTileData(uint8_t tileIdx, uint8_t dataStart);
    bool DRAW_2_dots(u_int8_t LY);
    void check_window(uint8_t LY);
    bool check_EOL();

    const int DOTS_PER_LINE = 456;
    const int MAX_LY = 153;
    const int VP_ROWS = 144;
    const int VP_COLS = 160;
    void drawTileLine (std::vector<uint8_t>  tileData, uint8_t line, uint8_t x);
    
   


};

#endif
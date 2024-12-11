
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

    std::queue<Pixel> Sprite_FIFO;
    std::array<std::array<u_int8_t,160>,144> buffer;
    std::queue<Sprite> to_display;
    Display_Ctl display_ctl;
    uint8_t X_POS = 0;
    uint8_t dump_counter = 0;
    bool WYeqLY = false; 
    int clock = 0;
    const int t_cycles_in_OAM_scan = 80;
    const int t_cycles_in_V_blank = 4560;
    int cycles_left = 80;
    int mode_2_limit = 456 - 80;
    int mode_3_limit = mode_2_limit - 172;
    bool tall_mode = false;
    uint8_t H_BLANK_cycles;
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    
   
    void do_4_dots();
    void OAM_scan();
    bool DRAW_2_dots(u_int8_t LY);
    void check_window(uint8_t LY);
    bool check_EOL();
    void check_sprite_buffer();

    const int DOTS_PER_LINE = 456;
    const int MAX_LY = 153;
    const int VP_ROWS = 144;
    const int VP_COLS = 160;
    bool fetching_sprites = false;
    
   


};

#endif
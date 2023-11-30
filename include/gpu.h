
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
#include <vector>
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
    MODES& GPU_modes;
    std::array<std::array<u_int8_t,160>,144> buffer;
    Display_Ctl display_ctl;
    std::array<u_int8_t,160> curr_line;
    int clock = 0;
    int mode_2_limit = 456 - 80;
    int mode_3_limit = mode_2_limit - 172;
    // Going to point to the actual memory in my computer coz i want to read more than eight bits of this at a time and using the 16 bit idx of the array might make that a faff
    
    void render();
    void do_4_dots();
    void get_line(u_int8_t line_n);
    const int DOTS_PER_LINE = 456;
    const int MAX_LY = 153;
    const int VP_ROWS = 144;
    const int VP_COLS = 160;
    
   


};
#endif
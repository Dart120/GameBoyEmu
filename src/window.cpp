#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "window.h"
#include "memory.h"
#include <array>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>


u_int8_t* Window::get_tile_data(u_int8_t address) {
        return this->tiledata->getBGTile(address);
    }
u_int8_t Window::read_tilemap_n(u_int8_t x, u_int8_t y, u_int8_t line_n){
    u_int16_t idx = x + (y * 32);
    u_int16_t starting_at = this->memory.get_bit_from_addr(0xFF40,6) ? 0xC800 : 0x9800;
    return this->memory.read_8_bit(starting_at + idx);
}

// TODO the same to background
std::array<u_int8_t,160> Window::read_line(u_int8_t line){
    this->tiledata->read_tiledata();
    this->line_n_to_colours();
    

    auto between = [](u_int16_t* range, uint16_t address) {return address >= range[0] and address <= range[1]; };
    u_int8_t WY = this->memory.read_8_bit(0xFF4A);
    u_int8_t WX = this->memory.read_8_bit(0xFF4B) - 7;
    

    std::array<u_int8_t,160> pixels;
    // Five is the value that we will use to show that the window was undefined here
    pixels.fill(5);
 
    if (line < WY){
        return pixels;
    }
    u_int16_t window_line = line - WY;

    for (size_t i = WX; i < 160; i++)
    {
        pixels[i] = this->colour_map[window_line][i - WX];
     
    }
    
    
    return pixels;
}

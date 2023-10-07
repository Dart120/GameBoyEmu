#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "window.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

u_int8_t* Window::get_tile_data(u_int8_t address) {
        return this->tiledata->getBGTile(address);
    }
u_int8_t Window::read_tilemap_n(u_int8_t x, u_int8_t y){
    u_int8_t idx = x + (y * 32);
    u_int8_t starting_at = this->memory.get_bit_from_addr(0xFF40,6) ? 0xC800 : 0x9800;
    return this->memory.read_8_bit(starting_at + idx);
}

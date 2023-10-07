#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "background.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

// TODO Translate tiledata to colour map
u_int8_t* Background::get_tile_data(u_int8_t address) {
    // std::cout << this->memory.mem[0]<<std::endl;
        return this->tiledata->getBGTile(address);
    }
u_int8_t Background::read_tilemap_n(u_int8_t x, u_int8_t y){
    u_int8_t idx = x + (y * 32);
    u_int8_t starting_at = this->memory.get_bit_from_addr(0xFF40,3) ? 0xC800 : 0x9800;
    return this->memory.read_8_bit(starting_at + idx);
}

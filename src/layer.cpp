#include<iostream>
#include "Registers.h"
#define FMT_HEADER_ONLY
#include <fmt/core.h> 
#include <vector>
#include <algorithm>
#include "layer.h"
#include "memory.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
#include <map>

Layer::Layer(Memory& memory,TileData& tiledata): memory(memory), tiledata(tiledata){
        this->memory = memory;
        this->tiledata = tiledata;
        this->tilemap_starts_at = tilemap_starts_at;
        
    }

uint8_t Layer::tile_idx_at(uint8_t x, uint8_t y){
    uint8_t idx = y * 32 + x;
    return tilemap[idx];
}
void Layer::tile_data_to_colour_map(){
    for (size_t i = 0; i < 65536; i++){
        // figure out pixel_idx
        
        u_int8_t pix_y = i / 256;
        u_int8_t pix_x = i % 256;
        // figure out tile idx
        u_int8_t tile_y = pix_y / 8;
        u_int8_t tile_x = pix_x / 8;
        // figure out offset from corner of tile
        u_int8_t tile_pix_y = pix_y % 8;
        u_int8_t tile_pix_x = pix_x % 8;
        // need to get appropriate tilemap
        // based on bit in lcdc
        // get tile idx and tile data
        u_int8_t tile = this->read_tilemap_n(tile_x,tile_y);
        u_int8_t* tiledata = this->get_tile_data(tile);
        // how many bits have passed us coz of our row
        u_int8_t row = tile_pix_y * 16;
        // which coloumns to use
        u_int8_t f_col = tile_pix_x;
        u_int8_t s_col = tile_pix_x + 8;
        // get the bits and add them, this is our colour
        u_int8_t low = (*tiledata) >> (row + f_col) & 1;
        u_int8_t high = ((*tiledata) >> (row + s_col) & 1) << 1;
        this->colour_map[i] =  high + low;
    }
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 128; ++j) {
            // Calculate the appropriate index in the 1D array
            int index = i * 128 + j;
            std::cout << this->colour_map[index] << "\t";  // Use tab to space out the values
        }
        std::cout << std::endl;  // Move to the next line after printing each row
    }
    
}
